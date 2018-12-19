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
//#include "Categorie.h"
#include "Indicateur.h"
//#include "EtatSortie.h"
#include "TVDico.h"
#include "AgriSaisie.h"
#include "DefEtatSortie.h"
#include "DefProcedure.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "GereEtat.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "GereAtelier"
#pragma resource "*.dfm"
TGereEtatFrm *GereEtatFrm;

extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TGereEtatFrm::TGereEtatFrm(TComponent* Owner) :
		TGereAtelierFrm(Owner) {
}

//---------------------------------------------------------------------------
void __fastcall TGereEtatFrm::FormActivate(TObject *Sender)
{
	if(Origine==0)
	{
		GBAtelier->Caption="Etats";
		PClasst->Visible=false;
		LabelModifie->Visible=false;
		OrdreModif=false; //151203
		Categorie=NULL;
		Etat=NULL;
		BtCatEnabled(false);
		BtAtelierEnabled(false);
		Origine=1;

//        Caption="Etats";
		//DefEtatSortieFrm->Caption="Etat de Sortie";
		V_Categorie=V_CatEtatSortie;
		V_Etat =V_EtatSortie;
		CreeTV();

		CalculDonnees();

		//DefEtatSortieFrm->Caption="Etats de Sortie";                   //231101
		DefEtatSortieFrm->LabelModifie->Visible=false;
		DefEtatSortieFrm->HelpContext=1820;

		//TVDicoFrm->VientDe="GereEtat";
		TVDicoFrm->Origine=ETAT;
	}
}
//---------------------------------------------------------------------------
void __fastcall TGereEtatFrm::CalculDonnees(void)
{
	if(Global!=ENSEMBLE) // on travaille pour un agri
	{
		if(AgriEnCours)
		{
			AgriSaisieFrm->Calcul0(AgriEnCours);
			//Calcul0 a lancé ES->IniV_Elt
			//                CompleteV_Elt(AgriEnCours)
			//  complet=true je veux tous les éléments
			DefEtatSortieFrm->Agri=AgriEnCours;
			DefProcedureFrm->Agri=AgriEnCours;
			Forme0Frm->CreeTVToutElt(TVDicoFrm->TV,AgriEnCours,true);//060104
			Forme0Frm->CompleteV_Elt(AgriEnCours);
		}
	}
	else //Global=ENSEMBLE         on travaille pour un ensemble
	{
		if(EnsembleEnCours)
		{
			AgriSaisieFrm->CalculEnsemble(EnsembleEnCours);
			//CalculEnsemble a lancé ES->IniV_Elt
			//                       CompleteV_Elt(AgriEnCours)
			//  complet=true je veux tous les éléments
			DefEtatSortieFrm->Agri=EnsembleEnCours->Total;
			Forme0Frm->CreeTVToutElt(TVDicoFrm->TV,EnsembleEnCours->Total,true);//060104
		}
	}
}
//---------------------------------------------------------------------------
// creeTV
//---------------------------------------------------------------------------
void __fastcall TGereEtatFrm::CreeTV(void)
{
	Forme0Frm->CreeTVEtat(TV,V_Categorie,V_Etat);
}
//---------------------------------------------------------------------------
void __fastcall TGereEtatFrm::TVClick(TObject *Sender)
{
	TVDblClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TGereEtatFrm::TVDblClick(TObject *Sender)
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
			GBAtelier->Enabled=true;
		}
	}
	else //etat
	{
		Categorie= (CL_Categorie*)elt->Parent->Data;
		BtCatEnabled(true);
		// etat atelier à créer
		if(elt->Text=="[...]")
		{
			DefEtatSortieFrm->PossibleModifier(true);
			BtAtelierCreerClick(this);
			return;
		}
		else
		{

			Etat= (CL_EtatSortie*)elt->Data;
			BtAtelierEnabled(true);
			DefEtatSortieFrm->PossibleModifier(false);
			AffAtelier();
		}
	}

}
//---------------------------------------------------------------------------
//AffAtelier
//----------------------------------------------------------------------------
void __fastcall TGereEtatFrm::AffAtelier(void)
{

	if(PClasst->Visible==true)return;

	// si pas d'atelier voulez vous créer
	if(Etat==NULL)
	{
		BtAtelierCreerClick(this);
		return;
	}

	DefEtatSortieFrm->EtatSortie=Etat;
	DefEtatSortieFrm->Origine=0;
//	DefEtatSortieFrm->PossibleModifier(false);

	DefEtatSortieFrm->Caption=Categorie->Nom;//151203
	DefEtatSortieFrm->Categorie=Categorie;
	DefEtatSortieFrm->LabCatVar->Caption=Etat->Nom;

	DefEtatSortieFrm->Nature=Nature;//151203
	DefEtatSortieFrm->Show();
//	DefEtatSortieFrm->AffEtatSortie();
//    DefEtatSortieFrm->Nature=Nature;//151203

}
//---------------------------------------------------------------------------
//CATEGORIE
//---------------------------------------------------------------------------
//creer
//void __fastcall TGereEtatFrm::BtBnCreeCatClick(TObject *Sender)
//---------------------------------------------------------------------------
//supprimer
//void __fastcall TGereEtatFrm::BtCatSupprimerClick(TObject *Sender)
//---------------------------------------------------------------------------
//nettoyer
//  inutile a voir
//---------------------------------------------------------------------------
//copier
//---------------------------------------------------------------------------
void __fastcall TGereEtatFrm::BtCatCopierClick(TObject *Sender)
{
	bool rep;
	AnsiString newNom;
	int n;
	CL_EtatSortie *etat;
	CL_Categorie *catOrigine;
	catOrigine=Categorie;

	newNom=catOrigine->Nom;
	//rep=ES->EntrerNom("Nouvelle Catégorie copie de","",newNom);
	rep=ES->EntrerNom(L_NCatCopDe,"",newNom);
	if(rep==false) return;

	rep=VerifNomCat(newNom,CREER);
	if(rep==false) return;

	for(n=0;n<V_Etat->Nbelt;n++)
	{
		etat=V_Etat->Vecteur[n];
		if(etat->Categorie!=catOrigine) continue;

		etat=new CL_EtatSortie(etat);
		etat->Categorie=Categorie;
		etat->NoCategorie=Categorie->No;
		etat->Supprimable=true;

		V_Etat->ins(etat);
	}

	ES->ecrireFichier();
	CreeTV();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//modif Nom categorie
//void __fastcall TGereEtatFrm::BtCatModifNomClick(TObject *Sender)
//---------------------------------------------------------------------------
// verifie nom catégorie et l'insére dans TV
//bool __fastcall TGereAtelierFrm::VerifNomCat(AnsiString newNom,int action)

//---------------------------------------------------------------------------
// ETAT
//---------------------------------------------------------------------------
void __fastcall TGereEtatFrm::BtAtelierCreerClick(TObject *Sender)
{
	TTreeNode *elt;
	AnsiString titre;
	AnsiString newNom;

	bool rep;
	if(CEstBon()==false) return;

	elt=TV->Selected;
	if(elt==NULL) return;

	if(elt->Level==0 )
	Categorie= (CL_Categorie*)elt->Data;
	else
	Categorie= (CL_Categorie*)elt->Parent->Data;

	if(Categorie==NULL)
	{
		ShowMessage(L_PasSel); //"Aucune Catégorie sélectionnée");
		return;
	}
	newNom="";
	if (V_Etat==V_EtatSortie) titre=Categorie->Nom+L_NEtat; //"  Nouvel Etat";
	else if(V_Etat==V_SerieComp) titre=Categorie->Nom+L_NComp;//"  Nouvelle Comparaison";

	rep=ES->EntrerNom(titre,"",newNom);
	if(rep==false )return;
	VerifNomAtelier(newNom,CREER);
}
//---------------------------------------------------------------------------
//supprimer
//---------------------------------------------------------------------------
void __fastcall TGereEtatFrm::BtAtelierSupprimerClick(TObject *Sender)
{
	int rep;
	//tout atelier sélectionné est visible
	if(Etat==NULL) return;

	rep=MessageBox(Handle,L_Sup.c_str(),//"Vous voulez vraiment supprimer !",
			Etat->Nom.c_str(),MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDYES)
	{
		//retirer du vecteur
		V_Etat->sup(Etat);
		Etat=NULL;

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
void __fastcall TGereEtatFrm::BtAtelierCopierClick(TObject *Sender)
{
	CL_EtatSortie *etat= NULL;
	bool rep;
	AnsiString titre;
	AnsiString newNom;
	etat=DefEtatSortieFrm->EtatSortie;

	if(etat==NULL )
	{
		MessageBox(Handle,L_RienACop.c_str(),L_Prob.c_str(), //"Rien à copier","PROBLEME",
				MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	if(CEstBon()==false) return;

	//définir nom de la copie
	newNom=etat->Nom;
	titre=L_CopDe+etat->Nom;//"Copie de  "
	rep=ES->EntrerNom(titre,"",newNom);
	if(rep==false )return;
	//verif et insere
	VerifNomAtelier(newNom,COPIER);

}
//---------------------------------------------------------------------------
// modif nom etat
//---------------------------------------------------------------------------
void __fastcall TGereEtatFrm::BtAtelierModifClick(TObject *Sender)
{
	TTreeNode *elt;
	CL_EtatSortie *etat;
	bool rep;
	AnsiString newNom;
	if(TV->Selected==NULL)
	{
		MessageBox(Handle,L_PasSel.c_str(),L_Impo.c_str(), //"Aucun elément n'est sélectionné","IMPOSSIBLE",
				MB_OK|MB_ICONSTOP);
		return;
	}

	elt=TV->Selected;
	// categorie ou etat
	//modif nom Categorie
	if(elt->Level==0) return;
	etat=DefEtatSortieFrm->EtatSortie;
	newNom=etat->Nom;
	rep=ES->EntrerNom(L_ModNom,"",newNom);//"Modification Nom "
	if (rep==true)
	{
		newNom=newNom.Trim();
		if(newNom==etat->Nom) return;
		VerifNomAtelier(newNom,MODIFIER);
	}

}
//---------------------------------------------------------------------------
// verif nom atelier et l'insére dans TV
//---------------------------------------------------------------------------
bool __fastcall TGereEtatFrm::VerifNomAtelier(AnsiString newNom,int action)
{
	CL_EtatSortie *ancEtat=NULL;

	// le nom existe
	newNom=newNom.Trim();
	if (newNom.IsEmpty()==true) {ShowMessage(L_PasNom);return false;} //" Pas de nom"

	// il n'y a pas d'atelier avec ce nom
	ancEtat=V_Etat->trouve(newNom);
	if(ancEtat)
	{
		MessageBox(Handle,L_Existe.c_str(),L_Erreur.c_str(), //"Il existe déjà","ERREUR",
				MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	//on a seulement modifie le nom
	if(action==MODIFIER)
	{
		Etat->Nom= newNom;
		CreeTV();
		return true;
	}

	//CREER
	else if(action==CREER)
	{
		Etat=new CL_EtatSortie();
		Etat->Nom=newNom;
		Etat->Categorie=Categorie;
		Etat->NoCategorie=Categorie->No;

	}
	else if(action==COPIER)
	{
		Etat=new CL_EtatSortie(Etat);
		Etat->Nom=newNom;
	}
	V_Etat->ins(Etat);

	ES->ecrireFichier();
	CreeTV();
	AffAtelier();
	return true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Verif Close
//---------------------------------------------------------------------------
bool __fastcall TGereEtatFrm::CEstBon(void)
{
	if(DefEtatSortieFrm->Visible==false) return true;

	DefEtatSortieFrm->Close();
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TGereEtatFrm::FormCloseQuery(TObject *Sender,
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
//void __fastcall TGereEtatFrm::BtHautClick(TObject *Sender)

//---------------------------------------------------------------------------
//clBas
//void __fastcall TGereEtatFrm::BtBasClick(TObject *Sender)
//---------------------------------------------------------------------------
void __fastcall TGereEtatFrm::StockerOrdre(void)
{
	int i,jCat,jAt;
	TTreeNode *elt;
	CL_Categorie *categorie;
	CL_EtatSortie *etat;

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
			etat=(CL_EtatSortie*)elt->Data;
			V_Etat->Vecteur[jAt]=etat;
			jAt++;
		}
	}
}
//--------------------------------------------
void TGereEtatFrm::TexteChaine(void) {
	L_NCatCopDe = T->TrouveTexte("GereEtatFrm", "L_NCatCopDe");
	L_PasSel = T->TrouveTexte("GereEtatFrm", "L_PasSel");
	L_NEtat = T->TrouveTexte("GereEtatFrm", "L_NEtat");

	L_NComp = T->TrouveTexte("GereEtatFrm", "L_NComp");
	L_Sup = T->TrouveTexte("GereEtatFrm", "L_Sup");
	L_RienACop = T->TrouveTexte("GereEtatFrm", "L_RienACop");
	L_Prob = T->TrouveTexte("GereEtatFrm", "L_Prob");
	L_Impo = T->TrouveTexte("GereEtatFrm", "L_Impo");
	L_ModNom = T->TrouveTexte("GereEtatFrm", "L_ModNom");
	L_PasNom = T->TrouveTexte("GereEtatFrm", "L_PasNom");
	L_Existe = T->TrouveTexte("GereEtatFrm", "L_Existe");
	L_Erreur = T->TrouveTexte("GereEtatFrm", "L_Erreur");
	L_CopDe = T->TrouveTexte("GereEtatFrm", "L_CopDe");

}
//--------------------------------------------
void TGereEtatFrm::IniCaption(void) {
	GBAtelier->Caption = LC_GBAtelier;
	GereEtatFrm->Caption = LC_GereEtatFrm;

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
void TGereEtatFrm::TexteCaption(void) {
	LC_GBAtelier = T->TrouveCaption("GereEtat", "LC_GBAtelier");
	LC_GereEtatFrm = T->TrouveCaption("GereEtat", "LC_GereEtatFrm");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TGereEtatFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=1820;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

