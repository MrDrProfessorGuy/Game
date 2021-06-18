#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <iostream>
#include <vector>
#include <memory>
#include "Auxiliaries.h"
#include "Character.h"

namespace mtm {
    class Board {
    
    public:
        typedef std::vector< std::vector< std::shared_ptr<Character>>> GameBoard;
        
        Board(int width, int height);
        Board(const Board& other);
        Board& operator=(const Board& other);
        ~Board();//likeremove
        
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                                        units_t health, units_t ammo, units_t range, units_t power);
        void move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        void removeCharacter(GridPoint grid_point);//not finished
        void moveCharacter(GridPoint src_coordinates, GridPoint dst_coordinates);
        std::shared_ptr<Character> getCharacter(const GridPoint& grid_point);
        void attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        void reload(const GridPoint& coordinates);
        friend std::ostream& operator<<(std::ostream& os, const Board& board);
        bool isOver(Team* winningTeam = NULL) const;
    
    
    private:
        static const int invalid_location = -1;
        typedef std::vector< std::shared_ptr<Character>> GameBoardCol;
        int width;
        int height;
        int count_cross_fitters;
        int count_power_lifters;
        GameBoard game_board;
        
        bool validCoordinate(const GridPoint& grid_point);
        bool cellIsEmpty(const GridPoint& grid_point);
        
    };
    
    //std::ostream& operator<<(std::ostream& stream, const Board board);
    
    
    std::ostream& operator<<(std::ostream& os, const Board& board) {
        std::shared_ptr<Character> ptr_character= nullptr;
        for (int row_board = 0; row_board < board.height; row_board++) {
            for (int col_board = 0; col_board < board.width; col_board++) {
                ptr_character = board.game_board[row_board][col_board];
                if (ptr_character == nullptr) {
                    os << " ";
                }
                ptr_character->print(os);//true?
            }
        }
        
    }
}
#endif //GAME_BOARD_H