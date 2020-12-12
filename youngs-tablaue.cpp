#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <climits>

void fillTab(std::vector<std::vector<int>> &tab){
	int row = int(tab.size());
	int col = int(tab[0].size());
	tab.resize( row + 1);
	for(int i{0}; i <= row; i++)
		tab[i].resize(col + 1);
	for(auto &row : tab){
		for(auto &el : row)
			if(el == 0)
				el = INT_MAX;
	}
}

int extractMin(std::vector<std::vector<int>> &tab, int rowIndex, int colIndex){
	if(tab[rowIndex][colIndex + 1] == INT_MAX and tab[rowIndex + 1][colIndex] == INT_MAX){
		int min = tab[rowIndex][colIndex];
		tab[rowIndex][colIndex] = INT_MAX;
		return min;
	}
	if(tab[rowIndex][colIndex + 1] < tab[rowIndex + 1][colIndex]){
		std::swap(tab[rowIndex][colIndex], tab[rowIndex][colIndex + 1]);
		return extractMin(tab, rowIndex, colIndex + 1);
	}else{
		std::swap(tab[rowIndex][colIndex], tab[rowIndex + 1][colIndex]);
		return extractMin(tab, rowIndex + 1, colIndex);
	}
}



void printArr(std::vector<std::vector<int>> &tab){
	for(auto &row : tab){
		for(auto &el : row){
			if(el == INT_MAX)
				std::cout << char(236) << "    ";
			else
				std::cout << el << "    ";
		}
		std::cout << '\n';
	}
}


int main(){
	int row, col;
	std::cout << "Enter the number of rows and columns: ";
	std::cin >> row >> col;
	std::vector<std::vector<int>> tab(row, std::vector<int>(col));
	for(auto &row : tab)
		for(auto &el : row)
			std::cin >> el;
	fillTab(tab);
	std::cout << "Input Matrix:\n";
	printArr(tab);
	std::cout << "After extracting " << extractMin(tab, 0, 0) << ":\n";
	printArr(tab);



	std::cout << std::endl;
	return 0;
}