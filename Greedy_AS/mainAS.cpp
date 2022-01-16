#include <vector>
#include <iostream>

using std::vector;

//assumes activities are sorted by finish times
void recursiveAS(const vector<int>& s, const vector<int>& f, vector<int>& activities, int k, int n) {
	int m = k + 1;
	while (m <= n && s[m] < f[k])
		m++;
	activities.push_back(k);
	if (m <= n) {
		recursiveAS(s, f, activities, m, n);
	}
}

void iterativeAS(const vector<int>& s, const vector<int>& f, vector<int>& activities) {
	activities.push_back(0);
	int n = s.size() - 1;
	int k = 1;
	for (int m = 1; m <= n; m++) {
		if (s[m] >= f[k]) {
			activities.push_back(m);
			k = m;
		}
	}
}

int main() {
	vector<int> s{ 1,3,0,5,3,5,6,8,8,2,12,13,15 };
	vector<int> f{ 4,5,6,7,9,9,10,11,12,14,16,18,20 };
	vector<int> activities;
	//recursiveAS(s, f, activities, 0, s.size() - 1);
	iterativeAS(s, f, activities);
	for (int x : activities)
		std::cout << x << ' ';
}