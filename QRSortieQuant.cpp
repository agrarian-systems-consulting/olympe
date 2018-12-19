//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//#include "Olympedec.h"
#include "Olympe.hse"

#include "Forme0.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "Resultat.h"
#include "CL_Trad.h"

#include "QRSortieQuant.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "QRSortieVal"
#pragma resource "*.dfm"
TQRSortieQuantFrm *QRSortieQuantFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TQRSortieQuantFrm::TQRSortieQuantFrm(TComponent* Owner) :
		TQRSortieValFrm(Owner) {
}
//---------------------------------------------------------------------------

void __fastcall TQRSortieQuantFrm::QRNeedData(TObject *Sender,
		bool &MoreData)
{
	MoreData=CompleteDonnees();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool __fastcall TQRSortieQuantFrm::CompleteDonnees(void)
{
	CL_QrDon *donnees;
//TList *lst;
//    lst=QRPrepareSortieFrm->LstDonnees;

	if(NLigne>=LstDonnees->Count) return false;
//enum {QRDON,QRBIL,QRTITRE,QRTITRE1,QRBLANC};

	donnees=(CL_QrDon*)LstDonnees->Items[NLigne];
	if(donnees==NULL)
	return false;
	switch(donnees->Type)
	{
		case QRDON:
		case QRTITRE:
		case QRTITRE1:
		AffDonnees(donnees);break;
		case QRANI: AffAni(donnees); break;
		case QRBLANC: AffBlanc(); break;
		case QRTRAIT: AffTrait(); break;
		default:
		ShowMessage("Oubli Complete Donnees");
	}
	NLigne++;
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TQRSortieQuantFrm::AffDonnees(CL_QrDon *donnees)
{
	TQRLabel *tqr;
//int nColonne;
	int i,j;
	int digits;
//    nColonne=QR->Tag;
	DetailBand1->Frame->DrawTop=false;
//..    test pour modif taille si nom trop long-> illisible à l'ecran  211006
//    IntituleP->Font->Height=-7;
//    IntituleP->Font->Color=clBlack;
//..

	IntituleP->Caption=donnees->Nom;
	IntituleP->Left=donnees->PosNom;
	IntituleP->Font->Color=donnees->Couleur;

//    Unite->Caption=donnees->Unite;
//    Unite->Font->Color=donnees->Couleur;

	if(donnees->AvecTrait==true)
	DetailBand1->Frame->DrawTop=true;

	if(donnees->Val==NULL)
	{
		NomUnite->Caption="";
		for(i=0;i<11;i++)
		{
			tqr=(TQRLabel*)LstCaption->Items[i];
			tqr->Font->Color=donnees->Couleur;
			tqr->Caption="";
		}
	}
	else
	{
		tqr=(TQRLabel*)LstCaption->Items[0];
		tqr->Caption="";
		NomUnite->Caption=donnees->Unite;
		for(i=1,j=0;i<11;i++,j++)
		{
			tqr=(TQRLabel*)LstCaption->Items[i];
			tqr->Font->Color=donnees->Couleur;
			if(donnees->Val[j]==0)
			tqr->Caption="";
			else
			{ //160808
				if(donnees->Digits==-1)
				digits=ResultatFrm->Digits;
				else
				digits=donnees->Digits;
				tqr->Caption=FloatToStrF((double) donnees->Val[j],ffNumber,7,digits);
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TQRSortieQuantFrm::AffAni(CL_QrDon *donnees)
{
	TQRLabel *tqr;
//int nColonne;
	int i,j;
//    nColonne=QR->Tag;
	DetailBand1->Frame->DrawTop=false;

	IntituleP->Caption=donnees->Nom;
	IntituleP->Left=donnees->PosNom;
	IntituleP->Font->Color=donnees->Couleur;

//    Unite->Caption=donnees->Unite;
//    Unite->Font->Color=donnees->Couleur;

	if(donnees->AvecTrait==true)
	DetailBand1->Frame->DrawTop=true;

	if(donnees->ValInt==NULL)
	{
		NomUnite->Caption="";
		for(i=0;i<11;i++)
		{
			tqr=(TQRLabel*)LstCaption->Items[i];
			tqr->Font->Color=donnees->Couleur;
			tqr->Caption="";
		}
	}
	else
	{
		tqr=(TQRLabel*)LstCaption->Items[0];
		tqr->Caption="";
		NomUnite->Caption=donnees->Unite;
		for(i=1,j=0;i<11;i++,j++)
		{
			tqr=(TQRLabel*)LstCaption->Items[i];
			tqr->Font->Color=donnees->Couleur;
			if(donnees->ValInt[j]==0)
			tqr->Caption="";
			else
			tqr->Caption=IntToStr((int)donnees->ValInt[j]);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TQRSortieQuantFrm::AffBlanc(void)
{
	TQRLabel *tqr;
	DetailBand1->Frame->DrawTop=false;

	IntituleP->Caption="";
	NomUnite->Caption="";
	for(int i=0;i<11;i++)
	{
		tqr=(TQRLabel*)LstCaption->Items[i];
		tqr->Caption="";
	}
}
//---------------------------------------------------------------------------
void __fastcall TQRSortieQuantFrm::AffTrait(void)
{
	TQRLabel *tqr;
	DetailBand1->Frame->DrawTop=true;
	NomUnite->Caption="";
	IntituleP->Caption="";
	for(int i=0;i<11;i++)
	{
		tqr=(TQRLabel*)LstCaption->Items[i];
		tqr->Caption="";
	}
}

//---------------------------------------------------------------------------
void __fastcall TQRSortieQuantFrm::QRBeforePrint(TCustomQuickRep *Sender,
		bool &PrintReport)
{
	NLigne=0;
	PrintReport=true;
}

//---------------------------------------------------------------------------
void TQRSortieQuantFrm::TexteChaine(void) {
	L_Comp = T->TrouveTexte("QRSortieQuantFrm", "L_Comp");

	//QRResSortieQuant
	L_1 = T->TrouveTexte("QRSortieQuantFrm", "L_1");
	L_2 = T->TrouveTexte("QRSortieQuantFrm", "L_2");
	L_3 = T->TrouveTexte("QRSortieQuantFrm", "L_3");
	L_4 = T->TrouveTexte("QRSortieQuantFrm", "L_4");
	L_5 = T->TrouveTexte("QRSortieQuantFrm", "L_5");
	L_6 = T->TrouveTexte("QRSortieQuantFrm", "L_6");
	L_7 = T->TrouveTexte("QRSortieQuantFrm", "L_7");
	L_8 = T->TrouveTexte("QRSortieQuantFrm", "L_8");
	L_9 = T->TrouveTexte("QRSortieQuantFrm", "L_9");
}

/*
 //---------------------------------------------------------------------------
 void TQRSortieQuantFrm::Francais(void)
 {
 L_Comp=  "Comparaison";

 //QRResSortieQuant
 L_1=  "Quantites Physiques";
 L_2=  "Externalités";
 L_3=  "Produits";
 L_4=  "Charges";
 L_5=  "Animaux Vendus";
 L_6=  "tête";
 L_7=  "Animaux Achetés";
 L_8=  "Négatives";
 L_9=  "Positives";
 }



 //---------------------------------------------------------------------------
 void TQRSortieQuantFrm::Anglais(void)
 {
 L_Comp=  "Comparison";

 //QRResSortieQuant
 L_1=  "Actual Quantities";
 L_2=  "Externalities";
 L_3=  "Products";
 L_4=  "Costs";
 L_5=  "Animals Sold";
 L_6=  "head";
 L_7=  "Animals bought";
 L_8=  "Negative";
 L_9=  "Positive";


 }
 */

//--------------------------------------------
void TQRSortieQuantFrm::IniCaption(void) {
	NomUnite->Caption = T->LC_NomUnite;
	QRSortieQuantFrm->Caption = LC_QRSortieQuantFrm;
	Unite->Caption = T->LC_Unite;
}
//--------------------------------------------
void TQRSortieQuantFrm::TexteCaption(void) {
	LC_NomUnite = T->TrouveCaption("CL_Trad", "LC_NomUnite");
	LC_QRSortieQuantFrm = T->TrouveCaption("QRSortieQuant",
			"LC_QRSortieQuantFrm");
	LC_Unite = T->TrouveCaption("CL_Trad", "LC_Unite");

	IniCaption();

}
//--------------------------------------------

