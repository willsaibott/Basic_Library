#ifndef GRAPH_H
#define GRAPH_H

#include "GraphAlgorithms.h"
#define MIN_PATH_ALGORITHM_OFF -1

template <class A>
class Graph {
private:
    List<GraphNode<A>*> nodes;
    bool printPath = false;
    bool directioned = true;
    bool negative = false;
    List<weight_association<A>*> *weightTable;

public:
    Graph(){weightTable = new List<weight_association<A>*>;}
    Graph(List<GraphNode<A>*> newGraph);
    ~Graph();

    //getters
    int Size(){return nodes.getSize();}
    void get2Nodes(A elem1, A elem2, GraphNode<A> **node1, GraphNode<A> **node2);
    GraphNode<A> *getNode(A elem1);
    bool isNegative(){return negative;}


    //setters
    void setNodes(List<GraphNode<A>*> newNodes);
    void setPrintable(bool print){printPath = print;}
    void setDirectioned(bool dir){directioned = dir;}
    void setAllNodesVisited(bool visited);
    void setGraphNegative(){negative = true;}


    // others
    Weight minPath(A start, A target, int algorithm){return minPath(start, target, algorithm, NULL);}
    Weight minPath(A start, A target, int algorithm, Weight *(*heuristicFunction)(Weight*, int, int));
    Weight minPathByTable(A start, A target);

    bool insertNode(A elem);
    bool insertEdge(A elem1, A elem2, Weight weight);
    bool insertEdge(A elem1, A elem2);
    bool removeEdge(A elem1, A elem2);
    bool removeNode(A elem);
    bool setWeight(A elem1, A elem2, Weight weight);
    void erase();

    void printGraph(int width);
};


template <class A>
Graph<A>::Graph(List<GraphNode<A> *> newGraph){
    nodes = newGraph;
    weightTable = new List<weight_association<A>*>;
}

template <class A>
Graph<A>::~Graph(){
    //this->erase();

}


template <class A>
void Graph<A>:: setAllNodesVisited(bool visited){
    for (int i = 0; i < nodes.getSize(); i++)
        nodes[i]->setVisited(false);

}


template<class A>
GraphNode<A> * Graph<A>:: getNode(A elem){
    for (int i = 0; i < nodes.getSize(); i++){
        if (Search<A>::compare(nodes[i]->getData(), elem)==0)
            return nodes[i];
    }
    return NULL;
}


template <class A>
void Graph<A>::get2Nodes(A elem1, A elem2, GraphNode<A> **node1, GraphNode<A> **node2){
    *node1 = *node2 = NULL;
    for (int i = 0; i < nodes.getSize(); i++){
        if (*node1==NULL && Search<A>::compare(nodes[i]->getData(), elem1)==0){
            *node1 = nodes[i];
        }
        if (*node2==NULL && Search<A>::compare(nodes[i]->getData(), elem2)==0){
            *node2 = nodes[i];
        }
    }

}

template <class A>
bool Graph<A>:: insertNode(A elem){
    if (getNode(elem)!=NULL)
        return false;

    GraphNode<A> *newNode = new GraphNode<A>;
    newNode->setData(elem);
    nodes.insert(newNode);
    return true;
}

template <class A>
bool Graph<A>:: insertEdge(A elem1, A elem2, Weight weight){
    GraphNode<A> *node1, *node2;
    if (!isNegative() && weight < 0){
        if (printPath)
            cout << "\nError: This Graph does not accept negative values for weight.\n";
        return false;
    }

    get2Nodes(elem1, elem2, &node1, &node2);
    if (node1==NULL){
        node1 = new GraphNode<A>;
        node1->setData(elem1);
        nodes.insert(node1);
    }
    if (node2==NULL){
        node2 = new GraphNode<A>;
        node2->setData(elem2);
        nodes.insert(node2);
    }

    if (directioned){
        return node1->insertEdge(node2, weight);
    }
    else{
        if (Search<A>::compare(elem1, elem2)==0)
            return ((node1->insertEdge(node2, weight) || node2->insertEdge(node1, weight)));
        else
            return (node1->insertEdge(node2, weight) && node2->insertEdge(node1, weight));
    }
}

template <class A>
bool Graph<A>:: insertEdge(A elem1, A elem2){
    return insertEdge(elem1, elem2, 0);
}

template <class A>
bool Graph<A>:: removeEdge(A elem1, A elem2){
    GraphNode<A> *node1, *node2;
    node1 = node2 = NULL;
    get2Nodes(elem1, elem2, &node1, &node2);


    if (node1==NULL || node2==NULL)
        return false;
    else if (directioned){
        return node1->removeEdge(elem2);
    }
    else{
        if (Search<A>::compare(elem1, elem2)==0)
            return (node1->removeEdge(elem2) || node2->removeEdge(elem1));
        return (node1->removeEdge(elem2) && node2->removeEdge(elem1));
    }
    weightTable->erase();
}

