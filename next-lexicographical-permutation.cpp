#include <iostream>
#include <vector>

void printArr(std::vector<int> &arr){
	for(auto el: arr)
		std::cout << el << "    ";
	std::cout << std::endl;
}

bool nextPermutation(std::vector<int> &arr){
	//Step 1: Find the head of suffix.
	int suffixHead{-1};
	for(int i{1}; i < int(arr.size()); i++)
		if(arr[i] > arr[i - 1])
			suffixHead = i;
	if(suffixHead == -1)
		return false;
	//Step 2: Assign the pivot.
	int pivot{suffixHead - 1};
	//Step 3: Find the smallest element such that: a.it is greater than the pivot
	//b.it is the smallest among all such elements in the suffix.
	int toSwap = suffixHead;
	for(int i{suffixHead + 1}; i < int(arr.size()); i++){
		if(arr[i] > arr[pivot] and arr[i] <= arr[toSwap])
			toSwap = i;
	}
	//Step 4: Swap the element found in step 3 with the pivot.
	std::swap(arr[pivot], arr[toSwap]);
	//Step 5: Finally, Reverse the suffix of the resulting array.
	for(int i{suffixHead}, j{int(arr.size()) -1}; i < j; i++, j--)
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
	while(nextPermutation(arr)){
		std::cout << "Next highest permutation: ";
		printArr(arr);
	}
	std::cout << '\n';
	return 0;
}