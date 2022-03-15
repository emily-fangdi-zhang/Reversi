#include "controller.hxx"

Controller::Controller(int size)
        : Controller(size, size)
{ }

Controller::Controller(int width, int height)
        : model_(width, height),
          view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& sprites)
{
    view_.draw(sprites, pos_mouse);
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
Controller::on_mouse_up(ge211::Mouse_button, ge211::Posn<int> mouse)
{
    Model::Position pos_board = view_.screen_to_board(mouse);

    if (model_.find_move(pos_board) != nullptr) {
        model_.play_move(pos_board);
    }
}

void
Controller::on_mouse_move(ge211::Posn<int> pos)
{
    pos_mouse = pos;
}

void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('q')) {
        quit();
    }
}

