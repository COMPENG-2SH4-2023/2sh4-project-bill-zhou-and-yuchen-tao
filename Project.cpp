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
    if(myPlayer -> checkFoodConsumption() == 1)
    {
        myFood -> generateFood(myPlayer -> getPlayerPos());
        myPlayer -> increasePlayerLength();
        myGM -> incrementScore();
    }
    else if(myPlayer -> checkFoodConsumption() == 2)
    {
        myFood -> generateFood(myPlayer -> getPlayerPos());
        for(int i = 0; i < 10; i++)
            myGM -> incrementScore();
    }
    
    if(myPlayer -> checkSelfCollision())
    {
        myGM -> setLoseTrue();
        myGM -> setExitTrue();
    }
    

}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    objPosArrayList* tempPosList = myPlayer->getPlayerPos();
    objPosArrayList* tempFoodList = myFood -> getFoodPos(); 
    objPos tempPos;
    objPos tempFoodPos;

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
            for(int k = 0; k < tempFoodList -> getSize() ; k++)
            {
                tempFoodList -> getElement(tempFoodPos,k);
                if(j == tempFoodPos.x && i == tempFoodPos.y)
                {
                    break;
                }
            }
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
    MacUILib_printf("\tScore:%d\n",myGM -> getScore());

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen(); 
    
    if(myGM -> getLoseFlagStatus())
    {
        MacUILib_printf("Final Score:%d\n",myGM -> getScore());
        MacUILib_printf("You Lose The Game! Try It Again!\n");
        MacUILib_uninit();
    }
    else
    {
        MacUILib_uninit();
    }
       

    delete myFood;
    delete myPlayer;
    delete myGM;


}
