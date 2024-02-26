#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <set>
#include "Gauss.h"

void readMatrices(const string& fileName);

void swapColumns(vector<vector<pair<int, int>>>& matrix, int col1, int col2);

void inputBasicVariables(vector<int>& indexBasicVariables, vector<vector<pair<int, int>>>& matrix);

void obtainingDecision(vector<vector<pair<int, int>>>& matrix, vector<int>& indexBasicVariables);

void outputMatrix(const vector<vector<pair<int, int>>>& matrix, vector<int>& indexBasicVariables);

bool contain(vector<int>& indexVariables, int index);

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    readMatrices("matrix.txt");
}

void obtainingDecision(vector<vector<pair<int, int>>>& matrix, vector<int>& indexBasicVariables) {
    vector<pair<int, int>> solution(matrix.size());
    outputMatrix(matrix, indexBasicVariables);
    if (Gauss::methodGauss(matrix))
        outputMatrix(matrix, indexBasicVariables);
    matrix.clear();
}

void readMatrices(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Cannot open file!" << std::endl;
    }

    while (!file.eof()) {
        int rows, cols;
        file >> rows >> cols;
        vector<vector<pair<int, int>>> matrix(rows, vector<pair<int, int>>(cols));
        vector<int> indexBasicVariables(cols - 1);

        for (int i = 0; i < cols - 1; i++)
            indexBasicVariables[i] = i;

        for (int i = 0; i < rows; ++i) {

            for (int j = 0; j < cols; ++j) {
                string token;
                file >> token;
                if (token.find('/') != string::npos) {
                    size_t pos = token.find('/');
                    matrix[i][j].first = stoi(token.substr(0, pos));
                    matrix[i][j].second = stoi(token.substr(pos + 1));
                }
                else {
                    matrix[i][j].first = stoi(token);
                    matrix[i][j].second = 1;
                }
            }
        }
        if (cols - rows > 1)
            inputBasicVariables(indexBasicVariables, matrix);
        obtainingDecision(matrix, indexBasicVariables);
    }
    file.close();
}

void inputBasicVariables(vector<int>& indexBasicVariables, vector<vector<pair<int, int>>>& matrix) {
    unsigned long long n = matrix.size();
    unsigned long long m = indexBasicVariables.size();
    cout << "Enter index of Basic Variables (total " << n << ")\n";

    vector<int> listOfIndex;
    int count = 0;

    for (int i = 0; i < n; i++) {
        int index = -1;
        while (index < 0 || index > m) {
            cin >> index;
            listOfIndex.push_back(index);
        }  
    }
    cout << listOfIndex.size() << "\n";
    for (int i = 0; i < indexBasicVariables.size(); i++) {
        if (!contain(listOfIndex, i)) {
            swapColumns(matrix, count, i);
            swap(indexBasicVariables[count], indexBasicVariables[i]);
            count++;
        }
    }
}

bool contain(vector<int>& indexVariables, int index) {
    bool result = false;
    for (int i = 0; i < indexVariables.size(); i++) {
        if (indexVariables[i] == index)
            result = true;
    }
    return result;
}

void swapColumns(vector<vector<pair<int, int>>>& matrix, int col1, int col2) {
    int rows = matrix.size();
    for (int i = 0; i < rows; i++) {
        swap(matrix[i][col1], matrix[i][col2]);
    }
}

void outputMatrix(const vector<vector<pair<int, int>>>& matrix, vector<int>& indexBasicVariables) {
    cout << "Index variables from 0:\n";
    for (auto element : indexBasicVariables)
        cout << element << " ";
    cout << "\n";
    cout << "The matrix looks like:\n";
    for (const auto& row : matrix) {
        for (const auto& element : row) {
            cout << element.first;
            if (element.first != 0) {
                if (element.second != 1)
                    cout << "/" << element.second;
            }
            cout << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}
