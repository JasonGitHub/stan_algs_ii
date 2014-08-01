#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <deque>
#include <algorithm>

// #define _DEBUG_

using namespace std;

struct Node {
  int val;
  Node* left;
  Node* right;
  Node(int val) : val(val), left(nullptr), right(nullptr) {};
};

Node* recon_optimal_bst(const vector<vector<int> > &root, int i, int j) {
  if (i > j) return nullptr;
  int r = root[i][j];
  Node* curr = new Node(r);
  curr->left = recon_optimal_bst(root, i, r - 1);
  curr->right = recon_optimal_bst(root, r + 1, j);
  return curr;
}

Node* optimal_bst(const vector<double> &p) {
  const int n = p.size();
  vector<vector<double> > e(n, vector<double>(n, 0));  // expected cost of sub-bst from i to j
  vector<vector<double> > w(n, vector<double>(n, 0));  // sum of probabilities from i to j
  vector<vector<int> > root(n, vector<int>(n, 0));  // root of subtree from i to j
  for (int l = 1; l <= n; ++l) {
    for (int i = 0; i < n - l + 1; ++i) {
      int j = i + l - 1;
      e[i][j] = numeric_limits<double>::max();
      w[i][j] = i <= j - 1 ? w[i][j - 1] + p[j] : p[j];
      for (int r = i; r <= j; ++r) {
        double left_tree = i <= r - 1 ? e[i][r - 1] : 0;
        double right_tree = r + 1 <= j ? e[r + 1][j] : 0;
        double sum = w[i][j] + left_tree + right_tree;
        if (sum < e[i][j]) {
          e[i][j] = sum;
          root[i][j] = r;
        }
      }
    }
  }
#ifdef _DEBUG_
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << setw(6) << e[i][j] << " ";
    }
    cout << endl;
  }
#endif
  return recon_optimal_bst(root, 0, n - 1);
}

void print(Node* node, string indent, bool is_tail) {
  cout << indent << (is_tail ? "└── " : "├── ");
  if (node == nullptr) {
    cout << "*" << endl;
    return;
  }
  cout << node->val << endl;
  if (node->left != nullptr || node->right != nullptr) {
    indent.append(is_tail ? "    " : "│   ");
    print(node->right, indent, false);
    print(node->left, indent, true);
  }
}

void print_vertical(Node* root) {
  if (root == nullptr) return;
  deque<Node*> curr, next;
  curr.push_back(root);
  while (!curr.empty() && !all_of(curr.begin(), curr.end(), bind2nd(equal_to<Node*>(), nullptr))) {
    while (!curr.empty()) {
      Node* n = curr.front();
      curr.pop_front();
      if (n != nullptr) {
        next.push_back(n->left);
        next.push_back(n->right);
        cout << n->val << " ";
      } else {
        next.push_back(nullptr);
        next.push_back(nullptr);
        cout << "* ";
      }
    }
    cout << endl;
    swap(curr, next);
  }
}

void delete_tree(Node* node) {
  if (node == nullptr) return;
  delete_tree(node->left);
  delete_tree(node->right);
  delete node;
}

int main() {
  vector<double> p = {0.05, 0.4, 0.08, 0.04, 0.1, 0.1, 0.23};
  Node* bst = optimal_bst(p);
  print(bst, "", true);
  print_vertical(bst);
  delete_tree(bst);
  return 0;
}
