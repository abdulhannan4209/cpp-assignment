#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.size();
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    int maxLen = 0, endPos = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLen) {
                    maxLen = dp[i][j];
                    endPos = i - 1;
                }
            } else dp[i][j] = 0;
        }
    }

    cout << "Lookup Table:\n";
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << dp[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "Longest Common Substring: " << s1.substr(endPos - maxLen + 1, maxLen) << "\n";
    cout << "Length: " << maxLen << "\n";
    return 0;
}
