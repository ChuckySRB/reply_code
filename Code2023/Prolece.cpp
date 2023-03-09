#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;
const int MAXL = 1005;
const int INF = 1e9;

int C, R, S;
int L[MAXL];
int Vrc[MAXN][MAXN];
int dp[MAXN][MAXN][2];
pair<pair<int, int>, pair<char, pair<int, int>>> ans[MAXN];

int*** dist;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    // Input
    cin >> C >> R >> S;
    for (int i = 0; i < S; i++) {
        cin >> L[i];
    }
    cout<<C<<" "<<R<<endl;
    int ctr=0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            char c;
            cin >> c;
            //cout<<c<<" broj"<<endl;
            if (c == '*') {
                Vrc[i][j] = 0;
            } else {
                Vrc[i][j] = c;
         }


        }
    }

    // Allocate dist table
    dist = new int**[R];
    for (int i = 0; i < R; i++) {
        dist[i] = new int*[C];
        for (int j = 0; j < C; j++) {
            dist[i][j] = new int[L[S-1]+1];
        }
    }

    // Precompute minimum distances for snakes of all possible lengths
    for (int k = 1; k <= L[S-1]; k++) {
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                if (k == 1) {
                    dist[i][j][k] = 1;
                } else {
                    dist[i][j][k] = INF;
                    if (i > 0) {
                        dist[i][j][k] = min(dist[i][j][k], 1 + dist[i-1][j][k-1]);
                    }
                    if (i < R-1) {
                        dist[i][j][k] = min(dist[i][j][k], 1 + dist[i+1][j][k-1]);
                    }
                    if (j > 0) {
                        dist[i][j][k] = min(dist[i][j][k], 1 + dist[i][j-1][k-1]);
                    }
                    if (j < C-1) {
                        dist[i][j][k] = min(dist[i][j][k], 1 + dist[i][j+1][k-1]);
                    }
                }
            }
        }
    }

    // Dynamic programming
    int max_relevance = 0;
    for (int k = 1; k <= L[S-1]; k++) {
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                dp[i][j][k % 2] = 0;
                for (int m = 0; m < R; m++) {
                    for (int n = 0; n < C; n++) {
                        if (dist[m][n][k] <= L[S-1] - k + 1) {
                            int relevance = dp[m][n][(k-1) % 2] + Vrc[i][j];
                            if (Vrc[m][n] != 0 && Vrc[m][n] != -1) {
                                int l = L[S-1] - k + dist[m][n][k];
                                relevance = max(relevance, dp[m][n][l % 2] + Vrc[i][j]);
                            }
                            dp[i][j][k % 2] = max(dp[i][j][k % 2], relevance);
                    }
                }
            }
            if (k == L[S-1] && dp[i][j][k % 2] > max_relevance) {
                max_relevance = dp[i][j][k % 2];
            }
        }
    }
}

// Backtracking
int snake_idx = 0;
int k = L[S-1];
int max_i, max_j;
for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
        if (dp[i][j][k % 2] == max_relevance) {
            max_i = i;
            max_j = j;
            break;
        }
    }
}
while (snake_idx < S) {
    int l = L[snake_idx];
    ans[snake_idx].first.first = max_j;
    ans[snake_idx].first.second = max_i;
    if (snake_idx < S-1) {
        int prev_max_i = max_i, prev_max_j = max_j;
        for (int m = 0; m < R; m++) {
            for (int n = 0; n < C; n++) {
                if (dist[m][n][l] <= L[S-2-snake_idx]) {
                    int relevance = dp[m][n][(k-1) % 2];
                    if (Vrc[m][n] != 0 && Vrc[m][n] != -1) {
                        int ll = L[S-2-snake_idx] - dist[m][n][l] + 1;
                        relevance = max(relevance, dp[m][n][ll % 2]);
                    }
                    if (relevance + Vrc[max_i][max_j] == dp[max_i][max_j][k % 2]) {
                        max_i = m;
                        max_j = n;
                        ans[snake_idx].second.first = (m > prev_max_i) ? 'D' : (m < prev_max_i) ? 'U' : (n > prev_max_j) ? 'R' : 'L';
                        ans[snake_idx].second.second.first = prev_max_j;
                        ans[snake_idx].second.second.second = prev_max_i;
                    }
                }
            }
        }
    }
    snake_idx++;
    k--;
}

// Output
cout << max_relevance << '\n';
for (int i = 0; i < S; i++) {
    cout << ans[i].first.first << ' ' << ans[i].first.second << ' ';
    if (i < S-1) {
        cout << ans[i].second.first << ' ' << ans[i].second.second.first << ' ' << ans[i].second.second.second << '\n';
    } else {
        cout << '\n';
    }
}

return 0;
}
