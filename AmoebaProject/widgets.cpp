#include "widgets.hpp"
#include "graphics.hpp"
using namespace genv;
Widget::Widget(int a, int b, int size_a, int size_b)
{
    x=a;
    y=b;
    size_x=size_a;
    size_y=size_b;
    active=false;
}
void Widget::set_active(int mouse_x, int mouse_y)
{

    active = mouse_x>x && mouse_x<x+size_x && mouse_y>y && mouse_y<y+size_y;

}
bool Widget::get_active()
{
    return active;
}

void Widget::rajzol() const
{

}
void Widget::kezel (genv::event ev)
{

}

string Widget::get_status() const
{

}
