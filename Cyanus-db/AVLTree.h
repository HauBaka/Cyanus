#ifndef AVLTREE_H
#define AVLTREE_H

template<typename T, typename K>
class AVLTree {
private:
    struct Node {
        T data;
        K key;
        Node* left, * right;
        int level;
        Node(const T& val, const K& k) : data(val), key(k), left(nullptr), right(nullptr), level(1) {}
    };


    Node* root;

    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    int getLevel(Node* node);
    int getBalance(Node* node);
    void updateLevel(Node* node);
    Node* update(Node* root);
    Node* mostLeftNode(Node* node);
    Node* findNodeByKey(Node* root, const K& key);
    Node* add(Node* root, Node* node);
    Node* remove(Node* root, Node* node);
    void destroy(Node* node);
public:
    AVLTree();
    ~AVLTree();

    typename AVLTree<T, K>::Node* findNodeByKey(const K& key);
    void createNode(const T& value, const K& key);
    void add(Node* node);
    void remove(const K& key);
};

#endif 