#include "bartender.hxx"
#include "game_config.hxx"

Game_config local_config_2;

Bartender::Bartender()
    : b_posn(ge211::Posn<int> {local_config_2.counter_right,1})
{

}

void
Bartender::move_up()
{
    if(b_posn.y<=0) {
        b_posn.y = 3;
    }
    else {
        b_posn.y-=1;
    }
}

void
Bartender::move_down()
{
    if(b_posn.y>=3) {
        b_posn.y = 0;
    }
    else {
        b_posn.y+=1;
    }
}
