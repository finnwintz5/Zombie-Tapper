#include "model.hxx"
#include <catch.hxx>

using namespace ge211;

TEST_CASE("full example game")
{
    Model model;
    // (1) CHECK INITIAL GAME STATE
    CHECK(model.zombies.size() == 0);
    CHECK(model.glasses.size() == 0);
    CHECK(model.zombies_back.size() == 0);
    CHECK(model.exploding.size() == 0);
    // **** specification 1 ****
    CHECK(model.bartender.b_posn.y == 1);
    CHECK(model.bartender.b_posn.x == 800);
    CHECK(model.game_state() == GameState::start);
    model.change_game_state(GameState::running);
    CHECK(model.lives()==4);
    CHECK(model.score()==0);

    // (2) CHECK INITIAL GAME STATE
    // **** specification 2 & 3 ****
    // move bartender up and down
    model.move_bartender_up();
    CHECK(model.bartender.b_posn.y == 0);
    model.move_bartender_up();
    CHECK(model.bartender.b_posn.y == 3);
    model.move_bartender_down();
    CHECK(model.bartender.b_posn.y == 0);
    model.move_bartender_down();
    CHECK(model.bartender.b_posn.y == 1);

    // (3) ZOMBIE HITS WALL & DISAPPEARS -> 3 lives
    // **** specification 9 ****
    model.spawn_zombie();
    model.spawn_zombie();
    model.spawn_zombie();
    CHECK(model.zombies.size() == 3);
    // make sure the other two zombies don't move
    model.zombies[1].z_speed_ = 0;
    model.zombies[2].z_speed_ = 0;
    // check that it is initialized correctly
    // check y posn (counter #)
    // **** specification 6 ****
    CHECK(model.zombies[0].z_posn.y >=0);
    CHECK(model.zombies[0].z_posn.y <=3);
    // check x posn (x-coord)
    CHECK(model.zombies[0].z_posn.x ==-100);
    // make sure zombie moves forward
    model.on_frame(100.0);
    CHECK(model.zombies[0].z_posn.x == 400);
    // reassign zombie so we can be certain
    model.zombies[0].z_posn.x = 900;
    model.on_frame(.125);
    // all 3 zombies should be deleted
    CHECK(model.zombies.size() == 0);
    CHECK(model.exploding.size() == 1);
    CHECK(model.lives()==3);

    // (4) GLASS HITS WALL & DISAPPEARS -> 2 lives
    // **** specification 4 & 5 ****
    model.spawn_glass();
    CHECK(model.glasses.size() == 1);
    CHECK(model.bartender.b_posn.y == 1);
    CHECK(model.glasses[0].g_posn.y == 1);
    CHECK(model.glasses[0].g_posn.x == 765);
    // spawn zombie and ensure they won't touch
    model.spawn_zombie();
    model.zombies[0].z_posn.y = 2;
    model.zombies[0].z_speed_ = 0;
    model.on_frame(.5);
    CHECK(model.glasses[0].g_posn.x < 765);

    model.on_frame(100.0);
    CHECK(model.glasses.size() == 0);
    CHECK(model.zombies.size() == 0);
    CHECK(model.lives()==2);

    // (5) GLASS HITS ZOMBIE -> score+50
    // **** specification 7 ****
    model.spawn_zombie();
    model.spawn_zombie();
    model.zombies[0].z_posn.y = 1;
    model.zombies[0].z_speed_ = 500;
    model.zombies[0].z_posn.x = 223;

    model.zombies[1].z_posn.y = 2;
    model.zombies[1].z_speed_ = 0;
    model.spawn_glass();
    model.glasses[0].g_posn.y = 1;
    model.glasses[0].g_posn.x = 300;
    CHECK(model.score()==0);
    model.on_frame(.01);
    CHECK(model.score()==50);
    CHECK(model.lives()==2);
    CHECK(model.zombies_back.size() == 1);

    model.on_frame(.02);
    CHECK(model.zombies.size() == 1);

    CHECK(model.glasses.size() == 0);
    CHECK(model.score()==50);

    CHECK(model.lives()==2);

    // (6) GLASS HITS WALL 2 MORE TIMES -> 0 lives
    model.spawn_glass();
    model.on_frame(100.0);
    CHECK(model.lives()==1);
    CHECK(model.glasses.size()==0);

    // **** specification 10 & 11 ****
    model.spawn_glass();
    model.on_frame(100.0);
    CHECK(model.lives()==0);
    CHECK(model.glasses.size()==0);
    CHECK(model.game_state() == GameState::game_over);
    CHECK(model.score() == 50);
}

//
// TODO: Write preliminary model tests.
//
// These tests should demonstrate your functional requirements.
//
