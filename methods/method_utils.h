#ifndef METHOD_UTILS_H
#define METHOD_UTILS_H

#include <vector>

template <typename T>
struct quard 
{
    T a, b, c, d;
};

std::vector <double> solve_3_diag (std::vector <quard <double> > const & values);

inline size_t get_size (std::pair <double, double> range, double delta) noexcept
{
    return (delta + range.second - range.first) / delta;
}

inline void fill_0_column (std::vector <std::vector <double> > & dst, std::vector <double> const & src)
{
    for (size_t i = 0; i != dst.size(); ++i)
    {
        dst[i][0] = src[i];
    }
}


inline double calc_r (double, double cappa, double delta_x, double delta_t) noexcept
{
    return cappa * delta_t / (delta_x * delta_x);
}

inline double calc_s (double u, double,     double delta_x, double delta_t) noexcept
{
    return u * delta_t / delta_x;
}

inline double calc_cappa (double, double r, double delta_x, double delta_t) noexcept
{
    return r * (delta_x * delta_x) / delta_t;
}

inline double calc_u (double s, double,     double delta_x, double delta_t) noexcept
{
    return s * delta_x / delta_t;
}

#endif
