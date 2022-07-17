#pragma once

#include <ge211.hxx>

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>

class ExplodingGlass
{
public:

    // PRIVATE MEMBER VARIABLES
    // animation
    ge211::Image_sprite e_sprite_;
    std::queue<ge211::Image_sprite> e_sprites_;
    double curr_duration_ = 0;
    int times_completed_ = 0;
    bool done_animating_ = false;
    // location
    int counter_;
    bool left_;


public:
    // CONSTRUCTOR
    ExplodingGlass(int counter,bool left);
    bool done_animating();
    // FUNCTIONS
    void e_update_sprite(double dt);
};