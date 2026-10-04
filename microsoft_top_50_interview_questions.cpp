#include <bits/stdc++.h>
using namespace std;

/*
    Microsoft Top 50 Interview Questions in C++
    --------------------------------------------
    Questions 1-30 are reused from microsoft_top_30_interview_questions.cpp.
    Questions 31-50 below add the most valuable missing patterns from the
    larger Microsoft preparation list.

    Every added problem includes the optimal pattern, complexity, and a
    sample in main(). Practice explaining the brute-force idea first, then
    derive the optimized pattern.
*/

#define MICROSOFT_TOP_30_AS_LIBRARY
#include "microsoft_top_30_interview_questions.cpp"
#undef MICROSOFT_TOP_30_AS_LIBRARY

// 31) Valid Anagram
// Brute: sort both strings, O(n log n). Optimal: frequency table, O(n) time/O(1) space.
bool validAnagram(string s, string t) {
    if (s.size() != t.size()) return false;
    array<int, 256> count{};
    for (unsigned char ch : s) ++count[ch];
    for (unsigned char ch : t) if (--count[ch] < 0) return false;
    return true;
}

// 32) Group Anagrams
// Brute: compare every pair. Optimal: sorted word as a hash key, O(n*k log k).
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;
    for (string word : strs) {
        string key = word;
        sort(key.begin(), key.end());
        groups[key].push_back(word);
    }
    vector<vector<string>> result;
    for (auto& [key, words] : groups) result.push_back(words);
    return result;
}

// 33) Minimum Window Substring
// Brute: inspect every substring. Optimal: counting sliding window, O(n) time/O(1) space.
string minimumWindow(string s, string t) {
    vector<int> need(256, 0);
    for (unsigned char ch : t) ++need[ch];
    int missing = static_cast<int>(t.size());
    int left = 0, bestStart = 0, bestLength = INT_MAX;
    for (int right = 0; right < static_cast<int>(s.size()); ++right) {
        if (need[static_cast<unsigned char>(s[right])]-- > 0) --missing;
        while (missing == 0) {
            if (right - left + 1 < bestLength) {
                bestStart = left;
                bestLength = right - left + 1;
            }
            if (++need[static_cast<unsigned char>(s[left++])] > 0) ++missing;
        }
    }
    return bestLength == INT_MAX ? "" : s.substr(bestStart, bestLength);
}

// 34) Daily Temperatures
// Brute: scan right for each day, O(n^2). Optimal: monotonic decreasing stack, O(n).
vector<int> dailyTemperatures(vector<int>& temperatures) {
    vector<int> answer(temperatures.size());
    stack<int> waiting;
    for (int i = 0; i < static_cast<int>(temperatures.size()); ++i) {
        while (!waiting.empty() && temperatures[i] > temperatures[waiting.top()]) {
            int previous = waiting.top();
            waiting.pop();
            answer[previous] = i - previous;
        }
        waiting.push(i);
    }
    return answer;
}

// 35) Evaluate Reverse Polish Notation
// Brute: repeatedly resolve tokens. Optimal: one stack, O(n) time/O(n) space.
int evalRPN(vector<string>& tokens) {
    stack<long long> values;
    for (const string& token : tokens) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            long long right = values.top(); values.pop();
            long long left = values.top(); values.pop();
            if (token == "+") values.push(left + right);
            else if (token == "-") values.push(left - right);
            else if (token == "*") values.push(left * right);
            else values.push(left / right);
        } else {
            values.push(stoll(token));
        }
    }
    return static_cast<int>(values.top());
}

// 36) Reorder List
// Brute: repeatedly find the tail, O(n^2). Optimal: middle + reverse + merge, O(n) time/O(1) space.
void reorderList(ListNode* head) {
    if (!head || !head->next) return;
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* second = reverseList(slow->next);
    slow->next = nullptr;
    ListNode* first = head;
    while (second) {
        ListNode* firstNext = first->next;
        ListNode* secondNext = second->next;
        first->next = second;
        second->next = firstNext;
        first = firstNext;
        second = secondNext;
    }
}

