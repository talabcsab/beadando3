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
    canmove=false;
}
void Widget::set_active(int mouse_x, int mouse_y)
{

    active = mouse_x>x && mouse_x<x+size_x && mouse_y>y && mouse_y<y+size_y;

}
bool Widget::get_active()
{
    return active;
}
void Widget::mozgat (int mouse_a, int mouse_b, event ev)
{
    mouse_a=ev.pos_x;
    mouse_b=ev.pos_y;

    if(active && ev.type==ev_mouse && ev.button==btn_left)
    {
        canmove=true;
        dist_x=x-mouse_a;
        dist_y=y-mouse_b;

    }
    if(active && ev.type==ev_mouse && ev.button==-btn_left)
    {
        canmove=false;
    }
    if(canmove==true &&ev.type==ev_mouse)
    {
        gout << move_to(x,y) << color (0,0,0) <<box(size_x, size_y);
        x=mouse_a + dist_x;
        y=mouse_b + dist_y;
    }
    if (x<=0)
    {
        x=0;
    }
    if (y<=0)
    {
        y=0;
    }

    if (x>=700-size_x)
    {
        x=700-size_x;
    }

    if (y>=700-size_y)
    {
        y=700-size_y;
    }

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
