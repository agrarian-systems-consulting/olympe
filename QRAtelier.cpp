//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"
#include "CL_Trad.h"

#include "Forme0.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"

#include "QRAtelier.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TQRAtelierFrm *QRAtelierFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TQRAtelierFrm::TQRAtelierFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TQRAtelierFrm::FormCreate(TObject *Sender)
{
	LstCaption=new TObjectList;
	LstCaption->Add(NomPro);
	LstCaption->Add(NomCat);
	LstCaption->Add(NomUnite);
	LstCaption->Add(NomAppro);
	LstCaption->Add(NomUniteAppro);

	DebutVal=LstCaption->Count;

	LstCaption->Add(V0);
	LstCaption->Add(V1);
	LstCaption->Add(V2);
	LstCaption->Add(V3);
	LstCaption->Add(V4);
	LstCaption->Add(V5);
	LstCaption->Add(V6);
	LstCaption->Add(V7);
	LstCaption->Add(V8);
	LstCaption->Add(V9);
	LstCaption->Add(V10);
	LstCaption->Add(V11);
	LstCaption->Add(V12);
	LstCaption->Add(V13);

	LstCol=new TObjectList;
	LstCol->Add(C0);
	LstCol->Add(C1);
	LstCol->Add(C2);
	LstCol->Add(C3);
	LstCol->Add(C4);
	LstCol->Add(C5);
	LstCol->Add(C6);
	LstCol->Add(C7);
	LstCol->Add(C8);
	LstCol->Add(C9);
	LstCol->Add(C10);
	LstCol->Add(C11);
	LstCol->Add(C12);
	LstCol->Add(C13);
}
//---------------------------------------------------------------------------
void __fastcall TQRAtelierFrm::MaBlanc(void)
{
	int i;
	TQRLabel *tqr;
	for(i=0;i<LstCaption->Count;i++)
	{
		tqr=(TQRLabel*)LstCaption->Items[i];
		//tqr->Font->Color=donnees->Couleur;
		tqr->Caption="";
	}
}
//---------------------------------------------------------------------------
void __fastcall TQRAtelierFrm::MaBlancCol(void)
{
	int i;
	TQRLabel *tqr;
	for(i=0;i<LstCol->Count;i++)
	{
		tqr=(TQRLabel*)LstCol->Items[i];
		//tqr->Font->Color=donnees->Couleur;
		tqr->Caption="";
	}
}
//---------------------------------------------------------------------------
void __fastcall TQRAtelierFrm::Prepare(CL_Atelier *atelier)
{
	Digits=0;
	if(AgriEnCours)
	NomAgri->Caption=AgriEnCours->Nom.c_str();
	TitreEtat->Caption=atelier->Nom.c_str();
	LstDonnees=new TList;
	NbPhase=atelier->NbPhase;
	switch(atelier->Nature)
	{
		case CULTURE:
		case ANIMAUX:EnTeteCulture();break;
		case PERENNE:EnTetePerenne(atelier);break;
		case VIVRIER:EnTeteVivrier();break;
		default:
		ShowMessage("Oubli Prepare");
	}
	if(atelier->V_Produit->Nbelt)
	{
		entreTitre("Produits");
		Item(atelier->V_Produit);
		entreBlanc();
	}
	if(atelier->V_Charge->Nbelt)
	{
		entreTitre("Charges");
		Item(atelier->V_Charge);
		entreBlanc();
	}
	if(atelier->V_ChargeVolume->Nbelt)
	{
		entreTitre("Charges fonction de la Production");
		ItemVol(atelier->V_ChargeVolume);
		entreBlanc();
	}
	if(atelier->V_Externalite->Nbelt)
	{
		entreTitre("Externalités");
		Item(atelier->V_Externalite);
		entreBlanc();
	}
	//....
	Initialise();
	QR->Preview();
	DelDonnees();
}
//---------------------------------------------------------------------------
void __fastcall TQRAtelierFrm::QRBeforePrint(TCustomQuickRep *Sender,
		bool &PrintReport)
{
	NLigne=0;
	PrintReport=true;
}

