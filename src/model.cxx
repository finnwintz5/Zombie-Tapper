#include "model.hxx"
#include <chrono>
#include <thread>

static int const z_sprite_width = 78;


Model::Model()
{

}

int
Model::lives() const
{
    return lives_;
}

int
Model::score() const
{
    return score_;
}

GameState
Model::game_state() const
{
    return game_state_;
}

void
Model::move_bartender_down()
{
    bartender.move_down();
}

void
Model::move_bartender_up()
{
    bartender.move_up();
}

bool
Model::glass_hit_wall(double glass_x)
{
    return glass_x <= (config.counter_left-g_offset_value);
}

bool
Model::glass_hit_zombie(double g_next, double z_next)
{
    return g_next<=(z_next + z_sprite_width);
}

bool
Model::zombie_hit_end_counter(double zombie_x)
{
    return (zombie_x + z_sprite_width)>=config.counter_right;
}

bool
Model::zombie_back_hit_wall(double zombie_back_x)
{
    return zombie_back_x <= config.counter_left-100;
}

void
Model::spawn_zombie()
{
    zombies.push_back(Zombie(total_time_));
}

void
Model::spawn_glass()
{
    glasses.push_back(Glass(bartender.b_posn.y));
}
void
Model::spawn_exploding(int counter,bool left)
{
    exploding.push_back(ExplodingGlass(counter,left));
    // sound effect activated
    explode_sound = true;
}

void
Model::spawn_zombie_back(Position posn)
{
    zombies_back.push_back(ZombieBack(posn));
}

void
Model::lost_life_reset()
{
    if (lives_<=1) {
        zombies.clear();
        glasses.clear();
        zombies_back.clear();
        game_state_ = GameState::game_over;
        lives_ = 0;
    }
    else {
        zombies.clear();
        glasses.clear();
        zombies_back.clear();
        lives_ -= 1;
    }
}

void
Model::change_game_state(GameState state)
{
    game_state_ = state;
}

void
Model::reset_score()
{
    score_ = 0;
}

void
Model::zombies_hit_end_or_move(double dt)
{
    for(size_t i=0;i<zombies.size();i++) {
        double nzombie_x = zombies[i].z_next_x(dt);
        // 1. ZOMBIE HITS END OF COUNTER
        if(zombie_hit_end_counter(nzombie_x)) {
            lost_life_reset();
            spawn_exploding(zombies[i].z_counterr(),false);
            break;
        }
        // 2. ZOMBIE CONTINUES
        else {
            zombies[i].z_update_sprite(dt);
            zombies[i].reassign_zombie_x(nzombie_x);
        }
    }
}

void
Model::glasses_hit_zombies_walls_or_move(double dt)
{
    for (size_t i = 0; i < glasses.size(); i++) {
        bool erased = false;
        double nglass_x = glasses[i].g_next_x(dt);
        // 1. GLASS HITS WALL
        if(glass_hit_wall(nglass_x)) {
            // glass breaks, wait 1 second
            lost_life_reset();
            spawn_exploding(glasses[i].g_counterr(),true);
            break;
        }
        // 2. GLASS HITS A ZOMBIE
        for (size_t j = 0; j < zombies.size(); j++) {
            // if the glass hits the zombie
            double nzombie_x = zombies[j].z_next_x(dt);
            if (glass_hit_zombie(nglass_x, nzombie_x) &&
                zombies[j].z_counterr() == glasses[i].g_counterr()) {
                // erase glass
                glasses.erase (glasses.begin()+i);
                erased = true;
                // spawn zombie back
                spawn_zombie_back(zombies[j].z_posn);
                // erase zombie
                zombies.erase (zombies.begin()+j);
                // add to score
                score_ += 50;
                break;
            }
        }
        // 3. GLASS CONTINUES
        if(!erased) {
            glasses[i].reassign_glass_x(nglass_x);
        }
    }
}

void
Model::spawn_zombies_periodically(double dt)
{
    double update_rate = 5-(total_time_*.1);
    if (update_rate < .5) {
        update_rate = .5;
    }
    curr_duration_ += dt;
    total_time_ += dt;
    if(curr_duration_ > update_rate) {
        curr_duration_ = 0;
        spawn_zombie();
    }
}

void
Model::exploding_animation(double dt)
{
    for (size_t i = 0; i<exploding.size();i++) {
        exploding[i].e_update_sprite(dt);
        if(exploding[i].done_animating()) {
            exploding.erase (exploding.begin()+i);
        }
    }
}

void
Model::move_zombies_back(double dt)
{
    for(size_t i=0;i<zombies_back.size();i++) {
        double nzombie_x = zombies_back[i].zb_next_x(dt);
        if (zombie_back_hit_wall(nzombie_x)) {
            zombies_back.erase (zombies_back.begin()+i);
        }
        else {
            zombies_back[i].zb_update_sprite(dt);
            zombies_back[i].reassign_zombie_back_x(nzombie_x);
        }
    }
}

void
Model::on_frame(double dt)
{
    // we may have a problem looping when stuff is deleted
    if (game_state_ != GameState::paused) {
        if (game_state_ == GameState::running) {
            spawn_zombies_periodically(dt);
            glasses_hit_zombies_walls_or_move(dt);
            zombies_hit_end_or_move(dt);
            move_zombies_back(dt);
        }

        else if (game_state_ == GameState::game_over) {
            bartender.b_posn.y=1;
            lives_ = 4;
            curr_duration_ = 0;
            total_time_ = 0;
        }
        exploding_animation(dt);
    }
}
