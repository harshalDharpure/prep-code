#include <bits/stdc++.h>
using namespace std;

/*
    Microsoft Hard Questions (C++)
    -------------------------------
    This file is for strong interview preparation.
    Focus on understanding patterns, not memorizing code.
*/

// 1) Largest Rectangle in Histogram
int largestRectangleArea(vector<int>& heights) {
    stack<int> st;
    int maxArea = 0;

    for (int i = 0; i <= heights.size(); ++i) {
        int curr = (i == heights.size()) ? 0 : heights[i];
        while (!st.empty() && curr < heights[st.top()]) {
            int h = heights[st.top()];
            st.pop();
            int width = st.empty() ? i : i - st.top() - 1;
            maxArea = max(maxArea, h * width);
        }
        st.push(i);
    }
    return maxArea;
}

// 2) Minimum Window Substring
string minWindow(string s, string t) {
    unordered_map<char, int> need, have;
    for (char ch : t) need[ch]++;

    int required = need.size();
    int formed = 0;
    int left = 0, bestLeft = 0, minLen = INT_MAX;

    for (int right = 0; right < s.size(); ++right) {
        char ch = s[right];
        if (need.count(ch)) {
            have[ch]++;
            if (have[ch] == need[ch]) formed++;
        }

        while (formed == required) {
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                bestLeft = left;
            }

            char leftCh = s[left];
            if (need.count(leftCh)) {
                have[leftCh]--;
                if (have[leftCh] < need[leftCh]) formed--;
            }
            left++;
        }
    }

    return minLen == INT_MAX ? "" : s.substr(bestLeft, minLen);
}

// 3) Distinct Subsequences
int numDistinct(string s, string t) {
    vector<long long> dp(t.size() + 1, 0);
    dp[0] = 1;

    for (char ch : s) {
        for (int j = t.size() - 1; j >= 0; --j) {
            if (ch == t[j]) dp[j + 1] += dp[j];
        }
    }
    return (int)dp[t.size()];
}

// 4) Word Ladder
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> dict(wordList.begin(), wordList.end());
    if (!dict.count(endWord)) return 0;

    queue<string> q;
    q.push(beginWord);
    int steps = 1;

    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; ++i) {
            string curr = q.front(); q.pop();
            for (int j = 0; j < curr.size(); ++j) {
                string next = curr;
                for (char ch = 'a'; ch <= 'z'; ++ch) {
                    next[j] = ch;
                    if (next == curr) continue;
                    if (next == endWord) return steps + 1;
                    if (dict.count(next)) {
                        dict.erase(next);
                        q.push(next);
                    }
                }
            }
        }
        steps++;
    }
    return 0;
}

// 5) N-Queens
vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> ans;
    vector<string> board(n, string(n, '.'));
    vector<int> col(n), diag1(2 * n - 1), diag2(2 * n - 1);

    function<void(int)> backtrack = [&](int row) {
        if (row == n) {
            ans.push_back(board);
            return;
        }

        for (int c = 0; c < n; ++c) {
            if (col[c] || diag1[row + c] || diag2[row - c + n - 1]) continue;
            board[row][c] = 'Q';
            col[c] = diag1[row + c] = diag2[row - c + n - 1] = 1;
            backtrack(row + 1);
            board[row][c] = '.';
            col[c] = diag1[row + c] = diag2[row - c + n - 1] = 0;
        }
    };

    backtrack(0);
    return ans;
}

// 6) Serialize and Deserialize Binary Tree
struct Node {
    int val;
    Node* left;
    Node* right;
    Node(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
public:
    string serialize(Node* root) {
        if (!root) return "#,";
        return to_string(root->val) + "," + serialize(root->left) + serialize(root->right);
    }

    Node* deserialize(string data) {
        queue<string> q;
        string token;
        stringstream ss(data);
        while (getline(ss, token, ',')) {
            if (!token.empty()) q.push(token);
        }
        return build(q);
    }

    Node* build(queue<string>& q) {
        string val = q.front(); q.pop();
        if (val == "#") return nullptr;

        Node* root = new Node(stoi(val));
        root->left = build(q);
        root->right = build(q);
        return root;
    }
};

// 7) Median of Two Sorted Arrays
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    if (nums1.size() > nums2.size()) return findMedianSortedArrays(nums2, nums1);

