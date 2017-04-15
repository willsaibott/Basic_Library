#ifndef GRAPHALGORITHMS_H
#define GRAPHALGORITHMS_H
#include "GraphNode.h"
#include "HeuristicTable.h"


#define MIN_PATH_ALGORITHM_DIJKSTRA 1
#define MIN_PATH_ALGORITHM_BELLMAN_FORD 2
#define MIN_PATH_ALGORITHM_A_STAR 3
#define MIN_PATH_ALGORITHM_FLOYD_WARSHALL 4
#define MIN_PATH_ALGORITHM_JOHNSON 5

#define INF_NEGATIVE -1.7E+308
#define INF_POSITIVE 1.7E+308

#define ERROR_CODE_NODE_NOT_EXIST -13101310
#define ERROR_CODE_HEURISTIC_FUNCTION_NOT_DEFINED -10101313
#define LAST_NODE_UNKNOW 0
#define ERROR_CODE_NODE_NOT_REACHABLE INF_POSITIVE

template <class A>
struct weight_association{
    A start, last;
    GraphNode<A> *target;
    Weight weight, gWeight;
    List<A> visitedNodes;
};

struct graph_path_index{
    int start;
    int target;
};



template <class A>
class GraphAlgorithms{
private:
    static graph_path_index getIndex(List<GraphNode<A>*> nodes, A start, A target);
    static int getAssociationIndex(List<weight_association<A>*> *weightTable, A start, A target);

public:
    GraphAlgorithms(){}

    static weight_association<A>* getNew_WeightAssociation(A startNode, GraphNode<A> *targetNode, A lastNode, Weight weight);
    static List<weight_association<A>*> * Dijkstra(List<GraphNode<A>*> nodes, A startNode, A targetNode, bool printable);
    static List<weight_association<A>*> * BellmanFord(List<GraphNode<A>*> nodes, A startNode, A targetNode, bool printable, bool isNegative);
    static List<weight_association<A>*> * A_star(List<GraphNode<A>*> nodes, A startNode, A targetNode, Weight* (*heuristicFunction)(Weight*, int, int), bool printable);
    static List<weight_association<A>*> *FloydWarshall(List<GraphNode<A>*> nodes, bool printable, bool isNegative);
    static List<weight_association<A>*> *Johnson(List<GraphNode<A>*> nodes, bool printable, bool isNegative);

    static Weight **graphInMatrix(List<GraphNode<A>*> nodes);
    static List<weight_association<A>*> *matrixToListOfWeightAssociation(Weight** matrix, Size size, List<GraphNode<A>*> nodes);
};

template <class A>
graph_path_index GraphAlgorithms<A>::getIndex(List<GraphNode<A> *> nodes, A start, A target){
    graph_path_index index;
    index.start = ELEMENT_NOT_FOUND;
    index.target = ELEMENT_NOT_FOUND;


    for (int i = 0; i < nodes.getSize(); i++){
        nodes[i]->setVisited(false);
        if (compare(nodes[i]->getData(), start)==0)
            index.start = i;
        if (compare(nodes[i]->getData(), target)==0)
            index.target = i;

    }

    return index;
}

template <class A>
int GraphAlgorithms<A>::getAssociationIndex(List<weight_association<A>*> *weightTable, A start, A target){
    for (int i = 0; i < weightTable->getSize(); i++){
        if (compare((*weightTable)[i]->start, start)==0 && compare((*weightTable)[i]->target->getData(), target)==0){
            return i;
        }
    }
    return ELEMENT_NOT_FOUND;
}

template <class A>
weight_association<A> *GraphAlgorithms<A>::getNew_WeightAssociation(A startNode, GraphNode<A> *targetNode, A lastNode, Weight weight){
    weight_association<A> *wa = new weight_association<A>;
    wa->last = lastNode;
    wa->start = startNode;
    wa->target = targetNode;
    wa->weight = weight;
    return wa;
}

