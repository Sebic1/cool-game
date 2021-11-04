#include <stblib.h>
#include <stdio.h>
#include <stdbool.h> 

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
        while(RGFail == 1){
            RoomOriginX[i] = 0;
            RoomOriginY[i] = 0;
            RoomCornerX[i] = 0;
            RoomCornerY[i] = 0;
            RGFail = 0;
            RoomOriginX[i] = randNumb(1, FS_X-2);
            RoomOriginY[i] = randNumb(1, FS_Y-2);
            RoomCornerX[i] = randNumb(RoomOriginX[i]+MIN_RS_X,RoomOriginX[i]+MAX_RS_X);
            RoomCornerY[i] = randNumb(RoomOriginY[i]+MIN_RS_Y,RoomOriginY[i]+MAX_RS_Y);
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
    }
}

int main(){
    int floor[FLOOR_AMOUNT][FS_Y][FS_X];
    genFloor(5,0);
}