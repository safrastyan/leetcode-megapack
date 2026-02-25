// Time:  O(n)
// Space: O(n)

// freq table
class Solution {
public:
    int firstUniqueFreq(vector<int>& nums) {
        unordered_map<int, int> cnt;
        for (const auto & x : nums) {
            ++cnt[x];
        }
        unordered_map<int, int> cnt2;
        for (const auto& [_, v] : cnt) {
            ++cnt2[v];
        }
        for (const auto& x : nums) {
            if (cnt2[cnt[x]] == 1) {
                return x;
            }
        }
        return -1;
    }
};
