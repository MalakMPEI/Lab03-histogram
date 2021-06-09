#include "svg.h"



Test make_info_text()
{

    Test inform;
    //stringstream buffer;
    DWORD WINAPI GetVersion(void);
    DWORD info = 0;
    info = GetVersion();
    printf("n = %08x\n",info); //16
    printf("%u ", info);//10
    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = info & mask;
    //cerr << " "<<version<<endl;
    DWORD mask1 = 0x0000ffff;
    DWORD platform = info >> 16;

    DWORD maskVision = 0b00000000'11111111;

    inform.version_major = version & maskVision;
    DWORD mask2 = 0x0000ffff;
    inform.version_minor = version >> 8;
    if ((info & 0x1000ffff) == 0)
    {
        inform.version_major = 0;
    }
    inform.build = platform;

    //cout<<"<Wndows v.'"<<inform.version_major<<"'.'"<<inform.version_minor<<"' (build '"<<inform.build<<"') />";

    LPSTR   x;
    LPDWORD y;
            char system_dir[MAX_PATH];
    //inform.name =(DWORD)GetComputerNameA(system_dir, MAX_PATH)
    inform.name = GetSystemDirectory(system_dir, MAX_PATH);

    //printf("System directory: %s", system_dir);
    //cout << "< Computer name: '" << GetComputerNameA(x,y) << "'/>";
    return inform;
}




void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}


void svg_end()
{
    cout << "</svg>\n";
}

void svg_rect(double x, double y, double width, double height, string stroke, string fill)
{
    cout <<"<rect x='"<<x<<"' y='"<<y<<"' width='"<<width<<"' height='"<<height<<"' stroke='"<<stroke<<"' fill='"<<fill<<"' />";
}

void svg_text(double left, double baseline, string text)
{
   cout << "<text x='" << left << "' y='" << baseline << "'>" <<text<< "</text>";


}

void show_histogram_svg(vector<size_t> bins,vector<size_t> p)
{
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    int z=0;
    string per = "%";








    for (size_t bin : bins)
    {

    const double bin_width = BLOCK_WIDTH * bin;



/*
    size_t bin_max = 0;
    for(int i = 0; i<bins.size();i++)
    {


        if (bins[i]>bin_max) bin_max = bins[i];
    }

    if (bin_max>(76-5)) bin_width = (76 - 5)*(static_cast<double>(bin) / bins_max)

*/

    svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
    svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT,"red","#ffeeee");

    svg_text(IMAGE_WIDTH-50,top + TEXT_BASELINE,to_string(p[z]));
    svg_text(IMAGE_WIDTH-30,top + TEXT_BASELINE,per);
    top += BIN_HEIGHT;
    z++;
    }
    string windows ="Windows v ";
    string point = ".";
    string build1 = "(build ";
    string build2 = ")";
    string Computer = "Computer name: ";

    top += BIN_HEIGHT;
    Test info;
    info = make_info_text();
    svg_text(TEXT_LEFT, top + TEXT_BASELINE,windows);
    svg_text(TEXT_LEFT+75, top + TEXT_BASELINE,to_string(info.version_major));
    svg_text(TEXT_LEFT+85, top + TEXT_BASELINE,point);
    svg_text(TEXT_LEFT+90, top + TEXT_BASELINE,to_string(info.version_minor));
    svg_text(TEXT_LEFT+100, top + TEXT_BASELINE,build1);
    svg_text(TEXT_LEFT+140, top + TEXT_BASELINE,to_string(info.build));
    svg_text(TEXT_LEFT+172, top + TEXT_BASELINE,build2);


    top += BIN_HEIGHT;
    svg_text(TEXT_LEFT, top + TEXT_BASELINE,Computer);
    svg_text(TEXT_LEFT+110, top + TEXT_BASELINE,to_string(info.name));


    svg_end();
}
