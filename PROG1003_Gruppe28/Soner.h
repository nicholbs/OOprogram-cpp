#pragma once
#include <map>
using namespace std;

class Sone;
class Soner
{
public:
	int sisteNr;
	map <int, Sone*> soneMap;

	void nySone(int snr);
	void nyBolig(int snr);
};

