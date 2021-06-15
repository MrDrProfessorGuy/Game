#ifndef GAME_BOARD_H
#define GAME_BOARD_H
#include <iostream>
#include <vector>
#include <memory>
#include "Auxiliaries.h"
#include "Character.h"

namespace mtm {
    class Board {
    private:
        int width;
        int length;
        std::vector< std::vector< std::shared_ptr<Character>>> board;
        
        bool validCoordinate(mtm::GridPoint grid_point);
    
    public:
        Board(int width, int length);
        Board(const Board& board);
        Board& operator=(const Board& board);
        ~Board();
        
        
        void addCharacter(GridPoint grid_point, std::shared_ptr<Character> character);
        void removeCharacter(GridPoint grid_point);
        void moveCharacter(GridPoint src_coordinates, GridPoint dst_coordinates);
        std::shared_ptr<Character> getCharacter(GridPoint grid_point);
        void attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        friend std::ostream& operator<<(std::ostream& stream, const Board board);
        
    };
    
}




#endif //GAME_BOARD_H
