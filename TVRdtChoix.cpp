//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "Main.h"

#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "Forme00.h"
#include "AleaRdt.h"
#include "TendanceEnum.h"

#include "GereAleaRdt.h"
#include "FichierLire.h"

#include "TVRdtChoix.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TVPrixChoix"
#pragma resource "*.dfm"
TTVRdtChoixFrm *TVRdtChoixFrm;
extern CL_ES *ES;

//---------------------------------------------------------------------------
__fastcall TTVRdtChoixFrm::TTVRdtChoixFrm(TComponent* Owner) :
		TTVPrixChoixFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTVRdtChoixFrm::TVDblClick(TObject *Sender)
{
	TTreeNode *elt;
	CL_Item *item;
	int c=LaGrille->Col;
	bool nouveau=false;
	bool rep;
	int nature;
	if(c!=2) return;

	elt=TV->Selected;
	if(elt==NULL) return;

	if(elt->Level==0) return;
	if(elt->Text=="[...]")
	{
//    	TVChoixFrm->Visible=false;
		TVRdtChoixFrm->Close();//Visible=false;
		switch(LaGrille->Tag)
		{
			case GTProd:
			case GSProd: MainForm->NouvelleDefinition(PRODUIT);return;
			case GTCharge :
			case GSCharge :MainForm->NouvelleDefinition(CHARGE);return;
			case GTExter:
			case GSExter :MainForm->NouvelleDefinition(EXTPOS);return;
		}
	}

	item=(CL_Item*)elt->Data;
	if(item==NULL) return;
	nature=GereAleaRdtFrm->Nature[1];

	V_Delta=AleaRdtFrm->Tendance->V_Delta;

	/*
	 switch ( GereAleaRdtFrm->Nature[2])
	 {
	 case TENDANCE:V_Delta=AleaRdtFrm->Tendance->V_Delta;break;
	 case SCENARIO:V_Delta=AleaRdtFrm->Scenario->V_Delta;break;
	 }
	 nature[0]=PRIX;nature[1]=PRODUIT;nature[2]=TENDANCE;nature[3]=0 branche NON déployée
	 QUANTITE       CHARGE            SCENARIO           1 branchz déployée
	 EXTER
	 */

	//trouver les ateliers ou cet item est produit ou utilisé
	rep=insereDelta(item,V_Culture,nature);if(rep==true)nouveau=true;
	rep=insereDelta(item,V_Animaux,nature);if(rep==true)nouveau=true;
	rep=insereDelta(item,V_Vivrier,nature);if(rep==true)nouveau=true;
	rep=insereDelta(item,V_Perenne,nature);if(rep==true)nouveau=true;

	if(nouveau==true)
	{
		classeDelta(nature);
		AleaRdtFrm->AppelerVersGrille();
	}
	else
	ShowMessage(" N'est pas produit ou utilisé  ou déjà défini");
}
//---------------------------------------------------------------------------
bool __fastcall TTVRdtChoixFrm::insereDelta(CL_Item *item,
		CL_Vecteur<CL_Atelier> *v_Atelier,int nature)
{
	int i,j;
	CL_Atelier *atelier;
	CL_Vecteur<CL_ItemParAtelier> *v_ItemParAtelier;
	CL_ItemParAtelier *itemParAtelier;
	CL_Delta *delta;
	bool nouveau=false;
	for(i=0;i<v_Atelier->Nbelt;i++)
	{
		atelier=v_Atelier->Vecteur[i];
		switch(nature)
		{
			case PRODUIT:v_ItemParAtelier=atelier->V_Produit;break;
			case CHARGE: v_ItemParAtelier=atelier->V_Charge;break;
			case EXTER: v_ItemParAtelier=atelier->V_Externalite;break;
			default:ShowMessage("Oubli TVRdtChoix");return false;
		}
		for(j=0;j<v_ItemParAtelier->Nbelt;j++)
		{
			itemParAtelier=v_ItemParAtelier->Vecteur[j];
			if(item==itemParAtelier->Item)
			{
				if(deltaExiste(atelier,item)!=NULL) continue;

				nouveau=true;
				delta=new CL_Delta();
				delta->Flag='N';
				delta->Item=item;
				delta->NoItem=item->No;
				delta->Atelier=atelier;
				delta->NoAtelier=atelier->No;
				if(v_Atelier==V_Culture)
				{
					delta->Rdt=trouveRdtCulture(itemParAtelier,atelier->NbPhase);
					delta->Nature=CULTURE;
				}
				else if(v_Atelier==V_Animaux)
				{
					delta->Rdt=trouveRdtCulture(itemParAtelier,atelier->NbPhase);
					delta->Nature=ANIMAUX;
				}
				else if(v_Atelier==V_Vivrier)
				{
					delta->Rdt=trouveRdtCulture(itemParAtelier,atelier->NbPhase);
					delta->Nature=VIVRIER;
				}
				else if(v_Atelier==V_Perenne)
				{
					delta->Rdt=trouveRdtPerenne(itemParAtelier,atelier->NbPhase);
					delta->Nature=PERENNE;
				}
				AleaRdtFrm->Tendance->V_Delta->ins(delta);
			}
		}
	}
	return nouveau;
}
//---------------------------------------------------------------------------
float TTVRdtChoixFrm::trouveRdtCulture(CL_ItemParAtelier *itemParAtelier,
		int nbPhase) {
	float rdt = 0;
	for (int i = 0; i < nbPhase; i++)
		rdt += itemParAtelier->QtePhase[i];
	return rdt;
}
//---------------------------------------------------------------------------
float TTVRdtChoixFrm::trouveRdtPerenne(CL_ItemParAtelier *itemParAtelier,
		int nbPhase) {
	float rdt = 0;
	for (int i = 0; i < nbPhase; i++) {
		if (itemParAtelier->QtePhase[i] > rdt)
			rdt = itemParAtelier->QtePhase[i];
	}
	return rdt;
}
//---------------------------------------------------------------------------
CL_Delta* __fastcall TTVRdtChoixFrm::deltaExiste(CL_Atelier *atelier,CL_Item *item)
{
	int i;
	CL_Delta *delta;
	for(i=0;i<V_Delta->Nbelt;i++)
	{
		delta=V_Delta->Vecteur[i];
		if(delta->Atelier==atelier && delta->Item==item) return delta;
	}
	return NULL;
}
//---------------------------------------------------------------------------
void __fastcall TTVRdtChoixFrm::classeDelta(int nature)
{
	int i;
	TList *listDelta;
	CL_Item *item;
	CL_Delta *delta;
	CL_Vecteur<CL_Item> *v_Item;

	listDelta=new TList;
	switch(nature)
	{
		case PRODUIT:v_Item=V_Produit;break;
		case CHARGE: v_Item=V_Charge;break;
		case EXTER: v_Item=V_Externalite;break;
		default:ShowMessage("Oubli TVRdtChoix");return;
	}

	for(i=0;i<v_Item->Nbelt;i++)
	{
		item=v_Item->Vecteur[i];
		classeDelta2(V_Culture,item,listDelta);
		classeDelta2(V_Animaux,item,listDelta);
		classeDelta2(V_Vivrier,item,listDelta);
		classeDelta2(V_Perenne,item,listDelta);
	}

	V_Delta->Nbelt=0;
	for(int i=0;i<listDelta->Count;i++)
	{
		delta=(CL_Delta*)listDelta->Items[i];
		V_Delta->insSans(delta);
	}
}
//---------------------------------------------------------------------------
void __fastcall TTVRdtChoixFrm::classeDelta2(CL_Vecteur<CL_Atelier> *v_Atelier,
		CL_Item *item,TList *listDelta)
{
	int j;
	CL_Atelier *atelier;
	CL_Delta *delta;
	for(j=0;j<v_Atelier->Nbelt;j++)
	{
		atelier=v_Atelier->Vecteur[j];
		delta=deltaExiste(atelier,item);
		if(delta)
		listDelta->Add(delta);
	}
}
/*
 delta=(CL_Delta*)LaGrille->Objects[0][r];

 if(delta==NULL)
 {
 delta=new CL_Delta;()
 delta->Flag='N';
 LaGrille->Objects[0][r]=(TObject*)delta;
 LaGrille->Cells[0][r]=r;
 }
 else
 {
 rep=MessageBox(Handle,"A Remplacer ?"," ATTENTION",MB_YESNO|MB_ICONEXCLAMATION);
 if(rep==ID_NO) return;
 }

 if(delta->Flag!='N')delta->Flag='M';

 delta->NoItem=item->No;
 delta->Item  =item;
 LaGrille->Cells[2][r]=item->Nom;
 LaGrille->Cells[3][r]=item->Categorie->Nom;
 LaGrille->Cells[4][r]=Forme00Frm->Aff(item->Prix,Digits);

 Forme00Frm->AjouterRow();


 LaGrille->Objects[0][r]=(TObject*)delta;
 LaGrille->Cells[0][r]=r;
 LaGrille->Cells[2][r]=item->Nom;
 LaGrille->Cells[3][r]=atelier->Nom;
 //rdt a trouver
 //LaGrille->Cells[4][r]=Forme00Frm->Aff(item->Prix,Digits);
 Forme00Frm->AjouterRow();
 r++;
 }
 */
//---------------------------------------------------------------------------
/*
 CL_Vecteur<CL_Atelier>      *V_Culture;
 CL_Vecteur<CL_Atelier>      *V_Animaux;
 CL_Vecteur<CL_Atelier>      *V_Vivrier;

 CL_Vecteur<CL_Espece>       *V_Espece;
 CL_Vecteur<CL_Atelier>      *V_Perenne;
 */

