//---------------------------------------------------------------------------

#include <vcl.h>

// CBuilder5 : pour pouvoir utiliser "OlePropertySet" (seb).
#include <utilcls.h>

#include <dir.h>
//#pragma hdrstop

#include "Olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "QuelExcelCSV.h"
#include "Forme0.h"
#include "Tableur.h"

//---------------------------------------------------------------------------
//#pragma resource "*.dfm"
#pragma package(smart_init)
extern CL_ES *ES;
extern CL_Excel *EX;
//---------------------------------------------------------------------------
// MODIF EXcelStart a voir

//---------------------------------------------------------------------------
CL_Excel::CL_Excel(void) {
}
;
CL_Excel::~CL_Excel() {
}
//------------------------------------------------------------------------------
void CL_Excel::EcritGrilleFichier(TStringGrid *grille, AnsiString TitreGrille) {
	int r, c;
	double val;
//char car;
	int colDeb;
	AnsiString s;
	char car;
	/// le fichier est ouvert par quelExcelCSV

	fprintf(fichier, "\n");
	fprintf(fichier, "\n");
	if (AgriEnCours)
		EcrireNomVC(AgriEnCours);

	if (TitreGrille.Length())
		fprintf(fichier, "%s\n", TitreGrille.c_str());
	/// si  les colonnes de gauche ne servent qu'a afficher numero et * pour supprimable
	/// ne pas les enoyer sur tableur
	if (grille->ColWidths[0] == 20 && grille->ColWidths[1] == 10)
		colDeb = 2;
	else
		colDeb = 0;
	// ligne du haut
	r = 0;
	for (c = colDeb; c < grille->ColCount; c++)
		fprintf(fichier, "%s;", grille->Cells[c][r].c_str());
	fprintf(fichier, "\n");

	for (r = 1; r < grille->RowCount; r++) {
		if (RowVide(grille, r) == true)
			continue;
		for (c = colDeb; c < grille->ColCount; c++) {
			s = grille->Cells[c][r];
			s.Trim();
			if (s == "") {
				fprintf(fichier, "  ;");
				continue;
			} //030103
			car = s[1];
			if (car >= '1' && car <= '9') //retire les thousand separator etc..
					{
				val = Forme0Frm->ValeurDe(s);
				s = val;
			}
			fprintf(fichier, "%s;", s);
		}
		fprintf(fichier, "\n");
	}
	fprintf(fichier, "\n");
//    fclose(fichier);
}
//------------------------------------------------------------------------------
void CL_Excel::FermerFichier(void) {
	fclose(fichier);
}
//----------------------------------------------------------------------------
bool CL_Excel::RowVide(TStringGrid *grille, int row) {
	AnsiString s;
	for (int c = 1; c < grille->ColCount; c++) // en 0 c'est num° de ligne
			{
		s = grille->Cells[c][row].Trim();
		if (s.IsEmpty() == false)
			return false;
//    	if(LaGrille->Cells[c][row].IsEmpty()==false) return false;
	}
	return true;
}
//--------------------------------------------------------------------------
void CL_Excel::EnTeteDate(void) {
	AnsiString date;
	TDateTime time;
	fprintf(fichier, "\n");
	fprintf(fichier, "\n");
	fprintf(fichier, "\n");
	time = TDateTime::CurrentDateTime();
	date = time.DateTimeString();
	fprintf(fichier, "%s;\n", date.c_str());
	fprintf(fichier, "\n");
}
//--------------------------------------------------------------------------
void CL_Excel::Titre(int col, char *titre) {
	CelluleVide(0, col);
	fprintf(fichier, "%s;\n", titre);
}
//--------------------------------------------------------------------------
void CL_Excel::CelluleVide(int colDeb, int colFin) {
	int c;
	for (c = colDeb; c < colFin; c++)
		fprintf(fichier, "   ;");
}
//--------------------------------------------------------------------------
bool CL_Excel::EstVide(float *valeur) //160905
		{
	int n;
	for (n = 0; n > N_X; n++)
		if (valeur[n] != 0.)
			return false;
	return true;
}

