#include "zombie.hxx"
#include <cstdlib>
#include "game_config.hxx"

Game_config local_config;

std::vector<std::string>
z_sprites_create()
{
    std::vector<std::string> z_sprite_files;
    for (int i=0;i<12;i++) {
        z_sprite_files.push_back("zombie-"+
                                 std::to_string(i) + ".png");
    }
    return z_sprite_files;
}

static std::vector<std::string> z_sprite_files = z_sprites_create();

Zombie::Zombie(int time_elapsed)
    : z_speed_(5+(time_elapsed*1.25)),
      z_sprite_(z_sprite_files[0]),
      z_sprites_(),
      z_posn(ge211::Posn<int>{local_config.counter_left-100,rand()%4}) //
      // generates random
      // counter
{
    for(std::string const& filename : z_sprite_files) {
        z_sprites_.push(ge211::Image_sprite(filename));
    }
}

double
Zombie::z_next_x(double dt)
{
    double result = z_posn.x + dt*z_speed_;
    return result;
}

int
Zombie::z_counterr()
{
    return z_posn.y;
}

void
Zombie::z_update_sprite(double dt)
{
    double update_rate = 1.0 / z_sprites_.size(); // changes sprites every 2
    // units

    curr_duration_ += dt;
    if(curr_duration_ > update_rate) {
        curr_duration_ = 0;
        z_sprite_ = z_sprites_.front();
        z_sprites_.push(z_sprites_.front());
        z_sprites_.pop();
    }
}

void
Zombie::reassign_zombie_x(double new_x)
{
    z_posn.x = new_x;
}