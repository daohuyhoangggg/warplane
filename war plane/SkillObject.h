﻿#ifndef SKILL_OBJECT_H_
#define SKILL_OBJECT_H_

#include "BaseObject.h"
#include "thuvien.h"
#include <vector>


class SkillObject : public BaseObject
{
public:
	enum{
		STAR = 0,			// cộng điểm
		SHIELD = 1			// cường hóa đạn
	};

	SkillObject ();
	~SkillObject ();

	void InitSkill(SkillObject* p_object);
	void MakeSkill(SDL_Surface* des, const int& x_limit, const int& y_limit);
	void HandleMove(const int& x_border, const int& y_border);
	void Reset(const int& x_border);

	int get_type() const {return skill_type_;}
	void set_type(const int& type) {skill_type_ = type;}
private:
	int skill_type_;
	std::vector<SkillObject*> p_skill_list;
};

#endif