#include "board.h"
#include "Exceptions.h"
#include"Soldier.h"
#include"Medic.h"
#include"Sniper.h"
#include <memory>

using namespace mtm;
const int Board::invalid_location;


bool Board::validCoordinate(const GridPoint& grid_point) {
    if (grid_point.row < 0 || grid_point.col < 0 || grid_point.row >= height || grid_point.col >= width) {
        return false;
    }
    
    return true;
}

bool Board::cellIsEmpty(const GridPoint& grid_point) {
    if (getCharacter(grid_point) == nullptr) {
        return true;
    }
    return false;
}

Board::Board(int width, int height) : width(width), height(height),team_character_count(),
                                    game_board(height, GameBoardCol(width, nullptr)) {
    if (height <= 0 || width <= 0) {
        throw IllegalArgument();
    }
    
}

Board::Board(const Board& other){
    width = other.width;
    height = other.height;
    team_character_count[CROSSFITTERS] = other.team_character_count[CROSSFITTERS];
    team_character_count[POWERLIFTERS] = other.team_character_count[POWERLIFTERS];
    
    game_board = GameBoard(height, GameBoardCol(width, nullptr));
    try {
        for (int board_row = 0; board_row < height; board_row++) {
            for (int board_col = 0; board_col < width; board_col++) {
                if (other.game_board[board_row][board_col] != nullptr){
                    Character* character_copy = other.game_board[board_row][board_col]->clone();
                    game_board[board_row][board_col].reset(character_copy);
                }
            }
        }
    }
    catch (std::bad_alloc&) {
        clearGameBoard();
        throw;
    }
    
    
}

Board& Board::operator=(const Board& other) {
    if (this == &other) {
        return *this;
    }
    width = other.width;
    height = other.height;
    team_character_count[CROSSFITTERS] = other.team_character_count[CROSSFITTERS];
    team_character_count[POWERLIFTERS] = other.team_character_count[POWERLIFTERS];
    GameBoard game_board_copy(height, GameBoardCol(width, nullptr));
    try{
        for (int board_row = 0; board_row < height; board_row++) {
            for (int board_col = 0; board_col < width; board_col++) {
                Character* temp_ptr_character = other.game_board[board_row][board_col]->clone();
                game_board_copy[board_row][board_col].reset(temp_ptr_character);
            }
        }
    }
    catch (std::bad_alloc&) {
        for (int board_row = 0; board_row < height; board_row++) {
            for (int board_col = 0; board_col < width; board_col++) {
                game_board_copy[board_row][board_col].reset();
            }
        }
        throw;
    }
    
    clearGameBoard();
    game_board = game_board_copy;
    return *this;
}

Board::~Board() {
    clearGameBoard();
}

void Board::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character) {
    bool point_valid = validCoordinate(coordinates);
    if (!point_valid) {
        throw IllegalCell();
    }
    
    if (!cellIsEmpty(coordinates)) {
        throw CellOccupied();
    }
    
    //character->addCrossOrPowerCount(&count_cross_fitters, &count_power_lifters);//to use in isOver
    team_character_count[character->getTeam()]++;
    
    character->Character::set_location(coordinates);
    game_board[coordinates.row][coordinates.col] = character;
}

std::shared_ptr<Character> Board:: makeCharacter(CharacterType type, Team team,
                                                 units_t health, units_t ammo, units_t range, units_t power) {
    if (health <= 0 || ammo < 0 || power < 0) {
        throw IllegalArgument();
    }
    std::shared_ptr<Character> shared_ptr;
    if (type == SOLDIER) {
        shared_ptr = std::make_shared<Soldier>(team, health, ammo, range, power, invalid_location, invalid_location);
    }
    if (type == MEDIC) {
        shared_ptr = std::make_shared<Medic>(team, health, ammo, range, power, invalid_location, invalid_location);
    }
    if (type == SNIPER) {
        shared_ptr = std::make_shared<Sniper>(team, health, ammo, range, power, invalid_location, invalid_location);
    }
    
    return shared_ptr;
}

std::shared_ptr<Character> Board::getCharacter(const GridPoint& grid_point) {
    bool point_valid = validCoordinate(grid_point);
    if (!point_valid) {
        throw IllegalCell();
    }
    return game_board[grid_point.row][grid_point.col];//if empty okay because we intialize cells to nullptr
}