template <class A>
bool Graph<A>::removeNode(A elem){
    int index = -1;

    for(int i = 0; i < nodes.getSize(); i++){
        if (Search<A>::compare(nodes[i]->getData(), elem)==0){
            index = i;
            nodes[i]->erase();
            break;
        }
    }
    if (index < 0)
        return false;

    for (int i = 0; i < nodes.getSize(); i++){
        nodes[i]->removeEdge(nodes[index]->getData());
    }

    nodes.remove(index);
    weightTable->erase();
    return true;

}

template <class A>
bool Graph<A>:: setWeight(A elem1, A elem2, Weight weight){
    GraphNode<A> *node1, *node2;
    get2Nodes(elem1, elem2, &node1, &node2);


    if (node1==NULL || node2==NULL)
        return false;
    else if (directioned){
        return node1->setWeight(elem2, weight);
    }
    else{
        if (Search<A>::compare(elem1, elem2)==0)
            return (node1->setWeight(elem2, weight) || node2->setWeight(elem1, weight));
        return (node1->setWeight(elem2, weight) && node2->setWeight(elem1, weight));
    }
}


template <class A>
Weight Graph<A>:: minPath(A start, A target, int algorithm, Weight* (*heuristicFunction)(Weight *, int, int)){
    Weight minWeight = 0;
    switch (algorithm) {
    case MIN_PATH_ALGORITHM_DIJKSTRA:
        if (weightTable!=NULL)
            weightTable->erase();
        weightTable = GraphAlgorithms<A>::Dijkstra(nodes, start, target, printPath);
        minWeight = minPathByTable(start, target);
        break;
    case MIN_PATH_ALGORITHM_A_STAR:
        if (weightTable!=NULL)
            weightTable->erase();
        if (heuristicFunction==NULL)
            return ERROR_CODE_HEURISTIC_FUNCTION_NOT_DEFINED;
        weightTable = GraphAlgorithms<A>::A_star(nodes, start, target, heuristicFunction, printPath);
        minWeight = minPathByTable(start, target);
        break;
    case MIN_PATH_ALGORITHM_FLOYD_WARSHALL:
        if (weightTable!=NULL)
            weightTable->erase();
        weightTable = GraphAlgorithms<A>::FloydWarshall(nodes, printPath, negative);
        minWeight = minPathByTable(start, target);
        break;
    case MIN_PATH_ALGORITHM_BELLMAN_FORD:
        if (weightTable!=NULL)
            weightTable->erase();
        weightTable =  GraphAlgorithms<A>::BellmanFord(nodes, start, target, printPath, negative);
        minWeight = minPathByTable(start, target);
        break;
    case MIN_PATH_ALGORITHM_JOHNSON:
        if (weightTable!=NULL)
            weightTable->erase();
        weightTable = GraphAlgorithms<A>::Johnson(nodes, printPath, negative);
        minWeight = minPathByTable(start, target);
        break;
    default:
        minWeight = minPathByTable(start, target);
        break;
    }
    return minWeight;
}


template <class A>
Weight Graph<A>::minPathByTable(A start, A target){
    if (weightTable==NULL || weightTable->getSize()==0)
        return ERROR_CODE_NODE_NOT_EXIST;
    bool exist1, exist2;
    exist1 = exist2 = false;
    for (int i = 0; i < (weightTable)->getSize(); i++){
        if(compare((*weightTable)[i]->start, start)==0){
            exist1 = true;
            if (compare((*weightTable)[i]->target->getData(), target)==0)
                return (*weightTable)[i]->weight;
        }
        if (compare((*weightTable)[i]->target->getData(), target)==0)
            exist2 = true;

    }
    if (exist1 && exist2)
        return ERROR_CODE_NODE_NOT_REACHABLE;
    return ERROR_CODE_NODE_NOT_EXIST;
}


template <class A>
void Graph<A>:: erase(){
    nodes.erase();
    if (weightTable!=NULL)
        weightTable->erase();
    negative = false;
}


template <class A>
void Graph<A>:: printGraph(int width){
    GraphNode<A> *edge;
    Weight w;
    cout << setw(width);
    cout << "\nX\t";
    for (int i = 0; i < nodes.getSize(); i++){
        cout << nodes[i]->getData() << "\t";
    }
    cout << endl;
    for (int i = 0; i < nodes.getSize(); i++){
        cout << nodes[i]->getData() << "\t";
        for (int j = 0; j < nodes.getSize(); j++){
            edge = nodes[i]->getEdge(nodes[j]->getData(), &w);
            if (edge!=NULL)
                cout << w << "\t";
            else
                cout << " \t";

        }
        cout << endl;
    }
    cout << endl;
}

#endif // GRAPH_H
