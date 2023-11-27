#include "Food.h"

Food::Food()
{

}

Food::~Food()
{

}

void Food::generateFood(objPosArrayList* blockOff)
{
    srand(time(NULL));
    bool generate = false;
    char rand_symbol;
    objPos rand_coord;
    GameMechs GM;
    objPos tempBlockOff;

    int coordV[28][13] = {0};

    while(!generate)
    {
        int _Flag = 1;
        rand_coord.setObjPos((rand() % (GM.getBoardSizeX() - 2)) + 1, (rand() % (GM.getBoardSizeY() - 2)) + 1, '0');
        for(int i = 0 ; i < blockOff -> getSize() ; i++)
        {
            blockOff -> getElement(tempBlockOff, i);
            if(rand_coord.x == tempBlockOff.x && rand_coord.y == tempBlockOff.y)
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
                foodPos.setObjPos(rand_coord);
                generate = true;
            }
        }
    }


}

void Food::getFoodPos(objPos &returnPos)
{
    returnPos.setObjPos(foodPos);
}