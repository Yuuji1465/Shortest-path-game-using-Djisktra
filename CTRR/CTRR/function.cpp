#pragma once
#include "Prototype.h"
#include "Header.h"
int counter = 0;
bool isMouseInsideCircle(int mouseX, int mouseY, int circleX, int circleY, int radius) {
    int dx = mouseX - circleX;
    int dy = mouseY - circleY;
    return dx * dx + dy * dy <= radius * radius;
}
void drawCircle(SDL_Renderer* renderer, int x, int y, int radius) {
    for (int i = 0; i < 360; ++i) {
        double angle = i * 3.141592653589793 / 180; // Chuyển đổi độ sang radian
        int cx = x + radius * cos(angle);
        int cy = y + radius * sin(angle);
        SDL_RenderDrawPoint(renderer, cx, cy);
    }
}
// Hàm vẽ văn bản
void renderText(SDL_Renderer* renderer, int x, int y, const std::string& text, SDL_Color color, TTF_Font* font) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect textRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
void drawFilledCircle(SDL_Renderer* renderer, int x, int y, int radius, SDL_Color color) {
    // Lưu trạng thái màu hiện tại
    Uint8 originalR, originalG, originalB, originalA;
    SDL_GetRenderDrawColor(renderer, &originalR, &originalG, &originalB, &originalA);
    originalR = color.r;
    originalG = color.g;
    originalB = color.b;
    originalA = color.a;
    // Đặt màu fill mới
    SDL_SetRenderDrawColor(renderer, originalR, originalG, originalB, originalA);

    for (int dy = -radius; dy <= radius; dy++) {
        for (int dx = -radius; dx <= radius; dx++) {
            if (dx * dx + dy * dy <= radius * radius) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }


}






// Hàm vẽ một hình tròn đánh số đỉnh
void drawNode(SDL_Renderer* renderer, Node a, SDL_Color nodeColor, TTF_Font* font, int radius) {
    // Vẽ hình tròn
    SDL_SetRenderDrawColor(renderer, nodeColor.r, nodeColor.g, nodeColor.b, nodeColor.a);
    drawCircle(renderer, a.x, a.y, radius);
    drawFilledCircle(renderer, a.x, a.y, radius, nodeColor);
    SDL_SetRenderDrawColor(renderer, textColor.r, textColor.g, textColor.b, textColor.a);

    // Hiển thị số thứ tự bên trong hình tròn

    std::string nodeText = std::to_string(a.number);
    int textWidth, textHeight;
    TTF_SizeText(font, nodeText.c_str(), &textWidth, &textHeight);
    int textX = a.x - textWidth / 2;
    int textY = a.y - textHeight / 2;

    // Vẽ văn bản
    renderText(renderer, textX, textY, nodeText, textColor, font);
}


// Hàm vẽ đồ thị
void drawGraph(SDL_Renderer* renderer, int** matrix, TTF_Font* font, int numNodes, int radius,Node a[]) {


    for (int i = 0; i < numNodes; i++)
    {
        drawNode(renderer, a[i], redColor, font, radius);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);



    for (int i = 0; i < numNodes; i++)
    {
        for (int j = 0; j < numNodes; j++)
        {
            if (matrix[i][j] != 100 && matrix[i][j] != 0 && i < j)
            {
                SDL_RenderDrawLine(renderer, a[i].x, a[i].y, a[j].x, a[j].y);

                int textX = (a[i].x + a[j].x) / 2;
                int textY = (a[i].y + a[j].y) / 2;
                std::string weightText = std::to_string(matrix[i][j]);
                SDL_Color textColor = { 255, 255, 255, 255 };
                renderText(renderer, textX, textY, weightText, textColor, font);
            }
        }
    }

    SDL_RenderPresent(renderer);

}
// Hàm để di chuyển nhân vật đến vị trí cụ thể
void moveCharacterToPosition(Character& character, int targetX, int targetY, int speed) {
    // Tính khoảng cách giữa vị trí hiện tại của nhân vật và vị trí đích
    int deltaX = targetX - character.x - 10; // Độ lệch theo trục X, giả sử nhân vật có kích thước 30x30 và nằm ở tâm
    int deltaY = targetY - character.y - 10; // Độ lệch theo trục Y, giả sử nhân vật có kích thước 30x30 và nằm ở tâm
    double distance = std::sqrt(deltaX * deltaX + deltaY * deltaY); // Tính khoảng cách Euclid giữa hai điểm

    // Kiểm tra xem nhân vật đã đến vị trí đích chưa
    if (distance <= speed) {
        // Nếu khoảng cách nhỏ hơn hoặc bằng tốc độ, nhân vật đã đến vị trí đích
        character.x = targetX - 15;
        character.y = targetY - 15;
    }
    else {
        // Nếu khoảng cách lớn hơn tốc độ, tính đơn vị hướng (vector đơn vị chỉ có độ lệch theo trục X và Y)
        double unitX = static_cast<double>(deltaX) / distance;
        double unitY = static_cast<double>(deltaY) / distance;

        // Di chuyển nhân vật theo hướng đơn vị với tốc độ đã cho
        character.x += static_cast<int>(unitX * speed);
        character.y += static_cast<int>(unitY * speed);
    }
}
int initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() < 0) {
        std::cerr << "SDL_ttf initialization failed: " << TTF_GetError() << std::endl;
        return 1;
    }
    // Khởi tạo thư viện SDL_Image
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
        std::cerr << "SDL_Image initialization failed: " << IMG_GetError() << std::endl;
        return 1;
    }

    return 0;
}

