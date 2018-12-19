//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Forme0.h"
#include "TendanceEnum.h"
#include "Tendance.h"

#include "GereAlea.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGereAleaFrm *GereAleaFrm;
//---------------------------------------------------------------------------
__fastcall TGereAleaFrm::TGereAleaFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TGereAleaFrm::FormActivate(TObject *Sender)
{
	if(Origine==0)
	{
		Origine=1;
		LabelModifie->Visible=false;
		TendanceFrm->LabelModifie->Visible=false;
		OrdreModif=false;
		No=0; //eviter reclassement si pas de sélection ???
		TendanceFrm->Tendance=NULL;
		ReCreeTV=true;
	}
	if(ReCreeTV==false) return; //ini dans Tendance/Produit si nouvelle tendance

	Forme0Frm->CreeTVAleaPrix(TV);
	ReCreeTV=false;
}
//---------------------------------------------------------------------------
void __fastcall TGereAleaFrm::BtBnQuitterClick(TObject *Sender)
{
	int rep;
	rep=MessageBox(Handle,"Vous voulez vraiment quitter","QUITTER",
			MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDYES) Application->Terminate();
	else return;

}
//---------------------------------------------------------------------------
void __fastcall TGereAleaFrm::TVDblClick(TObject *Sender)
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
		TendanceFrm->AFaire=CREER;
	}
	else
	{
		tendance=(CL_Tendance*)elt->Data;
		TendanceFrm->AFaire=0; //0 CREER COPIER
	}
	TendanceFrm->Tendance=tendance;
	TendanceFrm->Show();
	TendanceFrm->Produit(Nature);

}
//---------------------------------------------------------------------------
void __fastcall TGereAleaFrm::BtBnCreerClick(TObject *Sender)
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
	TendanceFrm->AFaire=CREER;
	TendanceFrm->Tendance=tendance;
	TendanceFrm->Show();
	TendanceFrm->Produit(Nature);
}
//---------------------------------------------------------------------------
void __fastcall TGereAleaFrm::BtCopierClick(TObject *Sender)
{
	CL_Tendance *tendance= NULL;
	bool rep;
	AnsiString titre;
	if(TendanceFrm->CEstBon()==false) return;

	tendance=TendanceFrm->Tendance;

	if(tendance==NULL )
	{
		MessageBox(Handle,"Rien à copier","PROBLEME",
				MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	TendanceFrm->AFaire=COPIER;
	TendanceFrm->Tendance=new CL_Tendance(tendance);
	TendanceFrm->Produit(Nature);
}
//---------------------------------------------------------------------------
void __fastcall TGereAleaFrm::BtsupprimerClick(TObject *Sender)
{
	int rep;
	bool supprimable;
	CL_Tendance *tendance =NULL;

	tendance=TendanceFrm->Tendance;
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
	TendanceFrm->SupTendance();
	Forme0Frm->CreeTVAleaPrix(TV); //???
}
//modifier nom
//---------------------------------------------------------------------------
void __fastcall TGereAleaFrm::BtModifierClick(TObject *Sender)
{
	CL_Tendance *tendance =NULL;
	bool rep;
	CL_Tendance *ancTend;
	AnsiString asCaption,nom;

	tendance=TendanceFrm->Tendance;
	if(tendance==NULL )return;

	nom=tendance->Nom;
	asCaption="Nouveau Nom";
	while(1)
	{
		rep=ES->EntrerNom(asCaption, "Donner son Nom", nom);
		if ( rep==true)
		{
			if(nom.Length()==0) continue;
			ancTend=TendanceFrm->V_Tendance->trouve(nom);
			if(ancTend)
			{
				MessageBox(Handle," Nom déjà donné","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
				continue;
			}
			TendanceFrm->Tendance->Nom=nom;
			TendanceFrm->EdNom->Text=nom;
			Forme0Frm->CreeTVAleaPrix(TV); //???
			return;
		}
		else
		return;
	}
//    Forme0Frm->CreeTVAleaPrix(TV);  //???

}
//---------------------------------------------------------------------------
void __fastcall TGereAleaFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	if(TendanceFrm->CEstBon()==false)
	{
		CanClose=false;
		return;
	}
	return;
}
//---------------------------------------------------------------------------

