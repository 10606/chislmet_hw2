#include "visualization.h"

#include "calc_min_max_and_draw_plots.h"
#include "../methods/predictor_corrector.h"
#include "../methods/method_utils.h"
#include <sstream>
#include <iomanip>

size_t visualization::get_len (double delta, std::pair <double, double> range)
{
    return (delta + range.second - range.first) / delta;
}

double visualization::get_pos (size_t index, double delta, std::pair <double, double> range)
{
    return range.first + static_cast <double> (index) * delta;
}


std::string visualization::format (double value, size_t precision = 5, size_t width = 10)
{
    std::stringstream ss;
    ss.precision(precision);
    ss << std::setw(width) << std::fixed << value;

    return ss.str();
}

std::vector <std::string> visualization::gen_names (std::string name, double delta_t, std::pair <double, double> t_range)
{
    size_t t_size = get_len(delta_t, t_range);
    std::vector <std::string> t_names;
    for (size_t cur_t = 0; cur_t != t_size; ++cur_t)
    {
        double t_value = get_pos(cur_t, delta_t, t_range);
        t_names.push_back(name + format(t_value));
    }
    return t_names;
}

plots_params::soft::soft
(
    size_t _step,
    double _legend_x,
    double _legend_y,
    std::pair <size_t, size_t> _size_picture,
    std::pair <double, double> _hard_border_x,
    std::pair <double, double> _hard_border_y
) :
    legend_x(_legend_x),
    legend_y(_legend_y),
    size_picture(_size_picture),
    hard_border_x(_hard_border_x),
    hard_border_y(_hard_border_y),
    step(_step)
{}

plots_params::plots_params 
(
    std::string _file_name, 
    std::string _axix_x_name,
    std::string _axix_y_name,
    std::string _axix_t_name,
    soft _soft_params
) :
    file_name(_file_name),
    axix_x_name(_axix_x_name),
    axix_y_name(_axix_y_name),
    axix_t_name(_axix_t_name),
    soft_params(_soft_params)
{}

visualization::visualization 
(
    Params const & _args,
        
    plots_params T_z_params,
    plots_params T_t_params,
    plots_params X_z_params,
    plots_params X_t_params
) :
    plots_T_z
    (
        gen_names(T_z_params.axix_t_name, _args.delta_z, {0, _args.max_z}), 
        T_z_params.file_name, 
        T_z_params.axix_x_name,
        T_z_params.axix_y_name,
        1,
        T_z_params.soft_params.legend_x,
        T_z_params.soft_params.legend_y,
        T_z_params.soft_params.size_picture,
        T_z_params.soft_params.hard_border_x,
        T_z_params.soft_params.hard_border_y,
        T_z_params.soft_params.step
    ),
    
    plots_T_t
    (
        gen_names(T_t_params.axix_t_name, _args.delta_t, {0, _args.max_t}), 
        T_t_params.file_name, 
        T_t_params.axix_x_name,
        T_t_params.axix_y_name,
        1,
        T_t_params.soft_params.legend_x,
        T_t_params.soft_params.legend_y,
        T_t_params.soft_params.size_picture,
        T_t_params.soft_params.hard_border_x,
        T_t_params.soft_params.hard_border_y,
        T_t_params.soft_params.step
    ),
    
    plots_X_z
    (
        gen_names(X_z_params.axix_t_name, _args.delta_z, {0, _args.max_z}), 
        X_z_params.file_name, 
        X_z_params.axix_x_name,
        X_z_params.axix_y_name,
        1,
        X_z_params.soft_params.legend_x,
        X_z_params.soft_params.legend_y,
        X_z_params.soft_params.size_picture,
        X_z_params.soft_params.hard_border_x,
        X_z_params.soft_params.hard_border_y,
        X_z_params.soft_params.step
    ),
    
    plots_X_t
    (
        gen_names(X_t_params.axix_t_name, _args.delta_t, {0, _args.max_t}), 
        X_t_params.file_name, 
        X_t_params.axix_x_name,
        X_t_params.axix_y_name,
        1,
        X_t_params.soft_params.legend_x,
        X_t_params.soft_params.legend_y,
        X_t_params.soft_params.size_picture,
        X_t_params.soft_params.hard_border_x,
        X_t_params.soft_params.hard_border_y,
        X_t_params.soft_params.step
    ),
 
    args(_args),
    
    z(get_len(args.delta_z, {0, args.max_z}), std::vector <double> (get_len(args.delta_t, {0, args.max_t}))),
    t(get_len(args.delta_z, {0, args.max_z}), std::vector <double> (get_len(args.delta_t, {0, args.max_t})))
{
    for (size_t i = 0; i != z.size(); ++i)
    {
        for (size_t j = 0; j != z[i].size(); ++j)
        {
            z[i][j] = get_pos(i, args.delta_z, {0, args.max_z});
            t[i][j] = get_pos(j, args.delta_t, {0, args.max_t});
        }
    }
}

visualization & visualization::add (std::function <Solution (Params const &)> method, std::string method_name)
{

    Solution solution = method(args);

    std::cout << solution.T.size() << " " << z.size() << "\n";
    std::cout << solution.X.size() << " " << z.size() << "\n";
    
    std::cout << solution.T[0].size() << " " << z[0].size() << "\n";
    std::cout << solution.X[0].size() << " " << z[0].size() << "\n";
    
    plots_T_t.add
    (
        z, 
        solution.T,
        method_name
    );
    
    plots_T_z.add
    (
        transponse(t), 
        transponse(solution.T),
        method_name
    );
    
    plots_X_t.add
    (
        z, 
        solution.X,
        method_name
    );
    
    plots_X_z.add
    (
        transponse(t), 
        transponse(solution.X),
        method_name
    );
    
    return * this;
}


visualization & visualization::add 
(
    std::function <Solution (Params const &)> method, 
    std::string method_name,
        
    Params const & _args
)
{
    Solution solution = method(_args);
    
    plots_T_z.add
    (
        z, 
        solution.T,
        method_name
    );
    
    plots_T_t.add
    (
        t, 
        transponse(solution.T),
        method_name
    );
    
    plots_X_z.add
    (
        z, 
        solution.X,
        method_name
    );
    
    plots_X_t.add
    (
        t, 
        transponse(solution.X),
        method_name
    );
    
    return * this;
}

