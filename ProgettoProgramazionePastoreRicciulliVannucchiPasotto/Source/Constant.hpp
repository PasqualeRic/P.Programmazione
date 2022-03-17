#pragma once
#include <string>
using namespace std;

const int MAP_HEIGHT = 35; // altezza della mappa
const int MAP_WIDTH = 60; // larghezza della mappa 
const int MAP_OFFSET_Y = 0; // distanza tra console e mappa in altezza
const int MAP_OFFSET_X = 20; // distanza tra console e mappa in larghezza

const int ENLARGE_FACTOR = 3; // dimensioni blocchi oggetti
const int LEVEL_WIDTH = MAP_WIDTH / ENLARGE_FACTOR;
const int LEVEL_LENGHT = 500;

const int START_GAME_SPEED = 19; //è in frame per secondo
const int SPEED_DIFFERENCE_BETWEEN_LEVEL = 4; //è in frame per secondo


const int POINT_PER_LEVEL = 800;  // punti per passare ogni livello
const int POINT_TO_GO_DOWN_LEVEL = POINT_PER_LEVEL / 8; 

const int CONSOLE_SIZE_X = 1030;  // dimensione console
const int CONSOLE_SIZE_Y = 800;


#define AirPair 0
#define GasPair 1
#define ObstaclePair 2
#define NailsPair 3
#define PitPair 4
#define WallPair 5
#define StandarWritePair 6
#define AllBlackPair 7

#define SelectedMenuOptionPair 99
 
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTAQUA 11
#define LIGHTRED 12
#define LIGHTPURPLE 13
#define LIGHTYELLOW 14
#define BRIGHTWHITE 15