    int m = nums1.size(), n = nums2.size();
    int left = 0, right = m;

    while (left <= right) {
        int partitionX = left + (right - left) / 2;
        int partitionY = (m + n + 1) / 2 - partitionX;

        int maxLeftX = (partitionX == 0) ? INT_MIN : nums1[partitionX - 1];
        int minRightX = (partitionX == m) ? INT_MAX : nums1[partitionX];
        int maxLeftY = (partitionY == 0) ? INT_MIN : nums2[partitionY - 1];
        int minRightY = (partitionY == n) ? INT_MAX : nums2[partitionY];

        if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
            if ((m + n) % 2 == 0) {
                return (max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2.0;
            }
            return max(maxLeftX, maxLeftY);
        } else if (maxLeftX > minRightY) {
            right = partitionX - 1;
        } else {
            left = partitionX + 1;
        }
    }
    return 0.0;
}

// 8) Regular Expression Matching
bool isMatch(string s, string p) {
    vector<vector<bool>> dp(s.size() + 1, vector<bool>(p.size() + 1, false));
    dp[0][0] = true;

    for (int j = 1; j <= p.size(); ++j) {
        if (p[j - 1] == '*') dp[0][j] = dp[0][j - 2];
    }

    for (int i = 1; i <= s.size(); ++i) {
        for (int j = 1; j <= p.size(); ++j) {
            if (p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 2] || (dp[i - 1][j] && (s[i - 1] == p[j - 2] || p[j - 2] == '.'));
            } else {
                dp[i][j] = dp[i - 1][j - 1] && (s[i - 1] == p[j - 1] || p[j - 1] == '.');
            }
        }
    }
    return dp[s.size()][p.size()];
}

// 9) Palindrome Partitioning
vector<vector<string>> partition(string s) {
    vector<vector<string>> result;
    vector<string> path;
    vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));

    for (int i = 0; i < s.size(); ++i) {
        for (int j = i; j < s.size(); ++j) {
            if (s[i] == s[j] && (j - i <= 1 || dp[i + 1][j - 1])) {
                dp[i][j] = true;
            }
        }
    }

    function<void(int)> backtrack = [&](int start) {
        if (start == s.size()) {
            result.push_back(path);
            return;
        }
        for (int end = start; end < s.size(); ++end) {
            if (dp[start][end]) {
                path.push_back(s.substr(start, end - start + 1));
                backtrack(end + 1);
                path.pop_back();
            }
        }
    };

    backtrack(0);
    return result;
}

// 10) Longest Palindromic Substring
string longestPalindrome(string s) {
    if (s.empty()) return "";
    int start = 0, maxLen = 1;

    auto expand = [&](int l, int r) {
        while (l >= 0 && r < s.size() && s[l] == s[r]) {
            if (r - l + 1 > maxLen) {
                maxLen = r - l + 1;
                start = l;
            }
            l--;
            r++;
        }
    };

    for (int i = 0; i < s.size(); ++i) {
        expand(i, i);
        expand(i, i + 1);
    }

    return s.substr(start, maxLen);
}

int main() {
    cout << "Microsoft Hard Questions - C++\n\n";
    vector<int> h = {2,1,5,6,2,3};
    cout << "1) Largest Rectangle in Histogram: " << largestRectangleArea(h) << "\n";

    cout << "2) Minimum Window Substring: " << minWindow("ADOBECODEBANC", "ABC") << "\n";
    cout << "3) Distinct Subsequences: " << numDistinct("babgbag", "bag") << "\n";

    vector<string> words = {"hot","dot","dog","lot","log","cog"};
    cout << "4) Word Ladder length: " << ladderLength("hit", "cog", words) << "\n";

    cout << "5) N-Queens count: " << solveNQueens(4).size() << "\n";
    cout << "7) Median of Two Sorted Arrays: " << findMedianSortedArrays({1,3}, {2}) << "\n";
    cout << "8) Regex matching: " << isMatch("aa", "a*") << "\n";
    cout << "10) Longest Palindromic Substring: " << longestPalindrome("babad") << "\n";

    return 0;
}
