// Time:  O(n)
// Space: O(1)

// simulation
class Solution {
public:
    int scoreDifference(vector<int>& nums) {
        int result = 0;
        for (int i = 0, sign = 1; i < size(nums); ++i) {
            if (nums[i] % 2) {
                sign *= -1;
            }
            if (i % 6 == 5) {
                sign *= -1;
            }
            result += sign * nums[i];
        }
        return result;
    }
};
