#include "visualization.h"
#include "../methods/implicit_forward_flow.h"
#include "../methods/explicit_forward_flow.h"
#include "../methods/implicit_backward_flow.h"
#include "../methods/explicit_backward_flow.h"
#include "../methods/cheharda.h"
#include "../methods/fake_method_copy.h"
#include "../methods/method_utils.h"
#include "../methods/predictor_corrector.h"

size_t MAX_FRAMES = 50; // approximately

int main ()
{
    Params p;
    p.delta_t = p.U() * 10000;
    p.max_t = p.delta_t * 1000;
    p.delta_z = p.deltaH() * 0.01;
    p.max_z = p.delta_z * 1000;
    p.D = 8e-12;
    p.K *= 50;
    p.alpha = 3;
    size_t z_skip = std::max(size_t(1), p.L() / MAX_FRAMES);
    size_t t_skip = std::max(size_t(1), p.N() / MAX_FRAMES);

    visualization vis
    (
        p,

        {"pictures/W_z_", "t", "-W", "z", plots_params::soft(next_step_by(z_skip), 0)},
        {"pictures/W_t_", "z", "-W", "t", plots_params::soft(next_step_by(t_skip), 0, 1.49, 1.79, {1280, 720})},
        {"pictures/T_z_", "t", "T", "z", plots_params::soft(next_step_by(z_skip), 0)},
        {"pictures/T_t_", "z", "T", "t", plots_params::soft(next_step_by(t_skip), 0)},
        {"pictures/X_z_", "t", "X", "z", plots_params::soft(next_step_by(z_skip), 0)},
        {"pictures/X_t_", "z", "X", "t", plots_params::soft(next_step_by(t_skip), 1)}
    );

    vis.add(solve,  " ");
}
