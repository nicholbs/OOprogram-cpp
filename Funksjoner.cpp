#include "Const.h"
#include "Funksjoner.h"
#include "Kunder.h"
#include "LesData3.h"
#include "Soner.h"
#include <ctype.h>		//toupper()
#include <iostream>
#include <iomanip>
#include <string>
//#include <locale> //sialpha, is nuermic osv

using namespace std;

extern Kunder gKunder;
extern Soner gSoner;

/**
*  Skriver all data i alle boliger i alle kundens interessesoner til fil på leselig format.
*
*  @see Kunder::finnKundeSone(..)
*  @see Soner::finnBoligerISone(..)
*  @see Bolig::skrivTilKundeFil(..)
**/
void kundeOversiktTilFil()
{
	int kundeNr;	//Variabel for å holde medsent int i kommando "K O <knr>"

	cout << '\n';
	cin.ignore();
	kundeNr = lesInt("Kundenummer:", 1, MAX_PERSONER);

	if (!gKunder.kundeListeTomSjekk())
	{
		vector <int> kundeSoneInteresse;	//Holder alle kundens interessesoner
		vector<Bolig*> boligVector;			//Holder alle boligene i en interessesone

		kundeSoneInteresse = gKunder.finnKundeSone(kundeNr);
		if (!kundeSoneInteresse.empty())
		{
			string filNavn = "K" + to_string(kundeNr) + ".DTA";		//Oppretter filnavn
			ofstream ut(filNavn);

			for (int i = 0; i < kundeSoneInteresse.size(); i++)		//Skriver alle boliger i alle interessesoner til fil
			{
				ut << "\n SONE " << kundeSoneInteresse[i] << "\n";
				boligVector = gSoner.finnBoligerISone(kundeSoneInteresse[i]);

				//Skriver all boligdata på leselig format
				ut << "-----------------------------------------------------\n";
				for (int i = 0; i < boligVector.size(); i++)
				{
					if (boligVector[i]->erEnebolig())
						static_cast<Enebolig*>(boligVector[i])->skrivData(ut);
					else
						boligVector[i]->skrivData(ut);
					ut << "\n-----------------------------------------------------\n";
				}
			}
		}
		else
			cout << setw(35) << "Kunden fantes, men han har ingen registrert soner\n" << endl;
	}
	else
		cout << setw(35) << "Det finnes ingen kunder\n" << endl;
}

/**
*	Meny for Kunde basert på input
*
*	De forskjellige kommandoer er:
*	N - lager ny kunde
*	1 - skriver informasjon om en kunde
*	A - skriver hoveddata om alle kunder
*	E - Valgt kunde sin data skrives ut, for å så kunne bli endret
*	S - Sletter valgt kunde
*	O - All data om alle boliger i kundens interessesoner skrives på lesbart og forståelig format til filen Kxxxxx.DTA. Der «xxxxx» er kundens unike nummer.
**/
void menyKunde() {
	char kommando2;
	cin >> kommando2;

	switch (toupper(kommando2)) {
	case 'N':
		gKunder.nyKunde();
		gKunder.kunderSkrivAlleTilFil();
		break;

	case '1':
		//Skriv ut info om enkelt Kunde
		//Stans utskrift hver 10. sone
		cout << setw(35) << "Skriv info om en kunde" << endl;
		gKunder.kundeSkrivData();
		break;

	case 'A':
		//Skriv ut ALLE Kunder
		cout << setw(35) << "Skriv info om alle kunder" << endl;
		gKunder.kundeSAlleSkrivData();
		break;

	case 'E':
		//Skriv ut info om Kunde
		//Bruker kan legge til/slette soner fra kunden | NB SORTER VECTOR
		cout << setw(35) << "Endre info om kunde" << endl;
		gKunder.kundeEndreData();
		gKunder.kunderSkrivAlleTilFil();
		break;

	case 'S':
		//Slett kunde | HUSK PEKER
		cout << setw(35) << "Slett kunde" << endl;
		gKunder.slettKunde();
		gKunder.kunderSkrivAlleTilFil();
		break;

	case 'O':			//K -kunde, O - Skriv ut all data om kundens interesseSone, <knr> -valgt kunde
		kundeOversiktTilFil();
		break;

	case 'D':
		cout << "\nTest skriv ut alle kunder til fil";
		gKunder.kunderSkrivAlleTilFil();
		cout << "\nAlle skrevet til fil";
		break;
	case 'L':
		cout << "\nTest imprt alle kunder fra fil";
		gKunder.kunderLesAlleFraFil();
		cout << "\nFerdig";
		break;

	default:
		cout << setw(35) << "Kunde Default" << endl;
	}
}

