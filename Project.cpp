#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"



using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;



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

    myGM = new GameMechs();
    myPlayer = new Player(myGM);

}

void GetInput(void)
{
    int input = myGM -> getInput();
}

void RunLogic(void)
{
    if(myGM -> getInput() == ' ')
        myGM -> setExitTrue();
    myPlayer -> updatePlayerDir();
    myPlayer -> movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen(); 

    objPos tempPos;
    myPlayer -> getPlayerPos(tempPos);   

    MacUILib_printf("BoardSize: %d*%d, Player: <%d, %d> with %c\n", 
                    myGM -> getBoardSizeX(), myGM -> getBoardSizeY(), 
                    tempPos.x, tempPos.y, tempPos.symbol);

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

    delete myPlayer;
    delete myGM;
  
    MacUILib_uninit();


}
