#include <vector>
#include <climits>
#include <iostream>

//NOT DYNAMIC PROGRAMMING
//price contains the prices for the lengths of rod, n is the length of the rod to be divided
//INEFFICIENT: b/c solves same problems repeatedly
int cut_rod(std::vector<int> price, int n) {
	if (n == 0)
		return 0;
	int q = INT_MIN;
	for (int i = 1; i <= n; i++)
		q = std::max(q, price[i] + cut_rod(price, n - i));
	return q;
}

//DYNAMIC PROGRAMMING STARTING HERE
//top-down with memoization:
int memoized_cut_rod_aux(const std::vector<int>& price, int n, std::vector<int>& results) {
	if (results[n] != INT_MIN)
		return results[n];
	int q;
	if (n == 0)
		q = 0;
	else {
		q = INT_MIN;
		for (int i = 1; i <= n; i++)
			q = std::max(q, price[i] + memoized_cut_rod_aux(price, n - i, results));
	}
	results[n] = q;
	return q;
		
}

int memoized_cut_rod(const std::vector<int>& price, int n) {
	std::vector<int> results;
	for (int i = 0; i <= n; i++)
		results.push_back(INT_MIN);
	return memoized_cut_rod_aux(price, n, results);
}

//bottom-up version
int bottom_up_cut_rod(const std::vector<int>& price, int n) {
	std::vector<int> results;
	results.push_back(0);
	int q;
	for (int j = 1; j <= n; j++) {
		q = INT_MIN;
		for (int i = 1; i <= j; i++) {
			q = std::max(q, price[i] + results[j - i]);
		}
		results.push_back(q);
	}
	return results[n];
}

int main() {
	//the index represents the length, the value at the index is the price for that length of rod
	std::vector<int> price{ 0,1,5,8,9,10,17,17,20,24,30 };
	for (int i = 1; i <= 10; i++) {
		std::cout << "total price for rod length (using non-DP) " << i << ": " << cut_rod(price, i) << '\n';
		std::cout << "total price for rod length (using top-down) " << i << ": " << memoized_cut_rod(price, i) << '\n';
		std::cout << "total price for rod length (using bottom-up) " << i << ": " << bottom_up_cut_rod(price, i) << '\n';
	}

}