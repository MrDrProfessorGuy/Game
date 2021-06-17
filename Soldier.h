#include"Character.h"

namespace mtm {
    class Soldier : public Character {
    private:
        bool attackIsValid(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const override;
    
    public:
        Soldier(Team team, units_t health, units_t ammo, units_t range,
                units_t power, int row, int col);
        
        Soldier(const Soldier& other);
        
        Soldier& operator=(const Soldier& other);
        
        ~Soldier() = default;
        
        Character* clone() const  override;
        
        bool move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) override;
        
        void reload(const GridPoint& coordinates) override;
        
        void attack(std::shared_ptr<Character> ptr_character_attacked, const GridPoint& src_coordinates, const GridPoint& dst_coordinates, bool check_range, bool* health_zero) override;
        
        friend std::ostream& operator<<(std::ostream& stream, const Soldier& soldier);
        
    };
    
    
}