void Board::move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) {
    bool src_valid = validCoordinate(src_coordinates);
    bool dst_valid = validCoordinate(dst_coordinates);
    if (!src_valid || !dst_valid) {
        throw IllegalCell();
    }
    std::shared_ptr<Character> ptr_character_src = getCharacter(src_coordinates);
    if (ptr_character_src == nullptr) {
        throw CellEmpty();
    }
    std::shared_ptr<Character> ptr_dst_character = getCharacter(dst_coordinates);
    if (ptr_dst_character != nullptr) {
        throw CellOccupied();
    }
    
    ptr_character_src->move(src_coordinates, dst_coordinates);
    game_board[dst_coordinates.row][dst_coordinates.col] = ptr_character_src;
    game_board[src_coordinates.row][src_coordinates.col].reset();
}

void Board::removeCharacter(GridPoint grid_point) {
    bool point_valid = validCoordinate(grid_point);
    if (!point_valid) {
        throw IllegalCell();
    }
    std::shared_ptr<Character> character = getCharacter(grid_point);
    if (game_board[grid_point.row][grid_point.col] == nullptr) {
        throw CellEmpty();
    }
    
    team_character_count[character->getTeam()]--;
    game_board[grid_point.row][grid_point.col].reset();
}

void Board::attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) {
    
    bool src_valid = validCoordinate(src_coordinates);
    bool dst_valid = validCoordinate(dst_coordinates);
    if (!src_valid || !dst_valid) {
        throw IllegalCell();
    }
    std::shared_ptr<Character> ptr_character_attacker = game_board[src_coordinates.row][src_coordinates.col];
    std::shared_ptr<Character> ptr_character_attacked = game_board[dst_coordinates.row][dst_coordinates.col];
    if (ptr_character_attacker == nullptr) {
        throw CellEmpty();
    }
    
    //a flag to know whether the health of rival is zero or not in order to delete
    bool killed_opponent = false;
    
    
    //the "1" in function call is an indication that we are calling attack for the first time
    ptr_character_attacker->attack(ptr_character_attacked, src_coordinates, dst_coordinates
                                   , true, &killed_opponent);
    if (killed_opponent) {
        removeCharacter(dst_coordinates);
    }
    
    Soldier* attacker = dynamic_cast<Soldier*>(ptr_character_attacker.get());
    if (attacker != nullptr) {
        std::shared_ptr<Character> opponent;
        
        for (int board_row = 0; board_row < height; ++board_row) {
            for (int board_col = 0; board_col < width; ++board_col) {
                opponent = game_board[board_row][board_col];
                GridPoint opponent_coordinates(board_row, board_col);
                
                killed_opponent = false;
                if (opponent == nullptr || opponent_coordinates == src_coordinates) {
                    continue; //if there's not character no need to call attack
                }
                
                attacker->attack(opponent, dst_coordinates, opponent_coordinates
                                               , false, &killed_opponent);
                if (killed_opponent) {
                    removeCharacter(opponent_coordinates);
                }
                
            }//second for
            
        }//first for
        
    }//if
    
}//func

void Board::reload(const GridPoint& coordinates) {
    if (!validCoordinate(coordinates)) {
        throw IllegalCell();
    }
    
    if (cellIsEmpty(coordinates)) {
        throw CellEmpty();
    }
    std::shared_ptr<Character> ptr_character = getCharacter(coordinates);
    ptr_character->reload(coordinates);
}

bool Board::isOver(Team* winningTeam) const {
    if (team_character_count[CROSSFITTERS] > 0 && team_character_count[POWERLIFTERS] <= 0) {
        if (winningTeam != NULL) {
            *winningTeam = CROSSFITTERS;
        }
        return true;
    }
    
    if(team_character_count[POWERLIFTERS] > 0 && team_character_count[CROSSFITTERS] <= 0) {
        if (winningTeam != NULL) {
            *winningTeam = POWERLIFTERS;
        }
        return true;
    }
    
    return false;
}

void Board::clearGameBoard() {
    
    for (int board_row = 0; board_row < height; board_row++) {
        for (int board_col = 0; board_col < width; board_col++) {
            game_board[board_row][board_col].reset();
        }
    }
}

std::ostream& mtm::operator<<(std::ostream& os, const Board& board) {
    std::string delimiter = std::string(2 * board.width + 1, '*');
    std::shared_ptr<Character> ptr_character= nullptr;
    
    os << delimiter << std::endl;
    for (int row_board = 0; row_board < board.height; row_board++) {
        
        for (int col_board = 0; col_board < board.width; col_board++) {
            os << "|";
            ptr_character = board.game_board[row_board][col_board];
            if (ptr_character == nullptr) {
                os << " ";
            }
            if (ptr_character != nullptr){
                ptr_character->print(os);
            }
        }
        os << "|" << std::endl;
    }
    os << delimiter;
    return os;
}