void rendermap(SDL_Renderer* renderer, TTF_Font* font, int numNodes, int radius,int **weightMatrix, SDL_Texture* BackgroundTexture, SDL_Texture* Characterimg, SDL_Rect imageRect,Character &character,Node *a, int& mouseX, int& mouseY, Node &current_coordinate)
{

    SDL_RenderCopy(renderer, BackgroundTexture, NULL, NULL);
    drawGraph(renderer, weightMatrix, font, numNodes, radius,a);
    SDL_Surface* BackSurface = IMG_Load("Back_button.png");
    if (BackSurface == nullptr) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return ;
    }
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, BackSurface);
    SDL_FreeSurface(BackSurface); // Giải phóng bộ nhớ sau khi tạo texture
    SDL_RenderCopy(renderer, imageTexture, NULL, &Back_button);

    // Load hình ảnh
    
    SDL_RenderCopy(renderer, Characterimg, NULL, &imageRect);
    SDL_RenderPresent(renderer);
}
// Hàm đọc dữ liệu từ tệp và trả về ma trận trọng số
int** readInputFromFile(const std::string& fileName, int& numNodes) {
    std::ifstream inputFile(fileName);
    int** weightMatrix;

    if (!inputFile.is_open()) {
        std::cerr << "Không thể mở tệp " << fileName << std::endl;
        return nullptr;
    }

    std::string line;

    // Bỏ qua dòng đầu tiên (0: đồ thị vô hướng, 1: đồ thị có hướng)
    std::getline(inputFile, line);

    if (std::getline(inputFile, line)) {
        std::istringstream headerStream(line);
        headerStream >> numNodes;
    }

    // Tạo ma trận trọng số
    weightMatrix = new int* [numNodes];
    for (int i = 0; i < numNodes; ++i) {
        weightMatrix[i] = new int[numNodes];
    }

    // Đọc dữ liệu từ tệp
    for (int i = 0; i < numNodes; ++i) {
        std::getline(inputFile, line);
        std::istringstream rowStream(line);
        for (int j = 0; j < numNodes; ++j) {
            rowStream >> weightMatrix[i][j];
        }
    }

    inputFile.close();
    return weightMatrix;
}
SDL_Texture* LoadImg(SDL_Renderer* renderer, const char* filename)
{
    SDL_Surface* imageSurface = IMG_Load(filename);
    if (imageSurface == nullptr) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return NULL;
    }

    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface); // Giải phóng bộ nhớ sau khi tạo texture
    return imageTexture;
}
void MainMenu(SDL_Renderer* renderer, TTF_Font* font,TTF_Font *Menufont, SDL_Texture* BackgroundTexture)
{
    SDL_RenderCopy(renderer, BackgroundTexture, NULL, NULL);
    renderText(renderer, 100, 100, "SHORTEST PATH GAME", redColor, Menufont);
    
    SDL_SetRenderDrawColor(renderer, 76, 175, 80, 1);
    SDL_RenderFillRect(renderer, &Startbutton);
    renderText(renderer, 350, 423, "Start Game", black, font);

    SDL_SetRenderDrawColor(renderer, 76, 175, 80, 1);
    SDL_RenderFillRect(renderer, &Exitbutton);
    renderText(renderer, 375, 523, "Exit", black, font);
    SDL_RenderPresent(renderer);
}
void LevelMenu(SDL_Renderer* renderer, TTF_Font* font, SDL_Texture* BackgroundTexture)
{
    SDL_RenderCopy(renderer, BackgroundTexture, NULL, NULL);
    SDL_SetRenderDrawColor(renderer, 76, 175, 80, 1);
    SDL_RenderFillRect(renderer, &Option[0]);
    renderText(renderer, Option[0].x + 120, Option[0].y + 15  ,"Level 1", black, font);

    SDL_SetRenderDrawColor(renderer, 76, 175, 80, 1);
    SDL_RenderFillRect(renderer, &Option[1]);
    renderText(renderer, Option[1].x + 120, Option[1].y + 15  ,"Level 2", black, font);

    SDL_SetRenderDrawColor(renderer, 76, 175, 80, 1);
    SDL_RenderFillRect(renderer, &Option[2]);
    renderText(renderer, Option[2].x + 120, Option[2].y + 15 ,"Level 3", black, font);

    SDL_SetRenderDrawColor(renderer, 76, 175, 80, 1);
    SDL_RenderFillRect(renderer, &Option[3]);
    renderText(renderer, Option[3].x + 60, Option[3].y + 15, "Back to Main Menu", black, font);
    SDL_RenderPresent(renderer);
}
std::string intToString(int value) {
    return std::to_string(value);
}
void Handle_map(SDL_Renderer* renderer, TTF_Font* font, int numNodes, int radius, int** weightMatrix, SDL_Texture* BackgroundTexture, SDL_Texture* Characterimg, SDL_Rect imageRect, Character& character, Node *a, int& mouseX, int& mouseY, Node &current_coordinate, int &z, bool &ready_move)
{
    
    std::string counterText = "Total distance: " + intToString(counter);
    SDL_SetRenderDrawColor(renderer, 76, 175, 80, 1);
    SDL_RenderFillRect(renderer, &HintButton);
    renderText(renderer, 650, 100, "Hint", black, font);
    SDL_RenderFillRect(renderer, &CounterTable);
    renderText(renderer, 250, 100, counterText, black, font);
    SDL_RenderPresent(renderer);
    if (isMouseInsideCircle(mouseX, mouseY, current_coordinate.x, current_coordinate.y, radius))
    {
        SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));
        for (int j = 0; j < numNodes; j++)
        {
            if (weightMatrix[z][j] != 100 && weightMatrix[z][j] != 0)
            {
                drawNode(renderer, a[j], black, font, radius);
                SDL_RenderPresent(renderer);
            }

        }
        
        ready_move = true;

    }
    else if (ready_move)
    {

       
        for (int j = 0; j < numNodes; j++)
        {
            if (isMouseInsideCircle(mouseX, mouseY, a[j].x, a[j].y, radius) && !(a[j].x == current_coordinate.x && a[j].y == current_coordinate.y) && weightMatrix[z][j] != 100 && weightMatrix[z][j] != 0)
            {
                SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND));

                while (true)
                {

                    SDL_RenderClear(renderer);
                    SDL_RenderCopy(renderer, BackgroundTexture, NULL, NULL);
                    moveCharacterToPosition(character, a[j].x, a[j].y, 3);

                    // Vẽ lại đồ thị và nhân vật
                    drawGraph(renderer, weightMatrix, font, numNodes, radius,a);

                    // Vẽ nhân vật


                    // 
                    imageRect = { character.x, character.y, 30, 30 };
                    SDL_RenderCopy(renderer, Characterimg, NULL, &imageRect);
                  
                    // Cập nhật cửa sổ
                    SDL_RenderPresent(renderer);
                    if (character.x == a[j].x - 15 && character.y == a[j].y - 15)
                        break;
                   

                }
                counter += weightMatrix[z][j];
                current_coordinate = a[j];
                
                z = j;
                SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
                SDL_Surface* BackSurface = IMG_Load("Back_button.png");
                if (BackSurface == nullptr) {
                    std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
                    return;
                }
                SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, BackSurface);
                SDL_FreeSurface(BackSurface); // Giải phóng bộ nhớ sau khi tạo texture
                SDL_RenderCopy(renderer, imageTexture, NULL, &Back_button);
                SDL_SetRenderDrawColor(renderer, 76, 175, 80, 1);
                SDL_RenderFillRect(renderer, &HintButton);
                renderText(renderer, 650, 100, "Hint", black, font);
                SDL_RenderFillRect(renderer, &CounterTable);
                counterText = "Total distance: " + intToString(counter);
                renderText(renderer, 250, 100, counterText, black, font);
                SDL_RenderPresent(renderer);
               
            }
            
            
        }
        ready_move = false;
        
        saveprogress.push_back(current_coordinate.number);

    }
    else
    {
        
        SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
        ready_move = false;
        
    }
  
    
        
}
void create(vector<int>& previous, int start, int end) {
    if (start == end) {
        temp.push_back(start + 1);
        return;
    }
    create(previous, start, previous[end]);
    temp.push_back(end + 1);
}
void Dijkstra(int** weightMatrix, int numNodes, int startNode, vector<Node>& a,vector<int>&previous) {
    vector<int> distance(numNodes, INT_MAX);

    vector<bool> visited(numNodes, false);

    distance[startNode] = 0;

    for (int i = 0; i < numNodes - 1; ++i) {
        int minDistance = INT_MAX, minIndex;

        for (int v = 0; v < numNodes; ++v)
            if (!visited[v] && distance[v] <= minDistance) {
                minDistance = distance[v];
                minIndex = v;
            }

        int u = minIndex;
        visited[u] = true;

        for (int v = 0; v < numNodes; ++v)
            if (!visited[v] && weightMatrix[u][v] && distance[u] != INT_MAX && distance[u] + weightMatrix[u][v] < distance[v]) {
                distance[v] = distance[u] + weightMatrix[u][v];
                previous[v] = u;
            }
    }

    // In ra khoảng cách và đường đi từ đỉnh xuất phát đến các đỉnh khác
    /*for (int i = 0; i < numNodes; ++i) {
        cout << "Khoang cach tu dinh " << startNode + 1 << " den dinh " << i + 1 << " la " << distance[i] << ", Duong di: ";
        printPath(previous, startNode, i);
        cout << endl;
    }*/
}
void moveCharacterToNode(SDL_Renderer* renderer, int** weightMatrix, TTF_Font* font,SDL_Texture*BackgroundTexture, SDL_Texture* imageTexture, int numNodes, int radius, Character& character, Node destination, int speed, int characterWidth, int characterHeight,Node *a) {
    while (true) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, BackgroundTexture, NULL, NULL);
        

        // Vẽ lại đồ thị và nhân vật
      
        moveCharacterToPosition(character, destination.x, destination.y, speed);

        // Vẽ lại đồ thị và nhân vật
        drawGraph(renderer, weightMatrix, font, numNodes, radius,a);

        // Vẽ nhân vật
        SDL_Rect imageRect = { character.x, character.y, 30, 30 };
        SDL_RenderCopy(renderer, imageTexture, NULL, &imageRect);

        // Cập nhật cửa sổ
        SDL_RenderPresent(renderer);

        if (character.x == destination.x - 15 && character.y == destination.y - 15) {
            break;
        }
    }
}
