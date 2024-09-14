#ifndef _paiter_H
#define _paiter_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Input.H>
#include <vector>
#include "particle.hpp"
#include "sistem.hpp"
namespace Namespace_box{
    class painter: public Fl_Window
    {   
        std::vector <particle *> container;
        sistem* sistem_from_sis;
        Fl_Button* button_start;
        Fl_Button* button_add;
        Fl_Button* button_delite;
        Fl_Input* input;
        Fl_Window* add;
        Fl_Button* add_small;
        Fl_Button* add_big;
        Fl_Window* delite;
        Fl_Button* delite_small;
        Fl_Button* delite_big; 
        int time_t = 0;
    public:
        painter(int w , int h , const char* s);
        void draw();
        static void timer_callback(void* data);
        void update();
        void do_sistem_in_painter(sistem v);
        void set_sistem(sistem* a);
        static void button_start_callback(Fl_Widget* widget, void* data);
        static void button_add_callback(Fl_Widget* widget, void* data);
        static void button_add_small_callback(Fl_Widget* widget, void* data);
        static void button_add_big_callback(Fl_Widget* widget, void* data);
        static void button_delite_callback(Fl_Widget* widget, void* data);
        template <class T>
        static void button_delite_particle_callback(Fl_Widget* widget, void* data);
        static void set_step_input_callback(Fl_Widget* widget, void *data);
        ~painter();
    };
}; 

#endif  