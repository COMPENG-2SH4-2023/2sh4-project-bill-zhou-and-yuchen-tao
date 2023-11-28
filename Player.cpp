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
            playerPosList -> insertHead(playerPos);  
            playerPosList -> removeTail();  
            break;
        case DOWN:
            playerPos.y ++;
            if(playerPos.y > mainGameMechsRef -> getBoardSizeY() - 2)
                playerPos.y = 1;
            playerPosList -> insertHead(playerPos);  
            playerPosList -> removeTail();  
            break;
        case LEFT:
            playerPos.x --;
            if(playerPos.x < 1)
                playerPos.x = mainGameMechsRef -> getBoardSizeX() - 2;
            playerPosList -> insertHead(playerPos);  
            playerPosList -> removeTail(); 
            break;
        case RIGHT:
            playerPos.x ++;
            if(playerPos.x > mainGameMechsRef -> getBoardSizeX() - 2)
                playerPos.x = 1;
            playerPosList -> insertHead(playerPos);  
            playerPosList -> removeTail(); 
            break;
        case STOP:
            playerPos.x = mainGameMechsRef -> getBoardSizeX() / 2;
            playerPos.y = mainGameMechsRef -> getBoardSizeY() / 2;
            playerPosList -> insertHead(playerPos);  
            playerPosList -> removeTail();
            break;
        default:
            break;
    }
}

int Player::checkFoodConsumption()
{
    int set;
    objPos playerPos;
    objPos foodPos;
    playerPosList -> getHeadElement(playerPos);
    objPosArrayList* foodBucket = food -> getFoodPos();

    for(int i = 0; i < foodBucket -> getSize(); i++)
    {
        foodBucket -> getElement(foodPos, i);
        if(playerPos.isPosEqual(&foodPos) && foodPos.symbol == '0')
        {
            set = 1;
            break;
        }
        else if(playerPos.isPosEqual(&foodPos) && foodPos.symbol == '1')
        {
            set = 2;
            break;
        }
        else
        {
            set = 0;
        }
    }

    return set;
}

void Player::increasePlayerLength()
{
    objPos playerPos;
    playerPosList->getHeadElement(playerPos);
    playerPosList->insertHead(playerPos);
}

bool Player::checkSelfCollision()
{   
    objPos head;
    objPos body;
    for(int i = 2 ; i < playerPosList -> getSize() ; i++)
    {
        playerPosList -> getHeadElement(head);
        playerPosList -> getElement(body , i);
        if(body.x == head.x && body.y == head.y)
        {
            return true;
        }
    }
    return false;
}