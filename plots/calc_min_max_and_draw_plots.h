#ifndef CALC_MIN_MAX_AND_DRAW_PLOTS_H
#define CALC_MIN_MAX_AND_DRAW_PLOTS_H

#include "plots_utils.h"
#include "plots.h"

extern const std::vector <std::string> plots_color;

struct next_step_by
{
    next_step_by (size_t _step = 1);
    size_t operator () ();

private:
    size_t cur_pos;
    size_t step;
};

struct draw_plot
{
    draw_plot
    (
        std::string _name, 
        std::string _file_name, 
        std::string _axis_x = "X",
        std::string _axis_y = "Y",
        bool _has_legend = 1,
        double _legend_x = 1.0,
        double _legend_y = 0.5,
        std::pair <size_t, size_t> _size_picture = {1920, 1080},
        std::pair <double, double> _hard_border_x = {- std::numeric_limits <double> :: infinity(), std::numeric_limits <double> :: infinity()},
        std::pair <double, double> _hard_border_y = {-100., 100.}
    );
    
    void add
    (
        std::vector <double> const & x,
        std::vector <double> const & y,
        std::string const & legend_f_name = "",
        std::string const & plot_color = ""
    );

    ~draw_plot ();
    
private:
    
    std::string name;
    std::string file_name;
    std::string axis_x;
    std::string axis_y;
    bool has_legend;
    double legend_x;
    double legend_y;
    std::pair <size_t, size_t> size_picture;
    std::pair <double, double> const hard_border_x;
    std::pair <double, double> const hard_border_y;


    size_t color_pos;
    std::vector <std::vector <double> > x_values; //[method][x]
    std::vector <std::vector <double> > y_values;
    std::vector <std::pair <std::string, std::string> > legend_names; //color name
};




struct draw_plots
{
    draw_plots
    (
        std::vector <std::string> _name, 
        std::string _file_name, 
        std::string _axis_x = "X",
        std::string _axis_y = "Y",
        bool _has_legend = 1,
        double _legend_x = 1.0,
        double _legend_y = 0.5,
        std::pair <size_t, size_t> _size_picture = {1920, 1080},
        std::pair <double, double> _hard_border_x = {- std::numeric_limits <double> :: infinity(), std::numeric_limits <double> :: infinity()},
        std::pair <double, double> _hard_border_y = {-100., 100.},
        std::function <size_t ()> _step = next_step_by(1)
    );

    void add
    (
        std::vector <std::vector <double> > const & x, //[x][t]
        std::vector <std::vector <double> > const & y,
        std::string const & legend_f_name = "",
        std::string const & plot_color = ""
    );

    ~draw_plots ();
    
private:
    
    std::vector <std::string> name;
    std::string file_name;
    std::string axis_x;
    std::string axis_y;
    bool has_legend;
    double legend_x;
    double legend_y;
    std::pair <size_t, size_t> size_picture;
    std::pair <double, double> hard_border_x;
    std::pair <double, double> hard_border_y;
    std::function <size_t ()> step;


    size_t color_pos;
    std::vector <std::vector <std::vector <double> > > x_values; //[method][t][x]
    std::vector <std::vector <std::vector <double> > > y_values;
    std::vector <std::pair <std::string, std::string> > legend_names; //color name
};

#endif
