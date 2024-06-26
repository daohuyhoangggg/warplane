
#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "BaseObject.h"
#include "BulletObject.h"
#include "thuvien.h"

#define  WIDTH_MAIN_OBJECT	 80
#define  HEIGHT_MAIN_OBJECT	 45

class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();

	void Flap();			
	void HandleMove();		// Xu ly di chuyen

	void CreateBullet1(Mix_Chunk* bullet_sound);
	void CreateBullet2();
	void CreateBullet3();

	void MakeBullet(SDL_Surface* des);

	void SetBulletList(std::vector<BulletObject*> bullet_list) {p_bullet_list = bullet_list;}			
	std::vector<BulletObject*> GetBulletList() const {return p_bullet_list;}

private:
	int x_val_;
	int y_val_;
	int velocity_y;
	std::vector<BulletObject*> p_bullet_list;
};
#endif