// Time:  O(logn + 10)
// Space: O(10)

// freq table
vector<int> FACT(2, 1);
const auto& factorial = [](int n) {
    while (size(FACT) <= n) {
        FACT.emplace_back(FACT.back() * size(FACT));
    }
    return FACT[n];
};

class Solution {
public:
    bool isDigitorialPermutation(int n) {
        const auto& f = [](int x) {
            vector<int> cnt(10);
            for (; x; x /= 10) {
                ++cnt[x % 10];
            }
            return cnt;
        };

        int total = 0;
        for (int x = n; x; x /= 10) {
            total += factorial(x % 10);
        }
        return f(total) == f(n);
    }
};