// 37) Binary Tree Zigzag Level Order Traversal
// Brute: level traversal plus reversing copies. Optimal: BFS with direction, O(n).
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    if (!root) return {};
    vector<vector<int>> result;
    queue<TreeNode*> nodes;
    nodes.push(root);
    bool leftToRight = true;
    while (!nodes.empty()) {
        int size = static_cast<int>(nodes.size());
        vector<int> level(size);
        for (int i = 0; i < size; ++i) {
            TreeNode* node = nodes.front(); nodes.pop();
            int index = leftToRight ? i : size - 1 - i;
            level[index] = node->val;
            if (node->left) nodes.push(node->left);
            if (node->right) nodes.push(node->right);
        }
        result.push_back(level);
        leftToRight = !leftToRight;
    }
    return result;
}

// 38) Diameter of Binary Tree
// Brute: calculate height for every node, O(n^2). Optimal: one postorder DFS, O(n).
int diameterDfs(TreeNode* root, int& best) {
    if (!root) return 0;
    int leftHeight = diameterDfs(root->left, best);
    int rightHeight = diameterDfs(root->right, best);
    best = max(best, leftHeight + rightHeight);
    return 1 + max(leftHeight, rightHeight);
}

int diameterOfBinaryTree(TreeNode* root) {
    int best = 0;
    diameterDfs(root, best);
    return best;
}

// 39) Kth Smallest Element in a BST
// Brute: store and sort all values. Optimal: inorder traversal with a counter, O(h+k).
int kthSmallest(TreeNode* root, int k) {
    stack<TreeNode*> nodes;
    while (true) {
        while (root) {
            nodes.push(root);
            root = root->left;
        }
        root = nodes.top(); nodes.pop();
        if (--k == 0) return root->val;
        root = root->right;
    }
}

// 40) Find Minimum in Rotated Sorted Array
// Brute: linear scan, O(n). Optimal: binary search, O(log n).
int findMinRotated(vector<int>& nums) {
    int left = 0, right = static_cast<int>(nums.size()) - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[right]) left = mid + 1;
        else right = mid;
    }
    return nums[left];
}

// 41) Capacity to Ship Packages Within D Days
// Brute: try every capacity. Optimal: binary search the answer, O(n log sum).
int shipWithinDays(vector<int>& weights, int days) {
    int low = *max_element(weights.begin(), weights.end());
    int high = accumulate(weights.begin(), weights.end(), 0);
    auto works = [&](int capacity) {
        int usedDays = 1, current = 0;
        for (int weight : weights) {
            if (current + weight > capacity) {
                ++usedDays;
                current = 0;
            }
            current += weight;
        }
        return usedDays <= days;
    };
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (works(mid)) high = mid;
        else low = mid + 1;
    }
    return low;
}

// 42) Jump Game II
// Brute: recursive choices. Optimal: greedy range expansion, O(n) time/O(1) space.
int jumpMinimum(vector<int>& nums) {
    if (nums.size() <= 1) return 0;
    int jumps = 0, currentEnd = 0, farthest = 0;
    for (int i = 0; i < static_cast<int>(nums.size()) - 1; ++i) {
        farthest = max(farthest, i + nums[i]);
        if (i == currentEnd) {
            ++jumps;
            currentEnd = farthest;
        }
    }
    return jumps;
}

// 43) Unique Paths
// Brute: recursive grid choices. Optimal: one-dimensional DP, O(m*n) time/O(n) space.
int uniquePaths(int m, int n) {
    vector<int> dp(n, 1);
    for (int row = 1; row < m; ++row)
        for (int col = 1; col < n; ++col)
            dp[col] += dp[col - 1];
    return dp[n - 1];
}

