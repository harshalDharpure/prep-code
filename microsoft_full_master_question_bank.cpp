#include <bits/stdc++.h>
using namespace std;

/*
    Microsoft Full Master Question Bank
    -----------------------------------
    This file contains the strongest Microsoft-style interview questions.
    Each question includes:
      - Problem idea
      - Brute-force approach
      - Better approach
      - Optimal approach
      - Time / space complexity
      - Example input/output
      - C++ implementation

    Purpose:
    - Strengthen pattern recognition
    - Improve interview communication
    - Prepare for most Microsoft coding-round questions
*/

// ------------------------------------------------------------
// 1) Two Sum
// Brute-force: O(n^2)
// Better: sort + two pointers O(n log n)
// Optimal: hash map O(n)
// ------------------------------------------------------------
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen;
    for (int i = 0; i < nums.size(); ++i) {
        int needed = target - nums[i];
        if (seen.count(needed)) return {seen[needed], i};
        seen[nums[i]] = i;
    }
    return {};
}



// ------------------------------------------------------------
// 2) Best Time to Buy and Sell Stock
// Brute-force: O(n^2)
// Optimal: O(n)
// ------------------------------------------------------------
int maxProfit(vector<int>& prices) {
    if (prices.empty()) return 0;
    int minPrice = prices[0];
    int best = 0;
    for (int price : prices) {
        minPrice = min(minPrice, price);
        best = max(best, price - minPrice);
    }
    return best;
}

// ------------------------------------------------------------
// 3) Valid Parentheses
// Brute-force: recursion / repeated string rebuild
// Optimal: stack O(n)
// ------------------------------------------------------------
bool isValidParentheses(string s) {
    stack<char> st;
    unordered_map<char, char> mp = {{')','('},{']','['},{'}','{'}};
    for (char ch : s) {
        if (ch == '(' || ch == '[' || ch == '{') st.push(ch);
        else {
            if (st.empty() || st.top() != mp[ch]) return false;
            st.pop();
        }
    }
    return st.empty();
}

// ------------------------------------------------------------
// 4) Longest Substring Without Repeating Characters
// Brute-force: O(n^3)
// Better: sliding window O(n)
// ------------------------------------------------------------
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> lastPos;
    int left = 0, best = 0;
    for (int right = 0; right < s.size(); ++right) {
        if (lastPos.count(s[right])) left = max(left, lastPos[s[right]] + 1);
        lastPos[s[right]] = right;
        best = max(best, right - left + 1);
    }
    return best;
}

// ------------------------------------------------------------
// 5) Merge Intervals
// Brute-force: O(n^2)
// Optimal: sort + merge O(n log n)
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
// Brute: O(n^2)
// Better: map O(n)
// Optimal: Boyer-Moore O(n), O(1)
// ------------------------------------------------------------
int majorityElement(vector<int>& nums) {
    int candidate = 0, count = 0;
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
// Brute: sort frequencies O(n log n)
// Optimal: min heap O(n log k)
// ------------------------------------------------------------
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int x : nums) ++freq[x];

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
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
// Brute: O(n^2)
// Optimal: prefix + suffix O(n), O(1) extra aside from result
// ------------------------------------------------------------
vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, 1);
    for (int i = 1; i < n; ++i) result[i] = result[i - 1] * nums[i - 1];
    int suffix = 1;
    for (int i = n - 1; i >= 0; --i) {
        result[i] *= suffix;
        suffix *= nums[i];
    }
    return result;
}

// ------------------------------------------------------------
// 9) Contains Duplicate
// Brute: O(n^2)
// Optimal: hash set O(n)
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
// Brute: O(n^2)
// Optimal: set + start point check O(n)
// ------------------------------------------------------------
int longestConsecutive(vector<int>& nums) {
    unordered_set<int> s(nums.begin(), nums.end());
    int best = 0;
    for (int x : nums) {
        if (!s.count(x - 1)) {
            int len = 1;
            while (s.count(x + len)) ++len;
            best = max(best, len);
        }
    }
    return best;
}

// ------------------------------------------------------------
// 11) Reverse Linked List
// Brute: recursion O(n)
// Optimal: iterative three pointers O(n)
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
        ListNode* nxt = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nxt;
    }
    return prev;
}

// ------------------------------------------------------------
// 12) Merge Two Sorted Lists
// Brute: concatenate then sort
// Optimal: merge while traversing O(n+m)
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
// Brute: visited set O(n)
// Optimal: Floyd cycle detection O(n)
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
// Brute: count length then remove O(n)
// Optimal: two pointers + dummy O(n)
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
// Brute: DFS recursion O(n)
// Optimal: BFS queue O(n)
// ------------------------------------------------------------
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<vector<int>> levelOrder(TreeNode* root) {
    if (!root) return {};
    vector<vector<int>> res;
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
        res.push_back(level);
    }
    return res;
}

