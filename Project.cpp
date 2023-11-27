#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"



using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;
Food* myFood;



void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM -> getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    objPos tempPos;
    myFood = new Food();
    myGM = new GameMechs();
    myPlayer = new Player(myGM, myFood);
    myPlayer -> getPlayerPos(tempPos);
    myFood -> generateFood(tempPos);

}

void GetInput(void)
{
    if(myGM -> getInput() == ' ')
        myGM -> setExitTrue();
}

void RunLogic(void)
{
    myPlayer -> updatePlayerDir();
    myPlayer -> movePlayer();
    if(Player -> checkFoodConsumption())
    {
        myPlayer -> increasePlayerLength();
        myFood -> generateFood(myPlayer -> getPlayerPos());

    }


}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    objPos tempPos;
    objPos tempFoodPos;
    myPlayer -> getPlayerPos(tempPos);  
    myFood -> getFoodPos(tempFoodPos); 

    MacUILib_printf("BoardSize: %d*%d, Player: <%d, %d> with %c\n", 
                    myGM -> getBoardSizeX(), myGM -> getBoardSizeY(), 
                    tempPos.x, tempPos.y, tempPos.symbol);
    MacUILib_printf("Food: <%d, %d> with %c\n",  
                    tempFoodPos.x, tempFoodPos.y, tempFoodPos.symbol);

    for(int i = 0; i < myGM -> getBoardSizeY(); i++)
    {
        MacUILib_printf("#");
        for(int j = 1; j < myGM -> getBoardSizeX() - 1; j++)
        {
            if(i == 0 || i == myGM -> getBoardSizeY() - 1)
            {
                MacUILib_printf("#");
            }
            else if(j == tempPos.x && i == tempPos.y)
            {
                MacUILib_printf("%c", tempPos.symbol);
            }
            else if(j == tempFoodPos.x && i == tempFoodPos.y)
            {
                MacUILib_printf("%c", tempFoodPos.symbol);
            }
            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("#");
        MacUILib_printf("\n");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    delete myFood;
    delete myPlayer;
    delete myGM;
  
    MacUILib_uninit();


}
