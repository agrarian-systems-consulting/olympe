//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "CL_Trad.h"
#include "Aide.h"

#include "LBChoixBestiaux.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LBChoix"
#pragma resource "*.dfm"
TLBChoixBestiauxFrm *LBChoixBestiauxFrm;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TLBChoixBestiauxFrm::TLBChoixBestiauxFrm(TComponent* Owner) :
		TLBChoixFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TLBChoixBestiauxFrm::FormActivate(TObject *Sender)
{
	int i;
	CL_Categorie *cat;
	Agri=TroupeauFrm->Agri;
	LB->Clear();
	for(i=0;i<V_CatBestiaux->Nbelt;i++)
	{
		cat=V_CatBestiaux->Vecteur[i];
		LB->Items->AddObject(cat->Nom,(TObject*)cat);
	}
	LB->Items->AddObject("[...]",NULL);
}
//---------------------------------------------------------------------------
void __fastcall TLBChoixBestiauxFrm::LBClick(TObject *Sender)
{
	int n;
	int rep;
	AnsiString s;
	CL_Categorie *cat;
	CL_Troupeau *troupeau;
	bool doublon;
	n=LB->ItemIndex;
	s=LB->Items->Strings[n];
	if(s=="[...]")
	{
		ShowMessage("NouvelleDefinition a faire");
	}
	cat=(CL_Categorie*)LB->Items->Objects[n];
	//éviter double définition
	doublon=false;
	for(n=0;n<Agri->LstTroupeaux->Count;n++)
	{
		troupeau=(CL_Troupeau*)Agri->LstTroupeaux->Items[n];
		if(troupeau->CatBestiaux==cat)
		{
			ShowMessage("Déjà présent");
			doublon=true;
		}
	}
	if(doublon==true) return;

//    TroupeauFrm->TroupeauEnCours=new CL_Troupeau(cat);
	rep=MessageBox(Handle,"A introduire ?","NOUVEAU TROUPEAU",
			MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDNO) return;

	n=TroupeauFrm->LBTroupeau->ItemIndex;
	Agri->TroupeauEnCours=new CL_Troupeau(cat);
	Agri->LstTroupeaux->Add(Agri->TroupeauEnCours);
	TroupeauFrm->TroupeauEnCours=Agri->TroupeauEnCours;
	TroupeauFrm->Debuter();
	Close();
}
//---------------------------------------------------------------------------

//--------------------------------------------
void TLBChoixBestiauxFrm::IniCaption(void) {
	LBChoixBestiauxFrm->Caption = T->LC_LBChoixBestiauxFrm;
}
//--------------------------------------------
void TLBChoixBestiauxFrm::TexteCaption(void) {
	LC_LBChoixBestiauxFrm = T->TrouveCaption("CL_Trad",
			"LC_LBChoixBestiauxFrm");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TLBChoixBestiauxFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

