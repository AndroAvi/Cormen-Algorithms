#include <iostream>
#include <vector>
#include <tuple>
#include <climits>

std::tuple<int, int, int> kadan_subarray(std::vector<int> arr){
	int max_sum{INT_MIN};
	int curr_sum{0};
	int high{0},low{0};
	int curr_low{0};
	for(int j{0}; j < static_cast<int>(arr.size()); j++){
		curr_sum += arr[j];
		if(curr_sum > max_sum){
			max_sum = curr_sum;
			low = curr_low;
			high = j;
		}
		if(curr_sum < 0){
			curr_sum = 0;
			curr_low = j + 1;
		}
	}
	return std::make_tuple(low, high, max_sum);
}

void printMaxSubArray(std::vector<int> arr){
	std::tuple<int, int, int> max_subarray = kadan_subarray(arr);
	std::cout << "Maximum Subarray is: ";
	for(int i{std::get<0>(max_subarray)} ;  i <= std::get<1>(max_subarray); i++){
		std::cout << arr[i] << "    ";
	}
	std::cout << " \nMaximum Sum: " << std::get<2>(max_subarray);
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