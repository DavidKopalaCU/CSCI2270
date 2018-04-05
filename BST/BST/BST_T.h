//
//  BST_T.h
//  BST
//
//  Created by David Kopala on 3/9/18.
//  Copyright © 2018 davidkopala. All rights reserved.
//

#ifndef BST_T_h
#define BST_T_h

//https://stackoverflow.com/questions/4484982/how-to-convert-typename-t-to-string-in-c - LIFESAVER _ enables print tree for most data types, and extendable to custom types
template<typename T>
struct GetString {
    static string toString(T test) {
        return std::to_string(test);
    }
};
//Add more of these for problematic data types, as well as custom types
template<>
struct GetString<string> {
    static string toString(string s) {
        return s;
    }
};

template <class T>
class BST_T {

private:
    struct node {
        T value;
        node *left;
        node *right;
        node *parent;
        
        node(T val, node *p, node *l, node *r) {
            value = val;
            parent = p;
            left = l;
            right = r;
        }
    };
    node *root;
    int height;
    
    void priv_addValue(node *parent, T value, int depth) {
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
    };
    
    void priv_deleteValue(node *parent, T target) {
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
    };
    bool priv_find(node *parent, T target) {
        if (parent == nullptr) {
            return false;
        } else if (parent->value == target) {
            return true;
        } else if (target < parent->value) {
            return priv_find(parent->left, target);
        } else {
            return priv_find(parent->right, target);
        }
    };
    void getLevel_recur(node *parent, int level, string *build) {
        if (level == 0) {
            if (parent == nullptr) {
                (*build) += "-,";
            } else {
                try {
                    //(*build) += to_string(parent->value) + ",";
                    (*build) += GetString<T>::toString(parent->value) + ",";
                } catch (exception e) {
                    cout<<"Error"<<endl;
                }
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
    };
    
public:
    BST_T(T start) {
        root = new node(start, nullptr, nullptr, nullptr);
        height = 0;
    };
    BST_T() {
        root = nullptr;
        height = -1;
    };
    void addValue(T value) {
        if (exists(value)) {
            return;
        }
        if (root == nullptr) {
            root = new node(value, nullptr, nullptr, nullptr);
            return;
        }
        priv_addValue(root, value, 0);
    };
    void deleteValue(T target) {
        if (!exists(target)) {
            return;
        }
        priv_deleteValue(root, target);
    };
    bool exists(T target) {
        return priv_find(root, target);
    };
    string *getLevel(int level) {
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
    };
    void printTree() {
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
    };
};

#endif /* BST_T_h */
