﻿#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include<windows.h>
#include<SDL.h>
#include<string>
#include<SDL_image.h>
#include<vector>


static SDL_Surface* gScreen = NULL;
static SDL_Surface* gBkground = NULL;
static SDL_Event gEven;


//Screen
const int SCREEN_WIDTH			= 1200;
const int SCREEN_HEIGHT			= 675;
const int SCREEN_BPP			= 32;
const int SCREEN_SPEED			= 2;

// Main object
const int  X_STAR_MAIN			= 150;
const int  Y_STAR_MAIN			= 15;
const int MAX_HEIGHT_OF_MAIN	= SCREEN_HEIGHT - 45;
const int  acceleration			= 1;
const int  SPEEDFLY				= 3;
const int MAX_VELOCITY_Y		= 8;	
const int SPEED_BULLET_MAIN		= 10;

// THREAT OBJECT
const int THREATS				= 2;
const int UNDER_LIMIT_THREAT	= 200;			// giới hạn dưới của mối đe dọa 
const int MAX_HEIGHT_OF_THREAT	= 600;			// độ cao giới hạn 
const int SPEED_THREAT			= 6;
const int SPEED_BULLET_THREAT	= 8;


//EXPLOSION THREAT
const int EXPLOSION_WIDTH		= 165;
const int EXPLOSION_HEIGHT		= 165;
const int NUMBER_OF_FRAMES		= 4;	


// SKILL OBJECT
const int  WIDTH_SKILL			=   50;
const int  HEIGHT_SKILL			=  49;
const int SKILLS				= 3;
const int MAX_HEIGHT_OF_SKILL	= 600;
const int UNDER_LIMIT_SKILL		= 200;

//GOLD MEDAL
static SDL_Surface* gMedal      = NULL;
const int RECT_X_MEDAL			= 1000;
const int RECT_Y_MEDAL			= 8;
const int MEDAL_WIDTH			= 25;
const int MEDAL_HEIGHT			= 28;

//TEXT OBJECT
const int RECT_X_TEXT = RECT_X_MEDAL + MEDAL_WIDTH + 10;
const int RECT_Y_TEXT = RECT_Y_MEDAL;


static char g_name_back_ground[]		= {"img/background_game.jpg"};


static char g_name_main_obj[]			= {"img/plane_object.png"};
static char g_name_bullet_main_obj[]	= {"img/bullet_main.png"};

static char g_name_threat_obj[]			= {"img/threat.png"};
static char g_name_bullet_threat_obj[]	= {"img/bullet_threat.png"};

static char g_name_exp_obj[]			= {"img/exp.png"};

static char g_name_skill_obj[]			= {"img/sao.png"};
static char g_name_medal[]				= {"img/gold.png"};

static char g_font_text[]				={"ttf/dlxfont.ttf"};

namespace SDLCommonFunc
{
	SDL_Surface* LoadImage(std::string file_path);				// tải ảnh 
	void ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);    // vẽ ảnh src lên des(màn hinh) tại tọa độ(x,y)
	void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x ,int y);
	bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);		// xử lý va chạm
	void CleanUp();					// Giải phóng tài nguyên
}

#endif