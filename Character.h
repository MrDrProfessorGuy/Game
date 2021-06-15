#ifndef GAME_CHARACTER_H
#define GAME_CHARACTER_H

#include<cstdio>
#include"Auxiliaries.h"
#include<memory>
#include<vector>

namespace mtm {
    class Character {
    protected:
        Team team;
        units_t health;
        units_t ammo;
        units_t range;
        units_t power;
        GridPoint location;
        //add to implement same row and same col
        virtual bool moveIsValid(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const = 0;
        virtual bool attackIsValid(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const = 0;
    
    public:
        //maybe location shouldn't be here? so it won't create a mofa3 of Character?
        Character(Team team, units_t health, units_t ammo, units_t range, units_t power, int row, int col);
        Character(const Character& other) = default; // right, even for location?
        Character& operator=(const Character& other) = default;//again make sure
        virtual ~Character() = default;//make sure?
        
        virtual Character* clone() const = 0;
        virtual bool move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        virtual void reload() = 0;
        virtual void attack(std::shared_ptr<Character> ptr_character) = 0;
        //virtual AttackMatrix getAttackMatrix(const GridPoint& attack_coordinates)=0;
    };
    
}


#endif //GAME_CHARACTER_H
