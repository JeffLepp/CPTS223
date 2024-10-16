#ifndef AVLTree_H
#define AVLTree_H

#include <iostream>
#include <limits>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename Comparable>
class AVLTree
{
private:
    struct AVLNode  // refer to textbook, Figure 4.40
    {
        Comparable element;
        AVLNode *left;
        AVLNode *right;
        int height;

        AVLNode( const Comparable & theElement, AVLNode *lt, AVLNode *rt ): element(theElement), left(lt), right(rt) {}
        AVLNode( Comparable && theElement, AVLNode *lt, AVLNode *rt ): element(move(theElement)), left(lt), right(rt) {}
    };

    AVLNode *root;

    AVLNode * findMin( AVLNode * t ) const;
    AVLNode * findMax( AVLNode * t ) const;
    void makeEmpty( AVLNode * & t );

    void balance(AVLNode * & t);
    void rotateWithLeftChild( AVLNode * & t );
    void rotateWithRightChild( AVLNode * & t );
    void doubleWithLeftChild( AVLNode * & t);
    void doubleWithRightChild( AVLNode * & t);

public:
    AVLTree();
    ~AVLTree();

    void makeEmpty();
    const Comparable & findMin() const;
    const Comparable & findMax() const;

    bool contains(const Comparable & x) const;
    bool contains( const Comparable & x, AVLNode* y ) const;

    void insert(const Comparable & x);
    void insert(const Comparable & x, AVLNode* & y);

    void remove(const Comparable & x);
    void remove( const Comparable & x, AVLNode* & y );

    int treeSize() const;
    int treeSize(AVLNode* t) const;

    int computeHeight() const;
    int computeHeight(AVLNode* t) const;

    int readRootHeight() const;

    bool isBalanced() const;
    bool isBalanced(AVLNode* t) const;
    
    bool isBST() const;
    bool isBST(AVLNode* t, Comparable min, Comparable max) const;

    double averageDepth() const;
    void averageDepth(AVLNode* t, int depth, int &totalDepth, int &nodeCount) const;


    void removeByRank(int rank);
    void removeByRank(AVLNode* & t, int rank, int &count);

    // the next line follows textbook Figure 4.42, Line 19
    static const int ALLOWED_IMBALANCE = 1;
};

// constructor
template <class Comparable>
AVLTree<Comparable>::AVLTree() : root(NULL) {}

// destructor
template <class Comparable>
AVLTree<Comparable>::~AVLTree()
{
    makeEmpty();
}

// public makeEmpty: follow the makeEmpty in BST, referring to textbook, Figure 4.27
template <typename Comparable>
void AVLTree<Comparable>::makeEmpty() {
    makeEmpty(root);
}

// private recursive makeEmpty: follow the makeEmpty in BST, referring to textbook, Figure 4.27
template <typename Comparable>
void AVLTree<Comparable>::makeEmpty(AVLNode * & t) {
    if ( t != NULL ) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = NULL;
    }
}

// public findMin: follow the findMin in BST, referring to textbook, Figure 4.20
template <typename Comparable>
const Comparable & AVLTree<Comparable>::findMin() const {
    
    if (root == NULL) {
        throw underflow_error("Tree is empty");
    }
    return findMin(root)->element;
}

// private findMin: follow the findMin in BST, referring to textbook, Figure 4.20
template <typename Comparable>
typename AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::findMin(AVLNode * t) const {

    if ( t == NULL ) {
        return NULL;
    } else if (t->left == NULL) {
        return t;
    } else {
        return findMin(t->left);
    }
}

// public findMax: follow the findMax in BST, referring to textbook, Figure 4.21
template <typename Comparable>
const Comparable & AVLTree<Comparable>::findMax() const {

    if (root == NULL) {
        throw underflow_error("Tree is empty");
    }
    return findMax(root)->element;
}

