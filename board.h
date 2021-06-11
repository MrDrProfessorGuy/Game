#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <iostream>
#include <vector>
#include <memory>
#include "Auxiliaries.h"

template<class T>
class GenericBoard{
private:
    int height;
    int width;
    
    /// T should have a default c'tor 
    std::vector< std::vector< T>> board;

public:
    
    GenericBoard(int board_height, int board_width){
        height = board_height;
        width = board_width;
    
        for (int i = 0; i < ; i++) {
            
        }
    }
    ~GenericBoard();
    GenericBoard(const GenericBoard& board);
    
    void addObject(mtm::GridPoint grid_point, T Object);
    void removeObject(mtm::GridPoint grid_point);
    void moveObject(mtm::GridPoint src_coordinates, mtm::GridPoint dst_coordinates);
    T getObject(mtm::GridPoint grid_point);
    bool validCoordinate(mtm::GridPoint grid_point);
    
};



class Board {
private:
    int width;
    int length;
    
    //std::unordered_map <mtm::GridPoint, std::shared_ptr<Character>> board;
    std::vector< std::vector< std::shared_ptr<Character>>> board;
    
public:
    class Character;
    
    Board(int width, int length);
    ~Board();
    Board(const Board& board);
    
    void addCharacter(mtm::GridPoint grid_point, std::shared_ptr<Character> character);
    void removeCharacter(mtm::GridPoint grid_point);
    void moveCharacter(mtm::GridPoint src_coordinates, mtm::GridPoint dst_coordinates);
    std::shared_ptr<Character> getCharacter(mtm::GridPoint grid_point);
    bool validCoordinate(mtm::GridPoint grid_point);
    
    friend std::ostream& operator<<(std::ostream& stream, const Board board);

};





#endif //GAME_BOARD_H
