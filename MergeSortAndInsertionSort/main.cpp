/* Anton Amstadt
* Insertion sort is efficient for very small containers. do not use for large containers
* has O(n^2)
*/


#include <iostream>
#include <vector>

using namespace std;

void insertionSort(vector<int>&);
void mergeSort(vector<int>&, int, int);
void merge(vector<int>&, int, int, int);

int main() {
	vector<int> numbers{3, 1, 2, 432, 524, 523, 623, 42, 4332, 5, 2, 453, 43, 4673, 83, 7823, 635, 5, 4356, 7};
	//insertionSort(numbers);
	mergeSort(numbers, 0, numbers.size() - 1);
	for (auto a : numbers)
		cout << a << " ";
	cout << endl;
	
}

void insertionSort(vector<int>& v) {
	//only j = 1
	for (int key, i, j = 1; j < v.size(); j++) {
		key = v[j];
		i = j - 1; 
		while (i >= 0 && v[i] > key) {
			v[i + 1] = v[i];
			i--;
		}
		v[i + 1] = key;
	}
}

// call mergeSort with p = 0 and r = v.size() - 1
void mergeSort(vector<int>& v, int p, int r) {
	if (p < r) {
		int q = (p + r) / 2;
		mergeSort(v, p, q);
		mergeSort(v, q + 1, r);
		merge(v, p, q, r);
	}
}

// merge is the combination portion of the mergeSort algorithm
void merge(vector<int>& v, int p, int q, int r) {
	vector<int> left;
	vector<int> right;
	for (int i = p; i <= q; i++)
		left.push_back(v[i]);
	for (int i = q+1; i <= r; i++)
		right.push_back(v[i]);

	int i = p;
	int j = 0;
	int k = 0;

	while(j < left.size() && k < right.size()){
		if (left[j] < right[k])
			v[i++] = left[j++];
		else 
			v[i++] = right[k++];
	}

	while (j < left.size())
		v[i++] = left[j++];

	while (k < right.size())
		v[i++] = right[k++];
}