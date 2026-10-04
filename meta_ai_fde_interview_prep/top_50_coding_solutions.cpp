#include <bits/stdc++.h>
using namespace std;

/*
    High-frequency coding workbook for Meta and AI/FDE interviews.
    This file reuses the existing Microsoft Top 50 implementations for
    shared fundamentals, then adds representative AI/FDE-friendly patterns.
    Use coding_question_bank.md for the complete question checklist.
*/

#define MICROSOFT_TOP_50_AS_LIBRARY
#define MICROSOFT_TOP_30_AS_LIBRARY
#include "../microsoft_top_50_interview_questions.cpp"
#undef MICROSOFT_TOP_30_AS_LIBRARY
#undef MICROSOFT_TOP_50_AS_LIBRARY

// 1) Subarray Sum Equals K
// Brute: O(n^2) prefix checks. Optimal: prefix-sum frequency map, O(n) time/O(n) space.
int subarraySumEqualsK(vector<int>& nums, int k) {
    unordered_map<int, int> frequency{{0, 1}};
    int prefix = 0, answer = 0;
    for (int value : nums) {
        prefix += value;
        if (frequency.count(prefix - k)) answer += frequency[prefix - k];
        ++frequency[prefix];
    }
    return answer;
}

// 2) Three Sum
// Brute: O(n^3). Better: hashing. Optimal standard solution: sort + two pointers, O(n^2).
vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    vector<vector<int>> result;
    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        int left = i + 1, right = static_cast<int>(nums.size()) - 1;
        while (left < right) {
            long long sum = 1LL * nums[i] + nums[left] + nums[right];
            if (sum == 0) {
                result.push_back({nums[i], nums[left], nums[right]});
                while (left < right && nums[left] == nums[left + 1]) ++left;
                while (left < right && nums[right] == nums[right - 1]) --right;
                ++left;
                --right;
            } else if (sum < 0) ++left;
            else --right;
        }
    }
    return result;
}

// 3) Sliding Window Maximum
// Brute: O(n*k). Optimal: monotonic deque, O(n) time/O(k) space.
vector<int> slidingWindowMaximum(vector<int>& nums, int k) {
    deque<int> window;
    vector<int> result;
    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
        while (!window.empty() && window.front() <= i - k) window.pop_front();
        while (!window.empty() && nums[window.back()] <= nums[i]) window.pop_back();
        window.push_back(i);
        if (i >= k - 1) result.push_back(nums[window.front()]);
    }
    return result;
}

// 4) Longest Repeating Character Replacement
// Brute: inspect every substring. Optimal: sliding window, O(n) time/O(1) alphabet space.
int characterReplacement(string s, int k) {
    array<int, 26> frequency{};
    int left = 0, mostFrequent = 0, answer = 0;
    for (int right = 0; right < static_cast<int>(s.size()); ++right) {
        mostFrequent = max(mostFrequent, ++frequency[s[right] - 'A']);
        while (right - left + 1 - mostFrequent > k) --frequency[s[left++] - 'A'];
        answer = max(answer, right - left + 1);
    }
    return answer;
}

// 5) Merge Intervals
// Brute: repeatedly compare intervals. Optimal: sort then merge, O(n log n).
vector<vector<int>> mergeInterviewIntervals(vector<vector<int>>& intervals) {
    if (intervals.empty()) return {};
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> result{intervals[0]};
    for (int i = 1; i < static_cast<int>(intervals.size()); ++i) {
        if (intervals[i][0] <= result.back()[1]) result.back()[1] = max(result.back()[1], intervals[i][1]);
        else result.push_back(intervals[i]);
    }
    return result;
}

