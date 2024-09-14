#include <iostream>
#include "particle.hpp"
#include "sistem.hpp"
#include "painter.hpp"
#include "constans.hpp"

int main() {
    int seed, sum_small, sum_big, time;
    std::cout<<"Enter"<<std::endl;
    std::cin>>seed>>sum_small>>sum_big;
    Namespace_box::sistem Sush;
    Sush.do_sistem(sum_small, sum_big, seed);
    Sush.do_index_null();
    Namespace_box::painter Paint(WINDOW_W, WINDOW_H,"st");
    Paint.do_sistem_in_painter(Sush);
    Paint.set_sistem(&Sush);
    Paint.show();
    return Fl::run();

}