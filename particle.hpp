#ifndef _particle_H
#define _particle_H
#include "constans.hpp"
namespace Namespace_box{
    class particle {
        private:
            double radius;
            double mass;
            double x, y;
            double dx, dy;
        public:
            particle(double width, double height,double radiuss, double mas, double speed_x, double speed_y);
            double get_particle_radius();
            double get_particle_width();
            double get_particle_heigh();
            virtual void update();
            bool check_collision( particle* b );
            void do_collision(particle* b);
    };

    class big_particle: public particle {
        public:
            big_particle(double width, double height,double radiuss, double mas, double speed_x, double speed_y);
    };

    class small_particle: public particle {
        public:
            small_particle(double width, double height, double speed_x, double speed_y);
    };

};
#endif