#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <iostream>
#include <map>
#include <memory>
#include "Character.h"
#include "Auxiliaries.h"

class Board {

    int width;
    int length;
    
    std::map <mtm::GridPoint, std::shared_ptr<Character>> board;

public:
    
    Board(int width, int length);
    ~Board();
    Board(const Board& board);
    
    
    
    void moveCharacter(mtm::GridPoint src_coordinates, mtm::GridPoint dst_coordinates);
    friend std::ostream& operator<<(std::ostream& stream, const Character character);

};





#endif //GAME_BOARD_H