template <class A>
List<weight_association<A>*> * GraphAlgorithms<A>::Dijkstra(List<GraphNode<A>*> nodes, A startNode, A targetNode, bool printable){
    Weight weightAcumulated = 0;
    Weight nextMinWeight = weightAcumulated;
    List<weight_association<A>*> *weightTable = new List<weight_association<A>*>;
    weight_association<A> *wa;
    graph_path_index index = getIndex(nodes, startNode, targetNode);
    GraphNode<A> *nodeFocused, *nextNodeFocused;
    if (index.start==ELEMENT_NOT_FOUND || index.target==ELEMENT_NOT_FOUND){
        if (printable)
            cout << "\nError Code: Node Does not exist";
        return NULL;
    }

    nodeFocused = nodes.get(index.start).getData();
    nextNodeFocused = nodeFocused;

    if (printable)
        cout << endl;

    weightTable->insert(getNew_WeightAssociation(nodeFocused->getData(), nodeFocused, nodeFocused->getData(), 0));
    while (true){
        if (printable){
            cout << "\n-> " << nodeFocused->getData();
            cout << "\nWT:\\n";
            for (int i = 0; i < weightTable->getSize(); i++)
                cout << "(" << (*weightTable)[i]->start << ", " << (*weightTable)[i]->target->getData() << ", " << (*weightTable)[i]->last << ", " << (*weightTable)[i]->weight << "), ";
            cout << endl;
        }
        nextMinWeight = 0;
        for (int i = 0; i < nodeFocused->getAdjacentNodeList()->getSize(); i++){
            Weight adj_weight = (*nodeFocused->getEdgesWeightList())[i];
            GraphNode<A> *adj_node = (*nodeFocused->getAdjacentNodeList())[i];

            int key = getAssociationIndex(weightTable, startNode, adj_node->getData());

            if (key!=ELEMENT_NOT_FOUND){
                if (compare((*weightTable)[key]->weight, (weightAcumulated + adj_weight))>0){
                    wa = (*weightTable)[key];
                    wa->last = nodeFocused->getData();
                    wa->weight = (weightAcumulated + adj_weight);

                }

                if ((compare(nextMinWeight, ((*weightTable)[key]->weight)) > 0 || nextMinWeight == 0) && (*weightTable)[key]->weight >= weightAcumulated && !adj_node->isVisited()){
                    nextMinWeight = ((*weightTable)[key]->weight);
                    nextNodeFocused = adj_node;

                }

            }
            else{
                weightTable->insert(getNew_WeightAssociation(startNode, adj_node, nodeFocused->getData(), weightAcumulated + adj_weight));

                if (Value<Weight>::compare(nextMinWeight, (weightAcumulated + adj_weight)) > 0 || nextMinWeight == 0){
                    nextMinWeight = (weightAcumulated + adj_weight);
                    nextNodeFocused = adj_node;

                }

            }
        }


        nodeFocused->setVisited(true);
        if (nextNodeFocused->isVisited()){
            nextNodeFocused = NULL;
            for (int i = 0; i < weightTable->getSize(); i++){
                if (!(*weightTable)[i]->target->isVisited()){
                    if (nextMinWeight > (*weightTable)[i]->weight || nextNodeFocused==NULL){
                        nextMinWeight = ((*weightTable)[i]->weight);
                        nextNodeFocused = ((*weightTable)[i]->target);
                    }
                }
            }
            if (nextNodeFocused==NULL)
                return weightTable;
        }
        weightAcumulated = nextMinWeight;
        nodeFocused = nextNodeFocused;


    }
    if (printable)
        cout << endl;

    return weightTable;
}

