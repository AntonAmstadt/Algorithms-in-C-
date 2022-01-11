#include <iostream>
#include <vector>
#include <climits> //for INT_MIN 

using namespace std;

// left and right bound the indexes of the max subarray and sum is the total of the max subarray
struct arrValues {
	int left;
	int right;
	int sum;
};

// has O(n)
arrValues kadanesAlgo(const vector<int>&);

// has O(nlogn)
arrValues findMaxSubarray(const vector<int>&, int, int);
arrValues findMaxCrossingSubarray(const vector<int>&, int, int, int);


//test function for the algorithms
int main() {
	vector<int> nums{ -1, 23, -43, 34, 64, -23, 54, -70, 30, 1, -42, 12, -90 };

	arrValues result = findMaxSubarray(nums, 0, nums.size() - 1);
	cout << result.left << ' ' << result.right << ' ' << result.sum << endl;

	arrValues result2 = kadanesAlgo(nums);
	cout << result2.left << ' ' << result2.right << ' ' << result2.sum << endl;

}

// finds the max subarray in O(n), will return arrValues{0, 0, 0} for empty vector
arrValues kadanesAlgo(const vector<int>& v) {
	int best_sum = 0;
	int best_start = 0;
	int best_end = 0;
	int current_sum = 0;
	int current_start = 0;

	for (int i = 0; i < v.size(); i++) {
		if (current_sum <= 0) {
			current_start = i;
			current_sum = v[i];
		}
		else
			current_sum += v[i];

		if (current_sum > best_sum) {
			best_sum = current_sum;
			best_start = current_start;
			best_end = i;
		}
	}

	return arrValues{ best_start, best_end, best_sum };
}

// a functin used by findMaxSubarrary to find the max subarray between partitioned arrays
arrValues findMaxCrossingSubarray(const vector<int>& v, int low, int mid, int high) {
	// maxLeft and maxRight are indexes in the vector, -1 is invalid but will be changed
	int maxLeft = -1;
	int maxRight = -1;
	int leftSum = INT_MIN;
	int sum = 0;
	for (int i = mid; i >= low; i--) {
		sum += v[i];
		if (sum > leftSum) {
			leftSum = sum;
			maxLeft = i;
		}
	}
	int rightSum = INT_MIN;
	sum = 0;
	for (int i = mid + 1; i <= high; i++) {
		sum += v[i];
		if (sum > rightSum) {
			rightSum = sum;
			maxRight = i;
		}
	}

	return arrValues{ maxLeft, maxRight, leftSum + rightSum };
}

// finds the max subarray from index low to index high
arrValues findMaxSubarray(const vector<int>& v, int low, int high) {
	if (high == low) {
		return arrValues{ low, high, v[low] };
	}
	else {
		int mid = (low + high) / 2;
		arrValues left = findMaxSubarray(v, low, mid);
		arrValues right = findMaxSubarray(v, mid + 1, high);
		arrValues cross = findMaxCrossingSubarray(v, low, mid, high);
		if (left.sum >= right.sum && left.sum >= cross.sum)
			return left;
		else if (right.sum >= left.sum && right.sum >= cross.sum)
			return right;
		else
			return cross;
	}
}