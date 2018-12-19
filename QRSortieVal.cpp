//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//#include "Olympedec.h"
#include "Olympe.hse"

#include "Forme0.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "AgriSaisie.h"
#include "Resultat.h"
#include "CL_Trad.h"
#include "QRSortieVal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
extern CL_Trad *T;

TQRSortieValFrm *QRSortieValFrm;
void __fastcall TQRSortieValFrm::FormCreate(TObject *Sender)
{
	LstCaption=new TObjectList;
	LstCaption->Add(Val0);
	LstCaption->Add(Val1);
	LstCaption->Add(Val2);
	LstCaption->Add(Val3);
	LstCaption->Add(Val4);
	LstCaption->Add(Val5);
	LstCaption->Add(Val6);
	LstCaption->Add(Val7);
	LstCaption->Add(Val8);
	LstCaption->Add(Val9);
	LstCaption->Add(Val10);

}
//---------------------------------------------------------------------------
__fastcall TQRSortieValFrm::TQRSortieValFrm(TComponent* Owner) :
		TForm(Owner) {
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//            CONSTRUCTEURS de CL_QrDon
//Sans Unité
//---------------------------------------------------------------------------
TQRSortieValFrm::CL_QrDon::CL_QrDon(int type, char *nom, float *val,
		TColor couleur, bool avecTrait) {
	Nom = nom;
	if (val)
		memcpy(Val, val, sizeof(Val));
	else
		memset(Val, 0, sizeof(Val));
	//Val=val; 270805
	Couleur = couleur;
	Type = type;
	Unite = NULL;
	MiseEnPage(type, avecTrait);
	Digits = -1;
}
//AVEC Unite val float
//---------------------------------------------------------------------------
TQRSortieValFrm::CL_QrDon::CL_QrDon(int type, char *nom, char *unite,
		float *val, TColor couleur, bool avecTrait) {
	Nom = nom;
	memcpy(Val, val, sizeof(Val));
	//Val=val;  270805
	Unite = unite;
	Couleur = couleur;
	Type = type;
	MiseEnPage(type, avecTrait);
	Digits = -1; //160808
}
//---------------------------------------------------------------------------
TQRSortieValFrm::CL_QrDon::CL_QrDon(int type, char *nom, char *unite,
		float *val, int digits, TColor couleur, bool avecTrait) {
	Nom = nom;
	memcpy(Val, val, sizeof(Val));
	//Val=val;  270805
	Unite = unite;
	Couleur = couleur;
	Type = type;
	MiseEnPage(type, avecTrait);
	Digits = digits;
}

//AVEC Unite val int
//---------------------------------------------------------------------------
TQRSortieValFrm::CL_QrDon::CL_QrDon(int type, char *nom, char *unite, int *val,
		TColor couleur, bool avecTrait) {
	Nom = nom;
	memset(Val, 0, sizeof(Val));
	//Val=NULL;
	memcpy(ValInt, val, sizeof(ValInt));
	Unite = unite;
	Couleur = couleur;
	Type = type;
	MiseEnPage(type, avecTrait);
	Digits = -1; //160808
}
//-------------------------------------------------------------------------
TQRSortieValFrm::CL_QrDon::CL_QrDon(int type, TColor couleur) {
	Type = type;
	Nom = NULL;
	Couleur = couleur;
	Unite = NULL;
	memset(Val, 0, sizeof(Val));
	//Val=NULL;
	PosNom = 0;
	AvecTrait = false;
	EstTitre = false;
	EstBlanc = true;
	Digits = -1; //160808
}
//-------------------------------------------------------------------------
TQRSortieValFrm::CL_QrDon::CL_QrDon(char *nom, TColor couleur) {
	Type = QRTITRE;
	Nom = nom;
	Couleur = couleur;
	Unite = NULL;
	memset(Val, 0, sizeof(Val));
//    Val=NULL;
	PosNom = 0;
	AvecTrait = false;
	EstTitre = false;
	EstBlanc = true;
	Digits = -1; //160808
}
//---------------------------------------------------------------------------
void TQRSortieValFrm::CL_QrDon::MiseEnPage(int type, bool avecTrait) {
	if (type == QRDON || type == QRBIL) {
		PosNom = 20;
		EstTitre = false;
		AvecTrait = avecTrait;
		EstTitre = false;
		EstBlanc = false;
	} else if (type == QRTITRE) {
		PosNom = 0;
		AvecTrait = avecTrait;
		EstTitre = true;
		EstBlanc = false;
	} else if (type == QRTITRE1) {
		PosNom = 10;
		AvecTrait = avecTrait;
		EstTitre = true;
		EstBlanc = false;
	}
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//  Utilitaire
//-------------------------------------------------------------------------
bool TQRSortieValFrm::EstVide(float *vecteur, int n_x) {
	for (int n = 0; n < n_x; n++) {
		if (vecteur[n] != 0)
			return false;
	}
	return true;
}
//-------------------------------------------------------------------------
bool TQRSortieValFrm::EstVide(int *vecteur, int n_x) {
	for (int n = 0; n < n_x; n++) {
		if (vecteur[n] != 0)
			return false;
	}
	return true;
}

//-------------------------------------------------------------------------
//  met les années
// cree LstCaption  pour afficher les données an/an
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::Initialise(void)
{
	int an;
	NomAgri->Caption=AgriSaisieFrm->Caption;

	an=Agri->DefSim->An_0-1;
	LabAn0->Caption=an++;
	LabAn1->Caption=an++;
	LabAn2->Caption=an++;
	LabAn3->Caption=an++;
	LabAn4->Caption=an++;
	LabAn5->Caption=an++;
	LabAn6->Caption=an++;
	LabAn7->Caption=an++;
	LabAn8->Caption=an++;
	LabAn9->Caption=an++;
	LabAn10->Caption=an;
	if(QR->Tag==10)
	LabAn0->Caption="";

	NLigne=0;
}
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::DelDonnees(void)
{
	CL_QrDon *donnees;
	int i;
	if(LstDonnees==NULL) return; //211204

	for(i=0;i<LstDonnees->Count;i++)
	{
		donnees=(CL_QrDon *)LstDonnees->Items[i];
		delete donnees;
	}
	delete LstDonnees;
	LstDonnees=NULL;
//    delete QRSortieFrm->LstCaption;  //problème
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//      Cree donnes pour contenir titre et valeurs à afficher sur une ligne de QR
//---------------------------------------------------------------------------
//valeurs monétaires
void __fastcall TQRSortieValFrm::entreDonnees(int type,char *nom,float *val,TColor couleur)
{
	CL_QrDon *donnees;
	donnees=new CL_QrDon(type,nom,val,couleur);
	LstDonnees->Add(donnees);
}
//Quantités en float avec Unités
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::entreDonnees(int type,char *nom,char *unite,float *val,TColor couleur)
{
	CL_QrDon *donnees;
	donnees=new CL_QrDon(type,nom,unite,val,couleur);
	LstDonnees->Add(donnees);
}
//Quantités en float avec Unités  et Digits
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::entreDonnees(int type,char *nom,char *unite,float *val,int digits, TColor couleur)
{
	CL_QrDon *donnees;
	donnees=new CL_QrDon(type,nom,unite,val,digits, couleur);
	LstDonnees->Add(donnees);
}
//Famille Nom Quantités en float avec Unités
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::entreDonnees(int type,CL_Elt *elt,TColor couleur)
{
	CL_QrDon *donnees;
	char *unite; //121103
	unite=elt->Donne_Unite();
	donnees=new CL_QrDon(type,elt->Nom,unite,elt->Valeur,elt->Digits, couleur);
	LstDonnees->Add(donnees);
}
//Quantités en int avec Unités
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::entreDonnees(int type,char *nom,char *unite,int *val,TColor couleur)
{
	CL_QrDon *donnees;
	donnees=new CL_QrDon(type,nom,unite,val,couleur);
	LstDonnees->Add(donnees);
}
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::entreBlanc(void)
{
	CL_QrDon *donnees;
	donnees=new CL_QrDon(QRBLANC);
	LstDonnees->Add(donnees);
}
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::entreTitre(char *nom)
{
	CL_QrDon *donnees;
	donnees=new CL_QrDon(nom);
	LstDonnees->Add(donnees);
}
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::entreTrait(void)
{
	CL_QrDon *donnees;
	donnees=new CL_QrDon(QRTRAIT);
	LstDonnees->Add(donnees);
}

//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::QRNeedData(TObject *Sender,
		bool &MoreData)
{
	/*
	 if(LstVal->Count<LaGrille->ColCount)  //030103
	 {
	 ShowMessage("Trop de colonnes");
	 MoreData=false;
	 return;
	 }
	 */
	MoreData=CompleteDonnees();
}
//---------------------------------------------------------------------------
bool __fastcall TQRSortieValFrm::CompleteDonnees(void)
{
	CL_QrDon *donnees;

//    if(NLigne==LstDonnees->Count-1) return false;
	if(NLigne>=LstDonnees->Count) return false;
	//enum {QRDON,QRBIL,QRTITRE,QRTITRE1,QRBLANC};

	donnees=(CL_QrDon*)LstDonnees->Items[NLigne];
	switch(donnees->Type)
	{
		case QRDON:
		case QRTITRE:
		case QRTITRE1:
		AffDonnees(donnees);break;

		case QRBIL: AffBilan (donnees);break;
		case QRBLANC: AffBlanc(); break;
		case QRTRAIT: AffTrait(); break;
		default:
		ShowMessage("Oubli Complete Donnees");
	}
	NLigne++;
	return true;
}
//affiche à parir de colonne 1
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::AffDonnees(CL_QrDon *donnees)
{
	TQRLabel *tqr;
//int nColonne;
	int i,j;
	int digits=ResultatFrm->Digits;

//    nColonne=QR->Tag;
	DetailBand1->Frame->DrawTop=false;

	IntituleP->Caption=donnees->Nom;

	IntituleP->Left=donnees->PosNom;
	IntituleP->Font->Color=donnees->Couleur;

	if(donnees->AvecTrait==true)
	DetailBand1->Frame->DrawTop=true;

	if(donnees->Val==NULL)
	{
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

		for(i=1,j=0;i<11;i++,j++)
		{
			tqr=(TQRLabel*)LstCaption->Items[i];
			tqr->Font->Color=donnees->Couleur;
			if(donnees->Val[j]==0)
			tqr->Caption="";
			else
			tqr->Caption=FloatToStrF((double) donnees->Val[j],ffNumber,7,digits);
		}
	}
}
//affiche à partir de colonne 0
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::AffBilan(CL_QrDon *donnees)
{
	TQRLabel *tqr;
	int nColonne;
	int digits=ResultatFrm->Digits;
//    nColonne=QR->Tag;
	nColonne=11;

	DetailBand1->Frame->DrawTop=false;

	IntituleP->Caption=donnees->Nom;
	IntituleP->Left=donnees->PosNom
	;
	IntituleP->Font->Color=donnees->Couleur;

	if(donnees->AvecTrait==true)
	DetailBand1->Frame->DrawTop=true;

	if(donnees->Val==NULL)
	{
		for(int i=0;i<11;i++)
		{
			tqr=(TQRLabel*)LstCaption->Items[i];
			//tqr->Font->Color=donnees->Couleur;
			tqr->Caption="";
		}
	}
	else
	{
		tqr=(TQRLabel*)LstCaption->Items[0];
		tqr->Font->Color=donnees->Couleur;
		tqr->Caption="";
		for(int i=0;i<11;i++)
		{
			tqr=(TQRLabel*)LstCaption->Items[i];
			tqr->Font->Color=donnees->Couleur;
			if(donnees->Val[i]==0)
			tqr->Caption="";
			else
			tqr->Caption=FloatToStrF((double) donnees->Val[i],ffNumber,7,digits);
		}
	}
	if(nColonne==10)
	Val10->Caption="";
}
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::AffBlanc(void)
{
	TQRLabel *tqr;
	DetailBand1->Frame->DrawTop=false;

	IntituleP->Caption="";
	for(int i=0;i<11;i++)
	{
		tqr=(TQRLabel*)LstCaption->Items[i];
		tqr->Caption="";
	}
}
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::AffTrait(void)
{
	TQRLabel *tqr;
	DetailBand1->Frame->DrawTop=true;

	IntituleP->Caption="";
	for(int i=0;i<11;i++)
	{
		tqr=(TQRLabel*)LstCaption->Items[i];
		tqr->Caption="";
	}
}
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::QRBeforePrint(TCustomQuickRep *Sender,
		bool &PrintReport)
{
	NLigne=0;
	PrintReport=true;
}
//---------------------------------------------------------------------------
void __fastcall TQRSortieValFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	ShowMessage("QRSortieValFrm Je ferme");
}
//---------------------------------------------------------------------------
void TQRSortieValFrm::TexteChaine(void) {
	L_1 = T->TrouveTexte("QRSortieValFrm", "L_1");
	L_2 = T->TrouveTexte("QRSortieValFrm", "L_2");
	L_3 = T->TrouveTexte("QRSortieValFrm", "L_3");
	L_4 = T->TrouveTexte("QRSortieValFrm", "L_4");
	L_5 = T->TrouveTexte("QRSortieValFrm", "L_5");
	L_6 = T->TrouveTexte("QRSortieValFrm", "L_6");
	L_7 = T->TrouveTexte("QRSortieValFrm", "L_7");
	L_8 = T->TrouveTexte("QRSortieValFrm", "L_8");
	L_9 = T->TrouveTexte("QRSortieValFrm", "L_9");
	L_10 = T->TrouveTexte("QRSortieValFrm", "L_10");
	L_11 = T->TrouveTexte("QRSortieValFrm", "L_11");
	L_12 = T->TrouveTexte("QRSortieValFrm", "L_12");
	L_13 = T->TrouveTexte("QRSortieValFrm", "L_13");
	L_14 = T->TrouveTexte("QRSortieValFrm", "L_14");
	L_15 = T->TrouveTexte("QRSortieValFrm", "L_15");
	L_16 = T->TrouveTexte("QRSortieValFrm", "L_16");
	L_17 = T->TrouveTexte("QRSortieValFrm", "L_17");
	L_18 = T->TrouveTexte("QRSortieValFrm", "L_18");
	L_19 = T->TrouveTexte("QRSortieValFrm", "L_19");
	L_20 = T->TrouveTexte("QRSortieValFrm", "L_20");
	L_21 = T->TrouveTexte("QRSortieValFrm", "L_21");
	L_22 = T->TrouveTexte("QRSortieValFrm", "L_22");
	L_23 = T->TrouveTexte("QRSortieValFrm", "L_23");
	L_24 = T->TrouveTexte("QRSortieValFrm", "L_24");
	L_25 = T->TrouveTexte("QRSortieValFrm", "L_25");
	L_26 = T->TrouveTexte("QRSortieValFrm", "L_26");
	L_27 = T->TrouveTexte("QRSortieValFrm", "L_27");
	L_28 = T->TrouveTexte("QRSortieValFrm", "L_28");
	L_29 = T->TrouveTexte("QRSortieValFrm", "L_29");
	L_30 = T->TrouveTexte("QRSortieValFrm", "L_30");
	L_31 = T->TrouveTexte("QRSortieValFrm", "L_31");
	L_32 = T->TrouveTexte("QRSortieValFrm", "L_32");
	L_33 = T->TrouveTexte("QRSortieValFrm", "L_33");
	L_34 = T->TrouveTexte("QRSortieValFrm", "L_34");
	L_35 = T->TrouveTexte("QRSortieValFrm", "L_35");
	L_36 = T->TrouveTexte("QRSortieValFrm", "L_36");
	L_37 = T->TrouveTexte("QRSortieValFrm", "L_37");
	L_38 = T->TrouveTexte("QRSortieValFrm", "L_38");
	L_39 = T->TrouveTexte("QRSortieValFrm", "L_39");
	L_40 = T->TrouveTexte("QRSortieValFrm", "L_40");
	L_41 = T->TrouveTexte("QRSortieValFrm", "L_41");
	L_42 = T->TrouveTexte("QRSortieValFrm", "L_42");
	L_43 = T->TrouveTexte("QRSortieValFrm", "L_43");
	L_44 = T->TrouveTexte("QRSortieValFrm", "L_44");
	L_45 = T->TrouveTexte("QRSortieValFrm", "L_45");
	L_46 = T->TrouveTexte("QRSortieValFrm", "L_46");
	L_47 = T->TrouveTexte("QRSortieValFrm", "L_47");
	L_48 = T->TrouveTexte("QRSortieValFrm", "L_48");
	L_49 = T->TrouveTexte("QRSortieValFrm", "L_49");
	L_50 = T->TrouveTexte("QRSortieValFrm", "L_50");
	L_51 = T->TrouveTexte("QRSortieValFrm", "L_51");
	L_52 = T->TrouveTexte("QRSortieValFrm", "L_52");
	L_53 = T->TrouveTexte("QRSortieValFrm", "L_53");
	L_54 = T->TrouveTexte("QRSortieValFrm", "L_54");
	L_55 = T->TrouveTexte("QRSortieValFrm", "L_55");
	L_56 = T->TrouveTexte("QRSortieValFrm", "L_56");
	L_57 = T->TrouveTexte("QRSortieValFrm", "L_57");
	L_58 = T->TrouveTexte("QRSortieValFrm", "L_58");
	L_59 = T->TrouveTexte("QRSortieValFrm", "L_59");
	L_60 = T->TrouveTexte("QRSortieValFrm", "L_60");
	L_61 = T->TrouveTexte("QRSortieValFrm", "L_61");
	L_62 = T->TrouveTexte("QRSortieValFrm", "L_62");
	L_63 = T->TrouveTexte("QRSortieValFrm", "L_63");
	L_64 = T->TrouveTexte("QRSortieValFrm", "L_64");
	L_65 = T->TrouveTexte("QRSortieValFrm", "L_65");
	L_66 = T->TrouveTexte("QRSortieValFrm", "L_66");
	L_67 = T->TrouveTexte("QRSortieValFrm", "L_67");
	L_68 = T->TrouveTexte("QRSortieValFrm", "L_68");
	L_69 = T->TrouveTexte("QRSortieValFrm", "L_69");
	L_70 = T->TrouveTexte("QRSortieValFrm", "L_70");
	L_71 = T->TrouveTexte("QRSortieValFrm", "L_71");
	L_72 = T->TrouveTexte("QRSortieValFrm", "L_72");
	L_73 = T->TrouveTexte("QRSortieValFrm", "L_73");
	L_74 = T->TrouveTexte("QRSortieValFrm", "L_74");
	L_75 = T->TrouveTexte("QRSortieValFrm", "L_75");
	L_76 = T->TrouveTexte("QRSortieValFrm", "L_76");
	L_77 = T->TrouveTexte("QRSortieValFrm", "L_77");
	L_78 = T->TrouveTexte("QRSortieValFrm", "L_78");
	L_79 = T->TrouveTexte("QRSortieValFrm", "L_79");
	L_80 = T->TrouveTexte("QRSortieValFrm", "L_80");
	L_81 = T->TrouveTexte("QRSortieValFrm", "L_81");
	L_82 = T->TrouveTexte("QRSortieValFrm", "L_82");
	L_83 = T->TrouveTexte("QRSortieValFrm", "L_83");
	L_84 = T->TrouveTexte("QRSortieValFrm", "L_84");
	L_85 = T->TrouveTexte("QRSortieValFrm", "L_85");
	L_86 = T->TrouveTexte("QRSortieValFrm", "L_86");
	L_87 = T->TrouveTexte("QRSortieValFrm", "L_87");
	L_88 = T->TrouveTexte("QRSortieValFrm", "L_88");
	L_89 = T->TrouveTexte("QRSortieValFrm", "L_89");
	L_90 = T->TrouveTexte("QRSortieValFrm", "L_90");
	L_91 = T->TrouveTexte("QRSortieValFrm", "L_91");
	L_92 = T->TrouveTexte("QRSortieValFrm", "L_92");
	L_93 = T->TrouveTexte("QRSortieValFrm", "L_93");
	L_94 = T->TrouveTexte("QRSortieValFrm", "L_94");
	L_95 = T->TrouveTexte("QRSortieValFrm", "L_95");
	L_96 = T->TrouveTexte("QRSortieValFrm", "L_96");
	L_97 = T->TrouveTexte("QRSortieValFrm", "L_97");
	L_98 = T->TrouveTexte("QRSortieValFrm", "L_98");
	L_99 = T->TrouveTexte("QRSortieValFrm", "L_99");
	L_100 = T->TrouveTexte("QRSortieValFrm", "L_100");
	L_101 = T->TrouveTexte("QRSortieValFrm", "L_101");
	L_102 = T->TrouveTexte("QRSortieValFrm", "L_102");
	L_103 = T->TrouveTexte("QRSortieValFrm", "L_103");
	L_104 = T->TrouveTexte("QRSortieValFrm", "L_104");
	L_105 = T->TrouveTexte("QRSortieValFrm", "L_105");
	L_106 = T->TrouveTexte("QRSortieValFrm", "L_106");
	L_107 = T->TrouveTexte("QRSortieValFrm", "L_107");
	L_108 = T->TrouveTexte("QRSortieValFrm", "L_108");
	L_109 = T->TrouveTexte("QRSortieValFrm", "L_109");
	L_110 = T->TrouveTexte("QRSortieValFrm", "L_110");
	L_111 = T->TrouveTexte("QRSortieValFrm", "L_111");
	L_112 = T->TrouveTexte("QRSortieValFrm", "L_112");
	L_113 = T->TrouveTexte("QRSortieValFrm", "L_113");
	L_114 = T->TrouveTexte("QRSortieValFrm", "L_114");
	L_115 = T->TrouveTexte("QRSortieValFrm", "L_115");
	L_116 = T->TrouveTexte("QRSortieValFrm", "L_116");
	L_117 = T->TrouveTexte("QRSortieValFrm", "L_117");
	L_118 = T->TrouveTexte("QRSortieValFrm", "L_118");
	L_119 = T->TrouveTexte("QRSortieValFrm", "L_119");
	L_120 = T->TrouveTexte("QRSortieValFrm", "L_120");
	L_121 = T->TrouveTexte("QRSortieValFrm", "L_121");
	L_122 = T->TrouveTexte("QRSortieValFrm", "L_122");
	L_123 = T->TrouveTexte("QRSortieValFrm", "L_123");
	L_124 = T->TrouveTexte("QRSortieValFrm", "L_124");
	L_125 = T->TrouveTexte("QRSortieValFrm", "L_125");
	L_126 = T->TrouveTexte("QRSortieValFrm", "L_126");
	L_127 = T->TrouveTexte("QRSortieValFrm", "L_127");
	L_128 = T->TrouveTexte("QRSortieValFrm", "L_128");

	L_AnnuInt = T->TrouveTexte("QRSortieValFrm", "L_AnnuInt");
	L_NouvEmpLT = T->TrouveTexte("QRSortieValFrm", "L_NouvEmpLT");
	L_CapDuLT = T->TrouveTexte("QRSortieValFrm", "L_CapDuLT");
}

/*
 //---------------------------------------------------------------------------
 void TQRSortieValFrm::Francais(void)
 {
 L_1=  "Synthèse Economique";
 L_2=  "Compte de Résultat";
 L_3=  "Bilan";
 L_4=  "Privé";
 L_5=  "Recettes Dépenses";
 L_6=  "Calcul Tva";
 L_7=  "Finances";
 L_8=  "Immobilisations";
 L_9=  "Pérennes Eléments comptables";
 L_10=  "Animaux Recettes Dépenses";
 L_11=  "Oubli dans Prepare";
 L_12=  "Chiffre d'affaire";
 L_13=  "MARGE";
 L_14=  "EBE ";
 L_15=  "CAF ";
 L_16=  "SOLDE";
 L_17=  "SOLDE CUMULE";
 L_18=  "Produits Ceg";
 L_19=  "Résultat Ceg";
 L_20=  "Amortissement Immo";
 L_21=  "Amortissement Plantation";
 L_22=  "Produits";
 L_23=  "Recettes";
 L_24=  "Recettes Diverses";
 L_25=  "Var. Stock";
 L_26=  "Var. stock en terre";
 L_27=  ".  Variation valeur plantation";
 L_28=  "Var. inv animal Repro";
 L_29=  "                Autre";
 L_30=  "Produits financiers";
 L_31=  "Production d'immo";
 L_32=  "Cession d'actif";
 L_33=  "Perte Exceptionnelle";
 L_34=  "Amortissement Subvention";
 L_35=  "Charges";
 L_36=  "Dépenses Exploitation";
 L_37=  "Dépenses Diverses";
 L_38=  "Val comptable cession";
 L_39=  "Charges de Structure";
 L_40=  "Frais fin LT";
 L_41=  "Frais fin CT";
 L_42=  "Frais fin OCCC";
 L_43=  "Autres Ch Struct";
 L_44=  "Résultat";
 L_45=  "EBE test";
 L_46=  "CAF test";
 L_47=  "aaaaaaaa";
 L_48=  "ACTIF";
 L_49=  "+ Apports ";
 L_50=  "- Prélevements";
 L_51=  "+ Production d'immo";
 L_52=  "+ Produits financiers";
 L_53=  "- Remboursement LT";
 L_54=  "- Remboursement CT";
 L_55=  "- Frais fin LT";
 L_56=  "- Frais fin CT";
 L_57=  "- Placements";
 L_58=  "Solde Privé";
 L_59=  "TOTAL Recettes Produits";
 L_60=  "TOTAL Charges opérationnelles";
 L_61=  "TOTAL Structure";
 L_62=  "TOTAL Recettes Diverses";
 L_63=  "TOTAL Dépenses Diverses";
 L_64=  "Recettes Familiales";
 L_65=  "TOTAL Recettes Familiales";
 L_66=  "Dépenses Familiales";
 L_67=  "TOTAL Dépenses Familiales";
 L_68=  "Subventions";
 L_69=  "Créances et Dettes";
 L_70=  "Créances";
 L_71=  "Dettes";
 L_72=  "Tva";
 L_73=  "Solde Tva";
 L_74=  "Trésorerie Initiale";
 L_75=  "total";
 L_76=  "Vente d'Animaux";
 L_77=  "Achat d'Animaux";
 L_78=  "SOLDE ventes-achats";
 L_79=  "Ventes d'animaux";
 L_80=  "Achats d'animaux";
 L_81=  "Immobilisation";
 L_82=  "Achat";
 L_83=  "Vente";
 L_84=  "Achat-Vente";
 L_85=  "Emprunts";
 L_86=  "Emprunt";
 L_87=  "Remboursement";
 L_88=  "Interet";
 L_89=  "net";
 L_90=  "Placements";
 L_91=  "Placé";
 L_92=  "Disponible";
 L_93=  "TOTAL Dépenses Charges";
 L_94=  "Encaissé";
 L_95=  "Versé";
 L_96=  "Acompte Fevrier";
 L_97=  "Régularisation ";
 L_98=  "Acompte Mai";
 L_99=  "Acompte Aout";
 L_100=  "Acompte Novembre";
 L_101=  "Solde";
 L_102=  "Emprunt Long Terme";
 L_103=  "Emprunt Court Terme";
 L_104=  "OCCC";
 L_105=  "Frais Occc";
 L_106=  "RECAPITULATION";
 L_107=  "Subvention";
 L_108=  "Amortissement";
 L_109=  "à amortir";
 L_110=  "Placement";
 L_111=  "Rentrée";
 L_112=  "Intérêt";
 L_113=  "Créance";
 L_114=  "Capital";
 L_115=  "Annuité";   //Versement";
 L_116=  "  Capital";//Remboursement";
 L_117=  "  Intérêt";
 L_118=  "Dette";
 L_119=  "Petit Matériel";
 L_120=  "Autres Immobilisations";
 L_121=  "Valeur Résiduelle";
 L_122=  "Production d'immobilisation";
 L_123=  "Plus Value";
 L_124=  "Moins Value";
 L_125=  "Valeur Plantations";
 L_126=  "Prod Immo";
 L_127=  "Prod Immo famille";
 }
 //---------------------------------------------------------------------------
 void TQRSortieValFrm::Anglais(void)
 {
 L_1=  "Economical Synthesis";
 L_2=  "Profit and Loss Account";
 L_3=  "balance sheet";
 L_4=  "Private";
 L_5=  "Incomes Expenses";
 L_6=  "Vat calculation";
 L_7=  "Finance";
 L_8=  "Fixed Assets";
 L_9=  "Tree crops accounting Items";
 L_10=  "Animals Incomes Expenses";
 L_11=  "Missing item in Planning";
 L_12=  "Sales";
 L_13=  "MARGIN";
 L_14=  "EBE ";
 L_15=  "CAF ";
 L_16=  "BALANCE";
 L_17=  "ADDED BALANCE";
 L_18=  "Products Ceg";
 L_19=  "Results  Ceg";
 L_20=  "Fixed Ass. Depreciation";
 L_21=  "Land Depreciation";
 L_22=  "Products";
 L_23=  "Incomes";
 L_24=  "Misc. Incomes";
 L_25=  "Stock Var.";
 L_26=  "Land stock Var.";
 L_27=  ".  Land value Variation";
 L_28=  "Var. No animal Breeder";
 L_29=  "               Other";
 L_30=  "Fin. Products";
 L_31=  "Fix. Ass. Outputs";
 L_32=  "Transfer of assets";
 L_33=  "Exceptional Losses";
 L_34=  "Depreciation Grant";
 L_35=  "Costs";
 L_36=  "Farm Expenses";
 L_37=  "Misc. Expenses";
 L_38=  "Transfer of Account Val.";
 L_39=  "Fixed Asset Costs";
 L_40=  "LT Fin. Cost";
 L_41=  "ST Fin. Cost";
 L_42=  "OCCC Fin. Cost";
 L_43=  "Other Fixed Costs";
 L_44=  "Result";
 L_45=  "EBE test";
 L_46=  "CAF test";
 L_47=  "aaaaaaaa";
 L_48=  "ASSETS";
 L_49=  "+ Inputs ";
 L_50=  "- Deductions";
 L_51=  "+ fixed assets";
 L_52=  "+ Fin. Products";
 L_53=  "- LT Reimbursment";
 L_54=  "- ST Reimbursment";
 L_55=  "- LT Fin. costs";
 L_56=  "- ST Fin. costs";
 L_57=  "- Investments";
 L_58=  "Private Balance";
 L_59=  "TOTAL Product Incomes";
 L_60=  "TOTAL Operational Costs";
 L_61=  "TOTAL Fixed Assets";
 L_62=  "TOTAL Misc. Incomes";
 L_63=  "TOTAL Misc. Expenses";
 L_64=  "Family Incomes";
 L_65=  "TOTAL Family Incomes";
 L_66=  "Family Expenses";
 L_67=  "TOTAL Family Expenses";
 L_68=  "Grants";
 L_69=  "Loans and Debts";
 L_70=  "Loans";
 L_71=  "Debts";
 L_72=  "Vat";
 L_73=  "Vat Balance";
 L_74=  "Initial Treasury";
 L_75=  "Total";
 L_76=  "Animals Sold";
 L_77=  "Animals bought";
 L_78=  "BALANCE sales-buying";
 L_79=  "Animals Sales";
 L_80=  "Animals Buying";
 L_81=  "Fixed Assets";
 L_82=  "Buying";
 L_83=  "Sale";
 L_84=  "Buying-Sales";
 L_85=  "Loans";
 L_86=  "Loan";
 L_87=  "Reimbursment";
 L_88=  "Interest";
 L_89=  "net";
 L_90=  "Investments";
 L_91=  "Invested";
 L_92=  "Available";
 L_93=  "TOTAL Expenses Costs";
 L_94=  "Received";
 L_95=  "Paid";
 L_96=  "Account February";
 L_97=  "Adjustment ";
 L_98=  "Account May";
 L_99=  "Account August";
 L_100=  "Account Novembere";
 L_101=  "Balance";
 L_102=  "Long Term Loan";
 L_103=  "Short Term Loan";
 L_104=  "OCCC";
 L_105=  "Occc costs";
 L_106=  "RECAP";
 L_107=  "Grant";
 L_108=  "Depreciation";
 L_109=  "To pay off";
 L_110=  "Investment";
 L_111=  "Input";
 L_112=  "Interest";
 L_113=  "Credit";
 L_114=  "Capital";
 L_115=  "Payment";
 L_116=  "  Reimbursment";
 L_117=  "  Interest";
 L_118=  "Debt";
 L_119=  "Small equipments";
 L_120=  "Other Fixed Assets";
 L_121=  "Residual value";
 L_122=  "Fixed Assets Production";
 L_123=  "SurPlus";
 L_124=  "Depreciation";
 L_125=  "Trees Value";
 L_126=  "Fix.Ass. Prod.";
 L_127=  "Family Fix.Ass. Prod.";

 }


 */

//--------------------------------------------
void TQRSortieValFrm::IniCaption(void) {
	IntituleP->Caption = T->LC_IntituleP;
	LabAn0->Caption = LC_LabAn0;
	LabAn1->Caption = LC_LabAn1;
	LabAn10->Caption = LC_LabAn10;
	LabAn2->Caption = LC_LabAn2;
	LabAn3->Caption = LC_LabAn3;
	LabAn4->Caption = LC_LabAn4;
	LabAn5->Caption = LC_LabAn5;
	LabAn6->Caption = LC_LabAn6;
	LabAn7->Caption = LC_LabAn7;
	LabAn8->Caption = LC_LabAn8;
	LabAn9->Caption = LC_LabAn9;
	NomAgri->Caption = T->LC_NomAgri;
	QRSortieValFrm->Caption = LC_QRSortieValFrm;
	TitreEtat->Caption = T->LC_TitreEtat;
	UniteMonnaie->Caption = T->LC_UniteMonnaie;
	Val0->Caption = T->LC_Val0;
	Val1->Caption = T->LC_Val1;
	Val10->Caption = T->LC_Val10;
	Val2->Caption = T->LC_Val2;
	Val3->Caption = T->LC_Val3;
	Val4->Caption = T->LC_Val4;
	Val5->Caption = T->LC_Val5;
	Val6->Caption = T->LC_Val6;
	Val7->Caption = T->LC_Val7;
	Val8->Caption = T->LC_Val8;
	Val9->Caption = T->LC_Val9;
	ValeurEn->Caption = T->LC_ValeurEn;
}
//--------------------------------------------
void TQRSortieValFrm::TexteCaption(void) {
	LC_IntituleP = T->TrouveCaption("CL_Trad", "LC_IntituleP");
	LC_LabAn0 = T->TrouveCaption("QRSortieVal", "LC_LabAn0");
	LC_LabAn1 = T->TrouveCaption("QRSortieVal", "LC_LabAn1");
	LC_LabAn10 = T->TrouveCaption("QRSortieVal", "LC_LabAn10");
	LC_LabAn2 = T->TrouveCaption("QRSortieVal", "LC_LabAn2");
	LC_LabAn3 = T->TrouveCaption("QRSortieVal", "LC_LabAn3");
	LC_LabAn4 = T->TrouveCaption("QRSortieVal", "LC_LabAn4");
	LC_LabAn5 = T->TrouveCaption("QRSortieVal", "LC_LabAn5");
	LC_LabAn6 = T->TrouveCaption("QRSortieVal", "LC_LabAn6");
	LC_LabAn7 = T->TrouveCaption("QRSortieVal", "LC_LabAn7");
	LC_LabAn8 = T->TrouveCaption("QRSortieVal", "LC_LabAn8");
	LC_LabAn9 = T->TrouveCaption("QRSortieVal", "LC_LabAn9");
	LC_NomAgri = T->TrouveCaption("CL_Trad", "LC_NomAgri");
	LC_QRSortieValFrm = T->TrouveCaption("QRSortieVal", "LC_QRSortieValFrm");
	LC_TitreEtat = T->TrouveCaption("CL_Trad", "LC_TitreEtat");
	LC_UniteMonnaie = T->TrouveCaption("CL_Trad", "LC_UniteMonnaie");
	LC_Val0 = T->TrouveCaption("CL_Trad", "LC_Val0");
	LC_Val1 = T->TrouveCaption("CL_Trad", "LC_Val1");
	LC_Val10 = T->TrouveCaption("CL_Trad", "LC_Val10");
	LC_Val2 = T->TrouveCaption("CL_Trad", "LC_Val2");
	LC_Val3 = T->TrouveCaption("CL_Trad", "LC_Val3");
	LC_Val4 = T->TrouveCaption("CL_Trad", "LC_Val4");
	LC_Val5 = T->TrouveCaption("CL_Trad", "LC_Val5");
	LC_Val6 = T->TrouveCaption("CL_Trad", "LC_Val6");
	LC_Val7 = T->TrouveCaption("CL_Trad", "LC_Val7");
	LC_Val8 = T->TrouveCaption("CL_Trad", "LC_Val8");
	LC_Val9 = T->TrouveCaption("CL_Trad", "LC_Val9");
	LC_ValeurEn = T->TrouveCaption("CL_Trad", "LC_ValeurEn");

	IniCaption();

}
//--------------------------------------------