template <class A>
List<weight_association<A>*> * GraphAlgorithms<A>::Johnson(List<GraphNode<A>*> nodes, bool printable, bool isNegative){
    List<weight_association<A>*> *weightTable = new List<weight_association<A>*>;
    List<weight_association<A>*> *aux;
    if (nodes.getSize()>0){
        if (isNegative){
            for (int i = 0; i < nodes.getSize()-1; i++){
                aux = BellmanFord(nodes, nodes[i]->getData(), nodes[nodes.getSize()-1]->getData(), printable, isNegative);
                for (int j = 0; j < aux->getSize(); j++)
                    weightTable->insert((*aux)[j]);
            }
            aux = BellmanFord(nodes, nodes[nodes.getSize()-1]->getData(), nodes[0]->getData(), printable, isNegative);
            for (int j = 0; j < aux->getSize(); j++)
                weightTable->insert((*aux)[j]);
        }else{
            for (int i = 0; i < nodes.getSize() -1; i++){
                aux = Dijkstra(nodes, nodes[i]->getData(), nodes[nodes.getSize()-1]->getData(), printable);
                for (int j = 0; j < aux->getSize(); j++)
                    weightTable->insert((*aux)[j]);
            }
            aux = Dijkstra(nodes, nodes[nodes.getSize()-1]->getData(), nodes[0]->getData(), printable);
            for (int j = 0; j < aux->getSize(); j++)
                weightTable->insert((*aux)[j]);
        }
    }
    return weightTable;
}



template <class A>
List<weight_association<A>*> * GraphAlgorithms<A>::BellmanFord(List<GraphNode<A> *> nodes, A startNode, A targetNode, bool printable, bool isNegative){
    Weight weightAcumulated = 0;
    List<weight_association<A>*> *weightTable = new List<weight_association<A>*>;
    graph_path_index index = getIndex(nodes, startNode, targetNode);
    GraphNode<A> *nodeFocused;
    weight_association<A> *wa;
    bool isRunning = true;
    uint iteration = 0;
    int key;

    if (index.start==ELEMENT_NOT_FOUND || index.target==ELEMENT_NOT_FOUND){
        if (printable)
            cout << "\nError Code: Node Does not exist";
        return NULL;
    }

    nodeFocused = nodes.get(index.start).getData();


    wa = getNew_WeightAssociation(startNode, nodeFocused, startNode, 0);
    wa->visitedNodes.insert(wa->last);
    weightTable->insert(wa);


    while (isRunning) {
        isRunning = false;

        if (printable){
            cout << "\titeration: " << ++iteration;
            cout << "\nWT:\\n";
            for (int i = 0; i < weightTable->getSize(); i++)
                cout << "(" << (*weightTable)[i]->start << ", " << (*weightTable)[i]->target->getData() << ", " << (*weightTable)[i]->last << ", " << (*weightTable)[i]->weight << "), ";
            cout << endl;
        }

        for (int j = 0; j < weightTable->getSize(); j++){
            nodeFocused = (*weightTable)[j]->target;
            weightAcumulated = (*weightTable)[j]->weight;
            for (int i = 0; i < nodeFocused->getAdjacentNodeList()->getSize(); i++){
                Weight adj_weight = (*nodeFocused->getEdgesWeightList())[i];
                GraphNode<A> *adj_node = (*nodeFocused->getAdjacentNodeList())[i];

                key = getAssociationIndex(weightTable, startNode, adj_node->getData());

                if (key!=ELEMENT_NOT_FOUND){
                    if (compare((*weightTable)[key]->weight, (weightAcumulated + adj_weight))>0){
                        if (isNegative)
                            if ((*weightTable)[key]->visitedNodes.contain(adj_node->getData()))
                                continue;

                        wa = (*weightTable)[key];
                        wa->last = nodeFocused->getData();
                        wa->weight = (weightAcumulated + adj_weight);
                        if (isNegative){
                            int key2 = getAssociationIndex(weightTable, startNode, nodeFocused->getData());
                            List<A>::copyList((*weightTable)[key2]->visitedNodes, &(wa->visitedNodes));
                            wa->visitedNodes.insert(adj_node->getData());
                        }
                        isRunning = true;
                        weightTable->setElement(wa, key);
                    }
                }
                else{
                    isRunning = true;
                    wa = getNew_WeightAssociation(startNode, adj_node, nodeFocused->getData(),(weightAcumulated + adj_weight));
                    if (isNegative){
                        int key2 = getAssociationIndex(weightTable, startNode, nodeFocused->getData());
                        List<A>::copyList((*weightTable)[key2]->visitedNodes, &(wa->visitedNodes));
                        wa->visitedNodes.insert(adj_node->getData());
                    }
                    weightTable->insert(wa);

                }


            }
        }

    }

    return weightTable;
}

