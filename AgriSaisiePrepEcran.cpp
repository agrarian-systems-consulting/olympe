//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "AgriSaisieEnum.h"

#include "TVChoix.h"
#include "TVDico.h"
#include "LBChoix.h"
#include "LBChoixMC.h"
#include "LBChoixTva.h"
#include "MvtAni.h"
#include "CL_Trad.h"

#include "TypeEmpLT.h"
#include "TypeAmor.h"
#include "TypeEmpCT.h"
#include "TypePlact.h"

#include "AgriSaisie.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//  Efface toutes TVChoix et LBChoix
extern CL_Trad *T;
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::PrepareEcran(void)
{
	LabelModifie->Visible=false;

//    PossibleModifier(false);     //pour Montpellier
	PossibleModifier(true);

	TVChoixFrm->Visible= false;
	TVDicoFrm->Visible= false;
	LBChoixFrm->Visible= false;
	LBChoixMCFrm->Visible= false;
	LBChoixTvaFrm->Visible= false;

	TypeEmpLTFrm->Visible=false;//130407
	TypeAmorFrm->Visible=false;//130407
	TypeEmpCTFrm->Visible=false;//130407
	TypePlactFrm->Visible=false;//130407

	BtDico->Caption=L_Dico;
	//BtDico->Caption="Dico";

	if(PClasst->Visible==true)
	{
		BtBnFermClasstClick(this);
		PClasst->Visible=false;
	}

	GrilleVisible();
	MemoVisible();
	BoutonVisible();
	BoutonIntitule();
	ReportPossible();
	AjoutRowPossible();
	CelluleModifiable();
	Titre();
	//RGModifiable
	// RadioGroupBox qui permet ou non de modifier
	// je pense qu'il ne sert plus a rien ???
	switch(LaGrille->Tag)
	{
		case GResul:
		case GClose:
//        case GNotes:
		LabSais->Caption="";
		RGModifiable->Visible=false;
		break;
		default:
//		    RGModifiable->Visible=true;
		RGModifiable->Visible=false;//pour Montpellier
	}
}
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::GrilleVisible(void)
{
	//grille Visible
	switch(LaGrille->Tag)
	{
		case GNotes:
		case GResul:
		LaGrille->Visible=false;
		break;
		default:
		LaGrille->Visible=true;
	}
}
//------------------------------------------------------------------------------
// pour saisie et affichage des formules
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::MemoVisible(void)
{
	//memo->Visible
	switch(LaGrille->Tag)
	{
		case GProduit:
		case GCharge:
		case GChStruct:
		case GRecDiv:
		case GDepDiv:
		case GRecFam:
		case GDepFam:
		case GExtNeg:
		case GExtPos:
		Memo->Height=HauteurMemo;
		Memo->Visible=true;
		break;
		case GNotes:
		Memo->Height=HauteurMemo*5;
		Memo->Visible=true;
		break;
		default:Memo->Visible=false;
	}
}
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::BoutonVisible(void)
{
	//boutons visible O/N
	BtDonnees->Visible= false;
	BtDico->Visible= false;
	BtMotCle->Visible= false;
	switch(LaGrille->Tag)
	{
		case GAssol:
		case GPerenne:
		case GVivrier:
		BtDonnees->Visible= true;
		BtDico->Visible= true; //pour surface
		break;
		case GVariable:
		case GAni:
		case GBestiaux:
		BtDonnees->Visible= true;
		break;
		case GProduit:
		case GCharge:
		case GChStruct:
		case GRecDiv:
		case GDepDiv:
		case GRecFam:
		case GDepFam:
		case GExtNeg:
		case GExtPos:
		BtDonnees->Visible= true;
		BtDico->Visible= true;
		BtMotCle->Visible= true;
		break;
//        case GEmpLT:            //130407
//            BtDonnees->Visible=  true;
//            break;

		case GResul:
		case GClose:
		case GNotes:
		//case GEmpLT:
		case GEmpCT:
		case GSub:
		case GPlact:
		case GOccc:
		case GFinSom:
		case GInvSom:
		break;
		case GImmo:
		case GPetit:
		BtDonnees->Visible= true;
		break;
		case GCreance:
		case GDette:
		BtDonnees->Visible= true;
//            BtDico->Visible=     true;
//            BtMotCle->Visible=   true;
		break;
		case GStock:
		case GPolStock://200802
		BtDonnees->Visible= true;
		break;
//        default:
	}
	//BtSup Visible
	switch(LaGrille->Tag)
	{
		case GOccc:
		case GFinSom:
		case GInvSom:
//        case GPolStock:  //200802
		BtBnSup->Enabled=false;
		break;
		default:
		BtBnSup->Enabled=true;
	}
	//BtBnVoir  Visible
	// amortissement, echeancier d'emprunt
	switch(LaGrille->Tag)
	{
		case GEmpLT:
		case GEmpCT:
		case GSub:
		case GPlact:
		case GImmo:
		case GStock:
		BtBnVoir->Visible=true;
		break;
		default:
		BtBnVoir->Visible=false;
	}
	//BtBnClasser  Visible
	switch(LaGrille->Tag)
	{
		case GOccc:
		case GFinSom:
		case GPetit:
		case GInvSom:
		case GCreance:
//        case GDette:
		case GPolStock://200802
		BtClasser->Visible=false;
		break;
		default:
		BtClasser->Visible=true;
	}
}
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::BoutonIntitule(void)
{
	//intitule boutons gauche=colonne de gauche
	switch(LaGrille->Tag)
	{
		case GAssol: BtDonnees->Caption=T->L_Culture;break;
		case GPerenne: BtDonnees->Caption=L_Perenne;break;
		case GAni: BtDonnees->Caption=L_Animaux;break;
		case GVivrier: BtDonnees->Caption=L_Pluri;break;
		case GBestiaux:BtDonnees->Caption=L_Animaux;break;
		case GVariable:BtDonnees->Caption=L_Variable;break; //?? réglé dans VariablesClick
		case GProduit: BtDonnees->Caption=T->L_Produit;break;
		case GCharge: BtDonnees->Caption=T->L_Charge;break;
		case GChStruct:BtDonnees->Caption=L_ChStruct;break;
		case GRecDiv: BtDonnees->Caption=L_RecDiv;break;
		case GDepDiv: BtDonnees->Caption=L_DepDiv;break;
		case GRecFam: BtDonnees->Caption=L_RecPriv;break;
		case GDepFam: BtDonnees->Caption=L_DepPriv;break;
		case GExtNeg: BtDonnees->Caption=L_ExtNeg;break;
		case GExtPos: BtDonnees->Caption=L_ExtPos;break;
		case GImmo:
		case GPetit: BtDonnees->Caption=L_Tva;break;
		case GCreance: BtDonnees->Caption=T->L_Produit;break;
		case GDette: BtDonnees->Caption=T->L_Charge;break;
		case GPolStock:
		case GStock: BtDonnees->Caption=T->L_Produit;break;
		case GEmpLT: BtDonnees->Caption="Type Emprunt";break;//140407
		//case GNotes:   BtDonnees->Caption=
		//case GResul:   BtDonnees->Caption=
		//case GClose:   BtDonnees->Caption=
	}
	//intitule boutons MotCle
	switch(LaGrille->Tag)
	{
		case GCreance:
		case GDette: BtMotCle->Caption=L_Tva;break;
		default: BtMotCle->Caption=L_MotCle;break;
	}
	//intitule boutons Dico
	switch(LaGrille->Tag)
	{
		case GAssol:
		case GPerenne:
		case GVivrier: BtDico->Caption=L_Surface;break;
//                       BtDico->Visible=     true; //pour surface
//                       break;
		default: BtDico->Caption="Dico";break;
	}
}
/*
 //------------------------------------------------------------------------------
 void __fastcall TAgriSaisieFrm::BoutonIntitule(void)
 {
 //intitule boutons gauche=colonne de gauche
 switch(LaGrille->Tag)
 {
 case GAssol:   BtDonnees->Caption="Cultures";break;
 case GPerenne: BtDonnees->Caption="Pérennes";break;
 case GAni:     BtDonnees->Caption="Animaux";break;
 case GVivrier: BtDonnees->Caption="PluriAnnuelles";break;
 case GBestiaux:BtDonnees->Caption="Animaux";break;
 case GVariable:BtDonnees->Caption="Variables";break;//?? réglé dans VariablesClick
 case GProduit: BtDonnees->Caption="Produits";break;
 case GCharge:  BtDonnees->Caption="Charges";break;
 case GChStruct:BtDonnees->Caption="Ch Struct";break;
 case GRecDiv:  BtDonnees->Caption="Rec Diverses";break;
 case GDepDiv:  BtDonnees->Caption="Dep Diverses";break;
 case GRecFam:  BtDonnees->Caption="Rec Privée";break;
 case GDepFam:  BtDonnees->Caption="Dep Privée";break;
 case GExtNeg:  BtDonnees->Caption="Ext Neg";break;
 case GExtPos:  BtDonnees->Caption="Ext Pos";break;
 case GImmo:
 case GPetit:   BtDonnees->Caption="TVA";break;
 case GCreance: BtDonnees->Caption="Produits";break;
 case GDette:   BtDonnees->Caption="Charges";break;
 case GPolStock:
 case GStock:   BtDonnees->Caption="Produits";break;
 //case GEmpLT:   BtDonnees->Caption=
 //case GNotes:   BtDonnees->Caption=
 //case GResul:   BtDonnees->Caption=
 //case GClose:   BtDonnees->Caption=
 }
 //intitule boutons MotCle
 switch(LaGrille->Tag)
 {
 case GCreance:
 case GDette:   BtMotCle->Caption="Tva";break;
 default:       BtMotCle->Caption="Mot Cle";break;
 }
 //intitule boutons Dico
 switch(LaGrille->Tag)
 {
 case GAssol:
 case GPerenne:
 case GVivrier: BtDico->Caption="Surface";break;
 //                       BtDico->Visible=     true; //pour surface
 //                       break;
 default:       BtDico->Caption="Dico";break;
 }
 }
 */
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::ReportPossible(void)
{
	//report droit
	switch(LaGrille->Tag)
	{
		case GPerenne:
		case GVivrier:
		case GNotes:
		case GResul:
		case GClose:
		case GEmpCT:
		case GSub:
		case GPlact:
		case GOccc:
		case GImmo:
		case GPetit:
		case GPolStock:
		case GCreance:
		case GDette:
		BtReportDroit->Enabled=false;
		break;
		default:BtReportDroit->Enabled=true;
	}

	//BtReportBas
	//BtRecopBas
	switch(LaGrille->Tag)
	{
		case GAssol:
		case GAni:
		case GPerenne: //081206
		case GVivrier:
		case GEmpLT:
		case GEmpCT:
		case GSub:
		case GPlact:
		case GOccc:
		case GImmo:
		case GPetit:
		case GCreance:
		case GDette:
		case GPolStock:
		case GPasse:
		BtReportBas->Enabled=true;
		BtRecopBas->Enabled=true;
		break;
		case GStock:
		BtReportBas->Enabled=true;
		break;
		default: BtReportBas->Enabled=false;
		BtRecopBas->Enabled=false;
	}
	//report droit  Tout
	switch(LaGrille->Tag)
	{
		case GPerenne:
		case GVivrier:
		case GNotes:
		case GResul:
		case GClose:
		case GEmpCT:
		case GSub:
		case GPlact:
		case GOccc:
		case GImmo:
		case GPetit:
		case GPolStock:
		case GCreance:
		case GDette:
		BtRepToutDroit->Enabled=false;
		break;
		default:BtRepToutDroit->Enabled=true;
	}

}
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::AjoutRowPossible(void)
{
	//AjouterRow
	switch(LaGrille->Tag)
	{
		case GOccc:
		case GPetit:
		case GFinSom:
		case GInvSom:
		case GPasse:
		//case GPolStock:
		AjoutRow=false;break;
		default: AjoutRow=true;
	}
}
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CelluleModifiable(void)
{
	//Cellule modifiable
	switch(LaGrille->Tag)
	{
		case GEmpLT:
		case GEmpCT:
		case GSub:
		case GPlact:
		case GImmo:
		case GPetit:
		case GInvSom:
		case GCreance:
		case GDette:
		case GStock:
		case GPolStock:
		case GPasse:
		CellModifiable(true);break;

		default: CellModifiable(false);break;
	}
}

