#include <string>
#include "Direction.hpp"
#include <vector>
namespace ariel
{
    class Board{
        int numOfRow;
        int numOfCloumn;
    public:
        Board(){
        
        }
        ~Board(){
        
        }
        void post(uint row,uint column,Direction direction,std::string const &ad );
        std::string read(uint row,uint cloumn,Direction direction,uint len);
        void show();
    };
}