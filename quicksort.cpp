#include <bits/stdc++.h>


bool ascending(int a, int b){
	return a <= b;
}

bool descending(int a, int b){
	return a >= b;
}

int partition(std::vector<int> &arr, int low, int high, bool (*comp)(int, int)){
	int key = arr[high];
	int i = low - 1;
	for(int j{low}; j < high; j++){
		if(comp(arr[j], key)){
			i++;
			std::swap(arr[i], arr[j]);
		}
	}
	std::swap(arr[i + 1], arr[high]);
	return i + 1;
}

void quicksort(std::vector<int> &arr, int low, int high,  bool (*comp)(int, int)){
	if(low < high){
		int mid = partition(arr, low, high, comp);
		quicksort(arr, low, mid - 1, comp);
		quicksort(arr, mid + 1, high, comp);
	}
}

int main(){
	std::cout << "Enter the number of elements: ";
	int n{0};
	std::cin >> n;
	std::cout << "Enter the elements of the array: ";
	std::vector<int> arr(n);
	for(auto &val : arr)
		std::cin >> val;
	std::cout << "Entered values: ";
	for(auto &val : arr){
		std::cout << val << "    ";
	}
	bool (*comp)(int, int){ &ascending};
	quicksort(arr, 0, n - 1, comp);
	std::cout << "\nSorted array: ";
	for(auto &val : arr)
		std::cout << val << "    ";
	std::cout << std::endl;
	return 0;
}