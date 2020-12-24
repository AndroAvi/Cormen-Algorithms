#include <iostream>
#include <vector>

class Item{
    public:
        int m_value;
        int m_weight;
        Item(int value, int weight) : m_value{value}, m_weight{weight} {}
        friend std::ostream& operator<<(std::ostream& out, const Item &item){
            out << "( " << item.m_value << " : " << item.m_weight << ")";
            return out;
        }
};

std::vector<std::vector<int>> solveSubKS(std::vector<Item> &items, int n, int w){
    std::vector<std::vector<int>> DP(n, std::vector<int>(w+1));
    for(int iii{0}; iii < n; iii++){
        for(int jjj{0}; jjj <= w; jjj++){
            if(jjj == 0)
                DP[iii][jjj] = 0;
            else if(iii == 0){
                if(jjj < items[iii].m_weight)
                    DP[iii][jjj] = 0;
                else
                    DP[iii][jjj] = items[iii].m_value;
            }else{
                if(jjj < items[iii].m_weight)
                    DP[iii][jjj] = DP[iii - 1][jjj];
                else
                    DP[iii][jjj] = std::max(DP[iii - 1][jjj], DP[iii - 1][jjj - items[iii].m_weight] + items[iii].m_value);
            }
        }
    }
    return DP;
}

int main(){
    std::cout << "Enter the number of items: ";
    int n{0};
    std::cin >> n;
    std::vector<Item> items;
    for(int i{0}; i < n; i++){
        int val{0}, weight{0};
        std::cout << "Enter the value and weight for item " << i + 1 << ": ";
        std::cin >> val >> weight;
        Item temp(val, weight);
        items.push_back(temp);  
    }
    std::cout << "Entered items(value : weight):\n";
    for(auto &item : items)
        std::cout << item;
    std::cout << "\nEnter the max weight: ";
    int w{0};
    std::cin >> w;
    std::vector<std::vector<int>> SubProbs = solveSubKS(items, n, w);

    for(auto &item : SubProbs){
        for(auto &maxVal : item)
            std::cout << maxVal << "    ";
        std::cout << '\n';
    }
    std::cout << std::endl;
    return 0;
}