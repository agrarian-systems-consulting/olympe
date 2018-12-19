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
#include "Erreur.h"

#include "Main.h"
//#include "Categorie.h"
#include "Indicateur.h"
//#include "EtatSortie.h"
#include "TVDico.h"
#include "AgriSaisie.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "GereIndic.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GereAtelier"
#pragma resource "*.dfm"
TGereIndicFrm *GereIndicFrm;

extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TGereIndicFrm::TGereIndicFrm(TComponent* Owner) :
		TGereAtelierFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TGereIndicFrm::FormActivate(TObject *Sender)
{
	if(Origine==0)
	{
		PClasst->Visible=false;
		LabelModifie->Visible=false;
		OrdreModif=false; //151203
		Categorie=NULL;
		Indic=NULL;
		BtCatEnabled(false);
		BtAtelierEnabled(false);
		Origine=1;

//        GereIndicFrm->Caption="INDICATEURS";
		V_Categorie=V_CatIndic;
		//V_Indic
		CreeTV();

		if(Global!=ENSEMBLE)// on travaille pour un agri
		{
			if(AgriEnCours)
			AgriSaisieFrm->Calcul0(AgriEnCours);
		}
		else //Global=ENSEMBLE         on travaille pour un ensemble
		{
			if(EnsembleEnCours)
			AgriSaisieFrm->CalculEnsemble(EnsembleEnCours);
		}
		IndicateurFrm->LabelModifie->Visible=false; //inutile ? c'est le boulot de IndicFrm->Activate
		TVDicoFrm->Origine=INDIC;
//        TVDicoFrm->VientDe="GereIndic";
	}
}
//---------------------------------------------------------------------------
// creeTV
//---------------------------------------------------------------------------
void __fastcall TGereIndicFrm::CreeTV(void)
{
	Forme0Frm->CreeTVIndicateur(TV);
}
//---------------------------------------------------------------------------
void __fastcall TGereIndicFrm::TVClick(TObject *Sender)
{
	TVDblClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TGereIndicFrm::TVDblClick(TObject *Sender)
{
	TTreeNode *elt;
	if(CEstBon()==false) return;

	if(TV->Selected==NULL) return;

	elt=TV->Selected;
	if(elt->Level==0 ) //categorie
	{
		// catégorie à créer
		if(elt->Text=="[...]")
		{
			BtCatCreerClick(this);
			return;
		}
		else
		{
			// catégorie existe  qu'est ce qu'on va en faire ?
			Categorie= (CL_Categorie*)elt->Data;
			BtCatEnabled(true);
		}
	}
	else //indicateur
	{
		Categorie= (CL_Categorie*)elt->Parent->Data;
		BtCatEnabled(true);
		// indicateur etat atelier à créer
		if(elt->Text=="[...]")
		{
			BtAtelierCreerClick(this);
			return;
		}
		else
		{
			Indic= (CL_Indicateur*)elt->Data;
			Indic->Flag=EXISTE;
			BtAtelierEnabled(true);
			IndicateurFrm->PossibleModifier(false);
			AffAtelier();
		}
	}

}
//---------------------------------------------------------------------------
//AffAtelier
//----------------------------------------------------------------------------
void __fastcall TGereIndicFrm::AffAtelier(void)
{

	if(PClasst->Visible==true)return;

	// si pas d'atelier voulez vous créer
	if(Indic==NULL)
	{
		BtAtelierCreerClick(this);
		return;
	}

	IndicateurFrm->Indicateur=Indic;
	IndicateurFrm->Origine=0;

	IndicateurFrm->Caption=Categorie->Nom; //151203
//??    IndicateurFrm->LabNom->Caption=Indic->Nom;

	IndicateurFrm->Show();
	IndicateurFrm->AffIndicateur();
	IndicateurFrm->Nature=Nature;//151203

}
//---------------------------------------------------------------------------
//CATEGORIE
//---------------------------------------------------------------------------
//creer
//void __fastcall TGereIndicFrm::BtBnCreeCatClick(TObject *Sender)
//---------------------------------------------------------------------------
//supprimer
//void __fastcall TGereIndicFrm::BtCatSupprimerClick(TObject *Sender)
//---------------------------------------------------------------------------
//nettoyer
//  inutile a voir
//---------------------------------------------------------------------------
//copier
//---------------------------------------------------------------------------
void __fastcall TGereIndicFrm::BtCatCopierClick(TObject *Sender)
{
	bool rep;
	AnsiString newNom;
	int n;
	CL_Indicateur *indic;
	CL_Categorie *catOrigine;
	catOrigine=Categorie;

	newNom=catOrigine->Nom;
	rep=ES->EntrerNom("Nouvelle Catégorie copie de","",newNom);
	if(rep==false) return;

	rep=VerifNomCat(newNom,CREER);
	if(rep==false) return;

	for(n=0;n<V_Indicateur->Nbelt;n++)
	{
		indic=V_Indicateur->Vecteur[n];
		if(indic->Categorie!=catOrigine) continue;

		indic=new CL_Indicateur(indic);
		indic->Categorie=Categorie;
		indic->NoCategorie=Categorie->No;
		indic->Supprimable=true;

		V_Indicateur->ins(indic);
	}

	ES->ecrireFichier();
	CreeTV();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//modif Nom categorie
//void __fastcall TGereIndicFrm::BtCatModifNomClick(TObject *Sender)
//---------------------------------------------------------------------------
// verifie nom catégorie et l'insére dans TV
//bool __fastcall TGereAtelierFrm::VerifNomCat(AnsiString newNom,int action)

//---------------------------------------------------------------------------
// Indicateur
//---------------------------------------------------------------------------
void __fastcall TGereIndicFrm::BtAtelierCreerClick(TObject *Sender)
{
	TTreeNode *elt;
	AnsiString titre;
	AnsiString newNom;

	bool rep;
	if(CEstBon()==false) return;

	elt=TV->Selected;
	if(elt->Level==0 )
	Categorie= (CL_Categorie*)elt->Data;
	else
	Categorie= (CL_Categorie*)elt->Parent->Data;

	if(Categorie==NULL)
	{
		ShowMessage("Aucune Catégorie sélectionnée");
		return;
	}

	newNom="";
	titre=Categorie->Nom+"  Nouvel Indicateur";
	rep=ES->EntrerNom(titre,"",newNom);
	if(rep==false )return;
	VerifNomAtelier(newNom,CREER);
}
//---------------------------------------------------------------------------
//supprimer
//---------------------------------------------------------------------------
void __fastcall TGereIndicFrm::BtAtelierSupprimerClick(TObject *Sender)
{
	int rep;
	//tout atelier sélectionné est visible
	if(Indic==NULL) return;
	if(Indic->Supprimable==false)
	{
		ShowMessage(" UTILISE ");
		return;
	}

	rep=MessageBox(Handle,"Vous voulez vraiment supprimer !",
			Indic->Nom.c_str(),MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDYES)
	{
		//retirer du vecteur
		V_Indicateur->sup(Indic);
		Indic=NULL;

		ES->ecrireFichier();
		CreeTV();
		//pb possible si Etat a erreurs
		// on ne peut supprimer que Etat correct:idiot!!
		//EtatFrm->Close();
	}

}
//---------------------------------------------------------------------------
//copier
//---------------------------------------------------------------------------
void __fastcall TGereIndicFrm::BtAtelierCopierClick(TObject *Sender)
{
	bool rep;
	AnsiString titre;
	AnsiString newNom;

	if(Indic==NULL )
	{
		MessageBox(Handle,"Rien à copier","PROBLEME",
				MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	if(CEstBon()==false) return;

	//définir nom de la copie
	newNom=Indic->Nom;
	titre="Copie de  "+Indic->Nom;
	rep=ES->EntrerNom(titre,"",newNom);
	if(rep==false )return;
	//verif et insere
	VerifNomAtelier(newNom,COPIER);

}
//---------------------------------------------------------------------------
// modif nom Indicateur
//---------------------------------------------------------------------------
void __fastcall TGereIndicFrm::BtAtelierModifClick(TObject *Sender)
{
	TTreeNode *elt;
	bool rep;
	AnsiString newNom;
	if(TV->Selected==NULL)
	{
		MessageBox(Handle,"Aucun elément n'est sélectionné","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		return;
	}

	elt=TV->Selected;
	// categorie ou etat
	//modif nom Categorie
	if(elt->Level==0) return;
//    indic=Indic;
	newNom=Indic->Nom;
	rep=ES->EntrerNom("Modification Nom Atelier","",newNom);
	if (rep==true)
	{
		newNom=newNom.Trim();
		if(newNom==Indic->Nom) return;
		VerifNomAtelier(newNom,MODIFIER);
	}

}
//---------------------------------------------------------------------------
// verif nom atelier et l'insére dans TV
//---------------------------------------------------------------------------
bool __fastcall TGereIndicFrm::VerifNomAtelier(AnsiString newNom,int action)
{
	CL_Indicateur *ancIndic=NULL;

	// le nom existe
	newNom=newNom.Trim();
	if (newNom.IsEmpty()==true) {ShowMessage(" Pas de nom");return false;}

	// il n'y a pas d'atelier avec ce nom
	ancIndic=V_Indicateur->trouve(newNom);
	if(ancIndic)
	{
		MessageBox(Handle,"Il existe déjà",
				"ERREUR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	//IndicateurFrm->LabelModifie->Visible=true; //030205
	// a faire après AffAtelier

	//on a seulement modifie le nom
	if(action==MODIFIER)
	{
		Indic->Nom= newNom;
		CreeTV();
		IndicateurFrm->PossibleModifier(false);
		return true;
	}

	else if(action==CREER)
	{
		Indic=new CL_Indicateur();
		Indic->Nom=newNom;
		Indic->Categorie=Categorie;
		Indic->NoCategorie=Categorie->No;
		IndicateurFrm->PossibleModifier(true);
	}

	else if(action==COPIER)
	{
		Indic=new CL_Indicateur(Indic);
		Indic->Nom=newNom;
		IndicateurFrm->PossibleModifier(false);
	}
	Indic->Flag=NOUVEAU;

	AffAtelier();
	IndicateurFrm->LabelModifie->Visible=true; //030205

	return true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Verif Close
//---------------------------------------------------------------------------
bool __fastcall TGereIndicFrm::CEstBon(void)
{
	if(IndicateurFrm->Visible==false) return true;

	IndicateurFrm->Close();
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TGereIndicFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	bool rep;
	TVDicoFrm->Visible=false;
	if(CEstBon()==false)
	{
		CanClose=false;
		return;
	}

	if(OrdreModif==true)
	{
		rep=MessageBox(Handle,T->L_DonModifQ.c_str(),
				//rep=MessageBox(Handle," Vous voulez conserver ?",
				"ORDRE MODIFIE",MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==true)
		{
			StockerOrdre();
			ES->ecrireFichier();
			LabelModifie->Visible=false;
		}
		OrdreModif=false;
	}

	if(LabelModifie->Visible==true)
	{
		ES->ecrireFichier();
		LabelModifie->Visible=false;
	}
//    EtatSortieFrm->Close(); fait dans CestBon
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//reclasse Tlist origine dans GereAtelier
// créer une classe mère de GereAtelier
//                            GereEtat
//                            GereIndic
//---------------------------------------------------------------------------
// clHaut
//void __fastcall TGereIndicFrm::BtHautClick(TObject *Sender)

//---------------------------------------------------------------------------
//clBas
//void __fastcall TGereIndicFrm::BtBasClick(TObject *Sender)
//---------------------------------------------------------------------------
void __fastcall TGereIndicFrm::StockerOrdre(void)
{
	int i,jCat,jAt;
	TTreeNode *elt;
	CL_Categorie *categorie;
	CL_Indicateur *indic;

	jCat=0;
	jAt=0;
	for(i=0;i<TV->Items->Count-1;i++) //ne pas voir le dernier [...]
	{
		elt=TV->Items->Item[i];
		if(elt->Text=="[...]")continue;

		if(elt->Level==0)
		{
			categorie=(CL_Categorie *)elt->Data;
			V_Categorie->Vecteur[jCat]=categorie;
			jCat++;
		}
		else
		{
			indic=(CL_Indicateur*)elt->Data;
			V_Indicateur->Vecteur[jAt]=indic;
			jAt++;
		}
	}
}

//***************************
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//reclasse Tlist origine dans GereAtelier
// créer une classe mère de GereAtelier
//                            GereEtat
//                            GereIndic
//---------------------------------------------------------------------------
//void __fastcall TGereIndicFrm::BtHautClick(TObject *Sender)
//---------------------------------------------------------------------------
//void __fastcall TGereIndicFrm::BtBasClick(TObject *Sender)

void __fastcall TGereIndicFrm::BtCatNettoyerClick(TObject *Sender)
{
//
	int n,rep;
	bool jAiSupprime;
	CL_Indicateur *indic;
	rep=MessageBox(Handle,"j'efface tous les indicateurs INUTILISES ?","NETTOYER",MB_YESNO|MB_ICONQUESTION);
	if(rep==IDNO) return;

	jAiSupprime=false;
	for(n=0;n<V_Indicateur->Nbelt;n++)
	{
		indic=V_Indicateur->Vecteur[n];
		if(indic->Categorie!=Categorie) continue;

		if(indic->Supprimable==false) continue;

		V_Indicateur->sup(indic);
		n--;
		jAiSupprime=true;
	}
	if(jAiSupprime==false) return;

	ES->ecrireFichier();
	CreeTV();

}
//---------------------------------------------------------------------------

//--------------------------------------------
void TGereIndicFrm::IniCaption(void) {
	GereIndicFrm->Caption = LC_GereIndicFrm;
	GBAtelier->Caption = T->LC_GBAtelier_A;

	BtBnAlpha->Caption = T->LC_BtBnAlpha;
	GBAtelier->Caption = T->LC_AtelierFrm;
	GBCategorie->Caption = T->LC_RGCat;
	GereAtelierFrm->Caption = LC_GereAtelierFrm;
	BtClasser->Caption = T->LC_BtClasser;
	BtCatCopier->Caption = T->LC_BtBnCopier;
	BtAtelierCopier->Caption = T->LC_BtBnCopier;
	BtCatCreer->Caption = T->LC_BtBnCreer;
	BtAtelierCreer->Caption = T->LC_BtBnCreer;
	BtCatModifNom->Caption = T->LC_BtModifier;
	BtAtelierModifNom->Caption = T->LC_BtModifier;
	LabelModifie->Caption = T->LC_LabelModifie_A;
	BtCatNettoyer->Caption = T->LC_BtBnEffacer;
	BtBnQuitter->Caption = T->LC_BtBnQuitter;
	BtCatSupprimer->Caption = T->LC_BtBnSupBesTrav;
	BtAtelierSupprimer->Caption = T->LC_BtBnSupBesTrav;

}
//--------------------------------------------
void TGereIndicFrm::TexteCaption(void) {
	LC_GereIndicFrm = T->TrouveCaption("GereIndic", "LC_GereIndicFrm");
	LC_GBAtelier_A = T->TrouveCaption("CL_Trad", "LC_GBAtelier_A");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TGereIndicFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

