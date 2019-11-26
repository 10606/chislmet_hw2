#ifndef CHEHARDA_H
#define CHEHARDA_H

#include "../utils.h"
#include "explicit_forward_flow.h"
#include "explicit_backward_flow.h"
#include "implicit_forward_flow.h"
#include "implicit_backward_flow.h"
#include <vector>

struct cheharda 
{
    cheharda (method_type _base_method = implicit_backward_flow);

    std::vector <std::vector <double> >  // T[x][t]
    operator ()
    (
        double delta_x,
        double delta_t,
        double u,
        double cappa,
        size_t x_size, 
        size_t t_size, 
        std::vector <double> const & T_t0_values,
        std::vector <double> const & T_xa_values,
        std::vector <double> const & T_xb_values
    );
    
    method_type base_method;
};

#endif
