//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"

#include "AleaRdt.h"

#include "GereAleaRdt.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GereAleaPrix"
#pragma resource "*.dfm"

TGereAleaRdtFrm *GereAleaRdtFrm;
extern CL_ES *ES;

//---------------------------------------------------------------------------
__fastcall TGereAleaRdtFrm::TGereAleaRdtFrm(TComponent* Owner) :
		TGereAleaPrixFrm(Owner) {
}
//---------------------------------------------------------------------------

/*
 //---------------------------------------------------------------------------
 void __fastcall TGereAleaRdtFrm::FormActivate(TObject *Sender)
 {
 if(Origine==0)
 {
 Origine=1;
 LabelModifie->Visible=false;
 OrdreModif=false;
 No=0; //eviter reclassement si pas de sélection ???
 Tendance=NULL;
 BtCopier->Enabled=false;
 Btsupprimer->Enabled=false;
 BtBnCreer->Enabled=false;
 BtModifier->Enabled=false;

 }
 //
 //    CreeTVAleaRdt
 //    nature=new int[4];
 //    nature[0]=PRIX;nature[1]=PRODUIT;nature[2]=TENDANCE;nature[3]=0 branche NON déployée
 //              QUANTITE       CHARGE            SCENARIO           1 branchz déployée
 //                             EXTER
 //

 CreeTV();//Forme0Frm->CreeTVAleaRdt(TV);

 }
 */
