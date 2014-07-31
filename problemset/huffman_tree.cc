#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
  int idx;
  double prob;
  Node* left;
  Node* right;
  Node(int idx, double prob) : idx(idx), prob(prob), left(nullptr), right(nullptr) {}
};

Node* huffman(const vector<double> &p) {
  auto comp = [](Node* n1, Node* n2) {return n1->prob > n2->prob;};
  priority_queue<Node*, vector<Node*>, decltype(comp)> q(comp);
  for (int i = 0; i < p.size(); ++i) {
    q.push(new Node(i, p[i]));
  }
  while (q.size() > 1) {
    Node* n1 = q.top();
    q.pop();
    Node* n2 = q.top();
    q.pop();
    Node* parent = new Node(-1, n1->prob + n2->prob);
    q.push(parent);
    parent->left = n1;
    parent->right = n2;
  }
  return q.top();
}

void dfs(Node* node, string &path) {
  if (node == nullptr) return;
  if (node->left == nullptr && node->right == nullptr) {
    cout << path << endl;
    return;
  }
  path.push_back('0');
  dfs(node->left, path);
  path.pop_back();
  path.push_back('1');
  dfs(node->right, path);
  path.pop_back();
}

void delete_tree(Node* node) {
  if (node == nullptr) return;
  delete_tree(node->left);
  delete_tree(node->right);
  delete node;
}

int main() {
  vector<double> p = {0.05, 0.4, 0.08, 0.04, 0.1, 0.1, 0.23};
  Node* root = huffman(p);
  string path;
  dfs(root, path);
  delete_tree(root);
  return 0;
}
