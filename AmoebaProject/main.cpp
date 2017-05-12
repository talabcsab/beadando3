#include "graphics.hpp"
#include "widgets.hpp"
#include "counter.hpp"
#include <vector>
#include <iostream>
#include "menu.hpp"
#include <string>
#include <strstream>
#include <sstream>
#include <fstream>

using namespace std;
using namespace genv;



///A szamlalo widgetek konstruktoraban megadhato parameterkent a pozcio mellett a kezdoertek, az intervallum minimum es maximumum erteke, valamint a lepeskoz.
///Iranyithato kattintassal, a fel-le gombok hasznalataval, valami a PgUp, PgDn gombok az intervallum hataraihoz allitjak a mutatott erteket.
///A kivalaszto/menu widget maximum 4 opciot jelenit meg, a tobbi gorgetessel erheto el.
///Az epp aktiv widget egy uj opcioval bovul, melyet az elozoekhez hasonloan ki lehet valasztani, ha gepelni kezdunk, majd 'Enter'-t nyomunk.
/// Minden widget huzassal athelyezheto, a 'space' billentyu lenyomasaval az epp aktualisan mutatott, ill. kivalasztott ertekek
/// a program konyvtaraban, egy "current.txt" nevu fajlba irodnak. Az aktualisan kivalasztott widget aktivitasat szinvaltozas jelzi.


void event_loop(vector<Widget*>& widgets, MenuWidget* mw1, MenuWidget* mw2) {
    event ev;

    while(gin >> ev ) {



        if(ev.type==ev_key && ev.keycode==key_space)
        {
            ofstream myfile;
            myfile.open ("current.txt");

            for (int i=0; i<widgets.size(); i++)
            {
                string temp=widgets[i]->get_status();
                myfile<<temp<< endl;
            }
            myfile.close();

        }

        if (ev.type == ev_mouse && ev.button==btn_left) {
            for (size_t i=0;i<widgets.size();i++) {
                widgets[i]->set_active(ev.pos_x, ev.pos_y);
               // widgets[i]->mozgat(ev.pos_x, ev.pos_y);
            }
        }
        for (size_t i=0;i<widgets.size();i++) {
            if (widgets[i]->get_active())
            {
                widgets[i]->kezel(ev);
                widgets[i]->mozgat(ev.pos_x, ev.pos_y, ev);
            }


            widgets[i]->rajzol();
        }
        gout << refresh;
    }
}


int main()
{
    gout.open(700,700);
    vector<Widget*> vec;
    vector<string> menu;
    menu.push_back("Option 1");
    menu.push_back("Option 2");
    menu.push_back("Option 3");
    menu.push_back("Option 4");
    menu.push_back("Option 5");
    menu.push_back("Option 6");
    menu.push_back("Option 7");
    menu.push_back("Option 8");
    vector<string> other_menu;
    other_menu.push_back("Option 1");
    other_menu.push_back("Option 2");
    CounterWidget * w1 = new CounterWidget (10, 10, 100, 10, 200, 1);
    CounterWidget * w2 = new CounterWidget (10,100, 124, 10, 200, 10);
    MenuWidget * w3 = new MenuWidget (500, 60, 100, 500, menu );
    MenuWidget * w4 =new MenuWidget (300, 60, 100, 500, other_menu);
    vec.push_back(w1);
    vec.push_back(w2);
    vec.push_back(w3);
    vec.push_back(w4);

    event_loop(vec, w3, w4);
    return 0;
}
