#include "graphics.hpp"
#include "widgets.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <strstream>
#include <sstream>
#include <fstream>
#include "field_button.hpp"
using namespace std;
using namespace genv;

int user_id=1;
int winner_user=0;

bool winning(vector<vector<FieldButton*>> &board)
{
    int counter=0;
    for (int i=0; i<board.size(); i++)
    {
        counter=0;
        for(int j=0; j<board[i].size(); j++)
        {
            FieldButton* current_button = board[i][j];
            if(current_button->get_user_id()==user_id)
            {
                counter+=1;
                if(counter==5)
                {
                    return true;
                }
            }
            else counter=0;
        }


    }
    return false;
}




void data_print()
{
    gout << move_to(630, 80) << color(255,0,0) << box(180, 100);
    stringstream player_id;
    player_id << user_id;
    string player_id_str="";
    player_id_str=player_id.str();
    gout << move_to(650, 100) << color(0,0,255) << text(player_id_str);
    if(winner_user!=0)
    {
        gout << text(". player WIN!") <<refresh;
    }
 else gout<<text(". player's turn!") << refresh;
}



void event_loop(vector<vector<FieldButton*>>& widgets)
{
    event ev;

    while(gin >> ev )
    {



        for (int i=0; i<widgets.size(); i++)
        {
            for(int j=0; j<widgets[i].size(); j++)
            {
                FieldButton* current_button = widgets[i][j];

                if (current_button->can_be_clicked() && current_button->is_clicked(ev))
                {

                    current_button->set_user_id(user_id);
                    if(winning(widgets))
                    {
                        winner_user=user_id;
                    }
                    if(user_id==1)
                    {
                        user_id=2;
                    }
                    else if(user_id==2)
                    {
                        user_id=1;
                    }
                    cout << "actual id: " <<user_id << ";" << widgets[i][j]->get_status() << endl;
                }



//cout << "actual id befora drawing:" << user_id << endl;
                current_button->rajzol();
            }

        }
        data_print();
        gout << refresh;
    }
}



int main()
{
    gout.open(900,600);
    vector<Widget*> vec;

    vector<vector<FieldButton*>> all;
    int board_size=20;
    for( int j=0; j<board_size; j++)
    {
        vector<FieldButton*> f_vec;
        for(int i=0; i<board_size; i++)
        {
            FieldButton* button  = new FieldButton(i*30,j*30);
            f_vec.push_back(button);

        }
        all.push_back(f_vec);
    }

    event_loop(all);
    return 0;
}
