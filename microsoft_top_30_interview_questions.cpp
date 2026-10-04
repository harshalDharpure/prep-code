#include <bits/stdc++.h>
using namespace std;

/*
    Microsoft Top 30 Interview Questions in C++
    -------------------------------------------
    This file is a focused interview-prep list.
    It is ordered by importance and frequency in Microsoft-style coding rounds.

    Strategy to use:
    1. Understand the pattern.
    2. Explain the idea in plain English.
    3. Write the code without looking.
    4. Check edge cases and complexity.
    5. Practice a few times until it feels natural.
*/

// ------------------------------------------------------------
// 1) Two Sum
// Input: nums = [2,7,11,15], target = 9
// Output: [0,1]
// ------------------------------------------------------------
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen;
    for (int i = 0; i < nums.size(); ++i) {
        if (seen.count(target - nums[i])) {
            return {seen[target - nums[i]], i};
        }
        seen[nums[i]] = i;
    }
    return {};
}

// ------------------------------------------------------------
// 2) Best Time to Buy and Sell Stock
// Input: [7,1,5,3,6,4]
// Output: 5
// ------------------------------------------------------------
int maxProfit(vector<int>& prices) {
    if (prices.empty()) return 0;
    int minPrice = prices[0];
    int maxProfit = 0;

    for (int price : prices) {
        minPrice = min(minPrice, price);
        maxProfit = max(maxProfit, price - minPrice);
    }
    return maxProfit;
}

// ------------------------------------------------------------
// 3) Valid Parentheses
// Input: "([{}])"
// Output: true
// ------------------------------------------------------------
bool isValid(string s) {
    stack<char> st;
    unordered_map<char, char> pairs = {{')', '('}, {']', '['}, {'}', '{'}};

    for (char ch : s) {
        if (ch == '(' || ch == '[' || ch == '{') {
            st.push(ch);
        } else {
            if (st.empty() || st.top() != pairs[ch]) return false;
            st.pop();
        }
    }
    return st.empty();
}

// ------------------------------------------------------------
// 4) Longest Substring Without Repeating Characters
// Input: "abcabcbb"
// Output: 3
// ------------------------------------------------------------
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> lastPos;
    int left = 0;
    int best = 0;

    for (int right = 0; right < s.size(); ++right) {
        if (lastPos.count(s[right])) {
            left = max(left, lastPos[s[right]] + 1);
        }
        lastPos[s[right]] = right;
        best = max(best, right - left + 1);
    }
    return best;
}

// ------------------------------------------------------------
// 5) Merge Intervals
// Input: [[1,3],[2,6],[8,10],[15,18]]
// Output: [[1,6],[8,10],[15,18]]
// ------------------------------------------------------------
vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> merged;
    merged.push_back(intervals[0]);

    for (int i = 1; i < intervals.size(); ++i) {
        if (intervals[i][0] <= merged.back()[1]) {
            merged.back()[1] = max(merged.back()[1], intervals[i][1]);
        } else {
            merged.push_back(intervals[i]);
        }
    }
    return merged;
}

// ------------------------------------------------------------
// 6) Majority Element
// Input: [2,2,1,2,3,2,2]
// Output: 2
// ------------------------------------------------------------
int majorityElement(vector<int>& nums) {
    int candidate = 0;
    int count = 0;

    for (int x : nums) {
        if (count == 0) {
            candidate = x;
            count = 1;
        } else if (candidate == x) {
            count++;
        } else {
            count--;
        }
    }
    return candidate;
}

// ------------------------------------------------------------
// 7) Top K Frequent Elements
// Input: [1,1,1,2,2,3], k=2
// Output: [1,2]
// ------------------------------------------------------------
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int x : nums) ++freq[x];

    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> minHeap;
    for (auto& [value, count] : freq) {
        minHeap.push({count, value});
        if (minHeap.size() > k) minHeap.pop();
    }

    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().second);
        minHeap.pop();
    }
    sort(result.begin(), result.end(), [&](int a, int b) {
        return freq[a] > freq[b];
    });
    return result;
}

// ------------------------------------------------------------
// 8) Product of Array Except Self
// Input: [1,2,3,4]
// Output: [24,12,8,6]
// ------------------------------------------------------------
vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, 1);

    for (int i = 1; i < n; ++i) {
        result[i] = result[i - 1] * nums[i - 1];
    }

    int suffix = 1;
    for (int i = n - 1; i >= 0; --i) {
        result[i] *= suffix;
        suffix *= nums[i];
    }
    return result;
}

