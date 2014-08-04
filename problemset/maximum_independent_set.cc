#include <iostream>
#include <vector>

using namespace std;

vector<int> recon_maximum_independent_set(const vector<int> &w, const vector<int> &items) {
  vector<int> ret;
  int i = items.size() - 1;
  while (i >= 0) {
    if (w[i] == (i >= 1 ? w[i - 1] : 0)) {
      --i;
    } else {
      ret.push_back(items[i]);
      i -= 2;
    }
  }
  return ret;
}

int maximum_independent_set(const vector<int> &items) {
  const int n = items.size();
  vector<int> w(n, 0);
  for (int i = 0; i < n; ++i) {
    int case1 = i >= 1 ? w[i - 1] : 0;
    int case2 = (i >= 2 ? w[i - 2] : 0) + items[i];
    w[i] = max(case1, case2);
  }
  vector<int> solution = move(recon_maximum_independent_set(w, items));
  for (int i : solution) cout << i << " "; cout << endl;
  return w[n - 1];
}

int main() {
  vector<int> items = {1, 2, 3, 4, 5};
  cout << maximum_independent_set(items) << endl;
  return 0;
}
