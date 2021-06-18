#include "board.h"
#include"Character.h"
#include "Exceptions.h"
#include"Auxiliaries.h"
#include"Soldier.h"
#include"Medic.h"
#include"Sniper.h"
#include<vector>
#include<memory>

using namespace mtm;


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

Board::Board(int width, int height) : width(width), height(height),count_cross_fitters(0),
                                    count_power_lifters(0), game_board(height, GameBoardCol(width, nullptr)) {
    if (height <= 0 || width <= 0) {
        throw IllegalArgument();
    }
    
}

Board::Board(const Board& other){
    width = other.width;
    height = other.height;
    count_cross_fitters = other.count_cross_fitters;
    count_power_lifters = other.count_power_lifters;
    
    game_board = GameBoard(height, GameBoardCol(height, nullptr));
    
    for (int board_row = 0; board_row < height; board_row++) {
        for (int board_col = 0; board_col < height; board_col++) {
            Character* temp_ptr_character = other.game_board[board_row][board_col]->clone();
            game_board[board_row][board_col].reset(temp_ptr_character);
        }
    }
    
}

Board& Board::operator=(const Board& other) {
    if (this == &other) {
        return *this;
    }
    width = other.width;
    height = other.height;
    GameBoard board_copy(height, GameBoardCol(width, nullptr));
    for (int board_row = 0; board_row < height; board_row++) {
        for (int board_col = 0; board_col < height; board_col++) {
            Character* temp_ptr_character = other.game_board[board_row][board_col]->clone();
            game_board[board_row][board_col].reset(temp_ptr_character);
        }
    }
    return *this;
}

Board::~Board() {
    for (int row_board = 0; row_board < height; row_board++) {
        for (int col_board = 0; col_board < width; col_board++) {
            game_board[row_board][col_board].reset();
        }
    }
}

void Board::addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character) {
    bool point_valid = validCoordinate(coordinates);
    if (!point_valid) {
        throw IllegalCell();
    }
    
    if (cellIsEmpty(coordinates)) {
        throw CellOccupied();
    }
    
    character->addCrossOrPowerCount(&count_cross_fitters, &count_power_lifters);//to use in isOver
    
    GridPoint point_to_move(invalid_location, invalid_location);//move receives two parameters
    character->Character::move(point_to_move, coordinates);//uppdate location in Character
    game_board[coordinates.row][coordinates.col] = character;
}

std::shared_ptr<Character> Board:: makeCharacter(CharacterType type, Team team,
                                                 units_t health, units_t ammo, units_t range, units_t power) {
    if (health <= 0) {
        throw IllegalArgument();
    }
    if (type == SOLDIER) {
        Soldier(team, health, ammo, range, power, invalid_location, invalid_location);
    }
    if (type == MEDIC) {
        Medic(team, health, ammo, range, power, invalid_location, invalid_location);
        
    }
    if (type == SNIPER) {
        Sniper(team, health, ammo, range, power, invalid_location, invalid_location);
        
    }
}

std::shared_ptr<Character> Board::getCharacter(const GridPoint& grid_point) {
    bool point_valid = validCoordinate(grid_point);
    if (!point_valid) {
        throw IllegalCell();
    }
    return game_board[grid_point.col][grid_point.row];//if empty okay because we intialize cells to nullptr
}

void Board::move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) {
    bool src_valid = validCoordinate(src_coordinates);
    bool dst_valid = validCoordinate(dst_coordinates);
    if (!src_valid || !dst_valid) {
        throw IllegalCell();
    }
    std::shared_ptr<Character> ptr_character_src= game_board[src_coordinates.row][src_coordinates.col];
    if (ptr_character_src == nullptr) {
        throw CellEmpty();
    }
    
    std::shared_ptr<Character> ptr_dst_character = getCharacter(dst_coordinates);
    ptr_character_src->Character::move(ptr_dst_character,src_coordinates, dst_coordinates);
}

void Board::removeCharacter(GridPoint grid_point) {
    bool point_valid = validCoordinate(grid_point);
    if (!point_valid) {
        throw IllegalCell();
    }
    std::shared_ptr<Character> ptr_character_src = game_board[grid_point.row][grid_point.col];
    if (ptr_character_src == nullptr) {
        throw CellEmpty();
    }
    
    ptr_character_src.reset();
    //what aboit the character it used to point at?
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
    bool health_zero = false;
    
    
    //the "1" in function call is an indication that we are calling attack for the first time
    ptr_character_attacker->attack(ptr_character_attacked, src_coordinates, dst_coordinates, 1, &health_zero);
    if (health_zero == true) {
        removeCharacter(dst_coordinates);
    }
    
    if (typeid(ptr_character_attacker) == typeid(SOLDIER)) {
        std::shared_ptr<Character> ptr_character_first_attacked = game_board[dst_coordinates.row][dst_coordinates.col];
        std::shared_ptr<Character> ptr_character_to_check;
        
        for (int board_row = 0; board_row < height; ++board_row) {
            
            for (int board_col = 0; board_col < width; ++board_col) {
                
                ptr_character_to_check = game_board[board_row][board_col];
                GridPoint src_new_coordinates(board_row, board_col);
                health_zero = false;
                if (ptr_character_to_check) {
                    continue; //if there's not character no need to call attack
                }
                ptr_character_first_attacked->attack(ptr_character_to_check, dst_coordinates, src_new_coordinates, false, &health_zero);
                if (health_zero == true) {
                    removeCharacter(src_new_coordinates);
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
    if (count_cross_fitters > 0 && count_power_lifters == 0) {
        if (winningTeam != NULL) {
            *winningTeam = CROSSFITTERS;
        }
        return true;
    }
    
    if(count_power_lifters > 0 && count_cross_fitters == 0) {
        if (winningTeam != NULL) {
            *winningTeam = POWERLIFTERS;
        }
        return true;
    }
    
    return false;
}


