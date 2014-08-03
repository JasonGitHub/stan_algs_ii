#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

const int c_ab = 1;
const int c_gap = 1;

int get_cost(char a, char b) {
  return a == b ? 0 : c_ab;
}

pair<string, string> recon_match(string s1, string s2, const vector<vector<int> > &c) {
  string r1, r2;
  int i = s1.size(), j = s2.size();
  while (i > 0 && j > 0) {
    const int case1 = c[i - 1][j] + c_gap;
    const int case2 = c[i][j - 1] + c_gap;
    if (c[i][j] == case1) {
      r1.push_back(s1[i - 1]);
      r2.push_back('_');
      --i;
    } else if (c[i][j] == case2) {
      r1.push_back('_');
      r2.push_back(s2[j - 1]);
      --j;
    } else {
      r1.push_back(s1[i - 1]);
      r2.push_back(s2[j - 1]);
      --i;
      --j;
    }
  }
  if (i > 0) {
    r1.append(s1.substr(0, i));
    r2.append(i, '_');
  }
  if (j > 0) {
    r1.append(j, '_');
    r2.append(s2.substr(0, j));
  }
  reverse(r1.begin(), r1.end());
  reverse(r2.begin(), r2.end());
  return make_pair(r1, r2);
}

int cal_min_diff(string s1, string s2) {
  vector<vector<int> > c(s1.size() + 1, vector<int>(s2.size() + 1, 0));
  for (int i = 0; i <= s1.size(); ++i) {
    c[i][0] = i * c_gap;
  }
  for (int j = 0; j <= s2.size(); ++j) {
    c[0][j] = j * c_gap;
  }
  for (int i = 1; i <= s1.size(); ++i) {
    for (int j = 1; j <= s2.size(); ++j) {
      int case1 = c[i - 1][j] + c_gap;
      int case2 = c[i][j - 1] + c_gap;
      int case3 = c[i - 1][j - 1] + get_cost(s1[i - 1], s2[j - 1]);
      c[i][j] = min(case1, min(case2, case3));
    }
  }
  pair<string, string> p = recon_match(s1, s2, c);
  cout << p.first << " " << p.second << endl;
  return c[s1.size()][s2.size()];
}

int main() {
  string s1, s2;
  cin >> s1 >> s2;
  cout << cal_min_diff(s1, s2) << endl;
  return 0;
}
