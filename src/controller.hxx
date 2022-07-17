#pragma once

#include "model.hxx"
#include "view.hxx"

struct Controller : public ge211::Abstract_game
{
public:
    Controller();

protected:
    void draw(ge211::Sprite_set& set) override;
    View::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;
    void on_frame(double dt) override;
    void on_key(ge211::Key) override;
private:
    Model model_;
    View view_;
    // music stuff
    ge211::Music_track background_music_;
    ge211::Sound_effect explosion_sound_;

};
