#pragma once

#include "model.hxx"

#include <string>

class View
{
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// View rectangles will use `int` coordinates.
    using Rectangle = ge211::Rect<int>;

    /// Constructs a view that knows about the given model.
    explicit View(Model const&);

    void draw(ge211::Sprite_set& set, ge211::Posn<int> position);

    Dimensions initial_window_dimensions() const;

    std::string initial_window_title() const;

    // helper functions
    Model::Position screen_to_board (View::Position physical) const;

private:
    Model const& model_;

    // helper functions

    View::Position board_to_screen (Model::Position logical) const;

    void add_player_sprite(ge211::Sprite_set& sprites, Player which,
                           ge211::Posn<int> physical, int z_layer) const;

    // sprites
    ge211::Circle_sprite const dark_sprite;
    ge211::Circle_sprite const light_sprite;
    ge211::Rectangle_sprite const green_tile_sprite;
    ge211::Circle_sprite const grey_sprite;
    ge211::Rectangle_sprite const red_tile_sprite;
    ge211::Circle_sprite const small_dark_sprite;
    ge211::Circle_sprite const small_light_sprite;
};
