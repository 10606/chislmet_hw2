#include "images_generator.h"

int main ()
{
    double delta_x = 0.1;
    double delta_t = 0.1;
    double u = 0.279;
    double cappa = 0.187;
    std::pair <double, double> x_range = {1., 25.};
    std::pair <double, double> t_range = {0., 200.};
    generate_images(delta_x, delta_t, u, cappa, x_range, t_range, "11001");
}
