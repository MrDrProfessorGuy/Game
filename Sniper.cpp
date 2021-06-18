#include"Exceptions.h"
#include"Sniper.h"
#include<assert.h>


using namespace mtm;

Sniper::Sniper(Team team, units_t health, units_t ammo, units_t range,
               units_t power, int row, int col, int count_attacks) : Character(team, health, ammo, 4, power, row, col), count_attacks(0) {}


Character* Sniper::clone() const {
    return new Sniper(*this);
    
}

bool Sniper::attackIsValid(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const {
    double distance = GridPoint::distance(src_coordinates, dst_coordinates);
    if ((distance <= range) && (distance >= ceil(range / 2))) {
        return true;
    }
    return false;
}

void Sniper::attack(std::shared_ptr<Character> ptr_character_attacked, const GridPoint& src_coordinates, const GridPoint& dst_coordinates, bool check_range, bool* health_zero) {
    if (!attackIsValid(src_coordinates, dst_coordinates)) {
        throw OutOfRange();
    }
    
    if (ptr_character_attacked != nullptr) {
        if (compareTeam(ptr_character_attacked)) {
            return;//should throw IlligalArgument here? it same team
        }
        
        if (ammo < 1) {
            throw OutOfAmmo();
        }
        count_attacks++;
        ammo--;
        if (count_attacks == 3) {
            decreaseHealth(2 * power, ptr_character_attacked, health_zero);//update the health value
            count_attacks = 0;
        }
        decreaseHealth(power, ptr_character_attacked, health_zero);//update the health value
        return;
    }
    
    assert(ptr_character_attacked == nullptr);
    throw IllegalTarget();
    
}

void Sniper::reload(const GridPoint& coordinates) {
    ammo += 2;
}

void Sniper::print(std::ostream& os) const {
    if (team == CROSSFITTERS) {
        os << "s";//no new line because it should be continuos
    }
    if (team == POWERLIFTERS) {
        os << "S";
    }
}

std::ostream& operator<<(std::ostream& os, const Sniper& sniper) {
    sniper.print(os);
    return os;
    
}
