#include "Player.h"



Player::Player(GameMechs* thisGMRef, Food* thisFood)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    food = thisFood;
    playerPosList = new objPosArrayList();


    objPos playerPos;
    playerPos.setObjPos(mainGameMechsRef -> getBoardSizeX() / 2, mainGameMechsRef -> getBoardSizeY() / 2, '*');

    // more actions to be included

    playerPosList -> insertHead(playerPos);

}


Player::~Player()
{
    delete playerPosList;
    // delete any heap members here
}

objPosArrayList* Player::getPlayerPos()
{
    // return the reference to the playerPos arrray list

    return playerPosList;
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
    objPos playerPos;
    playerPosList -> getHeadElement(playerPos);
    

    switch(myDir)
    {
        case UP:
            playerPos.y --;            
            if(playerPos.y < 1)
                playerPos.y = mainGameMechsRef -> getBoardSizeY() - 2;
            playerPosList -> removeHead();
            playerPosList -> insertHead(playerPos);  
            break;
        case DOWN:
            playerPos.y ++;
            if(playerPos.y > mainGameMechsRef -> getBoardSizeY() - 2)
                playerPos.y = 1;
            playerPosList -> removeHead();
            playerPosList -> insertHead(playerPos);  
            break;
        case LEFT:
            playerPos.x --;
            if(playerPos.x < 1)
                playerPos.x = mainGameMechsRef -> getBoardSizeX() - 2;
            playerPosList -> removeHead();
            playerPosList -> insertHead(playerPos);  
            break;
        case RIGHT:
            playerPos.x ++;
            if(playerPos.x > mainGameMechsRef -> getBoardSizeX() - 2)
                playerPos.x = 1;
            playerPosList -> removeHead();
            playerPosList -> insertHead(playerPos);  
            break;
        case STOP:
            playerPos.x = mainGameMechsRef -> getBoardSizeX() / 2;
            playerPos.y = mainGameMechsRef -> getBoardSizeY() / 2;
            playerPosList -> removeHead();
            playerPosList -> insertHead(playerPos);  
            break;
        default:
            break;
    }
}

bool Player::checkFoodConsumption()
{
    bool set;
    objPos playerPos;
    playerPosList -> getHeadElement(playerPos);
    objPos foodPos;
    food -> getFoodPos(foodPos);


    if(playerPos.x == foodPos.x && playerPos.y == foodPos.y)
    {
        set = true;
    }
    else
    {
        set = false;
    }

    return set;
}

void Player::increasePlayerLength()
{
    objPos playerPos;
    playerPosList->getHeadElement(playerPos);
    playerPosList->insertHead(playerPos);
}
