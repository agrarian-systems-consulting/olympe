//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "olympe.hse"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"

#include "Forme00.h"
#include "Indicateur.h"
#include "DefEtatSortie.h"
#include "Resultat.h"
#include "Compilateur.h"
#include "LBCompAgri.h"
#include "AgriSaisieEnum.h"

#include "AgriSaisie.h"
#include "DefAction.h"

//#include "Graph.h"

#include "SorRapPrep.h"

#include "SorRap.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSorRapFrm *SorRapFrm;
//---------------------------------------------------------------------------
__fastcall TSorRapFrm::TSorRapFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TSorRapFrm::FormCreate(TObject *Sender)
{
	int r;
	SG->ColCount=2;
	SG->RowCount=20;

	SG->ColWidths[0]=32;
	SG->ColWidths[1]=64;

	SG->Cells[1][0]="Alias";

	for(r=0;r<SG->RowCount;r++)SG->Cells[0][r]=r;

}
//---------------------------------------------------------------------------
void __fastcall TSorRapFrm::FormActivate(TObject *Sender)
{
	int n;
	int r,c;
	int rMax=5;
	for(r=1;r<rMax;r++)
	{
		SG->Cells[1][r]=SorRapPrepFrm->SG->Cells[4][r];
	}
}
//---------------------------------------------------------------------------
