//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"

#include "Forme0.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "CL_Trad.h"

#include "QRCatNomTva.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "QRCatNom"
#pragma resource "*.dfm"
TQRCatNomTvaFrm *QRCatNomTvaFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TQRCatNomTvaFrm::TQRCatNomTvaFrm(TComponent* Owner) :
		TQRCatNomFrm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TQRCatNomTvaFrm::AffBlanc(void)
{
	Sup->Caption="";
	NomPro->Caption= "";
//    UUt->Caption=     "";
//    UTrans->Caption=  "";
//    UGlobal->Caption= "";
//    PrixPro->Caption= "";
//    UnPro->Caption=   "";
	TauxTva->Caption= "";

}
//---------------------------------------------------------------------------
void __fastcall TQRCatNomTvaFrm::AffTitre(char *nom)
{
	Sup->Caption="";
	NomPro->Font->Style<<fsBold;
	NomPro->Caption= nom;
	NomPro->Left= 0;
//    UUt->Caption=     "";
//    UTrans->Caption=  "";
//    UGlobal->Caption= "";
//    PrixPro->Caption= "";
//    UnPro->Caption=   "";
	TauxTva->Caption="";
}
//---------------------------------------------------------------------------
void __fastcall TQRCatNomTvaFrm::AffItem(CL_Item *item)
{
	AnsiString as;
	if(item->Supprimable==true) Sup->Caption="";
	else Sup->Caption="*";
	NomPro->Font->Style>>fsBold;
	NomPro->Left= 20;
	NomPro->Caption=item->Nom;
//    UUt->Caption=item->SysUnite->UUt;
//    UTrans->Caption=item->SysUnite->UTrans;
//    UGlobal->Caption=item->SysUnite->UGlobal;
//    PrixPro->Caption=FloatToStrF((double)item->Prix,ffNumber,7,2);
//    as=SysMonnaie->UTrans+ " / "+item->SysUnite->UTrans;
//    UnPro->Caption=as;
	TauxTva->Caption=item->Tva->Nom;
}
//---------------------------------------------------------------------------
void __fastcall TQRCatNomTvaFrm::QRNeedData(TObject *Sender,
		bool &MoreData)
{
	MoreData=CompleteDonnees();
}
//---------------------------------------------------------------------------
bool __fastcall TQRCatNomTvaFrm::CompleteDonnees(void)
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
void TQRCatNomTvaFrm::IniCaption(void) {
	QRCatNomTvaFrm->Caption = LC_QRCatNomTvaFrm;
	TauxTva->Caption = T->LC_TauxTva;
	Tva->Caption = T->LC_BtBnTva;
}
//--------------------------------------------
void TQRCatNomTvaFrm::TexteCaption(void) {
	LC_QRCatNomTvaFrm = T->TrouveCaption("QRCatNomTva", "LC_QRCatNomTvaFrm");
	LC_TauxTva = T->TrouveCaption("CL_Trad", "LC_TauxTva");
	LC_BtBnTva = T->TrouveCaption("CL_Trad", "LC_BtBnTva");

	IniCaption();

}
//--------------------------------------------