// ------------------------------------------------------------
// 9) Contains Duplicate
// Input: [1,2,3,1]
// Output: true
// ------------------------------------------------------------
bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> seen;
    for (int x : nums) {
        if (seen.count(x)) return true;
        seen.insert(x);
    }
    return false;
}

// ------------------------------------------------------------
// 10) Longest Consecutive Sequence
// Input: [100,4,200,1,3,2]
// Output: 4
// ------------------------------------------------------------
int longestConsecutive(vector<int>& nums) {
    unordered_set<int> s(nums.begin(), nums.end());
    int best = 0;

    for (int x : nums) {
        if (!s.count(x - 1)) {
            int current = 1;
            while (s.count(x + current)) ++current;
            best = max(best, current);
        }
    }
    return best;
}

// ------------------------------------------------------------
// 11) Reverse Linked List
// Input: 1->2->3->null
// Output: 3->2->1->null
// ------------------------------------------------------------
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;

    while (curr) {
        ListNode* nextNode = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextNode;
    }
    return prev;
}

// ------------------------------------------------------------
// 12) Merge Two Sorted Lists
// Input: 1->2->4 and 1->3->4
// Output: 1->1->2->3->4->4
// ------------------------------------------------------------
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* tail = &dummy;

    while (l1 && l2) {
        if (l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    tail->next = (l1 ? l1 : l2);
    return dummy.next;
}

// ------------------------------------------------------------
// 13) Detect Cycle in Linked List
// Input: 3->2->0->-4 and cycle back to 2
// Output: true
// ------------------------------------------------------------
bool hasCycle(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}

// ------------------------------------------------------------
// 14) Remove Nth Node From End of List
// Input: 1->2->3->4->5, n=2
// Output: 1->2->3->5
// ------------------------------------------------------------
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(0);
    dummy.next = head;
    ListNode* fast = &dummy;
    ListNode* slow = &dummy;

    for (int i = 0; i <= n; ++i) fast = fast->next;
    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }
    ListNode* remove = slow->next;
    slow->next = remove->next;
    delete remove;
    return dummy.next;
}

// ------------------------------------------------------------
// 15) Binary Tree Level Order Traversal
// Input: root = [3,9,20,null,null,15,7]
// Output: [[3],[9,20],[15,7]]
// ------------------------------------------------------------
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<vector<int>> levelOrder(TreeNode* root) {
    if (!root) return {};
    vector<vector<int>> result;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();
        vector<int> level;
        for (int i = 0; i < size; ++i) {
            TreeNode* node = q.front(); q.pop();
            level.push_back(node->val);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        result.push_back(level);
    }
    return result;
}

// ------------------------------------------------------------
// 16) Maximum Depth of Binary Tree
// Input: root = [3,9,20,null,null,15,7]
// Output: 3
// ------------------------------------------------------------
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

// ------------------------------------------------------------
// 17) Lowest Common Ancestor of a Binary Tree
// Input: root=[3,5,1,6,2,0,8,null,null,7,4], p=5, q=1
// Output: 3
// ------------------------------------------------------------
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root == p || root == q) return root;
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    if (left && right) return root;
    return left ? left : right;
}

// ------------------------------------------------------------
// 18) Validate Binary Search Tree
// Input: [2,1,3]
// Output: true
// ------------------------------------------------------------
bool isValidBST(TreeNode* root, TreeNode* minNode = nullptr, TreeNode* maxNode = nullptr) {
    if (!root) return true;
    if (minNode && root->val <= minNode->val) return false;
    if (maxNode && root->val >= maxNode->val) return false;
    return isValidBST(root->left, minNode, root) && isValidBST(root->right, root, maxNode);
}

// ------------------------------------------------------------
// 19) Binary Search
// Input: nums=[-1,0,3,5,9,12], target=9
// Output: 4
// ------------------------------------------------------------
int binarySearch(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// ------------------------------------------------------------
// 20) Search in Rotated Sorted Array
// Input: [4,5,6,7,0,1,2], target=0
// Output: 4
// ------------------------------------------------------------
int searchRotated(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        if (nums[left] <= nums[mid]) {
            if (nums[left] <= target && target < nums[mid]) right = mid - 1;
            else left = mid + 1;
        } else {
            if (nums[mid] < target && target <= nums[right]) left = mid + 1;
            else right = mid - 1;
        }
    }
    return -1;
}

// ------------------------------------------------------------
// 21) Jump Game
// Input: [2,3,1,1,4]
// Output: true
// ------------------------------------------------------------
bool canJump(vector<int>& nums) {
    int farthest = 0;
    for (int i = 0; i < nums.size(); ++i) {
        if (i > farthest) return false;
        farthest = max(farthest, i + nums[i]);
        if (farthest >= nums.size() - 1) return true;
    }
    return true;
}