/**
*	Meny for Sone basert på input
*
*	De forskjellige kommandoer er:
*	N - lager ny Sone
*	1 - skriver all informasjon om en sone
*	A - skriver hoved data om alle soner
**/
void menySone() {
	char kommando2;
	int snr;

	cin >> kommando2;
	switch (toupper(kommando2)) {
	case 'N':
		cin >> snr;
		gSoner.nySone(snr);
		gSoner.skrivTilFil();
		break;
	case '1':
		cin >> snr;
		gSoner.skrivAlleOppdragISone(snr);
		break;
	case 'A':
		gSoner.skrivHovedDataAlleSoner();
		break;
	default:
		cout << "Sone Default" << endl;
	}
}

/**
*	Meny for Oppdrag basert på input
*
*	De forskjellige kommandoer er:
*	N - lager nytt oppdrag
*	1 - skriver informasjon om ett oppdrag
*	A - skriver all informasjon om alle oppdrag
*	S - Sletter spesifikt oppdrag
**/
void menyOppdrag() {
	char kommando2;
	int nr;

	cin >> kommando2;
	switch (toupper(kommando2)) {
	case 'N':
		cin.ignore();
		nr = lesInt("Sonenummer", 1, MAX_SONER);
		gSoner.nyttOppdrag(nr);
		gSoner.skrivTilFil();
		break;
	case '1':
		nr = lesInt("Oppdragsnummer", 1, MAX_OPPDRAG);
		gSoner.skrivOppdrag(nr);
		break;
	case 'S':
		cin >> nr;
		gSoner.slettOppdrag(nr);
		gSoner.skrivTilFil();
		break;
	default:
		cout << "Oppdrag Default" << endl;
	}
}

/**
*  Denne funksjonen validerer og registrerer en e-postaddr
*
*  @param -   epost   medsent variabel som skal fa data oppdatert
**/
void lesEpostAdr(std::string& epost) {
	int i;
	bool valider;

	do {
		valider = true;
		cout << "\nMailaddresse: ";
		cin.ignore();
		cin >> epost;
		
		//Sjekker om epostaddessen inneholder @
		if (epost.find("@") == string::npos)
			valider = false;
			
		//Sjekker at epost addresse inneholder minst et punktum
		if (epost.find(".") == string::npos)
			valider = false;
			

		//Sjekker teksten og sa lenge den kun inneholder bokstaver, tall - @ .
		for (i = 0; i < epost.size(); i++) 
		{
			if (!(isalpha(epost[i]) || isdigit(epost[i]) || epost[i] == '-' || epost[i] == '@' || epost[i] == '.'))
				valider = false;		
		}

		if (!valider)
		{
			cout << "\nUgyldig mailadresse!\n";
		}
	} while (valider == false);
}

/**
*  Denne funksjonen validerer og registrerer et gateaddresse
*
*  Gateaddresse inneholder forst en bokstav derretter ' ' ; - og tall.
*
* @param    gta -   Medsendt gateaddressevariabel
**/
void lesGateAdr(std::string & gta){
   int i; //Lokketeller
    bool valider; //Brukes til a sjekke innlest navn

    do
	{
        valider = false; //settes til false for a kontrollere lokken
        cout <<"\nGateaddresse: ";
        getline(cin,gta);

        //Sjekker at forste tegn inneholder en bokstav
        if (isalpha(gta[0]))
		{
            for (i = 1; i < gta.size(); i++)
			{
                //Sa lenge string inneholder bokstaver, mellomrom, tall og -
				if ((isalpha(gta[i]) || gta[i] == ' ' || isdigit(gta[i]) || gta[i] == '-'))
					valider = true;
            }
        } 

		if (!valider)
			cout << "\nUgyldig gateadresse!\n";
    }
	while(valider == false);
}

