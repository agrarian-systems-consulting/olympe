//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "Forme0.h"

#include "QRGrille00.h"
#include "QRCatNom.h"
#include "QRCatNomTva.h"
#include "QRCatNomUnite.h"
#include "QRCatTout.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "GereCatItem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGereCatItemFrm *GereCatItemFrm;
extern CL_ES *ES;
extern CL_Trad *T;

/*
 GereCatItem              V_Categorie   V_Item

 GereCatProduit           V_CatProduit  V_Produit
 V_CatCharge   V_Charge

 GereCatChStruct          V_CatChStruct  V_ChStruct
 V_CatDepDiv    V_DepDiv
 V_CatRecDiv    V_RecDiv
 V_CatDepFam    V_DepFam
 V_CatRecFam    V_RecFam

 GereCatVariable          V_CatVar          V_Variable
 V_CatExternalite  V_Externalite

 GereCatZone              V_CatTypeZone    V_TypeZone

 GereAtelier              V_Culture        V_Atelier=V_Culture
 GereEspece               V_Espece         V_Atelier
 GereEtat                 V_CatEtatSortie  V_EtatSortie
 GereIndic                V_CatIndic       V_Indic
 GereComparaison          V_CatSerieComp   V_SerieComp
 GereCalendrier           V_Calendrier

 */
