#ifndef THREAT_OBJECT_H_
#define THREAT_OBJECT_H

#include "thuvien.h"
#include "BaseObject.h"
#include "BulletObject.h"

#define WIDTH_THREAT 80
#define HEIGHT_THREAT 33 




class ThreatObject : public BaseObject
{
public:
	enum{
		THREAT1 = 0,
		THREAT2 = 1
	};
	ThreatObject();
	~ThreatObject();

	void HandleMove(const int& x_border, const int& y_border);
	void set_x_val(const int& val) {x_val_ = val;}
	void set_y_val(const int& val) {y_val_ = val;}
	int get_x_val() const {return x_val_;}
	int get_y_val() const {return y_val_;}

	int get_type() const {return threat_type;}
	void set_type(const int& type) {threat_type = type;}

	// xu ly dan cho doi tuong threat
	void SetBulletList(std::vector<BulletObject*> bullet_list) {p_bullet_list = bullet_list;}
	std::vector<BulletObject*> GetBulletList() const {return p_bullet_list;}
	void Reset(const int& x_border);			// reset each object
	void Reset(ThreatObject* p_threats);		// reset all

	void InitBullet(BulletObject* p_bullet);
	void MakeBullet(SDL_Surface* des, const int& x_limit, const int& y_limit);
	void ResetBullet(BulletObject* p_bullet);

private:
	int x_val_;
	int y_val_;
	int threat_type;
	std::vector<BulletObject*> p_bullet_list;


};
#endif