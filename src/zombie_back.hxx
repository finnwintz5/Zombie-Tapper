
#include <ge211.hxx>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>

class ZombieBack
{
public:

    // PRIVATE MEMBER VARIABLES
    double zb_speed_;
    ge211::Image_sprite zb_sprite_;
    std::queue<ge211::Image_sprite> zb_sprites_;
    double curr_duration_ = 0;

public:
    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<double>;
    // PUBLIC MEMBER VARIABLES
    Position zb_posn; // x value is x position, y value is counter #
    // CONSTRUCTOR
    ZombieBack(Position posn);

    // FUNCTIONS
    int zb_counterr();
    double zb_next_x(double dt);
    void zb_update_sprite(double dt);
    void reassign_zombie_back_x(double new_x);
};