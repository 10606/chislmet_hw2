#include "visualization.h"
#include "start_parameters.h"

#include "../methods/implicit_forward_flow.h"
#include "../methods/explicit_forward_flow.h"
#include "../methods/implicit_backward_flow.h"
#include "../methods/explicit_backward_flow.h"
#include "../methods/cheharda.h"

int main ()
{
    double delta_x = 0.01;
    double delta_t = 0.01;
    double u = 0.00279;
    double cappa = 0.00187;
    std::pair <double, double> x_range = {1., 25.};
    std::pair <double, double> t_range = {1., 20.};
    std::function <double (double)> T_t0_values = T_step(2., 14.);
    std::function <double (double)> T_xa_values = T_sin(2., 0.001, 19.);
    std::function <double (double)> T_xb_values = T_sin(1., 0.004, 11.);

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
        
        "pictures/example-"
    );

    vis.add(implicit_forward_flow,  "implicit\\_forward");
    //vis.add(implicit_backward_flow, "implicit\\_backward");
    //vis.add(explicit_forward_flow,  "explicit\\_forward");
    //vis.add(explicit_backward_flow, "explicit\\_backward");
    //vis.add(cheharda,               "cheharda");
}
