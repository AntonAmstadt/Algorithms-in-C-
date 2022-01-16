#include <string>
#include <iostream>
#include <memory>

using std::cout;
using std::string;


// returns the length of the longest common subsequence
// prints the longest common subsequence
// can also print the intermediate table if you uncomment that section
int lcs(string x, string y) {
	//create intermediate table
	int m = x.length() + 1;
	int n = y.length() + 1;
	std::unique_ptr<int[]> arr(new int[m * n]);

	for (int i = 0; i < m; i++)
		arr[i] = 0;
	for (int i = 1; i < n; i++)
		arr[m * i] = 0;

	for (int j = 1; j < n; j++) {
		for (int i = 1; i < m; i++) {
			if (x[i - 1] == y[j - 1])
				arr[j * m + i] = arr[(j - 1) * m + i - 1] + 1;
			else if (arr[j * m + i - 1] >= arr[(j - 1) * m + i])
				arr[j * m + i] = arr[j * m + i - 1];
			else
				arr[j * m + i] = arr[(j - 1) * m + i];
		}
	}
	//intermediate table completed

	//print intermediate table
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < m; i++) {
			cout << arr[j * m + i] << ' ';
		}
		cout << '\n';
	}

	//find the string value of the lcs
	std::string longestSubsequence{ "" };
	int j = n - 1;
	int i = m - 1;
	while (i > 0 && j > 0) {
		if (arr[j * m + i] == arr[m * (j - 1) + i])
			j--;
		else if (arr[j * m + i] == arr[m * j + i - 1])
			i--;
		else {
			longestSubsequence.insert(longestSubsequence.begin(), x[i - 1]);
			j--;
			i--;
		}
	}
	std::cout << "longest common subsequence: " << longestSubsequence << '\n';

	return arr[m * n - 1];
}

//same function as above, but without a smart pointer
int lcsUnsafe(string x, string y) {
	//create intermediate table
	int m = x.length() + 1;
	int n = y.length() + 1;
	int* arr = new int[m * n];

	for (int i = 0; i < m; i++) 
		*(arr + i) = 0;
	for (int i = 1; i < n; i++)
		*(arr + (m * i)) = 0;

	for (int j = 1; j < n; j++) {
		for (int i = 1; i < m; i++) {
			if (x[i - 1] == y[j - 1])
				*(arr + j * m + i) = *(arr + (j - 1) * m + i - 1) + 1;
			else if (*(arr + j * m + i - 1) >= *(arr + (j - 1) * m + i))
				*(arr + j * m + i) = *(arr + j * m + i - 1);
			else
				*(arr + j * m + i) = *(arr + (j - 1) * m + i);
		}
	}
	//intermediate table completed

	//print intermediate table
	//for (int j = 0; j < n; j++) {
	//	for (int i = 0; i < m; i++) {
	//		cout << *(arr + j * m + i) << ' ';
	//	}
	//	cout << '\n';
	//}

	//find the string value of the lcs
	std::string longestSubsequence{ "" };
	int j = n - 1;
	int i = m - 1;
	while (i > 0 && j > 0) {
		if (*(arr + m * j + i) == *(arr + m * (j - 1) + i))
			j--;
		else if (*(arr + m * j + i) == *(arr + m * j + i - 1))
			i--;
		else {
			longestSubsequence.insert(longestSubsequence.begin(), x[i - 1]);
			j--;
			i--;
		}
	}
	std::cout << "longest common subsequence: " << longestSubsequence << '\n';

	//clean up and return length
	int answer = *(arr + m * n - 1);
	delete[] arr;
	return answer; 
}

int main() {
	string x = "anton";
	string y = "amstadt";
	std::cout << "length of the longest common subsequence: " << lcs(x, y);
}