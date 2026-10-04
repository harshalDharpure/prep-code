#include <bits/stdc++.h>
using namespace std;

/*
    Microsoft Interview Preparation in C++
    --------------------------------------
    This file contains the strongest interview patterns that are most likely to be
    asked in Microsoft-style coding rounds. It covers both the beginner-level and
    advanced patterns that separate good candidates from excellent ones.

    Each problem includes:
      - The problem statement
      - The key idea / algorithm
      - Time and space complexity
      - A working C++ solution
      - Simple examples with input/output

    How to use this file:
      1. Read the explanation first.
      2. Understand the pattern behind the solution.
      3. Try to solve it yourself before looking at code.
      4. Run the sample input/output examples to see the behavior.
      5. Explain the solution out loud as if you were in an interview.

    Highest-probability patterns for Microsoft interviews:
      - Hashing
      - Sliding window
      - Two pointers
      - Stack and queue
      - Trees and BST
      - Binary search
      - Greedy
      - Dynamic programming
      - Graphs and topological sort
      - Heaps and priority queues
      - Design problems
*/

// ------------------------------------------------------------
// 1) Two Sum
// Problem: Return indices of two numbers adding to a target.
// Explanation:
//   If a number x is in the array, then we only need to check whether
//   target - x has been seen before. Using a hash map lets us do this in O(1)
//   average time per lookup.
// Example:
//   Input: nums = [2, 7, 11, 15], target = 9
//   Output: [0, 1]
//   Reason: 2 + 7 = 9
// Time: O(n), Space: O(n)
// ------------------------------------------------------------
vector<int> twoSum(const vector<int>& nums, int target) {
    unordered_map<int, int> seen;
    for (int i = 0; i < nums.size(); ++i) {
        int needed = target - nums[i];
        if (seen.find(needed) != seen.end()) {
            return {seen[needed], i};
        }
        seen[nums[i]] = i;
    }
    return {};
}



// ------------------------------------------------------------
// 2) Best Time to Buy and Sell Stock
// Problem: Max profit with at most one transaction.
// Explanation:
//   The best time to buy is when the price is minimum so far.
//   The profit for each day is current price - minimum price seen until then.
// Example:
//   Input: prices = [7, 1, 5, 3, 6, 4]
//   Output: 5
//   Reason: Buy at 1 and sell at 6 => profit 5
// Time: O(n), Space: O(1)
// ------------------------------------------------------------
int maxProfit(const vector<int>& prices) {
    if (prices.empty()) return 0;

    int minPrice = prices[0];
    int bestProfit = 0;

    for (int price : prices) {
        minPrice = min(minPrice, price);
        bestProfit = max(bestProfit, price - minPrice);
    }

    return bestProfit;
}

// ------------------------------------------------------------
// 3) Valid Parentheses
// Problem: Check if the input string has balanced parentheses.
// Explanation:
//   Use a stack. Every opening bracket is pushed. When a closing bracket appears,
//   it must match the most recent opening bracket. This follows LIFO behavior.
// Example:
//   Input: s = "([{}])"
//   Output: true
//   Input: s = "[(])"
//   Output: false
// Time: O(n), Space: O(n)
// ------------------------------------------------------------
bool isValidParentheses(const string& s) {
    stack<char> st;
    unordered_map<char, char> pairs = {{')', '('}, {']', '['}, {'}', '{'}};

    for (char ch : s) {
        if (ch == '(' || ch == '[' || ch == '{') {
            st.push(ch);
        } else {
            if (st.empty() || st.top() != pairs[ch]) {
                return false;
            }
            st.pop();
        }
    }

    return st.empty();
}