//---------------------------------------------------------------------------
//void __fastcall TGereAleaRdtFrm::BtBnQuitterClick(TObject *Sender)
//---------------------------------------------------------------------------
void __fastcall TGereAleaRdtFrm::TVDblClick(TObject *Sender)
{
	TTreeNode *elt,*parent;
//	if(CEstBon()==false) return;
	if(AleaRdtFrm->Visible==true)AleaRdtFrm->BtBnStockerClick(this);
	AleaXXFrm=AleaRdtFrm;

	if(TV->Selected==NULL) return;

	elt=TV->Selected;
	if(elt->Level<2)
	{
		Nature=(int *)elt->Data;
		if(Nature==NULL) return; //
		if(Nature[3]==0)Nature[3]=1;
		else Nature[3]=0;
		memcpy(AleaRdtFrm->Nature,Nature,sizeof(int)*4);
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
	memcpy(AleaRdtFrm->Nature,Nature,sizeof(int)*4);
	//if(Nature[0]==QUANTITE) toujours vrai pour GereAleaRdt
	if(Nature[1]==PRODUIT)
	{
		AleaRdtFrm->TitreColonne2="PRODUIT";
		if(Nature[2]==TENDANCE)
		{
			V_Tendance=V_TendQProd;
			AleaRdtFrm->Caption="QUANTITE: TENDANCE: Produit";
		}
		else if(Nature[2]==SCENARIO)
		{
			V_Tendance=V_ScenQProd;
			AleaRdtFrm->Caption="QUANTITE: SCENARIO: Produit";
		}
		else
		ShowMessage("Problème dans GereAleaRdt");
	}
	else if(Nature[1]==CHARGE)
	{
		AleaRdtFrm->TitreColonne2="CHARGE";
		if(Nature[2]==TENDANCE)
		{
			V_Tendance=V_TendQCharge;
			AleaRdtFrm->Caption="QUANTITE: TENDANCE: Charge";
		}
		else if(Nature[2]==SCENARIO)
		{
			V_Tendance=V_ScenQCharge;
			AleaRdtFrm->Caption="QUANTITE: SCENARIO: Charge";
		}
		else
		ShowMessage("Problème dans GereAleaRdt");
	}
	else if(Nature[1]==EXTER)
	{
		AleaRdtFrm->TitreColonne2="EXTERNALITE";
		if(Nature[2]==TENDANCE)
		{
			V_Tendance=V_TendQExt;
			AleaRdtFrm->Caption="QUANTITE: TENDANCE: Externalité";
		}
		else if(Nature[2]==SCENARIO)
		{
			V_Tendance=V_ScenQExt;
			AleaRdtFrm->Caption="QUANTITE: SCENARIO: Externalité";
		}
		else
		ShowMessage("Problème dans GereAleaRdt");
	}
	else
	ShowMessage("Problème dans GereAleaRdt");

	/*
	 CreeTVAleaRdt
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
void __fastcall TGereAleaRdtFrm::AffTendance(void)
{
	AleaRdtFrm->LabelModifie->Visible=false;
	AleaRdtFrm->Tendance=Tendance;
	AleaRdtFrm->Show();
	AleaRdtFrm->Produit(Nature);
}
//---------------------------------------------------------------------------/*

//---------------------------------------------------------------------------
void __fastcall TGereAleaRdtFrm::BtBnCreerClick(TObject *Sender)
{
	bool rep;
	AnsiString titre,newNom;

	if(AleaXXFrm->Visible==true)AleaXXFrm->Close();

	if(TV->Selected==NULL) return;

	newNom="";
	if(Nature[2]==TENDANCE)
	titre=AnsiString("  NouvelleTendance");
	else if(Nature[2]==SCENARIO)
	titre=AnsiString("  Nouveau Scenario");

	rep=ES->EntrerNom(titre,"",newNom);
	if(rep==false )return;
	VerifNomTendance(newNom,CREER);
}

//---------------------------------------------------------------------------/*

//---------------------------------------------------------------------------
void __fastcall TGereAleaRdtFrm::BtCopierClick(TObject *Sender)
{
	bool rep;
	AnsiString newNom;

	newNom=Tendance->Nom;
	rep=ES->EntrerNom("Nouvelle Tendance copie de","",newNom);
	if(rep==false) return;

	rep=VerifNomTendance(newNom,COPIER);

}

//---------------------------------------------------------------------------/*

//---------------------------------------------------------------------------
void __fastcall TGereAleaRdtFrm::BtsupprimerClick(TObject *Sender)
{
	int rep;
	if(Tendance==NULL )
	{
		MessageBox(Handle,"Rien à supprimer","PROBLEME",
				MB_OK|MB_ICONEXCLAMATION);
		return;
	}

	if(Tendance->Supprimable==false)
	{
		MessageBox(Handle,"est utilisé !","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		return;
	}

	rep=MessageBox(Handle,"Vous voulez vraiment supprimer !",
			Tendance->Nom.c_str(),MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDYES)
	{
		//retirer du vecteur
		V_Tendance->sup(Tendance);
		Tendance=NULL;
		AleaRdtFrm->Close();

		ES->ecrireFichier();
		CreeTV();//Forme0Frm->CreeTVAleaPrix(TV); //reaffiche TV
	}
}

//---------------------------------------------------------------------------/*
//---------------------------------------------------------------------------
void __fastcall TGereAleaRdtFrm::BtModifierClick(TObject *Sender)
{
	bool rep;
	AnsiString newNom;
	if(Tendance==NULL)
	{
		MessageBox(Handle,"Aucun élément n'est sélectionné","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		return;
	}

	newNom=Tendance->Nom;
	if(Nature[2]==TENDANCE)
	rep=ES->EntrerNom("Modification Nom Tendance","",newNom);
	if(Nature[2]==SCENARIO)
	rep=ES->EntrerNom("Modification Nom Scenario","",newNom);
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
//bool __fastcall TGereAleaPrixFrm::VerifNomTendance(AnsiString newNom,int action)

//---------------------------------------------------------------------------
void __fastcall TGereAleaRdtFrm::CreeTV(void)
{
	Forme0Frm->CreeTVAleaRdt(TV); //reaffiche TV
}

//---------------------------------------------------------------------------
void __fastcall TGereAleaRdtFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	if(AleaRdtFrm->Visible==true)
	AleaRdtFrm->Close();
	/*
	 if(AleaRdtFrm->CEstBon()==false)
	 {
	 CanClose=false;
	 return;
	 }
	 AleaRdtFrm->Close();
	 */
}

