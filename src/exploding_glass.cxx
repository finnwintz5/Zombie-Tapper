#include "exploding_glass.hxx"

std::vector<std::string>
e_sprites_create()
{
    std::vector<std::string> e_sprite_files;
    for (int i=0;i<12;i++) {
        e_sprite_files.push_back("download ("+
                                 std::to_string(i+1) + ").png");
    }
    return e_sprite_files;
}

static std::vector<std::string> e_sprite_files = e_sprites_create();

ExplodingGlass::ExplodingGlass(int counter, bool left)
        : e_sprite_(e_sprite_files[0]),
          e_sprites_(),
          counter_(counter),
          left_(left)
{
    for(std::string const& filename : e_sprite_files) {
        e_sprites_.push(ge211::Image_sprite(filename));
    }
}

void
ExplodingGlass::e_update_sprite(double dt)
{
    double update_rate = 0.75 / e_sprites_.size(); // changes sprites every 2
    // units

    curr_duration_ += dt;
    if(curr_duration_ > update_rate) {
        curr_duration_ = 0;
        e_sprite_ = e_sprites_.front();
        e_sprites_.push(e_sprites_.front());
        e_sprites_.pop();
        times_completed_++;
    }
    if (times_completed_ > 11) {
        done_animating_ = true;
    }
}

bool
ExplodingGlass::done_animating()
{
    return done_animating_;
}