template <class A>
List<weight_association<A>*> * GraphAlgorithms<A>::A_star(List<GraphNode<A> *> nodes, A startNode, A targetNode, Weight *(*heuristicFunction)(Weight *, int, int), bool printable){
    if (heuristicFunction==NULL || heuristicFunction==NULL)
        return NULL;
    Weight weightAcumulated = 0;
    Weight nextMinWeight = weightAcumulated, lastGWeight = weightAcumulated, nextLastGWeight = lastGWeight;
    Weight *hWeight = new Weight[nodes.getSize()];
    List<weight_association<A>*> *weightTable = new List<weight_association<A>*>;
    weight_association<A> *wa;
    graph_path_index index = getIndex(nodes, startNode, targetNode);
    GraphNode<A> *nodeFocused, *nextNodeFocused;
    HeuristicTable ht;
    int iteration = 0;
    bool solutionFound = false, isRunning = true, firstComparison;

    if (index.start==ELEMENT_NOT_FOUND || index.target==ELEMENT_NOT_FOUND){
        if (printable)
            cout << "\nError Code: Node Does not exist";
        return NULL;
    }


    nodeFocused = nodes.get(index.start).getData();
    nextNodeFocused = nodeFocused;

    if (printable)
        cout << endl;

    ht.runIteration(heuristicFunction, hWeight, iteration++, nodes.getSize());
    wa = getNew_WeightAssociation(nodeFocused->getData(), nodeFocused, nodeFocused->getData(), lastGWeight+ht[index.start]);
    weightTable->insert(wa);
    while (isRunning){
        solutionFound = (solutionFound)? true: (compare(nodeFocused->getData(), targetNode)!=0);

        if (printable){
            cout << "\n-> " << nodeFocused->getData();
            cout << "\nWT:\\n";
            for (int i = 0; i < weightTable->getSize(); i++)
                cout << "(" << (*weightTable)[i]->start << ", " << (*weightTable)[i]->target->getData() << ", " << (*weightTable)[i]->last << ", " << (*weightTable)[i]->weight << ", " << (*weightTable)[i]->gWeight << "), ";
            cout << endl;
        }
        firstComparison = true;
        for (int i = 0; i < nodeFocused->getAdjacentNodeList()->getSize(); i++){
            Weight adj_weight = (*nodeFocused->getEdgesWeightList())[i];
            GraphNode<A> *adj_node = (*nodeFocused->getAdjacentNodeList())[i];

            int key = getAssociationIndex(weightTable, startNode, adj_node->getData());

            if (key!=ELEMENT_NOT_FOUND){
                int key2 = getAssociationIndex(weightTable, startNode, nodeFocused->getData());
                if (compare((*weightTable)[key]->weight, ((*weightTable)[key2]->gWeight + adj_weight + ht[nodes.getPos(adj_node, BEGIN)]))>0){
                    adj_node->setVisited(false);
                    wa = (*weightTable)[key];
                    wa->last = nodeFocused->getData();
                    wa->gWeight = ((*weightTable)[key2]->gWeight + adj_weight);
                    wa->weight = wa->gWeight + ht[nodes.getPos(adj_node, BEGIN)];
                }

                if ((compare(nextMinWeight, ((*weightTable)[key]->weight)) > 0 || firstComparison) && !adj_node->isVisited()){
                    nextMinWeight = ((*weightTable)[key]->weight);
                    nextNodeFocused = adj_node;
                    nextLastGWeight = (*weightTable)[key]->gWeight;
                    firstComparison = false;
                }

            }
            else{
                Weight hw = ht[nodes.getPos(adj_node, BEGIN)];
                wa = getNew_WeightAssociation(startNode, adj_node, nodeFocused->getData(), lastGWeight + adj_weight+hw);
                wa->gWeight = lastGWeight + adj_weight;

                weightTable->insert(wa);

                if (compare(nextMinWeight, (wa->weight)) > 0 || firstComparison ){
                    nextMinWeight = wa->weight;
                    nextNodeFocused = adj_node;
                    nextLastGWeight = wa->gWeight;
                    firstComparison = false;
                }

            }
        }

        nodeFocused->setVisited(true);
        if (nextNodeFocused->isVisited()){
            nextNodeFocused = NULL;
            for (int i = 0; i < weightTable->getSize(); i++){
                if (!(*weightTable)[i]->target->isVisited()){
                    if (nextMinWeight > (*weightTable)[i]->weight || nextNodeFocused==NULL){
                        nextMinWeight = ((*weightTable)[i]->weight);
                        nextNodeFocused = ((*weightTable)[i]->target);
                        nextLastGWeight = (*weightTable)[i]->gWeight;
                    }
                }
            }

            if (nextNodeFocused==NULL)
                break;

        }
        weightAcumulated = nextMinWeight;
        lastGWeight = nextLastGWeight;
        nodeFocused = nextNodeFocused;
        ht.runIteration(heuristicFunction, hWeight, iteration++, nodes.getSize());
    }
    ht.erase();
    delete hWeight;
    return weightTable;
}

