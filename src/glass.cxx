#include <ge211.hxx>

#include "glass.hxx"
#include "game_config.hxx"

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
Game_config config;

Glass::Glass(int counter)
    : g_speed_(400),
    g_posn(ge211::Posn<int>{(config.counter_right-g_offset_value),counter})
{}

double
Glass::g_next_x(double dt)
{
    double result = g_posn.x - dt*g_speed_;
    return result;
}

int Glass::g_counterr()
{
    return g_posn.y;
}

void
Glass::reassign_glass_x(double new_x)
{
    g_posn = {new_x,g_posn.y};
}