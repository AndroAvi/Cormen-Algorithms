#include <iostream>
#include <vector>

void printArr(std::vector<int> &arr){
	for(auto el: arr)
		std::cout << el << "    ";
	std::cout << std::endl;
}

bool prevPermutation(std::vector<int> &arr){
	int suffixHead = -1;
	for(int i{1}; i < int(arr.size()); i++)
		if(arr[i] < arr[i - 1])
			suffixHead = i;
	if(suffixHead == -1)
		return false;
	int pivot = suffixHead - 1;
	int toSwap = suffixHead;
	for(int i{suffixHead + 1}; i < int(arr.size()); i++)
		if(arr[i] < arr[pivot] and arr[i] >= arr[toSwap])
			toSwap = i;
	std::swap(arr[pivot], arr[toSwap]);
	for(int i{suffixHead}, j{int(arr.size()) - 1}; i < j; i++, j--)
		std::swap(arr[i], arr[j]);
	return true;
}

int main(){
	int length;
	std::cout << "Enter the number of elements: ";
	std::cin >> length;
	std::vector<int> arr(length);
	std::cout << "Enter the elements: ";
	for(int i{0}; i < length; i++)
		std::cin >> arr[i];
	std::cout << "Input array: ";
	printArr(arr);
	while(prevPermutation(arr)){
		std::cout << "Next smallest permutation: ";
		printArr(arr);
	}
	std::cout << '\n';
	return 0;
}