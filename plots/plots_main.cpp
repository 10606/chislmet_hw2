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
    double u = 2.79;
    double cappa = 18.7;
    std::pair <double, double> x_range = {1., 66.};
    std::pair <double, double> t_range = {1., 72.}; 
    std::function <double (double)> T_t0_values = T_sin(2., 5., 1.);
    std::function <double (double)> T_xa_values = T_sin(2., 1., 9.);
    std::function <double (double)> T_xb_values = T_sin(1., 4., 1.);

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
        
        "../pictures/exapmle-"
    );

    vis.add(implicit_forward_flow,  "implicit_forward");
    vis.add(implicit_backward_flow, "implicit_backward");
    vis.add(explicit_forward_flow,  "explicit_forward");
    vis.add(explicit_backward_flow, "explicit_backward");
    vis.add(cheharda,               "cheharda");
}

