#ifndef GAME_GAME_H
#define GAME_GAME_H

#include "Auxiliaries.h"
#include "Character.h"
#include "Exceptions.h"
#include <memory>




class Game {



public:
    Game(int height, int width);
    ~Game();
    Game(const Game& other);
    Game& operator=(const Game& other);
    
    void addCharacter(const mtm::GridPoint& coordinates, std::shared_ptr<Character> character);
    static std::shared_ptr<Character> makeCharacter(mtm::CharacterType type, mtm::Team team,
                                                    mtm::units_t health, mtm::units_t ammo,
                                                    mtm::units_t range, mtm::units_t power);
    
    void move(const mtm::GridPoint & src_coordinates, const mtm::GridPoint & dst_coordinates);
    void attack(const mtm::GridPoint & src_coordinates, const mtm::GridPoint & dst_coordinates);
    void reload(const mtm::GridPoint & coordinates);
    bool isOver(mtm::Team* winningTeam=NULL) const;
    std::ostream& printGameBoard(std::ostream& os, const char* begin,
                                 const char* end, unsigned int width) const;
    
    
    
    
};













#endif //GAME_GAME_H
