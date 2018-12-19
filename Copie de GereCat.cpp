//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "Forme0.h"
#include "Brouillon.h"
#include "Tableur.h"
#include "ChoixCritere.h"

#include "Main.h"
#include "Categorie.h"
#include "GereAtelier.h"
#include "GereCat.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGereCatFrm *GereCatFrm;
extern CL_ES *ES;
//---------------------------------------------------------------------------
__fastcall TGereCatFrm::TGereCatFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::FormActivate(TObject *Sender)
{
//    FermerLesFenetres();  trouver solution
	if( GereAtelierFrm->Visible==true) GereAtelierFrm->Close();
//    if( GereCatFrm->Visible==true)             GereCatFrm->Close();

	Personnaliser();
	LB->Visible= true;
	if(Origine==0)
	{
		PClasst->Visible=false;
		LabelModifie->Visible=false;
		CategorieFrm->LabelModifie->Visible=false;
		CategorieFrm->Categorie=NULL;
		OrdreModif=false;
		Forme0Frm->CreeLBCat(LB,V_Categorie);
		No=0; //eviter reclassement si pas de sélection
	}
}
//---------------------------------------------------------------------------
//choix de la categorie
void __fastcall TGereCatFrm::LBClick(TObject *Sender)
{
//AnsiString nom;
	int n;
	n=LB->ItemIndex;
	No=n;// pour Reclasser
	//verif et stockage que si définitions d'élements de la catégorie
	if(CEstBon()==false) return;
	if(PClasst->Visible==true) return;
	if(LB->Items->Strings[n]=="[...]")
	Nouveau();
	else
	Existant();
}
//---------------------------------------------------------------------------
// on connait la categorie choisie dans LBClick
// trier dans V_Item les item qui appartiennent à cette catégorie
void __fastcall TGereCatFrm::Existant(void)
{
	int n=LB->ItemIndex;

	CategorieFrm->Categorie=(CL_Categorie*)LB->Items->Objects[n];
	CategorieFrm->Categorie->Flag=EXISTE;
	CategorieFrm->LabelModifie->Visible=false;
	CategorieFrm->Origine=0;
	CategorieFrm->AffItem();
	CategorieFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::Nouveau(void)
{
	bool rep;
	NewNom="";
	rep=ES->EntrerNom("Nouvelle Catégorie","",NewNom);
	if(rep==true)
	{
		NewNom=NewNom.Trim();
		if(NewNom.IsEmpty()==true) return;

		NouvCat=new CL_Categorie;
		NouvCat->Flag=NOUVEAU;
		BtOKClick(this);
	}
}
//----------------------------------------------------------------------------
void __fastcall TGereCatFrm::BtBnCreerClick(TObject *Sender)
{
	No=LB->Items->Count;
	Nouveau();
}
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::BtModifierClick(TObject *Sender)
{
	bool rep;
	if(CEstBon()==false) return;

	NouvCat=NULL;
	if(CategorieFrm->Categorie==NULL)
	{
		MessageBox(Handle,"Aucune elément n'est sélectionné","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		return;
	}
	NewNom=CategorieFrm->Categorie->Nom;
	rep=ES->EntrerNom("Modification du Nom",NewNom,NewNom);
	if(rep==true)
	{
		if(NewNom==CategorieFrm->Categorie->Nom) return;
		BtOKClick(this);
	}
}
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::BtSupprimerClick(TObject *Sender)
{
	int rep;
	bool supprimable;
	CL_Categorie *cat=NULL;
	char buf[100];
	cat=CategorieFrm->Categorie;
	if(cat==NULL)return;
	supprimable=cat->Supprimable;

	if(supprimable==false)
	{
		if(V_Categorie==V_CatBestiaux)
		MessageBox(Handle,"Ce troupeau est utilisé!","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		else
		MessageBox(Handle,"Cette catégorie a des éléments!","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		return;
	}

	sprintf(buf," Je supprime %s \n Vous êtes sur ?",cat->Nom.c_str() );
	rep=MessageBox(Handle,buf,"SUPPRESSION",MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDNO) return;

	if(rep==IDYES)
	{
		//retirer du vecteur
		V_Categorie->sup(cat);
		if(V_Categorie==V_CatTypeZone)
		majLBCatCritere();
		else if(V_Categorie==V_CatBestiaux)
		MajV_Bestiaux(cat);
		cat=NULL;
		ES->ecrireFichier();
		GereCatFrm->LabelModifie->Visible=false;
		///actualiser LB TV
		Forme0Frm->CreeLBCat(LB,V_Categorie);
		CategorieFrm->LabCatVar->Caption="";
		LB->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::majLBCatCritere(void)
{
	int n;
	TListBox *lB;
	CL_Categorie *categorie;

//    V_CatTypeZone->FlagMisA(false);

	lB=ChoixCritereFrm->LBCritere;
	lB->Clear();//141101

	//criteres Retenus
	for(n=0;n<V_CatTypeZone->Nbelt;n++)
	{
		categorie=V_CatTypeZone->Vecteur[n];
		if(categorie->Flag==true)
		lB->Items->AddObject(categorie->Nom,(TObject*)categorie);
	}
	//criteres Non Retenus
	lB=ChoixCritereFrm->LBCritereNR;
	lB->Clear();//141101
	for(n=0;n<V_CatTypeZone->Nbelt;n++)
	{
		categorie=V_CatTypeZone->Vecteur[n];
		if(categorie->Flag==false)
		lB->Items->AddObject(categorie->Nom,(TObject*)categorie);
	}
	ChoixCritereFrm->LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::MajV_Bestiaux(CL_Categorie *cat)
{
	int i;
	CL_Item *animal;
	for(i=0;i<V_Bestiaux->Nbelt;i++)
	{
		animal=V_Bestiaux->Vecteur[i];
		if(animal->Categorie==cat)
		V_Bestiaux->sup(animal);
	}

}
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::StockerOrdre(CL_Vecteur<CL_Categorie> *vecteur)
{
	int i;
	for(i=0;i<LB->Items->Count;i++)
	vecteur->Vecteur[i]=(CL_Categorie*)LB->Items->Objects[i];
	OrdreModif=false;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::BtOKClick(TObject *Sender)
{
	CL_Categorie *ancCat=NULL;
	TListBox *lB;
	NewNom=NewNom.Trim();
	if (NewNom.IsEmpty()==true) {ShowMessage(" Pas de nom");return;}

	ancCat=V_Categorie->trouve(NewNom);
	if(ancCat)
	{
		MessageBox(Handle,"Il existe déjà",
				"ERREUR",MB_OK|MB_ICONEXCLAMATION);
		return;
	}

	if(NouvCat==NULL) //on modifie le nom
	{
		CategorieFrm->Categorie->Nom= NewNom;
		CategorieFrm->LabCatVar->Caption= CategorieFrm->Categorie->Nom;
		GereCatFrm->LabelModifie->Visible=true;
		Forme0Frm->CreeLBCat(LB,V_Categorie); ///????
		return;
	}
	///NouvCat a été créé dans Nouveau
	NouvCat->Nom=NewNom;
	NouvCat->Flag=NOUVEAU;
	V_Categorie->ins(NouvCat);

	if(V_Categorie==V_CatTypeZone)
	{
		NouvCat->Flag=false;
		lB=ChoixCritereFrm->LBCritereNR; //critere Non Retenu
		lB->Items->AddObject(NouvCat->Nom,(TObject*)NouvCat);
		NouvCat->Flag=NOUVEAU;
	}
	CategorieFrm->Categorie=NouvCat;
	GereCatFrm->LabelModifie->Visible=true;

	Forme0Frm->CreeLBCat(LB,V_Categorie);
}

//reclasse ListBox
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::BtHautClick(TObject *Sender)
{
	if(No==0) return;
	if(No==LB->Items->Count-1)return; //derniere ligne= [...]

	LabelModifie->Visible=true;
	LB->Items->Exchange(No,No-1);
	No--;
	LB->ItemIndex=No;
	OrdreModif=true;
}
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::BtBasClick(TObject *Sender)
{
	if(No<0) return;
	if(No==LB->Items->Count-1)return; //derniere ligne= [...]
	if(No==LB->Items->Count-2)return;//derniere ligne= [...]

	LabelModifie->Visible=true;
	LB->Items->Exchange(No,No+1);
	No++;
	LB->ItemIndex=No;
	OrdreModif=true;
}
//---------------------------------------------------------------------------
// Verif Close
//---------------------------------------------------------------------------
bool __fastcall TGereCatFrm::CEstBon(void)
{
	int rep;

	if( GereCatFrm->LabelModifie->Visible==false
			&& CategorieFrm->LabelModifie->Visible==false)
	return true;

	else if( GereCatFrm->LabelModifie->Visible==true
			&& CategorieFrm->LabelModifie->Visible==false)
	{
		if(OrdreModif==true)StockerOrdre(V_Categorie);
		ES->ecrireFichier();
		GereCatFrm->LabelModifie->Visible==false;
		return true;
	}

	else
	{
		rep=MessageBox(Handle,"Modifié\nVoulez vous conserver","MODIFICATION",
				MB_YESNOCANCEL|MB_ICONEXCLAMATION);
		if(rep==ID_YES)
		{
			CategorieFrm->Stocker();
			GereCatFrm->LabelModifie->Visible= false;
			CategorieFrm->LabelModifie->Visible==false;
			return true;
		}
		else if(rep==ID_NO)
		{
			CategorieFrm->AffItem();
			return true;
		}
		else
		return false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::BtBnQuitterClick(TObject *Sender)
{
	int rep;
	rep=MessageBox(Handle,"Vous voulez vraiment quitter","QUITTER",
			MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDYES) Application->Terminate();
	else return;
}
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::BtBnFermerClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	if(CEstBon()==false)
	{
		CanClose=false;
		return;
	}
	CategorieFrm->Close();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::Personnaliser(void)
{

	switch(Forme0Frm->Nature)
	{
		case PRODUIT:
		GereCatFrm->Caption="Produits";
		V_Item= V_Produit;
		V_Categorie= V_CatProduit;
		GereCatFrm->Panel1->Visible= true;
		EcranProduit();
		break;
		case CHARGE:
		GereCatFrm->Caption="Charges Opérationnelles";
		V_Item= V_Charge;
		V_Categorie= V_CatCharge;
		GereCatFrm->Panel1->Visible= true;
		EcranProduit();
		break;
		case EXTPOS:
		GereCatFrm->Caption="Externalités";
		V_Item= V_Externalite;
		V_Categorie=V_CatExternalite;
		GereCatFrm->Panel1->Visible=false;
		EcranExternalite();
		break;
		case NOMANIMAUX:
		GereCatFrm->Caption=" Nom des Animaux";
		V_Item= V_Bestiaux;
		V_Categorie= V_CatBestiaux;
		GereCatFrm->Panel1->Visible= true;
		EcranNomAnimaux();
		break;
		case CHSTRUCT:
		GereCatFrm->Caption="Charges de structure";
		V_Item= V_ChStruct;
		V_Categorie=V_CatChStruct;
		GereCatFrm->Panel1->Visible=true;
		EcranRecDiv();
		break;
		case DEPDIV:
		GereCatFrm->Caption="Dépenses Diverses";
		V_Item= V_DepDiv;
		V_Categorie=V_CatDepDiv;
		GereCatFrm->Panel1->Visible=true;
		EcranRecDiv();
		break;
		case RECDIV:
		GereCatFrm->Caption="Recettes Diverses";
		V_Item= V_RecDiv;
		V_Categorie=V_CatRecDiv;
		GereCatFrm->Panel1->Visible=true;
		EcranRecDiv();
		break;
		case RECFAM:
		GereCatFrm->Caption="Recettes Familiales";
		V_Item= V_RecFam;
		V_Categorie=V_CatRecFam;
		GereCatFrm->Panel1->Visible=true;
		EcranRecDiv();
		break;
		case DEPFAM:
		GereCatFrm->Caption="Dépenses Familiales";
		V_Item= V_DepFam;
		V_Categorie=V_CatDepFam;
		GereCatFrm->Panel1->Visible=true;
		EcranRecDiv();
		break;
		case VARIABLE:
		GereCatFrm->Caption="Variables";
		V_Item= V_Variable;
		V_Categorie=V_CatVar;
		GereCatFrm->Panel1->Visible=true;
		EcranVariable();
		break;
		case ZONE:
		GereCatFrm->Caption="Zones et Types";
		V_Item= V_TypeZone;
		V_Categorie=V_CatTypeZone;
		GereCatFrm->Panel1->Visible=true;
		EcranZone();
		break;
		case DICO:
		GereCatFrm->Caption="Dictionnaire";
		V_Item= V_Dico;
		V_Categorie=V_CatDico;
		GereCatFrm->Panel1->Visible=true;
		EcranZone();
		break;
		default:
		ShowMessage("Oubli dans GereCat");
	}
	CategorieFrm->Caption= GereCatFrm->Caption;
}
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::EcranProduit(void)
{
//    CategorieFrm->BtNom->Visible=     false;
	CategorieFrm->BtTva->Visible= true;
	CategorieFrm->BtBnUnite->Visible= true;
//    CategorieFrm->TV->Visible=        false;
//    CategorieFrm->LBTva->Visible=     false;
//    CategorieFrm->LBUnite->Visible=   false;
}
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::EcranExternalite(void)
{
	CategorieFrm->BtTva->Visible= false;
	CategorieFrm->BtBnUnite->Visible= true;
}
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::EcranNomAnimaux(void)
{
	CategorieFrm->BtTva->Visible= true;
	CategorieFrm->BtBnUnite->Visible= false;
}
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::EcranRecDiv(void)
{
	CategorieFrm->BtTva->Visible= true;
	CategorieFrm->BtBnUnite->Visible= false;
}
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::EcranVariable(void)
{
	CategorieFrm->BtTva->Visible= false;
	CategorieFrm->BtBnUnite->Visible= true;
}
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::EcranZone(void)
{
	CategorieFrm->BtTva->Visible= false;
	CategorieFrm->BtBnUnite->Visible= false;
}
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::BtBnImpClick(TObject *Sender)
{
	CategorieFrm->ImpTout(V_Categorie,V_Item);
}

//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::BtClHautClick(TObject *Sender)
{
	if(No==0) return;
	if(No==LB->Items->Count-1)return; //derniere ligne= [...]

	LabelModifie->Visible=true;
	LB->Items->Exchange(No,No-1);
	No--;
	LB->ItemIndex=No;
	OrdreModif=true;

}
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::BtClBasClick(TObject *Sender)
{
	if(No<0) return;
	if(No==LB->Items->Count-1)return; //derniere ligne= [...]
	if(No==LB->Items->Count-2)return;//derniere ligne= [...]

	LabelModifie->Visible=true;
	LB->Items->Exchange(No,No+1);
	No++;
	LB->ItemIndex=No;
	OrdreModif=true;
}

//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::BtClasserClick(TObject *Sender)
{
	PClasst->Visible= true; //290302
	BtBnCreer->Enabled= false;
	BtSupprimer->Enabled= false;
	BtModifier->Enabled= false;

}
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::BtBnFermClasstClick(TObject *Sender)
{
	PClasst->Visible= false; //290302
	BtBnCreer->Enabled= true;
	BtSupprimer->Enabled= true;
	BtModifier->Enabled= true;

}
//---------------------------------------------------------------------------
void __fastcall TGereCatFrm::BtBnCopierClick(TObject *Sender)
{
	CL_Categorie *cat= NULL;
	bool rep;
	CL_Categorie *ancCat=NULL;
	AnsiString titre;
	int n;
	CL_Item *item,*nouvItem;
	TList *list;
	cat=CategorieFrm->Categorie;

	if(cat==NULL )
	{
		MessageBox(Handle,"Rien à copier","PROBLEME",
				MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	if(CEstBon()==false) return;

	NewNom=cat->Nom;
	titre="Copie de  "+cat->Nom;
	rep=ES->EntrerNom(titre,"",NewNom);
	if(rep==false )return;

	NewNom=NewNom.Trim();
	if(NewNom.IsEmpty()==true) return;
	if(NewNom=="[...]") return;
	if(NewNom==cat->Nom)
	{
		MessageBox(Handle,"modifier le nom "," EXISTE DEJA"
				,MB_OK|MB_ICONEXCLAMATION);
		return;
	}

	ancCat=V_Categorie->trouve(NewNom);
	if(ancCat)
	{
		MessageBox(Handle,"Elle existe déjà",
				"ERREUR",MB_OK|MB_ICONEXCLAMATION);
		return;
	}

	NouvCat=new CL_Categorie();
	NouvCat->Nom=NewNom;
	NouvCat->Flag=NOUVEAU;
	BtOKClick(this);
//	ShowMessage("Copier Items");
	list=new TList;
	for(n=0;n<V_Item->Nbelt;n++)
	{
		item=V_Item->Vecteur[n];
		if(item->Categorie!= cat) continue;

		nouvItem=new CL_Item (item);
		nouvItem->Categorie=NouvCat;
		nouvItem->NoCategorie=NouvCat->No;
		list->Add(nouvItem);
	}
	for(n=0;n<list->Count;n++)
	{
		nouvItem=(CL_Item*)list->Items[n];
		V_Item->ins(nouvItem);
	}
	delete list;
}
//---------------------------------------------------------------------------

