#include "sistem.hpp"
void Namespace_box::sistem::do_sistem(int sum_small, int sum_big, int seed)
{   
    srand(seed);
    for (int i=0; i < sum_small; i++)
    {   
        particle* a = nullptr;
        while(a == nullptr)
        {
            double ra = SMALL_RADIUS;
            double x_time = rand() % BOUND_RIGHT;
            double y_time = rand() % BOUND_DOWN;
            a= new small_particle(x_time, y_time, rand() % MAX_velocity_x, rand() % MAX_velocity_y);//small_particle(2, 3);
            a->update();
            for (int i = 0; i< container.size(); i++)
            {
                if (a->check_collision(container[i]))
                {
                    delete a;
                    a = nullptr;
                    break;
                };
            }
        }
        container.push_back(a);
    }

    for (int i=0; i < sum_big; i++)
    {   
        particle* a = nullptr;

        while(a == nullptr)
        {
            double ra = rand() % MAX_radius;
            double x_time = rand() % BOUND_RIGHT;
            double y_time = rand() % BOUND_DOWN;
            a= new big_particle(x_time, y_time, ra, rand() % MAX_MASS, rand() % MAX_velocity_x, rand() % MAX_velocity_y); //big_particle(),
            a->update();
            for (int i = 0; i< container.size(); i++)
            {
                if (a->check_collision(container[i]))
                {
                    delete a;
                    a = nullptr;
                    break;
                };
            }
        }
        container.push_back(a);

    }

}
void Namespace_box::sistem::do_index_null()
{
    index = 0;
}
Namespace_box::particle* Namespace_box::sistem::return_particle()
{   
    
    if (index >= container.size())
        return nullptr;
    return container[(index)++];
}
void Namespace_box::sistem::update()
{
    for (int i = 0; i < container.size(); ++i)
    {   
	    particle* a = container[i];
        for (int k = 0; k < container.size(); ++k)
        {   
            particle* b = container[k];
            if (a->check_collision(b))
                a->do_collision(b);
        }
        a->update();
    }
}
Namespace_box::particle *Namespace_box::sistem::return_last_particle()
{
    return (container[container.size() - 1]);
}
void Namespace_box::sistem::delite_particle(int number)
{
    container.erase(container.begin() + number);
}