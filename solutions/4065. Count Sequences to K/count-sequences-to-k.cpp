// Time:  O(3^(n/2))
// Space: O(3^(n/2))

// dp, meet in the middle
class Solution {
private:
    struct TupleHash {
        template <typename... T>
        std::size_t operator()(const std::tuple<T...>& t) const {
            return apply([](const auto&... args) {
                std::size_t seed = 0;
                ((seed ^= std::hash<std::decay_t<decltype(args)>>{}(args) +
                        0x9e3779b9 + (seed << 6) + (seed >> 2)), ...);
                return seed;
            }, t);
        }
    };

public:
    int countSequences(vector<int>& nums, long long k) {
        static const unordered_map<int, tuple<int, int, int>> LOOKUP = {
            {1, {0, 0, 0}},
            {2, {1, 0, 0}},
            {3, {0, 1, 0}},
            {4, {2, 0, 0}},
            {5, {0, 0, 1}},
            {6, {1, 1, 0}}
        };

        const auto& factors = [](int64_t x) {
            int cnt2 = 0;
            while (x % 2 == 0) {
                x /= 2;
                ++cnt2;
            }
            int cnt3 = 0;
            while (x % 3 == 0) {
                x /= 3;
                ++cnt3;
            }
            int cnt5 = 0;
            while (x % 5 == 0) {
                x /= 5;
                ++cnt5;
            }
            return x == 1 ? tuple(cnt2, cnt3, cnt5) : tuple(-1, -1, -1);
        };

        const auto& count = [](const auto& nums) {
            unordered_map<tuple<int, int, int>, int, TupleHash> dp;
            dp[{0, 0, 0}] = 1;
            for (const auto& x : nums) {
                unordered_map<tuple<int, int, int>, int, TupleHash> new_dp;
                const auto& [d2, d3, d5] = LOOKUP.at(x);
                for (const auto& [k, c] : dp) {
                    const auto& [c2, c3, c5] = k;
                    new_dp[{c2, c3, c5}] += c;
                    new_dp[{c2 + d2, c3 + d3, c5 + d5}] += c;
                    new_dp[{c2 - d2, c3 - d3, c5 - d5}] += c;
                }
                dp = move(new_dp);
            }
            return dp;
        };

        const auto& [c2, c3, c5] = factors(k);
        if (c2 == -1) {
            return 0;
        }
        auto left = count(vector<int>(cbegin(nums), cbegin(nums) + (size(nums) / 2)));
        auto right = count(vector<int>(cbegin(nums) + (size(nums) / 2), cend(nums)));
        int result = 0;
        for (const auto& [k, d] : left) {
            const auto& [d2, d3, d5] = k;
            result += d * right[{c2 - d2, c3 - d3, c5 - d5}];
        }
        return result;
    }
};

// Time:  O(3^n)
// Space: O(3^n)
// dp
class Solution2 {
private:
    struct TupleHash {
        template <typename... T>
        std::size_t operator()(const std::tuple<T...>& t) const {
            return apply([](const auto&... args) {
                std::size_t seed = 0;
                ((seed ^= std::hash<std::decay_t<decltype(args)>>{}(args) +
                        0x9e3779b9 + (seed << 6) + (seed >> 2)), ...);
                return seed;
            }, t);
        }
    };

public:
    int countSequences(vector<int>& nums, long long k) {
        static const unordered_map<int, tuple<int, int, int>> LOOKUP = {
            {1, {0, 0, 0}},
            {2, {1, 0, 0}},
            {3, {0, 1, 0}},
            {4, {2, 0, 0}},
            {5, {0, 0, 1}},
            {6, {1, 1, 0}}
        };

        const auto& factors = [](int64_t x) {
            int cnt2 = 0;
            while (x % 2 == 0) {
                x /= 2;
                ++cnt2;
            }
            int cnt3 = 0;
            while (x % 3 == 0) {
                x /= 3;
                ++cnt3;
            }
            int cnt5 = 0;
            while (x % 5 == 0) {
                x /= 5;
                ++cnt5;
            }
            return x == 1 ? tuple(cnt2, cnt3, cnt5) : tuple(-1, -1, -1);
        };

        const auto& count = [](const auto& nums) {
            unordered_map<tuple<int, int, int>, int, TupleHash> dp;
            dp[{0, 0, 0}] = 1;
            for (const auto& x : nums) {
                unordered_map<tuple<int, int, int>, int, TupleHash> new_dp;
                const auto& [d2, d3, d5] = LOOKUP.at(x);
                for (const auto& [k, c] : dp) {
                    const auto& [c2, c3, c5] = k;
                    new_dp[{c2, c3, c5}] += c;
                    new_dp[{c2 + d2, c3 + d3, c5 + d5}] += c;
                    new_dp[{c2 - d2, c3 - d3, c5 - d5}] += c;
                }
                dp = move(new_dp);
            }
            return dp;
        };

        const auto& [c2, c3, c5] = factors(k);
        if (c2 == -1) {
            return 0;
        }
        auto dp = count(nums);
        return dp[{c2, c3, c5}];
    }
};
