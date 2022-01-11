#include <vector>
#include <random>
#include <iostream>

// this is the same function that can be used in quicksort.
// it used in randomized_select
// O(n)
int randomized_partition(std::vector<int>& v, int p, int r) {
	//randomize input vector (well enough) 
	std::random_device rd;
	std::mt19937 gen(rd());
	int size = v.size();
	for (int i = p; i < r; i++) {
		std::uniform_int_distribution<> dist(i, r);
		int index = dist(gen);
		int temp = v[index];
		v[index] = v[i];
		v[i] = temp;
	}

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

// RANDOMIZED-SELECT chapter 9
// returns the ith smallest element of the vector v in range [p, r]
// assumes i is in range: [1, v.size()] where smallest element: i = 1, largest element: i = v.size()
// O(n^2) but average case run time of n, and randomized so no input is the worst
int randomized_select(std::vector<int>& v, int p, int r, int i) {
	if (p == r)
		return v[p];
	int q = randomized_partition(v, p, r);
	int k = q - p + 1; 
	if (i == k)
		return v[q];
	else if (i < k)
		return randomized_select(v, p, q - 1, i);
	else
		return randomized_select(v, q + 1, r, i - k);
}

/* Selection in worst-case linear time using the select algorithm.
   select uses the modified partition function and insertion sort.
   * IN A REAL SOFTWARE PROJECT: use the stl function nth_element insted */
// partition modified to take an element as input to partition around


void insertionSort(std::vector<int>& v) {
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

//p is index to start range we are interested in, r ends that range [p, r]
// partition the vector around the element at index partAround
int modified_partition(std::vector<int>& v, int p, int r, int partAround) {
	int vSubR = v[r];
	bool foundPartAround = (vSubR == partAround)? true : false;
	int i = p - 1;
	for (int j = p; j < r; j++) {
		if (!foundPartAround && v[j] == partAround) {
			foundPartAround = true;
			v[j] = vSubR;
		}
		if (v[j] <= partAround) {
			i++;
			int temp = v[j];
			v[j] = v[i];
			v[i] = temp;
		}
	}
	if (foundPartAround) {
		v[r] = v[i + 1];
		v[i + 1] = partAround;
	}
	//else {
	//	std::cerr << "WARNING: PARTAROUND NOT FOUND\n";
	//}	
	return i + 1;
}

// has O(n) and worst-case time of n
int select(std::vector<int>& v, int p, int r, int ith) {
	if (p >= r) { 
		return v[(r+p)/2];
	}
		
	int remainder = (r - p + 1) % 5;
	std::vector<std::vector<int>> groups;
	if (r - p + 1 > 4) {
		int i = p;
		while (i <= r - remainder) {
			std::vector<int> g;
			int j = 0;
			while (i <= r - remainder && j < 5) {
				g.push_back(v[i]);
				i++;
				j++;
			}
			groups.push_back(g);
		}
	}
	if (remainder != 0) {
		std::vector<int> rem;
		for (int i = 0; i < remainder; i++)
			rem.push_back(v[r - remainder + 1 + i]);
		groups.push_back(rem);
	}

	//insertion sort each group
	for (std::vector<int>& x : groups)
		insertionSort(x);

	// store the median of each group
	std::vector<int> medians;
	if (remainder == 0) {
		for (const std::vector<int>& x : groups) {
			medians.push_back(x[x.size()/2]);
		}
			
	}
	else {
		int lastGroup = groups.size() - 1;
		int index = 0;
		while (index != lastGroup) {
			if(groups[index].size()%2== 0)
				medians.push_back(groups[index][(groups[index].size() / 2) - 1]);
			else
				medians.push_back(groups[index][groups[index].size() / 2]);
			index++;
		}
		if (remainder % 2 == 0)
			medians.push_back(groups[lastGroup][(remainder / 2) - 1]); //pick lower median
		else
			medians.push_back(groups[lastGroup][remainder / 2]);
	}

	//find the median of medians (lower median if even number vector size)
	int medOfmeds;
	if(medians.size() > 1 && medians.size() % 2 == 0)
		medOfmeds = select(medians, 0, medians.size() - 1, (medians.size() / 2) - 1);
	else
		medOfmeds = select(medians, 0, medians.size() - 1, medians.size() / 2);

	int q = modified_partition(v, p, r, medOfmeds);
	int k = q - p + 1; 
	if (ith == k) {
		return v[q];//return v[q];
	}
	else if (ith < k) {
		return select(v, p, q - 1, ith);
	}
	else {
		return select(v, q + 1, r, ith - k);
	}
}

int main(int argc, char* argv[]) {
	/*std::vector<int> bees{ 65,64,67,53,54,34,76,83,12,89,32 };
	int beesnum = modified_partition(bees, bees.size() - 4, bees.size() - 3, 83);
	for (int x : bees)
		std::cout << x << ' ';
	std::cout << '\n' << beesnum << '\n';*/


	/*std::vector<int> v{ 59,43,56,62,37,11,35,21,63,52,31,41,51,43,77,88,99,21 };*/

	//int blama = modified_partition(v, 4, 4, 62);
	//for (auto x : v)
	//	std::cout << x << ' ';
	//std::cout << '\n' << blama;
	//select(v, 0, v.size() - 1, 0);
	//std::vector<int> a;
	//for (int i = 10; i >= 0; i--)
	//	a.push_back(i);
	//randomized_partition(v, 0, v.size() - 1);
	/*std::cout << randomized_select(a, 0, a.size() - 1, 1) << '\n';
	std::cout << randomized_select(a, 0, a.size() - 1, 2) << '\n';
	std::cout << randomized_select(a, 0, a.size() - 1, 3) << '\n';
	std::cout << randomized_select(a, 0, a.size() - 1, 4) << '\n';
	std::cout << randomized_select(a, 0, a.size() - 1, 5) << '\n';
	std::cout << randomized_select(a, 0, a.size() - 1, 6) << '\n';*/
	//std::cout << randomized_select(v, 0, v.size() - 1, v.size() - 3) << '\n';
	/*std::vector<int> b{ 0,1 };
	std::cout << select(b, 0, b.size() - 1, 1) << '\n';
	for (int x : b)
		std::cout << x << ' ';*/
	
	//for (int i = 1; i <= v.size(); i++) {
	//	std::cout << "FINAL RESULT FOR i = " << i << ": " << select(v, 0, v.size() - 1, i) << '\n';
	//	std::cout << '\n';
	//}

	std::vector<int> lar;
	for (int i = 1; i <= 1003; i++)
		lar.push_back(i);
	//randomize the vector order
	randomized_partition(lar, 0, lar.size() - 1);

	int eleChoice = argc ? atoi(argv[1]) : 400; //assumes first command line argument (if any) is number in range [1,lar.size()]
	std::cout << select(lar, 0, lar.size() - 1, eleChoice);
} 