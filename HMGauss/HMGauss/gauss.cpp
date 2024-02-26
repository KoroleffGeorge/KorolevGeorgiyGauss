#include <iostream>
#include "Euclid.h"
#include "Gauss.h"
#include "Math.h"
#include <vector>

using namespace std;

bool Gauss::methodGauss(vector<vector<pair<int, int>>>& matrix) {
    bool many = false, noone = false, result = false;
    preparation(matrix);
    forwardStroke(matrix);
    result = edgeSituations(matrix, many, noone);
    if (result) {
        reverseStroke(matrix);
        reductionIdentityMatrix(matrix);
    }
    else {
        if (many) {
            cout << "The system has infinitely many solutions\n\n";
        }
        if (noone) {
            cout << "The system is not compatible\n\n";
        }
    }
    return result;
}

void Gauss::preparation(vector<vector<pair<int, int>>>& matrix) {
    unsigned long long n = matrix.size();
    unsigned long long m = matrix[0].size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (abs(matrix[i][i].first * matrix[j][i].second) < abs(matrix[j][i].first * matrix[i][i].second)) {
                for (int k = 0; k < m; k++) {
                    matrix[i][k].first =
                        matrix[i][k].first * matrix[j][k].second + matrix[j][k].first * matrix[i][k].second;
                    matrix[i][k].second *= matrix[j][k].second;
                    matrix[j][k].first =
                        matrix[i][k].first * matrix[j][k].second - matrix[j][k].first * matrix[i][k].second;
                    matrix[j][k].second *= matrix[i][k].second;
                    matrix[i][k].first =
                        matrix[i][k].first * matrix[j][k].second - matrix[j][k].first * matrix[i][k].second;
                    matrix[i][k].second *= matrix[j][k].second;
                }
            }
        }
    }
}

void Gauss::forwardStroke(vector<vector<pair<int, int>>>& matrix) {
    unsigned long long n = matrix.size();
    unsigned long long m = matrix[0].size();

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            pair<int, int> coefficient;

            coefficient.first = matrix[j][i].first * matrix[i][i].second;
            coefficient.second = matrix[j][i].second * matrix[i][i].first;

            for (int k = i; k < m; k++) {
                int numerator = coefficient.first * matrix[i][k].first;
                int denominator = coefficient.second * matrix[i][k].second;

                matrix[j][k].first = matrix[j][k].first * denominator - matrix[j][k].second * numerator;
                matrix[j][k].second *= denominator;

                int gcd = Euclid::gcd(matrix[j][k].first, matrix[j][k].second);

                matrix[j][k].first /= gcd;
                matrix[j][k].second /= gcd;
            }
        }
    }
}

bool Gauss::edgeSituations(vector<vector<pair<int, int>>>& matrix, bool& many, bool& noone) {
    unsigned long long n = matrix.size();
    unsigned long long m = matrix[0].size();
    int countZeros = 0;
    for (int i = 0; i < m - 1; i++) {
        if (matrix[n - 1][i].first == 0) {
            countZeros++;
        }
    }
    many = (countZeros == m - 1) && (matrix[n - 1][m - 1].first == 0);
    noone = (countZeros == m - 1) && (matrix[n - 1][m - 1].first != 0);
    return !(many || noone);
}

void Gauss::reverseStroke(vector<vector<pair<int, int>>>& matrix) {
    unsigned long long n = matrix.size();
    unsigned long long m = matrix[0].size();

    for (int i = n - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            pair<int, int> coefficient;

            coefficient.first = matrix[j][i].first * matrix[i][i].second;
            coefficient.second = matrix[j][i].second * matrix[i][i].first;

            for (int k = m - 1; k >= i; k--) {
                int numerator = coefficient.first * matrix[i][k].first;
                int denominator = coefficient.second * matrix[i][k].second;

                matrix[j][k].first = matrix[j][k].first * denominator - matrix[j][k].second * numerator;
                matrix[j][k].second *= denominator;
                int gcd = Euclid::gcd(matrix[j][k].first, matrix[j][k].second);
                matrix[j][k].first /= gcd;
                matrix[j][k].second /= gcd;
                if (matrix[j][k].first == 0)
                    matrix[j][k].second = 1;
            }
        }
    }
}

void Gauss::reductionIdentityMatrix(vector<vector<pair<int, int>>>& matrix) {
    unsigned long long n = matrix.size();
    unsigned long long m = matrix[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < m; j++) {
            matrix[i][j].first *= matrix[i][i].second;
            matrix[i][j].second *= matrix[i][i].first;
            int gcd = Euclid::gcd(matrix[i][j].first, matrix[i][j].second);
            matrix[i][j].first /= gcd;
            matrix[i][j].second /= gcd;
            if ((matrix[i][j].first < 0 && matrix[i][j].second < 0) || matrix[i][j].second < 0) {
                matrix[i][j].first *= -1;
                matrix[i][j].second *= -1;
            }
        }
        matrix[i][i].first = matrix[i][i].second = 1;
    }
}