//---------------------------------------------------------------------------
__fastcall TGereCatItemFrm::TGereCatItemFrm(TComponent* Owner) :
		TForm(Owner) {
	if (ES->Verrou == MEDTER) //040205
	{
		BtBnCreer->Enabled = false;
		BtSupprimer->Enabled = false;
		BtModifier->Enabled = false;
		BtBnCopier->Enabled = false;
		BtClasser->Enabled = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TGereCatItemFrm::FormActivate(TObject *Sender)
{
	AnsiString as;
	as=GereCatItemFrm->L_Impo;
	as=L_Impo;
	L_Impo=GereCatItemFrm->L_Impo;
	RegleProbleme();
//290908
	Origine=0;
	if(Origine==0)
	{
		PClasst->Visible=false; //panel pour classer
		LabelModifie->Visible=false;
		OrdreModif=false;
		No=0;//eviter reclassement si pas de sélection
		Personnaliser();
		Forme0Frm->CreeLBCat(LB,V_Categorie);
//		Categorie=NULL; 301008
		Origine=1;

	}
}
//---------------------------------------------------------------------------
void __fastcall TGereCatItemFrm::Personnaliser(void)
{
	ShowMessage("Personnaliser absent");
}
//---------------------------------------------------------------------------
void __fastcall TGereCatItemFrm::LBClick(TObject *Sender)
{
	ShowMessage("LBClick absent");
}
//---------------------------------------------------------------------------
//Modifier le nom de la categorie
//---------------------------------------------------------------------------
void __fastcall TGereCatItemFrm::BtModifierNomClick(TObject *Sender)
{
	bool rep;
	AnsiString newNom;
	if(Categorie==NULL)
	{
		//MessageBox(Handle,"Aucun elément n'est sélectionné","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		MessageBox(Handle,L_PasSel.c_str(),L_Impo.c_str(),MB_OK|MB_ICONSTOP);
		return;
	}
	newNom=Categorie->Nom;
	rep=ES->EntrerNom(L_ModifNom,newNom,newNom);
	//rep=ES->EntrerNom("Modification du Nom",newNom,newNom);
	if(rep==true)
	{
		//on a redonné le même nom
		if(newNom==Categorie->Nom) return;
		//on a change le nom vérifier qu'il n'est pas vide et qu'il n'existe pas
		VerifNomCat(newNom,MODIFIER);
	}
}
//---------------------------------------------------------------------------
bool __fastcall TGereCatItemFrm::NouvelleCategorie(void)
{
	bool rep;
	AnsiString newNom;
	newNom="";
	rep=ES->EntrerNom(L_NouvCat,"",newNom);
	//rep=ES->EntrerNom("Nouvelle Catégorie","",newNom);
	if(rep==false) return false;

	newNom=newNom.Trim();
	if(newNom.IsEmpty()==true) return false;

	rep=VerifNomCat(newNom, CREER);
	return rep;
}
//---------------------------------------------------------------------------
void __fastcall TGereCatItemFrm::BtBnCopierClick(TObject *Sender)
{
	bool rep;
	int n;
	AnsiString titre;
	AnsiString newNom;
	CL_Categorie *cat;
	CL_Item *item,*nouvItem;

	if(Categorie==NULL )
	{
		MessageBox(Handle,L_RienACop.c_str(),L_Prob.c_str(),
				//MessageBox(Handle,"Rien à copier","PROBLEME",
				MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	cat=Categorie;

	// definir nom de la copie
	newNom=Categorie->Nom;
	//titre="Copie de  "+Categorie->Nom;
	titre=L_CopieDe+Categorie->Nom;
	rep=ES->EntrerNom(titre,"",newNom);
	if(rep==false )return;

	//nom existe et pas de doublon + insertion dans V_Categorie
	// Categorie c(est ce qu'on vient de créer
	VerifNomCat(newNom,CREER);

	//trouver les item de la categorie et les inserer dans V_item
	for(n=0;n<V_Item->Nbelt;n++)
	{
		item=V_Item->Vecteur[n];
		if(item->Categorie!= cat) continue;

		nouvItem=new CL_Item (item);
		nouvItem->Categorie=Categorie;
		nouvItem->NoCategorie=Categorie->No;
		V_Item->ins(nouvItem);
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//
//---------------------------------------------------------------------------
bool __fastcall TGereCatItemFrm::VerifNomCat(AnsiString newNom,int action)
{
	int n;
	CL_Categorie *cat, *ancCat=NULL;

	// le nom existe
	newNom=newNom.Trim();
	//if (newNom.IsEmpty()==true){ ShowMessage(" Pas de nom");return false; }
	if (newNom.IsEmpty()==true) {ShowMessage(L_PasNom);return false;}

	// il n'y a pas de categorie avec ce nom
	ancCat=V_Categorie->trouve(newNom);
	if(ancCat)
	{
		//MessageBox(Handle,"Il existe déjà",
		//        "ERREUR",MB_OK|MB_ICONEXCLAMATION);
		MessageBox(Handle,L_Existe.c_str(),
				L_Erreur.c_str(),MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	//on a seulement modifie le nom
	if(action==MODIFIER)
	{
		Categorie->Nom= newNom;
		LabelModifie->Visible=true;
		n=LB->ItemIndex;
		Forme0Frm->CreeLBCat(LB,V_Categorie);
		LB->ItemIndex=n;
		return true;
	}

	//CREER

	cat=new CL_Categorie();
	cat->Nom=newNom;
	V_Categorie->ins(cat);

	Categorie=cat;
	LabelModifie->Visible=true;

	n=LB->ItemIndex;
	Forme0Frm->CreeLBCat(LB,V_Categorie);
	LB->ItemIndex=n;
	return true;
}

//---------------------------------------------------------------------------
void __fastcall TGereCatItemFrm::BtBnCreerClick(TObject *Sender)
{
	No=LB->Items->Count;
	NouvelleCategorie();
}
//---------------------------------------------------------------------------
void __fastcall TGereCatItemFrm::BtSupprimerClick(TObject *Sender)
{
	int rep;
	char buf[100];
	AnsiString as;
	as=GereCatItemFrm->L_Impo;
	as=L_Impo;
	if(Categorie==NULL)return;

	if(Categorie->Supprimable==false)
	{
		//MessageBox(Handle,"Cette catégorie a des éléments!","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		MessageBox(Handle,T->L_CatAElt.c_str(),T->L_Impo.c_str(),MB_OK|MB_ICONSTOP);
		return;
	}

	//sprintf(buf," Je supprime %s \n Vous êtes sur ?",Categorie->Nom.c_str() );
	sprintf(buf,L_JSup.c_str(),Categorie->Nom.c_str() );
	//rep=MessageBox(Handle,buf,"SUPPRESSION",MB_YESNO|MB_ICONEXCLAMATION);
	rep=MessageBox(Handle,buf,L_Sup.c_str(),MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDNO) return;

	if(rep==IDYES)
	{
		//retirer du vecteur
		V_Categorie->sup(Categorie);
		Categorie=NULL;
		ES->ecrireFichier();
		LabelModifie->Visible=false;
		///actualiser LB TV
		Forme0Frm->CreeLBCat(LB,V_Categorie);
		//CategorieFrm->LabCatVar->Caption="";
		LB->SetFocus();
	}
}
//---------------------------------------------------------------------------
void __fastcall TGereCatItemFrm::StockerOrdre(CL_Vecteur<CL_Categorie> *vecteur)
{
	int i;
	for(i=0;i<LB->Items->Count;i++)
	vecteur->Vecteur[i]=(CL_Categorie*)LB->Items->Objects[i];
	OrdreModif=false;
}

//---------------------------------------------------------------------------
// Sortie Brutale
//---------------------------------------------------------------------------
void __fastcall TGereCatItemFrm::BtBnQuitterClick(TObject *Sender)
{
	int rep;
	rep=MessageBox(Handle,T->L_QuitQ.c_str(),T->L_QuitT.c_str(),
			//rep=MessageBox(Handle,"Vous voulez vraiment quitter","QUITTER OLYMPE",
			MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDYES) Application->Terminate();
	else return;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Sortie avec Verif
//---------------------------------------------------------------------------
void __fastcall TGereCatItemFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	int rep;
	if(LabelModifie->Visible==true)
	{
		//rep=MessageBox(Handle,T->L_DonModifQ.c_str(),"MODIFICATION",
		rep=MessageBox(Handle,T->L_DonModifQ.c_str(),L_Modif.c_str(),
				MB_YESNOCANCEL|MB_ICONEXCLAMATION);
		if(rep==ID_YES)
		{
			if(OrdreModif==true) StockerOrdre(V_Categorie);

			ES->ecrireFichier();
			LabelModifie->Visible=false;
		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TGereCatItemFrm::BtBnImpClick(TObject *Sender)
{
	switch(Nature)
	{
		case PRODUIT:
		//QRCatToutFrm->Prepare(AgriEnCours,"Produits",V_Categorie,V_Item);
		QRCatToutFrm->Prepare(AgriEnCours,L_Prod.c_str(),V_Categorie,V_Item);
		break;
		case CHARGE:
		//QRCatToutFrm->Prepare(AgriEnCours,"Charges Opérationnelles",V_Categorie,V_Item);
		QRCatToutFrm->Prepare(AgriEnCours,L_ChOp.c_str(),V_Categorie,V_Item);
		break;

		case ZONE:
		//QRCatNomFrm->Prepare(AgriEnCours,"Clé de Classement",V_Categorie,V_Item);
		QRCatNomFrm->Prepare(AgriEnCours,L_CleClass.c_str(),V_Categorie,V_Item);
		break;
		case BESTIAUX:
		//QRCatNomFrm->Prepare(AgriEnCours,"Animaux",V_Categorie,V_Item);
		QRCatNomFrm->Prepare(AgriEnCours,L_Ani.c_str(),V_Categorie,V_Item);
		break;

		case CHSTRUCT:
		//QRCatNomTvaFrm->Prepare(AgriEnCours,"Charges de Structure",V_Categorie,V_Item);
		QRCatNomTvaFrm->Prepare(AgriEnCours,L_ChStruct.c_str(),V_Categorie,V_Item);
		break;
		case RECDIV:
		//QRCatNomTvaFrm->Prepare(AgriEnCours,"Recettes Diverses",V_Categorie,V_Item);
		QRCatNomTvaFrm->Prepare(AgriEnCours,L_RecDiv.c_str(),V_Categorie,V_Item);
		break;
		case RECFAM:
		//QRCatNomTvaFrm->Prepare(AgriEnCours,"Recettes Familiales",V_Categorie,V_Item);
		QRCatNomTvaFrm->Prepare(AgriEnCours,L_RecFam.c_str(),V_Categorie,V_Item);
		break;
		case DEPFAM:
		//QRCatNomTvaFrm->Prepare(AgriEnCours,"Dépenses Familiales",V_Categorie,V_Item);
		QRCatNomTvaFrm->Prepare(AgriEnCours,L_DepFam.c_str(),V_Categorie,V_Item);
		break;

		case VARIABLE:
		//QRCatNomUniteFrm->Prepare(AgriEnCours,"Variables",V_Categorie,V_Item);
		QRCatNomUniteFrm->Prepare(AgriEnCours,L_Var.c_str(),V_Categorie,V_Item);
		break;
		case EXTPOS:
		//QRCatNomUniteFrm->Prepare(AgriEnCours,"Externalités",V_Categorie,V_Item);
		QRCatNomUniteFrm->Prepare(AgriEnCours,L_Exter.c_str(),V_Categorie,V_Item);
		break;
		default:
		ShowMessage("Oubli Categorie");
	}
}
//---------------------------------------------------------------------------
// Classer
//---------------------------------------------------------------------------
void __fastcall TGereCatItemFrm::BtClasserClick(TObject *Sender)
{
	PClasst->Visible= true; //290302
	BtBnCreer->Enabled= false;
	BtSupprimer->Enabled= false;
	BtBnCopier->Enabled= false;
	BtModifier->Enabled= false;

}
//---------------------------------------------------------------------------
void __fastcall TGereCatItemFrm::BtClHautClick(TObject *Sender)
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
void __fastcall TGereCatItemFrm::BtClBasClick(TObject *Sender)
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
void __fastcall TGereCatItemFrm::BtBnFermClasstClick(TObject *Sender)
{
	PClasst->Visible= false; //290302
	BtBnCreer->Enabled= true;
	BtBnCopier->Enabled= true;
	BtSupprimer->Enabled= true;
	BtModifier->Enabled= true;
//    BtClAlpha->
	LB->Sorted=false;
}
//---------------------------------------------------------------------------

void __fastcall TGereCatItemFrm::BtClAlphaClick(TObject *Sender)
{
	LB->Sorted=true;
}
//grand mystere ça règle le pb
//mais je voudrais comprendre
//---------------------------------------------------------------------------
void TGereCatItemFrm::RegleProbleme(void) {

	L_PasSel = GereCatItemFrm->L_PasSel;

	L_Impo = GereCatItemFrm->L_Impo;
//    L_CatAElt=GereCatItemFrm->L_CatAElt;
	L_ModifNom = GereCatItemFrm->L_ModifNom;
	L_NouvCat = GereCatItemFrm->L_NouvCat;
	L_RienACop = GereCatItemFrm->L_RienACop;
	L_Prob = GereCatItemFrm->L_Prob;
	L_PasNom = GereCatItemFrm->L_PasNom;
	L_Existe = GereCatItemFrm->L_Existe;
	L_Erreur = GereCatItemFrm->L_Erreur;
	L_JSup = GereCatItemFrm->L_JSup;
	L_Sup = GereCatItemFrm->L_Sup;
	L_Modif = GereCatItemFrm->L_Modif;
	L_Prod = GereCatItemFrm->L_Prod;
	L_ChOp = GereCatItemFrm->L_ChOp;
	L_CleClass = GereCatItemFrm->L_CleClass;
	L_Ani = GereCatItemFrm->L_Ani;
	L_ChStruct = GereCatItemFrm->L_ChStruct;
	L_DepDiv = GereCatItemFrm->L_DepDiv;
	L_RecDiv = GereCatItemFrm->L_RecDiv;
	L_RecFam = GereCatItemFrm->L_RecFam;
	L_DepFam = GereCatItemFrm->L_DepFam;
	L_Var = GereCatItemFrm->L_Var;
	L_Exter = GereCatItemFrm->L_Exter;
	L_CopieDe = GereCatItemFrm->L_CopieDe;

}

//---------------------------------------------------------------------------
void TGereCatItemFrm::TexteChaine(void) {

	L_PasSel = T->TrouveTexte("GereCatItemFrm", "L_PasSel");
	L_Impo = T->TrouveTexte("GereCatItemFrm", "L_Impo");
//    L_CatAElt=T->L_CatAElt");
	L_ModifNom = T->TrouveTexte("GereCatItemFrm", "L_ModifNom");
	L_NouvCat = T->TrouveTexte("GereCatItemFrm", "L_NouvCat");
	L_RienACop = T->TrouveTexte("GereCatItemFrm", "L_RienACop");
	L_Prob = T->TrouveTexte("GereCatItemFrm", "L_Prob");
	L_PasNom = T->TrouveTexte("GereCatItemFrm", "L_PasNom");
	L_Existe = T->TrouveTexte("GereCatItemFrm", "L_Existe");
	L_Erreur = T->TrouveTexte("GereCatItemFrm", "L_Erreur");
	L_JSup = T->TrouveTexte("GereCatItemFrm", "L_JSup");
	L_Sup = T->TrouveTexte("GereCatItemFrm", "L_Sup");
	L_Modif = T->TrouveTexte("GereCatItemFrm", "L_Modif");
	L_Prod = T->TrouveTexte("GereCatItemFrm", "L_Prod");
	L_ChOp = T->TrouveTexte("GereCatItemFrm", "L_ChOp");
	L_CleClass = T->TrouveTexte("GereCatItemFrm", "L_CleClass");
	L_Ani = T->TrouveTexte("GereCatItemFrm", "L_Ani");
	L_ChStruct = T->TrouveTexte("GereCatItemFrm", "L_ChStruct");
	L_RecDiv = T->TrouveTexte("GereCatItemFrm", "L_RecDiv");
	L_RecFam = T->TrouveTexte("GereCatItemFrm", "L_RecFam");
	L_DepFam = T->TrouveTexte("GereCatItemFrm", "L_DepFam");
	L_Var = T->TrouveTexte("GereCatItemFrm", "L_Var");
	L_Exter = T->TrouveTexte("GereCatItemFrm", "L_Exter");
	L_CopieDe = T->TrouveTexte("GereCatItem", "L_CopieDe");

}

//--------------------------------------------
void TGereCatItemFrm::IniCaption(void) {
	BtClAlpha->Caption = T->LC_BtBnAlpha;
	BtClasser->Caption = T->LC_BtClasser;
	BtBnCopier->Caption = T->LC_BtBnCopier;
	BtBnCreer->Caption = T->LC_BtBnCreer;
	BtBnFermer->Caption = T->LC_BtBnFermer;
	GereCatItemFrm->Caption = LC_GereCatItemFrm;
	BtModifier->Caption = T->LC_BtModifier;
	LabelModifie->Caption = T->LC_LabelModifie_A;
	BtBnQuitter->Caption = T->LC_BtBnQuitter;
	BtSupprimer->Caption = T->LC_BtBnSupBesTrav;
}
//--------------------------------------------
void TGereCatItemFrm::TexteCaption(void) {
	LC_BtBnAlpha = T->TrouveCaption("CL_Trad", "LC_BtBnAlpha");
	LC_BtClasser = T->TrouveCaption("CL_Trad", "LC_BtClasser");
	LC_BtBnCopier = T->TrouveCaption("CL_Trad", "LC_BtBnCopier");
	LC_BtBnCreer = T->TrouveCaption("CL_Trad", "LC_BtBnCreer");
	LC_BtBnFermer = T->TrouveCaption("CL_Trad", "LC_BtBnFermer");
	LC_GereCatItemFrm = T->TrouveCaption("GereCatItem", "LC_GereCatItemFrm");
	LC_BtModifier = T->TrouveCaption("CL_Trad", "LC_BtModifier");
	LC_LabelModifie_A = T->TrouveCaption("CL_Trad", "LC_LabelModifie_A");
	LC_BtBnQuitter = T->TrouveCaption("CL_Trad", "LC_BtBnQuitter");
	LC_BtBnSupBesTrav = T->TrouveCaption("CL_Trad", "LC_BtBnSupBesTrav");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TGereCatItemFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=295;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

void __fastcall TGereCatItemFrm::BtBnAideClick(TObject *Sender)
{
	HelpContext=295;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);

}
//---------------------------------------------------------------------------

