//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"

#include "Forme0.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "CL_Trad.h"

#include "QRCatNomUnite.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "QRCatNom"
#pragma resource "*.dfm"
TQRCatNomUniteFrm *QRCatNomUniteFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TQRCatNomUniteFrm::TQRCatNomUniteFrm(TComponent* Owner) :
		TQRCatNomFrm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TQRCatNomUniteFrm::AffBlanc(void)
{
	Sup->Caption="";
	NomPro->Caption= "";
	UUt->Caption= "";
	UTrans->Caption= "";
	UGlobal->Caption= "";
//    PrixPro->Caption= "";
//    UnPro->Caption=   "";
//    TauxTva->Caption= "";

}
//---------------------------------------------------------------------------
void __fastcall TQRCatNomUniteFrm::AffTitre(char *nom)
{
	Sup->Caption="";
	NomPro->Font->Style<<fsBold;
	NomPro->Caption= nom;
	NomPro->Left= 0;
	UUt->Caption= "";
	UTrans->Caption= "";
	UGlobal->Caption= "";
//    PrixPro->Caption= "";
//    UnPro->Caption=   "";
//    TauxTva->Caption="";
}
//---------------------------------------------------------------------------
void __fastcall TQRCatNomUniteFrm::AffItem(CL_Item *item)
{
	AnsiString as;
	if(item->Supprimable==true) Sup->Caption="";
	else Sup->Caption="*";
	NomPro->Font->Style>>fsBold;
	NomPro->Left= 20;
	NomPro->Caption=item->Nom;
	UUt->Caption=item->SysUnite->UUt;
	UTrans->Caption=item->SysUnite->UTrans;
	UGlobal->Caption=item->SysUnite->UGlobal;
//    PrixPro->Caption=FloatToStrF((double)item->Prix,ffNumber,7,2);
//    as=SysMonnaie->UTrans+ " / "+item->SysUnite->UTrans;
//    UnPro->Caption=as;
//    TauxTva->Caption=item->Tva->Nom;
}
//---------------------------------------------------------------------------
void __fastcall TQRCatNomUniteFrm::QRNeedData(TObject *Sender,
		bool &MoreData)
{
	MoreData=CompleteDonnees();
}
//---------------------------------------------------------------------------
bool __fastcall TQRCatNomUniteFrm::CompleteDonnees(void)
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
void TQRCatNomUniteFrm::IniCaption(void) {
	Atelier->Caption = T->LC_AtelierFrm;
	Expl->Caption = LC_Expl;
	QRCatNomUniteFrm->Caption = LC_QRCatNomUniteFrm;
	Region->Caption = LC_Region;
	UGlobal->Caption = LC_UGlobal;
	Unite->Caption = T->LC_BtBnUnite;
	UTrans->Caption = LC_UTrans;
	UUt->Caption = LC_UUt;
}
//--------------------------------------------
void TQRCatNomUniteFrm::TexteCaption(void) {
	LC_AtelierFrm = T->TrouveCaption("CL_Trad", "LC_AtelierFrm");
	LC_Expl = T->TrouveCaption("QRCatNomUnite", "LC_Expl");
	LC_QRCatNomUniteFrm = T->TrouveCaption("QRCatNomUnite",
			"LC_QRCatNomUniteFrm");
	LC_Region = T->TrouveCaption("QRCatNomUnite", "LC_Region");
	LC_UGlobal = T->TrouveCaption("QRCatNomUnite", "LC_UGlobal");
	LC_BtBnUnite = T->TrouveCaption("CL_Trad", "LC_BtBnUnite");
	LC_UTrans = T->TrouveCaption("QRCatNomUnite", "LC_UTrans");
	LC_UUt = T->TrouveCaption("QRCatNomUnite", "LC_UUt");

	IniCaption();

}
//--------------------------------------------

