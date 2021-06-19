#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <iostream>
#include <vector>
#include "Auxiliaries.h"
#include "Character.h"


namespace mtm {
    class Board {
    
    public:
        static const int invalid_location = -1;
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
        typedef std::vector< std::shared_ptr<Character>> GameBoardCol;
        int width;
        int height;
        //int count_cross_fitters;
        //int count_power_lifters;
        int team_character_count[2];
        GameBoard game_board;
        
        bool validCoordinate(const GridPoint& grid_point);
        bool cellIsEmpty(const GridPoint& grid_point);
        void clearGameBoard();
    
        
    };
    std::ostream& operator<<(std::ostream& os, const Board& board);

}
#endif //GAME_BOARD_H