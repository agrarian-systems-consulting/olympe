//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"

#include "LesVecteurs.hse"
#include "GereAgri.h"
#include "Erreur.h"
#include "Resultat.h"
//#include "Compilateur.h"

#include "TVChoix.h"
#include "TVDico.h"
#include "LBChoix.h"
#include "LBChoixMC.h"
#include "LBChoixTva.h"

#include "AgriDefSim.h"
#include "PolStock.h"
#include "Commercialisation.h"

//#include "Reclasse.h"
#include "SituDepart.h"

#include "AgriSaisieEnum.h"
#include "Assol.h"
//#include "Graph.h"
#include "InvAni.h"
#include "Troupeau.h"
#include "LBCompAgri.h"

#include "QRGrille00.h"

#include "FenRepart.h"
#include "Treso.h"
#include "CL_Trad.h"
#include "NoteAgri.h"

#include "Outil.h"
#include "Main.h"
#include "TypeEmpLT.h"
#include "TypeAmor.h"
#include "TypeEmpCT.h"
#include "TypePlact.h"
#include "Aide.h"
#include "Conversion.h"
#include "ResGraph.h"
#include "TravGraph.h"
#include "TravCal.h"

#include "AgriSaisie.h"
//extern CL_Compil *Compil;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TAgriSaisieFrm *AgriSaisieFrm;

extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TAgriSaisieFrm::TAgriSaisieFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
}
//---------------------------------------------------------------------------
/*
 Height 480  745
 Width  696  1032
 */
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::FormCreate(TObject *Sender)
{
	LaGrille=Grille0;
//    debut=true;
	EstInitialise=false;

//FormCreate appelle  FormActivate                  ²²²²²²²

}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::FormActivate(TObject *Sender)
{
	MainForm->Visible=false;
	if(EstInitialise==false)
	{
//        WindowState=wsMaximized;
		LaGrille=Grille0;
		LabSais->Caption="";
		AjoutRow=true;
		GrilleX=1;// a augmenter
		LesGrilles[0]=Grille0;//cf forme00 VideLesGrilles

//!!        Grille0->Visible=  false;
		// ajout item ds menu leblanc p 171
		if(Agri==NULL )
		{
			if(EstInitialise==false)return; // bug toujours mysterieux
			ShowMessage("Pas d'agriculteur");
			AgriSaisieFrm->Close();
			return;
		}

		TVChoixFrm->Left=
		AgriSaisieFrm->Left+AgriSaisieFrm->Width-TVChoixFrm->Width;
		TVChoixFrm->Top= AgriSaisieFrm->Top+20;

		LBChoixFrm->Left= AgriSaisieFrm->Left+AgriSaisieFrm->Width-LBChoixFrm->Width;
		LBChoixFrm->Top= AgriSaisieFrm->Top+20;

		LBChoixMCFrm->Left= BtMotCle->Left;

		HauteurMemo=Memo->Height;
		EstInitialise=true;
	}
//  si on vient de GereAgri
	AgriEnCours=Agri;

	TVDicoFrm->Complet=false;//pour n'afficher que les élt presents chez l'agri
	TVDicoFrm->Agri=Agri;

	AgriSaisieFrm->Caption=Agri->NomVC();
	if(Origine==0)//est mis à 0 dans GereAgri
	{
		// trouver pour mettre a jour en cas de modif des CatVar
		LaGrille->Tag=GClose;
		PrepareEcran();
		Grille0->Visible= false;
		Agri->IniGlobal();
		Calcul0(Agri);

//      c'est fait dans Calcul0
//	    ES->IniV_Elt();
//		CreeTVToutElt(TVDicoFrm->TV,Agri,false);

		Origine=2;
		return;
	}

}
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::correction(void)
{
}
//......
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::FormResize(TObject *Sender)
{

	LEcran=AgriSaisieFrm->Width;
	HEcran=AgriSaisieFrm->Height-20; //150506 les hollandais ont menu sur 2 lignes
	TailleGrille();
	Repaint();

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DefinitionClick(TObject *Sender)
{
	if(CEstBon()==false) return;

	AgriDefSimFrm->Origine=0;
	AgriDefSimFrm->Aff();
	AgriDefSimFrm->Show();

}
//---------------------------------------------------------------------------
//CEstBon stocke données actualise resultats y compris formule
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::AssolementClick(TObject *Sender)
{
	TMenuItem *tmi;
	if(CEstBon()==false) return;

	LaGrille->Tag=GAssol;
	PrepareEcran();

	tmi=(TMenuItem *)Sender;
	LabSais->Caption=tmi->Caption;

	TVChoixFrm->Caption=T->L_Culture;
	//TVChoixFrm->Caption="CULTURES";
	TitreGrille=T->L_Culture;
	//TitreGrille="CULTURES";
	IniGrille(LaGrille);
	VersGrille(LaGrille);

	LaGrille->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::PerennesClick(TObject *Sender)
{
	TMenuItem *tmi;
	if(CEstBon()==false) return;

	LaGrille->Tag=GPerenne;
	PrepareEcran();

	tmi=(TMenuItem *)Sender;
	LabSais->Caption=tmi->Caption;

	TVChoixFrm->Caption=L_Perenne;
	//TVChoixFrm->Caption="PERENNES";
	TitreGrille=L_Perenne;
	//TitreGrille="PERENNES";
	IniGrille(LaGrille);
	VersGrille(LaGrille);
//    CellDebut();
	LaGrille->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::AnimauxClick(TObject *Sender)
{
	TMenuItem *tmi;
	if(CEstBon()==false) return;

	LaGrille->Tag=GAni;
	PrepareEcran();

	tmi=(TMenuItem *)Sender;
	LabSais->Caption=tmi->Caption;

	TVChoixFrm->Caption=L_Animaux;
	//TVChoixFrm->Caption="ANIMAUX";
	TitreGrille=L_Animaux;
	IniGrille(Grille0);
	VersGrille(Grille0);
//    CellDebut();
	LaGrille->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::InventaireAnimauxClick(TObject *Sender)
{
	if(CEstBon()==false) return;

	TroupeauFrm->Origine=0;
	TroupeauFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VivriersClick(TObject *Sender)
{
	TMenuItem *tmi;
	if(CEstBon()==false) return;

	LaGrille->Tag=GVivrier;
	PrepareEcran();

	tmi=(TMenuItem *)Sender;
	LabSais->Caption=tmi->Caption;

	TVChoixFrm->Caption=L_Pluri;
	//TVChoixFrm->Caption="PLURIANNUELLES";
	TitreGrille=L_Pluri;
	IniGrille(Grille0);
	VersGrille(Grille0);

//	CellDebut();
	LaGrille->Visible=true;

}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VariablesClick(TObject *Sender)
{
	if(CEstBon()==false) return;

	LaGrille->Tag=GVariable;
	PrepareEcran();

	LabSais->Caption=L_Variable;
	//LabSais->Caption="Variables";
	BtDonnees->Caption =L_Variable;
	TitreGrille=L_Variable;
	IniGrille(Grille0);
	VersGrille(Grille0);

	LaGrille->Visible=true;
}
//---------------------------------------------------------------------------
// grille a formule
// une TV colonne de gauche
// une TV pour le memo
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::PRODUITSClick(TObject *Sender)
{
	if(CEstBon()==false) return;

	LaGrille->Tag=GProduit;
	PrepareEcran();

	LabSais->Caption=T->L_Produit;
	//LabSais->Caption="Produits";
	// pour remplir colonne de gauche
	TVChoixFrm->Caption=T->L_Produit;
	TitreGrille=T->L_Produit.UpperCase();//"PRODUITS";
	IniGrille(LaGrille);
	VersGrille(LaGrille);

//	AffFormule(Agri->V_Produits,V_CatProduit);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::ChargesOpeClick(TObject *Sender)
{
	if(CEstBon()==false) return;

	LaGrille->Tag=GCharge;
	PrepareEcran();

	LabSais->Caption=L_ChOpe; //="Charges Opérationnelles";
	// pour remplir colonne de gauche
	TVChoixFrm->Caption=L_ChOpe;
	TitreGrille=L_ChOpe.UpperCase();//"CHARGES OPERATIONNELLES";
	IniGrille(Grille0);
	VersGrille(Grille0);

//	AffFormule(Agri->V_Charges,V_CatCharge);
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::StructureClick(TObject *Sender)
{
//    ShowMessage("En Travaux");return;
	if(CEstBon()==false) return;

	LaGrille->Tag=GChStruct;
	PrepareEcran();

	LabSais->Caption=L_ChStruct;//            "Charges de Structure";
	// pour remplir colonne de gauche
	TVChoixFrm->Caption=L_ChStruct;//"CH. de Structure";
	TitreGrille=L_ChStruct.UpperCase();//"CHARGES DE STRUCTURE";
	IniGrille(Grille0);
	VersGrille(Grille0);

//	AffFormule(Agri->V_ChStruct,V_CatChStruct);
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::ProduitsDiversClick(TObject *Sender)
{
//	if(CEstBon()==false) return;
	Calcul0(Agri);//test 191211
	LaGrille->Tag=GRecDiv;
	PrepareEcran();

	LabSais->Caption=L_RecDiv;//"Recettes Diverses";
	// pour remplir colonne de gauche
	TVChoixFrm->Caption=L_RecDiv;//"Recettes Diverses";
	TitreGrille=L_RecDiv.UpperCase();//"RECETTES DIVERSES";
	IniGrille(Grille0);
	VersGrille(Grille0);

//	AffFormule(Agri->V_RecDiv,V_CatRecDiv);

}
//---------------------------------------------------------------------------
//charges Divers
void __fastcall TAgriSaisieFrm::ChargesDiversClick(TObject *Sender)
{
//ShowMessage("en travaux");//return;

	if(CEstBon()==false) return;

	LaGrille->Tag=GDepDiv;
	PrepareEcran();

	LabSais->Caption=L_DepDiv;//"Dépenses Diverses";
	// pour remplir colonne de gauche
	TVChoixFrm->Caption=L_DepDiv;//"Dépenses Diverses";
	TitreGrille=L_DepDiv.UpperCase();//"DEPENSES DIVERSES";

	IniGrille(Grille0);
	VersGrille(Grille0);

//	AffFormule(Agri->V_DepDiv,V_CatDepDiv);

}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::NegativesClick(TObject *Sender)
{
	if(CEstBon()==false) return;

	LaGrille->Tag=GExtNeg;
	PrepareEcran();

	LabSais->Caption=L_ExtNeg; //"Externalités Négatives";
	LabSais->Caption=L_ExtNeg;//"Ext Neg";
	LBChoixFrm->Caption=L_ExtNeg;//"Ext Neg";
	TitreGrille=L_ExtNeg.UpperCase();//"EXTERNALITES NEGATIVES";

	// pour remplir colonne de gauche

	IniGrille(Grille0);
	VersGrille(Grille0);

//	AffFormule(Agri->V_ExtNeg,V_CatExternalite);
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::PositivesClick(TObject *Sender)
{
	if(CEstBon()==false) return;

	LaGrille->Tag=GExtPos;
	PrepareEcran();

	LabSais->Caption=L_ExtPos; //"Externalités Positives";
	// pour remplir colonne de gauche
	LBChoixFrm->Caption=L_ExtPos;//"Ext Pos";
	TitreGrille=L_ExtPos.UpperCase();//"EXTERNALITES POSITIVES";

	IniGrille(Grille0);
	VersGrille(Grille0);

//	AffFormule(Agri->V_ExtPos,V_CatExternalite);
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RecettesPriveClick(TObject *Sender)
{
	if(CEstBon()==false) return;

	LaGrille->Tag=GRecFam;
	PrepareEcran();

	LabSais->Caption=L_RecPriv; //"Recettes Privées";
	// pour remplir colonne de gauche
	//LBChoixFrm->Caption=L_RecPriv;            //"Rec Privé";
	TVChoixFrm->Caption=L_RecPriv;//"Rec Privé";    290809
	TitreGrille=L_RecPriv.UpperCase();//"RECETTES PRIVEES";

	IniGrille(Grille0);
	VersGrille(Grille0);

//	AffFormule(Agri->V_RecFam,V_CatRecFam);
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DepensesPriveClick(TObject *Sender)
{
	if(CEstBon()==false) return;

	LaGrille->Tag=GDepFam;
	PrepareEcran();

	LabSais->Caption=L_DepPriv; //"Dépenses Privées";
	// pour remplir colonne de gauche
	//LBChoixFrm->Caption=L_DepPriv;            //"Dep Privé";
	TVChoixFrm->Caption=L_DepPriv;//"Dep Privé";     290908
	TitreGrille=L_DepPriv.UpperCase();//"DEPENSES PRIVEES";

	IniGrille(Grille0);
	VersGrille(Grille0);

//	AffFormule(Agri->V_DepFam,V_CatDepFam);
}
//---------------------------------------------------------------------------
// EMPRUNT LT
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::LongTermeClick(TObject *Sender)
{
	if(CEstBon()==false) return;

	LaGrille->Tag=GEmpLT;
	PrepareEcran();

	LabSais->Caption=L_EmpLT; //"Long Terme" ;
	TitreGrille=L_EmpLT.UpperCase();//"EMPRUNTS LONG TERME";

	IniGrille(Grille0);
	VersGrille(Grille0);

//    CellDebut();
	LaGrille->Visible=true;
	AgriSaisieFrm->HelpFile="Olympe.hlp";
	AgriSaisieFrm->HelpContext=5091;

	TypeEmpLTFrm->Visible=true;//140707

}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CourtTermeClick(TObject *Sender)
{
	if(CEstBon()==false) return;

	LaGrille->Tag=GEmpCT;
	PrepareEcran();
	TypeEmpCTFrm->Visible=true; //130407

	LabSais->Caption=L_EmpCT;//"Court Terme" ;
	TitreGrille=L_EmpCT.UpperCase();//"EMPRUNTS COURT TERME";

	IniGrille(Grille0);
	VersGrille(Grille0);

//    CellDebut();
	LaGrille->Visible=true;

	AgriSaisieFrm->HelpFile="Olympe.hlp";
	AgriSaisieFrm->HelpContext=5092;

}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::SubventionClick(TObject *Sender)
{
	if(CEstBon()==false) return;

	LaGrille->Tag=GSub;
	PrepareEcran();

	LabSais->Caption=L_Sub; //"Subventions" ;
	TitreGrille=L_Sub.UpperCase();//"SUBVENTIONS";

	IniGrille(Grille0);
	VersGrille(Grille0);

//    CellDebut();
	LaGrille->Visible=true;

	AgriSaisieFrm->HelpFile="Olympe.hlp";
	AgriSaisieFrm->HelpContext=5094;

}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::OcccClick(TObject *Sender)
{
	if(CEstBon()==false) return;

	LaGrille->Tag=GOccc;
	PrepareEcran();

	LabSais->Caption=L_Occc; // "Ouverture de Crédit" ;
	TitreGrille=L_Occc.UpperCase();//"OCCC";

	IniGrille(Grille0);
	VersGrille(Grille0);

//    CellDebut();
	LaGrille->Visible=true;

	AgriSaisieFrm->HelpFile="Olympe.hlp";
	AgriSaisieFrm->HelpContext=5093;

}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::PlacementClick(TObject *Sender)
{
	if(CEstBon()==false) return;

	LaGrille->Tag=GPlact;
	PrepareEcran();

	LabSais->Caption=L_Plact; // "Placements" ;
	TitreGrille=L_Plact.UpperCase();//"PLACEMENTS";
	TypePlactFrm->Visible=true;//130407

	IniGrille(Grille0);
	VersGrille(Grille0);

//    CellDebut();
	LaGrille->Visible=true;

	AgriSaisieFrm->HelpFile="Olympe.hlp";
	AgriSaisieFrm->HelpContext=5095;

}
//Entrée sommaire financement
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::FinSomClick(TObject *Sender)
{
	if(CEstBon()==false) return;

	LaGrille->Tag=GFinSom;
	PrepareEcran();

	LabSais->Caption=L_EmpSom; //"Emprunts Saisie Rapide" ;
	TitreGrille=L_EmpSom.UpperCase();//"EMPRUNTS SAISIE RAPIDE";

	IniGrille(Grille0);
	VersGrille(Grille0);

//    CellDebut();
	LaGrille->Visible=true;

	AgriSaisieFrm->HelpFile="Olympe.hlp";
	AgriSaisieFrm->HelpContext=5096;
}
//---------------------------------------------------------------------------
// Inventaire
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::InventaireClick(TObject *Sender)
{
	if(CEstBon()==false) return;

	LaGrille->Tag=GImmo;
	PrepareEcran();

	LabSais->Caption=L_Immo; //"Immobilisations" ;
	LBChoixFrm->Caption=L_Tva;// "TVA";
	TitreGrille=L_Immo.UpperCase();//"IMMOBILISATIONS";

	IniGrille(Grille0);
	VersGrille(Grille0);

//    CellDebut();
	LaGrille->Visible=true;
	AgriSaisieFrm->HelpFile="Olympe.hlp";
	AgriSaisieFrm->HelpContext=5081;

	TypeAmorFrm->Visible=true;//140707

}
//---------------------------------------------------------------------------
//Petit Matériel
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::PetitClick(TObject *Sender)
{
	if(CEstBon()==false) return;

	LaGrille->Tag=GPetit;
	PrepareEcran();

	LabSais->Caption=L_Petit; //"Petit Matériel" ;
	TitreGrille=L_Petit.UpperCase();//"PETIT MATERIEL";

	IniGrille(Grille0);
	VersGrille(Grille0);

//    CellDebut();
	LaGrille->Visible=true;
	AgriSaisieFrm->HelpFile="Olympe.hlp";
	AgriSaisieFrm->HelpContext=5082;

}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::InvSomClick(TObject *Sender)
{

	if(CEstBon()==false) return;

	LaGrille->Tag=GInvSom;
	PrepareEcran();

	LabSais->Caption=L_ImmoRap; // "Immobilisation Saisie Rapide" ;
	TitreGrille=L_ImmoRap.UpperCase();//"IMMOBILISATION SAISIE RAPIDE";

	IniGrille(Grille0);
	VersGrille(Grille0);

//    CellDebut();
	LaGrille->Visible=true;
	AgriSaisieFrm->HelpFile="Olympe.hlp";
	AgriSaisieFrm->HelpContext=5083;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::PolitiqueStockageClick(TObject *Sender)
{
	if(CEstBon()==false) return;
	LaGrille->Tag=GPolStock;
	PrepareEcran();
	TitreGrille=L_PolStock; //"POLITIQUE DE STOCKAGE";

	IniGrille(Grille0);
	VersGrille(Grille0);

	if(LaGrille->RowCount==1)
	ShowMessage(L_PasProd.c_str());//"Aucun Produit !!");
//    else
//	    CellDebut();
	LaGrille->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::StockIniClick(TObject *Sender)
{
//int rep;
	if(CEstBon()==false) return;
	LaGrille->Tag=GStock;
	PrepareEcran();
	TitreGrille=L_StockIni;//"STOCKS INITIAUX";

	LabSais->Caption=L_Stocks;// "Stocks" ;

	IniGrille(Grille0);
	VersGrille(Grille0);

//    CellDebut();
	LaGrille->Visible=true;
//    AgriSaisieFrm->HelpFile="Olympe.hlp";
//    AgriSaisieFrm->HelpContext=23;
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CommercialisationClick(TObject *Sender)
{
	if(CEstBon()==false) return;
	CommercialisationFrm->Origine=0;
	CommercialisationFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CreancesClick(TObject *Sender)
{
	if(CEstBon()==false) return;

	LaGrille->Tag=GCreance;
	PrepareEcran();

	LabSais->Caption=L_Creance; //"Créances" ;
	TitreGrille=L_Creance.UpperCase();//"CREANCES";

	IniGrille(Grille0);
	VersGrille(Grille0);

//    CellDebut();
	LaGrille->Visible=true;
//    AgriSaisieFrm->HelpFile="Olympe.hlp";
//    AgriSaisieFrm->HelpContext=23;

}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::DetteClick(TObject *Sender)
{
	if(CEstBon()==false) return;

	LaGrille->Tag=GDette;
	PrepareEcran();

	LabSais->Caption=L_Dettes; //"Dettes" ;
	TitreGrille=L_Dettes.UpperCase();//"DETTES";

	IniGrille(Grille0);
	VersGrille(Grille0);

	LaGrille->Visible=true;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::PasseClick(TObject *Sender)
{
	int i,nbElt;
	CL_Elt *elt;

	if(CEstBon()==false) return;
	TitreGrille=L_Passe; //"PASSE";

	//compter les éléments pour lesquels on a besoin du passé
	// ils ont elt->Passe!=NULL  en fait elt->Passe =*Valeur Valeur[5]
	// elt->Passe=passe->Valeur cf CL_Passe
	nbElt=0;
	for(i=0;i<V_Elt->Nbelt;i++)
	{
		elt=V_Elt->Vecteur[i];
		if(elt->Passe)
		nbElt++;
	}
	if(nbElt==0)
	{
		MessageBox(Handle,"",L_PasDon.c_str(),MB_ICONEXCLAMATION);
		//MessageBox(Handle,"","Aucune Donnée à introduire",MB_ICONEXCLAMATION);
		return;
	}

	LaGrille->Tag=GPasse;
	PrepareEcran();

	LabSais->Caption=L_DonPasse; //"Données du Passé nécessaires" ;

	IniGrille(Grille0);
	VersGrille(Grille0);

	LaGrille->Visible=true;
}
//---------------------------------------------------------------------------
//test daatselar
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::ComparaisonClick(TObject *Sender)
{

	if(CEstBon()==false) return;
	Calcul0(Agri);

	LaGrille->Tag=GResul;
	PrepareEcran();

	ResultatFrm->Origine=0;
	//Global=false;
	AgriEnCours=Agri;
	AgriEnCours->IniGlobal();
	ResultatFrm->Origine=0;
	ResultatFrm->Agri=Agri;
//    GraphiqueFrm->An_0=Agri->DefSim->An_0;             //111002
	ResultatFrm->Caption=L_ResDe+Agri->NomVC();
	//ResultatFrm->Caption="résultats de "+Agri->NomVC();
	//LBCompAgriFrm->BtBnTousClick(this);   //160808     //100512
	ResultatFrm->Show();

	ResultatFrm->BtBnComparaisonClick(this);//!!
	//ResultatFrm->RGUnOuEnsemble->ItemIndex=1;   //100512
	ResultatFrm->RGUnOuEnsemble->ItemIndex=0;

//!!	ResultatFrm->PresenterResultat();
}
//---------------------------------------------------------------------------

// version ok
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RESULTATSClick(TObject *Sender)
{

	if(CEstBon()==false) return;
	Calcul0(Agri);

	LaGrille->Tag=GResul;
	PrepareEcran();

	ResultatFrm->Origine=0;
	//Global=false;
	AgriEnCours=Agri;
	AgriEnCours->IniGlobal();
	ResultatFrm->Origine=0;
	ResultatFrm->Agri=Agri;
//    GraphiqueFrm->An_0=Agri->DefSim->An_0;             //111002
	ResultatFrm->Caption=L_ResDe+Agri->NomVC();
	//ResultatFrm->Caption="résultats de "+Agri->NomVC();
	ResultatFrm->Show();
	ResultatFrm->PresenterResultat();
}

//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TresorerieClick(TObject *Sender)
{
	if(CEstBon()==false) return;

	TresoFrm->Origine=0;
	//TresoFrm->AgriEnCours=AgriEnCours;     //010506
	TresoFrm->Show();

}
//---------------------------------------------------------------------------
//Boutons
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::BoutFermerClick(TObject *Sender)
{
	int rep;
	rep=MessageBox(Handle,L_QuitAgri.c_str(),L_Att.c_str(),MB_YESNO|MB_ICONEXCLAMATION);
	//rep=MessageBox(Handle," Je quitte cet agriculteur. Vous êtes sur ?",
	//"ATTENTION",MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDNO) return;

	if(CEstBon()==false) return;
	LaGrille->Tag=GClose;
	PrepareEcran();
	Close();//utilise FormCloseQuery de AgriSaisie
			  //et non celui de Forme00
}
//---------------------------------------------------------------------------
//4
//intitule des boutons cf PrepareEcran
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::BtDonneesClick(TObject *Sender)
{
//ne doit etre utilisé que pour choisir dans la deuxieme colonne
//sauf Immo
//    if(Grille0->Tag==GImmo && Grille0->Col!=7)return;//120506
//    if(LaGrille->Col!=2 && LaGrille->Col!=7) return;
	//effacer TV LB si visible
	switch(LaGrille->Tag)
	{
		case GNotes:
		case GResul: return;

//        case GAni:
//    	case GVariable:
		case GExtNeg:
		case GExtPos:
//        case GChStruct:
//        case GRecDiv:
//        case GDepDiv:
//        case GDepFam:
//        case GRecFam:
		case GImmo:
		case GPetit:
		if(LBChoixFrm->Visible==true) {LBChoixFrm->Visible=false;return;}
		break;
		default:
		if(TVChoixFrm->Visible==true) {TVChoixFrm->Visible=false;return;}
	}
	//actualiser TV ou LB: on a pu creer des nouveaux éléments
	switch(LaGrille->Tag)
	{
		case GAssol: CreeTVAtelier (TVChoixFrm->TV,V_CatCulture,V_Culture);break;
		case GVivrier: CreeTVAtelier (TVChoixFrm->TV,V_CatVivrier,V_Vivrier);break;
		case GPerenne: CreeTVPerenne (TVChoixFrm->TV,V_Espece,V_Perenne); break;
		case GAni: CreeTVAtelier (TVChoixFrm->TV, V_CatAnimaux,V_Animaux);break;
//        case GBestiaux: CreeTVItem    (TVChoixFrm->TV, V_CatBestiaux,V_Bestiaux);break;
		case GVariable: CreeTVItem (TVChoixFrm->TV,V_CatVar,V_Variable); break;
		case GProduit: CreeTVItem(TVChoixFrm->TV,V_CatProduit,V_Produit);break;
		case GCharge: CreeTVItem(TVChoixFrm->TV,V_CatCharge,V_Charge); break;
		case GChStruct: CreeTVItem(TVChoixFrm->TV,V_CatChStruct,V_ChStruct); break;
		case GExtNeg: CreeLBItem(LBChoixFrm->LB,V_Externalite,EXTNEG); break;
		case GExtPos: CreeLBItem(LBChoixFrm->LB,V_Externalite,EXTPOS); break;
		case GRecDiv: CreeTVItem(TVChoixFrm->TV,V_CatRecDiv,V_RecDiv); break;
		case GDepDiv: CreeTVItem(TVChoixFrm->TV,V_CatDepDiv,V_DepDiv); break;
		case GRecFam: CreeTVItem(TVChoixFrm->TV,V_CatRecFam,V_RecFam); break;
		case GDepFam: CreeTVItem(TVChoixFrm->TV,V_CatDepFam,V_DepFam); break;
		case GImmo: TypeAmorFrm->Visible=true;
		CreeLBTva(LBChoixFrm->LB,V_Tva,true);
		break;
		case GPetit: CreeLBTva(LBChoixFrm->LB,V_Tva,true); break;
		case GCreance: CreeTVCreance(TVChoixFrm->TV); break;
		case GDette: CreeTVDette (TVChoixFrm->TV); break;
		case GPolStock:
		case GStock: CreeTVItem(TVChoixFrm->TV,V_CatProduit,V_Produit);break;

		case GEmpLT: TypeEmpLTFrm->Visible=true; return;//130407
		//case GEmpLT:    TypeEmpLTFrm->Show();                             return;//130407
		default:ShowMessage(" Oubli BtDonneesClick");break;
	}
	//rendre visible
	switch(LaGrille->Tag)
	{
//        case GAni:       montp
//    	case GVariable:
		case GExtNeg:
		case GExtPos:
//        case GChStruct:
//        case GDepDiv:
//        case GRecDiv:
//        case GDepFam:
//        case GRecFam:
		case GImmo:
		case GPetit:
		LBChoixFrm->Visible=true;
		break;
		default:
		TVChoixFrm->Visible=true;
		break;
	}
}
//BtDico mal nommé  sert pour afficher les surfaces
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::BtDicoClick(TObject *Sender)
{
	int i;
	CL_Verger *verger;
	for(i=0;i<Agri->V_Verger->Nbelt;i++)
	verger=Agri->V_Verger->Vecteur[i];
	switch(LaGrille->Tag)
	{
		case GAssol:
		case GPerenne:
		case GVivrier:
		Grille0Click(this);
		if(VerifGrille()==false)return;
		DesGrilles();

		AssolFrm->Agri=Agri;
		for(i=0;i<Agri->V_Verger->Nbelt;i++)
		{
			verger=Agri->V_Verger->Vecteur[i];
			AssolFrm->VergerSurface(verger); //110302
		}

		AssolFrm->Agri=Agri;
		for(i=0;i<Agri->V_Vivrier->Nbelt;i++)
		{
			verger=Agri->V_Vivrier->Vecteur[i];
			AssolFrm->VergerSurface(verger); //110302
		}

		AssolFrm->Show();
		break;
		/*
		 case GBestiaux:
		 ShowMessage("DicoInvAni Vente");
		 break;
		 */
		default:
		TVDicoFrm->Origine=AGRI;
//            TVDicoFrm->VientDe="AgriSaisie";
		TVDicoFrm->Visible=!TVDicoFrm->Visible;
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::BtMotCleClick(TObject *Sender)
{
	switch(LaGrille->Tag)
	{
		case GCreance:
		case GDette:
		LBChoixTvaFrm->Visible=!LBChoixTvaFrm->Visible;break;
		/*
		 case GBestiaux:
		 ShowMessage("DicoInvAni Achat");
		 break;
		 */
		default:
		LBChoixMCFrm->Visible=!LBChoixMCFrm->Visible;
	}
}
//6
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::BtBnSupClick(TObject *Sender)
{
	int rep;
	int r=LaGrille->Row;
	CL_Valeur *valeur;
	CL_Verger *verger;
//CL_InvAni  *invAni;
	CL_Formule *formule;
	CL_EmpLT *empLT;
	CL_EmpCT *empCT;
	CL_Sub *sub;
	CL_Plact *plact;
//CL_Occc    *occc;
	CL_Immo *immo;
	CL_Petit *petit;
	CL_StockIni *stockIni;
	CL_EnCours *enCours;

	bool supprimable;
	TObject *object=LaGrille->Objects[0][r];
	if(object==NULL) return;
	SelLigne();
	valeur= (CL_Valeur*) LaGrille->Objects[0][r];
	verger= (CL_Verger*) LaGrille->Objects[0][r];
//	invAni= (CL_InvAni*)     LaGrille->Objects[0][r];
	formule=(CL_Formule*) LaGrille->Objects[0][r];
	empLT= (CL_EmpLT*) LaGrille->Objects[0][r];
	empCT= (CL_EmpCT*) LaGrille->Objects[0][r];
	sub= (CL_Sub*) LaGrille->Objects[0][r];
	plact= (CL_Plact*) LaGrille->Objects[0][r];
//    occc=   (CL_Occc*)   LaGrille->Objects[0][r];
	immo= (CL_Immo*) LaGrille->Objects[0][r];
	petit= (CL_Petit*) LaGrille->Objects[0][r];
	stockIni=(CL_StockIni*) LaGrille->Objects[0][r];
	enCours= (CL_EnCours*) LaGrille->Objects[0][r];
	r=r;//aew
	//Grille NON modifiable ?
	if( RGModifiable->ItemIndex==0)
	{
		MessageBox(Handle,L_DonNonModif.c_str(),T->L_Erreur.c_str(),MB_ICONSTOP);
		//MessageBox(Handle,"Données NON Modifiables","ERREUR",MB_ICONSTOP);
		DeSelLigne();
		return;
	}
	supprimable=true;
	switch( LaGrille->Tag)
	{
		//case GAssol:                              //cultures
		//case GAni:                                //animaux
		//case GVariable:                           //variables
		//        supprimable=true;
		//        break;
		//case GPerenne:                             //perennes
		//        supprimable=verger->Supprimable;
		//        break;
		//300512 TP
		case GExtPos:
		case GExtNeg:
		//--case GProduit:
		case GCharge:
		case GChStruct:
		case GRecDiv:
		case GDepDiv:
		case GRecFam:
		case GDepFam:
		if(formule->Origine=='C')supprimable=false;
		else supprimable=true;
		break;
		//default:ShowMessage("BtSupClick Oubli");
	}

	if(supprimable==false)
	{
		MessageBox(Handle,L_LiNonSup.c_str(),T->L_Impo.c_str(),MB_OK|MB_ICONSTOP);
		//MessageBox(Handle," Ligne NON supprimable?","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
		DeSelLigne();
		return;
	}

	rep=MessageBox(Handle,T->L_SupLiQ.c_str(),T->L_SupT.c_str(), MB_YESNO|MB_ICONEXCLAMATION);

	//rep=MessageBox(Handle," Je supprime la ligne. Vous êtes sur ?","SUPPRESSION",
	if(rep==IDNO) {DeSelLigne(); return;}
	switch( LaGrille->Tag)
	{
		case GAssol: //cultures
		case GAni://animaux
		valeur->Flag='S';break;
		case GVariable://variables
		//if(valeur->Supprimable
		valeur->Flag='S';break;
		/*
		 case GBestiaux:
		 invAni->Flag='S';break;
		 */
		case GVivrier:
		case GPerenne: //perennes
		verger->Flag='S';break;
		//300512 TP
		case GExtPos:
		case GExtNeg:
		//--
		case GProduit:
		case GCharge:
		case GChStruct:
		case GRecDiv:
		case GDepDiv:
		case GRecFam:
		case GDepFam: formule->Flag='S';break;

		case GEmpLT: empLT->Flag='S';break;
		case GEmpCT: empCT->Flag='S';break;
		case GSub: sub->Flag='S';break;
		case GPlact: plact->Flag='S';break;
//        case GOccc:     occc->Flag='S';break;
		case GImmo: immo->Flag='S';break;
		case GPetit: petit->Flag='S';break;
		case GCreance:
		case GDette: enCours->Flag='S';break;
		case GStock: stockIni->Flag='S';
		SupprimerLigne(2);//300603
		GrilleModif[LaGrille->Tag]=true;
		DeSelLigne();
		return;
		case GPolStock: break;//je stocke tout le tableau:simplification

		default:ShowMessage("BtSupClick Oubli");
	}
	SupprimerLigne();
	GrilleModif[LaGrille->Tag]=true;
	DeSelLigne();
}
//---------------------------------------------------------------------------

void __fastcall TAgriSaisieFrm::BtBnVoirClick(TObject *Sender)
{
	bool correct;
	CL_EmpLT *empLT;
	CL_EmpCT *empCT;
	CL_Sub *sub;
	CL_Plact *plact;
	CL_Immo *immo;
	int row;
	int rep;
	row=LaGrille->Row;
	if(LaGrille->Objects[0][row]==NULL) return;

	switch( LaGrille->Tag)
	{
		case GEmpLT:
		Forme01Frm->NatureGEmprunt="lt";
		empLT=(CL_EmpLT*)LaGrille->Objects[0][row];
		correct=VerifEmpLT(row);
		if(correct==false) {ErreurFrm->Show();break;}
		if(empLT->Flag!='N') empLT->Flag='M'; //pour forcer à relire les modif
		DeGEmpLT(row);
		empLT->Aff(Agri->DefSim->An_0);//les calculs sont demandés pas Aff
		break;
		case GEmpCT:
		Forme01Frm->NatureGEmprunt="ct";
		correct=VerifEmpCT(row);
		if(correct==false) {ErreurFrm->Show();break;}
		empCT=(CL_EmpCT*)LaGrille->Objects[0][row];
		if(empCT->Flag!='N')empCT->Flag='M';
		DeGEmpCT(row);
		empCT->Aff(Agri->DefSim->An_0);
		break;
		case GSub:
		Forme01Frm->NatureGEmprunt="sub";
		correct=VerifSub(row);
		if(correct==false) {ErreurFrm->Show();break;}
		sub=(CL_Sub*)LaGrille->Objects[0][row];
		if(sub->Flag!='N')sub->Flag='M';
		DeGSub(row);
		sub->Aff(Agri->DefSim->An_0);
		break;
		case GPlact:
		Forme01Frm->NatureGEmprunt="plact";
		correct=VerifPlact(row);
		if(correct==false) {ErreurFrm->Show();break;}
		plact=(CL_Plact*)LaGrille->Objects[0][row];
		if(plact->Flag!='N')plact->Flag='M';
		DeGPlact(row);
		plact->Aff(Agri->DefSim->An_0,Agri->DefSim->MDeb);
		break;
		case GImmo:
		Forme01Frm->NatureGEmprunt="immo";
		correct=VerifImmo(row);
		if(correct==false) {ErreurFrm->Show();break;}
		rep=MessageBox(Handle,"Un=Oui Ensemble=Non","Afficher Un ou Ensemble",MB_YESNOCANCEL|MB_ICONQUESTION);
		if(rep==IDYES)
		{
			immo=(CL_Immo*)LaGrille->Objects[0][row];
			if(immo->Flag!='N')immo->Flag='M';
			DeGImmo(row);
			immo->Aff(Agri->DefSim->An_0);
		}
		else if(rep==IDNO)
		{
			Forme01Frm->Show();
			Forme01Frm->IniGrilleImmo(Agri,AMOR); //300406
		}
		break;
		case GStock:
		correct=VerifGrilleStockIni();
		if(correct==false) {ErreurFrm->Show();break;}
		DeGrilleStockIni(Agri->V_StockIni);
		VoirStockIni();
		break;
		default:ShowMessage("BtBnVoirClick Oubli");
	}

}
//----------------------------------------------------------------------------
//  							BtBnStockerClick
void __fastcall TAgriSaisieFrm::BoutAnnulClick(TObject *Sender)
{
	Stocker();
}
//---------------------------------------------------------------------------
bool __fastcall TAgriSaisieFrm::Stocker(void)
{
	/*
	 //260908
	 if(Agri->EstPlus10Ans==true && Agri->NoSerie!=0)
	 {
	 ShowMessage("Interdit de modifier en dehors de la première décade");
	 }
	 else
	 */
	ES->ecrireFichier();
	MazModif();
	Agri->Flag=EXISTE;
	LabelModifie->Visible=false;
	return true;
}
//---------------------------------------------------------------------------
// modif possible oui non
// Cette fonction n'est plus utilisée Provisoirement ??
// RGModifiable->Visible=false
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RGModifiableClick(TObject *Sender)
{
	if(RGModifiable->ItemIndex==0)
	{
		RGModifiable->Color=clRed;
		Grille0->EditorMode=false;
		LaGrille->EditorMode=false;
		Memo->ReadOnly=true;
	}
	else
	{
		RGModifiable->Color=clLime;
		Grille0->EditorMode=true;
		LaGrille->EditorMode=true;
		Memo->ReadOnly=false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::PossibleModifier(bool modifiable)
{
//	RGModifiable->Visible=true;
	RGModifiable->Visible=false;//
	if(modifiable==false)
	{
		RGModifiable->ItemIndex=0;
		RGModifiable->Color=clRed;
//       Grille0->EditorMode=false;
		Grille0->EditorMode=true;//!!!
		Memo->ReadOnly=true;
	}
	else
	{
		RGModifiable->ItemIndex=1;
		RGModifiable->Color=clLime;
		Grille0->EditorMode=true;
		Memo->ReadOnly=false;
	}
}
//Evite verif de form00
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	int rep;
	if (Agri==NULL) // Sinon, une fonction va tester Agri et... (sebastien)
	{
		CanClose=true;
		TVDicoFrm->Complet=true;
		return;
	}
	if(CEstBon()==true)
	{
		rep=MessageBox(Handle,L_QuitAgri.c_str(),L_Att.c_str(),MB_YESNO|MB_ICONEXCLAMATION);

		//rep=MessageBox(Handle," Je quitte cet agriculteur. Vous êtes sur ?","ATTENTION",
		//MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==IDNO)
		{
			CanClose=false;
			return;
		}
		CanClose=true;

		LBChoixFrm->Visible=false;
		LBChoixMCFrm->Visible=false;
		TVChoixFrm->Visible=false;
		TVDicoFrm->Visible=false;
		TVDicoFrm->Complet=true; // dico contient Tous les elt

		//081008
		AgriDefSimFrm->Visible=false;
		ResultatFrm->Visible=false;
		TypeAmorFrm->Visible=false;
		TypeEmpCTFrm->Visible=false;
		TypeEmpLTFrm->Visible=false;
		CommercialisationFrm->Visible=false;//Close();
		SituDepartFrm->Visible=false;
		LBCompAgriFrm->Visible=false;
		TVDicoFrm->Visible=false;
		ConversionFrm->Visible=false;
		ResGraphFrm->Visible=false;
		TresoFrm->Visible=false;
		Forme01Frm->Visible=false;
		TravGraphFrm->Visible=false;
		TravCalFrm->Visible=false;
		TroupeauFrm->Visible=false;

		MainForm->Show();
	}
	else
	CanClose=false;
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::BtBnStockerClick(TObject *Sender)
{
	CEstBon();
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::Tva1Click(TObject *Sender)
{
	SituDepartFrm->Agri=Agri;
	SituDepartFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::BtBnImpClick(TObject *Sender)
{
	//int n;
//    n=LaGrille->RowCount;
	QRGrille00Frm->LaGrille=LaGrille;
	QRGrille00Frm->NomAgri->Caption=Caption;//LabSais->Caption;
	QRGrille00Frm->TitreEtat->Caption=LabEnCours->Caption;
	QRGrille00Frm->TypeCol=TypeCol;
	QRGrille00Frm->Initialise();
	QRGrille00Frm->QR->Preview();

}
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::BtBnNotesClick(TObject *Sender)
{
	NoteAgriFrm->VientDe="AgriDefSim";
	NoteAgriFrm->Agri=AgriSaisieFrm->Agri;
	NoteAgriFrm->Caption=AgriSaisieFrm->Caption;
	NoteAgriFrm->Memo->Text=AgriSaisieFrm->Agri->Notes;

	NoteAgriFrm->Show();

}
//---------------------------------------------------------------------------
void TAgriSaisieFrm::TexteChaine(void) {

	L_Perenne = T->TrouveTexte("AgriSaisieFrm", "L_Perenne");
	L_Animaux = T->TrouveTexte("AgriSaisieFrm", "L_Animaux");
	L_Pluri = T->TrouveTexte("AgriSaisieFrm", "L_Pluri");
	L_Variable = T->TrouveTexte("AgriSaisieFrm", "L_Variable");
	L_ChOpe = T->TrouveTexte("AgriSaisieFrm", "L_ChOpe");
	L_ChStruct = T->TrouveTexte("AgriSaisieFrm", "L_ChStruct");
	L_RecDiv = T->TrouveTexte("AgriSaisieFrm", "L_RecDiv");
	L_DepDiv = T->TrouveTexte("AgriSaisieFrm", "L_DepDiv");
	L_ExtNeg = T->TrouveTexte("AgriSaisieFrm", "L_ExtNeg");
	L_ExtPos = T->TrouveTexte("AgriSaisieFrm", "L_ExtPos");
	L_RecPriv = T->TrouveTexte("AgriSaisieFrm", "L_RecPriv");
	L_DepPriv = T->TrouveTexte("AgriSaisieFrm", "L_DepPriv");
	L_EmpLT = T->TrouveTexte("AgriSaisieFrm", "L_EmpLT");
	L_EmpCT = T->TrouveTexte("AgriSaisieFrm", "L_EmpCT");
	L_Sub = T->TrouveTexte("AgriSaisieFrm", "L_Sub");
	L_Occc = T->TrouveTexte("AgriSaisieFrm", "L_Occc");
	L_Plact = T->TrouveTexte("AgriSaisieFrm", "L_Plact");
	L_EmpSom = T->TrouveTexte("AgriSaisieFrm", "L_EmpSom");
	L_Immo = T->TrouveTexte("AgriSaisieFrm", "L_Immo");
	L_Tva = T->TrouveTexte("AgriSaisieFrm", "L_Tva");
	L_Petit = T->TrouveTexte("AgriSaisieFrm", "L_Petit");
	L_ImmoRap = T->TrouveTexte("AgriSaisieFrm", "L_ImmoRap");
	L_PolStock = T->TrouveTexte("AgriSaisieFrm", "L_PolStock");
	L_PasProd = T->TrouveTexte("AgriSaisieFrm", "L_PasProd");
	L_StockIni = T->TrouveTexte("AgriSaisieFrm", "L_StockIni");
	L_Stocks = T->TrouveTexte("AgriSaisieFrm", "L_Stocks");
	L_Creance = T->TrouveTexte("AgriSaisieFrm", "L_Creance");
	L_Dettes = T->TrouveTexte("AgriSaisieFrm", "L_Dettes");
	L_Passe = T->TrouveTexte("AgriSaisieFrm", "L_Passe");
	L_PasDon = T->TrouveTexte("AgriSaisieFrm", "L_PasDon");
	L_DonPasse = T->TrouveTexte("AgriSaisieFrm", "L_DonPasse");
	L_ResDe = T->TrouveTexte("AgriSaisieFrm", "L_ResDe");
	L_Att = T->TrouveTexte("AgriSaisieFrm", "L_Att");
	L_DonNonModif = T->TrouveTexte("AgriSaisieFrm", "L_DonNonModif");
	L_LiNonSup = T->TrouveTexte("AgriSaisieFrm", "L_LiNonSup");
	L_QuitAgri = T->TrouveTexte("AgriSaisieFrm", "L_QuitAgri");

	// agrege
	L_Moy = T->TrouveTexte("AgriSaisieFrm", "L_Moy");
	L_Surface = T->TrouveTexte("AgriSaisieFrm", "L_Surface");

	//controleCell
	L_ErrDateAn = T->TrouveTexte("AgriSaisieFrm", "L_ErrDateAn");
	L_ErrEmpDur = T->TrouveTexte("AgriSaisieFrm", "L_ErrEmpDur");
	L_ErrSub = T->TrouveTexte("AgriSaisieFrm", "L_ErrSub");
	L_ErrAm = T->TrouveTexte("AgriSaisieFrm", "L_ErrAm");

	//iniG
	L_TitrePer = T->TrouveTexte("AgriSaisieFrm", "L_TitrePer");
	L_TitreViv = T->TrouveTexte("AgriSaisieFrm", "L_TitreViv");
	L_TitreEmp = T->TrouveTexte("AgriSaisieFrm", "L_TitreEmp");
	L_TitreSub = T->TrouveTexte("AgriSaisieFrm", "L_TitreSub");
	L_TitrePlact = T->TrouveTexte("AgriSaisieFrm", "L_TitrePlact");
	L_TitreOccc = T->TrouveTexte("AgriSaisieFrm", "L_TitreOccc");
	L_TitreImmo = T->TrouveTexte("AgriSaisieFrm", "L_TitreImmo");
	L_TitrePetit = T->TrouveTexte("AgriSaisieFrm", "L_TitrePetit");
	L_TitreCrDette = T->TrouveTexte("AgriSaisieFrm", "L_TitreCrDette");
	L_TitrePolStock = T->TrouveTexte("AgriSaisieFrm", "L_TitrePolStock");
	L_TitrePasse = T->TrouveTexte("AgriSaisieFrm", "L_TitrePasse");
	L_Nom = T->TrouveTexte("AgriSaisieFrm", "L_Nom");
	//Marge
	L_LesAteliers = T->TrouveTexte("AgriSaisieFrm", "L_LesAteliers");
	//PrepareEcran
	L_Dico = T->TrouveTexte("AgriSaisieFrm", "L_Dico");
	L_MotCle = T->TrouveTexte("AgriSaisieFrm", "L_MotCle");
	L_Assol = T->TrouveTexte("AgriSaisieFrm", "L_Assol");
	L_Mvt = T->TrouveTexte("AgriSaisieFrm", "L_Mvt");
	//report
	L_ErrPasImmo = T->TrouveTexte("AgriSaisieFrm", "L_ErrPasImmo");
	L_ErrRepImpo = T->TrouveTexte("AgriSaisieFrm", "L_ErrRepImpo");
	L_ErrIntCal = T->TrouveTexte("AgriSaisieFrm", "L_ErrIntCal");
	//Cestbon
	L_Modifie = T->TrouveTexte("AgriSaisieFrm", "L_Modifie");
	//Verif
	L_ErrPasNom = T->TrouveTexte("AgriSaisieFrm", "L_ErrPasNom");
	L_ErrPasSurf = T->TrouveTexte("AgriSaisieFrm", "L_ErrPasSurf");
	L_ErrPasDatePlant = T->TrouveTexte("AgriSaisieFrm", "L_ErrPasDatePlant");
	L_ErrArrach = T->TrouveTexte("AgriSaisieFrm", "L_ErrArrach");
	L_ErrDurTropL = T->TrouveTexte("AgriSaisieFrm", "L_ErrDurTropL");
	L_ErrPasMontant = T->TrouveTexte("AgriSaisieFrm", "L_ErrPasMontant");
	L_ErrPasDuree = T->TrouveTexte("AgriSaisieFrm", "L_ErrPasDuree");
	L_ErrPasDur2 = T->TrouveTexte("AgriSaisieFrm", "L_ErrPasDur2");
	L_ErrPasTaux = T->TrouveTexte("AgriSaisieFrm", "L_ErrPasTaux");
	L_ErrPasTaux2 = T->TrouveTexte("AgriSaisieFrm", "L_ErrPasTaux2");
	L_ErrDurSup50 = T->TrouveTexte("AgriSaisieFrm", "L_ErrDurSup50");
	L_ErrPasTypEmp = T->TrouveTexte("AgriSaisieFrm", "L_ErrPasTypEmp");
	L_ErrPasDateReal = T->TrouveTexte("AgriSaisieFrm", "L_ErrPasDateReal");
	L_ErrPasDateRembEmp = T->TrouveTexte("AgriSaisieFrm",
			"L_ErrPasDateRembEmp");
	L_ErrPasEPEmp = T->TrouveTexte("AgriSaisieFrm", "L_ErrPasEPEmp");
	L_ErrIntEmpCT = T->TrouveTexte("AgriSaisieFrm", "L_ErrIntEmpCT");
	L_ErrPbDate = T->TrouveTexte("AgriSaisieFrm", "L_ErrPbDate");
	L_ErrTypePlact = T->TrouveTexte("AgriSaisieFrm", "L_ErrTypePlact");
	L_ErrPasDateTerme = T->TrouveTexte("AgriSaisieFrm", "L_ErrPasDateTerme");
	L_LT = T->TrouveTexte("AgriSaisieFrm", "L_LT");
	L_ErrPasValNeuf = T->TrouveTexte("AgriSaisieFrm", "L_ErrPasValNeuf");
	L_ErrPasDateAchat = T->TrouveTexte("AgriSaisieFrm", "L_ErrPasDateAchat");
	L_ErrPasTypAmor = T->TrouveTexte("AgriSaisieFrm", "L_ErrPasTypAmor");
	L_ErrPasDurAmor = T->TrouveTexte("AgriSaisieFrm", "L_ErrPasDurAmor");
	L_ErrPasVal = T->TrouveTexte("AgriSaisieFrm", "L_ErrPasVal");
	L_ErrPasDate = T->TrouveTexte("AgriSaisieFrm", "L_ErrPasDate");
	//VersG
	L_PrixRevient = T->TrouveTexte("AgriSaisieFrm", "L_PrixRevient");
	//videTout
	L_JeffToutQ = T->TrouveTexte("AgriSaisieFrm", "L_JeffToutQ");
	//voir
	L_Vente = T->TrouveTexte("AgriSaisieFrm", "L_Vente");
	L_EvolStock = T->TrouveTexte("AgriSaisieFrm", "L_EvolStock");
	//..100206
	L_DetteLT = T->TrouveTexte("AgriSaisieFrm", "L_DetteLT");
	L_RembCapLT = T->TrouveTexte("AgriSaisieFrm", "L_RembCapLT");
	L_IntLT = T->TrouveTexte("AgriSaisieFrm", "L_IntLT");
	L_NouvLT = T->TrouveTexte("AgriSaisieFrm", "L_NouvLT");

	L_DetteCT = T->TrouveTexte("AgriSaisieFrm", "L_DetteCT");
	L_RembCapCT = T->TrouveTexte("AgriSaisieFrm", "L_RembCapCT");
	L_IntCT = T->TrouveTexte("AgriSaisieFrm", "L_IntCT");
	L_NouvCT = T->TrouveTexte("AgriSaisieFrm", "L_NouvCT");
	L_V_Resid = T->TrouveTexte("AgriSaisieFrm", "L_V_Resid");
	L_Amor = T->TrouveTexte("AgriSaisieFrm", "L_Amor");
	L_Achat = T->TrouveTexte("AgriSaisieFrm", "L_Achat");
	L_Revente = T->TrouveTexte("AgriSaisieFrm", "L_Revente");
	L_PlusVal = T->TrouveTexte("AgriSaisieFrm", "L_PlusVal");
	L_MoinsVal = T->TrouveTexte("AgriSaisieFrm", "L_MoinsVal");
	L_ProdImmo = T->TrouveTexte("AgriSaisieFrm", "L_ProdImmo");

	L_EMP = T->TrouveTexte("AgriSaisieFrm", "L_EMP");
	L_Montant = T->TrouveTexte("AgriSaisieFrm", "L_Montant");
	L_Dur1 = T->TrouveTexte("AgriSaisieFrm", "L_Dur1");
	L_Taux1 = T->TrouveTexte("AgriSaisieFrm", "L_Taux1");
	L_Dur2 = T->TrouveTexte("AgriSaisieFrm", "L_Dur2");
	L_Taux2 = T->TrouveTexte("AgriSaisieFrm", "L_Taux2");
	L_Type = T->TrouveTexte("AgriSaisieFrm", "L_Type");
	L_Real = T->TrouveTexte("AgriSaisieFrm", "L_Real");
	L_Remb = T->TrouveTexte("AgriSaisieFrm", "L_Remb");
	L_EouP = T->TrouveTexte("AgriSaisieFrm", "L_EouP");

}
//--------------------------------------------
void TAgriSaisieFrm::IniCaption(void) {
	PRODUITS->Caption = LC_PRODUITS;
	AgriSaisieFrm->Caption = LC_AgriSaisieFrm;
	Animaux->Caption = LC_Animaux;
	Assolement->Caption = T->LC_Assolement;
	CHARGES1->Caption = T->LC_LabPCharge;
	Commercialisation1->Caption = T->LC_Commercialisation1;
	CourtTerme->Caption = LC_CourtTerme;
	Creances1->Caption = LC_Creances1;
	Definition->Caption = LC_Definition;
	ChargesDivers->Caption = T->LC_ChargesDivers;
	Depenses->Caption = T->LC_ChargesDivers;
	Dettes1->Caption = LC_Dettes1;
	BtDico->Caption = T->LC_BtDico;
	DIVERS1->Caption = T->LC_DIVERS1;
	BtDonnees->Caption = LC_BtDonnees;
	CreancesDettes1->Caption = T->LC_CreancesDettes1;
	EXTERNALITES1->Caption = LC_EXTERNALITES1;
	FINANCES->Caption = LC_FINANCES;
	InvSommaire->Caption = LC_InvSommaire;
	Sommaire->Caption = LC_InvSommaire;
	IMMOBILISATION->Caption = LC_IMMOBILISATION;
	Inventaire->Caption = LC_Inventaire;
	LabSais->Caption = T->LC_LabSais;
	LongTerme->Caption = LC_LongTerme;
	RGModifiable->Caption = T->LC_RGModifiable;
	BtMotCle->Caption = T->LC_BtMotCle;
	Negatives->Caption = LC_Negatives;
	Occc->Caption = T->LC_Occc;
	ChargesOpe1->Caption = LC_ChargesOpe1;
	Passe->Caption = LC_Passe;
	Perennes->Caption = LC_Perennes;
	PetitMatriel->Caption = T->LC_PetitMatriel;
	Placement->Caption = LC_Placement;
	Vivriers->Caption = LC_Vivriers;
	PolitiqueStockage1->Caption = LC_PolitiqueStockage1;
	Positives->Caption = LC_Positives;
	PRIVE->Caption = LC_PRIVE;
	PRODUCTIONS->Caption = T->LC_PRODUCTIONS;
	Produits1->Caption = T->LC_Produits1;
	Recettes->Caption = T->LC_Produits1;
	RESULTATS->Caption = T->LC_RESULTATS;
	S1->Caption = T->LC_S1;
	StockInitial->Caption = LC_StockInitial;
	Structure1->Caption = T->LC_Structure1;
	Subvention->Caption = LC_Subvention;
	Tva1->Caption = LC_Tva1;
	Tresorerie->Caption = T->LC_Tresorerie;
	InventaireAnimaux->Caption = LC_InventaireAnimaux;
	VARIABLES->Caption = T->LC_VARIABLES;
	BtBnVoir->Caption = LC_BtBnVoir;

	BtClasser->Caption = T->LC_BtClasser; //090206
	ChBRepTout->Caption = T->LC_ChBRepTout;
	BoutFermer->Caption = T->TrouveCaption("AgriSaisie", "LC_QuitterAgri");
}
//--------------------------------------------
void TAgriSaisieFrm::TexteCaption(void) {
	LC_PRODUITS = T->TrouveCaption("AgriSaisie", "LC_PRODUITS");
	LC_AgriSaisieFrm = T->TrouveCaption("AgriSaisie", "LC_AgriSaisieFrm");
	LC_Animaux = T->TrouveCaption("AgriSaisie", "LC_Animaux");
	LC_Assolement = T->TrouveCaption("CL_Trad", "LC_Assolement");
	LC_LabPCharge = T->TrouveCaption("CL_Trad", "LC_LabPCharge");
	LC_Commercialisation1 = T->TrouveCaption("CL_Trad",
			"LC_Commercialisation1");
	LC_CourtTerme = T->TrouveCaption("AgriSaisie", "LC_CourtTerme");
	LC_Creances1 = T->TrouveCaption("AgriSaisie", "LC_Creances1");
	LC_Definition = T->TrouveCaption("AgriSaisie", "LC_Definition");
	LC_ChargesDivers = T->TrouveCaption("CL_Trad", "LC_ChargesDivers");
	LC_Dettes1 = T->TrouveCaption("AgriSaisie", "LC_Dettes1");
	LC_BtDico = T->TrouveCaption("CL_Trad", "LC_BtDico");
	LC_DIVERS1 = T->TrouveCaption("CL_Trad", "LC_DIVERS1");
	LC_BtDonnees = T->TrouveCaption("AgriSaisie", "LC_BtDonnees");
	LC_CreancesDettes1 = T->TrouveCaption("CL_Trad", "LC_CreancesDettes1");
	LC_EXTERNALITES1 = T->TrouveCaption("AgriSaisie", "LC_EXTERNALITES1");
	LC_FINANCES = T->TrouveCaption("AgriSaisie", "LC_FINANCES");
	LC_InvSommaire = T->TrouveCaption("Agrisaisie", "LC_InvSommaire");
	LC_IMMOBILISATION = T->TrouveCaption("AgriSaisie", "LC_IMMOBILISATION");
	LC_Inventaire = T->TrouveCaption("AgriSaisie", "LC_Inventaire");
	LC_LabSais = T->TrouveCaption("CL_Trad", "LC_LabSais");
	LC_LongTerme = T->TrouveCaption("AgriSaisie", "LC_LongTerme");
	LC_RGModifiable = T->TrouveCaption("CL_Trad", "LC_RGModifiable");
	LC_BtMotCle = T->TrouveCaption("CL_Trad", "LC_BtMotCle");
	LC_Negatives = T->TrouveCaption("AgriSaisie", "LC_Negatives");
	LC_Occc = T->TrouveCaption("CL_Trad", "LC_Occc");
	LC_ChargesOpe1 = T->TrouveCaption("AgriSaisie", "LC_ChargesOpe1");
	LC_Passe = T->TrouveCaption("AgriSaisie", "LC_Passe");
	LC_Perennes = T->TrouveCaption("AgriSaisie", "LC_Perennes");
	LC_PetitMatriel = T->TrouveCaption("CL_Trad", "LC_PetitMatriel");
	LC_Placement = T->TrouveCaption("AgriSaisie", "LC_Placement");
	LC_Vivriers = T->TrouveCaption("AgriSaisie", "LC_Vivriers");
	LC_PolitiqueStockage1 = T->TrouveCaption("AgriSaisie",
			"LC_PolitiqueStockage1");
	LC_Positives = T->TrouveCaption("AgriSaisie", "LC_Positives");
	LC_PRIVE = T->TrouveCaption("AgriSaisie", "LC_PRIVE");
	LC_PRODUCTIONS = T->TrouveCaption("CL_Trad", "LC_PRODUCTIONS");
	LC_Produits1 = T->TrouveCaption("CL_Trad", "LC_Produits1");
	LC_RESULTATS = T->TrouveCaption("CL_Trad", "LC_RESULTATS");
	LC_S1 = T->TrouveCaption("CL_Trad", "LC_S1");
	LC_StockInitial = T->TrouveCaption("AgriSaisie", "LC_StockInitial");
	LC_Structure1 = T->TrouveCaption("CL_Trad", "LC_Structure1");
	LC_Subvention = T->TrouveCaption("AgriSaisie", "LC_Subvention");
	LC_Tva1 = T->TrouveCaption("AgriSaisie", "LC_Tva1");
	LC_Tresorerie = T->TrouveCaption("CL_Trad", "LC_Tresorerie");
	LC_InventaireAnimaux = T->TrouveCaption("AgriSaisie",
			"LC_InventaireAnimaux");
	LC_VARIABLES = T->TrouveCaption("CL_Trad", "LC_VARIABLES");
	LC_BtBnVoir = T->TrouveCaption("AgriSaisie", "LC_BtBnVoir");
	LC_QuitterAgri = T->TrouveCaption("AgriSaisie", "LC_QuitterAgri");

	IniCaption();

}

//---------------------------------------------------------------------------

void __fastcall TAgriSaisieFrm::Grille0Click(TObject *Sender)
{
	if(Grille0->Tag==GImmo && Grille0->Col==7)BtDonnees->Enabled=true; //120506
	else if(Grille0->Tag==GPolStock && Grille0->Col==1)BtDonnees->Enabled=true;//240506
	else if(Grille0->Col==2) BtDonnees->Enabled=true;
	else if(Grille0->Tag==GEmpLT)BtDonnees->Enabled=true;//140407
	else if(Grille0->Tag==GImmo)BtDonnees->Enabled=true;//140407
	else BtDonnees->Enabled=false;
//AnsiString Value;
	if(DerniereCell()==false)return;

	RepereCellEC(LaGrille->Col,LaGrille->Row);// ColEC RowEC ValueAvant
	SaisirCell(LaGrille->Col,LaGrille->Row);//il y a fonction de saisie
											//pour cas particulier

	if (PClasst->Visible)//seult si bouton classer actif
	MarquerLigne(LaGrille->Row);
}
//---------------------------------------------------------------------------

void __fastcall TAgriSaisieFrm::BtBnVersExcelClick(TObject *Sender)
{
//
//    OutilFrm->EcrireClipBoard(LaGrille,0,0,LaGrille->ColCount,LaGrille->RowCount);
	OutilFrm->VersExcel(LaGrille,0,0,LaGrille->ColCount,LaGrille->RowCount);
}
//---------------------------------------------------------------------------

void __fastcall TAgriSaisieFrm::BtBnDExcelClick(TObject *Sender)
{
	/*
	 if(OutilFrm->ClipboardFormatOK(CF_TEXT)==false) return;
	 OutilFrm->LireClipBoard(LaGrille,0,0);
	 LabelModifie->Visible==true;
	 */
	OutilFrm->DExcel(LaGrille,0,0,LaGrille->ColCount,LaGrille->RowCount);
	LabelModifie->Visible==true;

}
//---------------------------------------------------------------------------

bool __fastcall TAgriSaisieFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=900;
	AideFrm->AfficherAide(MainForm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

