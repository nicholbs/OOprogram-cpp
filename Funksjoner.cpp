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
*Denne funksjonen validerer og registrerer en e-postaddr
*
*@param -   epost   medsent variabel som skal fa data oppdatert
**/
void lesEpostAdr(std::string & epost){
    int i;
    bool valider;


    do{
        valider =true;
        cout <<"\nE-post addresse: ";
        cin >>epost;
        cin.ignore();

        //Sjekker om epostaddessen inneholder @
        if (epost.find("@") !=string::npos){
            valider = true;
        }else valider = false;
        //Sjekker at epost addresse inneholder minst et punktum
         if (epost.find(".") !=string::npos){
            valider = true;
        } else valider = false;
        //Sjekker teksten og sa lenge den kun inneholder bokstaver, tall - @ .
        for(i= 0; i<epost.size(); i++){
            if(valider == true && (isalpha(epost[i]) ||isdigit(epost[i])
                        || epost[i] =='-' || epost[i]=='@' || epost[i]=='.')) {
                valider = true;
            }
            else {
                    valider = false;
            }
        }
        if(!valider){
            cout <<"\nIkke gyldig e-post addresse, Ma inneholde "
                 << "@ samt . og kan kun inneholde: "
                 <<"Bokstaver, tall, @ - . ";
        }
    }while(valider == false);
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
		nr = lesInt("Skriv hvilken sone det nye oppdraget skal ligge i",1, MAX_SONER);
		gSoner.nyttOppdrag(nr);
		break;
	case '1':
		nr = lesInt("Skriv inn nr på oppdrag du vil skrive ut", 1, MAX_OPPDRAG);
		gSoner.skrivOppdrag(nr);
		break;
	case 'A':		//TESTCASE - SKAL FJERNES
		gSoner.skrivAlleOppdrag();
		break;
	case 'S':
		cin >> nr;
		gSoner.slettOppdrag(nr);
		break;
	default:
		cout << "Oppdrag Default" << endl;
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
		break;
	case '1':
		////////////////////////skriv funksjon som skriver ut all info om valgt sone og stopper for input hver femte linje, henviser til kundeAllesklriv
		gSoner.skrivOppdrag(snr);
		break;
	case 'A':
		gSoner.skrivHovedDataAlleSoner();
		break;
	default:
		cout << "Sone Default" << endl;
	}
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
		skrivUtInteresseSoner();
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
*Denne funksjonen validerer og registrerer et gateaddresse
*
* @param    gta -   Medsendt gateaddressevariabel
**/
//Gateaddresse inneholder forst en bokstav derretter ' ' ; - og tall
void lesGateAdr(std::string & gta){
   int i; //Lokketeller
    bool valider =true; //Brukes til a sjekke innlest navn

    do{
        valider = true; //settes til true for a kontrollere lokken
        cout <<"\nGateaddresse: ";
        getline(cin,gta);
            //Sjekker at forste tegn inneholder en bokstav
            if (isalpha(gta[0])){
                for (i = 1; i < gta.size();i++){
                    //Sa lenge string inneholder bokstaver, mellomrom, tall og -
                    if(valider == true && (isalpha(gta[i]) || gta[i]==' '
                        || isdigit(gta[i])||gta[i]=='-')){
                        valider =true;
                    }
                    else {
                        valider = false;
                    }
                }
            } else valider=false;
    }while(valider ==false);
}

