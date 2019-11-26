#include "images_generator.h"
#include "start_parameters.h"
#include "../methods/implicit_forward_flow.h"
#include "../methods/explicit_forward_flow.h"
#include "../methods/implicit_backward_flow.h"
#include "../methods/explicit_backward_flow.h"
#include "../methods/cheharda.h"
#include "../methods/fake_method_copy.h"
#include "../methods/method_utils.h"

int main ()
{
    double s = 1.;
    double r = 0.;
    double delta_x = 0.1;
    double delta_t = 0.1;
    double u = calc_u(s, r, delta_x, delta_t);
    double cappa = calc_cappa(s, r, delta_x, delta_t);
    std::pair <double, double> x_range = {1., 25.};
    std::pair <double, double> t_range = {0., 100.};
    //std::function <double (double)> T_t0_values = T_rectangle(2., 3., 7., 11.);
    std::function <double (double)> T_t0_values = T_step(2., 7.);
    std::function <double (double)> T_xa_values = T_sin(2., 0.000, 1.);
    std::function <double (double)> T_xb_values = T_sin(1., 0.000, 0.);
    //generate_images(delta_x, delta_t, u, cappa, x_range, t_range, "11001", T_t0_values, T_xa_values, T_xb_values);
    visualization vis
    (
        delta_x,
        delta_t,
        u,
        cappa,
        x_range,
        t_range,
        T_t0_values,
        T_xa_values,
        T_xb_values,

        "pictures/example-",
        1.49,
        1.5,
        {1280, 720},
        {- std::numeric_limits <double> :: infinity(), std::numeric_limits <double> :: infinity()},
        {-10., 10.},
        5
    );

    vis.add(implicit_forward_flow,  "implicit\\_forward");
    //vis.add(implicit_backward_flow, "implicit\\_backward");
    //vis.add(explicit_forward_flow,  "explicit\\_forward");
    //vis.add(explicit_backward_flow, "explicit\\_backward");
    //vis.add(cheharda(fake_method_copy),         "cheharda");

    cout << "make che in plots_main\n\n";
    vis.add(cheharda(implicit_forward_flow),    "cheharda\\_if");
    //vis.add(cheharda(implicit_backward_flow),   "cheharda\\_ib");
    //vis.add(cheharda(explicit_forward_flow),    "cheharda\\_ef");
    //vis.add(cheharda(explicit_backward_flow),   "cheharda\\_eb");
}