// private findMax: follow the findMax in BST, referring to textbook, Figure 4.21
template <typename Comparable>
typename AVLTree<Comparable>::AVLNode* AVLTree<Comparable>::findMax(AVLNode * t) const {

    if ( t == NULL ) {
        return NULL;
    } else if (t->right == NULL) {
        return t;
    } else {
        return findMax(t->right);
    }
}

// start our implementation:
// public contains: follow the contains in BST, referring to textbook, Figure 4.17 and Figure 4.18
template<typename Comparable>
bool AVLTree<Comparable>::contains( const Comparable & x ) const {
    return contains(x, root);
}

// private contains
template<typename Comparable>
bool AVLTree<Comparable>::contains( const Comparable & x, AVLNode* y ) const {

    if (y == nullptr) 
    {
        return false;
    } else if (x < y->element) 
    {
        return contains(x, y->left); 
    } else if (y->element < x) 
    {
        return contains(x, y->right); 
    } else 
    {
        return true; 
    }
    return false;
}

// public insert: following BST, referring to textbook, Figure 4.17 and Figure 4.23
template<typename Comparable>
void AVLTree<Comparable>::insert(const Comparable & x) {
    insert(x, root);
}

// private insert
template<typename Comparable>
void AVLTree<Comparable>::insert(const Comparable & x, AVLNode* & y) {
    if ( y == nullptr) 
    {
        y  = new AVLNode(x, nullptr, nullptr);
    } else if (x < y->element) 
    {
        insert(x, y->left); 
    } else if (y->element < x) 
    {
        insert(x, y->right); 
    } else 
    {
        return;  // Handles case of duplicates implicitly
    }
    balance(y);
}

// public remove: refer to textbook, Figure 4.17 and Figure 4.26
template<typename Comparable>
void AVLTree<Comparable>::remove( const Comparable & x ) {
    remove(x, root);
}

// private remove
template<typename Comparable>
void AVLTree<Comparable>::remove( const Comparable & x, AVLNode* & y ) {
    if (y == nullptr) {
        return;
    }
    if (x < y->element) {
        remove(x, y->left); 
    } else if (y->element < x) {
        remove(x, y->right); 
    } else { 
        if (y->left && y->right) { 
            y->element = findMin(y->right)->element; 
            remove(y->element, y->right); 
        } else {
            AVLNode* oldNode = y; 
            y = (y->left != nullptr) ? y->left : y->right; 
            delete oldNode; 
        }
    }
    balance(y);
}

// private balance: refer to textbook, Figure 4.42, Line 21 - 40
// assume t is the node that violates the AVL condition, and we then identify which case to use (out of 4 cases)
template<typename Comparable>
void AVLTree<Comparable>::balance(AVLNode * & t) {
if (t == nullptr) {
        return;
    }

    // Update the height of the current node
    t->height = 1 + max(computeHeight(t->left), computeHeight(t->right));
    
    int imbalance = computeHeight(t->left) - computeHeight(t->right);

    // Left heavy
    if (imbalance > 1) {
        if (computeHeight(t->left->left) >= computeHeight(t->left->right)) {
            rotateWithLeftChild(t);
        } else {
            doubleWithLeftChild(t);
        }
    }
    // Right heavy
    else if (imbalance < -1) {
        if (computeHeight(t->right->right) >= computeHeight(t->right->left)) {
            rotateWithRightChild(t);
        } else {
            doubleWithRightChild(t);
        }
    }
}

// private rotateWithLeftChild: for case 1, referring to textbook, Figure 4.44 (code) and Figure 4.43 (visualization)
template<typename Comparable>
void AVLTree<Comparable>::rotateWithLeftChild(AVLNode * & k2) {
    AVLNode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(computeHeight(k2->left), computeHeight(k2->right)) +1; 
    k1->height = max(computeHeight(k1->left), k2->height) +1;
    k2 = k1;
}

// private rotateWithRightChild: for case 4 (the mirrored case of case 1)
template<typename Comparable>
void AVLTree<Comparable>::rotateWithRightChild(AVLNode * & k2) {
    AVLNode* k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = max(computeHeight(k2->left), computeHeight(k2->right)) +1; 
    k1->height = max(computeHeight(k1->right), k2->height) +1;
    k2 = k1;
}

