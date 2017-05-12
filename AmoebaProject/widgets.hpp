#ifndef WIDGETS_HPP_INCLUDED
#define WIDGETS_HPP_INCLUDED

#include "graphics.hpp"
#include "string"
#include "iostream"
using namespace std;


///Widget ososztaly

class Widget {
protected:
    int x, y, size_x, size_y;
    bool active;
    bool canmove;
    int dist_x, dist_y, click_x, click_y;
public:
    Widget(int a, int b, int size_a, int size_b);
    virtual void set_active(int mouse_x, int mouse_y);
    virtual bool get_active();
    virtual void mozgat (int mouse_a, int mouse_b, genv::event ev);
    virtual void rajzol() const;
    virtual void kezel (genv::event ev);
    virtual string get_status() const;
};

#endif // WIDGETS_HPP_INCLUDED
