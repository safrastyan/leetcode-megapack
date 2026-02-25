// Time:  O(n + r)
// Space: O(r)

// freq table, counting sort
class Solution {
public:
    vector<int> toggleLightBulbs(vector<int>& bulbs) {
        const auto& mx = ranges::max(bulbs);
        vector<int> cnt(mx + 1);
        for (const auto& x : bulbs) {
            cnt[x] ^= 1;
        }
        vector<int> result;
        for (int i = 1; i <= mx; ++i) {
            if (cnt[i]) {
                result.emplace_back(i);
            }
        }
        return result;
    }
};

// Time:  O(nlogn)
// Space: O(n)
// freq table, sort
class Solution2 {
public:
    vector<int> toggleLightBulbs(vector<int>& bulbs) {
        unordered_map<int, int> cnt;
        for (const auto& x : bulbs) {
            cnt[x] ^= 1;
        }
        vector<int> result;
        for (const auto& [k, v] : cnt) {
            if (v) {
                result.emplace_back(k);
            }
        }
        ranges::sort(result);
        return result;
    }
};
