#ifndef PLOTS_UTILS_H
#define PLOTS_UTILS_H

#include <vector>
#include <type_traits>
#include <utility>

template <typename T>
struct pass_T_from_vectors
{
    typedef T type;
};

template <typename T>
struct pass_T_from_vectors <std::vector <T> >
{
    typedef typename pass_T_from_vectors <T> :: type type;
};


template <typename T>
struct get_min_max
{
    get_min_max ()
    {}

    std::pair <T, T> operator () (T const & values)
    {
        return {values, values};
    }
};

template <typename T>
struct get_min_max <std::vector <T> >
{
    get_min_max ()
    {}

    typedef typename pass_T_from_vectors <T> :: type type;

    std::pair <type, type> operator () (std::vector <T> const & values)
    {
        if (values.empty())
        {
            return {type(), type()};
        }
        
        std::pair <type, type> answer = get_min_max <T> () (values[0]);

        for (T const & value : values)
        {
            std::pair <type, type> min_max_in_value = get_min_max <T> () (value);

            answer.first  = std::min(answer.first,  min_max_in_value.first);
            answer.second = std::max(answer.second, min_max_in_value.second);
        }

        return answer;
    }
};

template <typename T>
std::vector <std::vector <T> > transponse (std::vector <std::vector <T> > const & values)
{
    if (values.empty())
    {
        return {};
    }

    size_t max_size = 0;
    for (size_t i = 0; i != values.size(); ++i)
    {
        max_size = std::max(max_size, values[i].size());
    }
    
    std::vector <std::vector <T> > answer(max_size, std::vector <T> (values.size()));

    for (size_t i = 0; i != values.size(); ++i)
    {
        for (size_t j = 0; j != values[i].size(); ++j)
        {
            answer[j][i] = values[i][j];
        }
    }
    
    return answer;
}

template <typename F, typename ... T>
struct apply_function
{
    apply_function (T && ... _args) :
        args(std::forward <T &&> (_args) ...)
    {}
    
    template <size_t ... n>
    typename std::result_of <F(T && ...)> :: type apply (F && f, std::integer_sequence <size_t, n ...>)
    {
        return f(std::forward <T &&> (std::get <n> (args)) ...);
    }
    
    typename std::result_of <F(T && ...)> :: type operator () (F && f)
    {
        return apply(f, std::make_index_sequence <sizeof ... (T)>());
    }
    
private:
    std::tuple <T ...> args;
};

#endif
