//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "Forme0.h"
#include "TendanceEnum.h"
#include "AleaPrix.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "GereAleaPrix.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
extern CL_ES *ES;
extern CL_Trad *T;

TGereAleaPrixFrm *GereAleaPrixFrm;
//---------------------------------------------------------------------------
__fastcall TGereAleaPrixFrm::TGereAleaPrixFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TGereAleaPrixFrm::FormActivate(TObject *Sender)
{
	if(Origine==0) //mis à 0 dans Main
	{
		Origine=1;
		LabelModifie->Visible=false;
		OrdreModif=false;
		No=0; //eviter reclassement si pas de sélection ???
		Tendance=NULL;
		BoutonEnabled(true);//(false) 160206
	}
	HelpFile="Olympe.hlp";
	/*
	 nature=new int[4];
	 nature[0]=PRIX;nature[1]=PRODUIT;nature[2]=TENDANCE;nature[3]=0 branche NON déployée
	 QUANTITE       CHARGE            SCENARIO           1 branchz déployée
	 EXTER
	 */

	CreeTV();
}
//---------------------------------------------------------------------------
void __fastcall TGereAleaPrixFrm::BoutonEnabled(bool val)
{
	BtCopier->Enabled =val;
	Btsupprimer->Enabled =val;
	BtBnCreer->Enabled =val;
	BtModifier->Enabled =val;
}
//---------------------------------------------------------------------------
void __fastcall TGereAleaPrixFrm::BtBnQuitterClick(TObject *Sender)
{
	int rep;
	rep=MessageBox(Handle,T->L_QuitQ.c_str(),T->L_QuitT.c_str(),
			//rep=MessageBox(Handle,"Vous voulez vraiment quitter","QUITTER OLYMPE",
			MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDYES) Application->Terminate();
	else return;

}
//---------------------------------------------------------------------------
//TvDblClick
//                       level       0           1             2
//                                  Produits
//												 Tendance
//                                                 				tendance_no1
//                                                 Scenario
//                                  Charges
//---------------------------------------------------------------------------
void __fastcall TGereAleaPrixFrm::TVDblClick(TObject *Sender)
{
	TTreeNode *elt,*parent;
//	if(CEstBon()==false) return;
	if(AleaPrixFrm->Visible==true)AleaPrixFrm->BtBnStockerClick(this);
	AleaXXFrm=AleaPrixFrm;
	if(TV->Selected==NULL) return;

	elt=TV->Selected;
	if(elt->Level<2)
	{
		Nature=(int *)elt->Data;
		if(Nature==NULL) return; //
		if(Nature[3]==0)Nature[3]=1;
		else Nature[3]=0;
		memcpy(AleaPrixFrm->Nature,Nature,sizeof(int)*4);
		BoutonEnabled(false);

		return;
	}
	else
	{
		BoutonEnabled(true);
	}
	elt=TV->Selected;
	parent=elt->Parent;
	Nature=(int *)parent->Data;
	Nature[3]=1;
//    ShowMessage(AnsiString(Nature));
	memcpy(AleaPrixFrm->Nature,Nature,sizeof(int)*4);
	//if(Nature[0]==PRIX) toujours vrai pour GereAleaPrix
	if(Nature[1]==PRODUIT)
	{
		AleaPrixFrm->TitreColonne2=L_Prod; //"PRODUIT";
		if(Nature[2]==TENDANCE)
		{
			V_Tendance=V_TendPrixProd;
			AleaPrixFrm->Caption=L_PrixTendProd; //"PRIX: TENDANCE: Produit";
		}
		else if(Nature[2]==SCENARIO)
		{
			V_Tendance=V_ScenPrixProd;
			AleaPrixFrm->Caption=L_PrixScenProd; //PRIX: SCENARIO: Produit";
		}
		else
		ShowMessage("Problème dans GereAleaPrix");
	}
	else if(Nature[1]==CHARGE)
	{
		AleaPrixFrm->TitreColonne2=L_Charge; //"CHARGE";
		if(Nature[2]==TENDANCE)
		{
			V_Tendance=V_TendPrixCharge;
			AleaPrixFrm->Caption=L_PrixTendCha; //"PRIX: TENDANCE: Charge";
		}
		else if(Nature[2]==SCENARIO)
		{
			V_Tendance=V_ScenPrixCharge;
			AleaPrixFrm->Caption=L_PrixScenCha; //"PRIX: SCENARIO: Charge";
		}
		else
		ShowMessage("Problème dans GereAleaPrix");
	}
	else
	ShowMessage("Problème dans GereAleaPrix");
	/*
	 informé dans Forme0/CreeTVAleaPrix
	 nature=new int[4];
	 nature[0]=PRIX;nature[1]=PRODUIT;nature[2]=TENDANCE;nature[3]=0 branche NON déployée
	 QUANTITE       CHARGE            SCENARIO           1 branchz déployée
	 EXTER
	 */
	if(elt->Text=="[...]")
	{
		BtBnCreerClick(this);
	}
	else
	{
		Tendance=(CL_Tendance*)elt->Data;
	}
	AffTendance();
}
//---------------------------------------------------------------------------
void __fastcall TGereAleaPrixFrm::AffTendance(void)
{
	AleaPrixFrm->LabelModifie->Visible=false;
	AleaPrixFrm->Tendance=Tendance;
	AleaPrixFrm->Show();
	AleaPrixFrm->Produit(Nature);
}
//---------------------------------------------------------------------------
void __fastcall TGereAleaPrixFrm::BtBnCreerClick(TObject *Sender)
{
	bool rep;
	AnsiString titre,newNom;
	if(AleaXXFrm!=NULL && AleaXXFrm->Visible==true)AleaXXFrm->Close();
	//if(AleaXXFrm->Visible==true)AleaXXFrm->Close();

	if(TV->Selected==NULL) return;

	newNom="";
	if(Nature==NULL) return;//230206

	if(Nature[2]==TENDANCE)
	titre=L_NouvTend;//"  NouvelleTendance");
	else if(Nature[2]==SCENARIO)
	titre=L_NouvScen;//"  Nouveau Scenario");

	rep=ES->EntrerNom(titre,"",newNom);
	if(rep==false )return;
	VerifNomTendance(newNom,CREER);
}
//---------------------------------------------------------------------------
void __fastcall TGereAleaPrixFrm::BtCopierClick(TObject *Sender)
{
	bool rep;
	AnsiString newNom;

	newNom=Tendance->Nom;
	rep=ES->EntrerNom(L_NouvTendCop,"",newNom);
	//rep=ES->EntrerNom(L_NouvTendCop"Nouvelle Tendance copie de","",newNom);
	if(rep==false) return;

	rep=VerifNomTendance(newNom,COPIER);
}
//---------------------------------------------------------------------------
void __fastcall TGereAleaPrixFrm::BtsupprimerClick(TObject *Sender)
{
	int rep;
	if(Tendance==NULL )
	{
		MessageBox(Handle,L_Rien.c_str(),L_Pb.c_str(),
				//MessageBox(Handle,"Rien à supprimer","PROBLEME",
				MB_OK|MB_ICONEXCLAMATION);
		return;
	}

	if(Tendance->Supprimable==false)
	{
		MessageBox(Handle,L_Util.c_str(),T->L_Impo.c_str(),MB_OK|MB_ICONSTOP);
		//MessageBox(Handle,"est utilisé !","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		return;
	}

	rep=MessageBox(Handle,L_Sup.c_str(),
			//rep=MessageBox(Handle,"Vous voulez vraiment supprimer !",
			Tendance->Nom.c_str(),MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDYES)
	{
		//retirer du vecteur
		V_Tendance->sup(Tendance);
		Tendance=NULL;
		AleaPrixFrm->Close();
		ES->ecrireFichier();
		CreeTV();
		//Forme0Frm->CreeTVAleaPrix(TV); //reaffiche TV
	}

}
//modifier nom
//---------------------------------------------------------------------------
void __fastcall TGereAleaPrixFrm::BtModifierClick(TObject *Sender)
{
	bool rep;
	AnsiString newNom;
	if(Tendance==NULL)
	{
		MessageBox(Handle,L_PasSel.c_str(),T->L_Impo.c_str(),MB_OK|MB_ICONSTOP);
		//MessageBox(Handle,"Aucun elément n'est sélectionné","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		return;
	}

	newNom=Tendance->Nom;
	if(Nature[2]==TENDANCE)
	rep=ES->EntrerNom(L_ModifTend,"",newNom);
	//rep=ES->EntrerNom("Modification Nom Tendance","",newNom);
	if(Nature[2]==SCENARIO)
	rep=ES->EntrerNom(L_ModifScen,"",newNom);
	//rep=ES->EntrerNom("Modification Nom Scenario","",newNom);
	if (rep==true)
	{
		newNom=newNom.Trim();
		if(newNom==Tendance->Nom) return;
		VerifNomTendance(newNom,MODIFIER);
	}
}
//---------------------------------------------------------------------------
// verif nom tendance et l'insére dans TV
//---------------------------------------------------------------------------
bool __fastcall TGereAleaPrixFrm::VerifNomTendance(AnsiString newNom,int action)
{
	CL_Tendance *ancTend=NULL;

	// le nom existe
	newNom=newNom.Trim();
	if (newNom.IsEmpty()==true) {ShowMessage(L_PasNom.c_str());return false;}
	//if (newNom.IsEmpty()==true){ ShowMessage(" Pas de nom");return false; }

	// il n'y a pas d'atelier avec ce nom
	ancTend=V_Tendance->trouve(newNom);
	if(ancTend)
	{
		MessageBox(Handle,L_Existe.c_str(),T->L_Erreur.c_str(),
				MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	//MODIFIER on a seulement modifie le nom
	if(action==MODIFIER)
	{
		Tendance->Nom= newNom;
		CreeTV();
//        Forme0Frm->CreeTVAleaPrix(TV); //reaffiche TV
//    	return true;
	}
	//CREER
	else if(action==CREER)
	{
		Tendance=new CL_Tendance();
		Tendance->Nom=newNom;
		V_Tendance->ins(Tendance);
	}
	//COPIER
	else if(action==COPIER)
	{
		Tendance=new CL_Tendance(Tendance);
		Tendance->Nom=newNom;
		V_Tendance->ins(Tendance);
	}

	ES->ecrireFichier();
	CreeTV();
//    Forme0Frm->CreeTVAleaPrix(TV); //reaffiche TV

	AffTendance();

	return true;
}
//---------------------------------------------------------------------------
void __fastcall TGereAleaPrixFrm::CreeTV(void)
{
	Forme0Frm->CreeTVAleaPrix(TV); //reaffiche TV
}
//---------------------------------------------------------------------------
// pour chaque action modif creer copier
//  on a stocké
//donc fermer AleaPrix qui verifie
//---------------------------------------------------------------------------
void __fastcall TGereAleaPrixFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	if(AleaPrixFrm->Visible==true)
	AleaPrixFrm->Close();
}
//---------------------------------------------------------------------------
void TGereAleaPrixFrm::TexteChaine(void) {
	L_Prod = T->TrouveTexte("GereAleaPrixFrm", "L_Prod");
	L_PrixTendProd = T->TrouveTexte("GereAleaPrixFrm", "L_PrixTendProd");
	L_PrixScenProd = T->TrouveTexte("GereAleaPrixFrm", "L_PrixScenProd");
	L_Charge = T->TrouveTexte("GereAleaPrixFrm", "L_Charge");
	L_PrixTendCha = T->TrouveTexte("GereAleaPrixFrm", "L_PrixTendCha");
	L_PrixScenCha = T->TrouveTexte("GereAleaPrixFrm", "L_PrixScenCha");
	L_QuantTendProd = T->TrouveTexte("GereAleaPrixFrm", "L_QuantTendProd");
	L_QuantScenProd = T->TrouveTexte("GereAleaPrixFrm", "L_QuantScenProd");
	L_Exter = T->TrouveTexte("GereAleaPrixFrm", "L_Exter");
	L_QuantTendExt = T->TrouveTexte("GereAleaPrixFrm", "L_QuantTendExt");
	L_QuantScenExt = T->TrouveTexte("GereAleaPrixFrm", "L_QuantScenExt");

	L_NouvTend = T->TrouveTexte("GereAleaPrixFrm", "L_NouvTend");
	L_NouvScen = T->TrouveTexte("GereAleaPrixFrm", "L_NouvScen");
	L_NouvTendCop = T->TrouveTexte("GereAleaPrixFrm", "L_NouvTendCop");
	L_Rien = T->TrouveTexte("GereAleaPrixFrm", "L_Rien");
	L_Pb = T->TrouveTexte("GereAleaPrixFrm", "L_Pb");
	L_Util = T->TrouveTexte("GereAleaPrixFrm", "L_Util");
	L_Sup = T->TrouveTexte("GereAleaPrixFrm", "L_Sup");
	L_PasSel = T->TrouveTexte("GereAleaPrixFrm", "L_PasSel");
	L_ModifTend = T->TrouveTexte("GereAleaPrixFrm", "L_ModifTend");
	L_ModifScen = T->TrouveTexte("GereAleaPrixFrm", "L_ModifScen");
	L_PasNom = T->TrouveTexte("GereAleaPrixFrm", "L_PasNom");
	L_Existe = T->TrouveTexte("GereAleaPrixFrm", "L_Existe");
}
//--------------------------------------------
void TGereAleaPrixFrm::IniCaption(void) {
	GereAleaPrixFrm->Caption = LC_GereAleaPrixFrm;
	GBCategorie->Caption = T->LC_RGCat;
	BtCopier->Caption = T->LC_BtBnCopier;
	BtBnCreer->Caption = T->LC_BtBnCreer;
	BtBnFermer->Caption = T->LC_BtBnFermer;
	BtModifier->Caption = T->LC_BtModifier;
	LabelModifie->Caption = T->LC_LabelModifie_A;
	BtBnQuitter->Caption = T->LC_BtBnQuitter;
	GBReclasser->Caption = LC_GBReclasser;
	Btsupprimer->Caption = T->LC_BtBnSupBesTrav;
}
//--------------------------------------------
void TGereAleaPrixFrm::TexteCaption(void) {
	LC_GereAleaPrixFrm = T->TrouveCaption("GereAleaPrix", "LC_GereAleaPrixFrm");
	LC_RGCat = T->TrouveCaption("CL_Trad", "LC_RGCat");
	LC_BtBnCopier = T->TrouveCaption("CL_Trad", "LC_BtBnCopier");
	LC_BtBnCreer = T->TrouveCaption("CL_Trad", "LC_BtBnCreer");
	LC_BtBnFermer = T->TrouveCaption("CL_Trad", "LC_BtBnFermer");
	LC_BtModifier = T->TrouveCaption("CL_Trad", "LC_BtModifier");
	LC_LabelModifie_A = T->TrouveCaption("CL_Trad", "LC_LabelModifie_A");
	LC_BtBnQuitter = T->TrouveCaption("CL_Trad", "LC_BtBnQuitter");
	LC_GBReclasser = T->TrouveCaption("GereAleaPrix", "LC_GBReclasser");
	LC_BtBnSupBesTrav = T->TrouveCaption("CL_Trad", "LC_BtBnSupBesTrav");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TGereAleaPrixFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=1730;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

