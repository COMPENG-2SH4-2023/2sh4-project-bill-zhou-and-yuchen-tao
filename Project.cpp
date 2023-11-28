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
    objPosArrayList* tempPlayer = myPlayer->getPlayerPos();
    myFood -> generateFood(tempPlayer);

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
    if(myPlayer -> checkFoodConsumption())
    {
        myPlayer -> increasePlayerLength();
        myGM -> incrementScore();
        myFood -> generateFood(myPlayer -> getPlayerPos());
    }
    if(myPlayer -> checkSelfCollision())
    {
        myGM -> setLoseTrue();
    }
    if(myGM -> getLoseFlagStatus() == true)
    {
        MacUILib_clearScreen();
        MacUILib_printf("You Lose The Game! Try It Again!\n");
        MacUILib_printf("End of the Game, Your Score is: %d\n",myGM -> getScore());
        MacUILib_Delay(10000000);
        myGM -> setExitTrue();
    }

}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    objPosArrayList* tempPosList = myPlayer->getPlayerPos();
    objPos tempPos;
    objPos tempFoodPos;  
    myFood -> getFoodPos(tempFoodPos); 

    for(int i = 0; i < myGM -> getBoardSizeY(); i++)
    {
        MacUILib_printf("#");
        for(int j = 1; j < myGM -> getBoardSizeX() - 1; j++)
        {
            
            for(int k = 0; k < tempPosList -> getSize() ; k++)
            {
                tempPosList -> getElement(tempPos,k);
                if(j == tempPos.x && i == tempPos.y)
                {
                    break;
                }
            }
            //tempPosList -> getElement(tempPos,0);
            if(i == 0 || i == myGM -> getBoardSizeY() - 1)
            {
                MacUILib_printf("#");
            }
            //Food
            else if(j == tempFoodPos.x && i == tempFoodPos.y)
            {
                MacUILib_printf("%c", tempFoodPos.symbol);
            }
            //Player
            else if(j == tempPos.x && i == tempPos.y)
            {
                MacUILib_printf("%c", tempPos.symbol);
            }
            else
            {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("#");
        MacUILib_printf("\n");
    }
    MacUILib_printf("\tYour Score:%d\n",myGM -> getScore());

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
