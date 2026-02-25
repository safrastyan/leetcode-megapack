// Time:  O(n + 26)
// Space: O(26)

// hash table
const auto& init = []() {
    static const vector<string> KEYBOARD = {"qwertyuiop", "asdfghjkl", "zxcvbnm"};
    vector<pair<int, int>> lookup(26);
    for (int i = 0; i < size(KEYBOARD); ++i) {
        for (int j = 0; j < size(KEYBOARD[i]); ++j) {
            lookup[KEYBOARD[i][j] - 'a'] = {i, j};
        }
    }
    return lookup;
};

const auto& LOOKUP = init();
class Solution {
public:
    int totalDistance(string s) {
        int result = 0;
        pair<int, int> prev = LOOKUP[0];
        for (const auto& x : s) {
            auto curr = LOOKUP[x - 'a'];
            result += abs(curr.first - prev.first) + abs(curr.second - prev.second);
            prev = curr;
        }
        return result;
    }
};
