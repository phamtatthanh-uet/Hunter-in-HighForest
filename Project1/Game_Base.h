#pragma once

#include<SDL.h>
#include<iostream>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<string>
#include<vector>

using namespace std; 

const int BACKGROUND_LAYER = 5;

const int SCREEN_WIDTH = 928;
const int SCREEN_HEIGHT = 522;

#define SDL_ERROR 1
#define IMG_ERROR 2
#define MIX_ERROR 3
#define TFF_ERROR 4

#define SMALL_BUTTON 1
#define COMMON_BUTTON 2

#define BASE_OFFSET_SPEED 0

const int SMALL_BUTTON_WIDTH = 22;
const int SMALL_BUTTON_HEIGHT = 34;
const int COMMON_BUTTON_WIDTH = 150;
const int COMMON_BUTTON_HEIGHT = 98;
const int PLAY_BUTTON_POSX = 389;
const int PLAY_BUTTON_POSY = 186;

const double LAYER_1_SPEED = 0.0;
const double LAYER_2_SPEED = 0.15;
const double LAYER_3_SPEED = 0.3;
const double LAYER_4_SPEED = 0.35;
const double LAYER_5_SPEED = 0.2;

enum ButtonSprite {
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER = 1,
	BUTTON_TOTAL = 2
};

void GetError(std::string er, int errorCode = SDL_ERROR);