﻿#include "thuvien.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "ThreatObject.h"
#include "ExplosionObject.h"
#include "SkillObject.h"
#include "TextObject.h"

bool init();  // Thiet lap cua so man hinh
TTF_Font* g_fond_text = NULL;

int  main(int arc, char* argv[])
{

	if(!init())return -1;

	gBkground = SDLCommonFunc::LoadImage(g_name_back_ground);
	if(gBkground == NULL)return -1;

	// Create MainObject
	MainObject plane_object;
	bool ret = plane_object.LoadImg(g_name_main_obj);		// load ảnh nhân vật
	plane_object.SetRect(X_STAR_MAIN, Y_STAR_MAIN);
	if(ret == NULL) 
	{
		 printf( "Unable to load image %s! SDL Error: %s\n", g_name_main_obj, SDL_GetError() );
		return 0;
	}
	

	//Create ExplosionObject
	ExplosionObject exp;		
	ret = exp.LoadImg(g_name_exp_obj);
	if(ret == NULL) 
	{
		printf( "Unable to load image %s! SDL Error: %s\n", g_name_exp_obj, SDL_GetError() );
		return 0;
	}
	exp.set_clip();

	// Create ThreatObject
	ThreatObject* p_threats = new ThreatObject[THREATS];
	for(int t = 0; t < THREATS; t++)
	{
		ThreatObject* p_threat = (p_threats + t);
		if(p_threat)
		{
			ret = p_threat->LoadImg(g_name_threat_obj);
			if(ret == NULL)
			{
				printf( "Unable to load image %s! SDL Error: %s\n", g_name_threat_obj, SDL_GetError() );
				return 0;
			}

			int rand_y = rand()% MAX_HEIGHT_OF_THREAT + 50;
			if(rand_y > SCREEN_HEIGHT - 250)
			{
				rand_y = SCREEN_HEIGHT * 0.3;
			}

			p_threat->SetRect(SCREEN_WIDTH + t*500, rand_y);		// lam cho cac threat xuat hien khac thoi diem
			p_threat->set_x_val(SPEED_THREAT);

			// nap dan cho doi tuong threat
			BulletObject* p_bullet = new BulletObject();
			p_threat->InitBullet(p_bullet);

		}
	
	}


	// Create skill
	SkillObject* p_skills = new SkillObject[SKILLS];
	for(int s = 0; s < SKILLS; s++)
	{
		SkillObject* p_skill = (p_skills + s);
		if(p_skill)
		{
			int rand_y = rand()% MAX_HEIGHT_OF_THREAT + 20;
			if(rand_y > SCREEN_HEIGHT - UNDER_LIMIT_THREAT)
			{
				rand_y = SCREEN_HEIGHT * 0.3;
			} 
			p_skill->InitSkill(p_skill);
			p_skill->SetRect(SCREEN_WIDTH + s*400, rand_y);
		}
	}

	// Create gold medal
	gMedal = SDLCommonFunc::LoadImage(g_name_medal);
	if(gMedal == NULL){
		printf( "Unable to load image %s! SDL Error: %s\n", g_name_medal, SDL_GetError() );
		return 0;
	}

	// Create point_game
	TextObject point_game;
	point_game.SetColor(TextObject::BLACK_TEXT);
	int point = 0;


	bool is_quit = false;
	bool is_mouseButton = false;
	bool is_play = false;
	int speed_screen = 0;

	while(!is_quit)			// cap nhap man hình
	{
			
				while(SDL_PollEvent(&gEven))
				{
					if(gEven.type == SDL_QUIT){
						is_quit = true;
						break;
					}
					else if (gEven.type == SDL_MOUSEBUTTONDOWN) {
						if (gEven.button.button == SDL_BUTTON_LEFT) {
							is_mouseButton = true;	
							is_play = true;
							plane_object.Flap();
							plane_object.CreateBullet();		// Đặt biến trạng thái là true khi chuột được nhấn
					}
				}		
				else if (gEven.type == SDL_MOUSEBUTTONUP) {
					if (gEven.button.button == SDL_BUTTON_LEFT) {
						is_mouseButton = false;				// Đặt biến trạng thái là false khi chuột được nhả
					}
				}
		}
		if(is_mouseButton){
			plane_object.Flap();
		}	
		

		// apply background && xử lý di chuyển màn hình
		speed_screen -= SCREEN_SPEED;
		SDLCommonFunc::ApplySurface(gBkground, gScreen, speed_screen, 0);
		SDLCommonFunc::ApplySurface(gBkground, gScreen, speed_screen + SCREEN_WIDTH, 0);
		if (speed_screen <= -SCREEN_WIDTH) speed_screen = 0;

		// Make MainObject
		if(is_play)
		{
			plane_object.HandleMove();
		}
		plane_object.Show(gScreen);
		plane_object.MakeBullet(gScreen); // xử lý đạn cho đối tượng chính


		// Show gold medal
		SDLCommonFunc::ApplySurface(gMedal, gScreen, 1000, 8);


		//Make Skill object
		for(int ss = 0; ss < SKILLS; ss++)
		{
			SkillObject* p_skill = (p_skills + ss);
			if(p_skill)
			{
				p_skill->MakeSkill(gScreen, SCREEN_WIDTH, SCREEN_HEIGHT);
				p_skill->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);


				//Main object khi ăn được skill
				bool is_col3 = SDLCommonFunc::CheckCollision(plane_object.GetRect(), p_skill->GetRect());
				if(is_col3)
				{
					if(p_skill->get_type() == 0)
					{
						point += 10;
						p_skill->Reset(SCREEN_WIDTH);
					}
					
				}

			}
		}


		// Make ThreatObject
		for(int tt = 0; tt < THREATS; tt++)
		{
			ThreatObject* p_threat = (p_threats + tt);
			if(p_threat)
			{
				p_threat->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->Show(gScreen);
				if(p_threat->GetRect().x > plane_object.GetRect().x)
				{
					p_threat->MakeBullet(gScreen, SCREEN_WIDTH, SCREEN_HEIGHT);


					// xử lý va chạm giữa main và bullet_threat 
					std::vector<BulletObject*>bulletT_list = p_threat->GetBulletList();
					for(int  bt = 0; bt < bulletT_list.size(); bt++)
					{
						bool is_col = SDLCommonFunc::CheckCollision(plane_object.GetRect(), bulletT_list.at(bt)->GetRect());
						if(is_col)
						{

							// thực hiện vụ nổ cho main object 
							for(int ex_m = 0; ex_m < NUMBER_OF_FRAMES; ex_m++)
							{
								int x = (plane_object.GetRect().x + plane_object.GetRect().w * 0.5) - EXPLOSION_WIDTH * 0.5;
								int y = (plane_object.GetRect().y + plane_object.GetRect().h * 0.5) - EXPLOSION_HEIGHT * 0.5;

								exp.set_frame(ex_m);
								exp.SetRect(x, y);
								exp.ShowEx(gScreen);


								if(SDL_Flip(gScreen) == -1)return -1;


							}

							if(MessageBox(NULL, L"GAME OVER!", L"Info", MB_OK) == IDOK)
							{
								SDLCommonFunc::CleanUp();
								SDL_Quit();
								return -1;
							}
						}
					} 



					// xử lý va chạm giữa main và threat
					bool is_col1 = SDLCommonFunc::CheckCollision(plane_object.GetRect(), p_threat->GetRect());
					if(is_col1)
					{

						// thực hiện vụ nổ cho main object 
						for(int ex_m = 0; ex_m < NUMBER_OF_FRAMES; ex_m++)
						{
							int x = (plane_object.GetRect().x + plane_object.GetRect().w * 0.5) - EXPLOSION_WIDTH * 0.5;
							int y = (plane_object.GetRect().y + plane_object.GetRect().h * 0.5) - EXPLOSION_HEIGHT * 0.5;

							exp.set_frame(ex_m);
							exp.SetRect(x, y);
							exp.ShowEx(gScreen);
							

							if(SDL_Flip(gScreen) == -1)return -1;


						}



						// thực hiện vụ nổ cho threat object 
						for(int ex_t = 0; ex_t < NUMBER_OF_FRAMES; ex_t++)
						{
							int x = (p_threat->GetRect().x + p_threat->GetRect().w * 0.5) - EXPLOSION_WIDTH * 0.5;
							int y = (p_threat->GetRect().y + p_threat->GetRect().h * 0.5) - EXPLOSION_HEIGHT * 0.5;

							exp.set_frame(ex_t);
							exp.SetRect(x, y);
							exp.ShowEx(gScreen);

							if(SDL_Flip(gScreen) == -1)
							{
								delete [] p_threats;
								SDLCommonFunc::CleanUp();
								SDL_Quit();
								return -1;
							}
						}


						if(MessageBox(NULL, L"GAME OVER!", L"Info", MB_OK) == IDOK)
						{
							SDLCommonFunc::CleanUp();
							SDL_Quit();
							return -1;
						}
					}



					// xử lý va chạm giữa đạn của main object với threat object
					std::vector<BulletObject*> bulletM_list = plane_object.GetBulletList();
					for(int bm = 0; bm < bulletM_list.size(); bm++)
					{
						bool is_col2 = SDLCommonFunc::CheckCollision(bulletM_list.at(bm)->GetRect(), p_threat->GetRect());
						if(is_col2)
						{
							point += 10;
							for(int ex_t = 0; ex_t < NUMBER_OF_FRAMES; ex_t++)
							{
								int x = (p_threat->GetRect().x + p_threat->GetRect().w * 0.5) - EXPLOSION_WIDTH * 0.5;
								int y = (p_threat->GetRect().y + p_threat->GetRect().h * 0.5) - EXPLOSION_HEIGHT * 0.5;

								exp.set_frame(ex_t);
								exp.SetRect(x, y);
								exp.ShowEx(gScreen);
								if(SDL_Flip(gScreen) == -1)return -1;
							}
							
							bulletM_list.at(bm)->set_is_move(false);
							p_threat->Reset(SCREEN_WIDTH);	

						}

					}
				}
			}
		}
		// Show point_game
		std::string val_str_point = std::to_string(point);
		std::string strPoint("");
		strPoint += val_str_point;

		point_game.SetText(strPoint);
		point_game.CreateText(g_fond_text, gScreen);


		// Update screen
		if(SDL_Flip(gScreen) == -1)				// hiển thị
		{
			delete [] p_threats;
			SDLCommonFunc::CleanUp();
			SDL_Quit();
			return -1;
		}			
	}


	SDLCommonFunc::CleanUp();
	SDL_Quit();

	return 0;	
}

bool init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)					// khởi tạo các thành phần của SDL
	{
		return false;
	}
	gScreen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT,SCREEN_BPP, SDL_SWSURFACE);						// thiết lập cửa sổ video
	if(gScreen == NULL)
	{
		return false;
	}

	if(TTF_Init() == -1)
	{
		return false;
	}

	g_fond_text = TTF_OpenFont(g_font_text, 30);
	if(g_fond_text == NULL)
	{
		return false;
	}


	return true;
}

