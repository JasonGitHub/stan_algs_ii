#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
  vector<int> idxs;
  double prob;
  Node(int idx, double prob) : prob(prob) {
    idxs.push_back(idx);
  }
  bool operator>(const Node &that) const {
    return prob > that.prob;
  }
  Node operator+(const Node &that) const {
    Node ret(that);
    ret.idxs.insert(ret.idxs.begin(), idxs.begin(), idxs.end());
    ret.prob += prob;
    return ret;
  }
};

vector<string> huffman(const vector<double> &p) {
  vector<string> ret(p.size(), "");
  priority_queue<Node, vector<Node>, greater<Node>> q;
  for (int i = 0; i < p.size(); ++i) {
    q.emplace(Node(i, p[i]));
  }
  while (q.size() > 1) {
    Node n1 = q.top();
    q.pop();
    Node n2 = q.top();
    q.pop();
    q.push(n1 + n2);
    for (auto idx : n1.idxs) {
      ret[idx].push_back('0');
    }
    for (auto idx : n2.idxs) {
      ret[idx].push_back('1');
    }
  }
  return ret;
}

int main() {
  vector<double> p = {0.05, 0.4, 0.08, 0.04, 0.1, 0.1, 0.23};
  for (const auto &str : huffman(p)) {
    cout << str << endl;
  }
  return 0;
}
