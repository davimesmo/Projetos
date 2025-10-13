#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <cmath>
#include <climits>
#include <numeric>
#include <functional>
#include <cstring>
#include <cassert>
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res;
        int complemento = 0;
        for(int i =0; i < nums.size(); i++){
            complemento = nums[i] - target;
            if(complemento <= 0){
                for(int k = i+1; k < nums.size(); k++){
                    if(nums[k] + complemento == 0){
                        res.push_back(i);
                        res.push_back(k);
                    }
            }
            }
            
        }
    return res;
    }
};