#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "calc_min_max_and_draw_plots.h"
#include "../methods/predictor_corrector.h"
#include "../utils.h"
#include <vector>
#include <functional>
#include <string>

struct plots_params
{
    std::string file_name;
    std::string axix_x_name;
    std::string axix_y_name;
    std::string axix_t_name;


    struct soft
    {
        soft
        (
            size_t _step = 1,
            double _legend_x = 1.49,
            double _legend_y = 1.79,
            std::pair <size_t, size_t> _size_picture = {1280, 720},
            std::pair <double, double> _hard_border_x =
                {- std::numeric_limits <double> :: infinity(), std::numeric_limits <double> :: infinity()},
            std::pair <double, double> _hard_border_y = 
                {- std::numeric_limits <double> :: infinity(), std::numeric_limits <double> :: infinity()}
        );
    
        double legend_x;
        double legend_y;
        std::pair <size_t, size_t> size_picture;
        std::pair <double, double> hard_border_x;
        std::pair <double, double> hard_border_y;
        size_t step;
    } soft_params;

    plots_params 
    (
        std::string _file_name, 
        std::string _axix_x_name,
        std::string _axix_y_name,
        std::string _axix_t_name,
        soft _soft_params = soft()
    );
};

struct visualization
{
    visualization 
    (
        Params const & _args,
        
        plots_params T_z_params,
        plots_params T_t_params,
        plots_params X_z_params,
        plots_params X_t_params
    );

    visualization & add (std::function <Solution (Params const &)> method, std::string method_name);

    visualization & add 
    (
        std::function <Solution (Params const &)> method, 
        std::string method_name,
        
        Params const & _args
    );
    
private:

    static size_t get_len (double delta, std::pair <double, double> range);
    
    static double get_pos (size_t index, double delta, std::pair <double, double> range);
    
    static std::string format (double value, size_t precision, size_t width);

    static std::vector <std::string> gen_names (std::string name, double delta_t, std::pair <double, double> t_range);

    draw_plots plots_T_z;
    draw_plots plots_T_t;
    draw_plots plots_X_z;
    draw_plots plots_X_t;

    Params args;
    std::vector <std::vector <double> > z; //[z][t]
    std::vector <std::vector <double> > t; //[z][t]
};

#endif
