//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Forme0.h"
#include "TVChoixRepart.h"

#include "TresoRepart.h"
#include "TresoQouV.h"
#include "TresoRes.h"
#include "TresoEnum.h"
#include "TresoDefOccc.h"

#include "Treso.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme0"
#pragma resource "*.dfm"
TTresoFrm *TresoFrm;

extern CL_ES *ES;

/*
 AgriSaisie a appelé Treso en mettant Origine à 0
 */
//---------------------------------------------------------------------------
__fastcall TTresoFrm::TTresoFrm(TComponent* Owner) :
		TForme0Frm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::FormActivate(TObject *Sender)
{
	CL_Categorie *cat;
	if(Origine!=0) return;

	IlYaModif=false;
	if(AgriEnCours->Resultat==NULL)
	{
		ShowMessage("Choisir un agriculteur");
		return;
	}
	CompleteQuanVal();
	switch(TresoQouVFrm->RGQouV->ItemIndex)
	{
		case 0:Caption ="Tresorerie en Valeur";break;
		case 1:Caption ="Tresorerie en Quantité";break;
		case 2:Caption ="Tresorerie Autre";break; // a voir
	}
	Origine=1;
	if(V_CatRepart->Nbelt==0)
	{
		cat=new CL_Categorie("Standard",0);
		V_CatRepart->ins(cat);
	}
	Forme0Frm->CreeTVRepart(TVChoixRepartFrm->TV);

}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::QuantOuVal(void)
{
	if(TresoQouVFrm->RGQouV->ItemIndex==0)
	TresoRepartFrm->CalculEn=VALEUR;
	else
	TresoRepartFrm->CalculEn=QUANTITE;
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(IlYaModif==true)
	{
		StockRepart();
		ES->ecrireFichier();
	}
	TVChoixRepartFrm->Close();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::DefinitionClick(TObject *Sender)
{
	TVChoixRepartFrm->AFaire=AnsiString("Definir");
	TVChoixRepartFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::TypeValQuantClick(TObject *Sender)
{
	TresoQouVFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::ProduitsClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=PRODUIT;
	QuantOuVal();

	TresoRepartFrm->Show();
//    ShowMessage("Retour treso");
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::OperationnellesClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=CHARGE;
	QuantOuVal();
	TresoRepartFrm->Show();
//    ShowMessage("Retour treso");
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::StructureClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=CHSTRUCT;
	TresoRepartFrm->CalculEn=VALEUR;
	TresoRepartFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::DivRecettesClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=RECDIV;
	TresoRepartFrm->CalculEn=VALEUR;
	TresoRepartFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::DivDepensesClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=DEPDIV;
	TresoRepartFrm->CalculEn=VALEUR;
	TresoRepartFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::PrivRecettesClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=RECFAM;
	TresoRepartFrm->CalculEn=VALEUR;
	TresoRepartFrm->Show();
}

//---------------------------------------------------------------------------
void __fastcall TTresoFrm::ExternalitesClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=EXTER; //EXTNEG et EXTPOS
	TresoRepartFrm->CalculEn=QUANTITE;
	TresoRepartFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::InvestissementClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=IMMO;
	TresoRepartFrm->CalculEn=VALEUR;
	TresoRepartFrm->BtBnCalculClick(this);
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::PetitMatrielClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=PETITMAT;
	TresoRepartFrm->CalculEn=VALEUR;
	if(AgriEnCours->V_Petit->Nbelt==0)
	{
		ShowMessage("Aucun élément");
		return;
	}

	TresoRepartFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::FinanceClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=FINANCE;
	TresoRepartFrm->CalculEn=VALEUR;
	TresoRepartFrm->BtBnCalculClick(this);
//	TresoRepartFrm->Show();          si entree globale
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::PrivDepensesClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=DEPFAM;
	TresoRepartFrm->CalculEn=VALEUR;
	TresoRepartFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::EnCoursClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=DETTE;
	TresoRepartFrm->CalculEn=VALEUR;
	TresoRepartFrm->BtBnCalculClick(this);
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::TresoDetailClick(TObject *Sender)
{
	TresoResFrm->Origine=0;
	TresoResFrm->TypeSortie=DETAIL;
	TresoResFrm->Nature=AGRI;
	TresoRepartFrm->CalculEn=VALEUR;
	TresoResFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::TresoSemiDetailClick(TObject *Sender)
{
	TresoResFrm->Origine=0;
	TresoResFrm->TypeSortie=SEMIDETAIL;
	TresoRepartFrm->CalculEn=VALEUR;
	TresoResFrm->Nature=AGRI;
	TresoResFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::TresoSyntheseClick(TObject *Sender)
{
	TresoResFrm->Origine=0;
	TresoResFrm->TypeSortie=GLOBAL;
	TresoRepartFrm->CalculEn=VALEUR;
	TresoResFrm->Nature=AGRI;
	TresoResFrm->Show();
}

//---------------------------------------------------------------------------
void __fastcall TTresoFrm::CompleteQuanVal(void)
{
	int i;
	CL_Petit *petit; //petit Materiel
//	AgriEnCours->V_ItemRepart->vide();
	CompleteQuanVal1(AgriEnCours->Resultat->V_Produit, PRODUIT);
	CompleteQuanVal1(AgriEnCours->Resultat->V_Charge, CHARGE);
	CompleteQuanVal1(AgriEnCours->Resultat->V_ChStruct, CHSTRUCT);
	CompleteQuanVal1(AgriEnCours->Resultat->V_RecDiv, RECDIV);
	CompleteQuanVal1(AgriEnCours->Resultat->V_DepDiv, DEPDIV);
	CompleteQuanVal1(AgriEnCours->Resultat->V_RecFam, RECFAM);
	CompleteQuanVal1(AgriEnCours->Resultat->V_DepFam, DEPFAM);
	CompleteQuanVal1(AgriEnCours->Resultat->V_ExtNeg, EXTNEG);
	CompleteQuanVal1(AgriEnCours->Resultat->V_ExtPos, EXTPOS);

	//petit materiel
	if(AgriEnCours->V_Petit->Nbelt==0) return;

	for(i=0;i<N_X;i++)//il y a N_X elt
	{
		petit=AgriEnCours->V_Petit->Vecteur[i];
		AgriEnCours->QuanValPetit->Val[i]=petit->ValAchat;
	}
	AgriEnCours->QuanValPetit->ItemRepart=TrouveItemRepart(PETITMAT);
	AgriEnCours->QuanValPetit->ItemRepart->Famille=PETITMAT;

}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::CompleteQuanVal1(CL_Vecteur<CL_QuanVal>*vecteur,int nature)
{
	int i;
	CL_QuanVal *quanVal;
	for(i=0;i<vecteur->Nbelt;i++)
	{
		quanVal=vecteur->Vecteur[i];
		quanVal->ItemRepart=TrouveItemRepart(quanVal->Item->No,nature);
	}
}
//---------------------------------------------------------------------------
CL_ItemRepart* __fastcall TTresoFrm::TrouveItemRepart(int noItem,int famille)
{
	int i;
	CL_ItemRepart *itemRepart;

	for(i=0;i<AgriEnCours->V_ItemRepart->Nbelt;i++)
	{
		itemRepart=AgriEnCours->V_ItemRepart->Vecteur[i];
		if(itemRepart->NoItem==noItem && itemRepart->Famille==famille)
		return itemRepart;
	}
	itemRepart=new CL_ItemRepart(noItem,famille);
	return itemRepart;

}
//---------------------------------------------------------------------------
CL_ItemRepart* __fastcall TTresoFrm::TrouveItemRepart(int famille)
{
	int i;
	int noItem=-1;
	CL_ItemRepart *itemRepart;

	for(i=0;i<AgriEnCours->V_ItemRepart->Nbelt;i++)
	{
		itemRepart=AgriEnCours->V_ItemRepart->Vecteur[i];
		if( itemRepart->Famille==famille)
		return itemRepart;
	}
	itemRepart=new CL_ItemRepart(noItem,famille);
	return itemRepart;

}

//---------------------------------------------------------------------------
void __fastcall TTresoFrm::StockRepart(void)
{
	AgriEnCours->V_ItemRepart->vide();
	StockRepart1(AgriEnCours->Resultat->V_Produit);
	StockRepart1(AgriEnCours->Resultat->V_Charge);
	StockRepart1(AgriEnCours->Resultat->V_ChStruct);
	StockRepart1(AgriEnCours->Resultat->V_RecDiv);
	StockRepart1(AgriEnCours->Resultat->V_DepDiv);
	StockRepart1(AgriEnCours->Resultat->V_RecFam);
	StockRepart1(AgriEnCours->Resultat->V_DepFam);
	StockRepart1(AgriEnCours->Resultat->V_ExtNeg);
	StockRepart1(AgriEnCours->Resultat->V_ExtPos);
	if(AgriEnCours->V_Petit->Nbelt==0) return;

	AgriEnCours->V_ItemRepart->ins(AgriEnCours->QuanValPetit->ItemRepart);
	/*
	 int n;
	 CL_ItemRepart *itemRepart;
	 for(n=0;n<AgriEnCours->V_ItemRepart->Nbelt;n++)
	 itemRepart=AgriEnCours->V_ItemRepart->Vecteur[n];
	 */
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::StockRepart1(CL_Vecteur<CL_QuanVal>*vecteur)
{
	int i;
	CL_QuanVal *quanVal;
	for(i=0;i<vecteur->Nbelt;i++)
	{
		quanVal=vecteur->Vecteur[i];
		if(quanVal->ItemRepart)
		AgriEnCours->V_ItemRepart->ins(quanVal->ItemRepart);
	}
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::OcccClick(TObject *Sender)
{
	TresoDefOcccFrm->Show();
}
//---------------------------------------------------------------------------

