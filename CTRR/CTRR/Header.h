#pragma once
#include <SDL.h>
#include <iostream>
#include<vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string>
using namespace std;
extern int counter;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
extern SDL_Color textColor;
extern SDL_Color redColor;
extern SDL_Color black;
extern SDL_Rect Startbutton;
extern SDL_Rect Exitbutton;
extern SDL_Rect Option[6];
extern SDL_Rect Back_button;
extern SDL_Rect Button;
extern SDL_Rect HintButton;
extern SDL_Rect CounterTable;
enum GameState {
    MAIN_MENU,
    LEVEL_MENU,
    In_Game,
    
};

struct Node {
    int x, y;
    int number;
};
extern Node map1[8];
extern Node map2[17];
extern Node map3[20];
// Định nghĩa các thuộc tính của nhân vật của bạn
struct Character {
    int x, y;
};
extern std::vector<int> temp;
extern std::vector<int> saveprogress;


