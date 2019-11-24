#include "visualization.h"

#include "calc_min_max_and_draw_plots.h"
#include "../methods/method_utils.h"
#include <sstream>
#include <iomanip>

std::string visualization::format (double value, size_t precision = 5, size_t width = 10)
{
    std::stringstream ss;
    ss.precision(precision);
    ss << std::setw(width) << std::fixed << value;

    return ss.str();
}

std::vector <std::string> visualization::gen_names (double delta_t, std::pair <double, double> t_range)
{
    size_t t_size = (delta_t + t_range.second - t_range.first) / delta_t;
    std::vector <std::string> t_names;
    for (size_t cur_t = 0; cur_t != t_size; ++cur_t)
    {
        double t_value = t_range.first + static_cast <double> (cur_t) * delta_t;
        t_names.push_back("t = " + format(t_value));
    }
    return t_names;
}

visualization::visualization 
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
    double _legend_x,
    double _legend_y,
    std::pair <size_t, size_t> _size_picture,
    std::pair <double, double> _hard_border_x,
    std::pair <double, double> _hard_border_y,
    size_t _step
) :
    delta_x(_delta_x),
    delta_t(_delta_t),
    u(_u),
    cappa(_cappa),
    x_range(_x_range),
    t_range(_t_range),
    T_t0_values(),
    T_xa_values(),
    T_xb_values(),
    
    plots
    (
        gen_names(delta_t, t_range), 
        _file_name, 
        "x",
        "T",
        1,
        _legend_x,
        _legend_y,
        _size_picture,
        _hard_border_x,
        _hard_border_y,
        _step
    ),
    x()
{
    visualization::calc_xab_t0_x
    (
        T_t0_values,
        T_xa_values,
        T_xb_values,
        x, //[x][t]
        delta_x,
        delta_t,
        x_range,
        t_range,
        _T_t0_values,
        _T_xa_values,
        _T_xb_values
    );
}

void visualization::calc_xab_t0_x
(
    std::vector <double> & _T_t0_values,
    std::vector <double> & _T_xa_values,
    std::vector <double> & _T_xb_values,
    std::vector <std::vector <double> > & _x, //[x][t]
    double _delta_x,
    double _delta_t,
    std::pair <double, double> _x_range,
    std::pair <double, double> _t_range,
    std::function <double (double)> const & f_T_t0_values,
    std::function <double (double)> const & f_T_xa_values,
    std::function <double (double)> const & f_T_xb_values
)
{
    size_t x_size = get_size(_x_range, _delta_x);
    size_t t_size = get_size(_t_range, _delta_t);

    _x.resize(x_size, std::vector <double> (t_size));

    for (size_t cur_t = 0; cur_t != t_size; ++cur_t)
    {
        double t_value = _t_range.first + static_cast <double> (cur_t) * _delta_t;
        _T_xa_values.push_back(f_T_xa_values(t_value));
        _T_xb_values.push_back(f_T_xb_values(t_value));
    }

    for (size_t cur_x = 0; cur_x != x_size; ++cur_x)
    {
        double x_value = _x_range.first + static_cast <double> (cur_x) * _delta_x;
        _T_t0_values.push_back(f_T_t0_values(x_value));
    }

    for (size_t cur_t = 0; cur_t != t_size; ++cur_t)
    {
        for (size_t cur_x = 0; cur_x != x_size; ++cur_x)
        {
            double x_value = _x_range.first + static_cast <double> (cur_x) * _delta_x;
            _x[cur_x][cur_t] = x_value;
        }
    }
}

visualization & visualization::add (method_type method, std::string method_name)
{
    plots.add
    (
        x, 
        method
        (
            delta_x,
            delta_t,
            u,
            cappa,
            get_size(x_range, delta_x),
            get_size(t_range, delta_t),
            T_t0_values,
            T_xa_values,
            T_xb_values
        ), 
        method_name
    );
    
    return * this;
}


visualization & visualization::add 
(
    method_type method, 
    std::string method_name,
    
    double _u,
    double _cappa,
    std::function <double (double)> const & f_T_t0_values,
    std::function <double (double)> const & f_T_xa_values,
    std::function <double (double)> const & f_T_xb_values
)
{
    std::vector <double> _T_t0_values;
    std::vector <double> _T_xa_values;
    std::vector <double> _T_xb_values;

    std::vector <std::vector <double> > _x; //[x][t]

    visualization::calc_xab_t0_x
    (
        _T_t0_values,
        _T_xa_values,
        _T_xb_values,
        _x, //[x][t]
        delta_x,
        delta_t,
        x_range,
        t_range,
        f_T_t0_values,
        f_T_xa_values,
        f_T_xb_values
    );

    plots.add
    (
        _x, 
        method
        (
            delta_x,
            delta_t,
            _u,
            _cappa,
            get_size(x_range, delta_x),
            get_size(t_range, delta_t),
            _T_t0_values,
            _T_xa_values,
            _T_xb_values
        ), 
        method_name
    );
    
    return * this;
}

