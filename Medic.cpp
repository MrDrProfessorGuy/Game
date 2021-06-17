#include "Medic.h"
#include<cassert>
#include"Exceptions.h"
using namespace mtm;

Medic::Medic(Team team, units_t health, units_t ammo, units_t range,
             units_t power, int row, int col) : Character(team, health, ammo, 5, power, row, col) {}

Medic::Medic(const Medic& other) : Character(other) {} //is this considered deafault?
/*
Medic& Medic:: operator=(const Medic& other) {
    Character::operator=(other);//again is this considered default?
}*/

Character* Medic::clone() const {
    return new Medic(*this);
    
}

bool Character::attackIsValid(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const {
    if (!moveIsValid(src_coordinates, dst_coordinates)) {
        return false;
    }
    
    return true;
}

void Medic::attack(std::shared_ptr<Character> ptr_character_attacked, const GridPoint& src_coordinates, const GridPoint& dst_coordinates, bool check_range, bool* health_zero) {
    
    if (!attackIsValid(src_coordinates, dst_coordinates)) {
        throw OutOfRange();
    }
    
    if (ptr_character_attacked != nullptr) {
        if (compareTeam(ptr_character_attacked)) {
            //Medic* ptr_medic = static_cast<Medic*> (ptr_character_attacked);//if this works we can do the whole thing here
            increaseHealth(power, ptr_character_attacked);//increase health for who's in the targeted cell
            return;
        }
        
        if (ammo < 1) {
            throw OutOfAmmo();
        }
        
        ammo--;//ammo is decreased only once per attack
        decreaseHealth(power, ptr_character_attacked, health_zero);//update the power value of the rival in the intial attacked cell
        return;
    }
    
    assert(ptr_character_attacked == nullptr);
    throw IllegalTarget();
    
}

void Medic::reload(const GridPoint& coordinates) {
    ammo += 5;
}

std::ostream& operator<<(std::ostream& stream, const Medic& medic) {
    return stream;
}