// ------------------------------------------------------------
// 4) Merge Intervals
// Problem: Merge overlapping intervals.
// Explanation:
//   Sort intervals by their starting point. Then compare each interval with the
//   last merged interval. If they overlap, update the end value.
// Example:
//   Input: [[1,3], [2,6], [8,10], [15,18]]
//   Output: [[1,6], [8,10], [15,18]]
// Time: O(n log n), Space: O(n)
// ------------------------------------------------------------
vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};

    sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    });

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
// 5) Longest Substring Without Repeating Characters
// Problem: Find the longest substring with unique characters.
// Explanation:
//   Use sliding window. As we move the right pointer, if a character repeats,
//   move the left pointer forward so the window has unique characters again.
// Example:
//   Input: s = "abcabcbb"
//   Output: 3
//   Reason: "abc" is the longest unique substring
// Time: O(n), Space: O(n)
// ------------------------------------------------------------
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> lastIndex;
    int left = 0;
    int best = 0;

    for (int right = 0; right < s.size(); ++right) {
        if (lastIndex.count(s[right])) {
            left = max(left, lastIndex[s[right]] + 1);
        }
        lastIndex[s[right]] = right;
        best = max(best, right - left + 1);
    }

    return best;
}

// ------------------------------------------------------------
// 6) Reverse Linked List
// Problem: Reverse a singly linked list.
// Explanation:
//   Keep three pointers: previous, current, and next. Reconnect nodes one-by-one.
//   This is a classic pointer manipulation question in interviews.
// Example:
//   Input: 1 -> 2 -> 3 -> null
//   Output: 3 -> 2 -> 1 -> null
// Time: O(n), Space: O(1)
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
// 7) Binary Tree Inorder Traversal
// Problem: Print inorder traversal of a binary tree.
// Explanation:
//   In inorder traversal, we visit the left subtree, then root, then right subtree.
//   For BSTs, this prints values in sorted order.
// Example:
//   Tree:       1
//              / \
//             2   3
//            / \
//           4   5
//   Output: 4 2 5 1 3
// Time: O(n), Space: O(h) recursion stack or O(n) iterative stack
// ------------------------------------------------------------
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> st;
    TreeNode* curr = root;

    while (curr || !st.empty()) {
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }
        curr = st.top();
        st.pop();
        result.push_back(curr->val);
        curr = curr->right;
    }

    return result;
}

// ------------------------------------------------------------
// 8) Lowest Common Ancestor of a Binary Search Tree
// Problem: Find LCA of two nodes in a BST.
// Idea: Traverse root; if both nodes are on left, move left; if on right, move right.
// Time: O(h), Space: O(1)
// ------------------------------------------------------------
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root) return nullptr;

    if (p->val < root->val && q->val < root->val) {
        return lowestCommonAncestor(root->left, p, q);
    }
    if (p->val > root->val && q->val > root->val) {
        return lowestCommonAncestor(root->right, p, q);
    }
    return root;
}

