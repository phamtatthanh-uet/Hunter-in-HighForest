#include "Game_Base.h"
#include"LTexture.h"
#include "Button.h"
#include "GameFeature.h"

const std::string LAYER[BACKGROUND_LAYER] = {
	"imgs/background/plx-1.png",
	"imgs/background/plx-2.png",
	"imgs/background/plx-3.png",
	"imgs/background/plx-4.png",
	"imgs/background/plx-5.png",
};



bool init();
bool loadMedia();
void close();

LTexture gBackGroundTexture;
LTexture gBackgroundTexture[BACKGROUND_LAYER];
LTexture gPlayButtonTexture;
LTexture gGroundTexture; 

Button PlayButton(PLAY_BUTTON_POSX, PLAY_BUTTON_POSY);


SDL_Rect gPlayButton[BUTTON_TOTAL];


SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{

			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load PNG texture
	if (!gBackGroundTexture.LoadFromFile("imgs/background/menu.png", gRenderer)) {
		printf("Failed to load texture image!\n");
		success = false;
	}
	if (!gPlayButtonTexture.LoadFromFile("imgs/button/big_button/play_button.png",gRenderer)) {
		printf("Fail to load play_button image!\n");
		success = false;
	}
	else
	{
		for (int i = 0; i < BUTTON_TOTAL; ++i)
		{
			gPlayButton[i].x = 150* i;
			gPlayButton[i].y = 0;
			gPlayButton[i].w = 150;
			gPlayButton[i].h = 98;
		}
	}
	for (int i = 0; i < BACKGROUND_LAYER; ++i) {
		if (!gBackgroundTexture[i].LoadFromFile(LAYER[i].c_str(), gRenderer)) {
			printf("Fail to load BackGroundTexture");
			success = false;
		}
	}
	if (!gGroundTexture.LoadFromFile("imgs/background/ground.png", gRenderer))
	{
		std::cout << "Failed to load ground image" << std::endl;
		success = false;
	}
	return success;
}

void close()
{
	gBackGroundTexture.Free();
	gPlayButtonTexture.Free();
	for (int i = 0; i < BACKGROUND_LAYER; ++i) {
		gBackgroundTexture[i].Free();
	}
	gGroundTexture.Free();
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool Quit_Menu = false;
			bool Play_Again = false;

			//Event handler


			//While application is running
			while (!Quit_Menu)
			{
				SDL_Event e;
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						Quit_Menu = true;
					}
					bool Quit_Game = false;
					HandlePlayButton(&e, PlayButton, Quit_Menu, Play_Again);
					if (Quit_Game == true) {
						return 0;
					}

				}
				gBackGroundTexture.upBackGround(gRenderer);

				SDL_Rect* currentClip_Play = &gPlayButton[PlayButton.currentSprite];
				PlayButton.Render(currentClip_Play, gRenderer, gPlayButtonTexture);


				// Update screen
				SDL_RenderPresent(gRenderer);
			}
			while (Play_Again)
			{
				SDL_Event e;
				int OffsetSpeed_Ground = BASE_OFFSET_SPEED;
				std::vector <double> OffsetSpeed_Bkgr(BACKGROUND_LAYER, BASE_OFFSET_SPEED);

				bool Quit = false;
				bool Game_State = true;
				while (!Quit)
				{
					if (Game_State)
					{
						while (SDL_PollEvent(&e) != 0)
						{
							if (e.type == SDL_QUIT)
							{
								Quit = true;
								Play_Again = false;
							}
						}

						SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
						SDL_RenderClear(gRenderer);

						RenderScrollingBackground(OffsetSpeed_Bkgr, gBackgroundTexture, gRenderer);
						SDL_RenderPresent(gRenderer);
					}
				}
			}
		}
	}
	//Free resources and close SDL
	close();

	return 0;
}