#include "Medic.h"
#include<cassert>
#include"Exceptions.h"
using namespace mtm;

Medic::Medic(Team team, units_t health, units_t ammo, units_t range,
             units_t power, int row, int col) : Character(team, health, ammo, 5, power, row, col) {}


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
            increaseHealth(power, ptr_character_attacked);//increase health for who's in the targeted cell
            return;
        }
        
        if (ammo < 1) {
            throw OutOfAmmo();
        }
        
        ammo--;
        decreaseHealth(power, ptr_character_attacked, health_zero);//update the health value of the rival in the intial attacked cell
        return;
    }
    
    assert(ptr_character_attacked == nullptr);
    throw IllegalTarget();
    
}

void Medic::reload(const GridPoint& coordinates) {
    ammo += 5;
}


void Medic::print(std::ostream& os) const {
    if (team == CROSSFITTERS) {
        os << "m";//no new line because it should be continuos
    }
    if (team == POWERLIFTERS) {
        os << "M";
    }
}

std::ostream& operator<<(std::ostream& os, const Medic& medic) {
    medic.print(os);
    return os;
    
}

