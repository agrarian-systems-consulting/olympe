//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "LireFichier.h"
#include "SysUnite.h"
#include "Tva.h"
#include "EtatSortie.h"
#include "Categorie.h"
#include "AgriSaisie.h"

#include "Forme0.h"

#include "ReClasse.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TReClasseFrm *ReClasseFrm;
// Les extern
extern CL_ES *ES;
//---------------------------------------------------------------------------
__fastcall TReClasseFrm::TReClasseFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TReClasseFrm::FormActivate(TObject *Sender)
{
	LabelModifie->Visible=false;
	Fermer=false;
	switch(Nature)
	{
		case CATEGORIE: Forme0Frm->CreeLBCat (LB,VCat,false);break;
		case SYSUNITE: Forme0Frm->CreeLBUnite (LB,VSys,false);break;
		case TVA: Forme0Frm->CreeLBTva (LB,VTva,false);break;
		case ETATSORTIE: Forme0Frm->CreeLBElt (LB,VElt,false);break;
		case ITEM: Forme0Frm->CreeLBItem (LB,VItem,NoCat,false);break;
		case VALEUR: Forme0Frm->CreeLBValeur (LB,VValeur,false);break;
		case VERGER: Forme0Frm->CreeLBVerger (LB,VVerger,false);break;
		default:
		ShowMessage("Oubli dans ReClasse");Close();

	}
	ReClasser();
}
//---------------------------------------------------------------------------
void __fastcall TReClasseFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	int rep;
	if(LabelModifie->Visible==false) CanClose=true;
	else
	{
		rep=MessageBox(Handle,"Modifié\nVoulez vous conserver","MODIFICATION",
				MB_YESNOCANCEL|MB_ICONEXCLAMATION);
		if(rep==ID_YES)
		{
			Remplacer();
			CanClose=true;
		}
		else if(rep==ID_NO)
		{
			CanClose=true;
		}
		else
		CanClose=false;
	}
}
//---------------------------------------------------------------------------
//    Classement personnel 0   alphabétique  1
//---------------------------------------------------------------------------
void __fastcall TReClasseFrm::RGClick(TObject *Sender)
{
	ReClasser();
}
//---------------------------------------------------------------------------
void __fastcall TReClasseFrm::ReClasser(void)
{
	if(RG->ItemIndex==0) //tri alpha
	{
		BtBas->Enabled= false;
		BtHaut->Enabled=false;
		LB->Sorted= true;
		LabelModifie->Visible= true;
		Fermer=true;
		//ClasstAlpha();
	}
	else
	{
		BtBas->Enabled= true;
		BtHaut->Enabled=true;
		LB->Sorted= false;
	}
}
//---------------------------------------------------------------------------
//Classement personnel 0
//---------------------------------------------------------------------------
void __fastcall TReClasseFrm::LBClick(TObject *Sender)
{
	No=LB->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TReClasseFrm::BtHautClick(TObject *Sender)
{
	if(No==0) return;

	LabelModifie->Visible=true;
	LB->Items->Exchange(No,No-1);
	No--;
	LB->ItemIndex=No;
}
//---------------------------------------------------------------------------
void __fastcall TReClasseFrm::BtBasClick(TObject *Sender)
{
	if(No==LB->Items->Count-1)return;

	LabelModifie->Visible=true;
	LB->Items->Exchange(No,No+1);
	No++;
	LB->ItemIndex=No;
}
//---------------------------------------------------------------------------
// OK oui/non
//---------------------------------------------------------------------------
void __fastcall TReClasseFrm::BtOKClick(TObject *Sender)
{
	if( LabelModifie->Visible==true)
	{
		Remplacer();
		LabelModifie->Visible=false;
	}
	Fermer=true;
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TReClasseFrm::BtAnnuleClick(TObject *Sender)
{
	LabelModifie->Visible=false;
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TReClasseFrm::Remplacer(void)
{
	int i,n;
	CL_Item *item,*itemO;
	switch(Nature)
	{
		case CATEGORIE:
		for(n=0;n<VCat->Nbelt;n++)
		VCat->Vecteur[n]=(CL_Categorie*)LB->Items->Objects[n];
		break;
		case SYSUNITE:
		for(n=0;n<VSys->Nbelt;n++)
		VSys->Vecteur[n]=(CL_SystemeUnite*)LB->Items->Objects[n];
		SysUniteFrm->VersGrille(SysUniteFrm->Grille0);
		break;
		case TVA:
		for(n=0;n<VTva->Nbelt;n++)
		VTva->Vecteur[n]=(CL_Tva*)LB->Items->Objects[n];
		TvaFrm->VersGrille(TvaFrm->Grille0);
		break;
		case ETATSORTIE:
		for(n=0;n<VElt->Nbelt;n++)
		EtatSortieFrm->EtatSortie->V_Elt->Vecteur[n]=
		(CL_Elt*)LB->Items->Objects[n];
		EtatSortieFrm->VersGrille(EtatSortieFrm->Grille0);
		break;
		case ITEM:
		for(n=0,i=0;n<LB->Items->Count;n++)
		{
			item=(CL_Item*)LB->Items->Objects[n];
			for(;i<VItem->Nbelt;i++)
			{
				itemO=VItem->Vecteur[i];
				if(itemO->NoCategorie==NoCat)
				{
					VItem->Vecteur[i]=item;
					i++;
					break;
				}
			}
		}
		CategorieFrm->VersGrille(CategorieFrm->Grille0);
		break;
		// ce n'est qu pour culture    
		case VALEUR:
		for(n=0;n<VValeur->Nbelt;n++)
		AgriSaisieFrm->Agri->V_Culture->Vecteur[n]=
		(CL_Valeur*)LB->Items->Objects[n];
		AgriSaisieFrm->VersGrilleAssol(AgriSaisieFrm->Agri->V_Culture);
		break;
		case VERGER:
		for(n=0;n<VVerger->Nbelt;n++)
		AgriSaisieFrm->Agri->V_Verger->Vecteur[n]=
		(CL_Verger*)LB->Items->Objects[n];
		AgriSaisieFrm->VersGrilleVerger(AgriSaisieFrm->Agri->V_Verger);
		break;

		default:
		ShowMessage("Oubli dans ReClasse");Close();

	}
	ES->ecrireFichier();
}

