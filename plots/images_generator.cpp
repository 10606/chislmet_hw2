#include "images_generator.h"
#include "visualization.h"
#include "start_parameters.h"
#include "../methods/implicit_forward_flow.h"
#include "../methods/explicit_forward_flow.h"
#include "../methods/implicit_backward_flow.h"
#include "../methods/explicit_backward_flow.h"
#include "../methods/cheharda.h"

void generate_images
(
    double delta_x,
    double delta_t,
    double u,
    double kappa,
    std::pair <double, double> x_range,
    std::pair <double, double> t_range
)
{
    std::function <double (double)> T_t0_values = T_rectangle(2., 3., 7., 11.);
    std::function <double (double)> T_xa_values = T_sin(2., 0.000, 0.);
    std::function <double (double)> T_xb_values = T_sin(1., 0.000, 0.);

    visualization vis
    (
        delta_x,
        delta_t,
        u,
        kappa,
        x_range,
        t_range,
        T_t0_values,
        T_xa_values,
        T_xb_values,

        "pictures/example-",
        1.49,
        1.5
    );

    vis.add(implicit_forward_flow,  "implicit\\_forward");
    vis.add(implicit_backward_flow, "implicit\\_backward");
    vis.add(explicit_forward_flow,  "explicit\\_forward");
    vis.add(explicit_backward_flow, "explicit\\_backward");
    vis.add(cheharda,               "cheharda");
}
