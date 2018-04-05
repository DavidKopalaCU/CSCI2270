//
//  MovieTree.cpp
//  Assignment6
//
//  Created by David Kopala on 3/9/18.
//  Copyright © 2018 davidkopala. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "MovieTree.hpp"

MovieTree::MovieTree() {
    root = nullptr;
}

MovieTree::~MovieTree() {
    DeleteAll(root);
}

MovieNodeBST* MovieTree::searchBST(MovieNodeBST *node, std::string title)
{
    char c = title[0];
    if (node == nullptr) {
        return node;
    } else if (node->letter == c) {
        return node;
    } else if (c < node->letter) {
        return searchBST(node->leftChild, title);
    } else {
        return searchBST(node->rightChild, title);
    }
}

MovieNodeLL* MovieTree::searchLL(MovieNodeLL *head, std::string title)
{
    MovieNodeLL *temp = new MovieNodeLL();
    temp->next = head;
    while ((temp = temp->next) != nullptr) {
        if (temp->title == title) {
            return temp;
        }
    }
    return nullptr;
}

void MovieTree::findMovie(std::string title)
{
    MovieNodeBST *b = searchBST(root, title);
    if (b == nullptr) {
        std::cout<<"Movie not found."<<std::endl;
        return;
    }
    MovieNodeLL *l = searchLL(b->head, title);
    if (l == nullptr) {
        std::cout<<"Movie not found."<<std::endl;
        return;
    }
    
    std::cout<<"Movie Info:"<<std::endl;
    std::cout << "===========" << std::endl;
    std::cout << "Ranking:" << l->ranking << std::endl;
    std::cout << "Title:" << l->title << std::endl;
    std::cout << "Year:" << l->year << std::endl;
    std::cout << "Quantity:" << l->quantity << std::endl;
}

MovieNodeBST* addBSTNode(MovieNodeBST *parent, char c) {
    if (parent == nullptr) {
        MovieNodeBST *node = new MovieNodeBST(c);
        return node;
    } else if (c < parent->letter) {
        if (parent->leftChild == nullptr) {
            MovieNodeBST *node = new MovieNodeBST(c);
            node->parent = parent;
            parent->leftChild = node;
            return node;
        } else {
            return addBSTNode(parent->leftChild, c);
        }
    } else {
        if (parent->rightChild == nullptr) {
            MovieNodeBST *node = new MovieNodeBST(c);
            node->parent = parent;
            parent->rightChild = node;
            return node;
        } else {
            return addBSTNode(parent->rightChild, c);
        }
    }
}

void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity)
{
    MovieNodeBST *b = searchBST(root, title);
    if (b == nullptr) {
        MovieNodeBST *node = addBSTNode(root, title[0]);
        if (root == nullptr) {
            root = node;
            b = root;
        }
        node->head = new MovieNodeLL(ranking, title, releaseYear, quantity);
    } else {
        MovieNodeLL *newL = new MovieNodeLL(ranking, title, releaseYear, quantity);
        if (title < b->head->title) {
            newL->next = b->head;
            b->head = newL;
        } else {
            MovieNodeLL *temp = new MovieNodeLL();
            temp->next = b->head;
            while ((temp = temp->next)->next != nullptr) {
                if ((temp->title < title) && (title < temp->next->title)) {
                    newL->next = temp->next;
                    temp->next = newL;
                    return;
                }
            }
            temp->next = newL;
        }
    }
}

void deleteBSTNode(MovieNodeBST *parent, char target) {
    if (parent == nullptr) {
        return;
    } else if (parent->letter != target) {
        if (target < parent->letter) {
            return deleteBSTNode(parent->leftChild, target);
        } else {
            return deleteBSTNode(parent->rightChild, target);
        }
    } else {
        //No children
        if (parent->rightChild == nullptr && parent->leftChild == nullptr) {
            if (parent->parent == nullptr) {
                delete parent;
                return;
            }
            if (parent->parent->leftChild == parent) {
                parent->parent->leftChild = nullptr;
            } else {
                parent->parent->rightChild = nullptr;
            }
            delete parent;
            return;
        } else if ((parent->rightChild == nullptr) || (parent->leftChild == nullptr)) {  //One child
            if (parent->parent->leftChild == parent) {
                if (parent->leftChild != nullptr) {
                    parent->leftChild->parent = parent->parent;
                    parent->parent->leftChild = parent->leftChild;
                } else {
                    parent->rightChild->parent = parent->parent;
                    parent->parent->leftChild = parent->rightChild;
                }
            } else {
                if (parent->leftChild != nullptr) {
                    parent->leftChild->parent = parent->parent;
                    parent->parent->rightChild = parent->leftChild;
                } else {
                    parent->rightChild->parent = parent->parent;
                    parent->parent->rightChild = parent->rightChild;
                }
            }
            delete parent;
            return;
        } else { //Two Children
            if (parent->letter < parent->parent->letter) {
                MovieNodeBST *next = parent->rightChild;
                while (next->leftChild != nullptr) {
                    next = next->leftChild;
                }
                parent->parent->leftChild = next;
                if (next->rightChild != nullptr) {
                    next->parent->leftChild = next->rightChild;
                    next->rightChild->parent = next->parent;
                } else {
                    next->parent->leftChild = nullptr;
                }
                next->parent = parent->parent;
                parent->parent->leftChild = next;
                next->leftChild = parent->leftChild;
                next->rightChild = parent->rightChild;
            } else {
                MovieNodeBST *next = parent->leftChild;
                while (next->rightChild != nullptr) {
                    next = next->rightChild;
                }
                parent->parent->rightChild = next;
                if (next->leftChild != nullptr) {
                    next->parent->rightChild = next->leftChild;
                    next->leftChild->parent = next->parent;
                } else {
                    next->parent->rightChild = nullptr;
                }
                next->parent = parent->parent;
                parent->parent->rightChild = next;
                next->leftChild = parent->leftChild;
                next->rightChild = parent->rightChild;
            }
        }
    }
}

