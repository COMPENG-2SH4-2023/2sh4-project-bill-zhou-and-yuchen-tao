#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included

    playerPos.setObjPos(mainGameMechsRef -> getBoardSizeX() / 2, mainGameMechsRef -> getBoardSizeY() / 2, '*');
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list

    returnPos.setObjPos(playerPos);
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic    
    char input = mainGameMechsRef -> getInput();

    switch(input)
    {
        case 'W':
        case 'w':
            if(myDir != DOWN && myDir != UP)
                myDir = UP;
            break;
        case 'A':
        case 'a':
            if(myDir != RIGHT && myDir != LEFT)
                myDir = LEFT;
            break;
        case 'S':
        case 's':
            if(myDir != DOWN && myDir != UP)
                myDir = DOWN;
            break;
        case 'D':
        case 'd':
            if(myDir != RIGHT && myDir != LEFT)
                myDir = RIGHT;
            break;
        default:
            break;
    } 

    mainGameMechsRef -> clearInput();   
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    

    switch(myDir)
    {
        case UP:
            playerPos.y --;            
            if(playerPos.y < 1)
                playerPos.y = mainGameMechsRef -> getBoardSizeY() - 2;
            break;
        case DOWN:
            playerPos.y ++;
            if(playerPos.y > mainGameMechsRef -> getBoardSizeY() - 2)
                playerPos.y = 1;
            break;
        case LEFT:
            playerPos.x --;
            if(playerPos.x < 1)
                playerPos.x = mainGameMechsRef -> getBoardSizeX() - 2;
            break;
        case RIGHT:
            playerPos.x ++;
            if(playerPos.x > mainGameMechsRef -> getBoardSizeX() - 2)
                playerPos.x = 1;
            break;
        case STOP:
            playerPos.x = mainGameMechsRef -> getBoardSizeX() / 2;
            playerPos.y = mainGameMechsRef -> getBoardSizeY() / 2;
            break;
        default:
            break;
    }
}