// 44) Longest Increasing Subsequence
// Better: O(n^2) DP. Optimal: tails array with binary search, O(n log n).
int lengthOfLIS(vector<int>& nums) {
    vector<int> tails;
    for (int value : nums) {
        auto position = lower_bound(tails.begin(), tails.end(), value);
        if (position == tails.end()) tails.push_back(value);
        else *position = value;
    }
    return static_cast<int>(tails.size());
}

// 45) Rotting Oranges
// Brute: rescan the grid each minute. Optimal: multi-source BFS, O(rows*cols).
int orangesRotting(vector<vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size(), fresh = 0, minutes = 0;
    queue<pair<int, int>> rotten;
    for (int r = 0; r < rows; ++r) for (int c = 0; c < cols; ++c) {
        if (grid[r][c] == 2) rotten.push({r, c});
        else if (grid[r][c] == 1) ++fresh;
    }
    const int directions[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    while (!rotten.empty() && fresh) {
        int size = rotten.size();
        while (size--) {
            auto [r, c] = rotten.front(); rotten.pop();
            for (auto& direction : directions) {
                int nr = r + direction[0], nc = c + direction[1];
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 1) {
                    grid[nr][nc] = 2;
                    --fresh;
                    rotten.push({nr, nc});
                }
            }
        }
        ++minutes;
    }
    return fresh ? -1 : minutes;
}

// 46) Course Schedule II
// Brute: repeated dependency scanning. Optimal: Kahn topological sort, O(V+E).
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(numCourses);
    vector<int> indegree(numCourses);
    for (auto& edge : prerequisites) {
        graph[edge[1]].push_back(edge[0]);
        ++indegree[edge[0]];
    }
    queue<int> ready;
    for (int i = 0; i < numCourses; ++i) if (indegree[i] == 0) ready.push(i);
    vector<int> order;
    while (!ready.empty()) {
        int course = ready.front(); ready.pop();
        order.push_back(course);
        for (int next : graph[course]) if (--indegree[next] == 0) ready.push(next);
    }
    return order.size() == static_cast<size_t>(numCourses) ? order : vector<int>{};
}

// 47) K Closest Points to Origin
// Brute: sort all points, O(n log n). Optimal: max heap of size k, O(n log k).
vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
    using Entry = pair<long long, int>;
    priority_queue<Entry> farthest;
    for (int i = 0; i < static_cast<int>(points.size()); ++i) {
        long long distance = 1LL * points[i][0] * points[i][0] + 1LL * points[i][1] * points[i][1];
        farthest.push({distance, i});
        if (farthest.size() > k) farthest.pop();
    }
    vector<vector<int>> result;
    while (!farthest.empty()) {
        result.push_back(points[farthest.top().second]);
        farthest.pop();
    }
    return result;
}

// 48) Subsets
// Brute: enumerate bitmasks. Optimal backtracking, O(n*2^n) output-sensitive time.
vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> current;
    function<void(int)> build = [&](int index) {
        if (index == static_cast<int>(nums.size())) {
            result.push_back(current);
            return;
        }
        build(index + 1);
        current.push_back(nums[index]);
        build(index + 1);
        current.pop_back();
    };
    build(0);
    return result;
}

// 49) Permutations
// Brute: generate and deduplicate. Optimal swap backtracking, O(n*n!).
vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> result;
    function<void(int)> build = [&](int index) {
        if (index == static_cast<int>(nums.size())) {
            result.push_back(nums);
            return;
        }
        for (int i = index; i < static_cast<int>(nums.size()); ++i) {
            swap(nums[index], nums[i]);
            build(index + 1);
            swap(nums[index], nums[i]);
        }
    };
    build(0);
    return result;
}

// 50) Trie / Prefix Tree
// Brute: scan every stored word, O(number of words). Trie operations are O(word length).
class Trie {
    struct TrieNode {
        array<TrieNode*, 26> next{};
        bool terminal = false;
        TrieNode() { next.fill(nullptr); }
    };
    TrieNode* root = new TrieNode();

public:
    void insert(const string& word) {
        TrieNode* current = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (!current->next[index]) current->next[index] = new TrieNode();
            current = current->next[index];
        }
        current->terminal = true;
    }

    bool search(const string& word) const {
        TrieNode* node = findNode(word);
        return node && node->terminal;
    }

    bool startsWith(const string& prefix) const {
        return findNode(prefix) != nullptr;
    }

