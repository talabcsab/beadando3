#include "game_window.hpp"
#include <vector>

void GameWindow::menu()
{
    vector<string> options;
    string single="Single player";
    string multi="Multiplayer";
    options.push_back(single);
    options.push_back(multi);
    mode_menu = new MenuWidget(650, 400, 150, 20, options);
    mode_menu->rajzol();

    ///Letrehozza az ablak jobb oldalan talalhato menut, melynek ket opcioja a single és a multiplayer mode.

}



void GameWindow::start()
{
    gout.open(900,600);
    menu();
    board_maker();
    reset();
    event_loop();

///Itt (1) hozzuk letre az ablakot, (2) elokeszitjuk a jatekteret, (3) beallitjuk a kezdoallapotot, valamint (4) elindatjuk az esemenykezelest.
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
///Vizsgalja, hogy nyert-e valaki. Ot azonos user ID-val rendelkezo mezot keres, vizszintesen, fuggolegesen és atlosan is.
}

void GameWindow::board_maker()
{
    int board_size=20;
    board.clear();
    me.clear();
    opponent.clear();

    for( int j=0; j<board_size; j++)
    {
        vector<FieldButton*> f_vec;
        for(int i=0; i<board_size; i++)
        {
            FieldButton* button  = new FieldButton(i*30,j*30);
            f_vec.push_back(button);
        }
        board.push_back(f_vec);
        me.push_back(vector<int>(board_size));
        opponent.push_back(vector<int>(board_size));
    }
/// Adott a boardsize valtozo, melyet itt deklaralok a konnyu modositas erdekeben, majd letrehozok egy board_size x board_size meretu palyat
/// A palya FieldButton tipusu widgetekbol all.
}


void GameWindow::cleaner()
{
    cleaner_button->rajzol(255, 0,0 );
    if(cleaner_button->is_clicked(ev))
    {
        reset();
    }
///Vizsgalja, hogy a gombot megnyomjuk-e, majd ha igen, meghivja a lentebb deklaralt reset fv-t
}

void GameWindow::reset()
{
        winner_user=0;
        user_id=1;
        board_maker();
        full=false;

///Mindent visszaallit kezdeti ertekre, majd ujrarajzoltatja a palyat.
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
///Vizsgalja, hogy megtelt-e a palya, vagyis hogy van-e meg szabad(nulla erteku) mezo

}
void GameWindow::data_print()
{
    gout << move_to(630, 80) << color(176,224,230) << box(180, 50);
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
///Kiirja a soros jatekos szamat, ill. a nyertest es azt is tudatja, ha a palya megtelt.
}

int GameWindow::valueOnPos(int si, int sj, int player)
{


    if (!board[si][sj]->can_be_clicked())
    {
        return 0;
    }

    int startX = max(si-4,0);
    int endX = min(si+4,(int)board.size()-1);
    int startY = max(sj-4,0);
    int endY = min(sj+4,(int)board.size()-1);

    int res = 0;

    int counter = 0;
    bool valid=false;
    for (int i = si+1; i<=endX; i++)
    {
        if((board[i][sj]->get_user_id() == player))
        {
            counter += 1;
        }
        else
        {
            valid=board[i][sj]->can_be_clicked();
            break;
        }
    }


    for (int i = si-1; i>=startX; i--)
    {
        if((board[i][sj]->get_user_id() == player))
        {
            counter += 1;
        }
        else
        {
            valid=board[i][sj]->can_be_clicked() || valid;
            break;
        }
    }


    res = (counter > res && valid || counter==jackpot) ? counter : res;

    counter=0;
    valid=false;

    for (int j = sj+1; j<=endY; j++)
    {
        if((board[si][j]->get_user_id() == player))
        {
            counter += 1;
        }
        else
        {
            valid=board[si][j]->can_be_clicked();
            break;
        }
    }


    for (int j = sj-1; j>=startY; j--)
    {
        if((board[si][j]->get_user_id() == player ))
        {
            counter += 1;
        }
        else
        {
            valid=board[si][j]->can_be_clicked() || valid;
            break;
        }
    }

    res = (counter > res && valid || counter==jackpot) ? counter : res;

    counter=0;
    valid=false;

    for (int z=1; z<5; z++)
    {
        int dj = min(sj+z, (int) board.size()-1);
        int di = min(si+z, (int) board.size()-1);
        if(board[di][dj]->get_user_id() == player)
        {
            counter+=1;
        }
        else
        {

            valid=board[di][dj]->can_be_clicked() || valid;
            break;

        }
    }

    for (int z=1; z<5; z++)
    {
        int dj = max(sj-z, 0);
        int di = max(si-z, 0);
        if(board[di][dj]->get_user_id() == player)
        {
            counter+=1;
        }
        else
        {

            valid=board[di][dj]->can_be_clicked() || valid;
            break;

        }
    }

    res = (counter > res && valid || counter==jackpot) ? counter : res;

    counter=0;
    valid=false;

    for (int z=1; z<5; z++)
    {
        int di = max(si-z, 0);
        int dj = min(sj+z, (int) board.size()-1);
        if(board[di][dj]->get_user_id() == player)
        {
            counter+=1;
        }
        else
        {

            valid=board[di][dj]->can_be_clicked() || valid;
            break;

        }
    }

    for (int z=1; z<5; z++)
    {
        int di = min(si+z, (int) board.size()-1);
        int dj = max(sj-z, 0);
        if(board[di][dj]->get_user_id() == player)
        {
            counter+=1;
        }
        else
        {

            valid=board[di][dj]->can_be_clicked() || valid;
            break;

        }
    }

    res = (counter > res && valid || counter==jackpot) ? counter : res;

    return res;

///Erteket ad a kulonbozo mezoknak, annak fuggvenyeben, hogy az adott jatekosra nezve hany mezovel lenne szomszedos a kijelolheto mezok egyike. Nezi a a palya szelessegenek kozelseget is.
}

