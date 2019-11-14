#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "calc_min_max_and_draw_plots.h"
#include "../utils.h"
#include <vector>
#include <functional>
#include <string>

struct visualization
{
    visualization 
    (
        double _delta_x,
        double _delta_t,
        double _u,
        double _cappa,
        std::pair <double, double> _x_range, 
        std::pair <double, double> _t_range, 
        std::function <double (double)> const & _T_t0_values,
        std::function <double (double)> const & _T_xa_values,
        std::function <double (double)> const & _T_xb_values,
        
        std::string _file_name, 
        double _legend_x = 1.0,
        double _legend_y = 0.5,
        std::pair <size_t, size_t> _size_picture = {1280, 720}
    );

    visualization & add (method_type method, std::string method_name);
    
private:

    static std::string format (double value, size_t precision);

    static std::vector <std::string> gen_names (double delta_t, std::pair <double, double> t_range);

    double delta_x;
    double delta_t;
    double u;
    double cappa;
    std::pair <double, double> x_range; 
    std::pair <double, double> t_range; 
    std::vector <double> T_t0_values;
    std::vector <double> T_xa_values;
    std::vector <double> T_xb_values;

    draw_plots plots;
    std::vector <std::vector <double> > x; //[x][t]
};

#endif
