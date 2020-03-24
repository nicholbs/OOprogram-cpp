#pragma once
#include "Bolig.h"
class Enebolig : public Bolig
{
	int areal;
	bool festetomt;

public:
	Enebolig(int id);
	~Enebolig();
};

