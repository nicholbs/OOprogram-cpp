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
void kundeOversiktTilFil(int kundeNr)
{
	if (!gKunder.kundeListeTomSjekk())
	{
		vector <int> kundeSoneInteresse;	//Holder alle kundens interessesoner
		vector<Bolig*> boligVector;			//Holder alle boligene i en interessesone

		kundeSoneInteresse = gKunder.finnKundeSone(kundeNr);
		if (!kundeSoneInteresse.empty())
		{
			string filnavn = "K" + to_string(kundeNr) + ".DTA";		//Oppretter filnavn
			ofstream ut(filnavn);

			//Skriver all boligdata for alle boliger i sonen på leselig format
			for (int i = 0; i < kundeSoneInteresse.size(); i++)
				gSoner.skrivAlleOppdragISoneTilFil(kundeSoneInteresse[i], ut);	//BURDE BYTTES UT?

			cout << "\n Oversikt for Kunde " << kundeNr << " skrevet til \"" << filnavn << "\".\n";
		}
		else cout << setw(35) << "\n Kunden har ingen registrerte interessesoner.\n";
	}
	else cout << setw(35) << "\n Det finnes ingen kunder i systemet\n";
}

/**
*  Tar brukerinput som string, sjekker at det er et tall og innen et visst intervall, og returner som int.
*
*  Brukes i stedet for lesInt(..) for kommandovalg i main så brukeren skal kunne skrive inn hele kommandoen
*  (e.g. K 1 [kundenummer]) uten å få opp "Kundenummer (min-max): " etterpå.
*
*  @param min   -	minste aksepterte tall
*  @param max	-	høyeste aksepterte tall
*  @return val	-	stringen skrevet inn gjort om til en int    
**/
int lesIntX(int min, int max)
{
	string buffer;
	int val;
	cin.ignore();
	getline(cin, buffer);

	for (int i = 0; i < buffer.size(); i++)
	{
		if (!isdigit(buffer[i]))
		{
			cout << "\nInput matte vare en int\n";
			return 0;
		}
	}
	
	val = stoi(buffer);

	if (val < min || val > max)
	{
		cout << "\nTallet ma vare i intervallet [" << min << "-" << max << "]\n";
		return 0;
	}
	
	return val;
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
	int nr;

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
		nr = lesIntX(1, MAX_PERSONER);
		if(nr != 0)
			kundeOversiktTilFil(nr);
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
		snr = lesIntX(1, MAX_SONER);
		if (snr != 0)
		{
			gSoner.nySone(snr);
			gSoner.skrivTilFil();
		}
		break;
	case '1':
		snr = lesIntX(1, MAX_SONER);
		if (snr != 0)
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
		nr = lesIntX(1, MAX_SONER);
		if (nr != 0)
		{
			gSoner.nyttOppdrag(nr);
			gSoner.skrivTilFil();
		}
		break;
	case '1':
		nr = lesIntX(1, MAX_OPPDRAG);
		if(nr != 0)
			gSoner.skrivOppdrag(nr);
		break;
	case 'S':
		nr = lesIntX(1, MAX_OPPDRAG);
		if (nr != 0)
		{
			gSoner.slettOppdrag(nr);
			gSoner.skrivTilFil();
		}
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
		cout << "Mailaddresse: ";
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
			cout << "\nUgyldig mailadresse!\n"
				 << "Mail maa inneholde en \'@\' og et \'.\'; samt ikke inneholde noen spesielle tegn utenom \'-\'.\n";
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
        valider = true; //settes til false for a kontrollere lokken
        cout <<"Gateaddresse: ";
        getline(cin,gta);

        //Sjekker at forste tegn inneholder en bokstav
		if (!isalpha(gta[0]))
			valider = false;

		//Sa lenge string inneholder bokstaver, mellomrom, tall og -
		for (i = 1; i < gta.size(); i++)
		{
			if (!(isalpha(gta[i]) || gta[i] == ' ' || isdigit(gta[i]) || gta[i] == '-'))
				valider = false;
		}

		//Siste tegn må være et tall
		if (!isdigit(gta[gta.size() - 1]))
			valider = false;

		if (!valider)
		{
			cout << "\nUgyldig gateadresse!\n"
				<< "Gateadresse kan bare inneholde alfabetiske tegn, \'-\', mellomrom, og tall.\n";
		}	
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
        cout <<"Postadresse: ";
        getline(cin,pad);

        //Kontrolerer at de 3 forste er tall
        for (i=0; i < 3; i++)
		{
            if(!isdigit(pad[i]))
                valider = false;
        }

		//Sjekker at tegn 4 er enten et mellomrom eller ett tall etterfulgt av et mellomrom
		if (!(pad[3] == ' ' || (isdigit(pad[3]) && pad[4] == ' ')))
			valider = false;
		
        //Sjekker resten av teksten kan inneholde bokstaver, mellomrom, bindestrek 
        for(i=5; i < pad.size(); i++) 
		{
            if(!(isalpha(pad[i])|| pad[i]==' ' || pad[i]=='-')) 
                valider = false;
        }

		if (!valider)
			cout << "\nUgyldig postadresse!\n"
				 << "Postadressen maa ha enten 3 eller 4 sifre, etterfulgt av alfabetiske tegn, mellomrom, og \'-\'.\n";
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

/**
* Utskrift av meny for Oppdrag funksjoner, kommer etter input "O" fra hovedMeny
**/
void oppdragMeny() {
	cout << setw(35) << "Kommandoer tilgjengelig:" << endl;
	cout << setw(5) << "(N)" << setw(30) << "Lage ny Oppdrag" << endl;
	cout << setw(5) << "(1)" << setw(30) << "Skriv ut alt om alle oppdrag?? eller bare om et oppdrag" << endl;			///////////////Skal det skrives ut om en eller alle oppdrag??????????
	cout << setw(5) << "(S)" << setw(30) << "Slett oppdrag" << endl;
	cout << endl;

}