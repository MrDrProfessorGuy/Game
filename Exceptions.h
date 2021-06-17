#ifndef GAME_EXCEPTIONS_H
#define GAME_EXCEPTIONS_H
#include <exception>
#include <string>

namespace mtm {
    
    class Exceptions : public std::exception {
    public:
        
        class IllegalArgument {
            const char* what() const noexcept{
                return "";
            }
    
        };

        
        
        
        
    };
    
    
    class IllegalCell : public Exceptions {};
    class CellEmpty : public Exceptions {};
    class MoveTooFar : public Exceptions {};
    class CellOccupied : public Exceptions {};
    class OutOfRange : public Exceptions {};
    class OutOfAmmo : public Exceptions {};
    class IllegalTarget : public Exceptions {};
    
    
    
    
}





#endif //GAME_EXCEPTIONS_H