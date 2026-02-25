// Time:  O(n * k)
// Space: O(n * k)

// freq table
class Solution {
public:
    int prefixConnected(vector<string>& words, int k) {
        unordered_map<string, int> cnt;
        for (const auto& w : words) {
            if (size(w) < k) {
                continue;
            }
            ++cnt[w.substr(0, k)];
        }
        int result = 0;
        for (const auto& [_, v] : cnt) {
            if (v >= 2) {
                ++result;
            }
        }
        return result;
    }
};
