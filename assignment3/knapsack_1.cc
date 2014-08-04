#include <iostream>
#include <vector>

// #define _DEBUG_

using namespace std;

vector<int> recon_knapsack(const vector<int> &v, const vector<int> &w, int W, int n, const vector<vector<int> > &V) {
  vector<int> ret;
  int i = n, x = W;
  while (i >= 1 && x >= 0) {
    if (V[i][x] != V[i - 1][x]) {
      ret.push_back(i);
      x -= w[i];
    }
    --i;
  }
  return ret;
}

int knapsack(const vector<int> &v, const vector<int> &w, int W, int n) {
  vector<vector<int> > V(n + 1, vector<int> (W + 1, 0));
  for (int i = 1; i <= n; ++i) {
    for (int x = 0; x <= W; ++x) {
      int case_1 = x < w[i] ? INT_MIN : V[i - 1][x - w[i]] + v[i];
      int case_2 = V[i - 1][x];
      V[i][x] = max(case_1, case_2);
    }
  } 
#ifdef _DEBUG_
  vector<int> solution = move(recon_knapsack(v, w, W, n, V));
  for (auto i : solution) cout << i << " "; cout << endl;
#endif
  return V[n][W];
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
