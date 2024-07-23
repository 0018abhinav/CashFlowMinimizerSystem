
#ifndef BANK_H
#define BANK_H

#include <iostream>
#include <set>
#include <vector>
#include <unordered_map>
#include <climits>
#include <algorithm>

class bank {
public:
    std::string name;
    int netAmount;
    std::set<std::string> types;
};

int getMinIndex(bank listOfNetAmounts[], int numBanks);
int getSimpleMaxIndex(bank listOfNetAmounts[], int numBanks);
std::pair<int, std::string> getMaxIndex(bank listOfNetAmounts[], int numBanks, int minIndex, bank input[], int maxNumTypes);
void printAns(std::vector<std::vector<std::pair<int, std::string>>> ansGraph, int numBanks, bank input[]);
void minimizeCashFlow(int numBanks, bank input[], std::unordered_map<std::string, int>& indexOf, int numTransactions, std::vector<std::vector<int>>& graph, int maxNumTypes);

#endif // BANK_H
