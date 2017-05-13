#ifndef GAME_WINDOW_HPP_INCLUDED
#define GAME_WINDOW_HPP_INCLUDED


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

class GameWindow
{
private:
    virtual void event_loop();
    int user_id=1;
    int winner_user=0;
    bool full=false;
    int jackpot=4;
    event ev;
    Button* cleaner_button = new Button (685, 130, 70, 30, "CLEAN!");
    virtual bool winning();
    virtual void board_maker();
    virtual void cleaner();
    virtual bool is_full();
    virtual void data_print();
    vector<vector<FieldButton*>> board;
    virtual void user_clicked(int i, int j);

    vector<vector<int>> opponent;
    vector<vector<int>> me;
    void update_MI_matrix(int i, int j);
    void get_next_MI_step(int& i, int& j);
    int valueOnPos(int i, int j, int player);
    void log(vector<vector<int>>& m, string start);
    void zero(vector<vector<int>>& m);

public:
    GameWindow();
    virtual void start();

};


#endif // GAME_WINDOW_HPP_INCLUDED
