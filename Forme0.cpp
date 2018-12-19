//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <checklst.hpp>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "LesVecteurs.hse"
#include "FichierLire.h"

#include "Tableur.h"
#include "SysUnite.h"
#include "AgriSaisie.h"
#include "Tendance.h"
#include "Ensemble.h"
#include "TVDico.h"
#include "CL_Procedure.h"
#include "Main.h"
#include "CL_Trad.h"
#pragma hdrstop

#include "Forme0.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForme0Frm *Forme0Frm;

extern CL_ES *ES;
extern CL_Excel *EX;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TForme0Frm::TForme0Frm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TForme0Frm::FormCreate(TObject *Sender)
{
	memset(ValZero,0,sizeof(float)*N_X);
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForme0Frm::BoutImpEcranClick(TObject *Sender)
{
	Print();
}
//---------------------------------------------------------------------------
void __fastcall TForme0Frm::BtBnQuitterClick(TObject *Sender)
{
	int rep;
	rep=MessageBox(Handle,T->L_QuitQ.c_str(),T->L_QuitT.c_str(),
			MB_YESNO|MB_ICONEXCLAMATION);
//	rep=MessageBox(Handle,"Vous voulez vraiment quitter","QUITTER OLYMPE",

	if(rep==IDYES) Application->Terminate();

	else return;
}
//---------------------------------------------------------------------------
float __fastcall TForme0Frm::ValeurDe(AnsiString s)
{
	int c;
	int n;
	char car;
	char chaine[50];
	s=s.Trim();
	if(s=="" ||s==" ") return 0.;
	c=0;
	for(n=1;n<s.Length()+1;n++)
	{
		car=s[n];
		if (car>='0' && car<='9') chaine[c++] =car;
		else if(car=='.' || car==',') chaine[c++] ='.';
		else if(car=='-' && c==0) chaine[c++] ='-';
	}
	chaine[c]=0;
	s=AnsiString(chaine);
	return s.ToDouble();

}
//int nbCar   pour définir combien de caractere à faire si nécessaire
//---------------------------------------------------------------------------
AnsiString __fastcall TForme0Frm::NomMois(int n, int nbCar) {
	AnsiString nom;
	return LongMonthNames[n - 1];
	/*
	 switch(MainForm->Langue)
	 {
	 case'F':
	 switch(n)
	 {
	 case 1:nom="Janvier";break;
	 case 2:nom="Février";break;
	 case 3:nom="Mars";break;
	 case 4:nom="Avril";break;
	 case 5:nom="Mai";break;
	 case 6:nom="Juin";break;
	 case 7:nom="Juillet";break;
	 case 8:nom="Aout";break;
	 case 9:nom="Septembre";break;
	 case 10:nom="Octobre";break;
	 case 11:nom="Novembre";break;
	 case 12:nom="Décembre";break;
	 }
	 break;
	 case'E':
	 switch(n)
	 {
	 case 1:nom="January";break;
	 case 2:nom="Februar";break;
	 case 3:nom="March";break;
	 case 4:nom="April";break;
	 case 5:nom="May";break;
	 case 6:nom="June";break;
	 case 7:nom="July";break;
	 case 8:nom="August";break;
	 case 9:nom="September";break;
	 case 10:nom="October";break;
	 case 11:nom="November";break;
	 case 12:nom="December";break;
	 }
	 break;
	 }
	 return nom;
	 */
}
//---------------------------------------------------------------------------
// ligne
//////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// INI ListBox
//---------------------------------------------------------------------------

void __fastcall TForme0Frm::CreeLBCat(TListBox *LB,CL_Vecteur<CL_Categorie> *vecteur,
		bool avec)
{
	CL_Categorie *categorie;
	int i;
	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		categorie=vecteur->Vecteur[i];
		LB->Items->AddObject(categorie->Nom,(TObject*)categorie);
	}
	if(Forme0Frm->Nature==EXTPOS) return;
	LB->Items->AddObject("[...]",NULL);
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBUnite(TListBox *LB,CL_Vecteur<CL_SystemeUnite> *vecteur,bool avec)
{
	CL_SystemeUnite *systeme;
	int i;
	char buf[100];
//AnsiString buf;
	LB->Clear();
	LB->Font->Name="Courier New";
	for(i=0;i<vecteur->Nbelt;i++)
	{
		systeme=vecteur->Vecteur[i];
		sprintf(buf,"%-6.6s %-6.6s %-6.6s",
				systeme->UUt.c_str(),systeme->UTrans.c_str(),systeme->UGlobal.c_str());
		LB->Items->AddObject(buf,(TObject*)systeme);
	}
	if(avec==true)
	LB->Items->AddObject("[...]",NULL);

}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBTva(TListBox *LB,CL_Vecteur<CL_Tva> *vecteur,bool avec)
{
	CL_Tva *tva;
	int i;

	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		tva=vecteur->Vecteur[i];
		LB->Items->AddObject(tva->Nom,(TObject*)tva);
	}
	if(avec==true)
	LB->Items->AddObject("[...]",NULL);
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBAtelier(TListBox *LB,CL_Vecteur<CL_Atelier> *vecteur,bool avec)
{
	CL_Atelier *atelier;
	int i;

	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		atelier=vecteur->Vecteur[i];
		LB->Items->AddObject(atelier->Nom,(TObject*)atelier);
	}
	LB->Items->AddObject("[...]",NULL);
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBItem(TListBox *LB,CL_Vecteur<CL_Item> *vecteur, int noCat,bool avec)
{
	int i;
	CL_Item *item;
	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		item=vecteur->Vecteur[i];
		if(item->NoCategorie!=noCat) continue;
		LB->Items->AddObject(item->Nom,(TObject*)item);
	}
	LB->Items->AddObject("[...]",NULL);
}
//---------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBEtatSortie(TListBox *LB,CL_Vecteur<CL_EtatSortie> *vecteur)
{
	CL_EtatSortie *etat;
	int i; //,n;
	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		etat=vecteur->Vecteur[i];
		LB->Items->AddObject(etat->Nom,(TObject *)etat);
	}
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBElt(TListBox *LB,CL_Vecteur<CL_Elt> *vecteur,bool avec)
{
	CL_Elt *elt;
	int i; //,n;
	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		elt=vecteur->Vecteur[i];
		LB->Items->AddObject(elt->Nom,(TObject *)elt);
	}
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBVariable(TListBox *LB,CL_Categorie *cat,CL_Vecteur<CL_Item> *vecteur)
{
	CL_Item *variable;
	int i; //,n;
	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		variable=vecteur->Vecteur[i];
		if(variable->NoCategorie!=cat->No) continue;
		LB->Items->AddObject(variable->Nom,(TObject *)variable);
	}
	LB->Items->AddObject("[...]",NULL);
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBValeur(TListBox *LB,CL_Vecteur<CL_Valeur> *vecteur,bool avec)
{
	CL_Valeur *valeur;
	CL_Atelier *atelier;
	int i; //,n;
	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		valeur=vecteur->Vecteur[i];
		atelier=valeur->Atelier;
		LB->Items->AddObject(atelier->Nom,(TObject *)valeur);
	}
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBVerger(TListBox *LB,CL_Vecteur<CL_Verger> *vecteur,bool avec)
{
	CL_Verger *verger;
	CL_Atelier *atelier;
	int i; //,n;
	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		verger=vecteur->Vecteur[i];
		atelier=verger->Atelier;
		LB->Items->AddObject(atelier->Nom,(TObject *)verger);
	}
}
//Tendance
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBTendance(TListBox *LB,CL_Vecteur<CL_Tendance> *vecteur)
{
	CL_Tendance *tendance;
	int i; //,n;
	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		tendance=vecteur->Vecteur[i];
		LB->Items->AddObject(tendance->Nom,(TObject *)tendance);
	}
	LB->Items->AddObject("[...]",NULL);

}
//Calendrier
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBCalendrier(TListBox *LB,CL_Vecteur<CL_Calendrier> *vecteur)
{
	CL_Calendrier *calendrier;
	int i;
	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		calendrier=vecteur->Vecteur[i];
		LB->Items->AddObject(calendrier->Nom,(TObject *)calendrier);
	}
	LB->Items->AddObject("[...]",NULL);

}
//Conversion
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBConversion(TListBox *LB,CL_Vecteur<CL_Conversion> *vecteur)
{
	CL_Conversion *conversion;
	int i;
	LB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		conversion=vecteur->Vecteur[i];
		LB->Items->AddObject(conversion->Nom,(TObject *)conversion);
	}
	LB->Items->AddObject("[...]",NULL);

}
//---------------------------------------------------------------------------
// INI CheckListBox
//---------------------------------------------------------------------------

