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

#include "bstSequence.h"

using namespace std;

void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

/*
// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
  if (T == nullptr) return new Node(k);
  if (k < T->key) T->left = insert(T->left, k);
  else T->right = insert(T->right, k);
  fix_size(T);
  return T;
}
*/
Node *rightRotate(Node *T) {
    Node *L = T->left;
    T->left = L->right;
    L->right = T;
    fix_size(T);
    fix_size(L);
    return L;
}

Node *leftRotate(Node *T) {
    Node *R = T->right;
    T->right = R->left;
    R->left = T;
    fix_size(T);
    fix_size(R);
    return R;
}

// insert value v at rank r
Node* insert(Node* T, int v, int r) {
    if (!T) return new Node(v);
    int rank_of_root = T->left ? T->left->size : 0;
    if (r <= rank_of_root) {
        T->left = insert(T->left, v, r);
        T = rightRotate(T);
    } else {
        T->right = insert(T->right, v, r - rank_of_root - 1);
        T = leftRotate(T);
    }
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

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
  assert(T!=nullptr && r>=0 && r<T->size);

  int rank_of_root = T->left ? T->left->size : 0;
  if (r == rank_of_root) return T;
  if (r < rank_of_root) return select(T->left, r);
  else return select(T->right, r - rank_of_root - 1);
}

// Split tree T on rank r into tree L (containing ranks < r) and 
// a tree R (containing ranks >= r)
void split(Node *T, int r, Node **L, Node **R)
{
  //Implement void split(Node *T, int r, Node **L, Node **R)
    if (!T) {
        *L = nullptr;
        *R = nullptr;
        return;
    }
    int rank_left = T->left ? T->left->size : 0;
    if (r <= rank_left) {
        split(T->left, r, L, &T->left);
        *R = T;
    } else {
        split(T->right, r - rank_left - 1, &T->right, R);
        *L = T;
    }
    fix_size(T);
}

// insert value v at rank r

Node *insert_random(Node *T, int v, int r) {
    if (T == nullptr) return new Node(v);
    int rank_of_root = T->left ? T->left->size : 0;
    if (r <= rank_of_root) {
        T->left = insert_random(T->left, v, r);
        fix_size(T);
        if (rand() % T->size == 0) {
            // rotate right
            Node *tmp = T->left;
            T->left = tmp->right;
            tmp->right = T;
            T = tmp;
        }
    } else {
        T->right = insert_random(T->right, v, r - rank_of_root - 1);
        fix_size(T);
        if (rand() % T->size == 0) {
            // rotate left
            Node *tmp = T->right;
            T->right = tmp->left;
            tmp->left = T;
            T = tmp;
        }
    }
    return T;
}

// Returns true if team x defeated team y
// Leave this function unmodified
bool did_x_beat_y(int x, int y)
{
  assert (x != y);
  if (x > y) return !did_x_beat_y(y,x);
  unsigned long long lx = x;
  unsigned long long ly = y;
  return ((17 + 8321813 * lx + 1861 * ly) % 1299827) % 2 == 0;
}

// Return a BST containing a valid ordering of n teams
Node *order_n_teams(int n) {
    Node *T = nullptr;

    // add first team
    T = insert(T, 0, 0);

    // add remaining teams
    for (int i = 1; i < n; i++) {
        int lo = 0, hi = i - 1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            Node *node = select(T, mid);
            bool wins = did_x_beat_y(i, node->key);
            if (wins) {
                if (mid == 0 || !did_x_beat_y(i, select(T, mid - 1)->key)) {
                    // found location to insert new team
                    T = insert(T, i, mid);
                    break;
                } else {
                    hi = mid - 1;
                }
            } else {
                if (mid == i - 1 || did_x_beat_y(i, select(T, mid + 1)->key)) {
                    // found location to insert new team
                    T = insert(T, i, mid + 1);
                    break;
                } else {
                    lo = mid + 1;
                }
            }
        }
    }

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
  Node *T = nullptr;

  // test insert at beginning
  for (int i=0; i<5; i++)
    T = insert_random(T, i+1, 0);
  cout << "Tree should contain 5 4 3 2 1:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);

  // test insert at end
  for (int i=5; i<10; i++)
    T = insert_random(T, i+1, T->size);
  cout << "Tree should contain 5 4 3 2 1 6 7 8 9 10:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
  
  // test insert at middle
  for (int i=10; i<15; i++)
    T = insert_random(T, i+1, T->size/2);
  cout << "Tree should contain 5 4 3 2 1 12 14 15 13 11 6 7 8 9 10:\n";
  inorder=inorder_traversal(T);
  printVector(inorder);
    
  // once insert is working, the next step is to build the
  // insert_random function -- to test this, just change
  // calls to insert above to insert_random.

  int N = 100000; // this should run quickly even for very large N!
  Node *S = order_n_teams(N);
  if (S == nullptr || S->size != N)
    cout << "Size of tree returned by order_n_teams is wrong\n";
  else {
    cout << "Team ordering:\n";
        inorder=inorder_traversal(S);
        printVector(inorder);
    for (int i=0; i<N-1; i++) {
      Node *x = select(S, i);
      Node *y = select(S, i+1);
      if (!did_x_beat_y(x->key, y->key)) {
        cout << "Invalid sequence: team " << x->key << " (position " << i <<
	              ") lost to team " << y->key << " (position " << i+1 << ")\n";
      }
    }
  }  
  
  return 0;
}*/
