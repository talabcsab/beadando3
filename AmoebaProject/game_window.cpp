#include "game_window.hpp"

void GameWindow::start()
{
        cout << "itt!";

    gout.open(900,600);
    cout << "itt1!";
    board_maker();
    cout << "itt2!";
    cleaner();
    cout << "itt3!";
    event_loop();
}
bool GameWindow::winning()
{
    int row_counter=0;
    int column_counter=0;
    int diag1_counter=0;
    int diag2_counter=0;
    int diag3_counter=0;
    int diag4_counter=0;
    for (int i=0; i<board.size(); i++)
    {
        row_counter=0;
        column_counter=0;
        diag1_counter=0;
        diag2_counter=0;
        diag3_counter=0;
        diag4_counter=0;
        for(int j=0; j<board[i].size(); j++)
        {
            FieldButton* current_row_button = board[i][j];
            if(current_row_button->get_user_id()==user_id)
            {
                row_counter+=1;
                if(row_counter==5)
                {
                    return true;
                }
            }
            else
            {
                row_counter=0;
            }
            FieldButton* current_column_button = board[j][i];
            if(current_column_button->get_user_id()==user_id)
            {
                column_counter+=1;
                if(column_counter==5)
                {
                    return true;
                }
            }
            else
            {

                column_counter=0;

            }
            int diag1_index = min(j+i, (int) board.size()-1);
            FieldButton* current_diag1_button = board[j][diag1_index];
            if(current_diag1_button->get_user_id()==user_id)
            {
                diag1_counter+=1;
                if(diag1_counter==5)
                {
                    return true;
                }
            }
            else
            {
                diag1_counter=0;
            }
            int diag2_index = max(j-i,0);
            FieldButton* current_diag2_button = board[j][diag2_index];
            if(current_diag2_button->get_user_id()==user_id)
            {
                diag2_counter+=1;
                if(diag2_counter==5)
                {
                    return true;
                }
            }
            else
            {
                diag2_counter=0;
            }
            int diag3_index_1=board.size()-1-j;
            int diag3_index_2= min (i+j, (int) board.size()-1);
            FieldButton* current_diag3_button = board[diag3_index_1][diag3_index_2];
            if(current_diag3_button->get_user_id()==user_id)
            {
                diag3_counter+=1;
                if(diag3_counter==5)
                {
                    return true;
                }
            }
            else
            {
                diag3_counter=0;
            }
            int diag4_index_1 = max(j-i,0);
            int diag4_index_2 = board.size()-1-j;
            FieldButton* current_diag4_button = board[diag4_index_1][diag4_index_2];
            if(current_diag4_button->get_user_id()==user_id)
            {
                diag4_counter+=1;
                if(diag4_counter==5)
                {
                    return true;
                }
            }
            else
            {
                diag4_counter=0;
            }
        }


    }
    return false;
}

void GameWindow::board_maker()
{
    int board_size=20;
    board.clear();

    for( int j=0; j<board_size; j++)
    {
        vector<FieldButton*> f_vec;
        for(int i=0; i<board_size; i++)
        {
            FieldButton* button  = new FieldButton(i*30,j*30);
            f_vec.push_back(button);

        }
       board.push_back(f_vec);
    }
}


void GameWindow::cleaner()
{
    cleaner_button->rajzol(255, 0,0 );
    if(cleaner_button->is_clicked(ev))
    {
        winner_user=0;
        user_id=1;
        board_maker();
        full=false;

    }
}





bool GameWindow::is_full()
{
    for(int i=0; i<board.size(); i++)
    {
        for(int j=0; j<board[i].size(); j++)
        {
            if(board[i][j]->get_user_id()==0)
            {
                return false;
            }
        }

    }
    return true;

}
void GameWindow::data_print()
{
    gout << move_to(630, 80) << color(255,0,0) << box(180, 50);
    string player_id_str="";
    gout << move_to(650, 100) << color(0,0,255);
    if(winner_user!=0)
    {
        stringstream win_id;
        player_id_str="";
        win_id << winner_user;
        player_id_str = win_id.str();
        gout << text(player_id_str) <<text(". player WIN!");
    }
    else if(full==false)
    {
        stringstream player_id;
        player_id << user_id;
        player_id_str=player_id.str();
        gout<< text(player_id_str) <<text(". player's turn!");
    }
    if(full==true)
    {
        gout << move_to(650, 115)<<text("The board is full!");
    }
    gout <<refresh;

}

void GameWindow::event_loop()
{
    while(gin >> ev )
    {

        for (int i=0; i<board.size(); i++)
        {
            for(int j=0; j<board[i].size(); j++)
            {
                FieldButton* current_button = board[i][j];

                if (current_button->can_be_clicked() && current_button->is_clicked(ev) && winner_user==0 && full==false)
                {

                    current_button->set_user_id(user_id);
                    if(winning())
                    {
                        winner_user=user_id;
                    }
                    full=is_full();
                    if(user_id==1)
                    {
                        user_id=2;
                    }
                    else if(user_id==2)
                    {
                        user_id=1;
                    }
                }



                current_button->rajzol();
            }

        }
        cleaner();
        data_print();
        gout << refresh;
    }
}

GameWindow::GameWindow()
{
     winner_user=0;
        user_id=1;
        board_maker();
        full=false;
}
