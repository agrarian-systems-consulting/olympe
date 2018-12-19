//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "OlympeDec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"

#include "FenRepart.h"
#include "FenRepartDef.h"
#include "TresoProduits.h"
#include "Treso.h"
#include "TresoRepart.h"

#include "TVChoixRepart.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTVChoixRepartFrm *TVChoixRepartFrm;
extern CL_ES *ES;

//---------------------------------------------------------------------------
__fastcall TTVChoixRepartFrm::TTVChoixRepartFrm(TComponent* Owner)

:
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixRepartFrm::TVDblClick(TObject *Sender)
{
	TresoRepartFrm->LabelModifie->Visible=true;
	if(AFaire==AnsiString("Definir"))
	Definir();
	else if(AFaire==AnsiString("Copier"))
	Copier();
	else if(AFaire==AnsiString("Choisir"))
	Choisir();
	else
	{
		ShowMessage("oubli dans TTVChoixRepartFrm::TVDblClick");
		return;
	}
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixRepartFrm::Definir(void)
{
	TTreeNode *elt,*pere;

	elt=TV->Selected;
	if(elt==NULL) return;

	if(elt->Level==0 && elt->Text=="[...]")
	{
		NouvelleCat();
		return;
	}

	if(elt->Level==0) return;
	//Categorie est connu cf  TVExpanded
	pere=TrouverPere(TV,elt);
	Categorie=(CL_Categorie*)pere->Data;//211105
	FenRepartDefFrm->Categorie=Categorie;

	if( elt->Text=="[...]")
	{
		FenRepartDefFrm->Repart0=NULL;
	}
	else
	{
		FenRepartDefFrm->Repart0=(CL_Repart*)elt->Data;
		FenRepartDefFrm->Categorie=FenRepartDefFrm->Repart0->Categorie;
	}
	FenRepartDefFrm->Show();
	FenRepartDefFrm->Affiche();
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixRepartFrm::Copier(void)
{
	float totalPcent;
	TTreeNode *elt;
	CL_Repart *repart;
	elt=TV->Selected;
	if(elt==NULL) return;
	if(elt->Level==0) return;
	//Categorie est connu cf  TVExpanded

	if( elt->Text=="[...]")return;

	repart=(CL_Repart*)elt->Data;
	repart->GrilleEcrire(FenRepartDefFrm->LaGrille,0);
	totalPcent=repart->Total();
	FenRepartDefFrm->EdTotPcent->Text=FloatToStrF((double)totalPcent,ffNumber,7,0);
	FenRepartDefFrm->LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------
void __fastcall TTVChoixRepartFrm::Choisir(void)
{
	TTreeNode *elt;

	elt=TV->Selected;
	if(elt==NULL) return;
	if( elt->Text=="[...]")
	{
		FenRepartFrm->Visible=false;
		FenRepartDefFrm->Repart0=NULL;
		FenRepartDefFrm->Show();
		FenRepartDefFrm->Affiche();
		return;
	}
	if(elt->Text=="Standard") return; //200810

	FenRepartFrm->Repart=(CL_Repart*)elt->Data;
	TresoFrm->IlYaModif=true;
	FenRepartFrm->Show();
	FenRepartFrm->Affiche();
}
// pour faire connaitre la catégorie si nouvelle répartition dans FenRepart
//---------------------------------------------------------------------------
void __fastcall TTVChoixRepartFrm::TVExpanded(TObject *Sender,
		TTreeNode *Node)
{
	Categorie=(CL_Categorie*)Node->Data;
	FenRepartDefFrm->Categorie=Categorie;
}
//---------------------------------------------------------------------------
TTreeNode* TTVChoixRepartFrm::TrouverPere(TTreeView *tv, TTreeNode *tn0) {
	int n;
	TTreeNode *tn, *pere;
	for (n = 0; n < tv->Items->Count; n++) {
		tn = tv->Items->Item[n];
		if (tn->Level == tn0->Level - 1)
			pere = tn;
		if (tn == tn0)
			return pere;
	}
	return NULL;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTVChoixRepartFrm::NouvelleCat(void)
{
	bool rep;
	AnsiString newCat;
	CL_Categorie *cat;
	newCat="";
	rep=ES->EntrerNom("Nouvelle Catégorie","",newCat);
	if(rep==true)
	{
		newCat=newCat.Trim();
		if(newCat.IsEmpty()==true) return;

		cat=new CL_Categorie(newCat,0);
		V_CatRepart->ins(cat);
		Forme0Frm->CreeTVRepart(TVChoixRepartFrm->TV);
//        BtOKClick(this);
	}
}

