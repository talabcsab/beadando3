#include "graphics.hpp"
#include "string"
#include "button.hpp"
using namespace std;
using namespace genv;


    Button::Button(int bx, int by, int bw, int bh, string btitle)
     : Widget(bx, by, bw, bh)

    {


        title=btitle;
    }
    bool Button::is_contain(int mx, int my) const
    {
       return mx>x && mx<(x+size_x) && my>y && my<(y+size_y);
    }
    bool Button::is_clicked(genv::event ev) const
    {
        return ev.type==ev_mouse && ev.button==btn_left && is_contain(ev.pos_x, ev.pos_y);
    }
    void Button::rajzol() const
    {
        rajzol(220,220,220);
    }


    void Button::rajzol(int br, int bg, int bb) const {
        gout << move_to(x, y) << color(br, bg, bb) << box(size_x, size_y)
         << move_to(x+1, y+1) << color(255,250,250) << box(size_x-2, size_y-2)
         << move_to(x+11, y+20)<< color (0,0,255)<< text(title);
    }
    void Button::moving(int newx, int newy)
    {
        x=newx;
        y=newy;
    }