// ------------------------------------------------------------
// 22) House Robber
// Input: [1,2,3,1]
// Output: 4
// ------------------------------------------------------------
int rob(vector<int>& nums) {
    if (nums.empty()) return 0;
    int prev2 = 0, prev1 = 0;
    for (int x : nums) {
        int curr = max(prev1, prev2 + x);
        prev2 = prev1;
        prev1 = curr;
    }
    return prev1;
}

// ------------------------------------------------------------
// 23) Coin Change
// Input: coins=[1,2,5], amount=11
// Output: 3
// ------------------------------------------------------------
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;

    for (int i = 1; i <= amount; ++i) {
        for (int coin : coins) {
            if (coin <= i && dp[i - coin] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

// ------------------------------------------------------------
// 24) Word Break
// Input: s = "leetcode", wordDict = ["leet","code"]
// Output: true
// ------------------------------------------------------------
bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> words(wordDict.begin(), wordDict.end());
    vector<bool> dp(s.size() + 1, false);
    dp[0] = true;

    for (int i = 1; i <= s.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (dp[j] && words.count(s.substr(j, i - j))) {
                dp[i] = true;
                break;
            }
        }
    }
    return dp[s.size()];
}

// ------------------------------------------------------------
// 25) Course Schedule
// Input: numCourses=2, [[1,0]]
// Output: true
// ------------------------------------------------------------
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    vector<int> indegree(numCourses, 0);

    for (auto& edge : prerequisites) {
        graph[edge[1]].push_back(edge[0]);
        indegree[edge[0]]++;
    }

    queue<int> q;
    for (int i = 0; i < numCourses; ++i) {
        if (indegree[i] == 0) q.push(i);
    }

    int processed = 0;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        processed++;
        for (int neighbor : graph[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0) q.push(neighbor);
        }
    }
    return processed == numCourses;
}

// ------------------------------------------------------------
// 26) Number of Islands
// Input: [[1,1,0],[1,0,0],[0,0,1]]
// Output: 2
// ------------------------------------------------------------
int numIslands(vector<vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    int rows = grid.size(), cols = grid[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    int islands = 0;

    function<void(int,int)> dfs = [&](int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols) return;
        if (grid[r][c] == '0' || visited[r][c]) return;
        visited[r][c] = true;
        dfs(r + 1, c); dfs(r - 1, c);
        dfs(r, c + 1); dfs(r, c - 1);
    };

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == '1' && !visited[r][c]) {
                islands++;
                dfs(r, c);
            }
        }
    }
    return islands;
}

// ------------------------------------------------------------
// 27) Clone Graph
// Input: graph node 1 with neighbors 2 and 3
// Output: cloned graph with same structure
// ------------------------------------------------------------
class GraphNode {
public:
    int val;
    vector<GraphNode*> neighbors;
    GraphNode(int x) : val(x) {}
};

GraphNode* cloneGraph(GraphNode* node) {
    if (!node) return nullptr;
    unordered_map<GraphNode*, GraphNode*> mp;
    queue<GraphNode*> q;
    q.push(node);
    mp[node] = new GraphNode(node->val);

    while (!q.empty()) {
        GraphNode* curr = q.front(); q.pop();
        for (GraphNode* nei : curr->neighbors) {
            if (!mp.count(nei)) {
                mp[nei] = new GraphNode(nei->val);
                q.push(nei);
            }
            mp[curr]->neighbors.push_back(mp[nei]);
        }
    }
    return mp[node];
}

// ------------------------------------------------------------
// 28) Kth Largest Element in Array
// Input: [3,2,1,5,6,4], k=2
// Output: 5
// ------------------------------------------------------------
int findKthLargest(vector<int>& nums, int k) {
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int x : nums) {
        minHeap.push(x);
        if (minHeap.size() > k) minHeap.pop();
    }
    return minHeap.top();
}

// ------------------------------------------------------------
// 29) Merge K Sorted Lists
// Input: [[1,4,5],[1,3,4],[2,6]]
// Output: [1,1,2,3,4,4,5,6]
// ------------------------------------------------------------
ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<pair<int, ListNode*>, vector<pair<int, ListNode*>>, greater<pair<int, ListNode*>>> pq;
    for (ListNode* head : lists) {
        if (head) pq.push({head->val, head});
    }

    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (!pq.empty()) {
        auto [val, node] = pq.top(); pq.pop();
        tail->next = node;
        tail = tail->next;
        if (node->next) pq.push({node->next->val, node->next});
    }
    return dummy.next;
}

