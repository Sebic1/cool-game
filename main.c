#include <stblib.h>
#include <stdio.h>
#include <stdbool.h> 

#define FLOOR_AMOUNT 10
#define FS_X 300 
#define FS_Y 200
#define MAX_RS_X 30
#define MAX_RS_Y 20
#define MIN_RS_X 3
#define MIN_RS_Y 2

int randNum(min, max){
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
    bool RGSuccess = 1;
    for(int i = 0; i < roomAmount; i++){
        while(RGSuccess == 0){
            RoomOriginX[i] = 0;
            RoomOriginY[i] = 0;
            RoomCornerX[i] = 0;
            RoomCornerY[i] = 0;
            RGSuccess = 1;
            RoomOriginX[i] = randNumb(1, FS_X-2);
            RoomOriginX[i] = randNumb(1, FS_Y-2);
        }
    }
}

int main(){
    int floor[FLOOR_AMOUNT][FS_Y][FS_X];
    genFloor(5,0);
}