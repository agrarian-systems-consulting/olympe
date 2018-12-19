//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <vcl.h>
#include <grids.hpp>
#include <winbase.h>
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
#include "TVDico.h"

#include "AppelFct.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TAppelFctFrm *AppelFctFrm;
//---------------------------------------------------------------------------
__fastcall TAppelFctFrm::TAppelFctFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TAppelFctFrm::BtBnDicoClick(TObject *Sender)
{
	TVDicoFrm->Show();
}

//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// METHODES A CREER
//-----------------------------------------------------------------------------
void __fastcall TAppelFctFrm::Personnaliser(void)
{
	Grille0->Options>>goAlwaysShowEditor;
	Grille0->Options>>goEditing;
	Grille0->EditorMode=false;
	Grille0->Options<<goDrawFocusSelected;

}
//---------------------------------------------------------------------------
//-------------------------------------------------------------------------
void __fastcall TAppelFctFrm::DefinirLesGrilles(void)
{
	GrilleX=1;
	Grille0->Tag=0;
	LesGrilles[0]=Grille0;
	LaGrille=Grille0;
	LaGrille->ColCount=13;
	LaGrille->RowCount=4;
}
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void __fastcall TAppelFctFrm::IniGrille(TStringGrid *grille)
{
	int l=0;
	int largeur[] = {128,128,128,64,64,64,64,64,64,64,64,64,64,64,64};
//int largeur[] ={20,10,128,128,64,64,64,64,64,64,64,64,64,64};

	strcpy(TypeCol, "0000NNNNNNNNNNNNNNN");
	LaGrille->ColCount=13;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=0;

	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

//	TailleGrille();

	AffAn(3);
}
//---------------------------------------------------------------------------
void __fastcall TAppelFctFrm::AffAn(int col0)
{
	int i;
	int col;
	LaGrille->Cells[0][0]="Agriculteur";
	LaGrille->Cells[1][0]="Catégorie";
	LaGrille->Cells[2][0]="Nom";
//    if(col0==4)
//		LaGrille->Cells[3][0]="Catégorie";

	for(i=0,col=col0;i<10;i++,col++)
	LaGrille->Cells[col][0]="  "+AnsiString(AgriEnCours->DefSim->An_0+i);

}

//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void __fastcall TAppelFctFrm::VersGrille(TStringGrid *grille)
{
}
//-----------------------------------------------------------------------------
void __fastcall TAppelFctFrm::BtBnALancerClick(TObject *Sender)
{
	bool rep;
	AnsiString as,asExe,ligneCommande;

	STARTUPINFO siStartupInfo;
	PROCESS_INFORMATION piProcessInfo;
	memset(&siStartupInfo, 0, sizeof(siStartupInfo));
	memset(&piProcessInfo, 0, sizeof(piProcessInfo));
	siStartupInfo.cb = sizeof(siStartupInfo);

//  à remettre
	rep=OpenDialog->Execute();
	if(rep==false) return;

	asExe=OpenDialog->FileName;
//    ShowMessage(asExe);

//    asExe="c:\\Program Files\\Microsoft Office\\office10\\excel.exe";
	ligneCommande="c:\\olympeMaJour\\vendredi15.csv";
	ShowMessage(" Je vais lancer  "+asExe);

	rep=CreateProcess(
			asExe.c_str(),
			ligneCommande.c_str(),
			0,
			0,
			false,
			DETACHED_PROCESS,
			0,
			0,
			&siStartupInfo,
			&piProcessInfo);

	if(rep==false) ShowMessage("problème!!");

	WaitForSingleObject(piProcessInfo.hProcess,INFINITE);
	::CloseHandle(piProcessInfo.hThread);
	::CloseHandle(piProcessInfo.hProcess);

	ShowMessage("Je suis revenu");
}
//---------------------------------------------------------------------------
/*
 STARTUPINFO         siStartupInfo;
 PROCESS_INFORMATION piProcessInfo;

 memset(&siStartupInfo, 0, sizeof(siStartupInfo));
 memset(&piProcessInfo, 0, sizeof(piProcessInfo));
 siStartupInfo.cb = sizeof(siStartupInfo);
 if(CreateProcess("c:\\windows\\notepad.exe",
 "c:\\mydir\\toto.txt",0,0,FALSE,
 CREATE_DEFAULT_ERROR_MODE,0,0,
 &siStartupInfo,&piProcessInfo) == FALSE)
 {
 // erreur
 }
 else
 {
 // attente
 WaitForSingleObject(piProcessInfo.hProcess, INFINITE);

 ::CloseHandle(piProcessInfo.hThread);
 ::CloseHandle(piProcessInfo.hProcess);
 }
 */
//---------------------------------------------------------------------------
void __fastcall TAppelFctFrm::EdExecutableClick(TObject *Sender)
{
	bool rep;
	AnsiString as,asExe,ligneCommande;

	STARTUPINFO siStartupInfo;
	PROCESS_INFORMATION piProcessInfo;
	memset(&siStartupInfo, 0, sizeof(siStartupInfo));
	memset(&piProcessInfo, 0, sizeof(piProcessInfo));
	siStartupInfo.cb = sizeof(siStartupInfo);

//  à remettre
	rep=OpenDialog->Execute();
	if(rep==false) return;

	asExe=OpenDialog->FileName;
//    ShowMessage(asExe);

//    asExe="c:\\Program Files\\Microsoft Office\\office10\\excel.exe";
	ligneCommande="c:\\olympeMaJour\\vendredi15.csv";
	ShowMessage(" Je vais lancer  "+asExe);

	rep=CreateProcess(
			asExe.c_str(),
			ligneCommande.c_str(),
			0,
			0,
			false,
			DETACHED_PROCESS,
			0,
			0,
			&siStartupInfo,
			&piProcessInfo);

	if(rep==false) ShowMessage("problème!!");

	WaitForSingleObject(piProcessInfo.hProcess,INFINITE);
	::CloseHandle(piProcessInfo.hThread);
	::CloseHandle(piProcessInfo.hProcess);

	ShowMessage("Je suis revenu");

}
//---------------------------------------------------------------------------
void __fastcall TAppelFctFrm::EdLigneCommandeClick(TObject *Sender)
{
	bool rep;
	AnsiString as,asExe,ligneCommande;

	STARTUPINFO siStartupInfo;
	PROCESS_INFORMATION piProcessInfo;
	memset(&siStartupInfo, 0, sizeof(siStartupInfo));
	memset(&piProcessInfo, 0, sizeof(piProcessInfo));
	siStartupInfo.cb = sizeof(siStartupInfo);

//  à remettre
	rep=OpenDialog->Execute();
	if(rep==false) return;

	asExe=OpenDialog->FileName;
//    ShowMessage(asExe);

//    asExe="c:\\Program Files\\Microsoft Office\\office10\\excel.exe";
	ligneCommande="c:\\olympeMaJour\\vendredi15.csv";
	ShowMessage(" Je vais lancer  "+asExe);

	rep=CreateProcess(
			asExe.c_str(),
			ligneCommande.c_str(),
			0,
			0,
			false,
			DETACHED_PROCESS,
			0,
			0,
			&siStartupInfo,
			&piProcessInfo);

	if(rep==false) ShowMessage("problème!!");

	WaitForSingleObject(piProcessInfo.hProcess,INFINITE);
	::CloseHandle(piProcessInfo.hThread);
	::CloseHandle(piProcessInfo.hProcess);

	ShowMessage("Je suis revenu");

}
//---------------------------------------------------------------------------