void MovieTree::rentMovie(std::string title)
{
    MovieNodeBST *b = searchBST(root, title);
    if (b == nullptr) {
        std::cout<<"Movie not found."<<std::endl;
        return;
    }
    MovieNodeLL *l = searchLL(b->head, title);
    if (l == nullptr) {
        std::cout<<"Movie not found."<<std::endl;
        return;
    }
    
    std::cout<<"Movie has been rented."<<std::endl;
    (l->quantity)--;
    findMovie(title);
    if (l->quantity == 0) {
        deleteMovieNode(title);
    }
    
}

void MovieTree::deleteMovieNode(std::string title)
{
    //std::cout<<"Delete: "<<title<<std::endl;
    MovieNodeBST *b = searchBST(root, title);
    if (b == nullptr) {
        std::cout<<"Movie not found."<<std::endl;
        return;
    }
    MovieNodeLL *l = searchLL(b->head, title);
    if (l == nullptr) {
        std::cout<<"Movie not found."<<std::endl;
        return;
    }
    
    if (b->head == l) {
        b->head = l->next;
        delete l;
    } else {
        MovieNodeLL *temp = new MovieNodeLL();
        temp->next = b->head;
        while ((temp = temp->next)->next != l) {}
        temp->next = l->next;
        delete l;
    }
    if (b->head == nullptr) {
        if (b == root) {
            MovieNodeBST *parent = b;
            if (parent->rightChild != nullptr) {
                MovieNodeBST *next = parent->rightChild;
                while (next->leftChild != nullptr) {
                    next = next->leftChild;
                }
                //parent->parent->leftChild = next;
                if (next->rightChild != nullptr) {
                    next->parent->leftChild = next->rightChild;
                    next->rightChild->parent = next->parent;
                }
                next->parent->leftChild = nullptr;
                next->parent = nullptr;//parent->parent;
                root = next;//parent->parent->leftChild = next;
                next->leftChild = parent->leftChild;
                next->rightChild = parent->rightChild;
            } else if (parent->leftChild != nullptr) {
                MovieNodeBST *next = parent->leftChild;
                while (next->rightChild != nullptr) {
                    next = next->rightChild;
                }
                //parent->parent->rightChild = next;
                if (next->leftChild != nullptr) {
                    next->parent->rightChild = next->leftChild;
                    next->leftChild->parent = next->parent;
                }
                next->parent->rightChild = nullptr;
                next->parent = nullptr;//parent->parent;
                root = next;//parent->parent->rightChild = next;
                next->leftChild = parent->leftChild;
                next->rightChild = parent->rightChild;
            } else {
                root = nullptr;
            }
        } else {
            deleteBSTNode(root, b->letter);
        }
    }
}

void MovieTree::countMovieNodes(MovieNodeBST *node, int *c)
{
    if (node == nullptr) {
        return;
    }
    
    MovieNodeLL *l = new MovieNodeLL();
    l->next = node->head;
    while ((l = l->next) != nullptr) {
        (*c) += 1;
    }
    
    countMovieNodes(node->leftChild, c);
    countMovieNodes(node->rightChild, c);
}


int MovieTree::countMovieNodes() {
    int c = 0;
    countMovieNodes(root, &c);
    return c;
}

MovieNodeBST* MovieTree::treeMinimum(MovieNodeBST *node) {
    if (node->leftChild == nullptr) {
        return node;
    } else {
        return treeMinimum(node->leftChild);
    }
}

void MovieTree::printMovieInventory(MovieNodeBST *node)
{
    if (node != nullptr) {
        printMovieInventory(node->leftChild);
        MovieNodeLL *l = new MovieNodeLL();
        l->next = node->head;
        while ((l = l->next) != nullptr) {
            std::cout<<"Movie: "<<l->title<<" "<<l->quantity<<std::endl;
        }
        printMovieInventory(node->rightChild);
    }
}

void MovieTree::printMovieInventory()
{
    printMovieInventory(root);
}

void MovieTree::DeleteAll(MovieNodeBST *node)
{
    if (node != nullptr) {
        DeleteAll(node->leftChild);
        DeleteAll(node->rightChild);
        while (node->head != nullptr) {
            MovieNodeLL *del =  node->head;
            node->head = node->head->next;
            std::cout<<"Deleting: "<<del->title<<std::endl;
            delete del;
        }
        deleteBSTNode(root, node->letter);
    }
}
