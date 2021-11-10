#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 
#include <math.h>
#include <time.h>

#define DEBUG_MODE 1

#define FLOOR_AMOUNT 10
#define FS_X 400 
#define FS_Y 30    //FartShit_Yaght
#define MAX_RS_X 30
#define MAX_RS_Y 20
#define MIN_RS_X 3
#define MIN_RS_Y 2
#define MAX_ROOMS 300
#define SCREEN_X 80
#define SCREEN_Y 20

int gameFloor[FLOOR_AMOUNT][FS_Y][FS_X];
int spawnX;
int spawnY;
int playerX;
int playerY;
int playerZ;

int randNum(int min, int max){  // I wonder what this does??
    srand(time(NULL));
    if(min < max){
        return((rand() % (max-min))+min);
    } else if(max < min){
        return((rand() % (min-max))+max);
    } else {
        return min;
    }
}

float strtLineDist(int Xa, int Ya, int Xb, int Yb){
    return(sqrt(pow(Ya-Yb,2)+pow(Xa-Xb,2)));
}

int genFloor(int roomAmount, int floorNumb){
    for(int i = 0; i < FS_Y; i++){
        for(int j = 0; j < FS_X; j++){
            gameFloor[floorNumb][i][j] = 1;
        }
    }
    int RoomOriginX[MAX_ROOMS] = {0};
    int RoomOriginY[MAX_ROOMS] = {0};
    int RoomCornerX[MAX_ROOMS] = {0};
    int RoomCornerY[MAX_ROOMS] = {0};
    bool RGFail = 1;    // Room Generation Fail
    int maxX;
    int maxY;
    for(int i = 0; i < roomAmount; i++){
        RGFail = 1;
        while(RGFail == 1){ // Prevents overlapping rooms
            RGFail = 0;
            RoomOriginX[i] = randNum(1, FS_X-2);
            RoomOriginY[i] = randNum(1, FS_Y-2);
            maxX = RoomOriginX[i]+MAX_RS_X;
            maxY = RoomOriginY[i]+MAX_RS_Y;
            if(maxX >= FS_X){
                maxX = FS_X-1;
            }
            if(maxY >= FS_Y){
                maxY = FS_Y-1;
            }
            RoomCornerX[i] = randNum(RoomOriginX[i]+MIN_RS_X,maxX);
            RoomCornerY[i] = randNum(RoomOriginY[i]+MIN_RS_Y,maxY);
            for(int j = 0; j < i; j++){ 
                //((RoomOriginX[i] >= RoomOriginX[j])&&(RoomOriginX[i] <= RoomCornerX[j])||(RoomOriginX[j] >= RoomOriginX[i])&&(RoomOriginX[j] <= RoomCornerX[i]))&&((RoomOriginY[i] >= RoomOriginY[j])&&(RoomOriginY[i] <= RoomCornerY[j])||(RoomOriginY[j] >= RoomOriginY[i])&&(RoomOriginY[j] <= RoomCornerY[i]))
                //
                if((
                    (RoomOriginX[i] >= RoomOriginX[j])&&(RoomOriginX[i] <= RoomCornerX[j]) // if oxJ <= oxI <= cxJ
                    &&                                                                     // and
                    (RoomOriginY[i] >= RoomOriginY[j])&&(RoomOriginY[i] <= RoomCornerY[j]) // if oyJ <= oyI <= cyJ
                   ) 
                   ||
                   (
                    (RoomOriginX[i] >= RoomOriginX[j])&&(RoomOriginX[i] <= RoomCornerX[j]) // if oxJ <= oxI <= cxJ
                    &&                                                                     // and
                    (RoomOriginY[j] >= RoomOriginY[i])&&(RoomOriginY[j] <= RoomCornerY[i]) // if oyI <= oyJ <= cyI
                   )
                   ||
                   (
                    (RoomOriginX[j] >= RoomOriginX[i])&&(RoomOriginX[j] <= RoomCornerX[i]) // if oxI <= oxJ <= cxI
                    &&                                                                     // and
                    (RoomOriginY[i] >= RoomOriginY[j])&&(RoomOriginY[i] <= RoomCornerY[j]) // if oyJ <= oyI <= cyJ
                   )
                   ||
                   (
                    (RoomOriginX[j] >= RoomOriginX[i])&&(RoomOriginX[j] <= RoomCornerX[i]) // if oxI <= oxJ <= cxI
                    &&                                                                     // and
                    (RoomOriginY[j] >= RoomOriginY[i])&&(RoomOriginY[j] <= RoomCornerY[i]) // if oyI <= oyJ <= cyI
                   )){
                    RGFail = 1;
                }
                /*
                // SENARIO 1:
                // TL J corner is between TL I & o on X axis, and between TL I & o on Y axis, and therefore, both squares are over lapping
                //  I###|####o
                //  #   |    #
                //  ----J############o
                //  #   #    #       #
                //  o########I       #
                //      #            #
                //      o############J
                //
                // SENARIO 2:
                // Can't be bothered to explain, but cause of lines and being inbetween and shit, both squares are overlapping
                //    J#####o
                //    |     #
                // I--+##o  #
                // #  #  #  #
                // #  o#####J
                // #     #
                // o#####I
                //
                // SENARIO 3:
                // TP J corner is between TL I & o on X axis, but nothing is between on the Y axis, so it isn't overlapping
                // I##|##o
                // #  |  #
                // o##|##I
                //    |
                //    J#####o
                //    #     #
                //    o#####J
                */
            }
        }
        if(DEBUG_MODE){
            printf("room stuff %d: %d %d %d %d\n",i,RoomOriginX[i],RoomOriginY[i],RoomCornerX[i],RoomCornerY[i]);
        }
        if (i > 0){ // Makes coridoors between rooms
            int closestRoomDist = 1000000;
            int closestRoom = 0;
            int currentDist = 0;
            for(int j = 0; j < i; j++){ // Find closest room
                currentDist = strtLineDist((RoomOriginX[i]+RoomCornerX[i])/2,(RoomOriginY[i]+RoomCornerY[i])/2,(RoomOriginX[j]+RoomCornerX[j])/2,(RoomOriginY[j]+RoomCornerY[j])/2);
                if(currentDist < closestRoomDist){
                    closestRoom = j;
                    closestRoomDist = currentDist;
                }
            }
            int goalX = (RoomOriginX[closestRoom]+RoomCornerX[closestRoom])/2;
            int goalY = (RoomOriginY[closestRoom]+RoomCornerY[closestRoom])/2;
            int diggerX = (RoomOriginX[i]+RoomCornerX[i])/2;
            int diggerY = (RoomOriginY[i]+RoomCornerY[i])/2;
            int diggerPlanX; // The co-ordinates of where the digger plans to go
            int diggerPlanY;
            bool diggerDir = 1; // 1 means X direction, 0 means y
            while((diggerX != goalX)&&(diggerY != goalY)){
                if(diggerDir && (diggerX != goalX)){
                    diggerPlanX = randNum(diggerX,goalX);
                    for(int a = diggerX; a < diggerPlanX; a++){
                        gameFloor[floorNumb][diggerY][a] = 2;
                    }
                    diggerX = diggerPlanX;
                } else if(!diggerDir && (diggerY != goalY)) {
                    diggerPlanY = randNum(diggerY,goalY);
                    for(int a = diggerY; a < diggerPlanY; a++){
                        gameFloor[floorNumb][diggerY][a] = 2;
                    }
                    diggerY = diggerPlanY;
                }
            }
            int secondClosestRoomDist = 1000000;
            int secondClosestRoom = 0;
            currentDist = 0;
            if(i > 1 && randNum(0,1) == 0){ // Makes a second coridoor originating from this room
                secondClosestRoomDist = 1000000;
                secondClosestRoom = 0;
                currentDist = 0;
                for(int j = 0; j < i; j++){ // Find second closest room
                    currentDist = strtLineDist((RoomOriginX[i]+RoomCornerX[i])/2,(RoomOriginY[i]+RoomCornerY[i])/2,(RoomOriginX[j]+RoomCornerX[j])/2,(RoomOriginY[j]+RoomCornerY[j])/2);
                    if(currentDist < secondClosestRoomDist && currentDist < closestRoomDist){
                        secondClosestRoom = j;
                        secondClosestRoomDist = currentDist;
                    }
                }

            }
            goalX = (RoomOriginX[secondClosestRoom]+RoomCornerX[secondClosestRoom])/2;
            goalY = (RoomOriginY[secondClosestRoom]+RoomCornerY[secondClosestRoom])/2;
            diggerX = (RoomOriginX[i]+RoomCornerX[i])/2;
            diggerY = (RoomOriginY[i]+RoomCornerY[i])/2;
            diggerPlanX; // The co-ordinates of where the digger plans to go
            diggerPlanY;
            diggerDir = 1; // 1 means X direction, 0 means y
            while((diggerX != goalX)&&(diggerY != goalY)){
                if(diggerDir && (diggerX != goalX)){
                    diggerPlanX = randNum(diggerX,goalX);
                    for(int a = diggerX; a < diggerPlanX; a++){
                        gameFloor[floorNumb][diggerY][a] = 2;
                    }
                    diggerX = diggerPlanX;
                } else if(!diggerDir && (diggerY != goalY)) {
                    diggerPlanY = randNum(diggerY,goalY);
                    for(int a = diggerY; a < diggerPlanY; a++){
                        gameFloor[floorNumb][diggerY][a] = 2;
                    }
                    diggerY = diggerPlanY;
                }
            }
        }
    }
    // Dig out rooms!
    for(int i = 0; i < roomAmount; i++){
        for(int y = RoomOriginY[i]; y <= RoomCornerY[i]; y++){
            for(int x = RoomOriginX[i]; x <= RoomCornerX[i]; x++){
                gameFloor[floorNumb][y][x] = 2;
            }
        }
    }
    spawnX = (RoomOriginX[0]+RoomCornerX[0])/2;
    spawnY = (RoomOriginY[0]+RoomCornerY[0])/2;
    if(DEBUG_MODE){
        printf("\n\n");
        for(int i = 0; i < roomAmount; i++){
            printf("Room %d:\n     Origin(%d,%d)\n     Corner(%d,%d)\n\n",i,RoomOriginX[i],RoomOriginY[i],RoomCornerX[i],RoomCornerY[i]);
        }
        for(int y = 0; y < FS_Y; y++){
            for(int x = 0; x < FS_X; x++){
                printf("%d",gameFloor[floorNumb][y][x]);
            }
            printf("\n");
        }
    }
    return 0;
}

