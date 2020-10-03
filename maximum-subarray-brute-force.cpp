#include <iostream>
#include <tuple>
#include <climits>

std::tuple<int, int, int> findMaximumSubArray(int *arr, int length){
	int max_sum = INT_MIN, low = 0, high = 0;
	for(int i{0}; i < length; i++){
		int sum = 0;
		low = i;
		for(int j{i}; j < length; j++){
			sum += arr[j];
			if(sum > max_sum){
				max_sum = sum;
				high = j;
			}
		}
	}
	return std::make_tuple(low - 1, high, max_sum);
}

int main(){
	int arr[5] = {-1, 2, -3, 4, 2};
	std::tuple<int, int, int> max_subarray = findMaximumSubArray(arr, 5);
	std::cout << "Maximum Subarray:    ";
	for(int i{std::get<0>(max_subarray)}; i <= std::get<1>(max_subarray); i++){
		std::cout << arr[i] << "    ";
	}
	std::cout << "Maximum Sum: " << std::get<2>(max_subarray) << '\n';
	return 0;
}