// 6) Course Schedule II
// Brute: repeatedly scan dependencies. Optimal: Kahn topological sort, O(V+E).
vector<int> courseOrder(int courses, vector<vector<int>>& prerequisites) {
    vector<vector<int>> graph(courses);
    vector<int> indegree(courses);
    for (auto& edge : prerequisites) {
        graph[edge[1]].push_back(edge[0]);
        ++indegree[edge[0]];
    }
    queue<int> ready;
    for (int course = 0; course < courses; ++course) if (indegree[course] == 0) ready.push(course);
    vector<int> result;
    while (!ready.empty()) {
        int course = ready.front(); ready.pop();
        result.push_back(course);
        for (int next : graph[course]) if (--indegree[next] == 0) ready.push(next);
    }
    return result.size() == static_cast<size_t>(courses) ? result : vector<int>{};
}

// 7) Number of Connected Components using Union Find
// Brute: repeated DFS. Union Find: near O(E alpha(V)).
class DisjointSet {
    vector<int> parent, rankValue;

public:
    explicit DisjointSet(int size) : parent(size), rankValue(size, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int node) {
        return parent[node] == node ? node : parent[node] = find(parent[node]);
    }

    bool unite(int first, int second) {
        first = find(first);
        second = find(second);
        if (first == second) return false;
        if (rankValue[first] < rankValue[second]) swap(first, second);
        parent[second] = first;
        if (rankValue[first] == rankValue[second]) ++rankValue[first];
        return true;
    }
};

int countComponents(int n, vector<vector<int>>& edges) {
    DisjointSet sets(n);
    int components = n;
    for (auto& edge : edges) if (sets.unite(edge[0], edge[1])) --components;
    return components;
}

// 8) K Closest Points to Origin
// Sort: O(n log n). Max heap of size k: O(n log k).
vector<vector<int>> closestPoints(vector<vector<int>>& points, int k) {
    priority_queue<pair<long long, int>> farthest;
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

// 9) Time Based Key-Value Store
// Store sorted timestamps; get with upper_bound, O(log n).
class TimeMap {
    unordered_map<string, vector<pair<int, string>>> values;

public:
    void set(const string& key, const string& value, int timestamp) {
        values[key].push_back({timestamp, value});
    }

    string get(const string& key, int timestamp) {
        auto it = values.find(key);
        if (it == values.end()) return "";
        auto& history = it->second;
        auto position = upper_bound(history.begin(), history.end(), make_pair(timestamp, string("\xff")));
        return position == history.begin() ? "" : prev(position)->second;
    }
};

// 10) Token Bucket Rate Limiter sketch
// Amortized O(1). In production use a monotonic clock and atomic/shared state.
class TokenBucket {
    double capacity;
    double tokens;
    double refillPerSecond;
    chrono::steady_clock::time_point lastRefill;

public:
    TokenBucket(double capacity, double refillPerSecond)
        : capacity(capacity), tokens(capacity), refillPerSecond(refillPerSecond), lastRefill(chrono::steady_clock::now()) {}

    bool allow(double requested = 1.0) {
        auto now = chrono::steady_clock::now();
        double elapsed = chrono::duration<double>(now - lastRefill).count();
        tokens = min(capacity, tokens + elapsed * refillPerSecond);
        lastRefill = now;
        if (tokens < requested) return false;
        tokens -= requested;
        return true;
    }
};

int main() {
    cout << "Meta / AI Engineering / FDE coding workbook\n";
    vector<int> values = {1, 1, 1};
    cout << "Subarray sum equals 2: " << subarraySumEqualsK(values, 2) << "\n";
    vector<int> three = {-1, 0, 1, 2, -1, -4};
    cout << "Three-sum triplets: " << threeSum(three).size() << "\n";
    vector<int> window = {1, 3, -1, -3, 5, 3, 6, 7};
    cout << "Sliding-window results: " << slidingWindowMaximum(window, 3).size() << "\n";
    cout << "Character replacement: " << characterReplacement("AABABBA", 1) << "\n";
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {3, 4}};
    cout << "Connected components: " << countComponents(5, edges) << "\n";
    TimeMap timeMap;
    timeMap.set("feature", "v1", 1);
    timeMap.set("feature", "v2", 4);
    cout << "TimeMap at 3: " << timeMap.get("feature", 3) << "\n";
    return 0;
}
