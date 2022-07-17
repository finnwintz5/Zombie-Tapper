#pragma once

#include <ge211.hxx>
#include "zombie.hxx"
#include "glass.hxx"
#include "game_config.hxx"
#include "bartender.hxx"
#include "exploding_glass.hxx"
#include "zombie_back.hxx"

#include <iostream>
#include <vector>

enum class GameState
{
    start,
    running,
    paused,
    game_over,
};

class Model
{
    // PRIVATE MEMBER VARIABLES
    int lives_ = 4;
    int score_ = 0;
    GameState game_state_ = GameState::start;
    double curr_duration_ = 0;
    double total_time_ = 0;

public:
    using Position = ge211::Posn<double>;
    // PUBLIC MEMBER VARIABLES
    Game_config config;
    bool music_playing = true;
    bool explode_sound = false;
    // was in board
    std::vector<Zombie> zombies = {};
    std::vector<Glass> glasses = {};
    Bartender bartender;
    std::vector<ExplodingGlass> exploding = {};
    std::vector<ZombieBack> zombies_back = {};
    // CONSTRUCTOR
    Model();
    // FUNCTIONS
    // giving us our info
    int score() const;
    int lives() const;
    GameState game_state() const;
    // about moving
    void move_bartender_up();
    void move_bartender_down();
    // functions about hitting
    bool glass_hit_zombie(double g_next, double z_next);
    bool glass_hit_wall(double glass_x);
    bool zombie_hit_end_counter(double zombie_x);
    bool zombie_back_hit_wall(double zombie_back_x);
    // functions about spawning/deleting
    void spawn_zombie();
    void spawn_glass();
    void spawn_exploding(int counter,bool left);
    void spawn_zombie_back(Position posn);
    // functions about game state
    void lost_life_reset();
    void change_game_state(GameState state);
    void reset_score();

    // functions that move the zombies/glasses
        // and check if they hit anything
        // and do the correct thing if they do hit
        // something
    void zombies_hit_end_or_move(double dt);
    void glasses_hit_zombies_walls_or_move(double dt);
    void spawn_zombies_periodically(double dt);
    void exploding_animation(double dt);
    void move_zombies_back(double dt);
    // void exploding_glass(double dt);
    // functions moving zombies and glasses
    void on_frame(double dt);

};