template <class A>
List<weight_association<A>*> * GraphAlgorithms<A>::FloydWarshall(List<GraphNode<A>*> nodes, bool printable, bool isNegative){
    List<weight_association<A>*> *weightTable;
    Weight **matrix = graphInMatrix(nodes);
    Size size;
    uint n = (uint)nodes.getSize();
    size.cols = size.rows = n;
    if (matrix==NULL){
        if (printable)
            cout << "\nUnexpected error";
        return NULL;
    }

    for (int iteration = 0; iteration <= n; iteration++){
        if (printable){
            cout << "\nIteration: " << (iteration+1) << endl <<  "X";
            for (int i = 0; i < n; i++)
                cout << setw(8) << nodes[i]->getData();

            for (uint i = 0; i < n; i++){
                cout << endl << nodes[i]->getData();
                for (uint j = 0; j < n; j++)
                    if (matrix[i][j]==INF_POSITIVE)
                        cout << setw(8) << "+inf";
                    else
                        cout << setw(8) << matrix[i][j];
            }
            cout << endl;

        }
        for (uint i = 0; i < n && iteration < n; i++){
            if (matrix[i][iteration]==INF_POSITIVE) continue;
            for (uint j = 0; j < n; j++){
                if ((isNegative || i != j) && matrix[iteration][j]!=INF_POSITIVE){
                    matrix[i][j] = Value<Weight>::min((matrix[i][j]),(matrix[iteration][j]+matrix[i][iteration]));
                }
            }
        }
    }
    weightTable = matrixToListOfWeightAssociation(matrix, size, nodes);
    for (uint i = 0; i < n ; i++)
        delete[] matrix[i];
    delete matrix;
    return weightTable;
}

template<class A>
Weight** GraphAlgorithms<A>::graphInMatrix(List<GraphNode<A>*> nodes){
    Weight **matrix = new Weight*[nodes.getSize()];
    for (int i = 0; i < nodes.getSize(); i++){
        matrix[i] = new Weight[nodes.getSize()];
        for (int j = 0; j < nodes.getSize(); j++)
            matrix[i][j] = INF_POSITIVE;
        for (int j = 0; j < nodes[i]->getAdjacentNodeList()->getSize(); j++){
            Weight adj_weight = (*nodes[i]->getEdgesWeightList())[j];
            GraphNode<A> *adj_node = (*nodes[i]->getAdjacentNodeList())[j];
            int k = 0;
            while(compare(adj_node->getData(), nodes[k]->getData())!=0 && k++ < nodes.getSize());
            if (k > nodes.getSize())
                return NULL;
            matrix[i][k] = adj_weight;
        }
        matrix[i][i] = 0;
    }

    return matrix;
}

template <class A>
List<weight_association<A>*> *GraphAlgorithms<A>::matrixToListOfWeightAssociation(Weight** matrix, Size size, List<GraphNode<A>*> nodes){
    List<weight_association<A>*> *list = new List<weight_association<A>*>;
    for (uint i = 0; i < size.rows; i++)
        for (uint j = 0; j < size.cols; j++)
            list->insert(getNew_WeightAssociation(nodes[i]->getData(), nodes[j], (A)LAST_NODE_UNKNOW, matrix[i][j]));

    return list;
}


#endif // GRAPHALGORITHMS_H
