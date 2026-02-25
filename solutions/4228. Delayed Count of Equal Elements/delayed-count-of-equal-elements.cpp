// Time:  O(n)
// Space: O(n)

// freq table
class Solution {
public:
    vector<int> delayedCount(vector<int>& nums, int k) {
        vector<int> result(size(nums));
        unordered_map<int, int> cnt;
        for (int i = size(nums) - 1 - k; i >= 0; --i) {
            result[i] = cnt[nums[i]];
            ++cnt[nums[i + k]];
        }
        return result;
    }
};
