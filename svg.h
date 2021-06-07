#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED

#include <vector>
#include <iostream>
#include <windows.h>


using namespace std;


struct Test
{
    DWORD version_major;
    DWORD version_minor;
    DWORD build;
    DWORD name;

    //size_t number_count;
} ;

Test make_info_text();

void svg_begin(double width, double height);

void svg_end();

void svg_rect(double x, double y, double width, double height, string stroke, string fill);

void svg_text(double left, double baseline, string text);

void show_histogram_svg(vector<size_t> bins,vector<size_t> p);

int percent(vector<size_t> bins,size_t bin_count);

#endif // SVG_H_INCLUDED
