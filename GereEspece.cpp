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

#include "Main.h"
#include "Espece.h"
#include "Atelier.h"
#include "CL_Trad.h"
#include "GereCatItem.h"    //061206
#include "Aide.h"
#include "QRCatNom.h"
#include "QuelExcelCSV.h"

#include "GereEspece.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GereAtelier"
#pragma resource "*.dfm"
TGereEspeceFrm *GereEspeceFrm;

extern CL_ES *ES;
extern CL_Trad *T;
extern CL_Excel *EX;

//---------------------------------------------------------------------------
__fastcall TGereEspeceFrm::TGereEspeceFrm(TComponent* Owner) :
		TGereAtelierFrm(Owner) {
}
//---------------------------------------------------------------------------
//perso
//---------------------------------------------------------------------------
void __fastcall TGereEspeceFrm::FormActivate(TObject *Sender)
{
	if(Origine==0)
	{
		PClasst->Visible=false;
		LabelModifie->Visible=false;
		Personnaliser();
		Espece=NULL;
		Atelier=NULL;
		BtCatEnabled(false);
		BtAtelierEnabled(false);
		Origine=1;
	}
}
//---------------------------------------------------------------------------
void __fastcall TGereEspeceFrm::Personnaliser(void)
{
//	Caption=                   "Perennes";
	V_Atelier= V_Perenne;
//tjrs V_Espece
	AtelierFrm->Nature=Nature;
	CreeTV();

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//void __fastcall TGereEspeceFrm::CreeTV(void)
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
void __fastcall TGereEspeceFrm::TVClick(TObject *Sender)
{
	TVDblClick(Sender);
}
//----------------------------------------------------------------------------
void __fastcall TGereEspeceFrm::TVDblClick(TObject *Sender)
{
	TTreeNode *elt;
	if(CEstBon()==false) return;

	if(TV->Selected==NULL) return;

	elt=TV->Selected;
	if(elt->Level==0 ) //categorie
	{
		// espece à créer
		if(elt->Text=="[...]")
		{
			BtCatCreerClick(this);
			return;
		}
		else
		{
			// catégorie existe  qu'est ce qu'on va en faire ?
			Espece= (CL_Espece*)elt->Data;
			BtCatEnabled(true);
		}
	}
	else //atelier
	{
		Espece= (CL_Espece*)elt->Parent->Data;
		BtCatEnabled(true);
		// atelier à créer
		if(elt->Text=="[...]")
		{
			BtAtelierCreerClick(this);
			return;
		}
		else
		{
			Atelier= (CL_Atelier*)elt->Data;
			if(Atelier->NbPhase!=Atelier->Espece->NbPhase+1)
			modifQtePhase(Atelier);
			BtAtelierEnabled(true);
			AtelierFrm->Espece=Espece;
			AffAtelier();
		}
	}
}
//----------------------------------------------------------------------------
void __fastcall TGereEspeceFrm::AffAtelier(void)
{

	if(PClasst->Visible==true)return;

	// si pas d'atelier voulez vous créer
	if(Atelier==NULL)
	{
		BtAtelierCreerClick(this);
		return;
	}

	//indique si atelier supprimable
	if(Atelier->Supprimable==false)
	AtelierFrm->LabUtilise->Visible=true;
	else
	AtelierFrm->LabUtilise->Visible=false;

	AtelierFrm->Atelier=Atelier;
	AtelierFrm->Espece=Atelier->Espece;

	AtelierFrm->Origine=0;
	AtelierFrm->Show();
	AtelierFrm->AffAtelier();
	AtelierFrm->Caption=Espece->Nom;//151203
	AtelierFrm->Nature=Nature;//151203

}

//---------------------------------------------------------------------------
// CATEGORIE
//---------------------------------------------------------------------------
// créer
//---------------------------------------------------------------------------
void __fastcall TGereEspeceFrm::BtCatCreerClick(TObject *Sender)
{
	EspeceFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TGereEspeceFrm::RetourDeDefEspece(void)
{
	CreeTV();
}
//---------------------------------------------------------------------------
//void __fastcall TGereAtelierFrm::BtCatCreerClick(TObject *Sender)
//---------------------------------------------------------------------------
//  supprimer
//---------------------------------------------------------------------------
void __fastcall TGereEspeceFrm::BtCatSupprimerClick(TObject *Sender)
{
	int rep;

	if(Espece==NULL )return;
	// si a des éléments tous doivent etre supprimables
	if(Espece->Supprimable==false)
	{
		MessageBox(Handle,"a des éléments !",Espece->Nom.c_str(),MB_OK|MB_ICONSTOP);
		return;
	}

	rep=MessageBox(Handle,"Vous voulez vraiment supprimer !",
			Espece->Nom.c_str(),MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDYES)
	{
		V_Espece->sup(Espece);
		ES->ecrireFichier();
		CreeTV();
		Espece=NULL;
		BtCatEnabled(false);
		BtAtelierEnabled(false);
	}
}
//---------------------------------------------------------------------------
// Nettoie: retire tous les ateliers inutilisés
//---------------------------------------------------------------------------
//void __fastcall TGereAtelierFrm::BtCatNettoyerClick(TObject *Sender)
//---------------------------------------------------------------------------
//  copier
//---------------------------------------------------------------------------
void __fastcall TGereEspeceFrm::BtCatCopierClick(TObject *Sender)
{
	bool rep;
	AnsiString newNom;
	int n;
	CL_Atelier *atelier;
	CL_Espece *especeOrigine;
	especeOrigine=Espece;

	newNom=especeOrigine->Nom;
	rep=ES->EntrerNom("Nouvelle Catégorie copie de","",newNom);
	if(rep==false) return;

	rep=VerifNomCat(newNom,COPIER); //020804 COPIER
	if(rep==false) return;

	for(n=0;n<V_Atelier->Nbelt;n++)
	{
		atelier=V_Atelier->Vecteur[n];
		if(atelier->Espece!=especeOrigine) continue;

		atelier=new CL_Atelier(atelier);
		atelier->Espece=Espece;
		atelier->NoEspece=Espece->No;
		atelier->Supprimable=true;

		V_Atelier->ins(atelier);
	}

	ES->ecrireFichier();
	CreeTV();
}
//---------------------------------------------------------------------------
// modifier nom
//---------------------------------------------------------------------------
void __fastcall TGereEspeceFrm::BtCatModifNomClick(TObject *Sender)
{
	TTreeNode *elt;
	CL_Espece *espece;
	bool rep;
	AnsiString newNom;
	if(TV->Selected==NULL)
	{
		MessageBox(Handle,"Aucun elément n'est sélectionné","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		return;
	}

	elt=TV->Selected;
	// categorie ou atelier
	//modif nom Categorie
	if(elt->Level==0)
	espece=(CL_Espece*)elt->Data;
	else
	espece=(CL_Espece*)elt->Parent->Data;

	newNom=espece->Nom;
	rep=ES->EntrerNom("Modification Nom Espèce","",newNom);
	if (rep==true)
	{
		newNom=newNom.Trim();
		if(newNom==espece->Nom) return;
		VerifNomCat(newNom,MODIFIER);
	}
}
//---------------------------------------------------------------------------
// verifie nom catégorie et l'insére dans TV
//---------------------------------------------------------------------------
bool __fastcall TGereEspeceFrm::VerifNomCat(AnsiString newNom,int action)
{
	CL_Espece *ancEspece=NULL;

	// le nom existe
	newNom=newNom.Trim();
	if (newNom.IsEmpty()==true) {ShowMessage(" Pas de nom");return false;}

	// il n'y a pas de Espece
	ancEspece=V_Espece->trouve(newNom);
	if(ancEspece)
	{
		MessageBox(Handle,"Il existe déjà",
				"ERREUR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	//on a seulement modifie le nom
	if(action==MODIFIER)
	Espece->Nom= newNom;

	//CREER
	else if(action==CREER)
	{
		Espece=new CL_Espece();
		Espece->Nom=newNom;
		V_Espece->ins(Espece);
	}
	//COPIER
	else if(action==COPIER)
	{
		Espece=new CL_Espece(Espece);
		Espece->Nom=newNom;
		V_Espece->ins(Espece);
	}

	ES->ecrireFichier();
	CreeTV();
	return true;
}
//---------------------------------------------------------------------------
// ATELIER
//---------------------------------------------------------------------------
//créer
//---------------------------------------------------------------------------
void __fastcall TGereEspeceFrm::BtAtelierCreerClick(TObject *Sender)
{
	TTreeNode *elt;
	AnsiString titre;
	AnsiString newNom;

	bool rep;
	if(CEstBon()==false) return;

	elt=TV->Selected;
	if(elt->Level==0 )
	Espece= (CL_Espece*)elt->Data;
	else
	Espece= (CL_Espece*)elt->Parent->Data;

	if(Espece==NULL)
	{
		ShowMessage("Aucune Catégorie sélectionnée");
		return;
	}

	newNom="";
	titre=Espece->Nom+"  Nouvel Atelier";
	rep=ES->EntrerNom(titre,"",newNom);
	if(rep==false )return;
	VerifNomAtelier(newNom,CREER);
}
//---------------------------------------------------------------------------
//supprimer
//---------------------------------------------------------------------------
//void __fastcall TGereAtelierFrm::BtAtelierSupprimerClick(TObject *Sender)
//---------------------------------------------------------------------------
//copier
//---------------------------------------------------------------------------
//void __fastcall TGereAtelierFrm::BtAtelierCopierClick(TObject *Sender)
//---------------------------------------------------------------------------
//modifier nom
//---------------------------------------------------------------------------
//void __fastcall TGereAtelierFrm::BtAtelierModifClick(TObject *Sender)
//---------------------------------------------------------------------------
// verif nom atelier et l'insére dans TV
//---------------------------------------------------------------------------
bool __fastcall TGereEspeceFrm::VerifNomAtelier(AnsiString newNom,int action)
{
	CL_Atelier *ancAtelier=NULL;

	// le nom existe
	newNom=newNom.Trim();
	if (newNom.IsEmpty()==true) {ShowMessage(" Pas de nom");return false;}

	// il n'y a pas d'atelier avec ce nom
	ancAtelier=V_Atelier->trouve(newNom);
	if(ancAtelier)
	{
		MessageBox(Handle,"Il existe déjà",
				"ERREUR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	//on a seulement modifie le nom
	if(action==MODIFIER)
	{
		Atelier->Nom= newNom;
		CreeTV();
		return true;
	}

	//CREER
	else if(action==CREER)
	{
		Atelier=new CL_Atelier();
		Atelier->Nom=newNom;
		Atelier->Espece=Espece;
		Atelier->NoEspece=Espece->No;
		//
		Atelier->DurAmor=Espece->DurAmor;
		Atelier->DebAmor=Espece->DebAmor;

		Atelier->NbPhase=Espece->NbPhase+1;//310704 Tenir compte de l'année -1
	}
	else if(action==COPIER)
	{
		Atelier=new CL_Atelier(Atelier);
		Atelier->Nom=newNom;
	}
	V_Atelier->ins(Atelier);

	ES->ecrireFichier();
	CreeTV();
	AffAtelier();
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TGereEspeceFrm::StockerOrdre(void)
{
	int i,jCat,jAt;
	TTreeNode *elt;
	CL_Espece *espece;
	CL_Atelier *atelier;

	jCat=0;
	jAt=0;
	for(i=0;i<TV->Items->Count-1;i++) //ne pas voir le dernier [...]
	{
		elt=TV->Items->Item[i];
		if(elt->Text=="[...]")continue;

		if(elt->Level==0)
		{
			espece=(CL_Espece*)elt->Data;
			V_Espece->Vecteur[jCat]=espece;
			jCat++;
		}
		else
		{
			atelier=(CL_Atelier*)elt->Data;
			V_Atelier->Vecteur[jAt]=atelier;
			jAt++;
		}
	}
}

//**********
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TGereEspeceFrm::modifQtePhase(CL_Atelier *atelier)
{
	AnsiString as;
	MessageBox(Handle,"la durée a été modifiée",
			"DONNEES A REVOIR",MB_OK|MB_ICONEXCLAMATION);
	modifQtePhase1(atelier->V_Produit, atelier->NbPhase,atelier->Espece->NbPhase);
	modifQtePhase1(atelier->V_Charge, atelier->NbPhase,atelier->Espece->NbPhase);
	modifQtePhase1(atelier->V_ChargeVolume,atelier->NbPhase,atelier->Espece->NbPhase);
	modifQtePhase1(atelier->V_Externalite, atelier->NbPhase,atelier->Espece->NbPhase);
	//je tiens compte de l'année -1
	atelier->NbPhase=atelier->Espece->NbPhase+1;
}
//---------------------------------------------------------------------------
void __fastcall TGereEspeceFrm::modifQtePhase1(CL_Vecteur<CL_ItemParAtelier>*vecteur,int nb1,int nb2)
{
	float *qtePhase;
	CL_ItemParAtelier *itemPA;

	nb2++; //je tiens compte de l'année -1
	ShowMessage("210808");
//210808
	/*
	 for(int i=0;i<vecteur->Nbelt;i++)
	 {
	 itemPA=vecteur->Vecteur[i];
	 qtePhase =new float[nb2];
	 memset(qtePhase,0,sizeof(float)*nb2);
	 if(nb2>nb1)
	 for(int j=0;j<nb1;j++) qtePhase[j]=itemPA->QtePhase[j];
	 else
	 for(int j=0;j<nb2;j++) qtePhase[j]=itemPA->QtePhase[j];
	 delete []itemPA->QtePhase;

	 itemPA->QtePhase=qtePhase;
	 }
	 */
}
//--------------------------------------------
void TGereEspeceFrm::IniCaption(void) {
	GereEspeceFrm->Caption = LC_GereEspeceFrm;
	BtCatCreer->Caption = T->LC_BtBnCreer;
	BtAtelierCreer->Caption = T->LC_BtBnCreer;

	BtCatSupprimer->Caption = T->LC_BtBnSupBesTrav;
	BtAtelierSupprimer->Caption = T->LC_BtBnSupBesTrav;
	//BtCatSupprimer->Caption=T->LC_BtBnCreer;
	//BtAtelierSupprimer->Caption=T->LC_BtBnCreer;

	BtCatNettoyer->Caption = T->LC_BtBnEffacer;
	BtCatCopier->Caption = T->LC_BtBnCopier;
	BtAtelierCopier->Caption = T->LC_BtBnCopier;
	BtCatModifNom->Caption = T->LC_BtModifier;
	BtAtelierModifNom->Caption = T->LC_BtModifier;

	BtClasser->Caption = T->LC_BtClasser;
	BtBnFermer->Caption = T->LC_BtBnFermer;
	LabelModifie->Caption = T->LC_LabelModifie_A;
	BtBnQuitter->Caption = T->LC_BtBnQuitter;

	GBCategorie->Caption = T->LC_RGCat;
	GBAtelier->Caption = T->LC_AtelierFrm;

}
//--------------------------------------------
void TGereEspeceFrm::TexteCaption(void) {
	LC_GereEspeceFrm = T->TrouveCaption("GereEspece", "LC_GereEspeceFrm");

	IniCaption();

}
//---------------------------------------------------------------------------
//copier
//---------------------------------------------------------------------------
void __fastcall TGereEspeceFrm::BtAtelierCopierClick(TObject *Sender)
{
	CL_Atelier *atelier= NULL;
	CL_Atelier *newAtelier;
	bool rep;
	AnsiString titre;
	AnsiString newNom;
	atelier=AtelierFrm->Atelier;

	if(atelier==NULL )
	{
		//MessageBox(Handle,"Rien à copier","PROBLEME",
		MessageBox(Handle,GereCatItemFrm->L_RienACop.c_str(),GereCatItemFrm->L_Prob.c_str(),
				MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	if(CEstBon()==false) return;

	//définir nom de la copie
	newNom=atelier->Nom;
	titre="Copie de  "+atelier->Nom;
	rep=ES->EntrerNom(titre,"",newNom);
	if(rep==false )return;

	newAtelier=new CL_Atelier(atelier);
	newAtelier->Nom=newNom;
	V_Atelier->ins(newAtelier);

	Atelier=newAtelier;
	ES->ecrireFichier();
	CreeTV();
	AffAtelier();

}
//---------------------------------------------------------------------------

bool __fastcall TGereEspeceFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=545;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

void __fastcall TGereEspeceFrm::BtBnImpClick(TObject *Sender)
{
	AnsiString as;
	as=T->L_Atelier+"  "+T->L_Perenne;
	QRCatNomFrm->PreparePerenne(AgriEnCours,as.c_str(),V_Espece,V_Perenne);

}
//---------------------------------------------------------------------------

void __fastcall TGereEspeceFrm::BtBnExcelClick(TObject *Sender)
{
	QuelExcelCSVFrm->ShowModal();
	if(QuelExcelCSVFrm->Renonce==true) return;
	EX->CatPerenne(V_Espece,V_Perenne);
	EX->FermerFichier();

}
//---------------------------------------------------------------------------

