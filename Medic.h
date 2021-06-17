#include"Character.h"

namespace mtm {
    class Medic : public Character {
    private:
        bool attackIsValid(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const override;
    
    public:
        Medic(Team team, units_t health, units_t ammo, units_t range,
              units_t power, int row, int col);
        
        Medic(const Medic& other);
        
        Medic& operator=(const Medic& other);
        
        ~Medic() = default;
        
        Character* clone() const override;
        
        bool move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) override;
        
        void reload(const GridPoint& coordinates) override;
        
        void attack(std::shared_ptr<Character> ptr_character_attacked, const GridPoint& src_coordinates, const GridPoint& dst_coordinates, bool check_range, bool* health_zero) override;
        
        friend std::ostream& operator<<(std::ostream& stream, const Medic& medic);
        
    };
    
    
    std::ostream& operator<<(std::ostream& stream, const Medic& medic);
    
}

