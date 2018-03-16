#ifndef PLAYERHOLDER_CPP
#define PLAYERHOLDER_CPP

#include "PlayerHolder.h"

namespace Generic
{
    PlayerHolder::PlayerHolder(unsigned int k, std::string p)
    {
        this->setKey(k);
        this->setPrintMark(p);
    }

    PlayerHolder::~PlayerHolder()
    {
    }

    unsigned int PlayerHolder::getKey()
    {
        return this->key;
    }

    void PlayerHolder::setPrintMark(std::string p)
    {
        this->printMark = p;
    }

    std::string PlayerHolder::getPrintMark()
    {
        return this->printMark;
    }

    void PlayerHolder::setKey(unsigned int k)
    {
        this->key = k;
    }
}

#endif /* PLAYERHOLDER_CPP */