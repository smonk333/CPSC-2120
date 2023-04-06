/*
 * Name:
 * Date Submitted:
 * Lab Section:
 * Assignment Name:
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>

#include "binarySearchTree.h"

using namespace std;

void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
  if (T == nullptr) return new Node(k);
  if (k < T->key) T->left = insert(T->left, k);
  else T->right = insert(T->right, k);
  fix_size(T);
  return T;
}

// returns a vector of key values corresponding to the inorder traversal of T (i.e., the contents of T in sorted order)
vector<int> inorder_traversal(Node *T)
{
  vector<int> inorder;
  vector<int> rhs;
  if (T == nullptr) return inorder;
  inorder=inorder_traversal(T->left);
  inorder.push_back(T->key);
  rhs=inorder_traversal(T->right);
  inorder.insert(inorder.end(), rhs.begin(), rhs.end());
  return inorder;
}

// return a pointer to the node with key k in tree T, or nullptr if it doesn't exist
Node *find(Node *T, int k)
{
  //Implement Node *find(Node *T, int k)
  if (T == nullptr) {   //if T is nullptr, return nullptr
      return nullptr;
  }

  if (k == T->key) {    //if T has the right key, return T
      return T;
  }

  if (k < T->key) {     //if k is less than key of current T, search to the left
      return find(T->left, k);
  }

  else {
      return find(T->right, k);     //otherwise search right
  }

}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
  assert(T!=nullptr && r>=0 && r<T->size);
    int left_size = (T->left) ? T -> left->size : 0;
    if (r < left_size){
        return select(T->left, r);
    }
    if (r == left_size){
        return T;
    }
    return select(T->right, r - left_size - 1);
  //Implement Node *select(Node *T, int r)
}

// Join trees L and R (with L containing keys all <= the keys in R)
// Return a pointer to the joined tree.  
Node *join(Node *L, Node *R)
{
  // choose either the root of L or the root of R to be the root of the joined tree
  // (where we choose with probabilities proportional to the sizes of L and R)
  
  //Implement Node *join(Node *L, Node *R)
    if (L == nullptr){
        return R;
    }
    if (R == nullptr){
        return L;
    }
    if (rand() % (L->size + R->size) < L->size) {
        L->right = join(L->right, R);
        fix_size(L);
        return L;
    }
    else {
        R->left = join(L, R->left);
        fix_size(R);
        return R;
    }
}

// remove key k from T, returning a pointer to the resulting tree.
// it is required that k be present in T
Node *remove(Node *T, int k)
{
  assert(T != nullptr);
    if (k < T->key) {
        T->left = remove(T->left, k);
    }
    else if (k > T->key) {
        T->right = remove(T->right, k);
    }
    else {  // key found
        if (T->left == nullptr) {  // Case 1: no left child
            Node *temp = T->right;
            delete T;
            return temp;
        }
        else if (T->right == nullptr) {  // Case 2: no right child
            Node *temp = T->left;
            delete T;
            return temp;
        }
        else {  // Case 3: two children
            // Choose the maximum node from the left subtree as the new root
            Node *max_node = T->left;
            while (max_node->right != nullptr) {
                max_node = max_node->right;
            }

            T->key = max_node->key;
            T->left = remove(T->left, max_node->key);
        }
    }

    //Update the sizes of all affected nodes
    fix_size(T);

    //Return a pointer to the resulting tree
    return T;
}

// Split tree T on key k into tree L (containing keys <= k) and a tree R (containing keys > k)
void split(Node *T, int k, Node **L, Node **R)
{
  //Implement void split(Node *T, int k, Node **L, Node **R)
    if (!T) {
        *L = nullptr;
        *R = nullptr;
        return;
    }
    if (T->key <= k) {
        split(T->right, k, &(T->right), R);
        *L = T;
    }
    else {
        split(T->left, k, L, &(T->left));
        *R = T;
    }
    fix_size(T);
}

// insert key k into the tree T, returning a pointer to the resulting tree
Node *insert_random(Node *T, int k)
{
  // If k is the Nth node inserted into T, then:
  // with probability 1/N, insert k at the root of T
  // otherwise, insert_random k recursively left or right of the root of T
  
  //Implement Node *insert_random(Node *T, int k)
    if (T == nullptr) return new Node(k);

    int N = T->size + 1;
    if (rand() % N == 0) {
        // insert k at root with probability 1/N
        Node *new_node = new Node(k);
        new_node->left = T;
        new_node->size = T->size + 1;
        return new_node;
    }

    // otherwise, insert recursively left or right
    if (k < T->key) T->left = insert_random(T->left, k);
    else T->right = insert_random(T->right, k);
    fix_size(T);
    return T;
}

void printVector(vector<int> v)
{
    for (int i=0; i<v.size(); i++)
    {
        cout << v[i] << endl;
    }
}

/*int main(void)
{
  vector<int> inorder;
  vector<int> A(10,0);
  
  // put 0..9 into A[0..9] in random order
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
  cout << "Contents of A (to be inserted into BST):\n";
  printVector(A);
  
  // insert contents of A into a BST
  Node *T = nullptr;
  for (int i=0; i<10; i++) T = insert(T, A[i]);
  
  // print contents of BST (should be 0..9 in sorted order)
  cout << "Contents of BST (should be 0..9 in sorted order):\n";
  inorder=inorder_traversal(T);
  printVector(inorder);

  // test select
  for (int i=0; i<10; i++) {
    Node *result = select(T, i);
    if (!result || result->key != i) cout << "Select test failed for select(" << i << ")!\n";
  }

  // test find: Elements 0..9 should be found; 10 should not be found
  cout << "Elements 0..9 should be found; 10 should not be found:\n";
  for (int i=0; i<11; i++) 
    if (find(T,i)) cout << i << " found\n";
    else cout << i << " not found\n";

  // test split
  Node *L, *R;
  split(T, 4, &L, &R);
  cout << "Contents of left tree after split (should be 0..4):\n";
  inorder=inorder_traversal(L);
  printVector(inorder);
  cout << "Left tree size " << L->size << "\n";
  cout << "Contents of right tree after split (should be 5..9):\n";
  inorder=inorder_traversal(R);
  printVector(inorder);
  cout << "Right tree size " << R->size << "\n";
    
  // test join
  T = join(L, R);
  cout << "Contents of re-joined tree (should be 0..9)\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
  cout << "Tree size " << T->size << "\n";
  
  // test remove
  for (int i=0; i<10; i++) A[i] = i;
  for (int i=9; i>0; i--) swap(A[i], A[rand()%i]);
  for (int i=0; i<10; i++) {
    T = remove(T, A[i]);
    cout << "Contents of tree after removing " << A[i] << ":\n";
    inorder=inorder_traversal(T);
    printVector(inorder);
    if (T != nullptr)
      cout << "Tree size " << T->size << "\n";
  }

  // test insert_random
  cout << "Inserting 1 million elements in order; this should be very fast...\n";
  for (int i=0; i<1000000; i++) T = insert_random(T, i);
  cout << "Tree size " << T->size << "\n";
  cout << "Done\n";
  
  return 0;
}*/