void __fastcall TForme0Frm::CreeCLBCat(TCheckListBox *CLB,CL_Vecteur<CL_Categorie> *vecteur)
{
	CL_Categorie *categorie;
	int i;
	CLB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		categorie=vecteur->Vecteur[i];
		CLB->Items->AddObject(categorie->Nom,(TObject*)categorie);
	}
}
//-----------------------------------------------------------------------------
// ControlBox
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeCBType(TComboBox *CB,CL_Vecteur<CL_Item> *vecteur,int noCat)
{
	CL_Item *type;
	int i;
	CB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		type=vecteur->Vecteur[i];
		if(type->NoCategorie!=noCat) continue;
		CB->Items->AddObject(type->Nom,(TObject*)type);
	}
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeCBEspece(TComboBox *CB,CL_Vecteur<CL_Espece> *vecteur)
{
	CL_Espece *espece;
	int i;
	CB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		espece=vecteur->Vecteur[i];
		CB->Items->AddObject(espece->Nom,(TObject *)espece);
	}
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeCBCategorie(TComboBox *CB,CL_Vecteur<CL_Categorie> *vecteur)
{
	CL_Categorie *categorie;
	int i;
	CB->Clear();
	for(i=0;i<vecteur->Nbelt;i++)
	{
		categorie=vecteur->Vecteur[i];
		CB->Items->AddObject(categorie->Nom,(TObject *)categorie);
	}
}
//-----------------------------------------------------------------------------
//   TREENODE
//              TVPerenne  TVCulture=Culture+Vivrier
//              TV V_Produit V_Charge  V_Irrigation
//-----------------------------------------------------------------------------
// AgriSaisie
//-----------------------------------------------------------------------------
// AgriSaisie
// GereAtelier
void __fastcall TForme0Frm::CreeTVAtelier( TTreeView *TV,
		CL_Vecteur<CL_Categorie> *vCat,CL_Vecteur<CL_Atelier> *vAtelier)
{
	TTreeNode *tNCat,*tNElt;
	AnsiString s;
	int i,j;
	CL_Categorie *cat;
	CL_Atelier *atelier;
	int nature;
	if (vAtelier==V_Culture) nature=CULTURE; //c'est un entier
	else if(vAtelier==V_Animaux) nature=ANIMAUX;//c'est un entier
	else if(vAtelier==V_Vivrier) nature=VIVRIER;//c'est un entier

	TV->Items->Clear();

	tNCat=new TTreeNode(TV->Items);
	for(i=0;i<vCat->Nbelt;i++)
	{
		cat=vCat->Vecteur[i];
		tNElt=TV->Items->AddObject(tNCat,cat->Nom,cat);
		for(j=0;j<vAtelier->Nbelt;j++)
		{
			atelier=vAtelier->Vecteur[j];
			if(atelier->NoCategorie==cat->No)
			{
				TV->Items->AddChildObject(tNElt,atelier->Nom,atelier);
			}
		}
		TV->Items->AddChildObject(tNElt,"[...]",(TObject*)nature);
	}
	TV->Items->AddObject(tNCat,"[...]",(TObject*)nature);

}
//-----------------------------------------------------------------------------
// AgriSaisie
// GereAtelier
void __fastcall TForme0Frm::CreeTVPerenne( TTreeView *TV,
		CL_Vecteur<CL_Espece> *vEsp,CL_Vecteur<CL_Atelier> *vPer)
{
	TTreeNode *tNEspece,*tNElt;
	AnsiString s;
	int i,j;
	CL_Espece *espece;
	CL_Atelier *perenne;

	TV->Items->Clear();

	tNEspece=new TTreeNode(TV->Items);
	for(i=0;i<vEsp->Nbelt;i++)
	{
		espece=vEsp->Vecteur[i];
		tNElt=TV->Items->AddObject(tNEspece,espece->Nom,espece);
		for(j=0;j<vPer->Nbelt;j++)
		{
			perenne=vPer->Vecteur[j];
			if(perenne->NoEspece==espece->No)
			{
				TV->Items->AddChildObject(tNElt,perenne->Nom,perenne);
			}
		}
		TV->Items->AddChildObject(tNElt,"[...]",perenne);
	}
	TV->Items->AddObject(tNEspece,"[...]",NULL);

}
//-----------------------------------------------------------------------------
// Categorie
// AgriSaisie
// GereAtelier
void __fastcall TForme0Frm::CreeTVItem( TTreeView *TV,
		CL_Vecteur<CL_Categorie> *vCat,CL_Vecteur<CL_Item> *vElt)
{
	TTreeNode *tNCategorie,*tNElt;
	AnsiString s;
	int i,j;
	CL_Categorie *categorie;
	CL_Item *item;

	TV->Items->Clear();

	tNCategorie=new TTreeNode(TV->Items);
	for(i=0;i<vCat->Nbelt;i++)
	{
		categorie=vCat->Vecteur[i];
		tNElt=TV->Items->AddObject(tNCategorie,categorie->Nom,categorie);
		for(j=0;j<vElt->Nbelt;j++)
		{
			item=vElt->Vecteur[j];
			if(item->NoCategorie==categorie->No)
			{
				TV->Items->AddChildObject(tNElt,item->Nom,item);
			}
		}
		TV->Items->AddChildObject(tNElt,"[...]",item);
	}
	TV->Items->AddObject(tNCategorie,"[...]",NULL);

}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVBestiaux( TTreeView *TV,
		CL_Vecteur<CL_Categorie> *vCat,CL_Vecteur<CL_Bestiaux> *vElt)
{
	TTreeNode *tNCategorie,*tNElt;
	AnsiString s;
	int i,j;
	CL_Categorie *categorie;
	CL_Bestiaux *bestiaux;

	TV->Items->Clear();

	tNCategorie=new TTreeNode(TV->Items);
	for(i=0;i<vCat->Nbelt;i++)
	{
		categorie=vCat->Vecteur[i];
		tNElt=TV->Items->AddObject(tNCategorie,categorie->Nom,categorie);
		for(j=0;j<vElt->Nbelt;j++)
		{
			bestiaux=vElt->Vecteur[j];
			if(bestiaux->NoCategorie==categorie->No)
			{
				TV->Items->AddChildObject(tNElt,bestiaux->Nom,bestiaux);
			}
		}
		TV->Items->AddChildObject(tNElt,"[...]",bestiaux);
	}
	TV->Items->AddObject(tNCategorie,"[...]",NULL);

}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVProduitComm(TTreeView *TV,CL_Vecteur<CL_Categorie> *vCat,
		CL_Vecteur<CL_Formule> *vFormule,CL_Vecteur<CL_StockIni> *vStockIni)
{
	TTreeNode *tNCategorie,*tNElt;
	AnsiString s;
	int i,j;
	CL_Categorie *categorie;
	CL_Formule *formule;
	CL_StockIni *stockIni;
	CL_Item *item;

	TV->Items->Clear();
	vCat->FlagMisA('N');
	V_Produit->FlagMisA('N');
	for(j=0;j<vFormule->Nbelt;j++)
	{
		formule=vFormule->Vecteur[j];
		item=formule->Item;
		item->Flag='O';
		item->Categorie->Flag='O';
	}
	for(j=0;j<vStockIni->Nbelt;j++)
	{
		stockIni=vStockIni->Vecteur[j];
		item=stockIni->Item;
		item->Flag='O';
		item->Categorie->Flag='O';
	}

	tNCategorie=new TTreeNode(TV->Items);
	for(i=0;i<vCat->Nbelt;i++)
	{
		categorie=vCat->Vecteur[i];
		if(categorie->Flag=='N') continue;

		tNElt=TV->Items->AddObject(tNCategorie,categorie->Nom,categorie);
		for(j=0;j<V_Produit->Nbelt;j++)
		{
			item=V_Produit->Vecteur[j];
			if(item->Flag=='N') continue;
			if(item->Categorie!=categorie) continue;

			TV->Items->AddChildObject(tNElt,item->Nom,item);
		}
	}
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVCreance( TTreeView *TV)
{
	TTreeNode *tNFamille,*tNCategorie,*tNElt;
	AnsiString s;
	int i,j;
	CL_Vecteur<CL_Categorie> *vCat;
	CL_Vecteur<CL_Item> *vItem;
	CL_Categorie *categorie;
	CL_Item *item;

	TV->Items->Clear();
	tNFamille=new TTreeNode(TV->Items);
	tNCategorie=TV->Items->AddObject(tNFamille,T->L_Produit,NULL);
	//tNCategorie=TV->Items->AddObject(tNFamille,"Produits",NULL);
	vCat=V_CatProduit;
	vItem=V_Produit;
	for(i=0;i<vCat->Nbelt;i++)
	{
		categorie=vCat->Vecteur[i];
		tNElt=TV->Items->AddChildObject(tNCategorie,categorie->Nom,categorie);
		for(j=0;j<vItem->Nbelt;j++)
		{
			item=vItem->Vecteur[j];
			if(item->NoCategorie==categorie->No)
			TV->Items->AddChildObject(tNElt,item->Nom,item);
		}
	}
	TV->Items->AddChildObject(tNCategorie,"[...]",T->L_Produit.c_str());

	//tNCategorie=TV->Items->AddObject(tNFamille,"Recettes Diverses",NULL);
	tNCategorie=TV->Items->AddObject(tNFamille,L_RecDiv,NULL);
	vCat=V_CatRecDiv;
	vItem=V_RecDiv;
	for(i=0;i<vCat->Nbelt;i++)
	{
		categorie=vCat->Vecteur[i];
		tNElt=TV->Items->AddChildObject(tNCategorie,categorie->Nom,categorie);
		for(j=0;j<vItem->Nbelt;j++)
		{
			item=vItem->Vecteur[j];
			if(item->NoCategorie==categorie->No)
			TV->Items->AddChildObject(tNElt,item->Nom,item);
		}
	}
	TV->Items->AddChildObject(tNCategorie,"[...]","RecDiv");

}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVDette ( TTreeView *TV)
{
	TTreeNode *tNFamille,*tNCategorie,*tNElt;
	AnsiString s;
	int i,j;
	CL_Vecteur<CL_Categorie> *vCat;
	CL_Vecteur<CL_Item> *vItem;
	CL_Categorie *categorie;
	CL_Item *item;

	TV->Items->Clear();
	tNFamille=new TTreeNode(TV->Items);
	tNCategorie=TV->Items->AddObject(tNFamille,T->L_Charge,NULL);
	//tNCategorie=TV->Items->AddObject(tNFamille,"Charges",NULL);
	vCat=V_CatCharge;
	vItem=V_Charge;
	for(i=0;i<vCat->Nbelt;i++)
	{
		categorie=vCat->Vecteur[i];
		tNElt=TV->Items->AddChildObject(tNCategorie,categorie->Nom,categorie);
		for(j=0;j<vItem->Nbelt;j++)
		{
			item=vItem->Vecteur[j];
			if(item->NoCategorie==categorie->No)
			TV->Items->AddChildObject(tNElt,item->Nom,item);
		}
	}
	TV->Items->AddChildObject(tNCategorie,"[...]",T->L_Charge.c_str());
	//TV->Items->AddChildObject(tNCategorie,"[...]","Charges");

	tNCategorie=TV->Items->AddObject(tNFamille,T->L_ChStruct,NULL);
	//tNCategorie=TV->Items->AddObject(tNFamille,"Charges Structure",NULL);
	vCat= V_CatChStruct;
	vItem=V_ChStruct;
	for(i=0;i<vCat->Nbelt;i++)
	{
		categorie=vCat->Vecteur[i];
		tNElt=TV->Items->AddChildObject(tNCategorie,categorie->Nom,categorie);
		for(j=0;j<vItem->Nbelt;j++)
		{
			item=vItem->Vecteur[j];
			if(item->NoCategorie==categorie->No)
			TV->Items->AddChildObject(tNElt,item->Nom,item);
		}
	}
	TV->Items->AddChildObject(tNCategorie,"[...]","ChStruct");

	tNCategorie=TV->Items->AddObject(tNFamille,T->L_DepDiv,NULL);
	//tNCategorie=TV->Items->AddObject(tNFamille,"Dépenses Diverses",NULL);
	vCat=V_CatDepDiv;
	vItem=V_DepDiv;
	for(i=0;i<vCat->Nbelt;i++)
	{
		categorie=vCat->Vecteur[i];
		tNElt=TV->Items->AddChildObject(tNCategorie,categorie->Nom,categorie);
		for(j=0;j<vItem->Nbelt;j++)
		{
			item=vItem->Vecteur[j];
			if(item->NoCategorie==categorie->No)
			TV->Items->AddChildObject(tNElt,item->Nom,item);
		}
	}
	TV->Items->AddChildObject(tNCategorie,"[...]","DepDiv");

}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVIndicateur(TTreeView *TV)
{
	TTreeNode *tNCategorie,*tNElt;
	CL_Indicateur *indic;
	CL_Categorie *categorie;

	TV->Items->Clear();

	tNCategorie=new TTreeNode(TV->Items);
	for(int i=0;i<V_CatIndic->Nbelt;i++)
	{
		categorie=V_CatIndic->Vecteur[i];
		tNElt=TV->Items->AddObject(tNCategorie,categorie->Nom,categorie);
		for(int j=0;j<V_Indicateur->Nbelt;j++)
		{
			indic=V_Indicateur->Vecteur[j];
			if(indic->NoCategorie==categorie->No)
			{
				TV->Items->AddChildObject(tNElt,indic->Nom,indic);
			}
		}
		TV->Items->AddChildObject(tNElt,"[...]",NULL);
	}
	TV->Items->AddObject(tNCategorie,"[...]",NULL);
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVEtat(TTreeView *TV,
		CL_Vecteur<CL_Categorie> *vCat,CL_Vecteur<CL_EtatSortie> *vEtat)

{
	TTreeNode *tNCategorie,*tNElt;
	CL_EtatSortie *etat;
	CL_Categorie *categorie;

	TV->Items->Clear();

	tNCategorie=new TTreeNode(TV->Items);
	for(int i=0;i<vCat->Nbelt;i++)
	{
		categorie=vCat->Vecteur[i];
		tNElt=TV->Items->AddObject(tNCategorie,categorie->Nom,categorie);
		for(int j=0;j<vEtat->Nbelt;j++)
		{
			etat=vEtat->Vecteur[j];
			if(etat->NoCategorie==categorie->No)
			{
				TV->Items->AddChildObject(tNElt,etat->Nom,etat);
			}
		}
		TV->Items->AddChildObject(tNElt,"[...]",NULL);
	}
	TV->Items->AddObject(tNCategorie,"[...]",NULL);
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVProcedure(TTreeView *TV,
		CL_Vecteur<CL_Categorie> *vCat,CL_Vecteur<CL_Procedure> *vProcedure)

{
	TTreeNode *tNCategorie,*tNElt;
	CL_Procedure *procedure;
	CL_Categorie *categorie;

	TV->Items->Clear();

	tNCategorie=new TTreeNode(TV->Items);
	for(int i=0;i<vCat->Nbelt;i++)
	{
		categorie=vCat->Vecteur[i];
		tNElt=TV->Items->AddObject(tNCategorie,categorie->Nom,categorie);
		for(int j=0;j<vProcedure->Nbelt;j++)
		{
			procedure=vProcedure->Vecteur[j];
			if(procedure->Categorie==categorie) // à mettre ailleurs plus de no
			{
				TV->Items->AddChildObject(tNElt,procedure->Nom,procedure);
			}
		}
		TV->Items->AddChildObject(tNElt,"[...]",NULL);
	}
	TV->Items->AddObject(tNCategorie,"[...]",NULL);
}
///-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVMarge(TTreeView *TV,CL_Agriculteur *agri)
{
	int i;
	TTreeNode *tNCategorie,*tNElt;
	CL_Valeur *valeur;
	CL_Atelier *atelier;
	CL_Verger *verger;
	TV->Items->Clear();
	tNCategorie=new TTreeNode(TV->Items);
	if(agri->V_Culture->Nbelt)
	{
		tNElt=TV->Items->AddObject(tNCategorie,T->L_Culture,NULL);
		//tNElt=TV->Items->AddObject(tNCategorie,"Culture",NULL);
		for(i=0;i<agri->V_Culture->Nbelt;i++)
		{
			valeur=agri->V_Culture->Vecteur[i];
			atelier=valeur->Atelier;
			atelier->Flag='N';
		}
		for(i=0;i<agri->V_Culture->Nbelt;i++)
		{
			valeur=agri->V_Culture->Vecteur[i];
			atelier=valeur->Atelier;
			if(atelier->Flag=='N')
			{
				TV->Items->AddChildObject(tNElt,atelier->Nom,atelier);
				atelier->Flag='O';
			}
		}
	}
	if(agri->V_Animaux->Nbelt)
	{
		tNElt=TV->Items->AddObject(tNCategorie,T->L_Animaux,NULL);
		//tNElt=TV->Items->AddObject(tNCategorie,"Animaux",NULL);
		for(i=0;i<agri->V_Animaux->Nbelt;i++)
		{
			valeur=agri->V_Animaux->Vecteur[i];
			atelier=valeur->Atelier;
			atelier->Flag='N';
		}
		for(i=0;i<agri->V_Animaux->Nbelt;i++)
		{
			valeur=agri->V_Animaux->Vecteur[i];
			atelier=valeur->Atelier;
			if(atelier->Flag=='N')
			{
				TV->Items->AddChildObject(tNElt,atelier->Nom,atelier);
				atelier->Flag='O';
			}
		}
	}
	if(agri->V_Verger->Nbelt)
	{
		tNElt=TV->Items->AddObject(tNCategorie,T->L_Perenne,NULL);
		//tNElt=TV->Items->AddObject(tNCategorie,"Pérenne",NULL);
		for(i=0;i<agri->V_Verger->Nbelt;i++)
		{
			verger=agri->V_Verger->Vecteur[i];
			atelier=verger->Atelier;
			atelier->Flag='N';
		}
		for(i=0;i<agri->V_Verger->Nbelt;i++)
		{
			verger=agri->V_Verger->Vecteur[i];
			atelier=verger->Atelier;
			if(atelier->Flag=='N')
			{
				TV->Items->AddChildObject(tNElt,atelier->Nom,atelier);
				atelier->Flag='O';
			}
		}
	}
	if(agri->V_Vivrier->Nbelt)
	{
		tNElt=TV->Items->AddObject(tNCategorie,T->L_Vivrier,NULL);
		//tNElt=TV->Items->AddObject(tNCategorie,"Vivrier",NULL);
		for(i=0;i<agri->V_Vivrier->Nbelt;i++)
		{
			verger=agri->V_Vivrier->Vecteur[i];
			atelier=verger->Atelier;
			atelier->Flag='N';
		}
		for(i=0;i<agri->V_Verger->Nbelt;i++)
		{
			verger=agri->V_Vivrier->Vecteur[i];
			atelier=verger->Atelier;
			if(atelier->Flag=='N')
			{
				TV->Items->AddChildObject(tNElt,atelier->Nom,atelier);
				atelier->Flag='O';
			}
		}
	}
}
//-----------------------------------------------------------------------------
// CheckListBox pour choisir les ateliers choix des ateliers
// dont les marges sont à afficher
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBMarge(TCheckListBox *ChLB,CL_Agriculteur *agri)
{
	static CL_Atelier *atelierVenteBestiaux;
	static CL_Atelier *atelierAchatBestiaux;

	int i;
	CL_Valeur *valeur;
	CL_Atelier *atelier;
	CL_Verger *verger;
	CL_Troupeau *troupeau;

	if(atelierVenteBestiaux==NULL)
	{
		atelierVenteBestiaux=new CL_Atelier();
		atelierVenteBestiaux->Nom="Vente Animaux";
		atelierVenteBestiaux->Nature=VENTE;

		atelierAchatBestiaux=new CL_Atelier();
		atelierAchatBestiaux->Nom="Achat Animaux";
		atelierAchatBestiaux->Nature=ACHAT;
	}
	ChLB->Clear();

	if(agri->V_Culture->Nbelt)
	{
		for(i=0;i<agri->V_Culture->Nbelt;i++)
		{
			valeur=agri->V_Culture->Vecteur[i];
			atelier=valeur->Atelier;
			atelier->Flag='N';
		}
		for(i=0;i<agri->V_Culture->Nbelt;i++)
		{
			valeur=agri->V_Culture->Vecteur[i];
			atelier=valeur->Atelier;
			if(atelier->Flag=='N')
			{
				ChLB->Items->AddObject(atelier->Nom,(TObject*)atelier);
				atelier->Flag='O';
			}
		}
	}
	if(agri->V_Animaux->Nbelt)
	{
		for(i=0;i<agri->V_Animaux->Nbelt;i++)
		{
			valeur=agri->V_Animaux->Vecteur[i];
			atelier=valeur->Atelier;
			atelier->Flag='N';
		}
		for(i=0;i<agri->V_Animaux->Nbelt;i++)
		{
			valeur=agri->V_Animaux->Vecteur[i];
			atelier=valeur->Atelier;
			if(atelier->Flag=='N')
			{
				ChLB->Items->AddObject(atelier->Nom,(TObject*)atelier);
				atelier->Flag='O';
			}
		}
	}
	if(agri->V_Verger->Nbelt)
	{
		for(i=0;i<agri->V_Verger->Nbelt;i++)
		{
			verger=agri->V_Verger->Vecteur[i];
			atelier=verger->Atelier;
			atelier->Flag='N';
		}
		for(i=0;i<agri->V_Verger->Nbelt;i++)
		{
			verger=agri->V_Verger->Vecteur[i];
			atelier=verger->Atelier;
			if(atelier->Flag=='N')
			{
				ChLB->Items->AddObject(atelier->Nom,(TObject*)atelier);
				atelier->Flag='O';
			}
		}
	}
	if(agri->V_Vivrier->Nbelt)
	{
		for(i=0;i<agri->V_Vivrier->Nbelt;i++)
		{
			verger=agri->V_Vivrier->Vecteur[i];
			atelier=verger->Atelier;
			atelier->Flag='N';
		}
		for(i=0;i<agri->V_Vivrier->Nbelt;i++)
		{
			verger=agri->V_Vivrier->Vecteur[i];
			atelier=verger->Atelier;
			if(atelier->Flag=='N')
			{
				ChLB->Items->AddObject(atelier->Nom,(TObject*)atelier);
				atelier->Flag='O';
			}
		}
	}
	for(i=0;i<agri->LstTroupeaux->Count;i++)
	{
		troupeau=(CL_Troupeau*)agri->LstTroupeaux->Items[i];
		troupeau->CatBestiaux->Nom;
		atelier=new CL_Atelier();
		atelier->Nom=troupeau->CatBestiaux->Nom;
		atelier->Nature=BESTIAUX;
		ChLB->Items->AddObject(atelier->Nom,(TObject*)atelier);
	}

}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//  utilisé pour construire des formules
// ne comporte que les variables utilisées par l'agriculteur
// pas d'ajout possible
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVVariable( TTreeView *TV,
		CL_Vecteur<CL_Categorie> *vCat,CL_Vecteur<CL_Valeur> *vValeur)
{
	TTreeNode *tNCategorie,*tNElt;
	AnsiString s;
	int i,j;
	CL_Categorie *categorie;
	CL_Valeur *valeur;
	CL_Item *item;
	TV->Items->Clear();

	tNCategorie=new TTreeNode(TV->Items);
	for(i=0;i<vCat->Nbelt;i++)
	{
		categorie=vCat->Vecteur[i];
		tNElt=TV->Items->AddObject(tNCategorie,categorie->Nom,categorie);
		for(j=0;j<vValeur->Nbelt;j++)
		{
			valeur=vValeur->Vecteur[j];
			item=valeur->Item;
			if(item->NoCategorie==categorie->No)
			{
				TV->Items->AddChildObject(tNElt,item->Nom,item);
			}
		}
	}
}
// Variante Agri
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVVarianteAgri( TTreeView *TV,CL_Agriculteur *agri)
{
	TTreeNode *tNPere,*tNFils,*tNPetitFils;
	CL_Agriculteur *pere,*fils,*petitFils;
	AnsiString s;
	int i,j;
	ST_NoAgri *variante;
	TV->Items->Clear();

	pere=agri;
	tNPere=new TTreeNode(TV->Items);
	tNFils=TV->Items->AddObject(tNPere,pere->Nom,agri);

	for(i=0;i<pere->LstVariante->Count;i++)
	{
		variante=(ST_NoAgri*)pere->LstVariante->Items[i];
		fils=variante->Agri;
		tNPetitFils=TV->Items->AddChildObject(tNFils,fils->NoVariante,fils);
		for(j=0;j<fils->LstVariante->Count;j++)
		{
			variante=(ST_NoAgri*)fils->LstVariante->Items[j];
			petitFils=variante->Agri;
			CreeTVVarianteAgriSuite(TV,petitFils,tNPetitFils);
		}
		TV->Items->AddChildObject(tNPetitFils,"[...]",fils);
	}
	TV->Items->AddChildObject(tNFils,"[...]",pere);
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVVarianteAgriSuite(TTreeView *TV,
		CL_Agriculteur *fils,TTreeNode *tNFils)
{
	int j;
	ST_NoAgri *variante;
	CL_Agriculteur *petitFils;
	TTreeNode *tNPetitFils;
	tNPetitFils=TV->Items->AddChildObject(tNFils,fils->NoVariante,fils);

	for(j=0;j<fils->LstVariante->Count;j++)
	{
		variante=(ST_NoAgri*)fils->LstVariante->Items[j];
		petitFils=variante->Agri;
		CreeTVVarianteAgriSuite(TV,petitFils,tNPetitFils);
	}
	TV->Items->AddChildObject(tNPetitFils,"[...]",fils);
}
//-----------------------------------------------------------------------------
// GereAlea
/*
 CL_Vecteur<CL_Tendance>      *V_TendProd;
 CL_Vecteur<CL_Tendance>      *V_TendCharge;
 CL_Vecteur<CL_Tendance>      *V_ScenProd;
 CL_Vecteur<CL_Tendance>      *V_ScenCharge;
 PRIX
 Produits
 Tendance
 Scénario
 Charges
 Tendance
 Scénario
 QUANTITE
 Produits
 Tendance
 Scénario
 Charges
 Tendance
 Scénario
 Externalités
 Tendance
 Scénario

 */
void __fastcall TForme0Frm::CreeTVAleaPrix( TTreeView *TV)
{
	TTreeNode *tN0,*tN1,*tN2;
	AnsiString s;
	int i;
	CL_Tendance *tendance;
	int *nature;
	static int* lesNatures[4];
	static bool debut=true;
	if(debut==true)
	{
		nature=new int[4];
		lesNatures[0]=nature;
		nature[0]=PRIX;nature[1]=PRODUIT; nature[2]=TENDANCE;nature[3]=0;
		nature=new int[4];
		lesNatures[1]=nature;
		nature[0]=PRIX;nature[1]=PRODUIT; nature[2]=SCENARIO;nature[3]=0;
		nature=new int[4];
		lesNatures[2]=nature;
		nature[0]=PRIX;nature[1]=CHARGE; nature[2]=TENDANCE;nature[3]=0;
		nature=new int[4];
		lesNatures[3]=nature;
		nature[0]=PRIX;nature[1]=CHARGE; nature[2]=SCENARIO;nature[3]=0;
		debut =false;
	}
	TV->Visible=false;
	TV->Items->Clear();

	tN0=new TTreeNode(TV->Items);

//....Produits
	tN1=TV->Items->AddChild(tN0,T->L_Produit);
	//tN1=TV->Items->AddChild(tN0,"Produits");
	nature=lesNatures[0];
//    nature[0]=PRIX;nature[1]=PRODUIT;nature[2]=TENDANCE;
	tN2=TV->Items->AddChildObject(tN1,T->L_Tendance,nature);
	//tN2=TV->Items->AddChildObject(tN1,"Tendance",nature);
	for(i=0;i<V_TendPrixProd->Nbelt;i++)
	{
		tendance=V_TendPrixProd->Vecteur[i];
		TV->Items->AddChildObject(tN2,tendance->Nom,tendance);
	}
	TV->Items->AddChildObject(tN2,"[...]",NULL);
//!!    if(nature[3]>0) tN2->Expand(false);
//..    if(nature[3]>0) tN2->Expand(true);
	tN2->Expand(true);
	nature=lesNatures[1];
	//nature[0]=PRIX;nature[1]=PRODUIT;nature[2]=SCENARIO;
	tN2=TV->Items->AddChildObject(tN1,T->L_Scenario,nature);
	//tN2=TV->Items->AddChildObject(tN1,"Scénario",nature);
	for(i=0;i<V_ScenPrixProd->Nbelt;i++)
	{
		tendance=V_ScenPrixProd->Vecteur[i];
		TV->Items->AddChildObject(tN2,tendance->Nom,tendance);
	}
	TV->Items->AddChildObject(tN2,"[...]",NULL);
//!!    if(nature[3]>0) tN2->Expand(false);

//!!    tN1->Expand(false);

//....Charges
	tN1=TV->Items->AddChild(tN0,T->L_Charge);
	//tN1=TV->Items->AddChild(tN0,"Charges");
	nature=lesNatures[2];
	//nature[0]=PRIX;nature[1]=CHARGE;nature[2]=TENDANCE;
	tN2=TV->Items->AddChildObject(tN1,T->L_Tendance,nature);
	//tN2=TV->Items->AddChildObject(tN1,"Tendance",nature);
	for(i=0;i<V_TendPrixCharge->Nbelt;i++)
	{
		tendance=V_TendPrixCharge->Vecteur[i];
		TV->Items->AddChildObject(tN2,tendance->Nom,tendance);
	}
	TV->Items->AddChildObject(tN2,"[...]",NULL);
//!!    if(nature[3]>0) tN2->Expand(false);

	nature=lesNatures[3];
	nature[0]=PRIX;nature[1]=CHARGE;nature[2]=SCENARIO;
	tN2=TV->Items->AddChildObject(tN1,T->L_Scenario,nature);
	//tN2=TV->Items->AddChildObject(tN1,"Scenario",nature);
	for(i=0;i<V_ScenPrixCharge->Nbelt;i++)
	{
		tendance=V_ScenPrixCharge->Vecteur[i];
		TV->Items->AddChildObject(tN2,tendance->Nom,tendance);
	}
	TV->Items->AddChildObject(tN2,"[...]",NULL);
//!!    if(nature[3]>0) tN2->Expand(false);

//!!    tN1->Expand(false);
//    tN2->Expand(false);

	TV->Visible=true;

}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVAleaRdt( TTreeView *TV)
{
	TTreeNode *tN0,*tN1,*tN2;
	AnsiString s;
	int i;
	CL_Tendance *tendance;
	int *nature;
	static int* lesNatures[6];
	static bool debut=true;
	if(debut==true)
	{
		nature=new int[4];
		lesNatures[0]=nature;
		nature[0]=QUANTITE;nature[1]=PRODUIT; nature[2]=TENDANCE;nature[3]=0;

		nature=new int[4];
		lesNatures[1]=nature;
		nature[0]=QUANTITE;nature[1]=PRODUIT; nature[2]=SCENARIO;nature[3]=0;

		nature=new int[4];
		lesNatures[2]=nature;
		nature[0]=QUANTITE;nature[1]=CHARGE; nature[2]=TENDANCE;nature[3]=0;

		nature=new int[4];
		lesNatures[3]=nature;
		nature[0]=QUANTITE;nature[1]=CHARGE; nature[2]=SCENARIO;nature[3]=0;

		nature=new int[4];
		lesNatures[4]=nature;
		nature[0]=QUANTITE;nature[1]=EXTER; nature[2]=TENDANCE;nature[3]=0;

		nature=new int[4];
		lesNatures[5]=nature;
		nature[0]=QUANTITE;nature[1]=EXTER; nature[2]=SCENARIO;nature[3]=0;

		debut =false;
	}

	TV->Visible=false;
	TV->Items->Clear();

	tN0=new TTreeNode(TV->Items);
//QUANTITE
//....Produits
	tN1=TV->Items->AddChild(tN0,T->L_Produit);
	//tN1=TV->Items->AddChild(tN0,"Produits");
	nature=lesNatures[0];
	tN2=TV->Items->AddChildObject(tN1,T->L_Tendance,nature);
	//tN2=TV->Items->AddChildObject(tN1,"Tendance",nature);
	for(i=0;i<V_TendQProd->Nbelt;i++)
	{
		tendance=V_TendQProd->Vecteur[i];
		TV->Items->AddChildObject(tN2,tendance->Nom,tendance);
	}
	TV->Items->AddChildObject(tN2,"[...]",NULL);

	nature=lesNatures[1];
	tN2=TV->Items->AddChildObject(tN1,T->L_Scenario,nature);
	//tN2=TV->Items->AddChildObject(tN1,"Scénario",nature);
	for(i=0;i<V_ScenQProd->Nbelt;i++)
	{
		tendance=V_ScenQProd->Vecteur[i];
		TV->Items->AddChildObject(tN2,tendance->Nom,tendance);
	}
	TV->Items->AddChildObject(tN2,"[...]",NULL);
	tN1->Expand(false);

//....Charges
	tN1=TV->Items->AddChild(tN0,T->L_Charge);
	//tN1=TV->Items->AddChild(tN0,"Charges");
	nature=lesNatures[2];
	tN2=TV->Items->AddChildObject(tN1,T->L_Tendance,nature);
	//tN2=TV->Items->AddChildObject(tN1,"Tendance",nature);
	for(i=0;i<V_TendQCharge->Nbelt;i++)
	{
		tendance=V_TendQCharge->Vecteur[i];
		TV->Items->AddChildObject(tN2,tendance->Nom,tendance);
	}
	TV->Items->AddChildObject(tN2,"[...]",NULL);

	nature=lesNatures[3];
	tN2=TV->Items->AddChildObject(tN1,T->L_Scenario,nature);
	//tN2=TV->Items->AddChildObject(tN1,"Scenario",nature);
	for(i=0;i<V_ScenQCharge->Nbelt;i++)
	{
		tendance=V_ScenQCharge->Vecteur[i];
		TV->Items->AddChildObject(tN2,tendance->Nom,tendance);
	}
	TV->Items->AddChildObject(tN2,"[...]",NULL);

	tN1->Expand(false);

//....Externalités
	tN1=TV->Items->AddChild(tN0,L_Externalite="Externalités");
	//tN1=TV->Items->AddChild(tN0,"Externalités");
	nature=lesNatures[4];

	tN2=TV->Items->AddChildObject(tN1,T->L_Tendance,nature);
	//tN2=TV->Items->AddChildObject(tN1,"Tendance",nature);
	for(i=0;i<V_TendQExt->Nbelt;i++)
	{
		tendance=V_TendQExt->Vecteur[i];
		TV->Items->AddChildObject(tN2,tendance->Nom,tendance);
	}
	TV->Items->AddChildObject(tN2,"[...]",NULL);

	nature=lesNatures[5];
	tN2=TV->Items->AddChildObject(tN1,T->L_Scenario,nature);
	//tN2=TV->Items->AddChildObject(tN1,"Scenario",nature);
	for(i=0;i<V_ScenQExt->Nbelt;i++)
	{
		tendance=V_ScenQExt->Vecteur[i];
		TV->Items->AddChildObject(tN2,tendance->Nom,tendance);
	}
	TV->Items->AddChildObject(tN2,"[...]",NULL);

	tN1->Expand(false);

	TV->Visible=true;

}
//-----------------------------------------------------------------------------
// CheckListBox pour choisir les agri
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBToutAgri( TCheckListBox *ChLB)
{
	int n;
	CL_Agriculteur *agri;

	ChLB->Clear();

	for(n=0;n<V_Agriculteur->Nbelt;n++)
	{
		agri=V_Agriculteur->Vecteur[n];
		if(agri->EstVariante==true) continue;
		if(agri->EstPlus10Ans==true) continue;
		CreeLBToutAgriA(ChLB,agri);
	}
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBToutAgriA(TCheckListBox *ChLB,CL_Agriculteur *agri)
{
	int i;
	int noVariante;
	AnsiString nom;
	CL_Agriculteur *agriS,*agriV;
	ST_NoAgri *noAgri;
	if(agri->LstSerie==NULL)
	ChLB->Items->AddObject(agri->Nom,(TObject*)agri);
	else
	{
		for(i=0;i<agri->LstSerie->Count;i++)
		{
			if(i==0) // voir AgriDefSerieFrm->DefAgriApres
			{
				agriS=agri;
				noVariante=agriS->NoVariante;
			}
			else
			{
				noAgri=(ST_NoAgri*)agri->LstSerie->Items[i];
				agriS=noAgri->Agri;
				if(agriS==NULL)
				continue;
			}
			// DefSim peut ne pas etre encore créé
			//if(agriS->NoVariante <10)
			if(noVariante <10)
			nom=agriS->Nom+" "+(agriS->DefSim->An_0);
			else
			nom=agriS->Nom+noVariante+" "+(agriS->DefSim->An_0);
			ChLB->Items->AddObject(nom,(TObject*)agriS);
		}
	}
	if(agri->LstVariante==NULL)
	return;
	else
	{
		for(i=0;i<agri->LstVariante->Count;i++)
		{
			noAgri=(ST_NoAgri*)agri->LstVariante->Items[i];
			agriV=noAgri->Agri;
			CreeLBToutAgriA(ChLB,agriV);
		}
	}
}
//-----------------------------------------------------------------------------
// INUTILISE
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBToutAgriB(TCheckListBox *ChLB,AnsiString nomAieul,
		int nF,CL_Agriculteur *fils)
{
	int j,nPf;
	ST_NoAgri *variante;
	CL_Agriculteur *petitFils;
	AnsiString s,code;
	char blanc[]="      ";
	code=AnsiString(nF);
	s=nomAieul;
	for(int i=0;i<code.Length();i++)s=s+AnsiString(blanc);
	s=s+AnsiString(nF);
	ChLB->Items->AddObject(s,(TObject*)fils);

	for(j=0;j<fils->LstVariante->Count;j++)
	{
		nPf=nF*10+j+1;
		variante=(ST_NoAgri*)fils->LstVariante->Items[j];
		petitFils=variante->Agri;
		petitFils->NoVariante=nPf;
		CreeLBToutAgriB(ChLB,nomAieul,nPf,petitFils);
	}

}

///........
//-----------------------------------------------------------------------------
// CheckListBox pour choisir les ensembles
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBToutEnsemble( TCheckListBox *ChLB)
{
	int n;
	CL_Ensemble *ensemble;
	ChLB->Clear();
	for(n=0;n<V_Ensemble->Nbelt;n++)
	{
		ensemble=V_Ensemble->Vecteur[n];
		if(ensemble->EstVariante==true) continue;
		CreeLBToutEnsembleA(ChLB,ensemble);
	}
}

// Variante Ensemble
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBToutEnsembleA(TCheckListBox *ChLB,CL_Ensemble *ensemble)
{
	CL_Ensemble *pere,*fils,*petitFils;
	AnsiString s;
	AnsiString nomAieul;
	char blanc[]="      ";
	int i,j,nF,nPf;
	ST_NoEnsemble *variante;

	pere=ensemble;
	nomAieul=pere->Nom;
	ensemble->NoVariante=0;
	ChLB->Items->AddObject(nomAieul,(TObject*)ensemble);

	for(i=0;i<pere->LstVariante->Count;i++)
	{
		nF=i+1;
		variante=(ST_NoEnsemble*)pere->LstVariante->Items[i];
		fils=variante->Ensemble;
		fils->NoVariante=nF;
		s=nomAieul + AnsiString(blanc)+AnsiString(nF); //200801
		ChLB->Items->AddObject(s,(TObject*)fils);
		for(j=0;j<fils->LstVariante->Count;j++)
		{
			nPf=nF*10+j+1;
			variante=(ST_NoEnsemble*)fils->LstVariante->Items[j];
			petitFils=variante->Ensemble;
			petitFils->NoVariante=nPf;
			CreeLBToutEnsembleB(ChLB,nomAieul,nPf,petitFils);
		}
	}
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeLBToutEnsembleB(TCheckListBox *ChLB,AnsiString nomAieul,
		int nF,CL_Ensemble *fils)
{
	int j,nPf;
	ST_NoAgri *variante;
	CL_Agriculteur *petitFils;
	AnsiString s,code;
	char blanc[]="      ";
	code=AnsiString(nF);
	s=nomAieul;
	for(int i=0;i<code.Length();i++)s=s+AnsiString(blanc);
	s=s+AnsiString(nF);
	ChLB->Items->AddObject(s,(TObject*)fils);

	for(j=0;j<fils->LstVariante->Count;j++)
	{
		nPf=nF*10+j+1;
		variante=(ST_NoAgri*)fils->LstVariante->Items[j];
		petitFils=variante->Agri;
		petitFils->NoVariante=nPf;
		CreeLBToutAgriB(ChLB,nomAieul,nPf,petitFils);
	}

}
///...
//-----------------------------------------------------------------------------
// Variante Ensemble
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVVarianteEnsemble( TTreeView *TV,CL_Ensemble *ens)
{
	TTreeNode *tNPere,*tNFils,*tNPetitFils;
	CL_Ensemble *pere,*fils,*petitFils;
	AnsiString s;
	int i,j,nF,nPf;
	ST_NoEnsemble *variante;
	TV->Items->Clear();

	pere=ens;
	ens->NoVariante=0;
	tNPere=new TTreeNode(TV->Items);
	tNFils=TV->Items->AddObject(tNPere,pere->Nom,ens);

	for(i=0;i<pere->LstVariante->Count;i++)
	{
		nF=i+1;
		variante=(ST_NoEnsemble*)pere->LstVariante->Items[i];
		fils=variante->Ensemble;
		fils->NoVariante=nF;
		tNPetitFils=TV->Items->AddChildObject(tNFils,nF,fils);
		for(j=0;j<fils->LstVariante->Count;j++)
		{
			nPf=nF*10+j+1;
			variante=(ST_NoEnsemble*)fils->LstVariante->Items[j];
			petitFils=variante->Ensemble;
			petitFils->NoVariante=nPf;
			CreeTVVarianteEnsembleSuite(TV,nPf,petitFils,tNPetitFils);
		}
		//if(fils->LstVariante->Count==0)
		TV->Items->AddChildObject(tNPetitFils,"[...]",fils);
	}
	TV->Items->AddChildObject(tNFils,"[...]",pere);
}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVVarianteEnsembleSuite(TTreeView *TV,int nF,
		CL_Ensemble *fils,TTreeNode *tNFils)
{
	int j,nPf;
	ST_NoEnsemble *variante;
	CL_Ensemble *petitFils;
	TTreeNode *tNPetitFils;
// utilisation de nF ?? il est dans ens->NoVariante
	tNPetitFils=TV->Items->AddChildObject(tNFils,nF,fils);

	for(j=0;j<fils->LstVariante->Count;j++)
	{
		nPf=nF*10+j+1;
		variante=(ST_NoEnsemble*)fils->LstVariante->Items[j];
		petitFils=variante->Ensemble;
		petitFils->NoVariante=nPf;
		CreeTVVarianteEnsembleSuite(TV,nPf,petitFils,tNPetitFils);
	}
	TV->Items->AddChildObject(tNPetitFils,"[...]",fils);

}
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVRepart(TTreeView *TV)
{
	TTreeNode *tNCat,*tNElt;
	AnsiString s;
	int i,j;
	CL_Categorie *cat;
	CL_Repart *repart;
	TV->Items->Clear();

	tNCat=new TTreeNode(TV->Items);
	for(i=0;i<V_CatRepart->Nbelt;i++)
	{
		cat=V_CatRepart->Vecteur[i];
		tNElt=TV->Items->AddObject(tNCat,cat->Nom,cat);
		for(j=0;j<V_Repart->Nbelt;j++)
		{
			repart=V_Repart->Vecteur[j];
			if(repart->NoCategorie==cat->No)
			{
				TV->Items->AddChildObject(tNElt,repart->Nom,repart);
			}
		}
		TV->Items->AddChildObject(tNElt,"[...]",NULL);
//		TV->Items->AddChildObject(tNElt,"[...]",(TObject*)nature);
	}
	TV->Items->AddObject(tNCat,"[...]",NULL);
//    TV->Items->AddObject(tNCat,"[...]",(TObject*)nature);
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
///////////////////////////// GENERAL////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//complet  =false ne contient que les élements qui ont une valeur
//complet  =true  contient tout
//tVChoix->Tag=1  ne pas recréer tVChoix
//
//-----------------------------------------------------------------------------
void __fastcall TForme0Frm::CreeTVToutElt(TTreeView *tVChoix,CL_Agriculteur *agri,
		bool complet)
{
//static bool debut=true;
	int i;
	TTreeNode *tnTout;
	TTreeNode *tnFamille,*tnCategorie,*tnType;
	/** Initialisation : les premiers Elt sont des POSTE */
	int noFamille=POSTE;
	int noType;
	CL_Elt *elt,*eltTitreF,*eltTitreC,*eltTitreT;
	CL_Categorie *categorie=NULL;
	bool eltExiste;
	char *nom;
	AnsiString as;
//ShowMessage("Forme0  CreeTVToutElt");
// regler le delete pour PERENNE
	/*

	 // a voir pour éviter de faire n fois les memes calculs
	 //if(AgriEnCours) AgriSaisieFrm->Calcul(AgriEnCours);
	 */
	//ES->IniV_Elt(); doit etre appele avant d'utilise CreeTVToutElt
	if(agri)
	{
		PProd= agri->DefSim->TPProd;
		PCharge= agri->DefSim->TPCharge;
	}

	tVChoix->Items->Clear();

	tnTout=new TTreeNode(tVChoix->Items);
	noFamille=-1;
	//ShowMessage("CreeTVToutElt");
	/** On balaye le V_Elt */
	for(i=0;i<V_Elt->Nbelt;i++)
	{
		elt=V_Elt->Vecteur[i];
		/** Cet éléments est présent chez notre agriculteur ? */
		eltExiste=CompleteElt(elt,agri);

		/** Si on ne veut pas une liste exhaustive des Elt
		 et l'Elt n'est pas présent chez l'agriculteur,
		 on passe au suivant */
		if(complet==false && eltExiste==false) continue;

		if(elt->NoFamille!=noFamille)
		{
			/** On crée un nouveau noeud de famille à la racine
			 qui a le nom du Poste */
//            eltTitreF=new CL_Elt(elt->NomFamille);
//            tnFamille=tVChoix->Items->AddChildObject(tnTout,eltTitreF->NomFamille,eltTitreF);
			eltTitreF=new CL_Elt(elt->Poste);
			tnFamille=tVChoix->Items->AddChildObject(tnTout,elt->Poste->Nom,eltTitreF);
			/** Pointeur courant sur famille actualisé */
			noFamille=elt->NoFamille;
			categorie=NULL;
		}

		if(elt->Categorie)
		{
			/** On a changé de catégorie */
			if(elt->Categorie!=categorie)
			{
				/** Nouveau noeud de catégorie sous la famille courante */
				eltTitreC=new CL_Elt(elt->Poste,elt->Categorie);
				tnCategorie=tVChoix->Items->AddChildObject(tnFamille,elt->Categorie->Nom,eltTitreC);
				categorie=elt->Categorie;
			}
			// cas des animaux
			if(elt->NoType!=0 && elt->NoType!=noType)
			{
				noType=elt->NoType;
				as=elt->NomTypeMvtAni(elt->NoType);
				nom=as.c_str();
				/** Nouveau noeud de catégorie sous la famille courante */
				eltTitreT=new CL_Elt(elt->Poste,elt->Categorie);
				tnType=tVChoix->Items->AddChildObject(tnCategorie,nom,eltTitreT);
			}
			/** On accroche un noeud pour un Elt sous sa catégorie */
			if(elt->NoType==0)
			tVChoix->Items->AddChildObject(tnCategorie,elt->Nom,elt);
			else
			tVChoix->Items->AddChildObject(tnType,elt->Nom,elt);
		}
		else
		// Pas de catégorie Poste Bilan Ceg  Immo Emprunt
		{
			tVChoix->Items->AddChildObject(tnFamille,elt->Nom,elt);
		}
	}
//test
	/* pour test
	 DeleteFile("LesElt.txt");

	 ofstream outfile("LesElt.txt");
	 AnsiString date;
	 TDateTime time;

	 time=TDateTime::CurrentDateTime();
	 date=time.DateTimeString();

	 outfile << date.c_str() <<endl;
	 TTreeNode *tn;
	 for(i=0;i<V_Elt->Nbelt;i++)
	 {
	 elt=V_Elt->Vecteur[i];
	 outfile <<i <<"  "<< elt->NoFamille <<"  "<< elt->NoCategorie <<"  "<< elt->NoType
	 <<"  "<< elt->NoItem <<"  "<< elt->Nom <<"  "<< elt->NomCat <<"  "<< elt->NomFamille <<endl;
	 }
	 outfile<< "___________________"<<endl;

	 for(i=0;i<tVChoix->Items->Count;i++)
	 {
	 tn=tVChoix->Items->Item[i];
	 elt=(CL_Elt*)tn->Data;
	 outfile <<i <<"  "<< elt->NoFamille <<"  "<< elt->NoCategorie <<"  "<< elt->NoType
	 <<"  "<< elt->NoItem <<"  "<< elt->Nom <<"  "<< elt->NomCat <<"  "<< elt->NomFamille <<endl;

	 }
	 */
// fin test
	V_Elt->Flag=true;//inutile ?
	tVChoix->Tag=1;//les adresses ont été mises  inutile ?
	delete tnTout;

	//pour eviter de recréer inutilement
	TVDicoFrm->AncAgri=agri;//230103
	TVDicoFrm->AncTVItemCount=TVDicoFrm->TV->Items->Count;
	TVDicoFrm->AncComplet=complet;// false on est chez un agri
								  //   true on y est pas je veux donner l'accés à tout
}
//---------------------------------------------------------------------------
void __fastcall TForme0Frm::CompleteV_Elt( CL_Agriculteur *agri)
{
	int i;
	CL_Elt *elt;

	for(i=0;i<V_Elt->Nbelt;i++)
	{
		elt=V_Elt->Vecteur[i];
		Forme0Frm->CompleteElt(elt,agri);
	}
}
//---------------------------------------------------------------------------
/** Accroche aux Elt de V_Elt les Valeurs éparpillées dans :
 Agri, AgriRes
 */
bool __fastcall TForme0Frm::CompleteElt( CL_Elt *elt,CL_Agriculteur *agri)
{
	int i,j;
	bool enValeur;
	CL_Vecteur<CL_QuanVal> *vQuanVal;
	CL_QuanVal *quanVal;
	CL_Valeur *valeur;
	CL_Indicateur *indic;
	CL_Item *item;
	CL_Verger *verger;
	CL_TotEmp *totEmp;
	CL_Troupeau *troupeau;
	CL_InvAni *invAni;
	CL_Calendrier *calendrier;
	float *surface;
	bool rep;
	int j0;
	float bidon[10]; // cf ligne 2020
	if(agri==NULL) return false;

	j0=N_X *agri->NoSerie;

	PProd= agri->DefSim->TPProd;
	PCharge= agri->DefSim->TPCharge;

	if(elt->NoFamille==FORME) return false;

	if(elt->NoFamille==POSTE)
	{
		switch(elt->NoItem)
		{
			case PRODUIT: elt->Valeur=agri->Resultat->Produit;break;
			case CHARGE: elt->Valeur=agri->Resultat->Charge;break;
			case MARGE: elt->Valeur=agri->Resultat->Marge;break;
			case CHSTRUCT: elt->Valeur=agri->Resultat->ChStruct;break;
			case RECDIV: elt->Valeur=agri->Resultat->RecDiv;break;
			case DEPDIV: elt->Valeur=agri->Resultat->DepDiv;break;
			case RECFAM: elt->Valeur=agri->Resultat->RecFam;break;
			case DEPFAM: elt->Valeur=agri->Resultat->DepFam;break;
			case SOLDE: elt->Valeur=agri->Resultat->Solde;break;
			case SOLDECUMUL: elt->Valeur=agri->Resultat->SoldeCumul;break;
			case RESULTAT: elt->Valeur=agri->Resultat->resExercice;break;
			case EBE: elt->Valeur=agri->Resultat->Ebe;break;
			case CAF: elt->Valeur=agri->Resultat->Caf;break;
			default:
			ShowMessage("CompleteElt 1 Oubli");
			elt->Valeur=ValZero;
		}
		return true;
	}
	//  voir FichierElt CL_ES::IniV_EltBilan(void)

	if(elt->NoFamille==BILAN)
	{
		switch(elt->NoItem)
		{
			//Actif
			case 0 :elt->Valeur= agri->Resultat->totImmo; break;
			case 1 :elt->Valeur= agri->Resultat->ImmoTotal->Resid; break;
			case 2 :elt->Valeur= agri->Resultat->InvAniRepro; break;//260903
			case 3 :elt->Valeur= agri->Resultat->ValPlant; break;

			case 4 :elt->Valeur= agri->Resultat->Stock; break;
			case 5 :elt->Valeur= agri->Resultat->Avance; break;
			case 6 :elt->Valeur= agri->Resultat->InvAniAutre; break;
			case 7 :elt->Valeur= agri->Resultat->PlactE->Dette; break;
			case 8 :elt->Valeur= agri->Resultat->creanceTva; break;
			case 9 :elt->Valeur= agri->Resultat->Creance->CrDette; break;
			case 10 :elt->Valeur= agri->Resultat->tresorerie; break;
			case 11 :elt->Valeur= agri->Resultat->perte; break;
			case 12 :elt->Valeur= agri->Resultat->totActif; break;
			//Passif  13
			case 14 :elt->Valeur= agri->Resultat->capital; break;
			case 15 :elt->Valeur= agri->Resultat->soldePrive; break;
			case 16 :elt->Valeur= agri->Resultat->TotSub->Resid; break;
			case 17 :elt->Valeur= agri->Resultat->EmpLTE->Dette; break;
			case 18 :elt->Valeur= agri->Resultat->EmpCTE->Dette; break;
			case 19 :elt->Valeur= agri->Resultat->detteTva; break;
			case 20 :elt->Valeur= agri->Resultat->Dette->CrDette; break;
			case 21 :elt->Valeur= agri->Resultat->benefice; break;
			case 22 :elt->Valeur= agri->Resultat->totPassif; break;

		}
		return true;
	}
	//  voir FichierElt CL_ES::IniV_EltCeg(void)
	if(elt->NoFamille==CEG)
	{
		switch(elt->NoItem)
		{

			case 0: elt->Valeur=agri->Resultat->totProduit;break;

			case 1 :elt->Valeur=agri->Resultat->Produit;break;
			case 2 :elt->Valeur=agri->Resultat->RecDiv;break;
			case 3 :elt->Valeur=agri->Resultat->deltaStock;break;
			case 4 :elt->Valeur=agri->Resultat->deltaAvance;break;
			case 5 :elt->Valeur=agri->Resultat->deltaVarInvAniRepro;break;
			case 6 :elt->Valeur=agri->Resultat->deltaVarInvAniAutre;break;

			case 7 :elt->Valeur=agri->Resultat->PlactE->Interet;break;
			case 8 :elt->Valeur=agri->Resultat->ProdImmo;break;
			case 9 :elt->Valeur=agri->Resultat->ImmoTotal->Vente;break;
			case 10 :elt->Valeur=agri->Resultat->PertePlant;break;
			case 11 :elt->Valeur=agri->Resultat->TotSub->Amor;break;

			case 12 :elt->Valeur=agri->Resultat->totDepense;break;

			case 13 :elt->Valeur=agri->Resultat->Charge;break;
			case 14 :elt->Valeur=agri->Resultat->DepDiv;break;
			case 15 :elt->Valeur=agri->Resultat->ImmoTotal->ValCompta;break;

			case 16 :elt->Valeur=agri->Resultat->totChStruct;break;
			case 17 :elt->Valeur=agri->Resultat->ImmoTotal->Amor;break;
			case 18 :elt->Valeur=agri->Resultat->AmorPlant;break;
			case 19 :elt->Valeur=agri->Resultat->EmpLTE->Interet;break;
			case 20 :elt->Valeur=agri->Resultat->EmpCTE->Interet;break;
			case 21 :elt->Valeur=agri->Resultat->FraisOccc;break;
			case 22 :elt->Valeur=agri->Resultat->ChStruct;break;
			case 23 :elt->Valeur=agri->Resultat->resExercice;break;

		}
		return true;
	}

	if(elt->NoFamille==VARIABLE)
	{
		for(int i=0;i<agri->V_Variable->Nbelt;i++)
		{
			valeur=agri->V_Variable->Vecteur[i];
			item=valeur->Item;
			if(item->No==elt->NoItem && item->NoCategorie==elt->NoCategorie)
			{
				elt->Valeur=valeur->Valeur;
				return true;
			}
		}
		elt->Valeur=ValZero; return false;
	}
	// a ce stade les indicateurs doivent avoir été calculés
	if(elt->NoFamille==INDIC)
	{
		for(int i=0;i<V_Indicateur->Nbelt;i++)
		{
			indic=V_Indicateur->Vecteur[i];
			if(indic->No==elt->NoItem && indic->NoCategorie==elt->NoCategorie)
			{
				elt->Valeur=indic->Valeur;
				return true;
			}
		}
		elt->Valeur=ValZero; return false;
	}
	if(elt->NoFamille==PPRODUIT)
	{
		item=V_Produit->trouve(elt->NoItem);
		if(item==NULL) {elt->Valeur=ValZero; return false;}
		else
		{
			if(elt->Valeur==NULL)
			elt->Valeur=new float[N_X];
			elt->Pcent=trouveDelta(item,PProd);
			if(elt->Pcent==NULL)
			for(int i=0;i<N_X;i++)elt->Valeur[i]=item->Prix;
			else
			for(int i=0;i<N_X;i++)elt->Valeur[i]=item->Prix*elt->Pcent[i+j0]; //200907
			return true;
		}
	}

	if(elt->NoFamille==PCHARGE)
	{
		item=V_Charge->trouve(elt->NoItem);
		if(item==NULL) {elt->Valeur=ValZero; return false;}
		else
		{
			if(elt->Valeur==NULL)
			elt->Valeur=new float[N_X];
			elt->Pcent=trouveDelta(item,PCharge);
			if(elt->Pcent==NULL)
			for(int i=0;i<N_X;i++)elt->Valeur[i]=item->Prix;
			else
			for(int i=0;i<N_X;i++)elt->Valeur[i]=item->Prix*elt->Pcent[i+j0];
			return true;
		}
	}

	if(elt->NoFamille==IMMO)
	{
		switch(elt->NoItem)
		{
			case AMOR: elt->Valeur=agri->Resultat->ImmoTotal->Amor; return true;
			case VALRESID: elt->Valeur=agri->Resultat->ImmoTotal->Resid; return true;
			case VALACHAT: elt->Valeur=agri->Resultat->ImmoTotal->Achat; return true;
			case VALBRUT: elt->Valeur=agri->Resultat->ImmoTotal->ValBrut;return true;
			default:ShowMessage(L_OubliImmo);
			//default:ShowMessage("CompleteElt Immo Oubli");
		}
	}
	if(elt->NoFamille==SUBVENTION)
	{
		switch(elt->NoItem)
		{
			case AMOR: elt->Valeur=agri->Resultat->TotSub->Amor; return true;
			case VALRESID: elt->Valeur=agri->Resultat->TotSub->Resid; return true;
			case VALACHAT: elt->Valeur=agri->Resultat->TotSub->Valeur; return true;
			default:ShowMessage(L_OubliSubvention);
			//default:ShowMessage("CompleteElt Subvention Oubli");
		}
	}

	if(elt->NoFamille==TVA) //cf FichierElt IniV_EltTva
	{
		switch(elt->NoItem)
		{
			case 1: elt->Valeur=agri->Resultat->Tva->Recu; return true;
			case 2: elt->Valeur=agri->Resultat->Tva->Verse; return true;
			case 3: elt->Valeur=agri->Resultat->Tva->Regul; return true;
			case 4: elt->Valeur=agri->Resultat->Tva->Solde; return true;
			default:ShowMessage(L_OubliTva="CompleteElt tva Oubli");
			//default:ShowMessage("CompleteElt tva Oubli");
		}
	}

	if( elt->NoFamille==EMP ||elt->NoFamille==EMPLT
			||elt->NoFamille==EMPCT ||elt->NoFamille==EMPPRIVE)
	{
		switch(elt->NoFamille)
		{
			case EMP: totEmp=agri->Resultat->EmpTotal;break;
			case EMPLT: totEmp=agri->Resultat->EmpLTE;break;
			case EMPCT: totEmp=agri->Resultat->EmpCTE;break;
			case EMPPRIVE: totEmp=agri->Resultat->EmpTotalPrive;break;
			default:ShowMessage("CompleteElt Emprunt Oubli");
		}
		switch(elt->NoItem)
		{
			case ANNUITE: elt->Valeur=totEmp->Annuite; return true;
			case REMB: elt->Valeur=totEmp->Remb; return true;
			case INTERET: elt->Valeur=totEmp->Interet; return true;
			case NOUVEMP: elt->Valeur=totEmp->Capital; return true;
			case DETTE: elt->Valeur=totEmp->Dette; return true;
			default:ShowMessage("CompleteElt Emprunt Oubli");
		}
	}

	if(elt->NoFamille==CULTURE)
	{
		surface=elt->Valeur;
		if(surface==NULL) //140403
		surface=ValZero;
		memset(surface,0,sizeof(float)*N_X);
		rep=false;
		for(int i=0;i<agri->V_Culture->Nbelt;i++)
		{
			valeur=agri->V_Culture->Vecteur[i];
			if(valeur->NoAtelier==elt->NoItem)
			{
				rep=true;
				for(int i=0;i<N_X;i++)
				surface[i]+=valeur->Valeur[i];
			}
		}
		return rep;
	}
	//030303
	if(elt->NoFamille==ANIMAUX)
	{
		surface=elt->Valeur; //surface =effectif
		memset(surface,0,sizeof(float)*N_X);
		rep=false;
		for(int i=0;i<agri->V_Animaux->Nbelt;i++)
		{
			valeur=agri->V_Animaux->Vecteur[i];
			if(valeur->NoAtelier==elt->NoItem)
			{
				rep=true;
				for(int i=0;i<N_X;i++)
				surface[i]+=valeur->Valeur[i];
			}
		}
		return rep;
	}
	// modif du 240103
	if(elt->NoFamille==PERENNE)
	{
		if(elt->Valeur==NULL)
		{
			ShowMessage("Forme0elt->Valeur=NULL");
			return true;
		}
		surface=elt->Valeur;

		memset(surface,0,sizeof(float)*N_X);
		rep=false;
		for(int i=0;i<agri->V_Verger->Nbelt;i++)
		{
			verger=agri->V_Verger->Vecteur[i];
			if(verger->NoEspece!=elt->NoEspece) continue;
			if(verger->NoAtelier==elt->NoItem)
			{
				rep=true;
				for(int j=0;j<N_X;j++)
				{
					surface[j]+=verger->SurfaceAn[j];
					bidon[j]=surface[j];
				}
			}

		}
		return rep;
	}

	if(elt->NoFamille==VIVRIER)
	{
		surface=elt->Valeur;
		memset(surface,0,sizeof(float)*N_X);
		rep=false;
		for(int i=0;i<agri->V_Vivrier->Nbelt;i++)
		{
			verger=agri->V_Vivrier->Vecteur[i];
			if(verger->NoAtelier==elt->NoItem)
			{
				rep=true;
				for(int i=0;i<N_X;i++)
				surface[i]+=verger->SurfaceAn[i];
			}
		}
		return rep;
	}
	if(elt->NoFamille==MVT)
	{
		for(i=0;i<agri->LstTroupeaux->Count;i++)
		{
			troupeau=(CL_Troupeau*)agri->LstTroupeaux->Items[i];
			{
				for(j=0;j<troupeau->V_InvAni->Nbelt;j++)
				{
					invAni=troupeau->V_InvAni->Vecteur[j];
					if(invAni->NoAnimal==elt->NoItem)
					{
						switch(elt->NoType)
						{
							case EFF: elt->Valeur=invAni->Effectif; break;
							case EFFV: elt->Valeur=invAni->Vente; break;
							case EFFA: elt->Valeur=invAni->Achat; break;
							case VALV: elt->Valeur=invAni->ValVente; break;
							case VALA: elt->Valeur=invAni->ValAchat; break;
							case VALINV:elt->Valeur=invAni->Valeur; break;
						}
						return true;
					}
				}
			}
		}
		elt->Valeur=ValZero; return false;
	}
	//090306
	if(elt->NoFamille==CALENDRIER)
	{
		for(i=0;i<V_Calendrier->Nbelt;i++)
		{
			calendrier=V_Calendrier->Vecteur[i];
			if(elt->NoItem==calendrier->No)
			{
				elt->Valeur=calendrier->TotBesoins;
				return true;
			}
		}
		elt->Valeur=ValZero; return false;
	}
	//090306
	if(elt->NoFamille==AMORDETAIL)
	{
		ShowMessage("AMORDETAIL");
		return false;
	}

	vQuanVal=NULL;
	switch (elt->NoFamille)
	{
		//valeur
		case PRODUIT: vQuanVal=agri->Resultat->V_Produit; enValeur=true;break;
		case CHARGE: vQuanVal=agri->Resultat->V_Charge; enValeur=true;break;

		case CHSTRUCT: vQuanVal=agri->Resultat->V_ChStruct; enValeur=true;break;
		case RECDIV: vQuanVal=agri->Resultat->V_RecDiv; enValeur=true;break;
		case DEPDIV: vQuanVal=agri->Resultat->V_DepDiv; enValeur=true;break;
		case RECFAM: vQuanVal=agri->Resultat->V_RecFam; enValeur=true;break;
		case DEPFAM: vQuanVal=agri->Resultat->V_DepFam; enValeur=true;break;

		//quantité
		case EXTPOS: vQuanVal=agri->Resultat->V_ExtPos; enValeur=false;break;
		case EXTNEG: vQuanVal=agri->Resultat->V_ExtNeg; enValeur=false;break;
		case QPRODUIT: vQuanVal=agri->Resultat->V_Produit; enValeur=false;break;
		case QCHARGE: vQuanVal=agri->Resultat->V_Charge; enValeur=false;break;

		default:ShowMessage("CompleteElt 2 Oubli");
	}
	if(vQuanVal)
	{
		quanVal=vQuanVal->trouve(elt->NoItem);
//        elt->Item=quanVal->Item;   //040302
		if(quanVal==NULL) {elt->Valeur=ValZero; return false;}
		else
		{
			if(enValeur==true)
			{
				elt->Valeur=quanVal->Val;
				if (elt->NoFamille==PRODUIT)
				elt->Pcent=trouveDelta(elt->Item,PProd);
				else if(elt->NoFamille==CHARGE)
				elt->Pcent=trouveDelta(elt->Item,PCharge);
				return true;
			}
			else
			{
				elt->Valeur=quanVal->Qte;
				return true;
			}
		}
	}
	return false; //aew
}
//---------------------------------------------------------------------------
float* __fastcall TForme0Frm:: trouveDelta(CL_Item *item,CL_Tendance *tendance)
{
	int i;
	CL_Delta *delta;

	if ( tendance==NULL) return NULL;

	for(i=0;i<tendance->V_Delta->Nbelt;i++)
	{
		delta=tendance->V_Delta->Vecteur[i];
		if(delta->Item==item)
		{
			return delta->Pcent;
		}
	}
	return NULL;
}
//---------------------------------------------------------------------------
void TForme0Frm::TexteChaine(void) {

//	L_QuitterQ=        "Vous voulez vraiment quitter";
//   L_Quitter=         "QUITTER OLYMPE";
//  L_Produits=        "Produits";
//  L_RecDiv=          "Recettes Diverses";
//  L_Charges=         "Charges";
//    L_ChStruct=        "Charges Structure";
//    L_DepDiv=          "Dépenses Diverses";
//	L_Culture=         "Culture";
//	L_Animaux=         "Animaux";
//	L_Perenne=         "Pérenne";
//	L_Vivrier=         "Vivrier";

//    L_Tendance=        "Tendance";
//    L_Scenario=        "Scénario";
//    L_Externalite=     "Externalités";

	L_OubliImmo = "CompleteElt Immo Oubli";
	L_OubliSubvention = "CompleteElt Subvention Oubli";
	L_OubliTva = "CompleteElt tva Oubli";

}

//--------------------------------------------
void TForme0Frm::TexteCaption(void) {
	BtBnQuitter->Caption = T->LC_BtBnQuitter;
}
//--------------------------------------------
void TForme0Frm::IniCaption(void) {
	LC_BtBnQuitter = T->TrouveCaption("CL_Trad", "LC_BtBnQuitter");
}
//--------------------------------------------

/*
 //---------------------------------------------------------------------------
 void TForme0Frm:: Anglais(void)
 {
 //	L_QuitterQ=        "Do you really want to exit?";
 //    L_Quitter=         "EXIT OLYMPE";
 //    L_Produits=        "Products";
 //    L_RecDiv=          "Misc Revenues";
 //    L_Charges=         "Expenses";
 //    L_ChStruct=        "Fixed Assets";
 L_Tendance=        "Tendancy";
 L_Scenario=        "Scenario";
 L_Externalite=     "Externalities";
 L_OubliImmo=       "CompleteElt Fixed assets Empty";
 L_OubliSubvention= "CompleteElt Subvention Empty";
 L_OubliTva=        "CompleteElt Vat Empty";
 }
 */
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
/*
 Forme0
 Forme00
 SysUnite
 Espece
 Produit
 Charge
 Eau
 Fruit
 Categories
 RecDepAutre
 Structure
 Etat
 Famille
 Zone
 Externalite
 Forme000
 Animal
 Cultures
 Agriculteur

 */

