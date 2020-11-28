//incomplete
#include <iostream>
#include <algorithm>//for next_permutation
#include <climits>//for int_min
#include <vector>
#include <array>
#include <cmath>


bool isMagicSquare(std::vector<int> &squareVals, int n){
	int length = std::sqrt(n);
	std::vector<std::vector<int>> arr(n);
	for(int i{0}; i < length; i++)
		for(int j{0}; j < length; j++)
			arr[i][j] = squareVals[length * i + j];

	int sum = 0;
	for(int column{0}; column < length; column++)
		sum += arr[0][column];

	for(int row{1}; row < length; row++){
		int temp = 0;
		for(int column{0}; column < length; column++)
			temp += arr[row][column];
		if(temp != sum)
			return false;
	}
	for(int column{0}; column < length; column++){
		int temp = 0;
		for(int row{0}; row < length; row++)
			temp += arr[row][column];
		if(temp != sum)
			return false;
	}
	int temp = 0;
	for(int i{0}; i < length; i++){
		temp += arr[i][i];
	}
	if(temp != sum)
		return false;
	temp = 0;
	for(int i{0}; i < length; i++){
		temp += arr[(length - 1) - i][i];
	}
	if(temp != sum)
		return false;
	for(int i{0}; i < length; i++){
		for(int j{0}; j < length; j++)
			std::cout << arr[i][j] << "    ";
		std::cout << '\n';
	}
	return true;
}

void findMagicSquares(std::vector<std::vector<int>> &magicSquares, int n){
	std::vector<int> squareVals(n);
	for(int i{0}; i < n; i++)
		squareVals[i] = i + 1;
	do{
		if(isMagicSquare(squareVals, n))
			magicSquares.push_back(squareVals);
	} while(std::next_permutation(squareVals.begin(), squareVals.end()));
}

int convCost(std::vector<int> &vect1, std::vector<int> &vect2){
	int cost{0};
	for(int i{0}; i < static_cast<int>(vect1.size()); i++)
		cost += fabs(vect1[i] - vect2[i]);
	return cost;
}

int getMinCost(std::vector<int> &inputMatrix, int n){
	int minCost{INT_MAX};
	std::vector<std::vector<int>> magicSquares;
	findMagicSquares(magicSquares, n);
	for(auto &magicSquare : magicSquares)
		minCost = std::min(minCost, convCost(inputMatrix, magicSquare));
	return minCost;
}


int main(){
	int n;
	std::cout << "Enter the length/breadth of the matrix: ";
	std::cin >> n;
	n = std::pow(n, 2);
	std::vector<int> inputMatrix(n);
	std::cout << "Enter the matrix values: \n";
	for(int i{0}; i < n; i++)
		std::cin >> inputMatrix[i];
	std::cout << "The minimum cost to convert the matrix: " << getMinCost(inputMatrix, n) << ".\n";
	return 0;
}