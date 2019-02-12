#include <iostream>
#include <vector>

void Swap (std::vector<int> &v, int x, int y) {
	v[y] += v[x];
	v[x]  = v[y] - v[x];
	v[y] -= v[x]; 
}

int main(int argc, char const *argv[]) {
	int n;
	const int N = 4;

	std::cin >> n;
	std::vector <int> x(n);

	for (int i = 0; i < n; i++) {
		std::cin >> x[i];
	}

	std::vector <int> count(N);
	count[0] = 0;

	for (int e: x)
		count[e]++;

	count[3] = count[2] + count[1];
	count[2] = count[1] + count[0];
	count[1] = count[0];

	int i = 0, current = 0;
	/*
	std::cout << "__________________________________________________" << std::endl;
	
	std::cout << count[1] << " " << count[2] << " " << count[3];
	std::cout << std::endl;
	
	for (int i = 0; i < n; std::cout << i << " ", i++);
	std::cout << std::endl;

	for (int e: x) {
		std::cout << e << " ";
	} std::cout << std::endl;
	*/

	for (current = 0; current < n; current++) {
		if (current < count[2]) {
			if (x[current] == 3) {
				for (int k = n - 1; k >= count[2]; k--) {
					if (x[k] == 1) {
						Swap(x, current, k);
						i++;
						break;
					}
				}
			} else
			if (x[current] == 2) {
				for (int k = count[2]; k < n; k++) {
					if (x[k] == 1) {
						Swap(x, current, k);
						i++;
						break;
					}
				}
			}
		} else
		if (current < count[3] && x[current] == 3) {
			for (int k = count[3]; k < n; k++) {
				if (x[k] == 2) {
					Swap(x, current, k);
					i++;
					break;
				}
			}
		}
	}



	/*
	while (current < n) {
		if ((x[current] == 3) && current <= count[2]) {
			int j;
			for (j = n - 1; j > count[2]; j--) {
				if (x[j] == 1) {
					Swap(x, current, j);
					i++;
					break;
				}
			}

		} else
		if (x[current] == 3 && current <= count[3]) {

			for (int j = n - 1; j > count[3]; j--) {
				if (x[j] == 2) {
					Swap(x, current, j);
					i++;
					break;
				}
			}
		} else
		if ((x[current] == 2) && current <= count[2]) {

			for (int j = count[2]; j < n; j++) {
				if (x[j] == 1) {
					Swap(x, current, j);
					i++;
					break;
				}
			}
		}
		current++;
	}
	
	
	for (int e: x) {
		std::cout << e << " ";
	} std::cout << std::endl;
	*/

	std::cout << i << std::endl;

	return 0;
}