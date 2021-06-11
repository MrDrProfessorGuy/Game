#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#include <iostream>
#include <vector>
#include "Auxiliaries.h"
#include "board.h"



class DamageBoard{
public:


};



class Character {
public:
    
    virtual ~Character(){
    
    }
    virtual Character* clone() const = 0;
    
    virtual void reload() = 0;
    virtual void attack(mtm::GridPoint attack_coordinate) const = 0;
    
    friend std::ostream& operator<<(std::ostream& stream, const Character character) {
    
    }

protected:
    mtm::Team team;
    mtm::units_t health;
    mtm::units_t ammo;
    mtm::units_t range;
    mtm::units_t power;
    
    mtm::units_t attack_cost;
    mtm::units_t reload_addition;
    //bool in_game;
    char identifier;
    
    virtual bool validMove(mtm::GridPoint& src_coordinates, mtm::GridPoint& dst_coordinates) const = 0;
    virtual bool validAttack(mtm::GridPoint& src_coordinates, mtm::GridPoint& dst_coordinates) const = 0;
    bool same_team(const Character character) const{
    
    }
    
};



#endif //GAME_CHARACTER_H
