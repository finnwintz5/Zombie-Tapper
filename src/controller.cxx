#include "controller.hxx"

Controller::Controller()
        : model_(),
          view_(model_),
          background_music_("background_mus.mp3",mixer()),
          explosion_sound_("explosion.mp3",mixer())
{
    mixer().play_music(background_music_);
}

void
Controller::draw(ge211::Sprite_set& set)
{
    if (model_.game_state() != GameState::start) {
        view_.draw_bartables(set);
        view_.draw_score_and_lives(set);
        view_.draw_bartender(set);
        view_.draw_glasses(set);
        view_.draw_zombies(set);
        view_.draw_brain_collection(set);
        view_.draw_exploding(set);
        view_.draw_zombies_back(set);
    }
    else {
        view_.draw_start(set);
    }
    view_.draw_background(set);
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

void
Controller::on_frame(double dt)
{
    model_.on_frame(dt);
    if (model_.explode_sound && (mixer().get_music_state() ==
    ge211::Mixer::State::playing)) {
        mixer().play_effect(explosion_sound_,.5);
        model_.explode_sound = false;
    }
}

void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q')) {
        quit();
    }
    else if (key == ge211::Key::code('p')) {
        if (model_.game_state() == GameState::running) {
            // pause game
            model_.change_game_state(GameState::paused);
        }
        else if (model_.game_state() == GameState::paused) {
            // unpause game
            model_.change_game_state(GameState::running);
        }
    }
    else if (key == ge211::Key::code(' ')) {
        if (model_.game_state() == GameState::start) {
            model_.change_game_state(GameState::running);
        }
        else if (model_.game_state() == GameState::running) {
            // fill glass
            model_.spawn_glass();
        }
    }
    else if (key == ge211::Key::code('r')) {
        // restarts game
        model_.change_game_state(GameState::running);
        model_.reset_score();
    }

    else if (key == ge211::Key::up()) {
        // move bartender up
        if (model_.game_state() == GameState::running) {
            model_.move_bartender_up();
        }
    }
    else if (key == ge211::Key::down()) {
        // move bartender down
        if (model_.game_state() == GameState::running) {
            model_.move_bartender_down();
        }
    }
    else if (key == ge211::Key::code('m')) {
        if (mixer().get_music_state() == ge211::Mixer::State::paused) {
            mixer().resume_music();
            model_.music_playing = true;
        }
        else if (mixer().get_music_state() == ge211::Mixer::State::playing) {
            mixer().pause_music();
            model_.music_playing = false;
        }
    }
}