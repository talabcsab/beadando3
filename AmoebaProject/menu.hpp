#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include "button.hpp"
#include "string"
#include "vector"

using namespace std;
using namespace genv;

///Menu widget osztalya, szinten a Widget subclass-a.

class MenuWidget: public Widget {
protected:
    vector<string> options;
    vector<Button*> buttons;
    int headerheight=20;
    int btnheight=30;
    int max_btn_number=4;
    int selected_index=0;
    int scroll_index=0;
    int get_btn_number() const;

public:
    string new_option;

    MenuWidget(int mx, int my, int mw, int mh, vector<string> m_options);
    virtual void rajzol() const;
    virtual void kezel(genv::event ev);
    virtual string get_selected_option() const;
    virtual string get_status() const;
};

#endif // MENU_HPP_INCLUDED
