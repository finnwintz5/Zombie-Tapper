#pragma once
#include <ge211.hxx>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Bartender
{
public:

    // CONSTRUCTORS
    Bartender();
public:
    // PUBLIC MEMBER VARIABLES
    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;
    // PUBLIC MEMBER VARIABLES
    Position b_posn; // x value is x position, y value is counter #

    // PUBLIC FUNCTIONS
    // function to move the bartender to whatever counter is written
    void move_up();
    void move_down();

    // ge211::Posn<int> {config.counter_end,config
    // .counter_y_posns[1]}
};