#include "Food.h"

Food::Food()
{
    foodBucket = new objPosArrayList();
}

Food::~Food()
{
    delete foodBucket;
}

void Food::generateFood(objPosArrayList* blockOff)
{
    srand(time(NULL));
    int generate = 0;
    char rand_symbol;
    objPos rand_coord;
    GameMechs GM;
    objPos tempBlockOff;

    int coordV[28][13] = {0};
    int size = foodBucket -> getSize();
    while(size > 0)
    {
        foodBucket -> removeHead();
        size --;
    }

    while(generate != 3)
    {
        int _Flag = 1;
        rand_coord.setObjPos((rand() % (GM.getBoardSizeX() - 2)) + 1, (rand() % (GM.getBoardSizeY() - 2)) + 1, '0');
        for(int i = 0 ; i < blockOff -> getSize() ; i++)
        {
            blockOff -> getElement(tempBlockOff, i);
            if(tempBlockOff.isPosEqual(&rand_coord))
            {
                _Flag = 0;
                break;
            }
        }
        if(_Flag)
        {
            if(coordV[rand_coord.x - 1][rand_coord.y - 1] == 0)
            {
                coordV[rand_coord.x - 1][rand_coord.y - 1]++;
                foodBucket -> insertHead(rand_coord);
                generate ++;
            }
        }
    }

    while(generate != 5)
    {
        int _Flag = 1;
        rand_coord.setObjPos((rand() % (GM.getBoardSizeX() - 2)) + 1, (rand() % (GM.getBoardSizeY() - 2)) + 1, '1');
        for(int i = 0 ; i < blockOff -> getSize() ; i++)
        {
            blockOff -> getElement(tempBlockOff, i);
            if(tempBlockOff.isPosEqual(&rand_coord))
            {
                _Flag = 0;
                break;
            }
        }
        if(_Flag)
        {
            if(coordV[rand_coord.x - 1][rand_coord.y - 1] == 0)
            {
                coordV[rand_coord.x - 1][rand_coord.y - 1]++;
                foodBucket -> insertHead(rand_coord);
                generate ++;
            }
        }
    }


}

objPosArrayList* Food::getFoodPos()
{
    return foodBucket;
}