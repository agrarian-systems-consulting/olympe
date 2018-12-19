//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Forme0.h"
#include "TVChoixRepart.h"

#include "TresoRepart.h"
//#include "TresoQouV.h"
#include "TresoRes.h"
#include "TresoEnum.h"
#include "TresoDefOccc.h"
#include "FenRepart.h"

#include "CL_Trad.h"
#include "Aide.h"

#include "Treso.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme0"
#pragma resource "*.dfm"
TTresoFrm *TresoFrm;

extern CL_ES *ES;
extern CL_Trad *T;

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
		ShowMessage(L_ChoixAgri); //"Choisir un agriculteur");
		return;
	}
	FenRepartFrm->AgriEnCours=AgriEnCours;
	CompleteQuanVal();
	/*
	 switch(RGValOuQ->ItemIndex)
	 {
	 case 0:Caption =L_TresoVal;break;//"Tresorerie en Valeur";break;
	 case 1:Caption =L_TresoQuant;break;//"Tresorerie en Quantité";break;
	 case 2:Caption =L_TresoAutre;break;//"Tresorerie Autre";break;  // a voir
	 }
	 */
	Origine=1;
	if(V_CatRepart->Nbelt==0)
	{
		cat=new CL_Categorie(L_Standard,0); //"Standard",0);
		V_CatRepart->ins(cat);
	}
	Forme0Frm->CreeTVRepart(TVChoixRepartFrm->TV);
//	TresoRepartFrm->CalculEn=VALEUR;//par défaut 200810  161211

}
// a sup
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::QuantOuVal(void)
{
	TresoRepartFrm->CalculEn=VALEUR;
	/*
	 if(RGValOuQ->ItemIndex==0)
	 TresoRepartFrm->CalculEn=VALEUR;
	 else
	 TresoRepartFrm->CalculEn=QUANTITE;
	 */
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
	TVChoixRepartFrm->AFaire=AnsiString(L_Definir); //"Definir");
	TVChoixRepartFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::ProduitsClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=PRODUIT;

	TresoRepartFrm->RGRepart->Visible=true; //161211

	if(TresoRepartFrm->RGRepart->ItemIndex==0)TresoRepartFrm->CalculEn=VALEUR;
	else TresoRepartFrm->CalculEn=QUANTITE;

	TresoRepartFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::OperationnellesClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=CHARGE;

	TresoRepartFrm->RGRepart->Visible=true; //161211

	if(TresoRepartFrm->RGRepart->ItemIndex==0)TresoRepartFrm->CalculEn=VALEUR;
	else TresoRepartFrm->CalculEn=QUANTITE;

	TresoRepartFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::StructureClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=CHSTRUCT;

	TresoRepartFrm->RGRepart->Visible=false; //161211

	TresoRepartFrm->CalculEn=VALEUR;

	TresoRepartFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::DivRecettesClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=RECDIV;

	TresoRepartFrm->RGRepart->Visible=false; //161211

	TresoRepartFrm->CalculEn=VALEUR;

	TresoRepartFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::DivDepensesClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=DEPDIV;

	TresoRepartFrm->RGRepart->Visible=false; //161211

	TresoRepartFrm->CalculEn=VALEUR;

	TresoRepartFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::PrivRecettesClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=RECFAM;

	TresoRepartFrm->RGRepart->Visible=false; //161211

	TresoRepartFrm->CalculEn=VALEUR;

	TresoRepartFrm->Show();
}

