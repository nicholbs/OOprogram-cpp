#pragma once
#include <map>
using namespace std;

class Sone;
class Bolig;
class Soner
{
private:
	const int MAX_SONER = 100;
	int sisteNr;
	map <int, Sone*> soneMap;

public:	
	void nySone(int snr);
	void nyttOppdrag(int snr);
	bool finnesSone(int snr);
	const Bolig& finnOppdrag(int onr);
};