#include "calc_min_max_and_draw_plots.h"

const std::vector <std::string> plots_color = {"b", "g", "r", "E", "c", "m", "q", "p", "k"};

draw_plot::draw_plot
(
    std::string _name, 
    std::string _file_name, 
    std::string _axis_x,
    std::string _axis_y,
    bool _has_legend,
    double _legend_x,
    double _legend_y,
    std::pair <size_t, size_t> _size_picture
) :
    name(_name),
    file_name(_file_name),
    axis_x(_axis_x),
    axis_y(_axis_y),
    has_legend(_has_legend),
    legend_x(_legend_x),
    legend_y(_legend_y),
    size_picture(_size_picture),

    color_pos(0),
    x_values(),
    y_values(),
    legend_names()
{}

void draw_plot::add
(
    std::vector <double> const & x,
    std::vector <double> const & y,
    std::string const & legend_f_name,
    std::string const & plot_color
)
{
    if (plot_color == "")
    {
        legend_names.push_back({plots_color[color_pos], legend_f_name});
        color_pos = (color_pos + 1) % plots_color.size();
    }
    else
    {
        legend_names.push_back({plot_color, legend_f_name});
    }

    x_values.push_back(x);
    y_values.push_back(y);
}

draw_plot::~draw_plot ()
{
    std::pair <double, double> range_x = get_min_max <decltype (x_values)> () (x_values);
    std::pair <double, double> range_y = get_min_max <decltype (y_values)> () (y_values);
    relax_min(range_x.first);
    relax_min(range_y.first);
    relax_max(range_x.second);
    relax_max(range_y.second);

    make_plot result
    (
        name, 
        file_name, 
        range_x, 
        range_y,
        axis_x,
        axis_y,
        has_legend,
        legend_x,
        legend_y,
        size_picture
    );

    for (size_t i = 0; i != x_values.size(); ++i)
    {
        result.add(x_values[i], y_values[i], legend_names[i].first, legend_names[i].second);
    }
}
    





draw_plots::draw_plots
(
    std::vector <std::string> _name, 
    std::string _file_name, 
    std::string _axis_x,
    std::string _axis_y,
    bool _has_legend,
    double _legend_x,
    double _legend_y,
    std::pair <size_t, size_t> _size_picture
) :
    name(_name),
    file_name(_file_name),
    axis_x(_axis_x),
    axis_y(_axis_y),
    has_legend(_has_legend),
    legend_x(_legend_x),
    legend_y(_legend_y),
    size_picture(_size_picture),

    color_pos(0),
    x_values(),
    y_values(),
    legend_names()
{}

void draw_plots::add
(
    std::vector <std::vector <double> > const & x,
    std::vector <std::vector <double> > const & y,
    std::string const & legend_f_name,
    std::string const & plot_color
)
{
    if (plot_color == "")
    {
        legend_names.push_back({plots_color[color_pos], legend_f_name});
        color_pos = (color_pos + 1) % plots_color.size();
    }
    else
    {
        legend_names.push_back({plot_color, legend_f_name});
    }

    x_values.push_back(transponse(x));
    y_values.push_back(transponse(y));
}

draw_plots::~draw_plots ()
{
    std::pair <double, double> range_x = get_min_max <decltype (x_values)> () (x_values);
    std::pair <double, double> range_y = get_min_max <decltype (y_values)> () (y_values);

    std::cout << range_x.first << " " << range_x.second << "\n";
    std::cout << range_y.first << " " << range_y.second << "\n";
    std::cout << "\n";
    
    relax_min(range_x.first);
    relax_min(range_y.first);
    relax_max(range_x.second);
    relax_max(range_y.second);

    std::cout << range_x.first << " " << range_x.second << "\n";
    std::cout << range_y.first << " " << range_y.second << "\n";
    std::cout << "\n";
    std::cout << "\n";

    if (x_values.empty())
    {
        return;
    }

    for (size_t j = 0; j != x_values[0].size(); ++j)
    {
        make_plot result
        (
            name[j], 
            file_name + std::to_string(j),
            range_x, 
            range_y,
            axis_x,
            axis_y,
            has_legend,
            legend_x,
            legend_y,
            size_picture
        );

        for (size_t i = 0; i != x_values.size(); ++i)
        {
            result.add(x_values[i][j], y_values[i][j], legend_names[i].first, legend_names[i].second);
        }
    }
}
    
