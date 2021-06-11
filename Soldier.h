#ifndef GAME_SOLDIER_H
#define GAME_SOLDIER_H


#include "Character.h"



class Soldier : public Character{
    bool validMove(mtm::GridPoint& src_coordinates, mtm::GridPoint& dst_coordinates) const{
        if (mtm::GridPoint::distance(src_coordinates, dst_coordinates) <= range){
            return true;
        }
        return false;
        
    }
    
    bool validAttack(mtm::GridPoint& src_coordinates, mtm::GridPoint& dst_coordinates) const;

public:
    Soldier(mtm::Team character_team, mtm::units_t health_units){
        team = character_team;
        health = health_units;
        ammo = 3;
        range = 3;
        
        attack_cost = 1;
        reload_addition = 3;
        if (team == mtm::POWERLIFTERS){
            identifier = 'S';
        }
        else if (team == mtm::CROSSFITTERS){
            identifier = 's';
        }
    
    }
    ~Soldier();
    Character* clone() const override;
    
    
    void reload(){
        ammo += reload_addition;
    }
    void attack(Character& opponent) const;
    
    
    
    
    
};


#endif //GAME_SOLDIER_H
