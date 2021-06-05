#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED

#include <vector>

using namespace std;
struct Input {
    vector<double> numbers;
    size_t bin_count;
    //size_t number_count;
};
void find_minmax(const vector<double>& numbers, double& min, double& max);
//void percent(vector<size_t> bins,vector<double> data.numbers, vector<size_t> &p);
#endif // HISTOGRAM_H_INCLUDED
