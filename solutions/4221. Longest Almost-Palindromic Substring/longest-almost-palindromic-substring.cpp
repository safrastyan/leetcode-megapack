// Time:  O(n^2)
// Space: O(1)

// two pointers
class Solution {
public:
    int almostPalindromic(string s) {
        const auto& expand = [&](int left, int right) {
            while (0 <= left && right < size(s) && s[left] == s[right]) {
                --left;
                ++right;
            }
            return pair(left, right);
        };

        int result = 0;
        for (int i = 0; i < 2 * size(s) - 1; ++i) {
            const auto& [left, right] = expand(i / 2, (i + 1) / 2);
            for (const auto& [left, right] : {pair(left - 1, right), pair(left, right + 1)}) {
                const auto& [l, r] = expand(left, right);
                result = max(result, min((r - l + 1) - 2, static_cast<int>(size(s))));
            }
        }
        return result;
    }
};
