#include "model.hxx"

using namespace ge211;

Model::Model(int size)
        : Model(size, size)
{ }

Model::Model(int width, int height)
        : board_({width, height})
{
    compute_next_moves_();
}

Model::Rectangle
Model::board() const
{
    return board_.all_positions();
}

Player
Model::operator[](Position pos) const
{
    return board_[pos];
}

const Move*
Model::find_move(Position pos) const
{
    auto i = next_moves_.find(pos);

    if (i == next_moves_.end()) {
        // Nothing was found, so return NULL (nullptr in C++)
        return nullptr;
    } else {
        // Dereferences the iterator to get the value then returns a pointer
        // to that value. This is safe as the pointer is to a value living
        // within the `next_moves_` structure.
        return &(*i);
    }
}

void
Model::play_move(Position pos)
{
    if (is_game_over()) {
        throw Client_logic_error("Model::play_move: game over");
    }

    const Move* movep = find_move(pos);
    if (movep == nullptr) { // check if there was no such move
        throw Client_logic_error("Model::play_move: no such move");
    }

    really_play_move_(*movep);
}

//
// BELOW ARE HELPER FUNCTIONS
// Our tests will run on the public functions, not the helper functions
// However, these will be extremely useful in writing the above functions
//

Position_set
Model::find_flips_(Position current, Dimensions dir) const
{
    Position_set pset = {};

    // change to the first starting opposite player
    if (board_[current] == Player::neither) {
        current += dir;
    }

    // if position is in bound
    while (board_.good_position(current) && board_[current] !=
    Player::neither) {

        if (board_[current] != turn_) {
            pset[current] = true;
            current += dir;

        // reached the same player
        } else {
            return pset;
        }
    }
    return {};
}

Position_set
Model::evaluate_position_(Position pos) const
{
    Position_set pset = {};

    for (Dims<int> direction:Board::all_directions()) {
        pset |= find_flips_(pos, direction);
    }

    if (pset.empty()) {
        return pset;

    } else {
        pset[pos] = true;
        return pset;
    }
}

void
Model::compute_next_moves_()
{
    next_moves_.clear();

    // opening phase
    if ((board_.count_player(turn_) + board_.count_player(other_player(turn_)))
    < 4) {

        // center four rectangles
        for (Position pos:board_.center_positions()) {

            // check to c if empty
            if (board_[pos] == Player::neither) {
                next_moves_[pos] = Position_set {pos};
            }
        }

    // main phase
    } else {
        for(Position pos:board_.all_positions()) {

            Position_set pos_eval = evaluate_position_(pos);

            // if anything flips
            if (board_[pos] == Player::neither && !pos_eval.empty()) {
                next_moves_[pos] = pos_eval;
            }
        }
    }
}

bool
Model::advance_turn_()
{
    // switch to the other player
    turn_ = other_player(turn_);
    compute_next_moves_();

    return !next_moves_.empty();
}

void
Model::set_game_over_()
{
    turn_ = Player::neither;
    size_t dark = board_.count_player(Player::dark);
    size_t light = board_.count_player(Player::light);

    if (dark > light) {
        winner_ = Player::dark;

    } else if (dark < light) {
        winner_ = Player::light;

    } else {
        winner_ = turn_;
    }
}

void
Model::really_play_move_(Move move)
{
    board_.set_all(move.second, turn_);

    if (!advance_turn_()) {

        if (!advance_turn_()) {
            set_game_over_();
        }

    } else {
        return;
    }

}
