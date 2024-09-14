#include "painter.hpp"
#include "constans.hpp"
#include <typeinfo>
Namespace_box::painter::painter(int w, int h, const char* s): Fl_Window(w, h, s)
{
    button_start = new Fl_Button(50, 560, 100, 30, "Start");
    button_add = new Fl_Button(200, 560, 100, 30, "Add");
    button_delite = new Fl_Button(350, 560, 100, 30, "Delite");
    input = new Fl_Input(350+150,560,100,30);
    input->callback(set_step_input_callback, this);
    input->take_focus();
    
    button_start->callback(button_start_callback, this);
    button_add->callback(button_add_callback, this);
    button_delite->callback(button_delite_callback, this);
} 

void Namespace_box::painter::draw()
{   
    Fl_Window::draw();
    fl_line(BOUND_LEFT, BOUND_DOWN, BOUND_RIGHT, BOUND_DOWN);
    fl_begin_polygon();
    for (int i = 0; i<container.size(); ++i)
    {   
	    particle* a = container[i];
        if (typeid(*a) == typeid(small_particle)) 
	        fl_color(FL_RED);
        else if (typeid(*a) == typeid(big_particle)) 
            fl_color(FL_DARK_GREEN);
        else 
            fl_color(FL_YELLOW);
        fl_circle(a->get_particle_width(), a->get_particle_heigh(), a->get_particle_radius());
    }
    fl_end_polygon();
    
}
void Namespace_box::painter::timer_callback(void* data) 
	{
    	painter* self = static_cast<painter*>(data);
    	self->update();
	}
void Namespace_box::painter::update()
{
    sistem_from_sis->update();
    redraw();
    if (time_t != 0) 
    {   
        Fl::add_timeout(0.01,timer_callback, this);
        --time_t;
    }
    else 
    {
        const char* input_data = input->value();
        time_t = atoi(input_data);
    }
}
void Namespace_box::painter::set_sistem(Namespace_box::sistem *a)
{
    sistem_from_sis = a;
}

void Namespace_box::painter::do_sistem_in_painter(sistem v)
{
    v.do_index_null();
    particle* a =  v.return_particle();
    while(a)
    {
        container.push_back(a);
        a =  v.return_particle();
    }
}
void Namespace_box::painter::button_start_callback(Fl_Widget* widget, void* data)
{
    painter* obj = (painter*)data;
    obj->update();
}
 
void Namespace_box::painter::button_add_callback(Fl_Widget* widget, void *data)
{   
    painter* ob = (painter*)data;
    ob->add = new Fl_Window(200,200, "add");
    ob->add_small = new Fl_Button(10,10, 100,50,"small");
    ob->add_big = new Fl_Button(10,100, 100,50,"big");
    ob->add_small->callback(button_add_small_callback, ob);
    ob->add_big->callback(button_add_big_callback, ob);
    ob->add->show();
}

void Namespace_box::painter::button_add_small_callback(Fl_Widget* widget, void *data)
{  
    painter* ob = (painter*)data;
    (ob->sistem_from_sis)->do_sistem(1,0,rand());
    ob->container.push_back(ob->sistem_from_sis->return_last_particle());

}
void Namespace_box::painter::button_add_big_callback(Fl_Widget* widget, void *data)
{
    painter* ob = (painter*)data;
    (ob->sistem_from_sis)->do_sistem(0,1,rand());
    ob->container.push_back(ob->sistem_from_sis->return_last_particle());
}
void Namespace_box::painter::button_delite_callback(Fl_Widget* widget, void *data)
{   
    painter* ob = (painter*)data;
    ob->delite = new Fl_Window(200,200, "delite");
    ob->delite_small = new Fl_Button(10,10, 100,50,"small");
    ob->delite_big = new Fl_Button(10,100, 100,50,"big");
    ob->delite_small->callback(button_delite_particle_callback<small_particle>, ob);
    ob->delite_big->callback(button_delite_particle_callback<big_particle>, ob);
    ob->delite->show();
}
template <class T>
void Namespace_box::painter::button_delite_particle_callback(Fl_Widget* widget, void *data)
{
    painter* ob = (painter*)data;
    for(int i = 0;i<(ob->container).size();i++)
    {   
        if (typeid(*(ob->container[i])) == typeid(T))
        {   
            delete ob->container[i];
            *(ob->container).erase(ob->container.begin()+i);
            ob->sistem_from_sis->delite_particle(i);
            break;
        }
            
    }
}
void Namespace_box::painter::set_step_input_callback(Fl_Widget* widget, void *data)
{
    painter* ob = (painter*)data;
    const char* input_data = ob->input->value();
    ob->time_t = atoi(input_data);
    ob->button_start->callback(button_start_callback, ob);
}
Namespace_box::painter::~painter()
{
    delete button_start;
    delete button_add;
    delete button_delite;
    delete input;
    delete add;
    delete add_small;
    delete add_big;
    delete delite;
    delete delite_small;
    delete delite_big; 
    for (int i=0; i<container.size(); i++)
    {
        delete container[i];
    }
}
