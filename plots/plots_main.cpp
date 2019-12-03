#include "visualization.h"
#include "../methods/implicit_forward_flow.h"
#include "../methods/explicit_forward_flow.h"
#include "../methods/implicit_backward_flow.h"
#include "../methods/explicit_backward_flow.h"
#include "../methods/cheharda.h"
#include "../methods/fake_method_copy.h"
#include "../methods/method_utils.h"
#include "../methods/predictor_corrector.h"

int main ()
{
    visualization vis
    (
        Params(),
        
        {"pictures/T_z_", "t", "T", "z", plots_params::soft(1)},
        {"pictures/T_t_", "z", "T", "t", plots_params::soft(20000)},
        {"pictures/X_z_", "t", "X", "z", plots_params::soft(1)},
        {"pictures/X_t_", "z", "X", "t", plots_params::soft(20000)}
    );

    vis.add(solve,  "");
}
