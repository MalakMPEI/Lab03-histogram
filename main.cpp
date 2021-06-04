#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include "var.h"
#include <curl/curl.h>
using namespace std;

/*struct Input {
    vector<double> numbers;
    size_t bin_count;
};
*/

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;


vector<double> input_numbers(istream& in, size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}

Input read_input(istream& in, bool F) {

    Input data;

    if (F) cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    if (F) cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    if (F) cerr << "Enter bin count: ";
    in >> data.bin_count;

    return data;
}











vector<size_t> make_histogram(Input data)
{
    size_t number_count=data.numbers.size();
    vector<size_t> bins(data.bin_count);

    double max;
    double min;
    find_minmax(data.numbers, min, max);

    double bin_size = (max - min) / data.bin_count;
    for (size_t i = 0; i < number_count; i++)
    {

        bool found = false;
        for (size_t j = 0; (j < data.bin_count - 1) && !found; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;
            if ((lo <= data.numbers[i]) && (data.numbers[i] < hi))
            {
                bins[j]++;
                found = true;
            }
        }
        // цикл по numbers не закончился!

        if (!found)
        {
            bins[data.bin_count - 1]++;
        }

    } // конец цикла по numbers

    return bins;
}


void show_histogram_text(vector<size_t> bins, size_t bins_max)
{
    size_t bin_count = bins.size();

    size_t height;


    for (size_t i=0; i<bin_count; i++)
    {
        if (bins_max > MAX_ASTERISK)

            height = MAX_ASTERISK*(static_cast<double>(bins[i]) / bins_max);
       else height = bins[i];


        if (bins[i]<100) cout<<" ";
        if (bins[i]<10) cout<<" ";
        cout<<bins [i]<<"|";

        for(size_t j=0; j < height; j++)
        {
            cout<<"*";
        }
        cout<<endl;

    }

}





int main(int argc, char* argv[])
{
    if(argc>1)
    {
        cout<<argc<<endl;
        for (int i=0;i<argc;i++) cout<<"argv ["<<i<<"] = "<<argv[i]<<endl;
    return(0);
    }

    curl_global_init(CURL_GLOBAL_ALL);
    size_t number_count;
    size_t bin_count;


   // const auto numbers = input_numbers(cin,number_count);


   Input data = read_input(cin,true);


  /* double max;
    double min;
    find_minmax(data.numbers, min, max);
*/



   // cerr << "Enter bin count: ";
    //cin >> bin_count;

    //vector<size_t> bins(bin_count);


   // size_t bins_max;

    const auto bins = make_histogram(data);

    //show_histogram_text(bins,bins_max);
   // vector<size_t> p;
   // percent(bins, number_count,p);

    show_histogram_svg(bins);






    return 0;
}
