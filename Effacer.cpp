//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "CL_Trad.h"
#include "AgriClasst.h"
#include "Main.h"
#include "Aide.h"

#include "Effacer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEffacerFrm *EffacerFrm;
extern CL_ES *ES;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TEffacerFrm::TEffacerFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TEffacerFrm::FormActivate(TObject *Sender)
{
	static bool debut=true;
	if(debut==true)
	{
		debut=false;
		cocher();
	}
}

//---------------------------------------------------------------------------
void __fastcall TEffacerFrm::BtBnOKClick(TObject *Sender)
{
	int rep;
	rep=MessageBox(Handle,L_NettoyerQ.c_str(),L_NettoyerT.c_str(),
			//rep=MessageBox(Handle,"Vous voulez vraiment nettoyer","NETTOYAGE",
			MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDNO) return;
	else effacer();
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TEffacerFrm::BtBnFermerClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TEffacerFrm::cocher(void)
{
	int i,iMax;
	//Unite Tva
	iMax=ChLBUnite->Items->Count;
	for(i=0;i<iMax;i++)ChLBUnite->Checked[i]=false;
	//Définitions
	iMax=ChLBDef->Items->Count;
	for(i=0;i<iMax;i++)ChLBDef->Checked[i]=false;
	//Atelier
	iMax=ChLBAtelier->Items->Count;
	for(i=0;i<iMax;i++)ChLBAtelier->Checked[i]=false;
	//Alea
	iMax=ChLBAlea->Items->Count;
	for(i=0;i<iMax;i++)ChLBAlea->Checked[i]=false;
	// Agriculteurs
	ChBAgri->Checked=false;
	// Ensemble
	ChBEnsemble->Checked=false;
	//Indic Etat
	iMax=ChLBIndEtat->Items->Count;
	for(i=0;i<iMax;i++)ChLBIndEtat->Checked[i]=false;
	// Classification
	ChBClassif->Checked=false;
	ChBTypoAgri->Checked=false;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TEffacerFrm::effacer(void)
{
	bool nettoye;
	int n;
	int n1,n2;
	CL_Agriculteur *agri;
	//Ensemble
	if(ChBEnsemble->Checked==true)
	{
		V_Ensemble->purge();
		ES->Supprimable();
		EnsembleEnCours=NULL;
	}
	//Agriculteur
	if(ChBAgri->Checked==true)
	{
		V_Agriculteur->nettoie();
		ES->Supprimable();
		AgriEnCours=NULL;
	}
	//Classification
	if(ChBTypoAgri->Checked==true)
	{
		for(n=0;n<V_Agriculteur->Nbelt;n++)
		{
			agri=V_Agriculteur->Vecteur[n];
			agri->LstCritere->Clear();
		}
	}

	if(ChBClassif->Checked==true)
	{
		V_TypeZone->nettoie();
		ES->Supprimable();
		V_CatTypeZone->nettoie();
		ES->Supprimable();
		AgriClasstFrm->ChLBCatTypeZone->Clear();
	}
	//Alea
	nettoye=false;
	if(ChLBAlea->Checked[0]==true)
	{
		V_TendPrixProd->nettoie();
		V_TendPrixCharge->nettoie();
		V_ScenPrixProd->nettoie();
		V_ScenPrixCharge->nettoie();
		nettoye=true;
	}
	if(ChLBAlea->Checked[1]==true)
	{
		V_TendQProd->nettoie();
		V_TendQCharge->nettoie();
		V_ScenQProd->nettoie();
		V_ScenQCharge->nettoie();
		V_TendQExt->nettoie();
		V_ScenQExt->nettoie();
		nettoye=true;
	}
	if(nettoye==true) ES->Supprimable();

	//Atelier
	nettoye=false;
	if(ChLBAtelier->Checked[0]==true) {V_Culture->nettoie();nettoye=true;}
	if(ChLBAtelier->Checked[1]==true) {V_Animaux->nettoie();nettoye=true;}
	if(ChLBAtelier->Checked[3]==true) {V_Perenne->nettoie();nettoye=true;}
	/*
	 if(ChLBAtelier->Checked[3]==true) {
	 V_Perenne->nettoie();          //300408
	 ES->Supprimable();
	 V_Espece->nettoie();
	 nettoye=true;
	 }
	 */
	if(ChLBAtelier->Checked[4]==true) {V_Vivrier->nettoie();nettoye=true;}
	if(nettoye==true) ES->Supprimable();

	nettoye=false;
	if(ChLBAtelier->Checked[0]==true) {V_CatCulture->nettoie();nettoye=true;}
	if(ChLBAtelier->Checked[1]==true) {V_CatAnimaux->nettoie();nettoye=true;}
	if(ChLBAtelier->Checked[4]==true) {V_CatVivrier->nettoie();nettoye=true;}
	if(nettoye==true) ES->Supprimable();

	//Espece
	if(ChLBAtelier->Checked[2]==true)
	{
		V_Espece->nettoie();
		ES->Supprimable();
	}

	//Indicateurs etat...
	//d'abord etat   un etat peut contenir des indicateurs
	nettoye=false;
	if(ChLBIndEtat->Checked[1]==true) {V_EtatSortie->nettoie();nettoye=true;}
	if(nettoye==true) ES->Supprimable();

	if(ChLBIndEtat->Checked[2]==true) {V_CatSerieComp->nettoie();nettoye=true;}
	if(nettoye==true) ES->Supprimable();
	//indicateur
	if(ChLBIndEtat->Checked[0]==true)
	{

		while(1)
		{
			n1=V_Indicateur->Nbelt;
			V_Indicateur->nettoie();
			n2=V_Indicateur->Nbelt;
			ES->Supprimable();
			if(n2==n1)break;
		}
		//nettoye=true;
	}
	//if(nettoye==true) ES->Supprimable();

	nettoye=false;
	if(ChLBIndEtat->Checked[0]==true) {V_CatIndic->nettoie();nettoye=true;}
	if(ChLBIndEtat->Checked[1]==true) {V_CatEtatSortie->nettoie();nettoye=true;}
	if(nettoye==true) ES->Supprimable();

	//Item produits charges...
	nettoye=false;
	if(ChLBDef->Checked[0]==true) {V_Produit->nettoie();nettoye=true;}
	if(ChLBDef->Checked[1]==true) {V_Charge->nettoie();nettoye=true;}
	if(ChLBDef->Checked[2]==true) {V_Externalite->nettoie();nettoye=true;}
	if(ChLBDef->Checked[3]==true) {V_Bestiaux->nettoie();nettoye=true;}
	if(ChLBDef->Checked[4]==true) {V_Calendrier->nettoie();nettoye=true;}

	if(ChLBDef->Checked[6]==true) {V_ChStruct->nettoie();nettoye=true;}
	if(ChLBDef->Checked[7]==true) {V_DepDiv->nettoie();nettoye=true;}
	if(ChLBDef->Checked[8]==true) {V_RecDiv->nettoie();nettoye=true;}

	if(ChLBDef->Checked[10]==true) {V_RecFam->nettoie();nettoye=true;}
	if(ChLBDef->Checked[11]==true) {V_DepFam->nettoie();nettoye=true;}

	if(ChLBDef->Checked[13]==true) {V_Variable->nettoie();nettoye=true;}
	if(nettoye==true) ES->Supprimable();

	nettoye=false;
	if(ChLBDef->Checked[0]==true) {V_CatProduit->nettoie();nettoye=true;}
	if(ChLBDef->Checked[1]==true) {V_CatCharge->nettoie();nettoye=true;}
	//if(ChLBDef->Checked[2]==true) { V_CatExternalite->nettoie();nettoye=true;}
	if(ChLBDef->Checked[3]==true) {V_CatBestiaux->nettoie();nettoye=true;}
	// inutile pas de V_CatCalendrier

	if(ChLBDef->Checked[6]==true) {V_CatChStruct->nettoie();nettoye=true;}
	if(ChLBDef->Checked[7]==true) {V_CatDepDiv->nettoie();nettoye=true;}
	if(ChLBDef->Checked[8]==true) {V_CatRecDiv->nettoie();nettoye=true;}

	if(ChLBDef->Checked[10]==true) {V_CatRecFam->nettoie();nettoye=true;}
	if(ChLBDef->Checked[11]==true) {V_CatDepFam->nettoie();nettoye=true;}

	if(ChLBDef->Checked[13]==true) {V_CatVar->nettoie();nettoye=true;}
	if(nettoye==true) ES->Supprimable();

	// Unite Tva
	nettoye=false;
	if(ChLBUnite->Checked[0]==true) {V_SystemeUnite->nettoie();nettoye=true;}
	if(ChLBUnite->Checked[1]==true) {V_Tva->nettoie();nettoye=true;}

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void __fastcall TEffacerFrm::avantEffacerIndic(void)
{
	int i,j,k;
	CL_Indicateur *indicateur;
	CL_Arbre *arbre;
	ST_Branche branche;
	CL_Elt *elt;
	for(i=0;i<V_Indicateur->Nbelt;i++)
	{
		indicateur=V_Indicateur->Vecteur[i];
		arbre=indicateur->Prog->Arbre;
		if(arbre==NULL) continue;

		for(j=0;j<arbre->BrancheX;j++)
		{
			branche=arbre->LesBranches[j];
			if(branche.code!=IDENT)continue;
			for(k=0;k<V_Elt->Nbelt;k++)
			{
				elt=V_Elt->Vecteur[k];
				if( elt->NoFamille== branche.arg[0]
						&& elt->NoCategorie==branche.arg[1]
						&& elt->NoItem== branche.arg[2])
				{
					if(elt->Categorie)elt->Categorie->Supprimable=false;
					if(elt->Item) elt->Item->Supprimable= false;
//                   if(elt->Indic)    elt->Indic->Supprimable=    false;
				}
			}
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TEffacerFrm::BtDefAucunClick(TObject *Sender)
{
	int i,iMax;
	//Définitions
	iMax=ChLBDef->Items->Count;
	for(i=0;i<iMax;i++)ChLBDef->Checked[i]=false;

}
//---------------------------------------------------------------------------

void __fastcall TEffacerFrm::BtDefTousClick(TObject *Sender)
{
	int i,iMax;
	//Définitions
	iMax=ChLBDef->Items->Count;
	for(i=0;i<iMax;i++)ChLBDef->Checked[i]=true;

}
//---------------------------------------------------------------------------

void __fastcall TEffacerFrm::BtProAucunClick(TObject *Sender)
{
	int i,iMax;
	//Atelier
	iMax=ChLBAtelier->Items->Count;
	for(i=0;i<iMax;i++)ChLBAtelier->Checked[i]=false;
}
//---------------------------------------------------------------------------
void __fastcall TEffacerFrm::BtProTousClick(TObject *Sender)
{
	int i,iMax;
	//Atelier
	iMax=ChLBAtelier->Items->Count;
	for(i=0;i<iMax;i++)ChLBAtelier->Checked[i]=true;
}
//---------------------------------------------------------------------------

void __fastcall TEffacerFrm::BtIndAucunClick(TObject *Sender)
{
	int i,iMax;
	iMax=ChLBIndEtat->Items->Count;
	for(i=0;i<iMax;i++)ChLBIndEtat->Checked[i]=false;
}
//---------------------------------------------------------------------------

void __fastcall TEffacerFrm::BtIndTousClick(TObject *Sender)
{
	int i,iMax;
	iMax=ChLBIndEtat->Items->Count;
	for(i=0;i<iMax;i++)ChLBIndEtat->Checked[i]=true;
}
//---------------------------------------------------------------------------
void TEffacerFrm::TexteChaine(void) {
	L_NettoyerQ = T->TrouveTexte("EffacerFrm", "L_NettoyerQ");
	L_NettoyerT = T->TrouveTexte("EffacerFrm", "L_NettoyerT");
}
//--------------------------------------------
void TEffacerFrm::IniCaption(void) {
	GBAgri->Caption = T->LC_GBAgri;
	ChBAgri->Caption = T->LC_GBAgri;
	GBAlea->Caption = T->LC_GBAlea;
	GBAlea->Caption = T->LC_GBAlea;
	BtIndAucun->Caption = T->LC_BtIndAucun;
	BtProAucun->Caption = T->LC_BtIndAucun;
	BtDefAucun->Caption = T->LC_BtIndAucun;
	ChBClassif->Caption = T->LC_LabZone;
	LabInd->Caption = LC_LabInd;
	GBDefinition->Caption = T->LC_GBDefinition;
//    Label11->Caption=T->LC_Label11;
	EffacerFrm->Caption = LC_EffacerFrm;
	ChBEnsemble->Caption = T->LC_ChBEnsemble;
	GBEnsemble->Caption = T->LC_GBEnsemble;
	BtBnEffacer->Caption = T->LC_BtBnEffacer;
	ChBClassif->Caption = T->LC_PanClassif;
	GBProduction->Caption = T->LC_PRODUCTIONS;
	GBProduction->Caption = T->LC_PRODUCTIONS;
	BtIndTous->Caption = T->LC_BtIndTous;
	BtProTous->Caption = T->LC_BtIndTous;
	BtDefTous->Caption = T->LC_BtIndTous;

	ChLBUnite->Items->Strings[0] = T->LC_BtBnUnite;
	ChLBUnite->Items->Strings[1] = T->LC_BtBnTva;

	ChLBDef->Items->Strings[0] = T->LC_BtBnProduit;
	ChLBDef->Items->Strings[1] = LC_ChOpe;
	ChLBDef->Items->Strings[2] = LC_Exter;
	ChLBDef->Items->Strings[3] = LC_Troupeaux;
	ChLBDef->Items->Strings[4] = LC_PerTrav;
	ChLBDef->Items->Strings[6] = LC_ChStruct;
	ChLBDef->Items->Strings[7] = LC_DepDiv;
	ChLBDef->Items->Strings[8] = LC_RecDiv;
	ChLBDef->Items->Strings[10] = LC_RecFam;
	ChLBDef->Items->Strings[11] = LC_DepFam;
	ChLBDef->Items->Strings[13] = LC_Var;

	ChLBAtelier->Items->Strings[0] = LC_Cultures;
	ChLBAtelier->Items->Strings[1] = LC_Animaux;
	ChLBAtelier->Items->Strings[2] = LC_Phases;
	ChLBAtelier->Items->Strings[3] = LC_Perennes;
	ChLBAtelier->Items->Strings[4] = LC_Vivriers;

	ChBAgri->Caption = LC_Agri;
	ChBEnsemble->Caption = LC_Ensemble;

	ChBClassif->Caption = LC_Classif;
	ChBTypoAgri->Caption = LC_TypoAgri;

	ChLBAlea->Items->Strings[0] = LC_Prix;
	ChLBAlea->Items->Strings[1] = LC_Quantite;

	ChLBIndEtat->Items->Strings[0] = LC_Indic;
	ChLBIndEtat->Items->Strings[1] = LC_Etat;
	ChLBIndEtat->Items->Strings[2] = LC_Comp;
	GBTypologie->Caption = LC_Typologie;

}
//--------------------------------------------
void TEffacerFrm::TexteCaption(void) {
	LC_GBAgri = T->TrouveCaption("CL_Trad", "LC_GBAgri");
	LC_GBAlea = T->TrouveCaption("CL_Trad", "LC_GBAlea");
	LC_BtIndAucun = T->TrouveCaption("CL_Trad", "LC_BtIndAucun");
	LC_LabZone = T->TrouveCaption("CL_Trad", "LC_LabZone");
	LC_LabInd = T->TrouveCaption("Effacer", "LC_LabInd");
	LC_GBDefinition = T->TrouveCaption("CL_Trad", "LC_GBDefinition");
	LC_Label11 = T->TrouveCaption("CL_Trad", "LC_Label11");
	LC_EffacerFrm = T->TrouveCaption("Effacer", "LC_EffacerFrm");
	LC_ChBEnsemble = T->TrouveCaption("CL_Trad", "LC_ChBEnsemble");
	LC_GBEnsemble = T->TrouveCaption("CL_Trad", "LC_GBEnsemble");
	LC_BtBnEffacer = T->TrouveCaption("CL_Trad", "LC_BtBnEffacer");
	LC_PanClassif = T->TrouveCaption("CL_Trad", "LC_PanClassif");
	LC_PRODUCTIONS = T->TrouveCaption("CL_Trad", "LC_PRODUCTIONS");
	LC_BtIndTous = T->TrouveCaption("CL_Trad", "LC_BtIndTous");

	LC_ChOpe = T->TrouveCaption("Effacer", "LC_ChOpe");
	LC_Exter = T->TrouveCaption("Effacer", "LC_Exter");
	LC_Troupeaux = T->TrouveCaption("Effacer", "LC_Troupeaux");
	LC_PerTrav = T->TrouveCaption("Effacer", "LC_PerTrav");
	LC_ChStruct = T->TrouveCaption("Effacer", "LC_ChStruct");
	LC_DepDiv = T->TrouveCaption("Effacer", "LC_DepDiv");
	LC_RecDiv = T->TrouveCaption("Effacer", "LC_RecDiv");
	LC_RecFam = T->TrouveCaption("Effacer", "LC_RecFam");
	LC_DepFam = T->TrouveCaption("Effacer", "LC_DepFam");
	LC_Var = T->TrouveCaption("Effacer", "LC_Var");

	LC_Cultures = T->TrouveCaption("Effacer", "LC_Cultures");
	LC_Animaux = T->TrouveCaption("Effacer", "LC_Animaux");
	LC_Phases = T->TrouveCaption("Effacer", "LC_Phases");
	LC_Perennes = T->TrouveCaption("Effacer", "LC_Perennes");
	LC_Vivriers = T->TrouveCaption("Effacer", "LC_Vivriers");

	LC_Agri = T->TrouveCaption("Effacer", "LC_Agri");
	LC_Ensemble = T->TrouveCaption("Effacer", "LC_Ensemble");
	LC_Classif = T->TrouveCaption("Effacer", "LC_Classif");
	LC_TypoAgri = T->TrouveCaption("Effacer", "LC_TypoAgri");

	LC_Prix = T->TrouveCaption("Effacer", "LC_Prix");
	LC_Quantite = T->TrouveCaption("Effacer", "LC_Quantite");

	LC_Indic = T->TrouveCaption("Effacer", "LC_Indic");
	LC_Etat = T->TrouveCaption("Effacer", "LC_Etat");
	LC_Comp = T->TrouveCaption("Effacer", "LC_Comp");
	LC_Typologie = T->TrouveCaption("Effacer", "LC_Typologie");

	IniCaption();

}

//---------------------------------------------------------------------------
bool __fastcall TEffacerFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=210;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

void __fastcall TEffacerFrm::Button1Click(TObject *Sender)
{
//    CallHelp=false;
	HelpContext=210;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);

}
//---------------------------------------------------------------------------