void GameWindow::update_MI_matrix(int si, int sj)
{
    int startX = max(si-4,0);
    int endX = min(si+5,(int)board.size());
    int startY = max(sj-4,0);
    int endY = min(sj+5,(int)board.size());

    for (int i = startX; i<endX; i++)
    {
        for (int j = startY; j<endY; j++)
        {
            me[i][j] = valueOnPos(i,j,2);
            opponent[i][j] = valueOnPos(i,j,1);
        }
    }
///Frissiti a mindket jatekos matrixat a valueOnPos fv altal szamitott ertekekkel.
/// A me mátrix a board mátrixszal azonos dimenziójú, a gépi játékos lehetséges lépéseihez rendelt értékeket tartalmazza (körönként frissítjük).
/// Minél magasabb értékû egy elem ebben a mátrixban, annál közelebb jut a gépi játékos a nyeréshez.
///Az opponent mátrix nagyon hasonló, viszont az ellenfél ("ember játékos") lépseinek értékeit tartalmazza
/// (vagyis minél magasabb értékû egy mezõ, annál közelebb kerül vele a játékos a nyeréshez).
}

void GameWindow::log(vector<vector<int>>& m, string start)
{
    /*cout << start << endl;

    for (int i = 0; i<m.size(); i++)
    {
        for (int j = 0; j<m[i].size(); j++)
        {
            cout << m[i][j] << ", ";
        }
        cout << endl;
    }

    cout << endl;
    cout << endl;*/

    ///Ezt a fuggvenyt a valueOnPos es az update_MI_matrix megirasahoz hasznaltam fel, igy tudtam ellenorizni az adatokat. Azért van kikommentezve, hogy ne irjon mar a konzolra.

}

void GameWindow::get_next_MI_step(int& r_i, int& r_j)
{

    int max_res=0;
    for(int i=0; i<opponent.size(); i++)
    {
        for(int j=0; j<opponent[i].size(); j++)
        {
            int res=opponent[i][j];
            if(res>max_res)
            {
                max_res=res;
                r_i=i;
                r_j=j;
            }
        }
    }
    for(int i=0; i<me.size(); i++)
    {
        for(int j=0; j<me[i].size(); j++)
        {
            int res=me[i][j];
            if(res>=max_res)
            {
                max_res=res;
                r_i=i;
                r_j=j;
            }
        }
    }
    ///Vizsgalja a legkedvezobb lepes erdekeben a mezoket a gepi jatekos szamara.
    ///A gépi játékos következõ lépésének pozícióját alapvetõen a "me" legmagasabb értékû mezõjének (i,j) pozíciója adja
    ///(hiszen ez viszi õt legközelebb a nyeréshez).
    ///Ellenben ha az ellenfél közelebb kerülhet a nyeréshez, akkor õt akadályozza
    /// (vagyis ha az opponent mátrixban van nagyobb értékû mezõ, mint a me mátrixban,
    ///akkor ennek a mezõnek az (i,j) pozíciója adja a gépi játékos következõ lépését).
}


void GameWindow::event_loop()
{
    while(gin >> ev )
    {

        for (int i=0; i<board.size(); i++)
        {
            for(int j=0; j<board[i].size(); j++)
            {
                FieldButton* current_button = board[i][j]; ///A tabla [i][j] elemet tekinti aktualis gomban a vizsgalat soran.

                if (current_button->can_be_clicked() && current_button->is_clicked(ev) && winner_user==0 && full==false)
                {
                    user_clicked(i,j);
                    if(singleplayer){
                        update_MI_matrix(i,j);

                        log(me, "me");
                        log(opponent, "opponent");
                        int m_i, m_j;
                        get_next_MI_step(m_i, m_j);

                        user_clicked(m_i, m_j);
                        update_MI_matrix(m_i,m_j);
                    }
///Single player eseten a meghivja az MI-hez tartozo fv-eket, igy lep a gep is. Ha multi van, csak a klikkeles van, egymas utan a ket jatekos.
                }



                current_button->rajzol();
                ///X-et, ill. O-t rajzol az adott gombba az aktualis jatekso fuggvenyeben.
            }

        }
        cleaner();
        data_print();
        ///Ha restartolunk meghivodik a cleaner, ill. frissiti az aktualis jatekos sorszamat/kiirja a nyertest.

        if (ev.type == ev_mouse && ev.button==btn_left) {
                mode_menu->set_active(ev.pos_x, ev.pos_y);
            }

            if (mode_menu->get_active())
            {
                mode_menu->kezel(ev);
                bool new_singleplayer=mode_menu->get_selected_option()=="Single player";

                if (singleplayer != new_singleplayer) {
                    reset();
                    singleplayer = new_singleplayer;
                }

            }
///A menubol kivalasztott opcio alapjan inditja, ujrainditja a jatekot.

            mode_menu->rajzol();


        gout << refresh;
    }
}

void GameWindow::user_clicked(int i, int j)
{
    FieldButton* current_button = board[i][j];
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
///klikkeles utan jatekost valt, vizsgalja, hogy valamilyen modon vegetert-e a jatek.
}

GameWindow::GameWindow()
{
    reset();
}
