#pragma once
#include "Header.h"

bool isMouseInsideCircle(int mouseX, int mouseY, int circleX, int circleY, int radius);
void drawCircle(SDL_Renderer* renderer, int x, int y, int radius);
// Hàm vẽ văn bản
void renderText(SDL_Renderer* renderer, int x, int y, const std::string& text, SDL_Color color, TTF_Font* font);
void drawFilledCircle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color);
// Hàm vẽ một hình tròn đánh số đỉnh
void drawNode(SDL_Renderer* renderer, Node a, SDL_Color nodeColor, TTF_Font* font, int radius);
// Hàm vẽ đồ thị
void drawGraph(SDL_Renderer* renderer, int** matrix, TTF_Font* font, int numNodes, int radius,Node a[]);
// Hàm để di chuyển nhân vật đến vị trí cụ thể
int initSDL();
// Hàm đọc dữ liệu từ tệp và trả về ma trận trọng số
int** readInputFromFile(const std::string& fileName, int& numNodes);
SDL_Texture* LoadImg(SDL_Renderer* renderer, const char* filename);
void MainMenu(SDL_Renderer* renderer, TTF_Font* font,TTF_Font *Menufont, SDL_Texture* BackgroundTexture);
void LevelMenu(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* BackgroundTexture);
void rendermap(SDL_Renderer* renderer, TTF_Font* font, int numNodes, int radius, int** weightMatrix, SDL_Texture* BackgroundTexture, SDL_Texture* Characterimg, SDL_Rect imageRect, Character& character, Node *a,int& mouseX, int& mouseY, Node &current_coordinate);
void Handle_map(SDL_Renderer* renderer, TTF_Font* font, int numNodes, int radius, int** weightMatrix, SDL_Texture* BackgroundTexture, SDL_Texture* Characterimg, SDL_Rect imageRect, Character& character, Node *a, int& mouseX, int& mouseY, Node &current_coordinate,int &z, bool &ready_move);
void printPath(vector<int>& previous, int start, int end);
void Dijkstra(int** weightMatrix, int numNodes, int startNode, vector<Node>& a,vector<int>&previous);
void create(vector<int>& previous, int start, int end);
void moveCharacterToNode(SDL_Renderer* renderer, int** weightMatrix,
	TTF_Font* font,SDL_Texture*Backgroundtexture, SDL_Texture* imageTexture, int numNodes, int radius,
	Character& character, Node destination, int speed, int characterWidth, 
	int characterHeight,Node *a);
std::string intToString(int value);