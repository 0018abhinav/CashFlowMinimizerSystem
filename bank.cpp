
#include "bank.h"

int getMinIndex(bank listOfNetAmounts[], int numBanks) {
    int min = INT_MAX, minIndex = -1;
    for (int i = 0; i < numBanks; i++) {
        if (listOfNetAmounts[i].netAmount == 0) continue;

        if (listOfNetAmounts[i].netAmount < min) {
            minIndex = i;
            min = listOfNetAmounts[i].netAmount;
        }
    }
    return minIndex;
}

int getSimpleMaxIndex(bank listOfNetAmounts[], int numBanks) {
    int max = INT_MIN, maxIndex = -1;
    for (int i = 0; i < numBanks; i++) {
        if (listOfNetAmounts[i].netAmount == 0) continue;

        if (listOfNetAmounts[i].netAmount > max) {
            maxIndex = i;
            max = listOfNetAmounts[i].netAmount;
        }
    }
    return maxIndex;
}

std::pair<int, std::string> getMaxIndex(bank listOfNetAmounts[], int numBanks, int minIndex, bank input[], int maxNumTypes) {
    int max = INT_MIN;
    int maxIndex = -1;
    std::string matchingType;

    for (int i = 0; i < numBanks; i++) {
        if (listOfNetAmounts[i].netAmount == 0) continue;

        if (listOfNetAmounts[i].netAmount < 0) continue;

        std::vector<std::string> v(maxNumTypes);
        std::vector<std::string>::iterator ls = set_intersection(listOfNetAmounts[minIndex].types.begin(), listOfNetAmounts[minIndex].types.end(), listOfNetAmounts[i].types.begin(), listOfNetAmounts[i].types.end(), v.begin());

        if ((ls - v.begin()) != 0 && max < listOfNetAmounts[i].netAmount) {
            max = listOfNetAmounts[i].netAmount;
            maxIndex = i;
            matchingType = *(v.begin());
        }
    }

    return std::make_pair(maxIndex, matchingType);
}

void printAns(std::vector<std::vector<std::pair<int, std::string>>> ansGraph, int numBanks, bank input[]) {
    std::cout << "\nThe transactions for minimum cash flow are as follows : \n\n";
    for (int i = 0; i < numBanks; i++) {
        for (int j = 0; j < numBanks; j++) {
            if (i == j) continue;

            if (ansGraph[i][j].first != 0 && ansGraph[j][i].first != 0) {
                if (ansGraph[i][j].first == ansGraph[j][i].first) {
                    ansGraph[i][j].first = 0;
                    ansGraph[j][i].first = 0;
                } else if (ansGraph[i][j].first > ansGraph[j][i].first) {
                    ansGraph[i][j].first -= ansGraph[j][i].first;
                    ansGraph[j][i].first = 0;
                    std::cout << input[i].name << " pays Rs" << ansGraph[i][j].first << " to " << input[j].name << " via " << ansGraph[i][j].second << std::endl;
                } else {
                    ansGraph[j][i].first -= ansGraph[i][j].first;
                    ansGraph[i][j].first = 0;
                    std::cout << input[j].name << " pays Rs" << ansGraph[j][i].first << " to " << input[i].name << " via " << ansGraph[j][i].second << std::endl;
                }
            } else if (ansGraph[i][j].first != 0) {
                std::cout << input[i].name << " pays Rs" << ansGraph[i][j].first << " to " << input[j].name << " via " << ansGraph[i][j].second << std::endl;
            } else if (ansGraph[j][i].first != 0) {
                std::cout << input[j].name << " pays Rs" << ansGraph[j][i].first << " to " << input[i].name << " via " << ansGraph[j][i].second << std::endl;
            }

            ansGraph[i][j].first = 0;
            ansGraph[j][i].first = 0;
        }
    }
    std::cout << "\n";
}

void minimizeCashFlow(int numBanks, bank input[], std::unordered_map<std::string, int>& indexOf, int numTransactions, std::vector<std::vector<int>>& graph, int maxNumTypes) {
    bank listOfNetAmounts[numBanks];

    for (int b = 0; b < numBanks; b++) {
        listOfNetAmounts[b].name = input[b].name;
        listOfNetAmounts[b].types = input[b].types;

        int amount = 0;

        for (int i = 0; i < numBanks; i++) {
            amount += (graph[i][b]);
        }

        for (int j = 0; j < numBanks; j++) {
            amount += ((-1) * graph[b][j]);
        }

        listOfNetAmounts[b].netAmount = amount;
    }

    std::vector<std::vector<std::pair<int, std::string>>> ansGraph(numBanks, std::vector<std::pair<int, std::string>>(numBanks, {0, ""}));

    int numZeroNetAmounts = 0;

    for (int i = 0; i < numBanks; i++) {
        if (listOfNetAmounts[i].netAmount == 0) numZeroNetAmounts++;
    }

    while (numZeroNetAmounts != numBanks) {
        int minIndex = getMinIndex(listOfNetAmounts, numBanks);
        std::pair<int, std::string> maxAns = getMaxIndex(listOfNetAmounts, numBanks, minIndex, input, maxNumTypes);

        int maxIndex = maxAns.first;

        if (maxIndex == -1) {
            (ansGraph[minIndex][0].first) += abs(listOfNetAmounts[minIndex].netAmount);
            (ansGraph[minIndex][0].second) = *(input[minIndex].types.begin());

            int simpleMaxIndex = getSimpleMaxIndex(listOfNetAmounts, numBanks);
            (ansGraph[0][simpleMaxIndex].first) += abs(listOfNetAmounts[minIndex].netAmount);
            (ansGraph[0][simpleMaxIndex].second) = *(input[simpleMaxIndex].types.begin());

            listOfNetAmounts[simpleMaxIndex].netAmount += listOfNetAmounts[minIndex].netAmount;
            listOfNetAmounts[minIndex].netAmount = 0;

            if (listOfNetAmounts[minIndex].netAmount == 0) numZeroNetAmounts++;
            if (listOfNetAmounts[simpleMaxIndex].netAmount == 0) numZeroNetAmounts++;
        } else {
            int transactionAmount = std::min(abs(listOfNetAmounts[minIndex].netAmount), listOfNetAmounts[maxIndex].netAmount);

            (ansGraph[minIndex][maxIndex].first) += (transactionAmount);
            (ansGraph[minIndex][maxIndex].second) = maxAns.second;

            listOfNetAmounts[minIndex].netAmount += transactionAmount;
            listOfNetAmounts[maxIndex].netAmount -= transactionAmount;

            if (listOfNetAmounts[minIndex].netAmount == 0) numZeroNetAmounts++;
            if (listOfNetAmounts[maxIndex].netAmount == 0) numZeroNetAmounts++;
        }
    }

    printAns(ansGraph, numBanks, input);
}
