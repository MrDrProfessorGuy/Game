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
        units_t move_range;
        units_t attack_range;
        units_t power;
        GridPoint location;
        
        virtual bool moveIsValid(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const;
        virtual bool attackInRange(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const = 0;
        virtual bool validTarget(const GridPoint& src_coordinates, const GridPoint& dst_coordinates
                                 ,const std::shared_ptr<Character>& opponent) const = 0;
        virtual bool isTeamMate(const std::shared_ptr<Character>& character) const;
    
    public:
        Character(Team team, units_t health, units_t ammo, units_t attack_range
                  , units_t power, int row, int col);
        Character(const Character& other) = default;
        Character& operator=(const Character& other) = default;
        virtual ~Character() = default;
        
        virtual Character* clone() const = 0;
        void move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        void set_location(const GridPoint& coordinates);
        virtual void reload(const GridPoint& coordinates) = 0;
        virtual void attack(std::shared_ptr<Character> opponent, const GridPoint& src_coordinates,
                            const GridPoint& dst_coordinates, bool check_range, bool* killed_opponent) = 0;
        void decreaseHealth(units_t amount, bool *is_dead);
        void increaseHealth(units_t amount);
        void addCrossOrPowerCount(int* count_cross_fitters, int* count_power_lifters);
        Team getTeam();
        virtual void print(std::ostream& stream) const =0;
        // friend std::ostream& operator<<(std::ostream& stream, const Character& character);
        
        
    };
    
    std::ostream& operator<<(std::ostream& stream, const Character& character);
    
}

#endif //GAME_CHARACTER_H