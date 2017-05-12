#include "field_button.hpp"
#include <strstream>
#include <sstream>
#include <string>
#include <iostream>


FieldButton::FieldButton(int f_x, int f_y)
 :Button(f_x, f_y, 30, 30, "")
 {

 }

void FieldButton::set_user_id(int _user_id)
{
    user_id=_user_id;
    if(user_id==1) title="X";
    if(user_id==2) title="O";
    if(user_id==0) title="";
}
    string FieldButton::get_status() const
    {
        stringstream temp;
        temp << "(" << x << "," << y << ") - ui: " << user_id ;
        return temp.str();
    }

bool FieldButton::can_be_clicked() const
{
    if(user_id>0)
        {
            return false;
        }
    else return true;
}
