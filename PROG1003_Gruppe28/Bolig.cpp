#include "Bolig.h"
#include "LesData3.h"
#include <iostream>
#include <istream>
#include <iomanip>
#include <fstream>		//kanskje denne ikke trengs
#include <string>		//lesFraFil

Bolig::Bolig(int id) {
	ID = id;
	boligType = boligtype::Leilighet;

	cin.ignore();
	dato = lesInt("Dato [YYYYMMDD]: ", 0, 99999999);
	byggeaar = lesInt("Byggeaar: ", 0, 2020);
	bruttoareal = lesInt("Bruttoareal: ", 0, 10000);
	antallSoverom = lesInt("Soverom: ", 1, 20);
	pris = lesInt("Pris: ", 0, 1000000000);

	cout << "Saksbehandler: ";
	getline(cin, navnSaksbehandler);
	cout << "Eier: ";
	getline(cin, navnEier);
	cout << "Gateadresse: ";
	getline(cin, gateadresse);
	cout << "Postadresse: ";
	getline(cin, postadresse);
	cout << "Kort beskrivelse: ";
	getline(cin, beskrivelse);
}

Bolig::Bolig(ifstream& inn)
{
	boligType = boligtype::Leilighet;

	inn >> ID;
	inn.ignore();
	getline(inn, gateadresse);
	getline(inn, postadresse);
	getline(inn, navnEier);
	getline(inn, navnSaksbehandler);
	inn >> dato >> bruttoareal >> antallSoverom >> byggeaar;
	inn.ignore();
	getline(inn, beskrivelse);
	inn >> pris;
	inn.ignore();
}

Bolig::~Bolig() {
	cout << "\nSlettet ";
	if (boligType == boligtype::Leilighet)
		cout << "leilighet";
	else
		cout << "enebolig";
	cout << " med ID " << ID << ".\n";
}

int Bolig::getID() {
	return ID;
}

void Bolig::skrivData() {
	if (boligType == boligtype::Leilighet)
		cout << "\nLeilighet ";
	else
		cout << "\nEnebolig ";
	
	cout << "nr " << ID << ", annonse lagt inn " << dato << '\n'
		<< "Adresse: " << gateadresse << ", " << postadresse << "\n\n"
		<< setw(15) << left << "Eier: " << navnEier << '\n'
		<< setw(15) << left << "Saksbehandler: " << navnSaksbehandler << "\n\n"
		<< "Bruttoareal " << bruttoareal << " kvm med " << antallSoverom << " soverom."
		<< " Bygd " << byggeaar << ".\n" << '\"' << beskrivelse << "\"\n";

	if(boligType == boligtype::Leilighet)
		cout << "Pris: " << pris << " NOK\n\n";
}

void Bolig::skrivTilFil(ofstream& ut) {
	ut << "O-";
	if (boligType == boligtype::Leilighet)
		ut << "L ";
	else
		ut << "E ";
	ut << ID << '\n';

	ut	<< gateadresse << '-' << postadresse << '\n'
		<< navnEier << '\n' << navnSaksbehandler << '\n'
		<< dato << ' ' << bruttoareal << ' '
		<< antallSoverom << ' ' << byggeaar << '\n'
		<< beskrivelse << '\n' << pris << '\n';
}

void Bolig::skrivTilFil(ofstream& ut, vector <int> interesseSone) {
	if (boligType == boligtype::Leilighet)
	{
		ut << "Leilighet" << endl;
	}
	else
	{
		ut << "Enebolig" << endl;
	}


	ut << ID << ' ' << navnSaksbehandler << endl;
	ut << dato << ' ' << navnEier << endl;
	ut << byggeaar << ' ' << gateadresse << endl;
	ut << bruttoareal << ' ' << postadresse << endl;
	ut << antallSoverom << ' ' << beskrivelse << endl;
	ut << pris << endl;

	for (int i = 0; i < interesseSone.size(); i++)
	{
		ut << interesseSone[i];
	}
	ut << endl;
}

void Bolig::lesFraFil() {
	ifstream innfil;
innfil >> ID;
	innfil.ignore();	
		getline(innfil, navnSaksbehandler);
			
innfil >> dato;			
	innfil.ignore();	
		getline(innfil, navnEier);
			
innfil >> byggeaar;		
	innfil.ignore();	
		getline(innfil, gateadresse);
			
innfil >> bruttoareal;	
	innfil.ignore();	
		getline(innfil, postadresse);
			
innfil >> antallSoverom;
	innfil.ignore();	
		getline(innfil, beskrivelse);
	
innfil >> pris;	
	innfil.ignore();	
					
	string kundeSoneInteresse;
	int hentKundeSoneInteresse=NULL;
	innfil >> kundeSoneInteresse;
	kundeSoneInteresse = to_string(hentKundeSoneInteresse);	//Her kan jeg returnere hvilke soner kunden er interessert i, eller la være og bare opprette boligene.
				
	cout << setw(35) << "Her kommer utskrift fra objektet!!!:" << endl;
	cout << setw(35) << ID << endl;
	cout << setw(35) << navnSaksbehandler << endl;
	cout << setw(35) << dato << endl;
	cout << setw(35) << navnEier << endl;
	cout << setw(35) << byggeaar << endl;
	cout << setw(35) << gateadresse << endl;
	cout << setw(35) << bruttoareal << endl;
	cout << setw(35) << postadresse << endl;
	cout << setw(35) << antallSoverom << endl;
	cout << setw(35) << beskrivelse << endl;
}

Bolig::Bolig() {		//Brukt i menyKunder case H. Når vi lager bolig uten parameter leser den inn fra fil og lager enten leilighet eller bolig objekter. Disse blir ikke lagt til i noen containere per nå.
	cout << setw(35) << "Du er nå i Bolig::Bolig()" << endl;
	lesFraFil();
}

bool Bolig::erEnebolig()
{
	return (boligType == boligtype::Enebolig);
}