// ------------------------------------------------------------
// 9) Top K Frequent Elements
// Problem: Return the k most frequent elements.
// Idea: Count frequencies, then use min-heap of size k.
// Time: O(n log k), Space: O(n)
// ------------------------------------------------------------
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for (int x : nums) {
        ++freq[x];
    }

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    for (auto& [value, count] : freq) {
        minHeap.push({count, value});
        if (minHeap.size() > k) {
            minHeap.pop();
        }
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
// 10) Trapping Rain Water
// Problem: Compute trapped water between bars.
// Idea: Two-pointer approach using leftMax and rightMax.
// Time: O(n), Space: O(1)
// ------------------------------------------------------------
int trapRainWater(vector<int>& height) {
    int left = 0;
    int right = height.size() - 1;
    int leftMax = 0;
    int rightMax = 0;
    int water = 0;

    while (left < right) {
        if (height[left] <= height[right]) {
            if (height[left] >= leftMax) {
                leftMax = height[left];
            } else {
                water += leftMax - height[left];
            }
            ++left;
        } else {
            if (height[right] >= rightMax) {
                rightMax = height[right];
            } else {
                water += rightMax - height[right];
            }
            --right;
        }
    }

    return water;
}

// ------------------------------------------------------------
// 11) House Robber (Dynamic Programming)
// Problem: Maximum money robbed without adjacent houses.
// Idea: DP: dp[i] = max(dp[i-1], dp[i-2] + nums[i])
// Time: O(n), Space: O(n) or O(1)
// ------------------------------------------------------------
int rob(vector<int>& nums) {
    if (nums.empty()) return 0;
    if (nums.size() == 1) return nums[0];

    int prev2 = 0;
    int prev1 = nums[0];

    for (int i = 1; i < nums.size(); ++i) {
        int current = max(prev1, prev2 + nums[i]);
        prev2 = prev1;
        prev1 = current;
    }

    return prev1;
}

// ------------------------------------------------------------
// 12) LRU Cache Design
// Problem: Least Recently Used cache with O(1) operations.
// Idea: Hash map + doubly linked list.
// Time: O(1) for get/put, Space: O(capacity)
// ------------------------------------------------------------
class LRUCache {
private:
    list<pair<int, int>> cache;
    unordered_map<int, list<pair<int, int>>::iterator> pos;
    int capacity;

public:
    LRUCache(int cap) : capacity(cap) {}

    int get(int key) {
        auto it = pos.find(key);
        if (it == pos.end()) return -1;

        cache.splice(cache.begin(), cache, it->second);
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = pos.find(key);
        if (it != pos.end()) {
            it->second->second = value;
            cache.splice(cache.begin(), cache, it->second);
            return;
        }

        if (cache.size() == capacity) {
            int lastKey = cache.back().first;
            pos.erase(lastKey);
            cache.pop_back();
        }

        cache.emplace_front(key, value);
        pos[key] = cache.begin();
    }
};

// ------------------------------------------------------------
// 13) String to Integer (atoi)
// Problem: Convert string to integer with overflow handling.
// Idea: Skip spaces, handle sign, accumulate with overflow checks.
// Time: O(n), Space: O(1)
// ------------------------------------------------------------
int myAtoi(string s) {
    int i = 0;
    while (i < s.size() && s[i] == ' ') ++i;

    int sign = 1;
    if (i < s.size() && (s[i] == '+' || s[i] == '-')) {
        if (s[i] == '-') sign = -1;
        ++i;
    }

    long long number = 0;
    while (i < s.size() && isdigit(s[i])) {
        number = number * 10 + (s[i] - '0');
        if (sign == 1 && number > INT_MAX) return INT_MAX;
        if (sign == -1 && number > 1LL * INT_MAX + 1) return INT_MIN;
        ++i;
    }

    return sign == 1 ? (int)number : -(int)number;
}

// ------------------------------------------------------------
// 14) Word Break
// Problem: Determine if a string can be segmented into valid words.
// Idea: DP over positions. If substring is in wordSet and previous state true -> reachable.
// Time: O(n * L), Space: O(n)
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
// 15) Find the Majority Element
// Problem: Return element appearing more than n/2 times.
// Idea: Boyer-Moore Voting Algorithm.
// Time: O(n), Space: O(1)
// ------------------------------------------------------------
int majorityElement(vector<int>& nums) {
    int candidate = 0;
    int count = 0;

    for (int x : nums) {
        if (count == 0) {
            candidate = x;
            count = 1;
        } else if (x == candidate) {
            ++count;
        } else {
            --count;
        }
    }

    return candidate;
}

// ------------------------------------------------------------
// 16) Maximum Subarray (Kadane's Algorithm)
// Problem: Find the maximum sum subarray.
// Explanation:
//   Kadane's algorithm keeps the best subarray ending at the current position.
//   If the current sum becomes negative, reset it to zero or start fresh.
// Example:
//   Input: [-2,1,-3,4,-1,2,1,-5,4]
//   Output: 6
//   Reason: [4,-1,2,1] = 6
// Time: O(n), Space: O(1)
// ------------------------------------------------------------
int maxSubarrayKadane(vector<int>& nums) {
    int current = nums[0];
    int best = nums[0];

    for (int i = 1; i < nums.size(); ++i) {
        current = max(nums[i], current + nums[i]);
        best = max(best, current);
    }

    return best;
}

// ------------------------------------------------------------
// 17) Binary Search
// Problem: Find target in a sorted array.
// Explanation:
//   Binary search cuts the search space in half each step.
//   It only works when the array is sorted.
// Example:
//   Input: nums = [-1,0,3,5,9,12], target = 9
//   Output: 4
// Time: O(log n), Space: O(1)
// ------------------------------------------------------------
int binarySearch(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] < target) left = mid + 1;
        else right = mid - 1;
    }

    return -1;
}

