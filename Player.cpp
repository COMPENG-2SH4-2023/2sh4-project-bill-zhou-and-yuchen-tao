#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included

    playerPos.setObjPos(5, 5, '@');
}


Player::~Player()
{
    // delete any heap members here
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list

    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic    

    switch(input)
    {
        case 'W':
        case 'w':
            if(state != DOWN && state != UP)
                myDir = UP;
            break;
        case 'A':
        case 'a':
            if(state != RIGHT && state != LEFT)
                myDir = LEFT;
            break;
        case 'S':
        case 's':
            if(state != DOWN && state != UP)
                myDir = DOWN;
            break;
        case 'D':
        case 'd':
            if(state != RIGHT && state != LEFT)
                myDir = RIGHT;
            break;
        default:
            break;
    }    
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
}