int printScreen(int screenLength, int screenHeight){
    char screenToPrint[(SCREEN_X*SCREEN_Y)+SCREEN_Y];
    int screenOriginX = playerX - screenLength/2;
    int screenOriginY = playerY - screenHeight/2;
    if(screenOriginX < 0){
        screenOriginX = 0;
    } else if(screenOriginX+screenLength > FS_X){
        screenOriginX = FS_X - screenLength;
    }
    if(screenOriginY < 0){
        screenOriginY = 0;
    } else if(screenOriginY+screenHeight > FS_Y){
        screenOriginY = FS_Y - screenHeight;
    }
    int i = 0;
    if(DEBUG_MODE){
        printf("printScreen test: %d\n",screenOriginY);
        printf("printScreen test: %d\n",screenOriginY+screenHeight);
        getchar();
    }
    for(int y = screenOriginY; y < screenOriginY+screenHeight; y++){
        for(int x = screenOriginX; x < screenOriginX+screenLength; x++){
            if(gameFloor[playerZ][y][x] == 0){
                screenToPrint[i] = ' ';
            } else if(gameFloor[playerZ][y][x] == 1){
                screenToPrint[i] = '#';
            } else if(gameFloor[playerZ][y][x] == 2){
                screenToPrint[i] = '.';
            }
            i++;
        }
        screenToPrint[i] = '\n';
        i++;
    }
    screenToPrint[i] = '\0';
    printf("%s\n",screenToPrint);
    return 0;
}

int gameLoop(){
    char playerInput[];
    scanf("%s",&playerInput);
    if (playerInput == "up" && playerY-1 > 0){
        playerY = playerY - 1;
    } else if (playerInput == "down" && playerY+1 <= FS_Y){
        playerY = playerY + 1;
    } else if (playerInput == "left" && playerX-1 > 0){
        playerX = playerX - 1;
    } else if (playerInput == "right" && playerX+1 <= FS_X){
        playerX = playerX + 1;
    }
    printScreen(SCREEN_X,SCREEN_Y);
    getchar();
}

int main(){
    spawnX = 0;
    spawnY = 0;
    playerZ = 0;
    
    int genFloorTest = genFloor(8,0);
    if(DEBUG_MODE){
        printf("genFloor: %d\n",genFloorTest);
    }
    playerX = spawnX;
    playerY = spawnY;

    int printScreenTest = printScreen(SCREEN_X,SCREEN_Y);
    if(DEBUG_MODE){
        printf("printScreen: %d\n",printScreenTest);
    }
    gameLoop();
}