// ------------------------------------------------------------
// 18) Search in Rotated Sorted Array
// Problem: Find target in a rotated sorted array.
// Explanation:
//   Determine which half is sorted, then decide where target can be.
// Example:
//   Input: [4,5,6,7,0,1,2], target = 0
//   Output: 4
// Time: O(log n), Space: O(1)
// ------------------------------------------------------------
int searchRotatedSortedArray(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;

        if (nums[left] <= nums[mid]) {
            if (nums[left] <= target && target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            if (nums[mid] < target && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }

    return -1;
}

// ------------------------------------------------------------
// 19) Course Schedule (Topological Sort)
// Problem: Determine if it is possible to finish all courses.
// Explanation:
//   Build a graph of prerequisites and count incoming edges. If we can process
//   all courses with a queue, then ordering is possible.
// Example:
//   Input: numCourses = 2, prerequisites = [[1,0]]
//   Output: true
// Time: O(V + E), Space: O(V + E)
// ------------------------------------------------------------
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    vector<int> indegree(numCourses, 0);

    for (auto& edge : prerequisites) {
        int course = edge[0];
        int pre = edge[1];
        graph[pre].push_back(course);
        ++indegree[course];
    }

    queue<int> q;
    for (int i = 0; i < numCourses; ++i) {
        if (indegree[i] == 0) q.push(i);
    }

    int processed = 0;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        ++processed;

        for (int nxt : graph[cur]) {
            --indegree[nxt];
            if (indegree[nxt] == 0) q.push(nxt);
        }
    }

    return processed == numCourses;
}

// ------------------------------------------------------------
// 20) Number of Islands
// Problem: Count connected land regions in a grid.
// Explanation:
//   Use DFS/BFS with a visited matrix. Explore all 4 directions from a land cell.
// Example:
//   Input: grid = [
//      [1,1,0,0],
//      [1,1,0,0],
//      [0,0,1,0],
//      [0,0,0,1]
//   ]
//   Output: 3
// Time: O(rows * cols), Space: O(rows * cols)
// ------------------------------------------------------------
int numIslands(vector<vector<char>>& grid) {
    if (grid.empty() || grid[0].empty()) return 0;

    int rows = grid.size();
    int cols = grid[0].size();
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    int islands = 0;

    function<void(int, int)> dfs = [&](int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols) return;
        if (grid[r][c] == '0' || visited[r][c]) return;

        visited[r][c] = true;
        dfs(r + 1, c);
        dfs(r - 1, c);
        dfs(r, c + 1);
        dfs(r, c - 1);
    };

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (grid[r][c] == '1' && !visited[r][c]) {
                ++islands;
                dfs(r, c);
            }
        }
    }

    return islands;
}

// ------------------------------------------------------------
// 21) Clone Graph
// Problem: Deep copy a graph.
// Explanation:
//   Use BFS and a map from original node to cloned node to avoid repeating work.
// Example:
//   Input: A graph with 1->2 and 1->3
//   Output: a structurally identical clone
// Time: O(V + E), Space: O(V)
// ------------------------------------------------------------
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

Node* cloneGraph(Node* node) {
    if (!node) return nullptr;

    unordered_map<Node*, Node*> visited;
    queue<Node*> q;
    q.push(node);
    visited[node] = new Node(node->val);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        for (Node* neighbor : current->neighbors) {
            if (!visited.count(neighbor)) {
                visited[neighbor] = new Node(neighbor->val);
                q.push(neighbor);
            }
            visited[current]->neighbors.push_back(visited[neighbor]);
        }
    }

    return visited[node];
}

