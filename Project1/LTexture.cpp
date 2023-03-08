#include"LTexture.h"

LTexture::LTexture() {
	mTexture = nullptr;

	mHeight = 0; 
	mWidth = 0;
}

LTexture::~LTexture() {
	Free();
}

void LTexture::Free() {
	if (mTexture != nullptr) {
		mHeight = 0;
		mWidth = 0;
	}
}

bool LTexture::LoadFromFile(std::string path, SDL_Renderer* gRenderer) {
	Free();
	SDL_Texture* tmpTexture = nullptr;
	SDL_Surface* tmpSurface = IMG_Load(path.c_str());

	if (tmpSurface == nullptr) {
		GetError("Can not load image.", IMG_ERROR);
	}
	else {
		SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));
		tmpTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
		if (tmpTexture == nullptr) {
			GetError("Can not create texture from surface.", SDL_ERROR);
		}
		else {
			mWidth = tmpSurface->w;
			mHeight = tmpSurface->h;
		}
		SDL_FreeSurface(tmpSurface);
	}
	mTexture = tmpTexture; 
	return mTexture != nullptr;
}
void LTexture::Render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
	SDL_Rect renderSpace = { x, y, mWidth, mHeight };

	if (clip != nullptr)
	{
		renderSpace.w = clip->w;
		renderSpace.h = clip->h;
	}

	SDL_RenderCopy(gRenderer, mTexture, clip, &renderSpace);
}
void LTexture::upBackGround(SDL_Renderer* gRenderer) {
	SDL_RenderCopy(gRenderer, mTexture, NULL, NULL);
}

int LTexture::getHeight() {
	return mHeight;
}

int LTexture::getWidth() {
	return mWidth;
}