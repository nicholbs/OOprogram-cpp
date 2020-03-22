#pragma once
#include <map>
using namespace std;

class Sone;
class Soner
{
	int sisteNr;
	map <int, Sone*> soneMap;
};

