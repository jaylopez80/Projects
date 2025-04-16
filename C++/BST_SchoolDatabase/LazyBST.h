#ifndef LAZYBST_H
#define LAZYBST_H
#include <iostream>
#include <fstream>

using namespace std;
template <class T>
class TreeNode{

public:
    TreeNode();
    TreeNode(T key);
    virtual ~TreeNode();

    T key;
    TreeNode<T> *left;
    TreeNode<T> *right;
    int depthLeft; // depth of left subtree
    int depthRight; // depth of right subtree

};
template <class T>
TreeNode<T>::TreeNode() {
        key = T();
        left = NULL;
        right = NULL;
        depthLeft = 0;
        depthRight = 0;

}
template <class T>
TreeNode<T>::TreeNode(T key) {
    this->key = key;
    left = NULL;
    right = NULL;
    depthLeft = 0;
    depthRight = 0;
}
template <class T>
TreeNode<T>::~TreeNode() {
    cout << "Deleting node with key: " << key << endl;
    left = NULL;
    right = NULL;
}

template <class T>
class LazyBST{

public:
    LazyBST();
    virtual ~LazyBST();

    void insert(T key);
    bool contains(T key);
    bool deleteNode(T key);
    bool isEmpty();
    void printTree();
    T* getMin();
    T* getMax();
    TreeNode<T>* getSuccessor(TreeNode<T> *d); // d represents the node to be deleted
    TreeNode<T>* getRoot() const; // Function to get the root of the tree
    TreeNode<T>* find(T key); // Function to find a node with a specific key
    void recPrint(TreeNode<T> *node);
    void printTreeToFile(ofstream& file);

private:
    TreeNode<T> *root;
    int size; // number of nodes in the tree
    
    void updateDepths(TreeNode<T> *node); // update the depth of the node
    void balance(TreeNode<T>*& node); // balance the tree if needed
    void inOrderTraversal(TreeNode<T>* node, ofstream& file); // in order traversal of the tree
    void inOrderTraversal(TreeNode<T>* node); // in order traversal of the tree for printing only to console
    void inOrderTraversal(TreeNode<T>* node, T* arr, int& index); // in order traversal of the tree to store values in an array
    void deleteTree(TreeNode<T>* node); // delete the tree
    int calcBalance(TreeNode<T>*& node); // calculate the balance factor
    int calcSize(TreeNode<T>* node); // calculate the size of the tree
    TreeNode<T>* rebuildTree(T* arr, int size); // rebuild the tree from the array

};
template <class T>
LazyBST<T>::LazyBST() {
    root = NULL;
}
template <class T>
LazyBST<T>::~LazyBST() {
    deleteTree(root);

}
template <class T>
void LazyBST<T>::recPrint(TreeNode<T> *node) { // recursive print function
    if(node == NULL)
        return;
    cout << node->key << endl;
    recPrint(node->left);
    recPrint(node->right);
}
template <class T>
void LazyBST<T>::printTree() { // print function calls recursive print 
//     recPrint(root);
// }
    if (root == NULL) {
        cout << "Tree is empty." << endl;
        return;
    }
    inOrderTraversal(root);
    cout << endl;
}



template<typename T>
void LazyBST<T>::printTreeToFile(ofstream& file) {
    if (root == NULL) {
        file << "Empty.";
        return;
    }
    inOrderTraversal(root, file);
    file << endl;
   
}

template <class T>
bool LazyBST<T>::isEmpty() {
    return root == NULL;
}
template <class T>
T* LazyBST<T>::getMin() {
    if(isEmpty()) return NULL;
    TreeNode<T> *curr = root;
    while(curr->left != NULL) {
        curr = curr->left;
    }
    return &curr->key;
}
template <class T>
T* LazyBST<T>::getMax() {
    if(isEmpty()) return NULL;
    TreeNode<T> *curr = root;
    while(curr->right != NULL) {
        curr = curr->right;
    }
    return &curr->key;
}

template <class T>
TreeNode<T>* LazyBST<T>::getRoot() const {
    return root;
}

