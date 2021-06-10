#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <iostream>
#include <map>
#include <memory>
#include "Character.h"
#include "Auxiliaries.h"

class Board {
public:
    int width;
    int length;
    
    std::map <mtm::GridPoint, std::shared_ptr<Character>> board;
    
    
    Board(int width, int length);
    ~Board();
    Board(const Board& board);
    
    
    


};





#endif //GAME_BOARD_H