// ------------------------------------------------------------
// 16) Maximum Depth of Binary Tree
// Optimal: DFS recursion O(n)
// ------------------------------------------------------------
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

// ------------------------------------------------------------
// 17) Lowest Common Ancestor of a Binary Tree
// Optimal: recursion O(n)
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
// Brute: inorder traversal with previous pointer O(n)
// Optimal: range-check recursion O(n)
// ------------------------------------------------------------
bool isValidBST(TreeNode* root, TreeNode* minNode = nullptr, TreeNode* maxNode = nullptr) {
    if (!root) return true;
    if (minNode && root->val <= minNode->val) return false;
    if (maxNode && root->val >= maxNode->val) return false;
    return isValidBST(root->left, minNode, root) && isValidBST(root->right, root, maxNode);
}

// ------------------------------------------------------------
// 19) Binary Search
// Brute: linear scan O(n)
// Optimal: binary search O(log n)
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
// Brute: O(n)
// Optimal: O(log n)
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
// Brute: DFS O(2^n)
// Optimal: greedy O(n)
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
// Brute: recursion with memoization O(n)
// Optimal: DP with rolling values O(n)
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
// Brute: recursion O(2^n)
// Optimal: DP O(amount * coins)
// ------------------------------------------------------------
int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;
    for (int i = 1; i <= amount; ++i) {
        for (int coin : coins) {
            if (coin <= i && dp[i - coin] != INT_MAX) dp[i] = min(dp[i], dp[i - coin] + 1);
        }
    }
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

// ------------------------------------------------------------
// 24) Word Break
// Brute: recursion with memoization or backtracking
// Optimal: DP O(n * L)
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
// Brute: DFS cycle detection O(V+E)
// Optimal: topological sort with queue O(V+E)
// ------------------------------------------------------------
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    vector<int> indegree(numCourses, 0);
    for (auto& edge : prerequisites) {
        graph[edge[1]].push_back(edge[0]);
        indegree[edge[0]]++;
    }
    queue<int> q;
    for (int i = 0; i < numCourses; ++i) if (indegree[i] == 0) q.push(i);
    int processed = 0;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        processed++;
        for (int nxt : graph[node]) {
            indegree[nxt]--;
            if (indegree[nxt] == 0) q.push(nxt);
        }
    }
    return processed == numCourses;
}

// ------------------------------------------------------------
// 26) Number of Islands
// Brute: repeated scanning O(rows*cols)^2
// Optimal: DFS/BFS O(rows*cols)
// ------------------------------------------------------------
int numIslands(vector<vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;
    int rows = grid.size(), cols = grid[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    int islands = 0;

    function<void(int, int)> dfs = [&](int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols) return;
        if (grid[r][c] == '0' || visited[r][c]) return;
        visited[r][c] = true;
        dfs(r + 1, c); dfs(r - 1, c); dfs(r, c + 1); dfs(r, c - 1);
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
// Optimal: BFS + hash map O(V+E)
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
        GraphNode* cur = q.front(); q.pop();
        for (GraphNode* nei : cur->neighbors) {
            if (!mp.count(nei)) {
                mp[nei] = new GraphNode(nei->val);
                q.push(nei);
            }
            mp[cur]->neighbors.push_back(mp[nei]);
        }
    }
    return mp[node];
}

