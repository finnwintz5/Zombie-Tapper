#include "view.hxx"
#include <cmath>

// define colors
static ge211::Color const bartable_color {193, 154, 107};
static ge211::Color const bartender_color {255, 255, 102};

View::View(Model const& model)
        : model_(model),
          font_("arcadeclassic.ttf",40),
          font_big_("arcadeclassic.ttf",80),
          font_mid_("arcadeclassic.ttf",70),
          bartender_sprite_({10,50},bartender_color),
          bartender_sprite_2_("bartender.png"),
          glass_sprite_("brain_glass.png"),
          bar_box_("box.png"),
          brain_score_("brain_score.png"),
          background_("post-apocalyptic-2.jpeg"),
          brain_jar_("brain_collection.png"),
          intro_screen_("intro_screen.png")
{ }

void
View::draw_score_and_lives(ge211::Sprite_set& set)
{
    if (model_.game_state() != GameState::game_over) {
        // DRAWS SCORE
        ge211::Text_sprite::Builder text_builder(font_);
        text_builder.color(ge211::Color(0xFF,0xFF,0x00));
        text_builder << "Score   " << model_.score();
        score_text_.reconfigure(text_builder);
        set.add_sprite(score_text_,{50,20},10);
        // DRAWS LIVES TEXT
        ge211::Text_sprite::Builder text_builder_2(font_);
        text_builder_2.color(ge211::Color(0xFF,0xFF,0x00));
        text_builder_2 << "Lives ";
        lives_text_.reconfigure(text_builder_2);
        set.add_sprite(lives_text_,{50,55},10);
        // DRAWS SCORE BRAINS
        int lives =  model_.lives();
        if (lives >= 1) {
            set.add_sprite(brain_score_,{175,60},10);
        }
        if (lives >= 2) {
            set.add_sprite(brain_score_,{215,60},10);
        }
        if (lives >= 3) {
            set.add_sprite(brain_score_,{255,60},10);
        }
        if (lives >= 4) {
            set.add_sprite(brain_score_,{295,60},10);
        }
        //pause text
        ge211::Text_sprite::Builder text_builder_6(font_);
        text_builder_6.color(ge211::Color(0xFF,0xFF,0x00));
        if (model_.game_state() == GameState::running) {
            text_builder_6 << "Press   P   to   Pause";
        }
        else if (model_.game_state() == GameState::paused) {
            text_builder_6 << "Press   P   to   Resume";
        }
        pausing_text_.reconfigure(text_builder_6);
        set.add_sprite(pausing_text_,{650,20},10);
        // mute text
        ge211::Text_sprite::Builder text_builder_7(font_);
        text_builder_7.color(ge211::Color(0xFF,0xFF,0x00));
        if (model_.music_playing) {
            text_builder_7 << "Press   M   to   Mute";
        }
        else {
            text_builder_7 << "Press   M   to   Unmute";
        }
        music_text_.reconfigure(text_builder_7);
        set.add_sprite(music_text_,{650,55},10);
    }
    else {
        ge211::Text_sprite::Builder text_builder_3(font_big_);
        text_builder_3.color(ge211::Color(0xFF,0xFF,0x00));
        text_builder_3 << "Game   Over";
        game_over_text_.reconfigure(text_builder_3);
        set.add_sprite(game_over_text_,{300,100},10);

        ge211::Text_sprite::Builder text_builder_4(font_);
        text_builder_4.color(ge211::Color(0xFF,0xFF,0x00));
        text_builder_4 << "Final   Score    " << model_.score();
        final_score_text_.reconfigure(text_builder_4);
        set.add_sprite(final_score_text_,{300,200},10);

        ge211::Text_sprite::Builder text_builder_5(font_);
        text_builder_5.color(ge211::Color(0xFF,0xFF,0x00));
        text_builder_5 << "Press   R   to   Restart";
        how_to_restart_text_.reconfigure(text_builder_5);
        set.add_sprite(how_to_restart_text_,{300,250},10);

        // mute text
        ge211::Text_sprite::Builder text_builder_7(font_);
        text_builder_7.color(ge211::Color(0xFF,0xFF,0x00));
        if (model_.music_playing) {
            text_builder_7 << "Press   M   to   Mute";
        }
        else {
            text_builder_7 << "Press   M   to   Unmute";
        }
        music_text_.reconfigure(text_builder_7);
        set.add_sprite(music_text_,{650,20},10);


    }

}

