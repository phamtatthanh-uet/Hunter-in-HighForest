#pragma once
#include"Game_Base.h"
#include<string>
class LTexture {
public:
	LTexture();
	~LTexture();
	void Free();
	bool LoadFromFile(std::string path, SDL_Renderer* gRenderer);
	void Render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = nullptr);
	void upBackGround(SDL_Renderer* gRenderer);
	int getWidth();
	int getHeight();
private: 
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
};