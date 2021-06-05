#include "histogram.h"


void find_minmax(const vector<double>& numbers, double& min, double& max)
{   if (numbers.size()!=0)
{
    max=numbers[0];
    min=numbers[0];

    for(double elem:numbers)
    {
        if (elem<min)
            min=elem;
        if (elem>max)

            max=elem;
    }
}
}
/*
void percent(vector<size_t> bins,vector <double> data.numbers, vector<size_t> &p)
{
    auto number_count = data.numbers.size();
    p.resize(number_count);
    for (int i=0; i<(number_count-1);i++)
    {
        p[i] = (bins[i]*100/number_count);
    }


}
*/
