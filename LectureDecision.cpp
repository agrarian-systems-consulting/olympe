//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LectureDecision.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLectureDecisionFrm *LectureDecisionFrm;
//---------------------------------------------------------------------------
__fastcall TLectureDecisionFrm::TLectureDecisionFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TLectureDecisionFrm::BtBnFichierDecisionClick(
		TObject *Sender)
{
	AnsiString asFichier;
	OpenDialog1->InitialDir ="E:";
	if ( !OpenDialog1->Execute() )
	return;

	asFichier =OpenDialog1->FileName;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TLectureDecisionFrm::Lecture(void) {
	int i;
	CL_Agriculteur *agri;
	AnsiString as;
	Erreur = false;
	//les FichCSVs à lire
	for (i = 0; i < V_Agriculteur->Nbelt; i++) {
		agri = V_Agriculteur->Vecteur[i];
		LireFichierCsv(agri);

	}
}
//---------------------------------------------------------------------------
void TLectureDecisionFrm::LireFichierCsv(CL_Agriculteur *agri) {
	AnsiString asNomFich;

	char chaine[201];
	char *p;
	asNomFich = agri->Nom + ".csv";
	FichCSV = fopen(asNomFich.c_str(), "r");
	if (FichCSV == NULL) {
		Erreur = true;
		RE->Lines->Add(AnsiString("Impossible d'ouvrir  ") + asNomFich);
		return;
	}
	while (1) {
		p = fgets(chaine, 200, FichCSV);
		if (p == NULL)
			break;

		p = strtok(chaine, ";");
		if (strcmp(p, "Agriculteur") == 0)
			VerifNomAgri(p, agri);
		else if (strcmp(p, "CULTURES") == 0)
			LireCultures(agri);
	}
}
//---------------------------------------------------------------------------
void TLectureDecisionFrm::VerifNomAgri(char *chaine, CL_Agriculteur *agri) {
}
//---------------------------------------------------------------------------
void TLectureDecisionFrm::LireCultures(CL_Agriculteur *agri) {
	char chaine[201];
	char *p;
	//sauter NOM;Catégorie;2005;...
	p = fgets(chaine, 200, FichCSV);

	while (1) {
		p = fgets(chaine, 200, FichCSV);
		if (p == NULL)
			return;

		p = strtok(chaine, ";");
		while (p) {
			p = strtok(NULL, ";");
		}
	}
}

