#include <iostream>
#include<tuple>
#include <climits>
#include <vector>

int getMax(std::tuple<int, int, int> t){
	return std::get<2>(t);
}
std::tuple<int, int, int> findMaxCrossSubArray(std::vector<int> arr, int low,int mid, int high){
	int left_sum = INT_MIN, left_max = -1;
	int sum = 0;
	for(int i{mid}; i >= low; i--){
		sum += arr[i];
		if(sum > left_sum){
			left_sum = sum;
			left_max = i;
		}
	}
	int right_sum = INT_MIN, right_max = high + 1;
	sum = 0;
	for(int j{mid+1}; j <= high; j++){
		sum += arr[j];
		if(sum > right_sum){
			right_sum = sum;
			right_max = j;
		}
	}
	return std::make_tuple(left_max, right_max, left_sum + right_sum);
}


std::tuple<int, int , int> findMaximumSubArray(std::vector<int> arr, int low, int high){
	if(low == high)
		return std::make_tuple(low, high, arr[low]);
	int mid = (low + high) / 2;
	std::tuple<int, int, int> left, right, cross;
	left = findMaximumSubArray(arr, low, mid);
	right = findMaximumSubArray(arr, mid+1, high);
	cross = findMaxCrossSubArray(arr, low, mid, high);
	if(getMax(left) > getMax(right) and getMax(left) > getMax(cross))
		return left;
	else if(getMax(right) > getMax(left) and getMax(right) > getMax(cross))
		return right;
	else
		return cross;
}


int main(){
	int size{0};
	std::cout << "Enter the size of the random array to be generated: ";
	std::cin >> size;
	std::vector<int> arr(size);
	std::cout << "Enter the elements of the array: ";
	for(int i{0}; i < size; i++){
		std::cin >> arr[i];
	}

	std::tuple<int, int, int> max_subarray = findMaximumSubArray(arr, 0, size - 1);

	std::cout << "Maximum Subarray:    ";
	for(int i{std::get<0>(max_subarray)}; i <= std::get<1>(max_subarray); i++){
		std::cout << arr[i] << "    ";
	}
	std::cout << "Maximum Sum: " << std::get<2>(max_subarray) << '\n';
	return 0;
}