#include <iostream>
#include <algorithm>
#include <vector>

// #define _DEBUG_

using namespace std;

const int k = 4;

struct Edge {
  Edge(int n1, int n2, int cost) : n1(n1), n2(n2), cost(cost) {}
  bool operator<(Edge that) const {
    return cost < that.cost;
  }
  int n1, n2;
  int cost;
};

class UnionFind {
  public:
    UnionFind(int n) {
      for (int i = 0; i <= n; ++i) {
        head_.push_back(i);
      }
      union_size_ = vector<int>(n + 1, 1);
      num_of_unions_ = n;
    }
    void assign_head(int this_node, int that_node) {
      int current_head = head_[this_node];
      int new_head = head_[that_node];
      union_size_[new_head] += union_size_[current_head];
      if (union_size_[current_head] > 0) {
        union_size_[current_head] = 0;
        for (auto &head : head_) {
          if (head == current_head) head = new_head;
        }
      }
      --num_of_unions_;
    }
    int get_union_size(int node_id) {
      return union_size_[head_[node_id]];
    }
    int get_head(int node_id) {
      return head_[node_id];
    }
    int get_num_of_unions() {
      return num_of_unions_;
    }
#ifdef _DEBUG_
    void debug() {
      for (int i = 1; i < head_.size(); ++i) {
        cout << head_[i] << " ";
      }
      cout << endl;
      for (int i = 1; i < union_size_.size(); ++i) {
        cout << union_size_[i] << " ";
      }
      cout << endl;
      cout << num_of_unions_ << endl;
    }
#endif
  private:
    vector<int> head_;
    vector<int> union_size_;
    int num_of_unions_;
};

int k_clustering(vector<Edge> &edges, int n) {
  UnionFind union_find(n);
  sort(edges.begin(), edges.end());
  auto pedge = edges.begin();
  while (true) {
    if (union_find.get_head(pedge->n1) != union_find.get_head(pedge->n2)) {
      if (union_find.get_num_of_unions() == k) break;
      if (union_find.get_union_size(pedge->n1) > union_find.get_union_size(pedge->n2)) union_find.assign_head(pedge->n2, pedge->n1);
      else union_find.assign_head(pedge->n1, pedge->n2);
    }
    ++pedge;
  }
#ifdef _DEBUG_
  union_find.debug();
#endif
  return pedge->cost;
}

int main(){
  int n;
  cin >> n;
  vector<Edge> edges;
  int n1, n2, cost;
  while (cin >> n1 >> n2 >> cost) {
    edges.emplace_back(Edge(n1, n2, cost));
  }
  cout << k_clustering(edges, n) << endl;
  return 0;
}

