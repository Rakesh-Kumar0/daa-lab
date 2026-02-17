#include <bits/stdc++.h>
using namespace std;

// 0/1 Knapsack using Dynamic Programming (no user input)
// Example data is hardcoded for demonstration.

long long knap2D(const vector<int>& wt, const vector<int>& val, int W) {
    int n = wt.size();
    vector<vector<long long>> dp(n+1, vector<long long>(W+1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            dp[i][w] = dp[i-1][w];
            if (w >= wt[i-1])
                dp[i][w] = max(dp[i][w], dp[i-1][w - wt[i-1]] + val[i-1]);
        }
    }
    return dp[n][W];
}

long long knap1D(const vector<int>& wt, const vector<int>& val, int W) {
    int n = wt.size();
    vector<long long> dp(W+1, 0);

    for (int i = 0; i < n; ++i) {
        for (int w = W; w >= wt[i]; --w) {
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
        }
    }
    return dp[W];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Hardcoded example
    int n = 4;
    int W = 7;
    vector<int> wt = {3,4,9,6};
    vector<int> val = {30,40,90,60};

    long long ans2D = knap2D(wt, val, W);
    long long ans1D = knap1D(wt, val, W);

    cout << "Weights: "; for (int w : wt) cout << w << ' '; cout << '\n';
    cout << "Values:  "; for (int v : val) cout << v << ' '; cout << '\n';
    cout << "Capacity: " << W << "\n\n";

    cout << "Answer (2D DP): " << ans2D << '\n';
    cout << "Answer (1D optimized DP): " << ans1D << '\n';

    return 0;
}
