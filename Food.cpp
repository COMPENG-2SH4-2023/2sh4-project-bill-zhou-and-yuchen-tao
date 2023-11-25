#include "Food.h"

Food::Food()
{

}

Food::~Food()
{

}

void Food::generateFood(objPos blockOff)
{
    srand(time(NULL));
    bool generate = false;
    char rand_symbol;
    objPos rand_coord;
    GameMechs GM;

    int coordV[28][13] = {0};

    while(!generate)
    {
        rand_coord.setObjPos((rand() % (GM.getBoardSizeX() - 2)) + 1, (rand() % (GM.getBoardSizeY() - 2)) + 1, '0');
        if(rand_coord.x == blockOff.x && rand_coord.y == blockOff.y)
        {
            continue;
        }
        else
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