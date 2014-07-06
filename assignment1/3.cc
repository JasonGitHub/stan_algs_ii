/*
 * main.cc
 *
 *  Created on: Jul 3, 2014
 *      Author: Jason
 */

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <utility>
#include <cassert>
#include <algorithm>
#include <functional>

using namespace std;

int prim(const map<int, vector<pair<int, int> > > &graph) {
  set<int> x, v_x;
  for (auto i = graph.begin(); i != graph.end(); ++i) {
    if (i == graph.begin()) {
      x.insert(i->first);
    } else {
      v_x.insert(i->first);
    }
  }
  int sum = 0;
  while (!v_x.empty()) {
    int min_edge_cost = INT_MAX, min_node = -1;
    for (auto i = x.begin(); i != x.end(); ++i) {
      for (auto j = graph.at(*i).begin(); j != graph.at(*i).end(); ++j) {
        if (v_x.find(j->first) != v_x.end() && j->second < min_edge_cost) {
          min_edge_cost = j->second;
          min_node = j->first;
        }
      }
    }
    x.insert(min_node);
    v_x.erase(min_node);
    sum += min_edge_cost;
  }
  return sum;
}

struct Node {
  int id;
  int cost;
  Node(int id, int cost) : id(id), cost(cost) {}
  bool operator>(Node that) const {
    return cost > that.cost;
  }
};

void update_keys(int target, deque<Node> &v_x, const map<int, vector<pair<int, int> > > &graph) {
  for (auto i = graph.at(target).begin(); i != graph.at(target).end(); ++i) {
  	auto it = find_if(v_x.begin(), v_x.end(), [&](Node val){return val.id == i->first;});
  	if (it != v_x.end()) {
  		it->cost = min(it->cost, i->second);
  	}
  }
}

int prim_heap(const map<int, vector<pair<int, int> > > &graph) {
  set<int> x;
  deque<Node> v_x;
  int start = -1;
  // insert nodes into x and v-x
  for (auto i = graph.begin(); i != graph.end(); ++i) {
    if (i == graph.begin()) {
      start = i->first;
      x.insert(start);
    } else {
      v_x.push_back(Node(i->first, INT_MAX));
    }
  }
  update_keys(start, v_x, graph);
  make_heap(v_x.begin(), v_x.end(), greater<Node>());
  int sum = 0;
  // move a node from v-x to x until v-x is empty
  while (!v_x.empty()) {
    Node min_node = v_x.front();
    x.insert(min_node.id);
    v_x.pop_front();
    sum += min_node.cost;
    update_keys(min_node.id, v_x, graph);
    make_heap(v_x.begin(), v_x.end(), greater<Node>());
  }
  return sum;
}

int main() {
  int n, m;
  cin >> n >> m;
  map<int, vector<pair<int, int> > > graph;
  for (int i = 0; i < m; ++i) {
    int n1, n2, cost;
    cin >> n1 >> n2 >> cost;
    if (graph.find(n1) == graph.end()) {
      graph[n1] = vector<pair<int, int> > ();
    }
    if (graph.find(n2) == graph.end()) {
      graph[n2] = vector<pair<int, int> > ();
    }
    graph[n1].push_back(make_pair(n2, cost));
    graph[n2].push_back(make_pair(n1, cost));
  }
  cout << prim_heap(graph) << endl;
  return 0;
}
