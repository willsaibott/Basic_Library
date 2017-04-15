#ifndef AVLTREE_H
#define AVLTREE_H

#include "BinaryTree.h"

template <class A>
class AVLTree : public BinaryTree<A>{

public:

    virtual void update();


};

template <class A>
void AVLTree<A>::update(){
    BinaryNode<A> *father = this->pointer->getParent();
    int diff;


    while (father != NULL){
        cout << "\nPointer: "<< this->pointer->getData() << " Pai: " << father->getData() << endl;
        diff = this->getHeight(father->getLeft()) - this->getHeight(father->getRight());
        cout << "\n Diff: " << diff << endl;
        if (diff == 2){
            diff = this->getHeight(this->pointer->getLeft()) - this->getHeight(this->pointer->getRight());
            cout << "\n Diff2: " << diff << endl;
            if (diff == 1){
                if (father->getLeft()==this->pointer){
                    cout << "\nPai: " << father->getData() << " roda pra direita\n";
                    father->rightRotate();
                    if(father==this->root){
                        this->root = this->pointer;
                        cout << "\nTroca-se a raiz por " << this->pointer->getData();
                    }
                }
            }else if (diff == -1){
                this->pointer->leftRotate();
                father->rightRotate();
                if(father==this->root)
                    this->root = this->pointer;
            }

        }
        else if (diff == -2){
            diff = this->getHeight(this->pointer->getLeft()) - this->getHeight(this->pointer->getRight());
            cout << "\n Diff2: " << diff << endl;
            if (diff == -1){
                if (father->getRight()==this->pointer){
                    cout << "\nPai: " << father->getData() << " roda pra esquerda\n";
                    father->leftRotate();

                    if(father==this->root){
                        cout << "\nTroca-se a raiz por " << this->pointer->getData();
                        this->root = this->pointer;
                    }
                }
            }else if (diff == 1){
                this->pointer->rightRotate();
                father->leftRotate();
                if(father==this->root)
                    this->root = this->pointer;
            }
        }
        else{
            break;
        }

        this->pointer = this->pointer->getParent();
        father = this->pointer->getParent();
    }

    this->height = this->getHeight(this->root);
}


#endif // AVLTREE_H
