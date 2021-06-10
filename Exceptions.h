#ifndef GAME_EXCEPTIONS_H
#define GAME_EXCEPTIONS_H
#include <exception>




namespace mtm{
    
    class Exceptions : public std::exception {
    public:
        
        Exceptions();
        const char* what() const noexcept override;
        
        class IllegalArgument{};
        class IllegalCell {};
        class CellEmpty {};
        class MoveTooFar {};
        class CellOccupied {};
        class OutOfRange {};
        class OutOfAmmo {};
        class IllegalTarget {};
        
        
        
        
    };
 
    
    
    
    
    
    
}





#endif //GAME_EXCEPTIONS_H
