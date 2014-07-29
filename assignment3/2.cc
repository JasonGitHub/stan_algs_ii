#include <iostream>
#include <vector>

using namespace std;

int knapsack(const vector<int> &v, const vector<int> &w, int W, int n) {
  vector<int> V(W + 1, 0);
  for (int i = 1; i <= n; ++i) {
    for (int x = W; x >= 0; --x) {
      int case_1 = x < w[i] ? INT_MIN : V[x - w[i]] + v[i];
      int case_2 = V[x];
      V[x] = max(case_1, case_2);
    }
  } 
  return V[W];
}

int main() {
  int W, n;
  cin >> W >> n;
  vector<int> v(n + 1), w(n + 1);
  int value, weight;
  for (int i = 1; i <= n; ++i) {
    cin >> v[i] >> w[i];
  }
  cout << knapsack(v, w, W, n) << endl;
  return 0;
}
