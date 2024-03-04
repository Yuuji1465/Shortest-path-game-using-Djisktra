#include "Prototype.h"
#include "Header.h"


int main(int argc, char* args[]) {
    initSDL();
    TTF_Font* font = TTF_OpenFont("arialbd.ttf", 14);
    TTF_Font* Menu_font = TTF_OpenFont("arialbd.ttf", 20);
    TTF_Font* Menu_font1 = TTF_OpenFont("arialbd.ttf", 50);

    if (font == nullptr) {
        std::cerr << "Không thể mở font" << std::endl;
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("Graph Drawing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        return 1;
    }
    int radius = 12;
    //int currentTargetIndex = 0; // Chỉ mục của điểm đích hiện tại
    int numNodes; // Số đỉnh của đồ thị
    int** weightMatrix = nullptr;
    Character character;
    SDL_Texture* BackgroundTexture = LoadImg(renderer, "BackgroundTheme.jpg");
    SDL_Surface* imageSurface = IMG_Load("character.jpg");
    if (imageSurface == nullptr) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return 1;
    }
    SDL_SetColorKey(imageSurface, SDL_TRUE, SDL_MapRGB(imageSurface->format, 247, 247, 247));

    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    int characterWidth, characterHeight;
    SDL_QueryTexture(imageTexture, NULL, NULL, &characterWidth, &characterHeight);
    SDL_FreeSurface(imageSurface); // Giải phóng bộ nhớ sau khi tạo texture

    bool quit = false;
    SDL_Event e; int z = 0;
    Node current_coordinate;
    bool ready_move = false;
    Node* map = nullptr;
    bool canClick = false;
    GameState currentState = MAIN_MENU;
    int mapchoose = 0;
    int dest;
    bool youwin;
    bool correctAns;
    bool choose = false;
    bool rightPath = true;
    SDL_Rect imageRect = { 85, 285, 30, 30 };
    MainMenu(renderer, Menu_font, Menu_font1, BackgroundTexture);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX >= Startbutton.x && mouseX <= Startbutton.x + Startbutton.w &&
                    mouseY >= Startbutton.y && mouseY <= Startbutton.y + Startbutton.h && currentState == MAIN_MENU) {
                    // Xử lý khi nhấp vào nút Start
                    SDL_RenderClear(renderer);
                    currentState = LEVEL_MENU;
                }

                // Kiểm tra xem chuột có nằm trong nút Exit hay không
                if (mouseX >= Exitbutton.x && mouseX <= Exitbutton.x + Exitbutton.w &&
                    mouseY >= Exitbutton.y && mouseY <= Exitbutton.y + Exitbutton.h && currentState == MAIN_MENU) {
                    quit = true;
                }

                if (currentState == LEVEL_MENU)
                {
                    choose = false;
                    counter = 0;
                    LevelMenu(renderer, Menu_font, BackgroundTexture);
                    if (mouseX >= Option[3].x && mouseX <= Option[3].x + Option[3].w &&
                        mouseY >= Option[3].y && mouseY <= Option[3].y + Option[3].h)
                    {
                        SDL_RenderClear(renderer);
                        MainMenu(renderer, Menu_font, Menu_font1, BackgroundTexture);
                        currentState = MAIN_MENU;
                    }
                    else if (mouseX >= Option[0].x && mouseX <= Option[0].x + Option[0].w &&
                        mouseY >= Option[0].y && mouseY <= Option[0].y + Option[0].h)
                    {

                        weightMatrix = readInputFromFile("input2.txt", numNodes); // Đọc dữ liệu từ tệp
                        for (int i = 0; i < numNodes; ++i) {
                            for (int j = 0; j < numNodes; ++j) {
                                std::cout << weightMatrix[i][j] << " ";
                            }
                            std::cout << std::endl;
                        }
                        imageRect = { 85, 285, 30, 30 };
                        character.x = 85; character.y = 285;
                        map = map1;
                        dest = 8;
                        current_coordinate = map[0];
                        saveprogress.emplace(saveprogress.begin(), current_coordinate.number);
                        rendermap(renderer, font, numNodes, radius, weightMatrix, BackgroundTexture, imageTexture, imageRect, character, map, mouseX, mouseY, current_coordinate);
                        currentState = In_Game;
                        mapchoose = 1;
                    }
                    else if (mouseX >= Option[1].x && mouseX <= Option[1].x + Option[1].w &&
                        mouseY >= Option[1].y && mouseY <= Option[1].y + Option[1].h)
                    {
                        weightMatrix = readInputFromFile("Level2.txt", numNodes); // Đọc dữ liệu từ tệp
                        for (int i = 0; i < numNodes; ++i) {
                            for (int j = 0; j < numNodes; ++j) {
                                std::cout << weightMatrix[i][j] << " ";
                            }
                            std::cout << std::endl;
                        }
                        map = map2;
                        dest = 17;
                        imageRect = { 85,135,30,30 };
                        current_coordinate = map2[0];
                        saveprogress.emplace(saveprogress.begin(), current_coordinate.number);
                        character.x = 85; character.y = 135;
                        rendermap(renderer, font, numNodes, radius, weightMatrix, BackgroundTexture, imageTexture, imageRect, character, map2, mouseX, mouseY, current_coordinate);
                        currentState = In_Game;
                        mapchoose = 2;
                    }
                    else if (mouseX >= Option[2].x && mouseX <= Option[2].x + Option[2].w &&
                        mouseY >= Option[2].y && mouseY <= Option[2].y + Option[2].h)
                    {
                        weightMatrix = readInputFromFile("Level3.txt", numNodes); // Đọc dữ liệu từ tệp
                        for (int i = 0; i < numNodes; ++i) {
                            for (int j = 0; j < numNodes; ++j) {
                                std::cout << weightMatrix[i][j] << " ";
                            }
                            std::cout << std::endl;
                        }
                        map = map3;
                        dest = 20;
                        imageRect = { 85,185,30,30 };
                        current_coordinate = map3[0];
                        saveprogress.emplace(saveprogress.begin(), current_coordinate.number);
                        character.x = 85; character.y = 185;
                        rendermap(renderer, font, numNodes, radius, weightMatrix, BackgroundTexture, imageTexture, imageRect, character, map3, mouseX, mouseY, current_coordinate);
                        currentState = In_Game;
                        mapchoose = 3;
                    }
                    else
                        SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
                }
                if (currentState == In_Game)
                {
                    vector<int>previous(numNodes, -1);
                    vector<Node> nodes(map, map + sizeof(map) / sizeof(map[0]));
                    Dijkstra(weightMatrix, numNodes, 0, nodes, previous);
                    if (choose == false) {
  
                        cout << endl;
                        
                        cout << endl;
                        cout << "click vao nhan vat de chon duong di";
                        choose = true;
                        create(previous, 0, dest - 1);
                    }
                    Handle_map(renderer, font, numNodes, radius, weightMatrix, BackgroundTexture, imageTexture, imageRect, character, map, mouseX, mouseY, current_coordinate, z, ready_move);
                    if (mouseX >= Back_button.x && mouseX <= Back_button.x + Back_button.w &&
                        mouseY >= Back_button.y && mouseY <= Back_button.y + Back_button.h)
                    {
                        SDL_RenderClear(renderer);
                        LevelMenu(renderer, Menu_font, BackgroundTexture);
                        currentState = LEVEL_MENU;
                        z = 0;
                        ready_move = false;
                    }




                     
                    if (mouseX >= HintButton.x && mouseX <= HintButton.x + HintButton.w &&
                        mouseY >= HintButton.y && mouseY <= HintButton.y + HintButton.h) {
                       /* for (int it : temp) cout << it << " ";*/
                        for (auto& it : temp) {
                            moveCharacterToNode(renderer, weightMatrix, font, BackgroundTexture, imageTexture, numNodes, radius, character, map[it - 1], 2, characterWidth, characterHeight, map);
                           
                            
                        }
                        /*for (size_t i = 0; i < temp.size(); i++) {
                            if (temp[i] == current_coordinate.number) {
                                cout << "Duong di tiep theo la: " << temp[i + 1];
                                cout << endl;
                                break;
                            }

                        }*/
                        SDL_SetRenderDrawColor(renderer, 76, 175, 80, 1);
                        SDL_RenderFillRect(renderer, &Button);
                        renderText(renderer, 380, 303, "You lose", black, font);
                        cout << endl;
                        cout << "Click vao You Lose de quay ve menu";
                        SDL_RenderPresent(renderer);
                        temp.clear();
                        current_coordinate.number = dest;
                        youwin = false;
                        
        

                        
                    }
                   
                    if (current_coordinate.number == dest) {


                        cout << endl;
                        /*for (int it : temp) cout << it;*/
                        if (saveprogress.size() == temp.size()) {
                            youwin = true;
                            for (size_t i = 0; i < saveprogress.size(); i++) {
                                if (saveprogress[i] != temp[i]) {
                                    youwin = false;
                                    break;
                                }
                            }
                        }
                        else { youwin = false; }
                        cout << youwin;
                        if ((youwin == true)) {
                            SDL_SetRenderDrawColor(renderer, 76, 175, 80, 1);
                            SDL_RenderFillRect(renderer, &Button);
                            renderText(renderer, 380, 303, "You Win", black, font);
                            cout << endl;
                            cout << "Click vao You Win de quay ve menu";
                            SDL_RenderPresent(renderer);
                            temp.clear();
                            saveprogress.clear();
                        }
                        else {
                            SDL_SetRenderDrawColor(renderer, 76, 175, 80, 1);
                            SDL_RenderFillRect(renderer, &Button);
                            renderText(renderer, 380, 303, "You lose", black, font);
                            cout << endl;
                            cout << "Click vao You Lose de quay ve menu";
                            SDL_RenderPresent(renderer);
                            temp.clear();
                            saveprogress.clear();
                        }
                        if ((mouseX >= Button.x && mouseX <= Button.x + Button.w &&
                            mouseY >= Button.y && mouseY <= Button.y + Button.h)) {
                            SDL_RenderClear(renderer);
                            LevelMenu(renderer, Menu_font, BackgroundTexture);
                            currentState = LEVEL_MENU;
                            z = 0;
                            ready_move = false;
                            
                        }
                  

                    }


                }

            }
        }
    }
    // Hiển thị lên cửa sổ
    SDL_RenderPresent(renderer);
    // Giải phóng bộ nhớ

    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}