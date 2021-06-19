#include"Game.h"

using namespace mtm;

Game::Game(int height, int width): height(height), width(width), board_game(width, height){
}

void Game:: addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character){
    board_game.addCharacter(coordinates, character);
}
std::shared_ptr<Character> Game:: makeCharacter(CharacterType type, Team team, units_t health, units_t ammo,
                                                units_t range, units_t power){
    return Board::makeCharacter(type, team, health, ammo, range, power);
}

void Game::move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) {
    board_game.move(src_coordinates, dst_coordinates);
}
void Game::attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates){
    board_game.attack(src_coordinates, dst_coordinates);
}
void Game::reload(const GridPoint& coordinates){
    board_game.reload(coordinates);
}
bool Game::isOver(Team* winningTeam) const{
    return board_game.isOver(winningTeam);
}

std::ostream& mtm::operator<<(std::ostream& stream, const Game game){
    return stream << game.board_game;
}
