#include <iostream>
#include <vector>

void maxHeapify(std::vector<int> &arr, int i, int heapSize){
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if(left < heapSize and arr[left] > arr[largest])
		largest = left;
	if(right < heapSize and arr[right] > arr[largest])
		largest = right;
	if(largest != i){
		std::swap(arr[i], arr[largest]);
		maxHeapify(arr, largest, heapSize);
	}
}

void heapSort(std::vector<int> &arr){
	int length = int(arr.size());
	for(int i{length/2 - 1}; i >= 0; i--)
		maxHeapify(arr, i, length);
	for(int i{length - 1}; i >= 0; i--){
		std::swap(arr[i], arr[0]);
		maxHeapify(arr, 0, i);
	}
}

int main(){
	int length;
	std::cin >> length;
	std::vector<int> arr(length);
	for(int i{0}; i < length; i++)
		std::cin >> arr[i];
	std::cout << "Sorted Array: \n";
	heapSort(arr);
	for(auto el : arr)
		std::cout << el << " ";
	std::cout << '\n';
	return 0;
}