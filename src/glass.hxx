#pragma once

#include <ge211.hxx>

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

static int const g_offset_value = 35;

class Glass
{

    // PRIVATE MEMBER VARIABLES
    int g_speed_;

public:
    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;
    // PUBLIC MEMBER VARIABLES
    ge211::Posn<double> g_posn; // x value is x position, y value is counter #
    // CONSTRUCTOR
    Glass(int counter);
    // FUNCTIONS
    double g_next_x(double dt);
    int g_counterr();
    void reassign_glass_x(double new_x);
};