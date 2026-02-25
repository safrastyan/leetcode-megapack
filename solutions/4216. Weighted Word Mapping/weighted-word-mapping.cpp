// Time:  O(n * l)
// Space: O(1)

// string
class Solution {
public:
    string mapWordWeights(vector<string>& words, vector<int>& weights) {
        string result;
        result.reserve(size(words));
        for (const auto& w: words) {
            int i = 0;
            for (const auto& x : w) {
                i = (i + weights[x - 'a']) % 26;
            }
            result.push_back('z' - i);
        }
        return result;
    }
};
