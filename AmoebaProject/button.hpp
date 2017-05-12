#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED
#include "graphics.hpp"
#include "string"

using namespace genv;
using namespace std;

///A kulonbozo widgeteknel hasznalt gombok kozos tulajdonsagai, funkcioi miatt inkabb egy kulon osztalyt hoztam letre:

class Button {

public:
    int x, y, w, h;
    string title;
    Button(int bx, int by, int bw, int bh, string btitle);
    virtual bool is_contain(int mx, int my) const;
    virtual bool is_clicked(genv::event ev) const;
    virtual void moving(int newx, int newy);
    virtual void draw () const;
    virtual void draw (int br, int bg, int bb) const;

};



#endif // BUTTON_HPP_INCLUDED
