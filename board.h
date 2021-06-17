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
        typedef std::vector< std::vector< std::shared_ptr<Character>>> GameBoard ;
        
        Board(int width, int height);
        Board(const Board& other);
        Board& operator=(const Board& other);
        ~Board();
        
        void addCharacter(GridPoint grid_point, std::shared_ptr<Character> character);
        void removeCharacter(GridPoint grid_point);
        void moveCharacter(GridPoint src_coordinates, GridPoint dst_coordinates);
        std::shared_ptr<Character> getCharacter(const GridPoint& grid_point);
        void attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        void reload(const GridPoint& coordinates);
        friend std::ostream& operator<<(std::ostream& stream, const Board board);

    private:
        typedef std::vector< std::shared_ptr<Character>> GameBoardCol;
        int width;
        int height;
        GameBoard game_board;
    
        bool validCoordinate(const GridPoint& grid_point);
        bool cellIsEmpty(const GridPoint& grid_point);
    
    };
    
    
    
    
}
#endif //GAME_BOARD_H
