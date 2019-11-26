#include "images_generator.h"
#include "start_parameters.h"

int main ()
{
    double delta_x = 0.1;
    double delta_t = 0.1;
    double u = 0.279;
    double cappa = 0.187;
    std::pair <double, double> x_range = {1., 25.};
    std::pair <double, double> t_range = {0., 200.};

    std::function <double (double)> T_t0_values = T_step(2., 3.);
    std::function <double (double)> T_xa_values = T_sin(2., 0.000, 0.);
    std::function <double (double)> T_xb_values = T_sin(1., 0.000, 0.);

    generate_images(delta_x, delta_t, u, cappa, x_range, t_range, "11001", T_t0_values, T_xa_values, T_xb_values);
}
