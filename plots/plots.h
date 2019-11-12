#ifndef PLOTS
#define PLOTS

#include <mgl2/mgl.h>
#include <iostream>
#include <algorithm>


struct make_plot
{
    make_plot
    (
        std::string _name, 
        std::string _file_name, 
        std::pair <double, double> range_x, 
        std::pair <double, double> range_y,
        std::string _axis_x = "X",
        std::string _axis_y = "Y",
        bool _has_legend = 1,
        double _legend_x = 1.0,
        double _legend_y = 0.5,
        std::pair <size_t, size_t> size_picture = {1920, 1080}
    );
     
    void add
    (
        std::vector <double> const & x,
        std::vector <double> const & y,
        std::string const & plot_color = "b",
        std::string const & legend_f_name = ""
    );
     
    ~make_plot ();

    void plot_from_dots
    (
        std::vector <double> const & a,
        std::vector <double> const & b,
        std::string color = "r"
    );

private:
    mglGraph gr;
    std::string name;
    std::string file_name;
    std::string axis_x;
    std::string axis_y;
    bool has_legend = 1;
    double legend_x = 1.0;
    double legend_y = 0.5;
    std::vector <std::pair <std::string, std::string> > legend; //color name
};

#endif
