#ifndef FOOD_H
#define FOOD_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Food
{
    private:
        objPosArrayList* foodBucket;

    public:
        Food();
        ~Food();

        void generateFood(objPosArrayList* blockOff);
        objPosArrayList* getFoodPos();

};

#endif