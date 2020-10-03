#include <iostream>
#include<tuple>
#include <climits>
#include <random>     
#include <algorithm>  
#include <vector>     
#include <iterator>   
#include <functional> 
#include <iostream>  
#include <chrono>
 
class Timer
{
private:
	// Type aliases to make accessing nested type easier
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;
	
	std::chrono::time_point<clock_t> m_beg;
 
public:
	Timer() : m_beg(clock_t::now()) {}
	
	void reset(){
		m_beg = clock_t::now();
	}
	
	double elapsed() const{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

std::vector<int> create_random_data(int n) {
  std::random_device r;
  std::seed_seq      seed{r(), r(), r(), r(), r(), r(), r(), r()};
  std::mt19937       eng(seed); // a source of random data

  std::uniform_int_distribution<int> dist;
  std::vector<int> v(n);

  generate(begin(v), end(v), bind(dist, eng));
  return v;
}
int getMax(std::tuple<int, int, int> t){
	return std::get<2>(t);
}


std::tuple<int, int, int> bruteForce(std::vector<int> arr, int length){
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
	std::vector<int> arr = create_random_data(size);


	Timer t_rec;
	std::tuple<int, int, int> max_subarray = findMaximumSubArray(arr, 0, size - 1);
	double rec_time = static_cast<double>(t_rec.elapsed());


	Timer t_brute;
	max_subarray = bruteForce(arr, size);
	double brute_time = static_cast<double>(t_brute.elapsed());


	//Problem size for which recursive algo beats brute force: around 1230.
	//Answer is approximate because seed value for data is randomized.

	std::cout << "Brute Force time: " << brute_time << std::endl;
	std::cout << "Recursive Time: " << rec_time << std::endl;
 	std::cout << bool(rec_time < brute_time) << std::endl;
	return 0;
}