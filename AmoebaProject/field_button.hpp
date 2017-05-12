#ifndef FIELD_BUTTON_HPP_INCLUDED
#define FIELD_BUTTON_HPP_INCLUDED

#include "graphics.hpp"
#include "widgets.hpp"
#include "button.hpp"

using namespace std;
using namespace genv;

class FieldButton: public Button {
protected:
        int user_id=0;
public:

    FieldButton(int f_x, int f_y);
    virtual void set_user_id(int _user_id);
    string get_status() const;
    virtual bool can_be_clicked() const;

};

#endif // FIELD_BUTTON_HPP_INCLUDED