void
View::draw_zombies(ge211::Sprite_set& set)
{
    for(size_t i=0;i<model_.zombies.size();i++) {
        int x_value = round(model_.zombies[i].z_posn.x);
        int counter = model_.zombies[i].z_posn.y;
        int y_value = round(model_.config.counter_y_posns[counter])-30;
        set.add_sprite(model_.zombies[i].z_sprite_,
                                        {x_value,y_value},(2*counter)+1);
    }
}

void
View::draw_glasses(ge211::Sprite_set& set)
{
    for(size_t i=0;i<model_.glasses.size();i++) {
        int x_value = round(model_.glasses[i].g_posn.x);
        int y_value = round(model_.config.counter_y_posns
                                                [model_.glasses[i].g_posn.y])
                                                        -15;
        set.add_sprite(glass_sprite_,{x_value,y_value},9);
    }
}

void
View::draw_bartender(ge211::Sprite_set& set)
{
    // do something with bartender; using model_.bartender()
    set.add_sprite(bartender_sprite_2_,{model_.bartender.b_posn.x-80,model_
            .config.counter_y_posns[model_.bartender.b_posn.y]-10},10);
}

void
View::draw_bartables(ge211::Sprite_set& set)
{
    for(int i=0;i<4;i++) {
        for(int j=0;j<16;j++) {
            set.add_sprite(bar_box_,{model_.config.counter_left+(j*50),model_
            .config.counter_y_posns[i]+50},(i*2)+2);
        }
    }
    set.add_sprite(bar_box_,{200,model_.config.counter_y_posns[0]+50},2);
}

void
View::draw_background(ge211::Sprite_set& set)
{
    set.add_sprite(background_,{-730,-390},0);
}

void
View::draw_brain_collection(ge211::Sprite_set& set)
{
    for (size_t i=0;i<4;i++) {
        set.add_sprite(brain_jar_,{825,model_.config.counter_y_posns[i]-10},1);
    }
}

void
View::draw_start(ge211::Sprite_set& set)
{
    set.add_sprite(intro_screen_,{-80,-120},13);

    ge211::Text_sprite::Builder text_builder(font_);
    text_builder.color(ge211::Color(0xFF,0xFF,0xFF));
    text_builder << "Space   to   Send   Brain   Jar";
    space_instruct_text_.reconfigure(text_builder);
    set.add_sprite(space_instruct_text_,{250,525},10);

    ge211::Text_sprite::Builder text_builder_2(font_);
    text_builder_2.color(ge211::Color(0xFF,0xFF,0xFF));
    text_builder_2 << "Up   and   Down   to   Change   Counters";
    move_instruct_text_.reconfigure(text_builder_2);
    set.add_sprite(move_instruct_text_,{175,575},10);

    ge211::Text_sprite::Builder text_builder_3(font_mid_);
    text_builder_3.color(ge211::Color(0xFF,0xFF,0x00));
    text_builder_3 << "Press   Space   to   Continue";
    continue_instruct_text_.reconfigure(text_builder_3);
    set.add_sprite(continue_instruct_text_,{75,625},10);
}

void
View::draw_exploding(ge211::Sprite_set& set)
{
    for (size_t i=0;i<model_.exploding.size();i++) {
        int x_pos = 0;
        if (model_.exploding[i].left_) {
            x_pos = model_.config.counter_left-20;
        }
        else {
            x_pos = model_.config.counter_right-40;
        }
        set.add_sprite(model_.exploding[i].e_sprite_,{x_pos,
                                                   model_.config
                                                   .counter_y_posns[model_
                                                   .exploding[i].counter_]},
                                                   10);
        // set.add_sprite(model_.exploding[i].e_sprite_,{100,100},10);
    }
}

void
View::draw_zombies_back(ge211::Sprite_set& set)
{
    for(size_t i=0;i<model_.zombies_back.size();i++) {
        int x_value = round(model_.zombies_back[i].zb_posn.x);
        int counter = model_.zombies_back[i].zb_posn.y;
        int y_value = round(model_.config.counter_y_posns[counter])-30;
        set.add_sprite(model_.zombies_back[i].zb_sprite_,
                       {x_value,y_value},(2*counter)+1);
    }
}

View::Dimensions
View::initial_window_dimensions() const
{
    return model_.config.scene_dims;
}

std::string
View::initial_window_title() const
{
    // You can change this if you want:
    return "Zombie Tapper";
}