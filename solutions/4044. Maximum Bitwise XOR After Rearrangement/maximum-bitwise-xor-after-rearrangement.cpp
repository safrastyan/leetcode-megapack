// Time:  O(n)
// Space: O(1)

// greedy
class Solution {
public:
    string maximumXor(string s, string t) {
        vector<int> cnt(2);
        cnt[0] = count(cbegin(t), cend(t), '0');
        cnt[1] = size(t) - cnt[0];
        string result;
        result.reserve(size(s));
        for (const auto& c : s) {
            const auto& x = c - '0';
            if (cnt[x ^ 1]) {
                --cnt[x ^ 1];
                result.push_back('1');
            } else {
                --cnt[x];
                result.push_back('0');
            }
        }
        return result;
    }
};
