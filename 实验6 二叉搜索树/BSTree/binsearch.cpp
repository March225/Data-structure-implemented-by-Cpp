#include "binsearch.h"

// ¶þ·ÖËÑË÷
int BinarySearch(vector<int>& nums, int target) {
	int l = 0, r = int(nums.size()) - 1;
	while (l <= r) {
		int m = (r + l) / 2;
		if (nums[m] == target)
			return m;
		else if (nums[m] < target)
			l = m + 1;
		else
			r = m - 1;
	}
	return -1;
}