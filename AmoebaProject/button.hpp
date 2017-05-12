#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED
#include "graphics.hpp"
#include "string"
#include "widgets.hpp"

using namespace genv;
using namespace std;


class Button: public Widget {
protected:
        string title;



public:

    Button(int bx, int by, int bw, int bh, string btitle);
    virtual bool is_contain(int mx, int my) const;
    virtual bool is_clicked(genv::event ev) const;
    virtual void moving(int newx, int newy);
    virtual void rajzol () const;
    virtual void rajzol (int br, int bg, int bb) const;

};



#endif // BUTTON_HPP_INCLUDED
