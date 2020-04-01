#ifndef __Funksjoner_H
#define __Funksjoner_H
#include <string>

void hovedMeny();		//utskrift av kommandoer for Kunder, Soner og Oppdrag/bolig
void kundeMeny();		//utskrift av kommandoer for Kunder: N, 1, A, E, S og O
void soneMeny();		//utskrift av kommandoer for Soner: N, 1 og A
void oppdragMeny();		//utskrift av kommandoer for Oppdrag: N, 1 og S

void menyKunde();
void menySone();
void menyOppdrag();

void lesEpostAdr(std::string & epost);
void lesGateAdr(std::string & gta);
void lesPostAdr(std::string & pad);
void skrivNavn(std::string & nvn);

void kundeOversiktTilFil();

#endif