/*
 * main.cc
 *
 *  Created on: Jul 3, 2014
 *      Author: Jason
 */

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

bool divde(const pair<int, int> &a, const pair<int, int> &b) {
  return static_cast<double>(a.first) / a.second > static_cast<double>(b.first) / b.second;
}

int main() {
  int n;
  cin >> n;
  vector<pair<int, int>> order;
  for (int i = 0; i < n; ++i) {
    int weight, length;
    cin >> weight >> length;
    order.push_back(make_pair(weight, length));
  }
  sort(order.begin(), order.end(), divde);
  long long time = 0, sum = 0;
  for_each(order.begin(), order.end(), [&](pair<int,int> val){
    time += val.second;
    sum += time * val.first;
  });
  cout << sum;
  return 0;
}
