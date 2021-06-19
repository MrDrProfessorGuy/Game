#include"Character.h"

namespace mtm {
    class Sniper : public Character {
    private:
        int count_attacks;
        bool attackIsValid(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const override;
    
    public:
        Sniper(Team team, units_t health, units_t ammo, units_t attack_range
                ,units_t power, int row, int col, int count_attacks = 0);
        
        Sniper(const Sniper& other) = default;
        
        Sniper& operator=(const Sniper& other) = default;
        
        ~Sniper() = default;
        
        Character* clone() const override;
        
        void reload(const GridPoint& coordinates) override;
        
        void attack(std::shared_ptr<Character> ptr_character_attacked, const GridPoint& src_coordinates, const GridPoint& dst_coordinates, bool check_range, bool* health_zero) override;
        
        void print(std::ostream& stream) const override;
        
        //friend std::ostream& operator<<(std::ostream& stream, const Sniper& sniper);
        
    };
    
    
    std::ostream& operator<<(std::ostream& stream, const Sniper& sniper);
    
}

