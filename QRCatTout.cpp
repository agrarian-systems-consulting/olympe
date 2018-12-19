//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"

#include "Forme0.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "CL_Trad.h"

#include "QRCatTout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "QRCatNomUnite"
#pragma resource "*.dfm"
TQRCatToutFrm *QRCatToutFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TQRCatToutFrm::TQRCatToutFrm(TComponent* Owner) :
		TQRCatNomUniteFrm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TQRCatToutFrm::AffBlanc(void)
{
	Sup->Caption="";
	NomPro->Caption= "";
//    NomCat->Caption=  "";
	UUt->Caption= "";
	UTrans->Caption= "";
	UGlobal->Caption= "";
	PrixPro->Caption= "";
	UnPro->Caption= "";
	TauxTva->Caption= "";

}
//---------------------------------------------------------------------------
void __fastcall TQRCatToutFrm::AffTitre(char *nom)
{
	Sup->Caption="";
	NomPro->Font->Style<<fsBold;
	NomPro->Caption= nom;
	NomPro->Left= 0;
//    NomCat->Caption=  "";
	UUt->Caption= "";
	UTrans->Caption= "";
	UGlobal->Caption= "";
	PrixPro->Caption= "";
	UnPro->Caption= "";
	TauxTva->Caption="";
}
//---------------------------------------------------------------------------
void __fastcall TQRCatToutFrm::AffItem(CL_Item *item)
{
	AnsiString as;
	if(item->Supprimable==true) Sup->Caption="";
	else Sup->Caption="*";
	NomPro->Font->Style>>fsBold;
	NomPro->Left= 20;
	NomPro->Caption=item->Nom;
//    NomCat->Caption=item->Categorie->Nom;
	UUt->Caption=item->SysUnite->UUt;
	UTrans->Caption=item->SysUnite->UTrans;
	UGlobal->Caption=item->SysUnite->UGlobal;
	PrixPro->Caption=FloatToStrF((double)item->Prix,ffNumber,7,2);
	as=SysMonnaie->UTrans+ " / "+item->SysUnite->UTrans;
	UnPro->Caption=as;
	TauxTva->Caption=item->Tva->Nom;
}
//---------------------------------------------------------------------------
void __fastcall TQRCatToutFrm::QRNeedData(TObject *Sender,
		bool &MoreData)
{
	MoreData=CompleteDonnees();
}
//---------------------------------------------------------------------------
bool __fastcall TQRCatToutFrm::CompleteDonnees(void)
{
	CL_QrDon *donnees;

	if(NLigne>=LstDonnees->Count) return false;

	donnees=(CL_QrDon*)LstDonnees->Items[NLigne];
	switch(donnees->Type)
	{
		case 0: AffBlanc(); break;
		case 1: AffTitre(donnees->Nom);break;
		case 2: AffItem(donnees->Item);break;
		default:
		ShowMessage("Oubli QRProCharge Complete Donnees");
	}
	NLigne++;
	return true;
}

//--------------------------------------------
void TQRCatToutFrm::IniCaption(void) {
	Prix->Caption = T->LC_GBPrix;
	PrixPro->Caption = LC_PrixPro;
	QRCatToutFrm->Caption = LC_QRCatToutFrm;
	TauxTva->Caption = T->LC_TauxTva;
	Tva->Caption = T->LC_BtBnTva;
	UnPro->Caption = LC_UnPro;
}
//--------------------------------------------
void TQRCatToutFrm::TexteCaption(void) {
	LC_GBPrix = T->TrouveCaption("CL_Trad", "LC_GBPrix");
	LC_PrixPro = T->TrouveCaption("QRCatTout", "LC_PrixPro");
	LC_QRCatToutFrm = T->TrouveCaption("QRCatTout", "LC_QRCatToutFrm");
	LC_TauxTva = T->TrouveCaption("CL_Trad", "LC_TauxTva");
	LC_BtBnTva = T->TrouveCaption("CL_Trad", "LC_BtBnTva");
	LC_UnPro = T->TrouveCaption("QRCatTout", "LC_UnPro");

	IniCaption();

}
//--------------------------------------------

