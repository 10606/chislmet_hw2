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
        double _legend_x = 1.49,
        double _legend_y = 1.79,
        std::pair <size_t, size_t> _size_picture = {1280, 720}
    );

    visualization & add (method_type method, std::string method_name);

    visualization & add 
    (
        method_type method, 
        std::string method_name,
        
        double _u,
        double _cappa,
        std::function <double (double)> const & _T_t0_values,
        std::function <double (double)> const & _T_xa_values,
        std::function <double (double)> const & _T_xb_values
    );
    
private:

    static void calc_xab_t0_x
    (
        std::vector <double> & _T_t0_values,
        std::vector <double> & _T_xa_values,
        std::vector <double> & _T_xb_values,
        std::vector <std::vector <double> > & x, //[x][t]
        double _delta_x,
        double _delta_t,
        std::pair <double, double> x_range,
        std::pair <double, double> t_range,
        std::function <double (double)> const & f_T_t0_values,
        std::function <double (double)> const & f_T_xa_values,
        std::function <double (double)> const & f_T_xb_values
    );

    static std::string format (double value, size_t precision, size_t width);

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
