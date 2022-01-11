#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

//counting sort doesn't exist in the c++ STL
//counting sort assumes the range of values in the vector are in the range [0, k]
// has theta(n + k)
//if k has O(n) (where n is the number of elements in the vector), then counting sort has O(n)
// counting sort gets worse as k increases, if k = n^2, then O(n^2)
// counting sort is stable, meaning that elements with the same value in the input with appear in the
// same order in the output
void countingSort(vector<int>& v, int k) {
	vector<int> b(v.size(), 0); // b has same number of elements as v and is where the answer is stored
	vector<int> c(k + 1, 0);

	for (int i = 0; i < v.size(); i++)
		c[v[i]]++;
	//c[i] now contains the number of elements = to i

	for (int i = 1; i <= k; i++)
		c[i] += c[i - 1];
	//c[i] now contains number of elements in v <= i

	for (int i = v.size() - 1; i >= 0; i--) {
		b[c[v[i]] - 1] = v[i];
		c[v[i]]--;
	}
	// replace v with b
	v.clear();
	for (int i = 0; i < b.size(); i++)
		v.push_back(b[i]);
}

// radix sort is only as fast as the stable sort used within it
// Here I will make an implementation of radix sort using counting
// sort to sort int vectors where the max value in the vector doesn't
// have too many digits. Radix sort doesn't sort in place.

struct stringAndDig {
	string s; // string representation of an integer
	char d; // will store integral number 0 to 9 (not '0' to '9')
};

// stable sort by the digit attribute. Used in my radix sort
void countingSort2(vector<stringAndDig>& v) {
	int k = 9; // 9 is max digit
	vector<stringAndDig> b;
	for (int i = 0; i < v.size(); i++)
		b.push_back({ "", 0 });
	vector<int> c(k + 1, 0);

	for (int i = 0; i < v.size(); i++)
		c[v[i].d]++;

	for (int i = 1; i <= k; i++)
		c[i] += c[i - 1];

	for (int i = v.size() - 1; i >= 0; i--) {
		b[c[v[i].d] - 1].d = v[i].d;
		b[c[v[i].d] - 1].s = v[i].s;
		c[v[i].d]--;
	}
	// replace v with b
	v.clear();
	for (int i = 0; i < b.size(); i++)
		v.push_back({ b[i].s, b[i].d });
}

// values in vector must be >= 0
void radixSort(vector<int>& v) {
	vector<stringAndDig> srep;
	int max = 0;
	for (int i = 0; i < v.size(); i++) {
		srep.push_back({ to_string(v[i]), 0 });
		if (v[i] > max)
			max = v[i];
	}

	string s = to_string(max);

	for (int i = 0; i < s.size(); i++) { // loop "max amount of digits in a single element" times
		// set d to current sorting digit
		for (int j = 0; j < srep.size(); j++) {
			if (srep[j].s.size() > i) { // check if enough digits in number, otherwise digit = 0
				// assign to d the digit value of the digit that is the ith to last digit (last digit i = 0)
				srep[j].d = srep[j].s[srep[j].s.size() - 1 - i] - '0';
			}
			else
				srep[j].d = 0;
		}
		//sort by the current digit
		countingSort2(srep);
	}

	//srep is sorted now, transfer the values over to v
	v.clear();
	for (int i = 0; i < srep.size(); i++)
		v.push_back(stoi(srep[i].s));
}


/* insertion sort used in bucket sort 
 credit to geeksforgeeks.org*/
void insertionSort(list<double>& li) {
	for (auto it = li.begin(); it != li.end(); it++) {
		auto const insert = upper_bound(li.begin(), it, *it);
		rotate(insert, it, next(it));
	}
}

/* bucket sort assumes the input has a uniform  distribution.
* has average case run time of O(n). 
* Assumes all numbers are in range [0,1)
*/
void bucketSort(vector<double>& v) {
	int size = v.size();
	vector<list<double>> b(size);
	for (int i = 0; i < size; i++)
		b[static_cast<int> (size * v[i])].push_back(v[i]); //only works b/c nums in range [0,1)
	for (int i = 0; i < size; i++)
		insertionSort(b[i]);
	v.clear();
	for (int i = 0; i < size; i++) {
		for (auto it = b[i].begin(); it != b[i].end(); it++)
			v.push_back(*it);
	}
}

int main() {
	/*counting sort test*/
	//vector<int> nums{ 3,6,1,0,6,8,9,6 };
	//int k = 0;
	////get the max of the vector
	//for (int i = 0; i < nums.size(); i++) {
	//	if (nums[i] > k)
	//		k = nums[i];
	//}

	//countingSort(nums, k);
	//for (auto x : nums)
	//	cout << x << ' ';

	/*int a = 43;
	string s = to_string(a);
	cout << s.size() << " " << s[1];
	int b = s[1] - '0';
	int c = a + b;
	cout << c;*/

	/* radix sort test */
	//vector<int> nums2{ 1234,6543,4,34,23452,64,2345,432,0,54,34,0,645,34328,654 };
	//radixSort(nums2);
	//for (auto x : nums2)
	//	cout << x << ' ';

	/* insertion sort test */
	//list<double> l{ 0.51, 0.2, 0.15, 0.25, 0.4, 0.6, 0.3, 0.11, 0.8, 0.1 };
	//
	//insertionSort(l);
	//for (auto x : l)
	//	cout << x << ' ';
	//cout << '\n';

	vector<double> v2{0.51, 0.2, 0.15, 0.25, 0.4, 0.6, 0.3, 0.11, 0.8, 0.1};
	bucketSort(v2);
	for (auto x : v2)
		cout << x << ' ';
	
	
}