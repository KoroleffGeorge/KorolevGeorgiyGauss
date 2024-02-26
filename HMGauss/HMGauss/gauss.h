#ifndef GAUSS_H
#define GAUSS_H

#include <vector>

using  namespace std;

class Gauss {
public:
    static bool methodGauss(vector<vector<pair<int, int>>>& matrix);
private:
    static void preparation(vector<vector<pair<int, int>>>& matrix);
    static void forwardStroke(vector<vector<pair<int, int>>>& matrix);
    static bool edgeSituations(vector<vector<pair<int, int>>>& matrix, bool &many, bool &noone);
    static void reverseStroke(vector<vector<pair<int, int>>>& matrix);
    static void  reductionIdentityMatrix(vector<vector<pair<int, int>>>& matrix);
};

#endif //GAUSS_H