// private doubleWithLeftChild: for case 2, see textbook, Figure 4.46 (code) and Figure 4.45 (visualization)
template<typename Comparable>
void AVLTree<Comparable>::doubleWithLeftChild(AVLNode * & k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

// private doubleWithRightChild: for case 3 (the mirrored case of case 2)
template<typename Comparable>
void AVLTree<Comparable>::doubleWithRightChild(AVLNode * & k3) {
    rotateWithLeftChild(k3->right);
    rotateWithRightChild(k3);
}

// public isBalanced
template <class Comparable>
bool AVLTree<Comparable>::isBalanced() const {
    return isBalanced(root);
}

// private isBalanced
template <class Comparable>
bool AVLTree<Comparable>::isBalanced(AVLNode* t) const {
    if (t == nullptr) {
        return true;
    }
    return (abs(computeHeight(t->left) - computeHeight(t->right)) <= 1) && isBalanced(t->left) && isBalanced(t->right);
}

// public isBST
template <class Comparable>
bool AVLTree<Comparable>::isBST() const {
    return isBST(root, numeric_limits<Comparable>::min(), numeric_limits<Comparable>::max());
}

// private isBST
template<typename Comparable>
bool AVLTree<Comparable>::isBST(AVLNode* t, Comparable min, Comparable max) const {
    if (t == nullptr){
        return true;
    }
    if (t->element < min || t->element > max) {
        return false;
    }
    return isBST(t->left, min, t->element) && isBST(t->right, t->element, max);
}

// public treeSize
template <typename Comparable>
int AVLTree<Comparable>::treeSize() const {
    treeSize(root);
    return 0;
}

// private treeSize
template <typename Comparable>
int AVLTree<Comparable>::treeSize(AVLNode* t) const {
    if (t == nullptr) {
        return 0;
    }
    return 1 + treeSize(t->left) + treeSize(t->right);
}

// public computeHeight. See Figure 4.61 in Textbook
template <typename Comparable>
int AVLTree<Comparable>::computeHeight() const {
    return computeHeight(root);
}

// private computeHeight
template <typename Comparable>
int AVLTree<Comparable>::computeHeight(AVLNode* t) const {
    if (t == nullptr) {
        return -1;
    }
    return 1 + max(computeHeight(t->left), computeHeight(t->right));
}

// public readRootHeight
template <typename Comparable>
int AVLTree<Comparable>::readRootHeight() const {
    if (root == nullptr) {
        return -1;
    }

    return root -> height;
}

// public averageDepth
template <typename Comparable>
double AVLTree<Comparable>::averageDepth() const {
    int total = 0;
    int nodes = 0;
    averageDepth(root, 0, total, nodes);

    // static cast line adapted from information in https://www.daniweb.com/programming/software-development/threads/128202/issues-with-static-cast-double
    return (nodes > 0) ? static_cast<double>(total) / nodes : 0.0;
}

// private averageDepth
template <typename Comparable>
void AVLTree<Comparable>::averageDepth(AVLNode* t, int depth, int &total, int &nodes) const {
    if (t == nullptr) {
        return;
    }
    total += depth;
    nodes++;
    averageDepth(t->left, depth + 1, total, nodes);
    averageDepth(t->right, depth + 1, total, nodes);
}

// public removeByRank
template <typename Comparable>
void AVLTree<Comparable>::removeByRank(int rank) {
    int count = 0;
    removeByRank(root, rank, count);
}

// private removeByBank
template <typename Comparable>
void AVLTree<Comparable>::removeByRank(AVLNode* & t, int rank, int &count) {
    if (t == nullptr) {
        return;
    }

    if (t->left) {
        removeByRank(t->left, rank, count);
    }
    if (++count == rank) {
        remove(t->element);
        return;
    }
    if (t->right) {
        removeByRank(t->right, rank, count);
    }
}

#endif