//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LireFichier.h"
#include "LesVecteurs.hse"

#include "TendanceEnum.h"
#include "TVPrixChoix.h"

#include "GereRendement.h"

#include "Rendement.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//-----------------------------------------------------------------------------
void __fastcall TRendementFrm::IniGrille0(void)
{
	int l=0;
//              0  1  2   3  4  5  6  7  8  9  0  1  2  3  4  5
	int largeur[] = {20,10,96,96,48,48,48,48,48,48,48,48,48,48,48,48};
	LaGrille->ColCount=15;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;

	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;
	LaGrille->Cells[3][0]="Atelier";
	LaGrille->Cells[4][0]="Base";

}
