/* goal: implement the heap procedures from the book 
 * and practice with equivalent STL funcitons
*/

#include <iostream>
#include <vector>
#include <algorithm> // make_heap and sort_heap
#include <queue> // priority_queue

using namespace std;

//functions translated from the book used for making max heaps and doing heapsort
void maxHeapify(vector<int>& v, int i, int end);
void buildMaxHeap(vector<int>& v);
void heapSort(vector<int>& v);

// related min heap functions
void minHeapify(vector<int>& v, int i, int end);
void buildMinHeap(vector<int>& v);

// max heap as priority queue functions
int heapMaximum(const vector<int>& v);
int heapExtractMax(vector<int>& v);
void heapIncreaseKey(vector<int>& v, int i, int key);
int parent(int i); // could be used for any heap, but placed here b/c used in heapIncreaseKey
void maxHeapInsert(vector<int>& v, int key);

// function to output small heaps
void heapOutput(const vector<int>& v);


int main() {
	vector<int> nums{ 1,2,3,4,5,6,7,8,9,10,31,40,20,30 };

	/*buildMinHeap(nums);
	heapOutput(nums);*/
	
	buildMaxHeap(nums);
	heapOutput(nums);

	/* does NOT need to already be heap for "my" heapSort */
	//heapSort(nums);
	//for (auto x : nums)
	//	cout << x << ' ';

	/* rather than using buildMaxHeap and heapSort, use STL make_heap and sort_heap (#include <algorithm>) */
	/*make_heap(nums.begin(), nums.end());*/
	//heapOutput(nums);

	/* must already be a heap for sort_heap */
	/*sort_heap(nums.begin(), nums.end());
	for (auto x : nums)
		cout << x << ' ';*/

	/* priority queue functions testing (start with max heap) */
	/*cout << heapExtractMax(nums) << endl;
	heapOutput(nums);
	cout << heapExtractMax(nums) << endl;
	cout << heapExtractMax(nums) << endl;
	cout << heapExtractMax(nums) << endl;
	cout << heapExtractMax(nums) << endl;
	heapOutput(nums);
	heapIncreaseKey(nums, 4, 7);
	heapOutput(nums);
	maxHeapInsert(nums, 4);
	heapOutput(nums);
	maxHeapInsert(nums, 0);
	heapOutput(nums);
	maxHeapInsert(nums, 3);
	heapOutput(nums);
	maxHeapInsert(nums, 5);
	heapOutput(nums);
	maxHeapInsert(nums, 4);
	heapOutput(nums);*/

	/* using the STL priority_queue for both max and min heaps. used opengenus.org and cpprefeence.com as references*/
	// initialize max heap with vector
	priority_queue<int> pq(nums.begin(), nums.end());
	/*while (!pq.empty()) {
		cout << pq.top() << ' ';
		pq.pop();
	}*/
	/* use push instead of maxHeapInsert for priority_queue*/
	pq.push(3);

	// min heap priority queue
	// has form: priority_queue<T, vector<T>, less<typename Container::value_type>>
	// if you only specify T, then it is max heap by default (uses less comparison) and uses a vector of type T
	priority_queue <int, vector<int>, greater<int>> minPQ;
	minPQ.push(12);
	minPQ.push(3);
	
}

// assumes that all elements except root are in the correct place in the max heap, assume size of vector is the size of the heap
// moves the incorrectly placed root to the proper position creating a valid max heap
// O(lgn)
// i is the index where the heap starts, end is the index where the heap ends
void maxHeapify(vector<int>& v, int i, int end) {
	int l = (2 * i) + 1; // index of left child
	int r = (2 * i) + 2; // index of right child
	int largest;
	if (l <= end && v[l] > v[i])
		largest = l;
	else
		largest = i;
	if (r <= end && v[r] > v[largest])
		largest = r;
	if (largest != i) {
		int temp = v[i];
		v[i] = v[largest];
		v[largest] = temp;
		maxHeapify(v, largest, end);
	}
}

//convert v into a max heap
// O(n)
void buildMaxHeap(vector<int>& v) {
	int size = v.size();
	for (int i = size / 2; i >= 0; i--) {
		maxHeapify(v, i, size - 1);
	}
}

// O(nlgn)
// a good implementation of quicksort is better than heapsort in the average case
void heapSort(vector<int>& v) {
	buildMaxHeap(v);
	int heapEnd = v.size() - 1;
	for (int i = heapEnd; i > 0; i--) {
		int temp = v[0];
		v[0] = v[i];
		v[i] = temp;
		heapEnd--;
		maxHeapify(v, 0, heapEnd);
	}
}

//corresponding min heap functions: minHeapify and buildMinHeap
void minHeapify(vector<int>& v, int i, int end) {
	int l = (2 * i) + 1; // index of left child
	int r = (2 * i) + 2; // index of right child
	int smallest;
	if (l <= end && v[l] < v[i])
		smallest = l;
	else
		smallest = i;
	if (r <= end && v[r] < v[smallest])
		smallest = r;
	if (smallest != i) {
		int temp = v[i];
		v[i] = v[smallest];
		v[smallest] = temp;
		maxHeapify(v, smallest, end);
	}
}

void buildMinHeap(vector<int>& v) {
	int size = v.size();
	for (int i = size / 2; i >= 0; i--) {
		minHeapify(v, i, size - 1);
	}
}

// personal function for a more intuitive output of a heap
void heapOutput(const vector<int>& v) {
	if (v.size() > 0) {
		int i = 2;
		int k = 1;
		cout << v[0] << endl;
		for (int j = 1; j < v.size(); j++) {
			cout << v[j] << ' ';
			if (k % i == 0) {
				i *= 2;
				cout << endl;
				k = 0;
			}
			k++;
		}
		if (k != 1)
			cout << endl;
	}
	else
		cout << "vector has a size of 0\n";
}

//priority queue functions, using a max heap as a priority queue
// the entire vector is assumed to be part of the priority queue
// the values inside the vector are the keys and normally there would be more data attached
// to these keys, but for simplicity there is nothing more than the keys in the vector
int heapMaximum(const vector<int>& v) {
	return v[0];
}

// remove and return max element of the priority queue
// O(lgn)
int heapExtractMax(vector<int>& v) {
	if (v.size() > 0) {
		int max = v[0];
		v[0] = v[v.size() - 1];
		v.pop_back();
		maxHeapify(v, 0, v.size() - 1);
		return max;
	}
	else
		cerr << "called heapExtractMax with an empty vector";
	return -1; //lazy error handling
}

// replace the key at element i with the parameter key
// O(lgn)
void heapIncreaseKey(vector<int>& v, int i, int key) {
	if (i >= v.size())
		cerr << "heapIncreaseKey error, parameter i > vector size";
	else if (key < v[i])
		cerr << "key less than v[i]";
	else {
		v[i] = key;
		// make it a heap again
		while (i > 0 && v[parent(i)] < v[i]) {
			int p = parent(i);
			int temp = v[i];
			v[i] = v[p];
			v[p] = temp;
			i = p;
		}
	}
}

// given a child index, return the index of the parent in the heap
// assumes a valid child index is passed
int parent(int i) {
	if (i % 2 == 0)
		return (i / 2) - 1;
	else
		return i / 2;
}

// insert a new key into the priority queue
void maxHeapInsert(vector<int>& v, int key) {
	v.push_back(0); // 0 used because value doesn't matter
	heapIncreaseKey(v, v.size() - 1, key); // set key to value you want and make the vector a heap again
}