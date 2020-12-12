#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <climits>

void addPaddings(std::vector<std::vector<int>> &tab){
	int row = int(tab.size());
	int col = int(tab[0].size());
	std::vector<std::vector<int>> cTab = tab;
	tab.resize(row + 2);
	for(auto &row : tab)
		row.resize(col + 2);
	for(int j{0}; j < col + 2; j++)
		tab[0][j] = INT_MIN;
	for(int i{0};i < row + 2; i++)
		tab[i][0] = INT_MIN;
	for(int i{1}; i <= row; i++){
		for(int j{1}; j <= col; j++)
			tab[i][j] = cTab[i - 1][j - 1];
	}
}

void removePad(std::vector<std::vector<int>> &tab){
	int row = int(tab.size() - 2);
	int col = int(tab[0].size()) - 2;
	std::vector<std::vector<int>> cTab = tab;
	tab.resize(row);
	for(auto &row : tab)
		row.resize(col);
	for(int i{1}; i <= row; i++)
		for(int j{1}; j <= col; j++)
			tab[i - 1][j - 1] = cTab[i][j];
}

void fillTab(std::vector<std::vector<int>> &tab){
	addPaddings(tab);
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
			else if(el == INT_MIN)
				std::cout << '-' << char(236) << "    ";
			else
				std::cout << el << "    ";
		}
		std::cout << '\n';
	}
}

void insert(std::vector<std::vector<int>> &tab, int val){
	int row = int(tab.size()) - 2;
	int col = int(tab[0].size()) - 2;
	tab[row][col] = val;
	while(tab[row - 1][col] > tab[row][col] or tab[row][col - 1] > tab[row][col]){
		if(tab[row-1][col] > tab[row][col - 1]){
			std::swap(tab[row][col], tab[row - 1][col]);
			row--;
		}else{
			std::swap(tab[row][col], tab[row][col - 1]);
			col--;
		}
	}
}


int main(){
	/* Driver Code
	int row, col;
	std::cout << "Enter the number of rows and columns: ";
	std::cin >> row >> col;
	std::vector<std::vector<int>> tab(row, std::vector<int>(col));
	std::cout << "Enter the elements of the tableau:\n";
	for(auto &row : tab)
		for(auto &el : row)
			std::cin >> el;
	std::cout << "Input Tableau:\n";
	printArr(tab);
	
	//Testing Code for EXTRACT-MIN() Procedure in O(row + col) time.
	std::cout << "Enter row and column indeces of sub tableau to extract min from: ";
	int i, j;
	std::cin >> i >> j;
	fillTab(tab);
	std::cout << "After extracting " << extractMin(tab, i+1, j+1) << ":\n";
	removePad(tab);
	printArr(tab);


	
	//Testing Code for INSERT() Procedure in O(row + col) time.
	std::cout << "Enter element to insert: ";
	int val;
	std::cin >> val;
	fillTab(tab);
	insert(tab, val);
	removePad(tab);
	std::cout << "After inserting " << val << ":\n";
	printArr(tab);
	*/

	std::cout << std::endl;
	return 0;
}