// ------------------------------------------------------------
// 22) Merge K Sorted Lists
// Problem: Merge multiple sorted linked lists into one sorted list.
// Explanation:
//   Use a min-heap to always take the currently smallest node among lists.
// Example:
//   Input: [[1,4,5],[1,3,4],[2,6]]
//   Output: [1,1,2,3,4,4,5,6]
// Time: O(n log k), Space: O(k)
// ------------------------------------------------------------
ListNode* mergeKLists(vector<ListNode*>& lists) {
    priority_queue<pair<int, ListNode*>, vector<pair<int, ListNode*>>, greater<pair<int, ListNode*>>> pq;

    for (ListNode* head : lists) {
        if (head) pq.push({head->val, head});
    }

    ListNode* dummy = new ListNode(0);
    ListNode* tail = dummy;

    while (!pq.empty()) {
        auto [val, node] = pq.top();
        pq.pop();

        tail->next = node;
        tail = tail->next;

        if (node->next) {
            pq.push({node->next->val, node->next});
        }
    }

    return dummy->next;
}

// ------------------------------------------------------------
// 23) Jump Game
// Problem: Can you reach the last index?
// Explanation:
//   Maintain the farthest index you can reach. If you can never get past current index,
//   then the answer is false.
// Example:
//   Input: [2,3,1,1,4]
//   Output: true
// Time: O(n), Space: O(1)
// ------------------------------------------------------------
bool canJump(vector<int>& nums) {
    int maxReach = 0;

    for (int i = 0; i < nums.size(); ++i) {
        if (i > maxReach) return false;
        maxReach = max(maxReach, i + nums[i]);
        if (maxReach >= nums.size() - 1) return true;
    }

    return true;
}

