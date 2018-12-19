//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Rendement.h"

#include "GereRendement.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GereAlea"
#pragma resource "*.dfm"
TGereRendementFrm *GereRendementFrm;
//---------------------------------------------------------------------------
__fastcall TGereRendementFrm::TGereRendementFrm(TComponent* Owner) :
		TGereAleaFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TGereRendementFrm::FormActivate(TObject *Sender)
{
	if(Origine==0)
	{
		Origine=1;
		LabelModifie->Visible=false;
		RendementFrm->LabelModifie->Visible=false;
		OrdreModif=false;
		No=0; //eviter reclassement si pas de sélection ???
		RendementFrm->Tendance=NULL;
		ReCreeTV=true;
	}
	if(ReCreeTV==false) return; //ini dans Tendance/Produit si nouvelle tendance

	Forme0Frm->CreeTVAleaQuantite(TV);
	ReCreeTV=false;
}
//---------------------------------------------------------------------------
void __fastcall TGereRendementFrm::BtBnQuitterClick(TObject *Sender)
{
	int rep;
	rep=MessageBox(Handle,"Vous voulez vraiment quitter","QUITTER",
			MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDYES) Application->Terminate();
	else return;

}
//---------------------------------------------------------------------------
void __fastcall TGereRendementFrm::TVDblClick(TObject *Sender)
{
	TTreeNode *elt,*parent;
	CL_Tendance *tendance;
//	if(CEstBon()==false) return;

	if(TV->Selected==NULL) return;

	elt=TV->Selected;
	if(elt->Level<2)
	{
		Nature=(int *)elt->Data;
		if(Nature[3]==0)Nature[3]=1;
		else Nature[3]=0;
		return;
	}
	elt=TV->Selected;
	parent=elt->Parent;
	Nature=(int *)parent->Data;
	Nature[3]=1;
	/*
	 informé dans Forme0/CreeTVAleaPrix
	 nature=new int[3];
	 nature[0]=PRIX;nature[1]=PRODUIT;nature[2]=TENDANCE;

	 */
	if(elt->Text=="[...]")
	{
		tendance=new CL_Tendance;
		RendementFrm->AFaire=CREER;
	}
	else
	{
		tendance=(CL_Tendance*)elt->Data;
		TendanceFrm->AFaire=0; //0 CREER COPIER
	}
	RendementFrm->Tendance=tendance;
	RendementFrm->Show();
	RendementFrm->Produit(Nature);
}
//---------------------------------------------------------------------------
void __fastcall TGereRendementFrm::BtBnCreerClick(TObject *Sender)
{
	TTreeNode *elt,*parent;
	CL_Tendance *tendance;
//	if(CEstBon()==false) return;

	if(TV->Selected==NULL) return;

	elt=TV->Selected;
	switch(elt->Level)
	{
		case 1:
		elt=TV->Selected;
		Nature=(int *)elt->Data;
		break;
		case 2:
		elt=TV->Selected;
		parent=elt->Parent;
		Nature=(int *)parent->Data;
		break;
		default: return;
	}
	/*
	 informé dans Forme0/CreeTVAleaPrix
	 nature=new int[3];
	 nature[0]=PRIX;nature[1]=PRODUIT;nature[2]=TENDANCE;

	 */
	tendance=new CL_Tendance;
	RendementFrm->AFaire=CREER;
	RendementFrm->Tendance=tendance;
	RendementFrm->Show();
	RendementFrm->Produit(Nature);
}
//---------------------------------------------------------------------------
void __fastcall TGereRendementFrm::BtCopierClick(TObject *Sender)
{
	CL_Tendance *tendance= NULL;
	bool rep;
	AnsiString titre;
	if(RendementFrm->CEstBon()==false) return;

	tendance=RendementFrm->Tendance;

	if(tendance==NULL )
	{
		MessageBox(Handle,"Rien à copier","PROBLEME",
				MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	RendementFrm->AFaire=COPIER;
	RendementFrm->Tendance=new CL_Tendance(tendance);
	RendementFrm->Produit(Nature);
}
//---------------------------------------------------------------------------
void __fastcall TGereRendementFrm::BtsupprimerClick(TObject *Sender)
{
	int rep;
	bool supprimable;
	CL_Tendance *tendance =NULL;

	tendance=RendementFrm->Tendance;
	if(tendance==NULL )
	{
		MessageBox(Handle,"Rien à supprimer","PROBLEME",
				MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	supprimable=tendance->Supprimable;

	if(supprimable==false)
	{
		MessageBox(Handle,"est utilisé !","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		return;
	}
	RendementFrm->SupTendance();
	Forme0Frm->CreeTVAleaQuantite(TV); //???
}
//modifier nom
//---------------------------------------------------------------------------
void __fastcall TGereRendementFrm::BtModifierClick(TObject *Sender)
{
	CL_Tendance *tendance =NULL;
	bool rep;
	CL_Tendance *ancTend;
	AnsiString asCaption,nom;

	tendance=RendementFrm->Tendance;
	if(tendance==NULL )return;

	nom=tendance->Nom;
	asCaption="Nouveau Nom";
	while(1)
	{
		rep=ES->EntrerNom(asCaption, "Donner son Nom", nom);
		if ( rep==true)
		{
			if(nom.Length()==0) continue;
			ancTend=RendementFrm->V_Tendance->trouve(nom);
			if(ancTend)
			{
				MessageBox(Handle," Nom déjà donné","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
				continue;
			}
			RendementFrm->Tendance->Nom=nom;
			RendementFrm->EdNom->Text=nom;
			Forme0Frm->CreeTVAleaQuantite(TV); //???
			return;
		}
		else
		return;
	}

}
//---------------------------------------------------------------------------
void __fastcall TGereRendementFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	if(RendementFrm->CEstBon()==false)
	{
		CanClose=false;
		return;
	}
	RendementFrm->Close();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

