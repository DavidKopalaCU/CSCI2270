//
//  BST.cpp
//  BST
//
//  Created by David Kopala on 3/8/18.
//  Copyright © 2018 davidkopala. All rights reserved.
//

#include "BST.hpp"

BST::BST()
{
    root = nullptr;
    height = -1;
}

BST::BST(int start)
{
    root = new node(start, nullptr, nullptr, nullptr);
    height = 0;
}

bool BST::priv_find(node *parent, int target)
{
    if (parent == nullptr) {
        return false;
    } else if (parent->value == target) {
        return true;
    } else if (target < parent->value) {
        return priv_find(parent->left, target);
    } else {
        return priv_find(parent->right, target);
    }
}

bool BST::exists(int target)
{
    return priv_find(root, target);
}

void BST::addValue(int value)
{
    if (exists(value)) {
        return;
    }
    if (root == nullptr) {
        root = new node(value, nullptr, nullptr, nullptr);
        return;
    }
    priv_addValue(root, value, 0);
}

void BST::priv_addValue(node *parent, int value, int depth)
{
    if (value < parent->value) {
        if (parent->left == nullptr) {
            parent->left = new node(value, parent, nullptr, nullptr);
            if (depth == height) {
                height++;
            }
            return;
        } else {
            return priv_addValue(parent->left, value, ++depth);
        }
    } else {
        if (parent->right == nullptr) {
            parent->right = new node(value, parent, nullptr, nullptr);
            if (depth == height) {
                height++;
            }
            return;
        } else {
            return priv_addValue(parent->right, value, ++depth);
        }
    }
}

void BST::getLevel_recur(node *parent, int level, string *build)
{
    if (level == 0) {
        if (parent == nullptr) {
            (*build) += "-,";
        } else {
            (*build) += to_string(parent->value) + ",";
        }
        return;
    } else {
        if (parent == nullptr) {
            getLevel_recur(parent, level-1, build);
            getLevel_recur(parent, level-1, build);
        } else {
            getLevel_recur(parent->left, level-1, build);
            getLevel_recur(parent->right, level-1, build);
        }
    }
}

string *BST::getLevel(int level)
{
    string *levelVals = new string[pow(2, level)];
    string build;
    getLevel_recur(root, level, &build);
    stringstream s(build);
    int index = 0;
    while (!s.eof()) {
        string word;
        getline(s, word, ',');
        if (word == "") {
            continue;
        }
        levelVals[index++] = word;
    }
    return levelVals;
}

void BST::printTree()
{
    int maxWidth = pow(2, height+2);
    for (int i = 0; i <= height; i++) {
        int spacing = (maxWidth / (pow(2, i) + 1)) - (1);
        string *vals = getLevel(i);
        for (int j = 0; j < pow(2, i); j++) {
            if (j < (pow(2, i)/2)) {
                cout<<left<<setw(spacing)<<" "<<setw(2)<<vals[j];
            } else {
                cout<<right<<setw(spacing)<<" "<<setw(2)<<vals[j];
            }
        }
        cout<<endl;
    }
}

void BST::priv_deleteValue(node *parent, int target) {
    if (parent == nullptr) {
        return;
    } else if (parent->value != target) {
        if (target < parent->value) {
            return priv_deleteValue(parent->left, target);
        } else {
            return priv_deleteValue(parent->right, target);
        }
    } else {
        //No children
        if (parent->right == nullptr && parent->left == nullptr) {
            if (parent->parent->left == parent) {
                parent->parent->left = nullptr;
            } else {
                parent->parent->right = nullptr;
            }
            delete parent;
            return;
        } else if ((parent->right == nullptr) || (parent->left == nullptr)) {  //One child
            if (parent->parent->left == parent) {
                if (parent->left != nullptr) {
                    parent->left->parent = parent->parent;
                    parent->parent->left = parent->left;
                } else {
                    parent->right->parent = parent->parent;
                    parent->parent->left = parent->right;
                }
            } else {
                if (parent->left != nullptr) {
                    parent->left->parent = parent->parent;
                    parent->parent->right = parent->left;
                } else {
                    parent->right->parent = parent->parent;
                    parent->parent->right = parent->right;
                }
            }
            delete parent;
            return;
        } else { //Two Children
            if (parent == root) {
                return;
            } else if (parent->value < parent->parent->value) {
                node *next = parent->right;
                while (next->left != nullptr) {
                    next = next->left;
                }
                parent->parent->left = next;
                if (next->right != nullptr) {
                    next->parent->left = next->right;
                    next->right->parent = next->parent;
                } else {
                    next->parent->left = nullptr;
                }
                next->parent = parent->parent;
                parent->parent->left = next;
                next->left = parent->left;
                next->right = parent->right;
            } else {
                node *next = parent->left;
                while (next->right != nullptr) {
                    next = next->right;
                }
                parent->parent->right = next;
                if (next->left != nullptr) {
                    next->parent->right = next->left;
                    next->left->parent = next->parent;
                } else {
                    next->parent->right = nullptr;
                }
                next->parent = parent->parent;
                parent->parent->right = next;
                next->left = parent->left;
                next->right = parent->right;
            }
        }
    }
}

void BST::deleteValue(int target)
{
    if (!exists(target)) {
        return;
    }
    priv_deleteValue(root, target);
}
