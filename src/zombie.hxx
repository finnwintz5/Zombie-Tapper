
#include <ge211.hxx>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>

class Zombie
{
public:

    // PRIVATE MEMBER VARIABLES
    double z_speed_;
    ge211::Image_sprite z_sprite_;
    std::queue<ge211::Image_sprite> z_sprites_;
    double curr_duration_ = 0;

public:
    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<double>;
    // PUBLIC MEMBER VARIABLES
    Position z_posn; // x value is x position, y value is counter #
    // CONSTRUCTOR
    Zombie(int time_elapsed);

    // FUNCTIONS
    int z_counterr();
    double z_next_x(double dt);
    void z_update_sprite(double dt);
    void reassign_zombie_x(double new_x);
};