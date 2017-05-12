#ifndef COUNTER_HPP_INCLUDED
#define COUNTER_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include "button.hpp"

///Szamlalo, a Widget subclass-a.

class CounterWidget: public Widget {
protected:

    int value, minrange, maxrange, step;
    Button* up;
    Button* down;

public:
    CounterWidget(int cx, int cy, int initialvalue, int minrange, int maxrange, int step);
    virtual void rajzol() const;
    virtual void kezel(genv::event ev);
    int getvalue();
    void setvalue(int newvalue);
    virtual void mozgat(int mouse_a, int mouse_b, genv::event ev);
    virtual string get_status() const;

};
#endif // COUNTER_HPP_INCLUDED