//---------------------------------------------------------------------------
void __fastcall TTresoFrm::ExternalitesClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=EXTER; //EXTNEG et EXTPOS

	TresoRepartFrm->RGRepart->Visible=false;//161211

	TresoRepartFrm->CalculEn=QUANTITE;

	TresoRepartFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::InvestissementClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=IMMO;

	TresoRepartFrm->RGRepart->Visible=false; //161211

	TresoRepartFrm->CalculEn=VALEUR;

	TresoRepartFrm->BtBnCalculValClick(this);//130107
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::PetitMatrielClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=PETITMAT;
	TresoRepartFrm->CalculEn=VALEUR;

	TresoRepartFrm->RGRepart->Visible=false; //161211

	if(AgriEnCours->V_Petit->Nbelt==0)
	{
		ShowMessage(L_Aucun); //"Aucun élément");
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

	TresoRepartFrm->RGRepart->Visible=false; //161211

	TresoRepartFrm->BtBnCalculValClick(this);//130107
//	TresoRepartFrm->Show();          si entree globale
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::PrivDepensesClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=DEPFAM;

	TresoRepartFrm->RGRepart->Visible=false; //161211

	TresoRepartFrm->CalculEn=VALEUR;
	TresoRepartFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::EnCoursClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=DETTE;
	TresoRepartFrm->RGRepart->Visible=false; //161211

	TresoRepartFrm->CalculEn=VALEUR;
	TresoRepartFrm->BtBnCalculValClick(this);//130107
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::TresoDetailClick(TObject *Sender)
{
	TresoResFrm->Origine=0;
	TresoResFrm->TypeSortie=DETAIL;
	TresoRepartFrm->RGRepart->Visible=false; //161211

	TresoResFrm->Nature=AGRI;
	TresoRepartFrm->CalculEn=VALEUR;
	TresoResFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::TresoSemiDetailClick(TObject *Sender)
{
	TresoResFrm->Origine=0;
	TresoResFrm->TypeSortie=SEMIDETAIL;
	TresoRepartFrm->RGRepart->Visible=false; //161211

	TresoRepartFrm->CalculEn=VALEUR;
	TresoResFrm->Nature=AGRI;
	TresoResFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::TresoSyntheseClick(TObject *Sender)
{
	TresoResFrm->Origine=0;
	TresoResFrm->TypeSortie=GLOBAL;
	TresoRepartFrm->RGRepart->Visible=false; //161211

	TresoRepartFrm->CalculEn=VALEUR;
	TresoResFrm->Nature=AGRI;
	TresoResFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TTresoFrm::QuantiteClick(TObject *Sender)
{
	TresoResFrm->Origine=0;
	TresoResFrm->TypeSortie=DETAIL;
	TresoRepartFrm->RGRepart->Visible=false; //161211

	TresoResFrm->Nature=AGRI;
	TresoRepartFrm->CalculEn=QUANTITE;//140107
	TresoResFrm->Show();

}
//---------------------------------------------------------------------------

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
	if(AgriEnCours->LstTroupeaux->Count>0)//191205
	{
		CreeQuanValTroupeaux();
	}
	CompleteQuanVal1(AgriEnCours->Resultat->V_VenteAni, BESTIAUX);
	CompleteQuanVal1(AgriEnCours->Resultat->V_AchatAni, BESTIAUX);

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
	CL_Vecteur<CL_ItemRepart> *V_ItemRepart; //141205

	CL_ItemRepart *itemRepart;
	V_ItemRepart=AgriEnCours->V_ItemRepart;
	for(i=0;i<V_ItemRepart->Nbelt;i++)
	{
		itemRepart=V_ItemRepart->Vecteur[i];
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
void __fastcall TTresoFrm::CreeQuanValTroupeaux(void)
{
	int i,j,n;
	CL_Troupeau *troupeau;
	CL_InvAni *invAni;
	CL_QuanVal *quanVal;
	CL_Bestiaux *animal;
	AgriEnCours->Resultat->V_VenteAni->purge();
	AgriEnCours->Resultat->V_AchatAni->purge();

	for(i=0;i<AgriEnCours->LstTroupeaux->Count;i++)
	{
		troupeau=(CL_Troupeau*)AgriEnCours->LstTroupeaux->Items[i];
		for(j=0;j<troupeau->V_InvAni->Nbelt;j++)
		{
			invAni=troupeau->V_InvAni->Vecteur[j];
			if(EstVide(invAni->ValVente)==false)
			{
				animal=invAni->Animal;
				quanVal=new CL_QuanVal;
				quanVal->Item=animal;
				quanVal->No=animal->No;
				AgriEnCours->Resultat->V_VenteAni->ins(quanVal);
				for(n=0;n<N_X;n++)
				{
					quanVal->Val[n] +=invAni->ValVente[n];
					quanVal->Qte[n] +=invAni->Vente[n];
				}
			}
			if(EstVide(invAni->ValAchat)==false)
			{
				animal=invAni->Animal;
				quanVal=new CL_QuanVal;
				quanVal->Item=animal;
				quanVal->No=animal->No;
				AgriEnCours->Resultat->V_AchatAni->ins(quanVal);
				for(n=0;n<N_X;n++)
				{
					quanVal->Val[n] +=invAni->ValAchat[n];
					quanVal->Qte[n] +=invAni->Achat[n];
				}
			}
		}
	}
}
//--------------------------------------------------------------------------
bool TTresoFrm::EstVide(float *valeur) //160905
		{
	int n;
	for (n = 0; n < N_X; n++)
		if (valeur[n] != 0.)
			return false;
	return true;
}

//---------------------------------------------------------------------------
void __fastcall TTresoFrm::StockRepart(void)
{
	AgriEnCours->V_ItemRepart->vide();

	StockRepart1(AgriEnCours->Resultat->V_Produit);

	StockRepart1(AgriEnCours->Resultat->V_VenteAni); //201205
	StockRepart1(AgriEnCours->Resultat->V_AchatAni);

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

/*
 //---------------------------------------------------------------------------
 void __fastcall TTresoFrm::RGValOuQClick(TObject *Sender)
 {
 switch(RGValOuQ->ItemIndex)
 {
 case 0:
 Caption =L_TresoVal;//"Tresorerie en Valeur";
 break;
 case 1:
 Caption =L_TresoQuant;//"Tresorerie en Quantité";
 break;
 }

 // mal placé a voir !!!!!!
 TresoRepartFrm->Origine=0;

 }
 */
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TTresoFrm::TexteChaine(void) {
	L_ChoixAgri = T->TrouveTexte("TresoFrm", "L_ChoixAgri");
	L_TresoVal = T->TrouveTexte("TresoFrm", "L_TresoVal");
	L_TresoQuant = T->TrouveTexte("TresoFrm", "L_TresoQuant");
	L_TresoAutre = T->TrouveTexte("TresoFrm", "L_TresoAutre");
	L_Standard = T->TrouveTexte("TresoFrm", "L_Standard");
	L_Definir = T->TrouveTexte("TresoFrm", "L_Definir");
	L_Aucun = T->TrouveTexte("TresoFrm", "L_Aucun");
}

//--------------------------------------------
void TTresoFrm::IniCaption(void) {
	Charges->Caption = T->LC_LabPCharge;
	Depenses->Caption = T->LC_ChargesDivers;
	PrivDepenses->Caption = T->LC_ChargesDivers;
	TresoDetail->Caption = LC_TresoDetail;
	TresoDetail->Caption = LC_TresoDetail;
	Divers1->Caption = T->LC_DIVERS1;
	EnCours->Caption = T->LC_BtEnsEnCours;
	Externalites->Caption = T->LC_TSExternalite;
	Finance->Caption = LC_Finance;
	Immo->Caption = T->LC_Immo;
	Investissement->Caption = LC_Investissement;
	Occc->Caption = T->LC_Occc;
	Oprationnelles1->Caption = LC_Oprationnelles1;
	PetitMatriel->Caption = T->LC_PetitMatriel;
	Prive->Caption = LC_Prive;
	Produits1->Caption = T->LC_BtBnProduit;
	Recettes->Caption = T->LC_Produits1;
	PrivRecettes->Caption = T->LC_Produits1;
	Definition->Caption = T->LC_Definition;
	Resultat->Caption = T->LC_RESULTATS;
	TresoSemiDetail->Caption = LC_TresoSemiDetail;
	TresoSemiDetail->Caption = LC_TresoSemiDetail;
	Structure1->Caption = T->LC_Structure1;
	TresoSynthese->Caption = T->LC_BtSyntDetail;
	TresoSynthese->Caption = T->LC_BtSyntDetail;
//    Total->Caption=T->LC_LabTotal;
	TresoFrm->Caption = T->LC_Tresorerie;
//???    Troupeaux->Caption=LC_Troupeau;
//    TypeValQuant->Caption=LC_TypeValQuant;
}
//--------------------------------------------
void TTresoFrm::TexteCaption(void) {
	LC_LabPCharge = T->TrouveCaption("CL_Trad", "LC_LabPCharge");
	LC_ChargesDivers = T->TrouveCaption("CL_Trad", "LC_ChargesDivers");
	LC_TresoDetail = T->TrouveCaption("Treso", "LC_TresoDetail");
	LC_DIVERS1 = T->TrouveCaption("CL_Trad", "LC_DIVERS1");
	LC_BtEnsEnCours = T->TrouveCaption("CL_Trad", "LC_BtEnsEnCours");
	LC_TSExternalite = T->TrouveCaption("CL_Trad", "LC_TSExternalite");
	LC_Finance = T->TrouveCaption("Treso", "LC_Finance");
	LC_Immo = T->TrouveCaption("CL_Trad", "LC_Immo");
	LC_Investissement = T->TrouveCaption("Treso", "LC_Investissement");
	LC_Occc = T->TrouveCaption("CL_Trad", "LC_Occc");
	LC_Oprationnelles1 = T->TrouveCaption("Treso", "LC_Oprationnelles1");
	LC_PetitMatriel = T->TrouveCaption("CL_Trad", "LC_PetitMatriel");
	LC_Prive = T->TrouveCaption("Treso", "LC_Prive");
	LC_BtBnProduit = T->TrouveCaption("CL_Trad", "LC_BtBnProduit");
	LC_Produits1 = T->TrouveCaption("CL_Trad", "LC_Produits1");
	LC_Definition = T->TrouveCaption("CL_Trad", "LC_Definition");
	LC_RESULTATS = T->TrouveCaption("CL_Trad", "LC_RESULTATS");
	LC_TresoSemiDetail = T->TrouveCaption("Treso", "LC_TresoSemiDetail");
	LC_Structure1 = T->TrouveCaption("CL_Trad", "LC_Structure1");
	LC_BtSyntDetail = T->TrouveCaption("CL_Trad", "LC_BtSyntDetail");
	LC_LabTotal = T->TrouveCaption("CL_Trad", "LC_LabTotal");
	LC_Tresorerie = T->TrouveCaption("CL_Trad", "LC_Tresorerie");
	LC_TypeValQuant = T->TrouveCaption("Treso", "LC_TypeValQuant");
//??       LC_Troupeau=T->TrouveCaption("Treso" ,"LC_Troupeau");

	IniCaption();

}
//--------------------------------------------

//111206
void __fastcall TTresoFrm::BestiauxVenteClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=VENTE;
	QuantOuVal();
	TresoRepartFrm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TTresoFrm::BestiauxAchatClick(TObject *Sender)
{
	TresoRepartFrm->Origine=0;
	Nature=ACHAT;
	QuantOuVal();
	TresoRepartFrm->Show();

}
//---------------------------------------------------------------------------

void __fastcall TTresoFrm::TroupeauxClick(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

