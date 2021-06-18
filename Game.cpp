#include"Game.h"
#include"board.h"
#include "Character.h"
#include <memory>

using namespace mtm;

Game::Game(int height, int width): height(height), width(width), board_game(Board(height, width)){}

void Game:: addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character){}
std::shared_ptr<Character> Game:: makeCharacter(CharacterType type, Team team, units_t health, units_t ammo,
                                                units_t range, units_t power){}

void Game::move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) {}
void Game::attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates){}
void Game::reload(const GridPoint& coordinates){}
bool Game::isOver(Team* winningTeam) const{}

std::ostream& printGameBoard(std::ostream& os, const char* begin,
                             const char* end, unsigned int width){}

std::ostream& operator<<(std::ostream& stream, const Game game){}