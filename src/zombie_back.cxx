#include "zombie_back.hxx"
#include <cstdlib>

std::vector<std::string>
zb_sprites_create()
{
    std::vector<std::string> zb_sprite_files;
    for (int i=0;i<12;i++) {
        zb_sprite_files.push_back("zombie-back-"+
                                 std::to_string(i) + ".png");
    }
    return zb_sprite_files;
}

static std::vector<std::string> zb_sprite_files = zb_sprites_create();

ZombieBack::ZombieBack(Position posn)
        : zb_speed_(-200),
          zb_sprite_(zb_sprite_files[0]),
          zb_sprites_(),
          zb_posn(posn)
{
    for(std::string const& filename : zb_sprite_files) {
        zb_sprites_.push(ge211::Image_sprite(filename));
    }
}

double
ZombieBack::zb_next_x(double dt)
{
    double result = zb_posn.x + dt*zb_speed_;
    return result;
}

int
ZombieBack::zb_counterr()
{
    return zb_posn.y;
}

void
ZombieBack::zb_update_sprite(double dt)
{
    double update_rate = 1.0 / zb_sprites_.size(); // changes sprites every 2
    // units

    curr_duration_ += dt;
    if(curr_duration_ > update_rate) {
        curr_duration_ = 0;
        zb_sprite_ = zb_sprites_.front();
        zb_sprites_.push(zb_sprites_.front());
        zb_sprites_.pop();
    }
}

void
ZombieBack::reassign_zombie_back_x(double new_x)
{
    zb_posn.x = new_x;
}