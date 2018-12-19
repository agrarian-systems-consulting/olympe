//---------------------------------------------------------------------------

#pragma hdrstop
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"

#include "DefNom.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
void DefinirNoms(void) {
	TStringList *LstNom = new TStringList;
	TStringList *LstNomFinSom = new TStringList;

	LstNom->AddObject("LstNomFinSom", LstNomFinSom);

	LstNomFinSom->Add("Dette LT");
	LstNomFinSom->Add("Remb Capital LT");
	LstNomFinSom->Add("Interet LT");
	LstNomFinSom->Add("Nouveaux LT");

	LstNomFinSom->Add("Dette CT");
	LstNomFinSom->Add("Remb Capital CT");
	LstNomFinSom->Add("Interet CT");
	LstNomFinSom->Add("Nouveaux CT");

}

