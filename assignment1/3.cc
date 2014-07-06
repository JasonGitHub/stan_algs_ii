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

int get_edge_cost(int i, int j, const map<int, vector<pair<int, int> > > &graph) {
  assert(graph.find(i) != graph.end());
  auto it = find_if(graph.at(i).begin(), graph.at(i).end(), [&](pair<int, int> val) {return val.first == j;});
  assert(it != graph.at(i).end());
  return it->second;
}

int exist_edge(int i, int j, const map<int, vector<pair<int, int> > > &graph) {
  if (graph.find(i) == graph.end()) {
    return false;
  } else {
    auto it = find_if(graph.at(i).begin(), graph.at(i).end(), [&](pair<int, int> val) {return val.first == j;});
    return it != graph.at(i).end();
  }
}

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

int prim_heap(const map<int, vector<pair<int, int> > > &graph) {
  set<int> x;
  deque<Node> v_x;
  int start = -1;
  for (auto i = graph.begin(); i != graph.end(); ++i) {
    if (i == graph.begin()) {
      start = i->first;
      x.insert(start);
    } else {
      Node tmp(i->first, INT_MAX);
      if (exist_edge(tmp.id, start, graph)) tmp.cost = get_edge_cost(tmp.id, start, graph);
      v_x.push_back(tmp);
    }
  }
  make_heap(v_x.begin(), v_x.end(), greater<Node>());
  int sum = 0;
  while (!v_x.empty()) {
    Node min_node = v_x.front();
    x.insert(min_node.id);
    v_x.pop_front();
    sum += min_node.cost;
    for (auto i = v_x.begin(); i != v_x.end(); ++i) {
      if (exist_edge(min_node.id, i->id, graph)) i->cost = min(get_edge_cost(min_node.id, i->id, graph), i->cost);
    }
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
  cout << prim(graph) << endl;
  return 0;
}
