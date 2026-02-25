// Time:  O(n)
// Space: O(1)

// dp
class Solution {
public:
    long long rob(vector<int>& nums, vector<int>& colors) {
        vector<int64_t> dp(2);
        for (int i = 0; i < size(nums); ++i) {
            dp[i % 2] = (i - 1 >= 0 && colors[i - 1] == colors[i]) ? max(dp[((i - 2) % 2 + 2) % 2] + nums[i], dp[((i - 1) % 2 + 2) % 2]) : dp[((i - 1) % 2 + 2) % 2] + nums[i];
        }
        return dp[(size(nums) - 1) % 2];
    }
};

// Time:  O(n)
// Space: O(1)
// dp
class Solution2 {
public:
    long long rob(vector<int>& nums, vector<int>& colors) {
        vector<int64_t> dp(2);
        for (int i = 0; i < size(nums); ++i) {
            tie(dp[0], dp[1]) = pair(max(dp[0], dp[1]), ((i - 1 >= 0 && colors[i - 1] == colors[i]) ? dp[0] : max(dp[0], dp[1])) + nums[i]);
        }
        return max(dp[0], dp[1]);
    }
};