// ------------------------------------------------------------
// Demo / Example Usage
// This section shows sample input and the expected output for each problem.
// It helps you understand how the solution behaves with real values.
// ------------------------------------------------------------
int main() {
    cout << "Microsoft Interview C++ Preparation\n\n";

    // 1. Two Sum
    // Input: nums = [2, 7, 11, 15], target = 9
    // Output: [0, 1]
    vector<int> nums1 = {2, 7, 11, 15};
    vector<int> ans1 = twoSum(nums1, 9);
    cout << "1) Two Sum: ";
    for (int x : ans1) cout << x << " ";
    cout << "\n";

    // 2. Best Time to Buy and Sell Stock
    // Input: prices = [7,1,5,3,6,4]
    // Output: 5
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << "2) Max Profit: " << maxProfit(prices) << "\n";

    // 3. Valid Parentheses
    // Input: "([{}])" -> true
    // Input: "[(])" -> false
    cout << "3) Valid Parentheses: " << isValidParentheses("([{}])") << "\n";

    // 4. Merge Intervals
    // Input: [[1,3],[2,6],[8,10],[15,18]]
    // Output: [[1,6],[8,10],[15,18]]
    vector<vector<int>> intervals = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    vector<vector<int>> merged = mergeIntervals(intervals);
    cout << "4) Merged Intervals:\n";
    for (auto& range : merged) {
        cout << "[" << range[0] << ", " << range[1] << "] ";
    }
    cout << "\n";

    // 5. Longest Substring Without Repeating Characters
    // Input: "abcabcbb"
    // Output: 3
    cout << "5) Longest Unique Substring: " << lengthOfLongestSubstring("abcabcbb") << "\n";

    // 6. Reverse List
    // Input: 1 -> 2 -> 3
    // Output: 3 -> 2 -> 1
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    ListNode* reversed = reverseList(head);
    cout << "6) Reversed Linked List: ";
    while (reversed) {
        cout << reversed->val << " ";
        reversed = reversed->next;
    }
    cout << "\n";

    // 7. Inorder Traversal
    // Input tree: 1 with left 2 and right 3; 2 has 4 and 5
    // Output: 4 2 5 1 3
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    vector<int> inorder = inorderTraversal(root);
    cout << "7) Inorder Traversal: ";
    for (int x : inorder) cout << x << " ";
    cout << "\n";

    // 8. LCA in BST
    // Input: root=1, p=2, q=3
    // Output: 1
    TreeNode* lca = lowestCommonAncestor(root, root->left, root->right);
    cout << "8) LCA: " << lca->val << "\n";

    // 9. Top K Frequent Elements
    // Input: nums = [1,1,1,2,2,3], k=2
    // Output: [1,2]
    vector<int> nums2 = {1, 1, 1, 2, 2, 3};
    vector<int> top = topKFrequent(nums2, 2);
    cout << "9) Top K Frequent: ";
    for (int x : top) cout << x << " ";
    cout << "\n";

    // 10. Trapping Rain Water
    // Input: [0,1,0,2,1,0,1,3,2,1,2,1]
    // Output: 6
    vector<int> water = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    cout << "10) Trapped Rain Water: " << trapRainWater(water) << "\n";

    // 11. House Robber
    // Input: [1,2,3,1]
    // Output: 4
    vector<int> money = {1, 2, 3, 1};
    cout << "11) Max Robbed Money: " << rob(money) << "\n";

    // 12. LRU Cache Example
    // Input: put(1,1), put(2,2), get(1), put(3,3), get(2)
    // Output: 1, -1
    LRUCache cache(2);
    cache.put(1, 1);
    cache.put(2, 2);
    cout << "12) LRU get(1): " << cache.get(1) << "\n";
    cache.put(3, 3);
    cout << "12) LRU get(2): " << cache.get(2) << "\n";

    // 13. myAtoi
    // Input: "-42"
    // Output: -42
    cout << "13) atoi(\"-42\"): " << myAtoi("-42") << "\n";

    // 14. Word Break
    // Input: s = "leetcode", wordDict = ["leet", "code"]
    // Output: true
    vector<string> dict = {"leet", "code"};
    cout << "14) Word Break: " << wordBreak("leetcode", dict) << "\n";

    // 15. Majority Element
    // Input: [2,2,1,2,3,2,2]
    // Output: 2
    vector<int> arr = {2, 2, 1, 2, 3, 2, 2};
    cout << "15) Majority Element: " << majorityElement(arr) << "\n";

    // 16. Kadane's Algorithm
    vector<int> sub = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "16) Maximum Subarray: " << maxSubarrayKadane(sub) << "\n";

    // 17. Binary Search
    vector<int> bs = {-1, 0, 3, 5, 9, 12};
    cout << "17) Binary Search (target 9): " << binarySearch(bs, 9) << "\n";

    // 18. Search in Rotated Sorted Array
    vector<int> rot = {4, 5, 6, 7, 0, 1, 2};
    cout << "18) Rotated Search (target 0): " << searchRotatedSortedArray(rot, 0) << "\n";

    // 19. Course Schedule
    vector<vector<int>> prerequisites = {{1, 0}, {2, 1}};
    cout << "19) Course Schedule: " << canFinish(3, prerequisites) << "\n";

    // 20. Number of Islands
    vector<vector<char>> islandGrid = {
        {'1', '1', '0', '0', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '1', '0', '0'},
        {'0', '0', '0', '1', '1'}
    };
    cout << "20) Number of Islands: " << numIslands(islandGrid) << "\n";

    // 21. Jump Game
    vector<int> jump = {2, 3, 1, 1, 4};
    cout << "21) Jump Game: " << canJump(jump) << "\n";

    cout << "\nStrong Microsoft interview patterns covered: hashing, stacks, trees, greedy, binary search, graphs, DP, heaps.\n";

    return 0;
}

/*
    Final Notes:
    ------------
    1. Microsoft interview questions often test patterns, not just syntax.
    2. Practice explaining the approach before writing code.
    3. Focus on complexity analysis and edge cases.
    4. Frequent topics: Arrays, Strings, Hashing, Stack, Tree, Graph, DP, Greedy, Bit Manipulation.

    Good preparation strategy:
      - Solve 2 problems daily
      - Write the explanation in plain English
      - Practice dry runs on sample inputs
      - Optimize from O(n^2) to O(n) when possible
*/
