#ifndef AVLTREE_H
#define AVLTREE_H
#include <vector>
using namespace std;
template<typename T, typename K>
class AVLTree {
public:
    struct Node {
        T data;
        K key;
        Node* left, * right;
        int level;
        Node(const T& val, const K& k) : data(val), key(k), left(nullptr), right(nullptr), level(1) {}
    };

    AVLTree();
    ~AVLTree();

    typename AVLTree<T, K>::Node* findNodeByKey(const K& key);
    static Node* createNode(const T& value, const K& key);
    void add(Node* node);
    void remove(const K& key);

    std::vector<pair<T,K>> getAllData();
private:
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
    void preOrderTraversal(Node* root, vector<pair<T, K>>& data);

};

#endif 