// ------------------------------------------------------------
// 30) Trapping Rain Water
// Input: [0,1,0,2,1,0,1,3,2,1,2,1]
// Output: 6
// ------------------------------------------------------------
int trapWater(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int leftMax = 0, rightMax = 0, water = 0;

    while (left < right) {
        if (height[left] <= height[right]) {
            if (height[left] >= leftMax) leftMax = height[left];
            else water += leftMax - height[left];
            left++;
        } else {
            if (height[right] >= rightMax) rightMax = height[right];
            else water += rightMax - height[right];
            right--;
        }
    }
    return water;
}

// ------------------------------------------------------------
// Demo Section
// ------------------------------------------------------------
#ifndef MICROSOFT_TOP_30_AS_LIBRARY
int main() {
    cout << "Microsoft Top 30 Interview Questions\n\n";

    vector<int> a = {2, 7, 11, 15};
    vector<int> sumAns = twoSum(a, 9);
    cout << "1) Two Sum: ";
    for (int x : sumAns) cout << x << " ";
    cout << "\n";

    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << "2) Max Profit: " << maxProfit(prices) << "\n";

    cout << "3) Valid Parentheses: " << isValid("([{}])") << "\n";

    cout << "4) Longest Unique Substring: " << lengthOfLongestSubstring("abcabcbb") << "\n";

    vector<vector<int>> ivals = {{1,3},{2,6},{8,10},{15,18}};
    vector<vector<int>> merged = mergeIntervals(ivals);
    cout << "5) Merged Intervals: ";
    for (auto v : merged) cout << "[" << v[0] << "," << v[1] << "] ";
    cout << "\n";

    vector<int> maj = {2,2,1,2,3,2,2};
    cout << "6) Majority Element: " << majorityElement(maj) << "\n";

    vector<int> top = {1,1,1,2,2,3};
    vector<int> topAns = topKFrequent(top, 2);
    cout << "7) Top K Frequent: ";
    for (int x : topAns) cout << x << " ";
    cout << "\n";

    vector<int> prod = {1,2,3,4};
    vector<int> prodAns = productExceptSelf(prod);
    cout << "8) Product Except Self: ";
    for (int x : prodAns) cout << x << " ";
    cout << "\n";

    vector<int> dup = {1,2,3,1};
    cout << "9) Contains Duplicate: " << containsDuplicate(dup) << "\n";

    vector<int> cons = {100,4,200,1,3,2};
    cout << "10) Longest Consecutive: " << longestConsecutive(cons) << "\n";

    cout << "11) Reverse List example is already explained in the function section.\n";
    cout << "12) Merge Two Lists example is also explained in the function section.\n";
    cout << "13) Detect Cycle example is conceptually covered in the function.\n";
    cout << "14) Remove Nth Node example is conceptually covered in the function.\n";

    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    cout << "15) Level Order Traversal size: " << levelOrder(root).size() << "\n";
    cout << "16) Maximum Depth: " << maxDepth(root) << "\n";

    TreeNode* r2 = new TreeNode(2);
    r2->left = new TreeNode(1);
    r2->right = new TreeNode(3);
    cout << "18) Valid BST: " << isValidBST(r2) << "\n";

    vector<int> bs = {-1,0,3,5,9,12};
    cout << "19) Binary Search index: " << binarySearch(bs, 9) << "\n";

    vector<int> rot = {4,5,6,7,0,1,2};
    cout << "20) Rotated Search index: " << searchRotated(rot, 0) << "\n";

    vector<int> jump = {2,3,1,1,4};
    cout << "21) Jump Game: " << canJump(jump) << "\n";

    vector<int> robNums = {1,2,3,1};
    cout << "22) House Robber: " << rob(robNums) << "\n";

    vector<int> coins = {1,2,5};
    cout << "23) Coin Change: " << coinChange(coins, 11) << "\n";

    vector<string> dict = {"leet","code"};
    cout << "24) Word Break: " << wordBreak("leetcode", dict) << "\n";

    vector<vector<int>> pre = {{1,0}, {2,1}};
    cout << "25) Course Schedule: " << canFinish(3, pre) << "\n";

    vector<vector<char>> grid = {
        {'1','1','0'},
        {'1','0','0'},
        {'0','0','1'}
    };
    cout << "26) Number of Islands: " << numIslands(grid) << "\n";

    vector<int> kth = {3,2,1,5,6,4};
    cout << "28) Kth Largest: " << findKthLargest(kth, 2) << "\n";

    vector<int> water = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << "30) Trapped Rain Water: " << trapWater(water) << "\n";

    cout << "\nPractice order: Arrays -> Strings -> Linked Lists -> Trees -> Binary Search -> Greedy -> DP -> Graphs -> Heaps.\n";
    return 0;
}
#endif
