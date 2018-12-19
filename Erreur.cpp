//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <stdarg.h>
#pragma hdrstop
#include "CL_Trad.h"
#include "Forme00.h"

#include "Erreur.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TErreurFrm *ErreurFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TErreurFrm::TErreurFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TErreurFrm::FormActivate(TObject *Sender)
{
	Edit->Width=ClientWidth;
	Edit->Height=ClientHeight-Panel1->Height;
}
//---------------------------------------------------------------------------

//-------------------------------------------------------------------------
/*
 void __fastcall TErreurFrm::MonPrintf(char *format, ...)
 {
 va_list args;
 char work[256];
 va_start (args,format);
 vsprintf(work,format,args);
 va_end (args);
 if (!ErreurFrm->Visible)
 {
 ErreurFrm->Edit->Clear();
 ErreurFrm->Visible = true;
 ErreurFrm->BringToFront();
 }
 ErreurFrm->Edit->Lines->Add(work);
 }
 */

//---------------------------------------------------------------------------
void __fastcall TErreurFrm::BtImprimerClick(TObject *Sender)
{
	Edit->Print(Caption);
}
//---------------------------------------------------------------------------

void __fastcall TErreurFrm::FormClose(TObject *Sender,
		TCloseAction &Action)
{
//    ErreurFrm->Visible
	ErreurFrm->Caption=T->L_Erreur;
	Forme00Frm->AutreDonnee=false;

//ErreurFrm->Caption="Erreurs";
}
//---------------------------------------------------------------------------
void TErreurFrm::IniCaption(void) {
	ErreurFrm->Caption = T->LC_ErreurFrm;
	BtBnFermer->Caption = T->LC_BtBnFermer;
	BtImprimer->Caption = LC_BtImprimer;
}
//--------------------------------------------
void TErreurFrm::TexteCaption(void) {
	LC_ErreurFrm = T->TrouveCaption("CL_Trad", "LC_ErreurFrm");
	LC_BtBnFermer = T->TrouveCaption("CL_Trad", "LC_BtBnFermer");
	LC_BtImprimer = T->TrouveCaption("Erreur", "LC_BtImprimer");

	IniCaption();

}
//--------------------------------------------

