#include"GameFeature.h"
#include"LTexture.h"

void HandlePlayButton(SDL_Event* e,
    Button& PlayButton,
    bool& QuitMenu,
    bool& Play) {
		
			if (e->type == SDL_QUIT)
			{
				QuitMenu = true;
			}

			if (PlayButton.IsInside(e, COMMON_BUTTON))
			{
				switch (e->type)
				{
				case SDL_MOUSEMOTION:
					PlayButton.currentSprite = BUTTON_MOUSE_OVER;
					break;
				case SDL_MOUSEBUTTONDOWN:
					Play = true;
					QuitMenu = true;
					/*Mix_PlayChannel(MIX_CHANNEL, gClick, 0);*/
					PlayButton.currentSprite = BUTTON_MOUSE_OVER;
					break;
				}
			}
			else
			{
				PlayButton.currentSprite = BUTTON_MOUSE_OUT;
			}		
}
void RenderScrollingBackground(std::vector <double>& offsetSpeed,
	LTexture(&gBackgroundTexture)[BACKGROUND_LAYER],
	SDL_Renderer* gRenderer)
{
	std::vector <double> layer_speed;
	layer_speed.push_back(LAYER_1_SPEED);
	layer_speed.push_back(LAYER_2_SPEED);
	layer_speed.push_back(LAYER_3_SPEED);
	layer_speed.push_back(LAYER_4_SPEED);
	layer_speed.push_back(LAYER_5_SPEED);

	for (int i = 0; i < BACKGROUND_LAYER; ++i)
	{
		offsetSpeed[i] -= layer_speed[i];
		if (offsetSpeed[i] < -gBackgroundTexture[i].getWidth())
		{
			offsetSpeed[i] = 0;
		}
		gBackgroundTexture[i].Render(offsetSpeed[i],0 , gRenderer);
		gBackgroundTexture[i].Render(offsetSpeed[i] + gBackgroundTexture[i].getWidth(),0, gRenderer);
	}
}