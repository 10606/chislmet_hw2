#ifndef START_PARAMETERS_H
#define START_PARAMETERS_H

typedef double (* T_t0) (double x);
typedef double (* T_xa) (double a, double t);
typedef double (* T_xb) (double b, double t);

struct base_parameters
{
    virtual double operator () (double) = 0;
};

struct T_sin : base_parameters
{
    T_sin (double _a, double _b, double _c);
    
    virtual double operator () (double x);

private:
    double a;
    double b;
    double c;
};


#endif
