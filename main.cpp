#include <iostream>
#include <vector>
#include "histogram.h"
#include "svg.h"
#include <curl/curl.h>
#include <sstream>
#include <string>
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

    //if (F) cerr << "Enter bin count: ";
    //in >> data.bin_count;

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



Input
download(const string& address)
{
    stringstream buffer;

    CURL* curl = curl_easy_init();



    curl_global_init(CURL_GLOBAL_ALL);


    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
         if (res != 0) cout<<res;
        curl_easy_cleanup(curl);
}


    return read_input(buffer, false);
}


size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx) {


    auto data_size = item_size * item_count;

   // stringstream* buffer = reinterpret_cast<stringstream*>(ctx);

    //static_cast<const char*>(*buffer).write(items, data_size);

    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    (*buffer).write(reinterpret_cast<char*>(&items), data_size);

    return (data_size);
}


void percent(vector<size_t> bins,Input data, vector<size_t> &p)
{
    auto number_count = data.numbers.size();
    p.resize(number_count);
    for (int i=0; i<(number_count-1);i++)
    {
        p[i] = (bins[i]*100/number_count);
    }


}


int main(size_t bin_count, int argc, char* argv[])
{
    Input data;
    data.bin_count = bin_count;
    if(argc>1)
    {
        data = download(argv[1]);
    }
    else
    {
        data = read_input(cin,true);
    }


/*
    size_t number_count;
    size_t bin_count;
    */
    const auto bins = make_histogram(data);
    vector<size_t> p;
    percent(bins,data,p);



    show_histogram_svg(bins,p);





}
