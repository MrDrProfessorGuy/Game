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
        
        virtual bool moveIsValid(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const;
        virtual bool attackIsValid(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const = 0;
        virtual bool compareTeam(std::shared_ptr<Character> ptr_character);
    
    public:
        Character(Team team, units_t health, units_t ammo, units_t range, units_t power, int row, int col);
        Character(const Character& other) = default;
        Character& operator=(const Character& other) = default;
        virtual ~Character() = default;
        
        virtual Character* clone() const = 0;
        virtual bool move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);//make sure to implement just in character
        virtual void reload(const GridPoint& coordinates) = 0;
        virtual void attack(std::shared_ptr<Character> ptr_character_attacked, const GridPoint& src_coordinates,
                            const GridPoint& dst_coordinates, bool check_range, bool* health_zero) = 0;
        friend std::ostream& operator<<(std::ostream& stream, const Character& character);
        bool decreaseHealth(units_t updated_health, std::shared_ptr<Character> ptr_character_attacked, bool* health_zero);
        bool increaseHealth(units_t updated_health, std::shared_ptr<Character> ptr_character_attacked);
        
    };
    
    std::ostream& operator<<(std::ostream& stream, const Character& character);
    
}

#endif //GAME_CHARACTER_H
