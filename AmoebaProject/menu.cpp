#include "menu.hpp"
#include "graphics.hpp"
#include "button.hpp"
#include "string"

using namespace genv;

MenuWidget::MenuWidget(int mx, int my, int mw, int mh, vector<string> m_options)
    : Widget(mx, my, mw, mh)
{
    options=m_options;
    for( int i=0; i<max_btn_number; i++)
    {
        buttons.push_back(new Button(x, y+i*btnheight+headerheight, size_x, btnheight, ""));
    }

    int btn_number = get_btn_number();

    size_y=btn_number*btnheight+headerheight+20;
}
void MenuWidget::rajzol() const
{

    int b=50;
    int btn_number = get_btn_number();

    gout << move_to(x, y+20) << color(100, b, 255) << box(size_x, headerheight) << move_to(x+55, y+35) << color(0,0, 0) << text("MENU");
    gout << color(100, b, 255) << move_to(x, y) << box(size_x, 20);
    gout << move_to(x+3, y+3) << color(50, 50, 50) << box(size_x-6, 17 );

    gout << color(150,150,255) << move_to(x+5, y+3+gout.cascent()) << text(new_option) << refresh;
    for( int i=0; i<btn_number; i++)
    {
        buttons[i]->moving(x, y+i*btnheight+headerheight+20);
        buttons[i]->title=options[i+scroll_index];
        buttons[i]->rajzol();
    }
    if(selected_index!=-1 && selected_index-scroll_index>=0 && selected_index-scroll_index<max_btn_number)
    {
        buttons[selected_index-scroll_index]->rajzol(255, 0,0 );
    }


}

void MenuWidget::kezel(event ev)
    {

        int btn_number = get_btn_number();
        for(int i=0; i<btn_number; i++)
        {
            if(buttons[i]->is_clicked(ev))
            {
                selected_index=i+scroll_index;

            }
        }
        if(ev.type==ev_mouse && ev.button==btn_wheeldown && options.size()>=max_btn_number && scroll_index+max_btn_number<options.size())
        {
            scroll_index+=1;
        }
        if(ev.type==ev_mouse && ev.button==btn_wheelup && scroll_index>=1)
        {
            scroll_index-=1;
        }

        if ( ev.type == ev_key && ev.keycode >= 32 && ev.keycode <= 162)
    {

        new_option = new_option + (char)ev.keycode;

    }
    if ((ev.keycode == key_backspace && new_option.length() != 0 )|| new_option.length()>10)
    {
        new_option.resize(new_option.length()-1);
    }
    if (ev.keycode == key_enter && new_option.length()>0)
    {
        options.push_back(new_option);
        new_option.clear();
        int btn_number=get_btn_number();
        size_y=btn_number*btnheight+headerheight+20;
    }
    }
string MenuWidget::get_selected_option() const
    {
        if(selected_index>=0 && selected_index<=options.size())
        {
            return options[selected_index];
        }

        return "none";
    }
    int MenuWidget::get_btn_number() const
    {
        int btn_number;

        if(options.size()<=max_btn_number)
        {
            btn_number=options.size();

        }
        else btn_number=max_btn_number;

        return btn_number;

    }

    string MenuWidget::get_status() const
    {
        string s;
        s ="Selected option: " + get_selected_option();
        return s;
    }
