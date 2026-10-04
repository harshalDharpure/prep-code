#include <bits/stdc++.h>
using namespace std;

/*
    Microsoft Detailed Explanations
    ------------------------------
    This file focuses on understanding, not just code.
    Each question here is followed by an interview-style explanation.
*/

// Question 1: Two Sum
// Explanation:
// We scan the array once. For each value x, we check whether target - x was seen before.
// This is a classic hash map pattern.
// Time: O(n)
// Space: O(n)
vector<int> twoSumDetailed(vector<int>& nums, int target) {
    unordered_map<int, int> seen;
    for (int i = 0; i < nums.size(); ++i) {
        int needed = target - nums[i];
        if (seen.count(needed)) return {seen[needed], i};
        seen[nums[i]] = i;
    }
    return {};
}

// Question 2: Valid Parentheses
// Explanation:
// Stack is used because the last opening bracket must match the current closing bracket.
// Time: O(n)
// Space: O(n)
bool validParenthesesDetailed(string s) {
    stack<char> st;
    unordered_map<char, char> pair = {{')','('},{']','['},{'}','{'}};

    for (char ch : s) {
        if (ch == '(' || ch == '[' || ch == '{') st.push(ch);
        else {
            if (st.empty() || st.top() != pair[ch]) return false;
            st.pop();
        }
    }
    return st.empty();
}

// Question 3: Longest Substring Without Repeating Characters
// Explanation:
// Use a sliding window: expand right pointer, and when a repeat is found,
// move left pointer forward until uniqueness is restored.
// Time: O(n)
// Space: O(n)
int longestSubstringDetailed(string s) {
    unordered_map<char, int> lastIndex;
    int left = 0, best = 0;

    for (int right = 0; right < s.size(); ++right) {
        if (lastIndex.count(s[right])) {
            left = max(left, lastIndex[s[right]] + 1);
        }
        lastIndex[s[right]] = right;
        best = max(best, right - left + 1);
    }
    return best;
}

// Question 4: Merge Intervals
// Explanation:
// Sort by start, then merge whenever the next interval overlaps the current one.
// Time: O(n log n)
// Space: O(n)
vector<vector<int>> mergeDetailed(vector<vector<int>>& intervals) {
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> result;
    for (auto& it : intervals) {
        if (result.empty() || it[0] > result.back()[1]) {
            result.push_back(it);
        } else {
            result.back()[1] = max(result.back()[1], it[1]);
        }
    }
    return result;
}

// Question 5: Binary Tree Level Order Traversal
// Explanation:
// Use BFS with a queue. Each queue level represents one traversal level.
// Time: O(n)
// Space: O(n)
struct DTreeNode {
    int val;
    DTreeNode *left, *right;
    DTreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<vector<int>> levelOrderDetailed(DTreeNode* root) {
    if (!root) return {};
    vector<vector<int>> result;
    queue<DTreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int sz = q.size();
        vector<int> level;
        for (int i = 0; i < sz; ++i) {
            DTreeNode* node = q.front(); q.pop();
            level.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(level);
    }
    return result;
}

int main() {
    cout << "Detailed Explanation Practice\n\n";

    vector<int> nums = {2, 7, 11, 15};
    cout << "Two Sum: ";
    for (int x : twoSumDetailed(nums, 9)) cout << x << " ";
    cout << "\n";

    cout << "Valid Parentheses: " << validParenthesesDetailed("([{}])") << "\n";
    cout << "Longest substring length: " << longestSubstringDetailed("abcabcbb") << "\n";

    vector<vector<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};
    auto merged = mergeDetailed(intervals);
    cout << "Merged Intervals: ";
    for (auto i : merged) cout << "[" << i[0] << "," << i[1] << "] ";
    cout << "\n";

    DTreeNode* root = new DTreeNode(3);
    root->left = new DTreeNode(9);
    root->right = new DTreeNode(20);
    root->right->left = new DTreeNode(15);
    root->right->right = new DTreeNode(7);

    auto levels = levelOrderDetailed(root);
    cout << "Level Order: ";
    for (auto level : levels) {
        for (int x : level) cout << x << " ";
        cout << "| ";
    }
    cout << "\n";

    return 0;
}
