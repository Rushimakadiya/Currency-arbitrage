#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
int main() {
    // Exchange rates for the currencies
    vector<vector<double>> exchange_rates = {
         // USD, INR, AUD, RUB, EUR
        {1.0, 82.58, 1.53, 79.55, 0.93}, // USD
        {0.012, 1.0, 0.019, 0.96, 0.011}, // INR
        {0.65, 53.82, 1.0, 51.85, 0.61}, // AUD
        {0.013, 1.04, 0.019, 1.0, 0.012}, // RUB
        {1.07, 88.59, 1.65, 85.34, 1.0}  // EUR
    };

    vector<string> currency_names = { "USD", "INR", "AUD", "RUB", "EUR" };

    int num_currencies = exchange_rates.size();

    // User input for base currency
    cout << "Enter the base currency (1 - USD, 2 - INR, 3 - AUD, 4 - RUB, 5 - EUR): "<<endl<<endl;
    int base_currency;
    cin >> base_currency;
    base_currency--; // Adjust index

    vector<int> sequence(num_currencies);
    for (int i = 0; i < num_currencies; i++) {
        sequence[i] = i;
    }

    vector<vector<int>> arbitrage_sequences;
    vector<double> profits;

    // Arbitrage between 3 currencies
    for (int i = 0; i < num_currencies; i++) {
        for (int j = 0; j < num_currencies; j++) {
            if (i != j) {
                for (int k = 0; k < num_currencies; k++) {
                    if (k != i && k != j) {
                        vector<int> arbitrage_sequence = { i, j, k };
                        double profit = exchange_rates[i][j] * exchange_rates[j][k] * exchange_rates[k][i];
                        if (i == base_currency && profit > 1.0) {
                            arbitrage_sequences.push_back(arbitrage_sequence);
                            profits.push_back(profit);
                        }
                    }
                }
            }
        }
    }

    // Arbitrage between 4 currencies
    for (int i = 0; i < num_currencies; i++) {
        for (int j = 0; j < num_currencies; j++) {
            if (i != j) {
                for (int k = 0; k < num_currencies; k++) {
                    if (k != i && k != j) {
                        for (int l = 0; l < num_currencies; l++) {
                            if (l != i && l != j && l != k) {
                                vector<int> arbitrage_sequence = { i, j, k, l };
                                double profit = exchange_rates[i][j] * exchange_rates[j][k] * exchange_rates[k][l] * exchange_rates[l][i];
                                if (i == base_currency && profit > 1.0) {
                                    arbitrage_sequences.push_back(arbitrage_sequence);
                                    profits.push_back(profit);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Arbitrage between 5 currencies
    do {
        double profit = 1.0;
        vector<int> arbitrage_sequence;
        for (int i = 0; i < num_currencies - 1; i++) {
            profit *= exchange_rates[sequence[i]][sequence[i + 1]];
            arbitrage_sequence.push_back(sequence[i]);
        }
        arbitrage_sequence.push_back(sequence[num_currencies - 1]);

        if (sequence[0] == base_currency && profit > 1.0) {
            arbitrage_sequences.push_back(arbitrage_sequence);
            profits.push_back(profit);
        }
    } while (next_permutation(sequence.begin(), sequence.end()));

    int num_arbitrages = arbitrage_sequences.size();
    if (num_arbitrages > 0) {
        cout << "Positive Arbitrage Opportunities:" << endl;
        for (int i = 0; i < num_arbitrages; i++) {
            if(profits[i]<=3){
            cout << "Arbitrage Sequence: ";
            for (int j = 0; j < arbitrage_sequences[i].size(); j++) {
                cout << currency_names[arbitrage_sequences[i][j]];
                if (j < arbitrage_sequences[i].size() - 1) {
                    cout << " -> ";
                }
            }
            cout << endl;

            cout << "Profit: " << profits[i] << endl;
            
            cout << endl;
            }
        }
    } else {
        cout << "No positive arbitrage opportunities found." << endl;
    }

    return 0;
}
