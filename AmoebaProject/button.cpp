#include "graphics.hpp"
#include "string"
#include "button.hpp"
using namespace std;
using namespace genv;


    Button::Button(int bx, int by, int bw, int bh, string btitle)
    {
     x=bx;
     y=by;
     w=bw;
     h=bh;
     title=btitle;
    }
    bool Button::is_contain(int mx, int my) const
    {
       return mx>x && mx<x+w && my>y && my<y+h;
    }
    bool Button::is_clicked(genv::event ev) const
    {
        return ev.type==ev_mouse && ev.button==btn_left && is_contain(ev.pos_x, ev.pos_y);
    }
    void Button::draw() const
    {
        draw(220,220,220);
    }


    void Button::draw (int br, int bg, int bb) const {
        gout << move_to(x, y) << color(br, bg, bb) << box(w, h)
         << move_to(x+5, y+5) << color(50,50,50) << box(w-10, h-10)
         << move_to(x+11, y+18)<< color (250,250,255)<< text(title);
    }
    void Button::moving(int newx, int newy)
    {
        x=newx;
        y=newy;
    }
