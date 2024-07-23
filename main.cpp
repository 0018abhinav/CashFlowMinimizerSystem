
#include "bank.h"

int main() {
    std::cout << "\n\t\t\t\t********************* Welcome to CASH FLOW MINIMIZER SYSTEM ***********************\n\n\n";
    std::cout << "This system minimizes the number of transactions among multiple banks in the different corners of the world that use different modes of payment. There is one world bank (with all payment modes) to act as an intermediary between banks that have no common mode of payment. \n\n";
    std::cout << "Enter the number of banks participating in the transactions.\n";
    int numBanks;
    std::cin >> numBanks;

    bank input[numBanks];
    std::unordered_map<std::string, int> indexOf;

    std::cout << "Enter the details of the banks and transactions as stated:\n";
    std::cout << "Bank name, number of payment modes it has, and the payment modes.\n";
    std::cout << "Bank name and payment modes should not contain spaces\n";

    int maxNumTypes;
    for (int i = 0; i < numBanks; i++) {
        if (i == 0) {
            std::cout << "World Bank : ";
        } else {
            std::cout << "Bank " << i << " : ";
        }
        std::cin >> input[i].name;
        indexOf[input[i].name] = i;
        int numTypes;
        std::cin >> numTypes;

        if (i == 0) maxNumTypes = numTypes;

        std::string type;
        while (numTypes--) {
            std::cin >> type;
            input[i].types.insert(type);
        }
    }

    std::cout << "Enter number of transactions.\n";
    int numTransactions;
    std::cin >> numTransactions;

    std::vector<std::vector<int>> graph(numBanks, std::vector<int>(numBanks, 0));

    std::cout << "Enter the details of each transaction as stated:";
    std::cout << "Debtor Bank, creditor Bank, and amount\n";
    std::cout << "The transactions can be in any order\n";
    for (int i = 0; i < numTransactions; i++) {
        std::cout << (i) << " th transaction : ";
        std::string s1, s2;
        int amount;
        std::cin >> s1 >> s2 >> amount;

        graph[indexOf[s1]][indexOf[s2]] = amount;
    }

    minimizeCashFlow(numBanks, input, indexOf, numTransactions, graph, maxNumTypes);
    return 0;
}
