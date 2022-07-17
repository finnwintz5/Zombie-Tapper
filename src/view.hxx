#pragma once

#include "model.hxx"

#include <string>

class View
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// Constructs a view that knows about the given model.
    explicit View(Model const&);
    void draw_score_and_lives(ge211::Sprite_set& set);
    void draw_zombies(ge211::Sprite_set& set);
    void draw_glasses(ge211::Sprite_set& set);
    void draw_bartender(ge211::Sprite_set& set);
    void draw_bartables(ge211::Sprite_set& set);
    void draw_background(ge211::Sprite_set& set);
    void draw_brain_collection(ge211::Sprite_set& set);
    void draw_start(ge211::Sprite_set& set);
    void draw_exploding(ge211::Sprite_set& set);
    void draw_zombies_back(ge211::Sprite_set& set);
    Dimensions initial_window_dimensions() const;
    std::string initial_window_title() const;
private:
    Model const& model_;
    // things to display
    ge211::Font font_;
    ge211::Font font_big_;
    ge211::Font font_mid_;
    ge211::Text_sprite score_text_;
    ge211::Text_sprite lives_text_;
    ge211::Text_sprite game_over_text_;
    ge211::Text_sprite final_score_text_;
    ge211::Text_sprite how_to_restart_text_;
    ge211::Text_sprite pausing_text_;
    ge211::Text_sprite music_text_;

    // intro screen instructions
    // space to send brain jar
    ge211::Text_sprite space_instruct_text_;
    // up / down to change counters
    ge211::Text_sprite move_instruct_text_;
    ge211::Text_sprite continue_instruct_text_;



    // bartender
    ge211::Rectangle_sprite bartender_sprite_;
    ge211::Image_sprite bartender_sprite_2_;
    // glass
    ge211::Image_sprite glass_sprite_;
    // bar tables
    ge211::Image_sprite bar_box_;
    // lives brain
    ge211::Image_sprite brain_score_;
    // background
    ge211::Image_sprite background_;
    // brain jars
    ge211::Image_sprite brain_jar_;
    // intro screen
    ge211::Image_sprite intro_screen_;

};
