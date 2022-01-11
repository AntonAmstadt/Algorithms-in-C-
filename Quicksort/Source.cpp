/* goal translate the quicksort function from the book */

#include <iostream>  
#include <vector>
#include <random>

using namespace std;

// p and r bound the indices 
int partition(vector<int>& v, int p, int r) {
	int x = v[r];
	int i = p - 1;
	for (int j = p; j < r; j++) {
		if (v[j] <= x) {
			i++;
			int temp = v[j];
			v[j] = v[i];
			v[i] = temp;
		}
	}
	int t = v[r];
	v[r] = v[i + 1];
	v[i + 1] = t;
	return i + 1;
}


// to use: quicksort(myvector, 0, myvector.size() - 1);
// O(n^2) but expected run time of nlgn
void quicksort(vector<int>& v, int p, int r) {
	if (p < r) {
		int q = partition(v, p, r);
		quicksort(v, p, q - 1);
		quicksort(v, q + 1, r);
	}
}

int main() {
	vector<int> nums{ 5,4,7,3,8,2,9,7,9,10,1,3 };
	quicksort(nums, 0, nums.size() - 1);
	for (auto x : nums)
		cout << x << ' ';

}