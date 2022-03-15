#include "view.hxx"

// Convenient type aliases:
using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

// You can change this or even determine it some other way:
static int const grid_size = 8;

View::View(Model const& model)
        : model_(model),
        dark_sprite(grid_size * 0.45, Color::black()),
        light_sprite(grid_size * 0.45, Color::white()),
        green_tile_sprite ({int(grid_size * 0.90),
                            int(grid_size * 0.90)},
                           Color::from_rgba(0, 134, 0)),
        grey_sprite(grid_size * 0.45,
                    Color::from_rgba(169, 169, 169)),
        red_tile_sprite({int(grid_size * 0.90),
                         int(grid_size * 0.90)},
                        Color::medium_red()),
        small_dark_sprite(grid_size * 0.20, Color::black()),
        small_light_sprite(grid_size * 0.20, Color::white())
{ }

void View::draw(Sprite_set& set, ge211::Posn<int> position)
{
    for (Position pos:model_.board()) {

        // create background
        set.add_sprite(green_tile_sprite,
                       board_to_screen(pos), 0);

        // setting down dark
        if (model_[pos] == Player::dark) {
            add_player_sprite(set, Player::dark,
                              board_to_screen(pos), 3);


        // setting down light
        } else if (model_[pos] == Player::light) {
            add_player_sprite(set, Player::light,
                              board_to_screen(pos), 3);
        }
    }

    Position pos_mouse = screen_to_board(position);
    const Move* move = model_.find_move(pos_mouse);

    // invalid move
    if (move == nullptr) {

        int xval = board_to_screen(pos_mouse).x + grid_size/4;
        int yval = board_to_screen(pos_mouse).y + grid_size/4;
        Position centered = {xval, yval};

        // dark player
        if (model_.turn() == Player::dark) {
            set.add_sprite(small_dark_sprite,centered, 2);

        // light player
        } else if (model_.turn() == Player::light) {
            set.add_sprite(small_light_sprite,centered, 2);
        }

    // valid move
    } else {
        set.add_sprite(red_tile_sprite,
                       board_to_screen(pos_mouse), 3);
    }
}

View::Dimensions
View::initial_window_dimensions() const
{
    // You can change this if you want:
    return grid_size * model_.board().dimensions();
}

std::string
View::initial_window_title() const
{
    // You can change this if you want:
    return "Reversi";
}

View::Position
View::board_to_screen(Model::Position logical) const
{
    int xval = logical.x * grid_size;
    int yval = logical.y * grid_size;

    return View::Position (xval, yval);
}

Model::Position
View::screen_to_board(View::Position physical) const
{
    int xval = physical.x / grid_size;
    int yval = physical.y / grid_size;

    return Model::Position (xval, yval);
}

void
View::add_player_sprite(
        ge211::Sprite_set& sprites,
        Player which,
        ge211::Posn<int> physical,
        int z_layer) const
{
    // if game is not over
    if (model_.turn() != Player::neither) {
        z_layer = 3;

        if (which == Player::dark) {
            sprites.add_sprite(dark_sprite, physical, z_layer);

        } if (which == Player::light) {
            sprites.add_sprite(light_sprite, physical, z_layer);
        }
    }

    // if game is over
    if (model_.turn() == Player::neither) {

        // turn non-winning tiles grey
        // if tie
        if (model_.winner() == Player::neither) {

            // turn all tiles grey
            for (Position pos:model_.board()) {

                if ((model_[pos] == Player::dark) || (model_[pos] ==
                Player::light)) {
                    z_layer = 4;
                    sprites.add_sprite(grey_sprite,
                                       board_to_screen(pos),
                                       z_layer);
                }
            }

        // if light wins
        } else if (model_.winner() == Player::light) {

            // turn all dark tiles grey
            for (Position pos:model_.board()) {

                if (model_[pos] == Player::dark) {
                    z_layer = 4;
                    sprites.add_sprite(grey_sprite,
                                       board_to_screen(pos),
                                       z_layer);

                // reprint winning tiles
                } else if (model_[pos] == Player::light) {
                    z_layer = 4;
                    sprites.add_sprite(light_sprite,
                                       board_to_screen(pos),
                                       z_layer);
                }
            }

        // if dark wins
        } else if (model_.winner() == Player::dark) {
            // turn all light tiles grey
            for (Position pos:model_.board()) {

                if (model_[pos] == Player::light) {
                    z_layer = 3;
                    sprites.add_sprite(grey_sprite,
                                       board_to_screen(pos),
                                       z_layer);

                // reprint winning tiles
                } else if (model_[pos] == Player::dark) {
                    z_layer = 4;
                    sprites.add_sprite(dark_sprite,
                                       board_to_screen(pos),
                                       z_layer);
                }
            }
        }
    }
}