//---------------------------------------------------------------------------
void __fastcall TQRAtelierFrm::Initialise(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TQRAtelierFrm::DelDonnees(void)
{
	CL_QrDon *donnees;
	int i;
	for(i=0;i<LstDonnees->Count;i++)
	{
		donnees=(CL_QrDon *)LstDonnees->Items[i];
		delete donnees;
	}
	delete LstDonnees;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TQRAtelierFrm::QRNeedData(TObject *Sender, bool &MoreData)
{
	MoreData=CompleteDonnees();
}
//---------------------------------------------------------------------------
bool __fastcall TQRAtelierFrm::CompleteDonnees(void)
{
	CL_QrDon *donnees;

	if(NLigne>=LstDonnees->Count) return false;
	MaBlanc();
	donnees=(CL_QrDon*)LstDonnees->Items[NLigne];
	switch(donnees->Type)
	{
		case QRITEM: AffItem(donnees);break;
		case QRITEMVOL: AffItemVol(donnees);break;

		case QRBLANC: AffBlanc(); break;
		case QRTRAIT: AffTrait(); break;
		case QRTITRE: AffTitre(donnees); break;
		default:
		ShowMessage("Oubli Complete Donnees");
	}
	NLigne++;
	return true;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TQRAtelierFrm::EnTeteCulture(void)
{
	int i,j;
	TQRLabel *tqr;
	MaBlancCol();
	C0->Caption="Avant 1";
	for(i=1,j=0;i<NbPhase;i++,j++)
	{
		tqr=(TQRLabel*)LstCol->Items[i];
		//tqr->Font->Color=donnees->Couleur;
		tqr->Caption=IntToStr(j);
	}
}
//---------------------------------------------------------------------------
void __fastcall TQRAtelierFrm::EnTetePerenne(CL_Atelier *atelier)
{
	int i,j;
	int a0,a1;
	char chaine[20];
	CL_Espece *espece;
	TQRLabel *tqr;

	MaBlancCol();
	espece=atelier->Espece;
	C0->Caption=" Avant 1";
	for(i=1,j=0;j<atelier->NbPhase;i++,j++)
	{
		if(i>=14) break; //141105
		a0=espece->Phase[j];
		a1=espece->Phase[j+1];
		if(a1==a0+1) sprintf(chaine,"%2d",a0);
		else sprintf(chaine,"%2d et +",a0);
		tqr=(TQRLabel*)LstCol->Items[i];
		tqr->Caption=chaine;
	}
}
//---------------------------------------------------------------------------
void __fastcall TQRAtelierFrm::EnTeteVivrier(void)
{
	int i,j;
	TQRLabel *tqr;
	MaBlancCol();
	C0->Caption="Avant 1";
	for(i=1,j=0;i<NbPhase;i++,j++)
	{
		tqr=(TQRLabel*)LstCol->Items[i];
		//tqr->Font->Color=donnees->Couleur;
		tqr->Caption=IntToStr(j);
	}
}
//---------------------------------------------------------------------------
// ItemPA
//---------------------------------------------------------------------------
void __fastcall TQRAtelierFrm::Item (CL_Vecteur<CL_ItemParAtelier> *vecteur)
{
	int n,nbelt;
	CL_ItemParAtelier *itemPA;
	nbelt=vecteur->Nbelt;

	for( n=0;n<nbelt;n++)
	{
		itemPA =vecteur->Vecteur[n];
		entreDonnees(QRITEM,itemPA);
	}
}
//---------------------------------------------------------------------------
// quantités prop a la prduction
//---------------------------------------------------------------------------
void __fastcall TQRAtelierFrm::ItemVol (CL_Vecteur<CL_ItemParAtelier> *vecteur)
{
	int n,nbelt;
	CL_ItemParAtelier *itemPA;
	nbelt=vecteur->Nbelt;

	for( n=0;n<nbelt;n++)
	{
		itemPA =vecteur->Vecteur[n];
		entreDonnees(QRITEMVOL,itemPA);
	}
}
//---------------------------------------------------------------------------
//Aff...
//---------------------------------------------------------------------------
void __fastcall TQRAtelierFrm::AffItem(CL_QrDon *donnees)
{
	int i,j;
	CL_ItemParAtelier *itemPA;
	TQRLabel *tqr;
	MaBlanc();
	itemPA=donnees->ItemPA;
	NomPro->Caption=itemPA->Item->Nom.c_str();
	NomPro->Left=donnees->PosNom;
	NomCat->Caption=itemPA->Item->Categorie->Nom.c_str();
	NomUnite->Caption=itemPA->Item->SysUnite->UUt.c_str();
	for(i=0,j=DebutVal;i<NbPhase;i++,j++)
	{
		if(i>=14) break; //141105
		if(itemPA->QtePhase[i]==0) continue;
		{

			tqr=(TQRLabel*)LstCaption->Items[j];
			tqr->Caption=FloatToStrF((double)itemPA->QtePhase[i] ,ffNumber,7,Digits);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TQRAtelierFrm::AffItemVol(CL_QrDon *donnees)
{
	int i,j;
	TQRLabel *tqr;
	CL_ItemParAtelier *itemPA;
	CL_Item *produit;
	MaBlanc();

	itemPA=donnees->ItemPA;
	produit=itemPA->ItemPA->Item;

	NomPro->Caption=produit->Nom.c_str();
	NomPro->Left=donnees->PosNom;
	NomCat->Caption=produit->Categorie->Nom.c_str();
	NomUnite->Caption=produit->SysUnite->UUt.c_str();

	for(i=0,j=DebutVal;i<NbPhase;i++,j++)
	{
		if(i>=14) break; //141105
		if(itemPA->QtePhase[i]==0) continue;
		{
			tqr=(TQRLabel*)LstCaption->Items[j];
			tqr->Caption=FloatToStrF((double)itemPA->QtePhase[i] ,ffNumber,7,Digits);
		}
	}

	if(itemPA->Charge==NULL) return;

	NomAppro->Caption=itemPA->Charge->Nom.c_str();
	NomUniteAppro->Caption=itemPA->Charge->SysUnite->UUt;
}
//---------------------------------------------------------------------------
void __fastcall TQRAtelierFrm::AffTitre(CL_QrDon *donnees)
{
	MaBlanc();
	NomPro->Caption=donnees->Nom;
	NomPro->Left=donnees->PosNom;

}

//---------------------------------------------------------------------------
void __fastcall TQRAtelierFrm::AffTrait(void)
{
}
//---------------------------------------------------------------------------
void __fastcall TQRAtelierFrm::AffBlanc(void)
{
	MaBlanc();
}

//---------------------------------------------------------------------------
//entre...
//---------------------------------------------------------------------------
void __fastcall TQRAtelierFrm::entreDonnees (int type, CL_ItemParAtelier *itemPA)
{
	CL_QrDon *donnees;
	donnees=new CL_QrDon(type,itemPA);
	LstDonnees->Add(donnees);
}
//---------------------------------------------------------------------------
void __fastcall TQRAtelierFrm::entreTitre ( char *nom,TColor couleur)
{
	CL_QrDon *donnees;
	donnees=new CL_QrDon(QRTITRE,nom);
	LstDonnees->Add(donnees);
}
//---------------------------------------------------------------------------
void __fastcall TQRAtelierFrm::entreBlanc(void)
{
	CL_QrDon *donnees;
	donnees=new CL_QrDon(QRBLANC);
	LstDonnees->Add(donnees);
}
//---------------------------------------------------------------------------
// CL_QrDon:: constructeurs
//---------------------------------------------------------------------------
TQRAtelierFrm::CL_QrDon::CL_QrDon(int type, CL_ItemParAtelier *itemPA,
		TColor couleur) {
	Type = type;
	ItemPA = itemPA;
	Nom = NULL;
	EstTitre = false;
	AvecTrait = false;
	EstBlanc = false;
	Couleur = couleur;
	PosNom = 10;
}
//---------------------------------------------------------------------------
TQRAtelierFrm::CL_QrDon::CL_QrDon(int type, char *nom, TColor couleur) {
	Type = type;
	Nom = nom;
	ItemPA = NULL;
	EstTitre = true;
	AvecTrait = false;
	EstBlanc = false;
	Couleur = couleur;
	PosNom = 0;
}
//---------------------------------------------------------------------------
TQRAtelierFrm::CL_QrDon::CL_QrDon(int type, TColor couleur) {
	Type = type;
	Nom = NULL;
	ItemPA = NULL;
	EstTitre = true;
	AvecTrait = false;
	EstBlanc = false;
	Couleur = couleur;
	PosNom = 0;
}
//---------------------------------------------------------------------------
void TQRAtelierFrm::IniCaption(void) {
	Appro->Caption = LC_Appro;
	QRAtelierFrm->Caption = T->LC_AtelierFrm;
	C0->Caption = LC_C0;
	C1->Caption = LC_C1;
	C10->Caption = LC_C10;
	C11->Caption = LC_C11;
	C12->Caption = LC_C12;
	C13->Caption = LC_C13;
	C2->Caption = LC_C2;
	C3->Caption = LC_C3;
	C4->Caption = LC_C4;
	C5->Caption = LC_C5;
	C6->Caption = LC_C6;
	C7->Caption = LC_C7;
	C8->Caption = LC_C8;
	C9->Caption = LC_C9;
	Categorie->Caption = T->LC_RGCat;
	Nom->Caption = T->LC_Nom;
	NomAgri->Caption = T->LC_NomAgri_A;
	NomAppro->Caption = LC_NomAppro;
	NomCat->Caption = LC_NomCat;
	NomPro->Caption = T->LC_NomPro;
	NomUnite->Caption = T->LC_NomUnite;
	NomUniteAppro->Caption = LC_NomUniteAppro;
	TitreEtat->Caption = T->LC_TitreEtat;
	Unite->Caption = T->LC_Unite;
	UniteAppro->Caption = T->LC_Unite;
	V0->Caption = LC_V0;
	V1->Caption = LC_V1;
	V10->Caption = LC_V10;
	V11->Caption = LC_V11;
	V12->Caption = LC_V12;
	V13->Caption = LC_V13;
	V2->Caption = LC_V2;
	V3->Caption = LC_V3;
	V4->Caption = LC_V4;
	V5->Caption = LC_V5;
	V6->Caption = LC_V6;
	V7->Caption = LC_V7;
	V8->Caption = LC_V8;
	V9->Caption = LC_V9;
}
//--------------------------------------------
void TQRAtelierFrm::TexteCaption(void) {
	LC_Appro = T->TrouveCaption("QRAtelier", "LC_Appro");
	LC_AtelierFrm = T->TrouveCaption("CL_Trad", "LC_AtelierFrm");
	LC_C0 = T->TrouveCaption("QRAtelier", "LC_C0");
	LC_C1 = T->TrouveCaption("QRAtelier", "LC_C1");
	LC_C10 = T->TrouveCaption("QRAtelier", "LC_C10");
	LC_C11 = T->TrouveCaption("QRAtelier", "LC_C11");
	LC_C12 = T->TrouveCaption("QRAtelier", "LC_C12");
	LC_C13 = T->TrouveCaption("QRAtelier", "LC_C13");
	LC_C2 = T->TrouveCaption("QRAtelier", "LC_C2");
	LC_C3 = T->TrouveCaption("QRAtelier", "LC_C3");
	LC_C4 = T->TrouveCaption("QRAtelier", "LC_C4");
	LC_C5 = T->TrouveCaption("QRAtelier", "LC_C5");
	LC_C6 = T->TrouveCaption("QRAtelier", "LC_C6");
	LC_C7 = T->TrouveCaption("QRAtelier", "LC_C7");
	LC_C8 = T->TrouveCaption("QRAtelier", "LC_C8");
	LC_C9 = T->TrouveCaption("QRAtelier", "LC_C9");
	LC_RGCat = T->TrouveCaption("CL_Trad", "LC_RGCat");
	LC_Nom = T->TrouveCaption("CL_Trad", "LC_Nom");
	LC_NomAgri_A = T->TrouveCaption("CL_Trad", "LC_NomAgri_A");
	LC_NomAppro = T->TrouveCaption("QRAtelier", "LC_NomAppro");
	LC_NomCat = T->TrouveCaption("QRAtelier", "LC_NomCat");
	LC_NomPro = T->TrouveCaption("CL_Trad", "LC_NomPro");
	LC_NomUnite = T->TrouveCaption("CL_Trad", "LC_NomUnite");
	LC_NomUniteAppro = T->TrouveCaption("QRAtelier", "LC_NomUniteAppro");
	LC_TitreEtat = T->TrouveCaption("CL_Trad", "LC_TitreEtat");
	LC_Unite = T->TrouveCaption("CL_Trad", "LC_Unite");
	LC_V0 = T->TrouveCaption("QRAtelier", "LC_V0");
	LC_V1 = T->TrouveCaption("QRAtelier", "LC_V1");
	LC_V10 = T->TrouveCaption("QRAtelier", "LC_V10");
	LC_V11 = T->TrouveCaption("QRAtelier", "LC_V11");
	LC_V12 = T->TrouveCaption("QRAtelier", "LC_V12");
	LC_V13 = T->TrouveCaption("QRAtelier", "LC_V13");
	LC_V2 = T->TrouveCaption("QRAtelier", "LC_V2");
	LC_V3 = T->TrouveCaption("QRAtelier", "LC_V3");
	LC_V4 = T->TrouveCaption("QRAtelier", "LC_V4");
	LC_V5 = T->TrouveCaption("QRAtelier", "LC_V5");
	LC_V6 = T->TrouveCaption("QRAtelier", "LC_V6");
	LC_V7 = T->TrouveCaption("QRAtelier", "LC_V7");
	LC_V8 = T->TrouveCaption("QRAtelier", "LC_V8");
	LC_V9 = T->TrouveCaption("QRAtelier", "LC_V9");

	IniCaption();

}

