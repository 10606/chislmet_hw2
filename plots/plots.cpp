#include "plots.h"

make_plot::make_plot
(
    std::string _name,
    std::string _file_name,
    std::pair <double, double> range_x,
    std::pair <double, double> range_y,
    std::string _axis_x,
    std::string _axis_y,
    bool _has_legend,
    double _legend_x,
    double _legend_y,
    std::pair <size_t, size_t> size_picture
) :
    gr(),
    name(_name),
    file_name(_file_name),
    axis_x(_axis_x),
    axis_y(_axis_y),
    has_legend(_has_legend),
    legend_x(_legend_x),
    legend_y(_legend_y)
{
    gr.SetSize(size_picture.first, size_picture.second);
    gr.SetFontSize(3.0);
    gr.Title(name.c_str());
    gr.SetFontSize(2.0);

    gr.SetRange('x', range_x.first, range_x.second);
    gr.SetRange('y', range_y.first, range_y.second);

    //gr.SetQuality(MGL_DRAW_FAST);
    //std::cout << "quality == " << gr.GetQuality() << std::endl;

    gr.Adjust();
    gr.Axis("xy6f");

}

void make_plot::add
(
    std::vector <double> const & x,
    std::vector <double> const & y,
    std::string const & plot_color,
    std::string const & legend_f_name
)
{
    if (legend_f_name != "")
    {
        legend.push_back({plot_color, legend_f_name});
    }
    plot_from_dots(x, y, plot_color);
}


make_plot::~make_plot ()
{
    gr.SetFunc("", "");
    gr.SetFontSize(4.0);

    if (has_legend)
    {
        for (size_t i = 0; i != legend.size(); ++i)
        {
            gr.AddLegend(legend[i].second.c_str(), legend[i].first.c_str());
        }
        gr.Legend(legend_x, legend_y);
    }

    gr.Label('x', axis_x.c_str());
    gr.Label('y', axis_y.c_str());

    gr.WriteFrame((file_name + ".png").c_str());
}


void make_plot::plot_from_dots
(
    std::vector <double> const & a,
    std::vector <double> const & b,
    std::string color
)
{
    mglData points_a(a.size()), points_b(a.size()), points_c(a.size());
    for (size_t i = 0; i != a.size(); ++i)
    {
        points_a.a[i] = a[i];
        points_b.a[i] = b[i];
    }
    gr.Plot(points_a, points_b, points_c, color.c_str());
    gr.Dots(points_a, points_b, points_c, color.c_str());
}
