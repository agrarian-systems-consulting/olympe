//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "AgriSaisie.h"
#include "CL_Trad.h"
#include "SysUnite.h"
#include "Tva.h"
#include "GereAgri.h"
#include "DefZone.h"
#include "Ensemble.h"
#include "AleaPrix.h"
#include "Main.h"
#include "Indicateur.h"
#include "DefEtatSortie.h"
#include "Espece.h"

#include "NoteAgri.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TNoteAgriFrm *NoteAgriFrm;
extern CL_ES *ES;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TNoteAgriFrm::TNoteAgriFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TNoteAgriFrm::FormActivate(TObject *Sender)
{
	Modif=false;
//    Memo->Text=Agri->Notes;
//    Memo->Text=AgriEnCours->Notes;   //remis 251006 retiré 300407
//    Memo->Text=Notes;

}
//---------------------------------------------------------------------------
void __fastcall TNoteAgriFrm::MemoChange(TObject *Sender)
{
	Modif=true;
}
//---------------------------------------------------------------------------
void __fastcall TNoteAgriFrm::BtBnAnnuleClick(TObject *Sender)
{
	Modif=false;
}
//---------------------------------------------------------------------------
void __fastcall TNoteAgriFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	if(Modif==false)return;

	if (VientDe=="AgriDefSim") Agri->Notes=Memo->Text;
//    else if(VientDe=="GereAgri")            AgriEnCours->Notes=Memo->Text;  //251006
	else if(VientDe=="Main") MainForm->Notes=Memo->Text;
	else if(VientDe=="Atelier") Atelier->Notes=Memo->Text;
	else if(VientDe=="DefItem") Categorie->Notes=Memo->Text;
	else if(VientDe=="DefProduit") Categorie->Notes=Memo->Text;
	else if(VientDe=="DefVariable") Categorie->Notes=Memo->Text;
	else if(VientDe=="DefChStruct") Categorie->Notes=Memo->Text;
	else if(VientDe=="DefBestiaux") Categorie->Notes=Memo->Text;
	else if(VientDe=="DefCalendrier") Calendrier->Notes=Memo->Text;
	else if(VientDe=="SysUnite") SysUniteFrm->Notes=Memo->Text;
	else if(VientDe=="Tva") TvaFrm->Notes=Memo->Text;
	else if(VientDe=="GereAgri") GereAgriFrm->Notes=Memo->Text;
	else if(VientDe=="DefZone") Categorie->Notes=Memo->Text;
	else if(VientDe=="Ensemble") Ensemble->Notes=Memo->Text;
	else if(VientDe=="AleaPrix") Tendance->Notes=Memo->Text;
	else if(VientDe=="AleaRdt") Tendance->Notes=Memo->Text;
	else if(VientDe=="Indicateur") Indicateur->Notes=Memo->Text;
	else if(VientDe=="DefEtatSortie") EtatSortie->Notes=Memo->Text;
	else if(VientDe=="Espece") EspeceFrm->Notes=Memo->Text;

	else
	{
		ShowMessage(" Oubli NoteAgriFrm  VientDe ????");
		return;
	}
	ES->ecrireFichier();
}
//---------------------------------------------------------------------------
void __fastcall TNoteAgriFrm::BtBnVideToutClick(TObject *Sender)
{
	int repMB;
	repMB=MessageBox(Handle,"j'efface tout ?","EFFACER TOUT",MB_YESNO|MB_ICONQUESTION);
	if(repMB==IDNO) return;
	Memo->Text="";
}
//---------------------------------------------------------------------------

void __fastcall TNoteAgriFrm::BtBnImpClick(TObject *Sender)
{
	TPrinter *imprimante=Printer();
	int i,h,l;
	AnsiString s;
	Printer()->Orientation = poPortrait;
	imprimante->Canvas->Font->Name="Courier";
	imprimante->Canvas->Font->Size=10; //20;//8;
//    imprimante->Canvas->Font->Pitch=fpFixed;
//    imprimante->Canvas->Font->PixelsPerInch=550;//600;//500;
	h=imprimante->Canvas->TextHeight("aaaa");
	imprimante->BeginDoc();
	l=h;
	for(i=0;i<Memo->Lines->Count;i++)
	{
		s=Memo->Lines->Strings[i];
		imprimante->Canvas->TextOut(1,l,s);
		l+=h;
	}
	imprimante->EndDoc();
}
//---------------------------------------------------------------------------
void TNoteAgriFrm::IniCaption(void) {
	NoteAgriFrm->Caption = T->LC_BtBnNotes;
	Panel1->Caption = LC_Panel1;
}
//--------------------------------------------
void TNoteAgriFrm::TexteCaption(void) {
	LC_BtBnNotes = T->TrouveCaption("CL_Trad", "LC_BtBnNotes");
	LC_Panel1 = T->TrouveCaption("NoteAgri", "LC_Panel1");

	IniCaption();

}
//--------------------------------------------

