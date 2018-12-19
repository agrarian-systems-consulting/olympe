//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//#include "Olympedec.h"
#include "Olympe.hse"

#include "Forme0.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "CL_Trad.h"

#include "QRCatNom.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TQRCatNomFrm *QRCatNomFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TQRCatNomFrm::TQRCatNomFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
TQRCatNomFrm::CL_QrDon::CL_QrDon(int symbole) {
	Type = 0;
}
//---------------------------------------------------------------------------
TQRCatNomFrm::CL_QrDon::CL_QrDon(char *nom) {
	Type = 1;
	Nom = nom;
}
//---------------------------------------------------------------------------
TQRCatNomFrm::CL_QrDon::CL_QrDon(CL_Item *item) {
	Type = 2;
	Item = item;
}
//---------------------------------------------------------------------------
TQRCatNomFrm::CL_QrDon::CL_QrDon(CL_Atelier *atelier) {
	Type = 3;
	Atelier = atelier;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TQRCatNomFrm::entreDonnees(char *nom)
{
	CL_QrDon *donnees;
	donnees=new CL_QrDon(nom);
	LstDonnees->Add(donnees);
}
//---------------------------------------------------------------------------
void __fastcall TQRCatNomFrm::entreDonnees(CL_Item *item)
{
	CL_QrDon *donnees;
	donnees=new CL_QrDon(item);
	LstDonnees->Add(donnees);
}
//---------------------------------------------------------------------------
void __fastcall TQRCatNomFrm::entreDonnees(CL_Atelier *atelier)
{
	CL_QrDon *donnees;
	donnees=new CL_QrDon(atelier);
	LstDonnees->Add(donnees);
}
//---------------------------------------------------------------------------
void __fastcall TQRCatNomFrm::blanc(void)
{
	CL_QrDon *donnees;
	donnees=new CL_QrDon(BLANC);
	LstDonnees->Add(donnees);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TQRCatNomFrm::AffBlanc(void)
{
	Sup->Caption="";
	NomPro->Caption= "";

}
//---------------------------------------------------------------------------
void __fastcall TQRCatNomFrm::AffTitre(char *nom)
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
//    TauxTva->Caption="";
}
//---------------------------------------------------------------------------
void __fastcall TQRCatNomFrm::AffItem(CL_Item *item)
{
	AnsiString as;
	if(item->Supprimable==true) Sup->Caption="";
	else Sup->Caption="*";
	NomPro->Font->Style>>fsBold;
	NomPro->Left= 20;
	NomPro->Caption=item->Nom;
}
//---------------------------------------------------------------------------
void __fastcall TQRCatNomFrm::AffAtelier(CL_Atelier *atelier)
{
	AnsiString as;
	NomPro->Font->Style>>fsBold;
	NomPro->Left= 20;
	NomPro->Caption=atelier->Nom;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TQRCatNomFrm::Prepare(CL_Agriculteur *agri,char *titre,
		CL_Vecteur<CL_Categorie> *vCategorie,CL_Vecteur<CL_Item> *vItem)

{
	int i,j;
	CL_Categorie *categorie;
	CL_Item *item;

	if(vCategorie->Nbelt==0) return; //a mettre dans l'appel

	NomAgri->Caption=agri->Nom.c_str();
	TitreEtat->Caption=titre;
	NLigne=0;
	LstDonnees=new TList;
	for (i=0;i<vCategorie->Nbelt;i++)
	{
		categorie=vCategorie->Vecteur[i];
		entreDonnees(categorie->Nom.c_str());

		for(j=0;j<vItem->Nbelt;j++)
		{
			item=vItem->Vecteur[j];
			if(item->Categorie!=categorie) continue;
			entreDonnees(item);
		}
	}
	QR->Preview();
	DelDonnees();
}
//---------------------------------------------------------------------------
void __fastcall TQRCatNomFrm::PrepareAtelier(CL_Agriculteur *agri,char *titre,
		CL_Vecteur<CL_Categorie> *vCategorie,CL_Vecteur<CL_Atelier> *vAtelier)
{
	int i,j;
	AnsiString as;
	CL_Categorie *categorie;
	CL_Atelier *atelier;

	if(vCategorie->Nbelt==0) return; //a mettre dans l'appel

	NomAgri->Caption=agri->Nom.c_str();
	TitreEtat->Caption=titre;
	NLigne=0;
	LstDonnees=new TList;
	for (i=0;i<vCategorie->Nbelt;i++)
	{
		categorie=vCategorie->Vecteur[i];
		entreDonnees(categorie->Nom.c_str());

		for(j=0;j<vAtelier->Nbelt;j++)
		{
			atelier=vAtelier->Vecteur[j];
			if(atelier->Categorie!=categorie) continue;
			as=AnsiString("   ")+atelier->Nom;
			entreDonnees(atelier);
		}
	}
	QR->Preview();
	DelDonnees();
}
//---------------------------------------------------------------------------
void __fastcall TQRCatNomFrm::PreparePerenne(CL_Agriculteur *agri,char *titre,
		CL_Vecteur<CL_Espece> *vEspece,CL_Vecteur<CL_Atelier> *vAtelier)
{
	int i,j;
	AnsiString as;
	CL_Espece *espece;
	CL_Atelier *atelier;

	if(vEspece->Nbelt==0) return; //a mettre dans l'appel

	NomAgri->Caption=agri->Nom.c_str();
	TitreEtat->Caption=titre;
	NLigne=0;
	LstDonnees=new TList;
	for (i=0;i<vEspece->Nbelt;i++)
	{
		espece=vEspece->Vecteur[i];
		entreDonnees(espece->Nom.c_str());

		for(j=0;j<vAtelier->Nbelt;j++)
		{
			atelier=vAtelier->Vecteur[j];
			if(atelier->Espece!=espece) continue;
			as=AnsiString("   ")+atelier->Nom;
			entreDonnees(atelier);
		}
	}
	QR->Preview();
	DelDonnees();
}
//---------------------------------------------------------------------------
void __fastcall TQRCatNomFrm::QRNeedData(TObject *Sender,
		bool &MoreData)
{
	MoreData=CompleteDonnees();
}
//---------------------------------------------------------------------------
bool __fastcall TQRCatNomFrm::CompleteDonnees(void)
{
	CL_QrDon *donnees;

	if(NLigne>=LstDonnees->Count) return false;

	donnees=(CL_QrDon*)LstDonnees->Items[NLigne];
	switch(donnees->Type)
	{
		case 0: AffBlanc(); break;
		case 1: AffTitre(donnees->Nom);break;
		case 2: AffItem(donnees->Item);break;
		case 3: AffAtelier(donnees->Atelier);break;
		default:
		ShowMessage("Oubli QRProCharge Complete Donnees");
	}
	NLigne++;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TQRCatNomFrm::DelDonnees(void)
{
	CL_QrDon *donnees;
	for(int i=0;i<LstDonnees->Count;i++)
	{
		donnees=(CL_QrDon *)LstDonnees->Items[i];
		delete donnees;
	}
	delete LstDonnees;
}
//---------------------------------------------------------------------------
void __fastcall TQRCatNomFrm::QRBeforePrint(TCustomQuickRep *Sender,
		bool &PrintReport)
{
	NLigne=0;
	PrintReport=true;
}
//---------------------------------------------------------------------------
//--------------------------------------------
void TQRCatNomFrm::IniCaption(void) {
	Nom->Caption = T->LC_Nom;
	NomAgri->Caption = T->LC_NomAgri_A;
	NomPro->Caption = T->LC_NomPro;
	QRCatNomFrm->Caption = LC_QRCatNomFrm;
	Sup->Caption = LC_Sup;
	TitreEtat->Caption = T->LC_TitreEtat;
}
//--------------------------------------------
void TQRCatNomFrm::TexteCaption(void) {
	LC_Nom = T->TrouveCaption("CL_Trad", "LC_Nom");
	LC_NomAgri_A = T->TrouveCaption("CL_Trad", "LC_NomAgri_A");
	LC_NomPro = T->TrouveCaption("CL_Trad", "LC_NomPro");
	LC_QRCatNomFrm = T->TrouveCaption("QRCatNom", "LC_QRCatNomFrm");
	LC_Sup = T->TrouveCaption("QRCatNom", "LC_Sup");
	LC_TitreEtat = T->TrouveCaption("CL_Trad", "LC_TitreEtat");

	IniCaption();

}
//--------------------------------------------