/**
*Denne funksjonen validerer og registrerer en post addresse
*
*@param pad -  medsendt variabel for oppdatering av postaddresse
**/
//forutsettning 3 eller 4 første er tall, etterfulgt med et mellomrom og deretter tekst med . ' ' - eller bokstaver
void lesPostAdr(std::string & pad){
    int i; //Lokketeller
    bool valider = true; //Brukes til sjekk av tekst

    do{
        valider = true;
        cout <<"\nSkriv inn postnr poststed: ";
        getline(cin,pad);
        //Kontrolerer at de 3 forste er tall
        for (i=0;i<=2;i++){
            if(isdigit(pad[i])){
                valider = true;
            } else valider=false;
        }
        //Sjekker deretter at 4 tegn er tall eller mellomrom
        if(valider == true && (isdigit(pad[3]) || pad[3]==' ')){
            valider = true;
        } else valider = false;

        //Hvis det ikke er et mellomrom fra 4 tall og tekst sa skal det forkastes
        if(valider == true && (isdigit(pad[3]) && pad[4] !=' ')) {
            valider = false;
        }
        //Sjekker resten av tekstem kan inneholde bokstaver mellomrom - .
        for(i=5; i <pad.size(); i++) {
            if(valider == true && (isalpha(pad[i])|| pad[i]==' ' || pad[i]== '.'
                            || pad[i]=='-')) {
                valider = true;
            } else valider = false;
        }
        if(!valider){
            cout <<"\nUgyldig sammensettning av postnr og poststed"
                 <<", Kan kun inneholde bokstaver, tall, mellomrom, punktum, bindestrek"
                 <<" og Ma skrives pa format:\n"
                 <<"tre tall mellomrom etterfulgt av bokstaver, punktum og bindestrek eller:\n"
                 <<"fire tall mellomrom etterfulgt av bokstaver, punktum og bindestrek";
        }
    }while(valider == false);

}
/**
*Denne funksjonen validerer og registrerer et navn
*
*param  @nvn    -   navn
**/
//Tilater mellomrom og alfa.
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
* Utskrift av meny for Oppdrag/Bolig funksjoner, kommer etter input "O" fra hovedMeny
**/

void oppdragMeny() {
	cout << setw(35) << "Kommandoer tilgjengelig:" << endl;
	cout << setw(5) << "(N)" << setw(30) << "Lage ny Oppdrag" << endl;
	cout << setw(5) << "(1)" << setw(30) << "Skriv ut alt om alle oppdrag?? eller bare om et oppdrag" << endl;			///////////////Skal det skrives ut om en eller alle oppdrag??????????
	cout << setw(5) << "(S)" << setw(30) << "Slett oppdrag" << endl;
	cout << endl;

}

void skrivUtInteresseSoner()
{
	int kundeNr;	//Variabel for å holde medsent int i kommando "K O <knr>"
	cin >> kundeNr;	//Innskriving av <knr> går til helvette om bruker taster bokstav og ikke tall
	cout << setw(35) << "Leter etter kunde med nr:" << ' ' << kundeNr << endl;


	if (!gKunder.kundeListeTomSjekk())
	{
		vector <int> kundeSoneInteresse;
		kundeSoneInteresse = gKunder.finnKundeSone(kundeNr);
		if (!kundeSoneInteresse.empty())
		{
			string navnPaFil = "K";
			string kunde = to_string(kundeNr);
			kunde.append(".DTA");
			string skrivTilFil = navnPaFil + kunde;
			ofstream utfilA(skrivTilFil);

			for (int i = 0; i < kundeSoneInteresse.size(); i++)        //Utskrift av vector sin data
			{
				vector<Bolig*> boligVector;
				boligVector = gSoner.finnBoligerISone(i);
				if (boligVector.empty())
				{
					cout << setw(35) << "Det er ikke blitt skrevet til fil" << endl;
				}
				else
				{
					for (int i = 0; i < boligVector.size(); i++)
					{
						cout << setw(35) << "Skriver Bolig:" << ' ' << boligVector[i]->getID() << endl;
						boligVector[i]->skrivKundeTilFil(utfilA, kundeSoneInteresse);
					}
				}
			}

		}
		else
		{
			cout << setw(35) << "Kunden fantes, men han har ikke registrert noen soner:" << endl;
		}
	}
	else
	{
		cout << setw(35) << "Det finnes ingen kunder i hele tatt" << endl;
	}
}
