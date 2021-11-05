#include <stblib.h>
#include <stdio.h>
#include <stdbool.h> 
#include <math.h>

#define FLOOR_AMOUNT 10
#define FS_X 300 
#define FS_Y 200    //FartShit_Yaght
#define MAX_RS_X 30
#define MAX_RS_Y 20
#define MIN_RS_X 3
#define MIN_RS_Y 2

int randNum(min, max){  // I wonder what this does??
    return((rand() % (max-min))+min);
}

float strtLineDist(int Xa, int Ya, int Xb, int Yb){
    return(sqrt(pow(Ya-Yb,2)+pow(Xa-Xb,2)));
}

int genFloor(int roomAmount, int floorNumb){
    for(int i = 0; i < FS_Y; i++){
        for(int j = 0; j < FS_X; j++){
            floor[floorNumb][i][j] = 1;
        }
    }
    int RoomOriginX[];
    int RoomOriginY[];
    int RoomCornerX[];
    int RoomCornerY[];
    bool RGFail = 0;    // Room Generation Fail
    for(int i = 0; i < roomAmount; i++){
        while(RGFail == 1){ // Prevents overlapping rooms
            RoomOriginX[i] = 0;
            RoomOriginY[i] = 0;
            RoomCornerX[i] = 0;
            RoomCornerY[i] = 0;
            RGFail = 0;
            RoomOriginX[i] = randNum(1, FS_X-2);
            RoomOriginY[i] = randNum(1, FS_Y-2);
            RoomCornerX[i] = randNum(RoomOriginX[i]+MIN_RS_X,RoomOriginX[i]+MAX_RS_X);
            RoomCornerY[i] = randNum(RoomOriginY[i]+MIN_RS_Y,RoomOriginY[i]+MAX_RS_Y);
            for(int j = 0; j < i; j++){ 
                if(((RoomOriginX[i] >= RoomOriginX[j])&&(RoomOriginX[i] <= RoomCornerX[j])||(RoomOriginX[j] >= RoomOriginX[i])&&(RoomOriginX[j] <= RoomCornerX[i]))&&((RoomOriginY[i] >= RoomOriginY[j])&&(RoomOriginY[i] <= RoomCornerY[j])||(RoomOriginY[j] >= RoomOriginY[i])&&(RoomOriginY[j] <= RoomCornerY[i]))){
                    FGFail = 1:
                }
                //
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
                //
            }
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
            int goalY = (RoomOriginY[closestRoom]+RoomCornerY[closestRoomi])/2;
            int diggerX = (RoomOriginX[i]+RoomCornerX[i])/2;
            int diggerY = (RoomOriginY[i]+RoomCornerY[i])/2;
            int diggerPlanX; // The co-ordinates of where the digger plans to go
            int diggerPlanY;
            bool diggerDir = 1; // 1 means X direction, 0 means y
            while((diggerX != goalX)&&(diggerY != goalY)){
                if(diggerDir && (diggerX != goalX)){
                    diggerPlanX = randNum(diggerX,goalX);
                    for(int a = diggerX; a < diggerPlanX; a++){
                        floor[floorNumb][diggerY][a] = 2;
                    }
                    diggerX = diggerPlanX;
                } else if(!diggerDir && (diggerY != goalY)) {
                    diggerPlanY = randNum(diggerY,goalY);
                    for(int a = diggerY; a < diggerPlanY; a++){
                        floor[floorNumb][diggerY][a] = 2;
                    }
                    diggerY = diggerPlanY;
                }
            }
            if(i > 1 && randNum(0,1) == 0){ // Makes a second coridoor originating from this room
                int secondClosestRoomDist = 1000000;
                int secondclosestRoom = 0;
                int currentDist = 0;
                for(int j = 0; j < i; j++){ // Find second closest room
                    currentDist = strtLineDist((RoomOriginX[i]+RoomCornerX[i])/2,(RoomOriginY[i]+RoomCornerY[i])/2,(RoomOriginX[j]+RoomCornerX[j])/2,(RoomOriginY[j]+RoomCornerY[j])/2);
                    if(currentDist < secondclosestRoomDist && currentDist < closestRoomDist){
                        secondclosestRoom = j;
                        secondclosestRoomDist = currentDist;
                    }
                }

            }
            goalX = (RoomOriginX[secondClosestRoom]+RoomCornerX[secondClosestRoom])/2;
            goalY = (RoomOriginY[secondClosestRoom]+RoomCornerY[secondClosestRoomi])/2;
            diggerX = (RoomOriginX[i]+RoomCornerX[i])/2;
            diggerY = (RoomOriginY[i]+RoomCornerY[i])/2;
            diggerPlanX; // The co-ordinates of where the digger plans to go
            diggerPlanY;
            bool diggerDir = 1; // 1 means X direction, 0 means y
            while((diggerX != goalX)&&(diggerY != goalY)){
                if(diggerDir && (diggerX != goalX)){
                    diggerPlanX = randNum(diggerX,goalX);
                    for(int a = diggerX; a < diggerPlanX; a++){
                        floor[floorNumb][diggerY][a] = 2;
                    }
                    diggerX = diggerPlanX;
                } else if(!diggerDir && (diggerY != goalY)) {
                    diggerPlanY = randNum(diggerY,goalY);
                    for(int a = diggerY; a < diggerPlanY; a++){
                        floor[floorNumb][diggerY][a] = 2;
                    }
                    diggerY = diggerPlanY;
                }
            }
        }
        // TODO:
        // Dig out rooms!
        for(int i = 0; i < roomAmount; i++){
            for(int y = roomOriginY[i]; y <= roomCornerY[i]; y++){
                for(int x = roomOriginX[i]; x <= roomCornerX[i]; x++){
                    floor[floorNumb][y][x] = 2;
                }
            }
        }
    }
}

int main(){
    int spawnX;
    int spawnY;
    int floor[FLOOR_AMOUNT][FS_Y][FS_X];
    genFloor(5,0);
}