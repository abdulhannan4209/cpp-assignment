#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Function to solve the Two Sum problem
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen;  // store number -> index
    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        if (seen.find(complement) != seen.end()) {
            return {seen[complement], i};
        }
        seen[nums[i]] = i;
    }
    return {}; // not expected to happen, since one solution always exists
}

int main() {
    // Example 1
    vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    vector<int> result1 = twoSum(nums1, target1);
    cout << "Output: [" << result1[0] << "," << result1[1] << "]" << endl;

    // Example 2
    vector<int> nums2 = {3, 2, 4};
    int target2 = 6;
    vector<int> result2 = twoSum(nums2, target2);
    cout << "Output: [" << result2[0] << "," << result2[1] << "]" << endl;

    // Example 3
    vector<int> nums3 = {3, 3};
    int target3 = 6;
    vector<int> result3 = twoSum(nums3, target3);
    cout << "Output: [" << result3[0] << "," << result3[1] << "]" << endl;

    return 0;
}
