#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include "Node.h"
#include "Search.h"

template <class A>
class GraphNode : public Node<A>{
protected:
    List<GraphNode<A>*> adjacent_Nodes;
    List<Weight> edges_Weight;
public:

    GraphNode();
    GraphNode(A newData);
    ~GraphNode();

    //getters
    List<GraphNode<A>*> *getAdjacentNodeList(){return &adjacent_Nodes;}
    List<Weight> *getEdgesWeightList(){return &edges_Weight;}

    GraphNode<A>* getEdge(A elem, Weight *weight, int *pos);
    GraphNode<A>* getEdge(A elem, Weight *weight);
    GraphNode<A>* getEdge(A elem);

    //setters
    void setLinkedEdgesVisited(A elem, bool isVisited);
    void setAllLinkedEdgesVisited(bool isVisited);
    bool setWeight(A elem, Weight weight);


    //others
    bool insertEdge(GraphNode<A> *node, Weight weight);
    bool removeEdge(A elem);
    void erase();

};


template <class A>
GraphNode<A>::GraphNode() : Node<A>(){

}

template <class A>
GraphNode<A>::GraphNode(A newData) : Node<A>(newData){

}


template <class A>
GraphNode<A>::~GraphNode(){
    erase();
}

template <class A>
GraphNode<A> *GraphNode<A>::getEdge(A elem, Weight *weight, int *pos){
    for (int i = 0; i < adjacent_Nodes.getSize(); i++){
        if (compare(adjacent_Nodes[i]->getData(), elem)==0){
            *weight = edges_Weight[i];
            *pos = i;
            return adjacent_Nodes[i];
        }
    }
    return NULL;
}



template <class A>
GraphNode<A> *GraphNode<A>::getEdge(A elem, Weight *weight){
    int pos;
    return getEdge(elem, weight, &pos);
}

template <class A>
GraphNode<A> *GraphNode<A>::getEdge(A elem){
    int pos;
    Weight w;
    return getEdge(elem, &w, &pos);
}



template <class A>
void GraphNode<A>::setLinkedEdgesVisited(A elem, bool isVisited){
    GraphNode<A> *node = getEdge(elem);
    if (node!=NULL){
        node->setVisited(isVisited);
    }
}

template <class A>
void GraphNode<A>::setAllLinkedEdgesVisited(bool isVisited){
    for (int i = 0; i < adjacent_Nodes.getSize(); i++)
        adjacent_Nodes[i]->setVisited(isVisited);
}

template <class A>
bool GraphNode<A>::setWeight(A elem, Weight weight){
    GraphNode<A>* node;
    int pos;
    Weight w;
    node = getEdge(elem, &w, &pos);
    if (node==NULL)
        return false;
    edges_Weight.setElement(weight, pos);
    return true;
}


//others
template <class A>
bool GraphNode<A>::insertEdge(GraphNode<A> *node, Weight weight){
    if (node==NULL || getEdge(node->getData()) != NULL)
        return false;

    edges_Weight.insert(weight);
    adjacent_Nodes.insert(node);
    return true;
}
template <class A>
bool GraphNode<A>::removeEdge(A elem){
    for (int i = 0; i < adjacent_Nodes.getSize(); i++){
        if (Search<A>::compare(adjacent_Nodes[i]->getData(), elem)==0){
            adjacent_Nodes.remove(i);
            edges_Weight.remove(i);
            return true;
        }
    }
    return false;
}

template <class A>
void GraphNode<A>::erase(){
    adjacent_Nodes.erase();
    edges_Weight.erase();
}



#endif // GRAPHFACTORY_H
