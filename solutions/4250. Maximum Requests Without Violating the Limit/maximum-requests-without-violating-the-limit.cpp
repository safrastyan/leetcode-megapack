// Time:  O(nlogn)
// Space: O(n)

// hash table, sort, deque, sliding window
class Solution {
public:
    int maxRequests(vector<vector<int>>& requests, int k, int window) {
        unordered_map<int, vector<int>> lookup;
        for (const auto& r : requests) {
            lookup[r[0]].emplace_back(r[1]);
        }
        int result = size(requests);
        for (auto& [_, l] : lookup) {
            ranges::sort(l);
            deque<int> dq;
            for (const auto& x : l) {
                dq.emplace_back(x);
                if (size(dq) <= k) {
                    continue;
                }
                if (dq.back() - dq.front() > window) {
                    dq.pop_front();
                    continue;
                }
                dq.pop_back();
                --result;
            }
        }
        return result;
    }
};
