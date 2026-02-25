// Time:  O(nlogr), r = max(max(nums), 1)
// Space: O(n)

// two pointers, mono deque, bitmasks, prefix sum, hash table
class Solution {
public:
    int maxXor(vector<int>& nums, int k) {
        vector<int> lookup(size(nums), -1);
        deque<int> max_dq, min_dq;
        for (int right = 0, left = 0; right < size(nums); ++right) {
            while (!empty(max_dq) && nums[max_dq.back()] <= nums[right]) {
                max_dq.pop_back();
            }
            max_dq.emplace_back(right);
            while (!empty(min_dq) && nums[min_dq.back()] >= nums[right]) {
                min_dq.pop_back();
            }
            min_dq.emplace_back(right);
            while (nums[max_dq[0]] - nums[min_dq[0]] > k) {
                if (!empty(max_dq) && max_dq[0] == left) {
                    max_dq.pop_front();
                }
                if (!empty(min_dq) && min_dq[0] == left) {
                    min_dq.pop_front();
                }
                ++left;
            }
            lookup[right] = left;
        }
        int result = 0;
        const uint32_t mx = max(ranges::max(nums), 1);
        for (int i = bit_width(mx) - 1; i >= 0; --i) {
            unordered_map<int, int> lookup2;
            lookup2[0] = 0;
            for (int right = 0, prefix = 0; right < size(nums); ++right) {
                prefix ^= nums[right] >> i;
                if (lookup2.count(((result >> i) | 1) ^ prefix) && lookup2[((result >> i) | 1) ^ prefix] >= lookup[right]) {
                    result |= 1 << i;
                    break;
                }
                lookup2[prefix] = right + 1;
            }
        }
        return result;
    }
};

// Time:  O(nlogr), r = max(max(nums), 1)
// Space: O(n + t)
// two pointers, mono deque, bitmasks, prefix sum, trie
class Solution2 {
private:
    class Trie {
    public:
        Trie(int bit_length)
         : bit_length_(bit_length)
         , nodes_() {
             new_node();
         }

        void add(int num, int diff) {
            int curr = 0;
            for (int i = bit_length_ - 1; i >= 0; --i) {
                const auto& x = (num >> i) & 1;
                if (nodes_[curr][x] == -1) {
                    nodes_[curr][x] = new_node();
                }
                curr = nodes_[curr][x];
                cnts_[curr] += diff;
            }
        }

        int query(int prefix) {
            int result = 0, curr = 0;
            for (int i = bit_length_ - 1; i >= 0 && curr != -1; --i) {
                const auto& x = (prefix >> i) & 1;
                if (nodes_[curr][x ^ 1] != -1 && cnts_[nodes_[curr][x ^ 1]]) {
                    result |= 1 << i;
                    curr = nodes_[curr][x ^ 1];
                } else {
                    curr = nodes_[curr][x];
                }
            }
            return result;
        }

    private:
        int new_node() {
            nodes_.push_back(array<int, 2>{-1, -1});
            cnts_.emplace_back(0);
            return size(nodes_) - 1;
        }

        const int bit_length_;
        vector<array<int, 2>> nodes_;
        vector<int> cnts_;
    };

public:
    int maxXor(vector<int>& nums, int k) {
        int result = 0;
        vector<int> prefix(size(nums) + 1);
        for (int i = 0; i < size(nums); ++i) {
            prefix[i + 1] = prefix[i] ^ nums[i];
        }
        const uint32_t mx = max(ranges::max(nums), 1);
        Trie trie(bit_width(mx));
        trie.add(prefix[0], +1);
        deque<int> max_dq, min_dq;
        for (int right = 0, left = 0; right < size(nums); ++right) {
            while (!empty(max_dq) && nums[max_dq.back()] <= nums[right]) {
                max_dq.pop_back();
            }
            max_dq.emplace_back(right);
            while (!empty(min_dq) && nums[min_dq.back()] >= nums[right]) {
                min_dq.pop_back();
            }
            min_dq.emplace_back(right);
            while (nums[max_dq[0]] - nums[min_dq[0]] > k) {
                trie.add(prefix[left], -1);
                if (!empty(max_dq) && max_dq[0] == left) {
                    max_dq.pop_front();
                }
                if (!empty(min_dq) && min_dq[0] == left) {
                    min_dq.pop_front();
                }
                ++left;
            }
            result = max(result, trie.query(prefix[right + 1]));
            trie.add(prefix[right + 1], +1);
        }
        return result;
    }
};
