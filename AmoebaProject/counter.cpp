#include "counter.hpp"
#include "graphics.hpp"
#include <strstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;
using namespace genv;

    CounterWidget::CounterWidget(int cx, int cy, int cinitialvalue, int cminrange, int cmaxrange, int cstep)
    : Widget(cx, cy, 100, 50)
    {
        value=cinitialvalue;
        minrange=cminrange;
        maxrange=cmaxrange;
        step=cstep;
        up= new Button(cx+70, cy, 30, 30, "+");
        down= new Button(cx+70, cy+25, 30, 25, "-");
    }

    void CounterWidget::mozgat(int mouse_a, int mouse_b, genv::event ev)
    {
        Widget::mozgat(mouse_a, mouse_b, ev);
        up->moving(x+70, y);
        down->moving(x+70, y+25);


    }

    void CounterWidget::rajzol() const
    {
        int b=50;
        if(active) b=250;
        gout << move_to(x, y) << color(100,b,255) << box(size_x, size_y)
             << move_to(x+5, y+5) << color(50,50,50) << box(size_x-30, size_y-10)
             << move_to(x+size_x-20, y+20) << color (255, 0,0);

        stringstream temp;
        string s;
        temp << value;
        s = temp.str();
        gout << move_to(x+20, y+30)<< color (250,250,255)<< text(s);

        up->draw(100,b,255);
        down->draw(100,b,255);

        gout << refresh;
    }
    void CounterWidget::kezel(genv::event ev)
    {
        if(ev.keycode==key_up || up->is_clicked(ev)){
            setvalue(value+step);
        }
        if(ev.keycode==key_down ||down->is_clicked(ev)){
            setvalue(value-step);
        }
        if (ev.keycode==key_pgdn)
        {
            setvalue(minrange);
        }
        if (ev.keycode==key_pgup)
        {
            setvalue(maxrange);
        }
    }
    int CounterWidget::getvalue()
    {
        return value;
    }
    void CounterWidget::setvalue(int newvalue)
    {
        if(newvalue>maxrange || newvalue<minrange)
        {
            return;
        }
        value=newvalue;
    }


string CounterWidget::get_status() const
{
       stringstream temp;
       string s;
      temp << "Current value: " <<value;
      s = temp.str();
        return s;
}
