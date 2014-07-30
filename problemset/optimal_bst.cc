#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits>
#include <numeric>

using namespace std;

double optimal_bst(const vector<double> &p) {
  const int n = p.size();
  vector<vector<double> > a(n, vector<double>(n, 0));
  for (int l = 1; l <= n; ++l) {
    for (int i = 0; i < n - l + 1; ++i) {
      int j = i + l - 1;
      a[i][j] = numeric_limits<double>::max();
      for (int r = i; r <= j; ++r) {
        double left_tree = i <= r - 1 ? a[i][r - 1] : 0;
        double right_tree = r + 1 <= j ? a[r + 1][j] : 0;
        double sum = accumulate(p.begin() + i, p.begin() + j + 1, 0.0) + left_tree + right_tree;
        a[i][j] = min(sum, a[i][j]);
      }
    }  
  }
  // Debug
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << setw(6) << a[i][j] << " ";
    }
    cout << endl;
  }
  return a[0][n - 1];
}

int main() {
  vector<double> p = {0.05, 0.4, 0.08, 0.04, 0.1, 0.1, 0.23};
  cout << optimal_bst(p) << endl;
  return 0;
}