template <class T>
TreeNode<T>* LazyBST<T>::find(T key) {
    TreeNode<T>* current = root;
    while (current != NULL) {
        if (current->key == key) {
            return current;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NULL; 
}

template <class T>
void LazyBST<T>::insert(T key) {
    TreeNode<T> *node = new TreeNode<T>(key);
    if(isEmpty()) {
        root = node;
    } else {
        TreeNode<T> *curr = root;
        TreeNode<T> *parent = NULL;
        while (true) {
            parent = curr;
            if (key < curr->key) {
                curr = curr->left;
                if (curr == NULL) {
                    parent->left = node;
                    break;
                }
            } else {
                curr = curr->right;
                if (curr == NULL) {
                    parent->right = node;
                    break;
                }
            }
        }
    }
    updateDepths(root); // update the depths of the tree after inserting a node
    balance(root); // balance the tree if needed
}
template <class T>
bool LazyBST<T>::contains(T key) {
    if(isEmpty()) return false;
    TreeNode<T> *curr = root;
    while(curr->key != key) {
        if(key < curr->key) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
        if(curr == NULL) return false;
    }
    return true;
}
template <class T>
bool LazyBST<T>::deleteNode(T key) {
if(isEmpty())
    return false;
TreeNode<T> *curr = root;
TreeNode<T> *parent = root;
bool isLeft = true;
while(curr->key != key){
    parent = curr;
    if(key < curr->key){
        isLeft = true;
        curr = curr->left;
    } else {
        isLeft = false;
        curr = curr->right;
    }
    if(curr == NULL)
        return false;
}
// if we make it here, we found the node to be deleted
// case: node to be deleted has no children
if(curr->left == NULL && curr->right == NULL){
    if(curr == root){
        root = NULL;
    } else if(isLeft){
        parent->left = NULL;
    } else {
        parent->right = NULL;
    }
}
// case: node to be deleted has 1 child
else if(curr->right == NULL){
    // node to be deleted has a left child
    if(curr == root){
        root = curr->left;
    } else if(isLeft){
        parent->left = curr->left;
    } else {
        parent->right = curr->left;
    }

}
    else if(curr->left == NULL) {
        // node to be deleted has a right child
        if (curr == root) {
            root = curr->right;
        } else if (isLeft) {
            parent->left = curr->right;
        } else {
            parent->right = curr->right;
        }
    }
    else{
        //the node to be deleted has 2 children
        TreeNode<T> *successor = getSuccessor(curr);
        if(curr == root){
            root = successor;
        } else if(isLeft){
            parent->left = successor;
        } else {
            parent->right = successor;
        }
        successor->left = curr->left;
        curr->right = NULL;
        curr->left = NULL;
    }
    delete curr;
    size --;
    return true;
}
template <class T>
TreeNode<T>* LazyBST<T>::getSuccessor(TreeNode<T> *d) {
    //d represents the node to be deleted, we are finding the smallest in the right subtree of d
    TreeNode<T> *sp = d;
    TreeNode<T> *successor = d;
    TreeNode<T> *current = d->right;
    while(current != NULL){
        sp = successor;
        successor = current;
        current = current->left;
    }
    if (successor != d->right) {
        sp->left = successor->right;
        successor->right = d->right;
    }
    return successor;
}
template <class T>
void LazyBST<T>::updateDepths(TreeNode<T> *node) { //tracks the depth of the tree
    if (node == NULL) return;

    updateDepths(node->left);
    updateDepths(node->right);

    // Update depth of the left subtree
    if (node->left != NULL) {
        node->depthLeft = max(node->left->depthLeft, node->left->depthRight) + 1;
    } else {
        node->depthLeft = 0;
    }

    // Update depth of the right subtree
    if (node->right != NULL) {
        node->depthRight = max(node->right->depthLeft, node->right->depthRight) + 1;
    } else {
        node->depthRight = 0;
    }
}
template <class T>
int LazyBST<T>::calcSize(TreeNode<T>* node) {
    if (node == NULL) return 0;
    return 1 + calcSize(node->left) + calcSize(node->right);
}

template <class T>
int LazyBST<T>::calcBalance(TreeNode<T>*& node) {
    if (node == NULL) return 0;
    return node->depthLeft - node->depthRight;
}


template <class T>
void LazyBST<T>::balance(TreeNode<T>*& node) {
    if (node == NULL) return;

    int balanceFactor = calcBalance(node);

    // If balance factor is greater than 1.5, rebuild the tree
    if (balanceFactor > 1.5) {
        //Calculate the size of the tree
        int treeSize = calcSize(node);
        
        // Create an array to store values
        T* arr = new T[treeSize];
        
        //Perform in-order traversal and store values in the array
        int index = 0;
        inOrderTraversal(node, arr, index);
        
        //Rebuild the tree from the array
        node = rebuildTree(arr, treeSize);

        delete[] arr;
    } 

    // Update depths after rotation or rebuilding
    updateDepths(node->left);
    updateDepths(node->right);
}


template <class T>
void LazyBST<T>::inOrderTraversal(TreeNode<T>* node, ofstream& file) { // in order traversal of the tree to file
    if (node == NULL){
        return;
    }

    inOrderTraversal(node->left,file);
    file << node->key<< endl;
    inOrderTraversal(node->right,file);
}

template <class T>
void LazyBST<T>::inOrderTraversal(TreeNode<T>* node) { // in order traversal of the tree
    if (node == NULL) return;

    inOrderTraversal(node->left);
    cout << node->key<< endl;
    inOrderTraversal(node->right);
}
template <class T>
void LazyBST<T>::inOrderTraversal(TreeNode<T>* node, T* arr, int& index) {
    if (node == NULL) return;

    inOrderTraversal(node->left, arr, index);
    arr[index++] = node->key; // Store the current node's key in the array
    inOrderTraversal(node->right, arr, index);
}



template <class T>
void LazyBST<T>::deleteTree(TreeNode<T>* node) {
    if (node == NULL) return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

template <class T>
TreeNode<T>* LazyBST<T>::rebuildTree(T* arr, int size) {
    // Rebuild the tree from the sorted array
    if (size == 0) return NULL;

    int mid = size / 2;
    TreeNode<T>* node = new TreeNode<T>(arr[mid]);
    node->left = rebuildTree(arr, mid);
    node->right = rebuildTree(arr + mid + 1, size - mid - 1);
    updateDepths(node);
    return node;
}



#endif