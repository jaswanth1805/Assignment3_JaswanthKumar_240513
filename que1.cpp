class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        
        int l1 = nums1.size();
        int l2 = nums2.size();
        
        vector<int> nextGreaterElement(l1, -1);

        for (int i = 0; i < l1; i++) {
            for (int j = 0; j < l2; j++) {
                if (nums1[i] == nums2[j]) {
                    for (int k = j + 1; k < l2; k++) { 
                        if (nums2[k] > nums2[j]) {
                            nextGreaterElement[i] = nums2[k];
                            break;
                        }
                    }
                    break; 
                }
            }
        }
        return nextGreaterElement;
    }
};
