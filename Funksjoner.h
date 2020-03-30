#ifndef Funksjoner_H
#define Funksjoner_H
#include <string>

void hovedMeny();		//utskrift av kommandoer for Kunder, Soner og Oppdrag/bolig
void kundeMeny();		//utskrift av kommandoer for Kunder: N, 1, A, E, S og O
void lesEpostAdr(std::string & epost);
void lesGateAdr(std::string & gta);
void lesPostAdr(std::string & pad);
void menyOppdrag();
void menySone();
void oppdragMeny();		//utskrift av kommandoer for Oppdrag: N, 1 og S
void skrivNavn(std::string & nvn);
void soneMeny();		//utskrift av kommandoer for Soner: N, 1 og A



#endif
