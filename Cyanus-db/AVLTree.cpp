/**
* 
**/
#include <iostream>
#include "AVLTree.h"
#include <type_traits> //Check data is a pointer
template<typename T, typename K>
typename AVLTree<T, K>::Node* AVLTree<T, K>::rightRotate(Node* y) {
        Node* l = y->left;
        y->left = l->right;
        l->right = y;
        return l;
    }
template<typename T, typename K>
typename AVLTree<T, K>::Node* AVLTree<T, K>::leftRotate(Node* x) {
        Node* r = x->right;
        x->right = r->left;
        r->left = x;
        return r;
    }

template<typename T, typename K>
int AVLTree<T,K>::getLevel(Node* node) {
        return node ? node->level : 0;
    }

template<typename T, typename K>
int AVLTree<T, K>::getBalance(Node* node) {
        return node ? getLevel(node->left) - getLevel(node->right) : 0;
    }

template<typename T, typename K>
void AVLTree<T, K>::updateLevel(Node* node) {
        node->level = 1 + max(getLevel(node->left), getLevel(node->right));
    }


template<typename T, typename K>
typename AVLTree<T, K>::Node* AVLTree<T, K>::update(Node* root) {
        updateLevel(root);
        int k = getBalance(root);
        if (k > 1) {
            if (getBalance(root->left) >= 0) {
                root = rightRotate(root);
            }
            else {
                root->left = leftRotate(root->left);
                root = rightRotate(root);
            }
        }
        else if (k < -1) {
            if (getBalance(root->right) <= 0) {
                root = leftRotate(root);
            }
            else {
                root->right = rightRotate(root->right);
                root = leftRotate(root);
            }
        }
        return root;
    }

template<typename T, typename K>
typename AVLTree<T, K>::Node* AVLTree<T, K>::mostLeftNode(Node* node) {
        if (!node) return nullptr;
        while (node && node->left) node = node->left;
        return node;
    }


template<typename T, typename K>
typename AVLTree<T, K>::Node* AVLTree<T, K>::findNodeByKey(Node* root, const K& key) {
        if (!root) return nullptr;
        if (key == root->key) return root;
        return key > root->key ?
            findNodeByKey(root->right, key) :
            findNodeByKey(root->left, key);
    }


template<typename T, typename K>
typename AVLTree<T, K>::Node* AVLTree<T, K>::add(Node* root, Node* node) {
        if (!root) return node;
        if (root->key < node->key) root->right = add(root->right, node);
        else if (root->key > node->key) root->left = add(root->left, node);
        else return root;
        root = update(root);
        return root;
    }


template<typename T, typename K>
typename AVLTree<T, K>::Node* AVLTree<T, K>::remove(Node* root, Node* node) {
        if (!root) return nullptr;
        if (node->key > root->key) root->right = remove(root->right, node);
        else if (node->key < root->key) root->left = remove(root->left, node);
        else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    return nullptr;
                }
                else {
                    delete root;
                    root = temp;
                }
            }
            else {
                Node* temp = mostLeftNode(root->right);
                root->data = temp->data;
                root->key = temp->key;
                root->right = remove(root->right, temp);
            }
        }
        if (!root) return nullptr;
        root = update(root);
        return root;
    }

template<typename T, typename K>
void AVLTree<T, K>::destroy(Node* node) {
    if (!node) return;

    destroy(node->left);
    destroy(node->right);

    if constexpr (is_pointer<T>::value) {
        delete node->data;
    }

    delete node;
}
    
template<typename T, typename K>
AVLTree<T, K>::AVLTree() {
        root = nullptr;
    }
template<typename T, typename K>
AVLTree<T, K>::~AVLTree() {
        destroy(root); 
    }

template<typename T, typename K>
typename AVLTree<T, K>::Node* AVLTree<T, K>::findNodeByKey(const K& key) {
        return findNodeByKey(root, key);
    }

template<typename T, typename K>
AVLTree<T, K>::Node* AVLTree<T, K>::createNode(const T& value, const K& key) {
        if (findNodeByKey(this->root, key)) 
            throw "AVLTree: Key already exists!\n";
        return new Node(value, key);
    }

template<typename T, typename K>
void AVLTree<T, K>::add(Node* node) {
        root = add(root, node);
    }

template<typename T, typename K>
void AVLTree<T, K>::remove(const K& key) {
        Node* node = findNodeByKey(key);
        if (!node) {
            throw "AVLTree: Key not found!\n";
        }
        root = remove(root, node);
    }

template class AVLTree<int, int>;