private:
    TrieNode* findNode(const string& word) const {
        TrieNode* current = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (!current->next[index]) return nullptr;
            current = current->next[index];
        }
        return current;
    }
};

// Design bonus: LRU Cache, O(1) get/put using list + hash map.
class LRUCache {
    int capacity;
    list<pair<int, int>> items;
    unordered_map<int, list<pair<int, int>>::iterator> locations;

public:
    explicit LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        auto it = locations.find(key);
        if (it == locations.end()) return -1;
        items.splice(items.begin(), items, it->second);
        return it->second->second;
    }

    void put(int key, int value) {
        if (locations.count(key)) {
            items.erase(locations[key]);
        } else if (items.size() == static_cast<size_t>(capacity)) {
            locations.erase(items.back().first);
            items.pop_back();
        }
        items.push_front({key, value});
        locations[key] = items.begin();
    }
};

#ifndef MICROSOFT_TOP_50_AS_LIBRARY
int main() {
    cout << "Microsoft Top 50 Interview Questions\n\n";
    cout << "Questions 1-30: loaded from microsoft_top_30_interview_questions.cpp\n";
    cout << "31) Valid Anagram: " << boolalpha << validAnagram("anagram", "nagaram") << "\n";
    vector<string> anagramWords = {"eat", "tea", "tan", "ate", "nat", "bat"};
    cout << "32) Group Anagrams: " << groupAnagrams(anagramWords).size() << " groups\n";
    cout << "33) Minimum Window: " << minimumWindow("ADOBECODEBANC", "ABC") << "\n";
    vector<int> temperatures = {73, 74, 75, 71, 69, 72, 76, 73};
    cout << "34) Daily Temperatures answer size: " << dailyTemperatures(temperatures).size() << "\n";
    vector<string> rpn = {"2", "1", "+", "3", "*"};
    cout << "35) Evaluate RPN: " << evalRPN(rpn) << "\n";
    cout << "37) Zigzag traversal levels: " << zigzagLevelOrder(nullptr).size() << " for an empty tree\n";
    TreeNode* tree = new TreeNode(1);
    tree->right = new TreeNode(2);
    tree->right->right = new TreeNode(3);
    cout << "38) Diameter of tree: " << diameterOfBinaryTree(tree) << "\n";
    vector<int> rotated = {4, 5, 6, 7, 0, 1, 2};
    cout << "40) Minimum in rotated array: " << findMinRotated(rotated) << "\n";
    vector<int> weights = {1, 2, 3, 1, 1};
    cout << "41) Shipping capacity: " << shipWithinDays(weights, 4) << "\n";
    vector<int> jumpValues = {2, 3, 1, 1, 4};
    cout << "42) Minimum jumps: " << jumpMinimum(jumpValues) << "\n";
    cout << "43) Unique paths (3x7): " << uniquePaths(3, 7) << "\n";
    vector<int> lisValues = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "44) LIS length: " << lengthOfLIS(lisValues) << "\n";
    vector<vector<int>> oranges = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    cout << "45) Rotting oranges minutes: " << orangesRotting(oranges) << "\n";
    vector<int> subsetValues = {1, 2, 3};
    cout << "48) Number of subsets: " << subsets(subsetValues).size() << "\n";
    cout << "49) Number of permutations: " << permute(subsetValues).size() << "\n";
    Trie trie;
    trie.insert("apple");
    cout << "50) Trie search apple: " << trie.search("apple") << "\n";
    LRUCache cache(2);
    cache.put(1, 10);
    cache.put(2, 20);
    cout << "Design bonus) LRU get(1): " << cache.get(1) << "\n";
    return 0;
}
#endif
