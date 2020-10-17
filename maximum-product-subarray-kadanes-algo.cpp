#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <climits>

std::tuple<int, int, int> kadane_product_sa(std::vector<int> arr){
	int max_prod = INT_MIN;
	int curr_max{1}, curr_min{1};
	int low{0}, high{0};
	int curr_low = 0;
	for(int i{0}; i < int(arr.size()); i++){
		int prev_max = curr_max;
		curr_max = std::max(std::max(curr_max * arr[i], curr_min * arr[i]), arr[i]);
		curr_min = std::min(std::min(curr_min * arr[i], prev_max * arr[i]), arr[i]);
		if(curr_max >  max_prod){
			max_prod = curr_max;
			high = i;
			low = curr_low;
		}
		if(curr_max < 1){
			curr_low = i;
			curr_max = 1;
		}
	}
	return std::make_tuple(low, high, max_prod);
}

void printMaxSubArray(std::vector<int> arr){
	std::tuple<int, int, int> max_subarray = kadane_product_sa(arr);
	std::cout << "Maximum Subarray is: ";
	for(int i{std::get<0>(max_subarray)} ;  i <= std::get<1>(max_subarray); i++){
		std::cout << arr[i] << "    ";
	}
	std::cout << " \nMaximum Product: " << std::get<2>(max_subarray);
}

int main(){
	std::cout << "Enter the length of the array: ";
	int length;
	std::cin >> length;
	std::vector<int> arr(length);
	std::cout << "Enter the elements of the array:";
	for(int i{0}; i < length; i++)
		std::cin >> arr[i];
	printMaxSubArray(arr);
	return 0;
}