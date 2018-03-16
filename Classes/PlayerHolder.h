#ifndef PLAYERHOLDER_H
#define PLAYERHOLDER_H

#include <string>

namespace Generic
{
    class PlayerHolder
    {
    public:
        
        PlayerHolder(unsigned int k, std::string p);
        
        virtual ~PlayerHolder();
        
        unsigned int getKey();

        void setPrintMark(std::string p);
        
        std::string getPrintMark();
        
    private:
        unsigned int key;
        std::string printMark;
        
        void setKey(unsigned int k);
    };
}

#endif /* PLAYERHOLDER_H */

