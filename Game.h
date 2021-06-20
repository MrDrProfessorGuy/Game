#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "Auxiliaries.h"
#include "board.h"
#include "Exceptions.h"
#include <memory>



namespace mtm {
    class Game {
    
    public:
        Game(int height, int width);
        ~Game() = default;
        Game(const Game& other) = default;
        Game& operator=(const Game& other) = default;
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                                        units_t health, units_t ammo,
                                                        units_t range, units_t power);
        void move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        void attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        void reload(const GridPoint& coordinates);
        bool isOver(Team* winningTeam = NULL) const;
        std::ostream& printGameBoard(std::ostream& os, const char* begin,
                                     const char* end, unsigned int width);
        
        friend std::ostream& operator<<(std::ostream& stream, const Game game);
    
    private:
        int height;
        int width;
        Board board_game;
    };
    
    std::ostream& operator<<(std::ostream& stream, const Game game);
    
    
}



#endif //GAME_GAME_H