/**
*Denne funksjonen validerer og registrerer en post addresse
*
*  Forutsettning 3 eller 4 første er tall, etterfulgt med et mellomrom og deretter tekst med . ' ' - eller bokstaver.
*
*@param pad -  medsendt variabel for oppdatering av postaddresse
**/
void lesPostAdr(std::string & pad){
    int i; //Lokketeller
    bool valider; //Brukes til sjekk av tekst

    do{
        valider = true;
        cout <<"\nPostadresse: ";
        getline(cin,pad);

        //Kontrolerer at de 3 forste er tall
        for (i=0; i<=2; i++)
		{
            if(!isdigit(pad[i]))
                valider = false;
        }

		if (!(pad[3] == ' ' || (isdigit(pad[3]) && pad[4] == ' ')))
			valider = false;
		
		//Sjekker deretter at 4 tegn er tall eller mellomrom
        /*if(!(isdigit(pad[3]) || pad[3]==' '))
            valider = false;

        //Hvis det ikke er et mellomrom fra 4 tall og tekst sa skal det forkastes
        if(valider == true && (isdigit(pad[3]) && pad[4] !=' '))
            valider = false;
		*/
        //Sjekker resten av tekstem kan inneholde bokstaver mellomrom - .
        for(i=5; i <pad.size(); i++) {
            if(!(isalpha(pad[i])|| pad[i]==' ' || pad[i]== '.' || pad[i]=='-')) 
                valider = false;
        }
        if(!valider)
			cout << "\nUgyldig postadresse!\n";
    }while(valider == false);
}

/**
*Denne funksjonen validerer og registrerer av et navn med mellomrom og alfabetiske tegn.
*
*param  @nvn    -   navn
**/
void skrivNavn(string & nvn){
    int i; //Lokketeller
    bool valider =true; //Brukes til a sjekke innlest navn

    do{
        valider = true; //settes til true for a kontrollere lokken
        cout <<"\nNavn: ";
        getline(cin,nvn);
            for (i = 0; i < nvn.size();i++){
                //Sa lenge string inneholder bokstaver eller mellomrom
                if(valider == true && (isalpha(nvn[i]) || nvn[i]==' ')){
                    valider =true;
                }
            else {
                valider = false;
            }
        }
        if(!valider){
            cout <<"\nUgyldig navnformat, Kan kun besta av bokstaver og mellomrom!";
        }

    }while(valider ==false);
}

/**
* Utskrift av meny for hoved meny, med andre ord switch i main funksjonen
**/
void hovedMeny() {
	cout << setw(35) << "Kommandoer tilgjengelig:" << endl;
	cout << setw(5) << "(K)" << setw(30) << "for Kunde funksjoner" << endl;
	cout << setw(5) << "(S)" << setw(30) << "for Sone funksjoner" << endl;
	cout << setw(5) << "(O)" << setw(30) << "for Oppdrag/Bolig funksjoner" << endl;
	cout << endl;

}

/**
* Utskrift av meny for kunde funksjoner, kommer etter input "K" fra hovedMeny
**/
void kundeMeny() {
	cout << setw(35) << "Kommandoer tilgjengelig:" << endl;
	cout << setw(5) << "(N)" << setw(30) << "Lage ny Kunde" << endl;
	cout << setw(5) << "(1)" << setw(30) << "Skriv info om en kunde" << endl;
	cout << setw(5) << "(A)" << setw(30) << "Skriv info om alle kunder" << endl;
	cout << setw(5) << "(E)" << setw(30) << "Endre info om kunde" << endl;
	cout << setw(5) << "(S)" << setw(30) << "Slett kunde" << endl;
	cout << setw(5) << "(O)" << setw(30) << "Skriver all bolig data" << endl;
	cout << endl;

}

/**
* Utskrift av meny for Sone funksjoner, kommer etter input "S" fra hovedMeny
**/
void soneMeny() {
	cout << setw(35) << "Kommandoer tilgjengelig:" << endl;
	cout << setw(5) << "(N)" << setw(30) << "Lage ny Sone" << endl;
	cout << setw(5) << "(1)" << setw(30) << "Skriv ut alt om alle oppdrag" << endl;
	cout << setw(5) << "(A)" << setw(30) << "Hoveddata om alle soner" << endl;
	cout << endl;

}

void oppdragMeny() {
	cout << setw(35) << "Kommandoer tilgjengelig:" << endl;
	cout << setw(5) << "(N)" << setw(30) << "Lage ny Oppdrag" << endl;
	cout << setw(5) << "(1)" << setw(30) << "Skriv ut alt om alle oppdrag?? eller bare om et oppdrag" << endl;			///////////////Skal det skrives ut om en eller alle oppdrag??????????
	cout << setw(5) << "(S)" << setw(30) << "Slett oppdrag" << endl;
	cout << endl;

}