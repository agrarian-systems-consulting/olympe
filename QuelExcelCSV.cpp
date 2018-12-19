//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "Tableur.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "QuelExcelCSV.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TQuelExcelCSVFrm *QuelExcelCSVFrm;

extern CL_ES *ES;
extern CL_Excel *EX;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TQuelExcelCSVFrm::TQuelExcelCSVFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TQuelExcelCSVFrm::FormActivate(TObject *Sender)
{
	EdNomExcel->Text =ES->FExcel;
	ODExcel->FileName=ES->FExcel;
	/// (ac) au cas où l'utilisateur annulerait*/
	//Renonce = false;  //100512
	Renonce = true;
}
//---------------------------------------------------------------------------
void __fastcall TQuelExcelCSVFrm::BtBnParcourirClick(TObject *Sender)
{
	bool rep;
	rep=ODExcel->Execute();
	if(rep==true)
	{
		ES->FExcel=ODExcel->FileName;
		EdNomExcel->Text =ES->FExcel;
	}
}
//---------------------------------------------------------------------------
void __fastcall TQuelExcelCSVFrm::BtBnAnnulerClick(TObject *Sender)
{
	Renonce=true;
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TQuelExcelCSVFrm::BtBnOKClick(TObject *Sender)
{
	bool res;
	/// ecrire en fin de fichier ou ecraser
	switch(QuelExcelCSVFrm->RG->ItemIndex)
	{
		case 0:
		EX->fichier=fopen(ES->FExcel.c_str(),"a+b");
		break;
		case 1:
		EX->fichier=fopen(ES->FExcel.c_str(),"w");
		break;
		case 2:
//        	ShowMessage("A faire");
		res=ODExcel->Execute();
		if(res==false)
		ShowMessage("Pas de choix");
		else
		{
			ES->FExcel=ODExcel->FileName;
			EX->fichier=fopen(ES->FExcel.c_str(),"w");
		}
		break;
	}
	/*
	 /// ecrire en fin de fichier ou ecraser
	 if(QuelExcelCSVFrm->RG->ItemIndex==0)
	 EX->fichier=fopen(ES->FExcel.c_str(),"a+b");
	 else
	 EX->fichier=fopen(ES->FExcel.c_str(),"w");
	 */
	if(EX->fichier==NULL)
	{
		MessageBox(Handle,"Impossible d'ouvrir le fichier Excel doit être ouvert!","PROBLEME",MB_OK|MB_ICONSTOP);
		Renonce=true;
		return;
	}
	Renonce=false;
	Close();
}
//---------------------------------------------------------------------------
//--------------------------------------------
void TQuelExcelCSVFrm::IniCaption(void) {
	RG->Caption = LC_RG;
	QuelExcelCSVFrm->Caption = LC_QuelExcelCSVFrm;
	BtBnParcourir->Caption = LC_BtBnParcourir;
	RG->Items->Strings[0] = LC_ALaSuite;
	RG->Items->Strings[1] = LC_Maz;
	RG->Items->Strings[2] = LC_AutreF;
	RG->Caption = LC_AEcrire;
}
//--------------------------------------------
//--------------------------------------------
void TQuelExcelCSVFrm::TexteCaption(void) {
	LC_RG = T->TrouveCaption("QuelExcelCSV", "LC_RG");
	LC_QuelExcelCSVFrm = T->TrouveCaption("QuelExcelCSV", "LC_QuelExcelCSVFrm");
	LC_BtBnParcourir = T->TrouveCaption("QuelExcelCSV", "LC_BtBnParcourir");
	LC_ALaSuite = T->TrouveCaption("QuelExcelCSV", "LC_ALaSuite");
	LC_Maz = T->TrouveCaption("QuelExcelCSV", "LC_Maz");
	LC_AutreF = T->TrouveCaption("QuelExcelCSV", "LC_AutreF");
	LC_AEcrire = T->TrouveCaption("QuelExcelCSV", "LC_AEcrire");

	IniCaption();
}

bool __fastcall TQuelExcelCSVFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=1470;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

void __fastcall TQuelExcelCSVFrm::BtBnAideClick(TObject *Sender)
{
	HelpContext=1470;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

