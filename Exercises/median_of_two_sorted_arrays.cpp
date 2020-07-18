#include <vector>

// O(m + n) [Linear time]
class Solution {
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        auto forward_itr1 = nums1.begin();
        auto forward_itr2 = nums2.begin();
        auto back_itr1 = nums1.rbegin();
        auto back_itr2 = nums2.rbegin();
        int num_count = nums1.size() + nums2.size();
        std::vector<int> arr(num_count);
        
        int i = 0, j = num_count - 1, count = 0;
        while (count < num_count) {
            if (forward_itr1 != nums1.end() && forward_itr2 != nums2.end()) {
                if (*forward_itr1 < *forward_itr2) {
                    arr[i] = *forward_itr1;
                    ++forward_itr1;
                } else {
                    arr[i] = *forward_itr2;
                    ++forward_itr2;
                }
                ++count;
                ++i;
            } else { 
                if (forward_itr2 == nums2.end()) {
                    arr[i] = *forward_itr1;
                    ++forward_itr1;
                } else if (forward_itr1 == nums1.end()) {
                    arr[i] = *forward_itr2;
                    ++forward_itr2;
                }
                ++count;
                ++i;
            }
            
            if (back_itr1 != nums1.rend() && back_itr2 != nums2.rend()) {
                if (*back_itr1 > *back_itr2 ) {
                    arr[j] = *back_itr1;
                    ++back_itr1;
                } else {
                    arr[j] = *back_itr2;
                    ++back_itr2;
                }
                ++count;
                --j;
            } else {
                if (back_itr2 == nums2.rend()) {
                    arr[j] = *back_itr1;
                    ++back_itr1;
                } else if (back_itr1 == nums1.rend()) {
                    arr[j] = *back_itr2;
                    ++back_itr2;
                }
                ++count;
                --j;
            }
        }
        
        if (num_count % 2 != 0) {
            return static_cast<double>(arr[(num_count / 2)]);
        } else {
            return (arr[num_count / 2] + arr[(num_count / 2) - 1]) / 2.0;
        }
    }
};