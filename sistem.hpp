#ifndef _sistem_H_
#define _sistem_H_
#include <vector>
#include <random>
#include <cstdlib>
#include "particle.hpp"
#include "constans.hpp"
namespace Namespace_box{
    class sistem
    {
        std::vector <particle *> container;
        int index; 
    public:
        void do_sistem(int sum_small, int sum_big, int seed);
        particle* return_particle();
        void do_index_null();
        void update();
        particle* return_last_particle();
        void delite_particle(int number);
    };
};

#endif 