// ------------------------------------------------------------
// 28) Kth Largest Element in Array
// Brute: sort O(n log n)
// Optimal: min heap O(n log k)
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
// Brute: merge pairwise O(k*n log k)
// Optimal: heap O(total log k)
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
// Brute: O(n^2)
// Optimal: two pointers O(n)
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
// Demo / Examples with Input and Output
// ------------------------------------------------------------
int main() {
    cout << "=== Microsoft Full Master Question Bank ===\n\n";

    vector<int> nums1 = {2, 7, 11, 15};
    vector<int> ans1 = twoSum(nums1, 9);
    cout << "1) Two Sum\nInput: nums = [2,7,11,15], target = 9\nOutput: ";
    for (int x : ans1) cout << x << " ";
    cout << "\n\n";

    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << "2) Best Time to Buy and Sell Stock\nInput: [7,1,5,3,6,4]\nOutput: " << maxProfit(prices) << "\n\n";

    cout << "3) Valid Parentheses\nInput: \"([{}])\"\nOutput: " << isValidParentheses("([{}])") << "\n\n";

    cout << "4) Longest Substring Without Repeating Characters\nInput: abcabcbb\nOutput: " << lengthOfLongestSubstring("abcabcbb") << "\n\n";

    vector<vector<int>> intervals = {{1,3},{2,6},{8,10},{15,18}};
    auto merged = mergeIntervals(intervals);
    cout << "5) Merge Intervals\nInput: [[1,3],[2,6],[8,10],[15,18]]\nOutput: ";
    for (auto v : merged) cout << "[" << v[0] << "," << v[1] << "] ";
    cout << "\n\n";

    vector<int> majority = {2,2,1,2,3,2,2};
    cout << "6) Majority Element\nInput: [2,2,1,2,3,2,2]\nOutput: " << majorityElement(majority) << "\n\n";

    vector<int> top = {1,1,1,2,2,3};
    auto topAns = topKFrequent(top, 2);
    cout << "7) Top K Frequent\nInput: [1,1,1,2,2,3], k=2\nOutput: ";
    for (int x : topAns) cout << x << " ";
    cout << "\n\n";

    vector<int> prod = {1,2,3,4};
    auto prodAns = productExceptSelf(prod);
    cout << "8) Product Except Self\nInput: [1,2,3,4]\nOutput: ";
    for (int x : prodAns) cout << x << " ";
    cout << "\n\n";

    vector<int> dup = {1,2,3,1};
    cout << "9) Contains Duplicate\nInput: [1,2,3,1]\nOutput: " << containsDuplicate(dup) << "\n\n";

    vector<int> cons = {100,4,200,1,3,2};
    cout << "10) Longest Consecutive Sequence\nInput: [100,4,200,1,3,2]\nOutput: " << longestConsecutive(cons) << "\n\n";

    cout << "11) Reverse Linked List\nInput: 1->2->3\nOutput: 3->2->1\n\n";
    cout << "12) Merge Two Sorted Lists\nInput: 1->2->4 and 1->3->4\nOutput: 1->1->2->3->4->4\n\n";
    cout << "13) Detect Cycle in Linked List\nInput: cycle exists\nOutput: true\n\n";
    cout << "14) Remove Nth Node From End of List\nInput: 1->2->3->4->5, n=2\nOutput: 1->2->3->5\n\n";

    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);
    cout << "15) Binary Tree Level Order Traversal\nInput: [3,9,20,null,null,15,7]\nOutput: [[3],[9,20],[15,7]]\n\n";

    cout << "16) Maximum Depth of Binary Tree\nInput: [3,9,20,null,null,15,7]\nOutput: 3\n\n";
    cout << "17) Lowest Common Ancestor\nInput: p=5, q=1\nOutput: 3\n\n";
    cout << "18) Validate BST\nInput: [2,1,3]\nOutput: true\n\n";

    vector<int> bs = {-1,0,3,5,9,12};
    cout << "19) Binary Search\nInput: [-1,0,3,5,9,12], target=9\nOutput: " << binarySearch(bs, 9) << "\n\n";

    vector<int> rot = {4,5,6,7,0,1,2};
    cout << "20) Search in Rotated Sorted Array\nInput: [4,5,6,7,0,1,2], target=0\nOutput: " << searchRotated(rot, 0) << "\n\n";

    vector<int> jump = {2,3,1,1,4};
    cout << "21) Jump Game\nInput: [2,3,1,1,4]\nOutput: " << canJump(jump) << "\n\n";

    vector<int> robVals = {1,2,3,1};
    cout << "22) House Robber\nInput: [1,2,3,1]\nOutput: " << rob(robVals) << "\n\n";

    vector<int> coins = {1,2,5};
    cout << "23) Coin Change\nInput: coins=[1,2,5], amount=11\nOutput: " << coinChange(coins, 11) << "\n\n";

    vector<string> dict = {"leet","code"};
    cout << "24) Word Break\nInput: s=\"leetcode\", dict=[\"leet\",\"code\"]\nOutput: " << wordBreak("leetcode", dict) << "\n\n";

    vector<vector<int>> pre = {{1,0},{2,1}};
    cout << "25) Course Schedule\nInput: numCourses=3, prerequisites=[[1,0],[2,1]]\nOutput: " << canFinish(3, pre) << "\n\n";

    vector<vector<char>> grid = {{'1','1','0'},{'1','0','0'},{'0','0','1'}};
    cout << "26) Number of Islands\nInput: grid = [[1,1,0],[1,0,0],[0,0,1]]\nOutput: " << numIslands(grid) << "\n\n";

    cout << "27) Clone Graph\nInput: graph with 1->2, 1->3\nOutput: structurally identical clone\n\n";

    vector<int> kth = {3,2,1,5,6,4};
    cout << "28) Kth Largest Element in Array\nInput: [3,2,1,5,6,4], k=2\nOutput: " << findKthLargest(kth, 2) << "\n\n";

    cout << "29) Merge K Sorted Lists\nInput: lists = [[1,4,5],[1,3,4],[2,6]]\nOutput: [1,1,2,3,4,4,5,6]\n\n";

    vector<int> water = {0,1,0,2,1,0,1,3,2,1,2,1};
    cout << "30) Trapping Rain Water\nInput: [0,1,0,2,1,0,1,3,2,1,2,1]\nOutput: " << trapWater(water) << "\n\n";

    cout << "This file covers the strongest Microsoft interview patterns: arrays, strings, hashing, stacks, linked lists, trees, BST, binary search, greedy, DP, graphs, and heaps.\n";
    return 0;
}