//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::Titre(void)
{
	switch(LaGrille->Tag)
	{
		case GResul:
		case GClose: LabEnCours->Caption="";break;
		case GAssol: LabEnCours->Caption=L_Assol;break;
		case GPerenne: LabEnCours->Caption=L_Perenne;break;
		case GAni: LabEnCours->Caption=L_Animaux;break;
		case GVivrier: LabEnCours->Caption=L_Pluri;break;
		case GBestiaux: LabEnCours->Caption=L_Mvt;break;
		case GVariable:LabEnCours->Caption=L_Variable;break; //?? réglé dans VariablesClick
		case GProduit: LabEnCours->Caption=T->L_Produit;break;
		case GCharge: LabEnCours->Caption=L_ChOpe;break;
		case GChStruct:LabEnCours->Caption=L_ChStruct;break;
		case GRecDiv: LabEnCours->Caption=L_RecDiv;break;
		case GDepDiv: LabEnCours->Caption=L_DepDiv;break;
		case GRecFam: LabEnCours->Caption=L_RecPriv;break;
		case GDepFam: LabEnCours->Caption=L_DepPriv;break;
		case GExtNeg: LabEnCours->Caption=L_ExtNeg;break;
		case GExtPos: LabEnCours->Caption=L_ExtPos;break;

		case GImmo: LabEnCours->Caption=L_Immo;break;
		case GPetit: LabEnCours->Caption=L_Petit;break;
		case GInvSom: LabEnCours->Caption=L_ImmoRap;break;

		case GEmpLT: LabEnCours->Caption=L_EmpLT;break;
		case GEmpCT: LabEnCours->Caption=L_EmpCT;break;
		case GOccc: LabEnCours->Caption=L_Occc;break;
		case GSub: LabEnCours->Caption=L_Sub;break;
		case GFinSom: LabEnCours->Caption=L_EmpSom;break;
		case GPlact: LabEnCours->Caption=L_Plact;break;

		case GCreance: LabEnCours->Caption=L_Creance;break;
		case GDette: LabEnCours->Caption=L_Dettes;break;
		case GStock: LabEnCours->Caption=L_Stocks;break;
		case GPolStock:LabEnCours->Caption=L_PolStock;break;
		case GPasse: LabEnCours->Caption=L_Passe;break;
		default:ShowMessage("Oubli Agrisaisie PrepEcran Titre");break;
	}
}
/*
 //------------------------------------------------------------------------------
 void __fastcall TAgriSaisieFrm::Titre(void)
 {
 switch(LaGrille->Tag)
 {
 case GResul:
 case GClose:   LabEnCours->Caption="";break;
 case GAssol:   LabEnCours->Caption="ASSOLEMENT";break;
 case GPerenne: LabEnCours->Caption="PERENNES";break;
 case GAni:     LabEnCours->Caption="ANIMAUX";break;
 case GVivrier: LabEnCours->Caption="PLURIANNUELLES";break;
 case GBestiaux:  LabEnCours->Caption="MOUVEMENT DES ANIMAUX";break;
 case GVariable:LabEnCours->Caption="VARIABLES";break;//?? réglé dans VariablesClick
 case GProduit: LabEnCours->Caption="PRODUITS";break;
 case GCharge:  LabEnCours->Caption="CHARGES OPE";break;
 case GChStruct:LabEnCours->Caption="CHARGES STRUCT";break;
 case GRecDiv:  LabEnCours->Caption="REC DIVERSES";break;
 case GDepDiv:  LabEnCours->Caption="DEP DIVERSES";break;
 case GRecFam:  LabEnCours->Caption="REC PRIVEES";break;
 case GDepFam:  LabEnCours->Caption="DEP PRIVEES";break;
 case GExtNeg:  LabEnCours->Caption="EXT NEG";break;
 case GExtPos:  LabEnCours->Caption="EXT POS";break;

 case GImmo:    LabEnCours->Caption="IMMOBILISATIONS";break;
 case GPetit:   LabEnCours->Caption="PETIT MATERIEL";break;
 case GInvSom:  LabEnCours->Caption="IMMOBILISATIONS GLOBALES";break;

 case GEmpLT:   LabEnCours->Caption="EMPRUNTS LT";break;
 case GEmpCT:   LabEnCours->Caption="EMPRUNTS CT";break;
 case GOccc:    LabEnCours->Caption="OUVERTURE DE CREDIT";break;
 case GSub:     LabEnCours->Caption="SUBVENTION";break;
 case GFinSom:  LabEnCours->Caption="EMPRUNTS GLOBAL";break;
 case GPlact:   LabEnCours->Caption="PLACEMENTS";break;

 case GCreance: LabEnCours->Caption="CREANCES";break;
 case GDette:   LabEnCours->Caption="DETTES";break;
 case GStock:   LabEnCours->Caption="STOCKS";break;
 case GPolStock:LabEnCours->Caption="POLITIQUE DE STOCKAGE";break;
 case GPasse:   LabEnCours->Caption="Données du Passé nécessaires";break;
 default:ShowMessage("Oubli Agrisaisie PrepEcran Titre");break;
 }
 }

 */

//--------------------------------------------------------------------------------
/*

 L_Dico=        "Dico";
 L_MotCle=      "Mot Cle";
 L_Assol=       "Assolement";
 L_Mvt=         "Mouvement des Animaux";

 */
