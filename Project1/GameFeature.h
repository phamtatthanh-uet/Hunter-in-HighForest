#pragma once

#include"LTexture.h"
#include"Game_Base.h"
#include"Button.h"

bool Init();
bool LoadMedia();
void Close();
	
void HandlePlayButton(SDL_Event* e,
    Button& PlayButton,
    bool& QuitMenu,
    bool& Play
   );

void RenderScrollingBackground(std::vector <double>& offsetSpeed,
    LTexture(&gBackgroundTexture)[BACKGROUND_LAYER],
    SDL_Renderer* gRenderer);