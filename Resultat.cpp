//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <values.h>

#pragma hdrstop
#include "olympedec.h"
#include "olympe.hse"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"
#include "Forme0.h"
#include "Brouillon.h"
#include "Compilateur.h"
#include "Tableur.h"
#include "DefEtatSortie.h"
#include "TVDico.h"
#include "TVChoixEtat.h"
#include "TVChoixComp.h"
#include "TVChoixMarge.h"

#include "ResGraph.h"

#include "AgriSaisie.h"
#include "Assol.h"
#include "LesStocks.h"
#include "Conversion.h"
#include "LBCompAgri.h"
#include "LBMarge.h"
#include "GereEtat.h"
#include "QuelExcelCSV.h"
#include "Erreur.h"

#include "SortieEcran.h"

#include "QRSortieVal.h"
#include "QRSortieQuant.h"
#include "TravCal.h"
#include "CL_Trad.h"
#include "SortieLD.h"
#include "Aide.h"
#include "RacDef.h"

#include "Resultat.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "PERFGRAP"
#pragma resource "*.dfm"
TResultatFrm *ResultatFrm;

extern CL_Excel *EX;
extern CL_ES *ES;
extern CL_Trad *T;
extern CL_Compil *Compil;
//---------------------------------------------------------------------------
__fastcall TResultatFrm::TResultatFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::FormActivate(TObject *Sender)
{
	float *taux;
	int i;
	CL_Agriculteur *agri;
	static bool debut=true; //040512
// AgriSaisie appelle Resultat avec     ResultatFrm->Agri=Agri;
// Origine =0 défini par l'appel de AgriSaisie
//                                de GereEnsembla
//         =1  défini ici dans présenterResultat
//         =2  cf Conversion

	//FormActivate doit ? etre appelé à l'ouverture du programme et Agri n'est pas défini ????
	//si Global=ENSEMBLE CalculResultatEnsemble s'est chargé de definir Agri
	if(Agri==NULL)
	return;

	//   on vient de AgriSaisie
	//       ou   de GereEnsemble
	if (Origine==0 )
	{
		//Monnaie
		if(Global==AGRI||Global==MOYENNE) EdMonnaie->Text=SysMonnaie->UTrans;
		else EdMonnaie->Text=SysMonnaie->UGlobal;
		AgriOrigine=Agri;
		// si conversion de Monnaie on travaille avec Converti
		// nécessaire de revenir à l'AgriOrigine en fin
		//Pb ensemble
		SysMonnaieOrigine=SysMonnaie;

		CreeDico();

		if(Global!=ENSEMBLE)
		{
			//prépare eléments pour comparaison
			Forme0Frm->CreeTVEtat(TVChoixCompFrm->TV,V_CatSerieComp,V_SerieComp);
			//Forme0Frm->CreeLBToutAgri(LBCompAgriFrm->ChLB);  //040512
			if (debut==true)
			{
				debut=false; //040512
				Forme0Frm->CreeLBToutAgri(LBCompAgriFrm->ChLB);
				LBCompAgriFrm->BtBnTousClick(this);
				/*
				 for(i=0;i<LBCompAgriFrm->ChLB->Items->Count;i++)
				 {

				 agri=(CL_Agriculteur*)LBCompAgriFrm->ChLB->Items->Objects[i];
				 LBCompAgriFrm->ChLB->Checked[i]=true;//160808


				 }
				 */
			}
		}
		TVDicoFrm->Origine=RESULTAT; //meme effet que SERIECOMP;
		//si Global=ENSEMBLE  CalculResultatEnsemble s'est chargé du travail
		if(Global!=ENSEMBLE)
		{
			//TVDicoFrm->EstInitialise=false;
			// pour eviter de calculer à chaque demande les résultats des agri
			// cf RetourDeLBCompAgri
			for(i=0;i<V_Agriculteur->Nbelt;i++)
			V_Agriculteur->Vecteur[i]->Flag='N';
			// dans les comparaisons je dois allouer
			// donc reperer dans Tlist
			// faire le ménage en sortant
			LstValeur=new TList;
			LstEltA =new TList;
		}
		// pas de comparaison sur ensemble      A Faire
		if(Global==ENSEMBLE)BtBnComparaison->Enabled=false;
		else BtBnComparaison->Enabled=true;
		return;
	}

	else if (Origine==1)
	{
		ProgressBar->Position=0;
		return;
	}

	/// voir conversion.cpp
	else if (Origine==2)
	{
		Origine=1;
		if(AConvertir==true)
		{
			if(Conversion==NULL) //prudence ne sert à rien
			{
				ShowMessage("Taux de conversion NON Défini");
				return;
			}
			if(Global==AGRI||Global==MOYENNE) EdMonnaie->Text=Conversion->Sortie->UTrans;
			else EdMonnaie->Text=Conversion->Sortie->UGlobal;
			// on ne rentre jamais directement ici
			// donc on connait Agri
			if(Converti!=NULL)
			delete Converti;

			Converti=new CL_Agriculteur(Agri);
			Converti->Resultat=new CL_AgriRes(Agri->Resultat);
			taux=Conversion->TauxConvFrancVersEuro;

			AgriOrigine=Agri;
			Agri=Converti;
			AgriSaisieFrm->Convertir(Converti->Resultat,taux);
			for(int an=0;an<N_X;an++)
			{
				AgriSaisieFrm->CalculTreso(Converti,an); //par simplification je calcule tout
				AgriSaisieFrm->FaireCompta(Converti->Resultat,an);//par simplification je calcule tout
			}
			SysMonnaieOrigine=SysMonnaie;
			SysMonnaie=Conversion->Sortie;
//			AgriSaisieFrm->FaireCompta(Agri->Resultat);
//			AgriSaisieFrm->FaireCompta(Converti->Resultat);
//		    Converti->Resultat->FaireCompta(Agri->Resultat); //300603

//            AgriSaisieFrm->ChangeUniteMonnaie(SysMonnaieOrigine,SysMonnaie);
		}
		else
		{
			Agri=AgriOrigine;
//            AgriSaisieFrm->ChangeUniteMonnaie(SysMonnaie,SysMonnaieOrigine);
			SysMonnaie=SysMonnaieOrigine;
			if(Global==AGRI||Global==MOYENNE) EdMonnaie->Text=Conversion->Base->UTrans;
			else EdMonnaie->Text=Conversion->Base->UGlobal;
		}
	}
}
//---------------------------------------------------------------------------
void TResultatFrm::CreeDico(void) {
	//creer tvDico et ne pas le recreer inutilement
	Forme0Frm->CreeTVToutElt(TVDicoFrm->TV, Agri, false);
	//les etats peuvent servir pour afficher plusieyrs elements
	AjouteEtat(TVDicoFrm->TV);
	// pour eviter de recreer TVDicoFrm->TV
	TVDicoFrm->AncAgri = Agri; //230103
	TVDicoFrm->AncTVItemCount = TVDicoFrm->TV->Items->Count;
	TVDicoFrm->AncComplet = false;
}
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::AjouteEtat(TTreeView *TV)
{

	TTreeNode *tNTout,*tNEtat,*tNCategorie;
	CL_EtatSortie *etat;
	CL_Categorie *categorie;
	CL_Elt *elt;

	tNTout=new TTreeNode(TV->Items);
	tNEtat=TV->Items->Add(tNTout,"Etats");
	for(int i=0;i<V_CatEtatSortie->Nbelt;i++)
	{
		categorie=V_CatEtatSortie->Vecteur[i];
		tNCategorie=TV->Items->AddChildObject(tNEtat,categorie->Nom,categorie);
		for(int j=0;j<V_EtatSortie->Nbelt;j++)
		{
			etat=V_EtatSortie->Vecteur[j];
			if(etat->NoCategorie==categorie->No)
			{
				elt=new CL_Elt();
				elt->NoFamille=ETAT;
				elt->Etat=etat;
				elt->No=etat->No;
				TV->Items->AddChildObject(tNCategorie,etat->Nom,elt);
			}
		}
	}
}

// Appelé par AgriSaisie
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::PresenterResultat(void)
{
	NonVisible();
	Origine=1;
}
// efface les GroupeBox
//        les TV choix des elements
//               choix des séries de comparaison
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::NonVisible(void)
{
	TVDicoFrm->Visible= false;
	TVChoixEtatFrm->Visible= false;
	GBGraph->Visible= false;
	GBComparaison->Visible= false;
}
//---------------------------------------------------------------------------
// SORTIE STANDARDS
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::BtBnStandardClick(TObject *Sender)
{
	HelpContext=1380;
	GBComparaison->Visible=false;
	GBGraph->Visible= false;
	LBCompAgriFrm->Visible=false;
	LBSortie->Visible =true;

	LBSortie->Top= 32;
	LBSortie->Left= 130;
//    GBGraph->Height=  369;
//    GBGraph->Width=   353;

}
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::LBSortieDblClick(TObject *Sender)
{
	int n;
	n=LBSortie->ItemIndex;
	Forme0Frm->CreeTVEtat(TVChoixEtatFrm->TV,V_CatEtatSortie,V_EtatSortie);
//    Forme0Frm->CreeTVMarge(TVChoixMargeFrm->TV,Agri);
	Forme0Frm->CreeLBMarge(LBMargeFrm->ChLB,Agri);
	NonVisible();
	RGPrecisionClick(this);
	AffUneSortie(n);
}
//---------------------------------------------------------------------------
void TResultatFrm::AffUneSortie(int n) //090920
		{
	switch (n) {
	case 0: //Synthese
		if (RBQR->Checked == true || RBEcran->Checked == true)
			QRSortieValFrm->Prepare(SYNTHESE, Agri);
		if (RBExcel->Checked == true)
			EX->Synthese(Agri);
		break;
	case 1: //Valeurs
		if (RBEcran->Checked == true) {
			SortieEcranFrm->Demarre();
			SortieEcranFrm->Valeur(Agri);
			SortieEcranFrm->Show();
		} else if (RBLongueDuree->Checked == true) {
			if (Agri->LstSerie) //150407  +de 10 ans
			{
				SortieLDFrm->Agri = Agri;
				SortieLDFrm->DimGrille(VALEUR);
				SortieLDFrm->Aff(VALEUR);
				SortieLDFrm->Show();
			}
		} else if (RBExcel->Checked == true)
			EX->Valeur(Agri);
		else
			QRSortieValFrm->Prepare(VALEUR, Agri);

		break;

	case 2: //grands postes
		if (RBEcran->Checked == true) {
			SortieEcranFrm->Demarre();
			SortieEcranFrm->Valeur(Agri);
			SortieEcranFrm->Show();
		}
		if (RBQR->Checked == true)
			QRSortieValFrm->Prepare(TRESO, Agri);
		if (RBExcel->Checked == true)
			EX->GrandsPostes(Agri); //110905
		break;

	case 3: //Quantités
		if (RBExcel->Checked == true)
			EX->Quantite(Agri);
		else if (RBLongueDuree->Checked == true) {
			if (Agri->LstSerie) //150407  +de 10 ans
			{
				SortieLDFrm->Agri = Agri;
				SortieLDFrm->DimGrille(QUANTITE);
				SortieLDFrm->Aff(QUANTITE);
				SortieLDFrm->Show();
			}
		} else
			QRSortieQuantFrm->Prepare(QUANTITE, Agri);
		break;

	case 4: //ceg
		if (RBExcel->Checked == true)
			EX->Ceg(Agri);
		else if (RBLongueDuree->Checked == true) {
			if (Agri->LstSerie) //150407  +de 10 ans
			{
				SortieLDFrm->Agri = Agri;
				SortieLDFrm->DimGrille(CEG);
				SortieLDFrm->Aff(CEG);
				SortieLDFrm->Show();
			}
		} else
			QRSortieValFrm->Prepare(CEG, Agri);
		break;

	case 5: //Bilan
		if (RBExcel->Checked == true)
			EX->Bilan(Agri);
		else
			QRSortieValFrm->Prepare(BILAN, Agri);
		break;

	case 6: //Privé
		if (RBExcel->Checked == true)
			EX->Famille(Agri);
		else
			QRSortieValFrm->Prepare(FAMILLE, Agri);
		break;

	case 7: //Marge
		//TVChoixMargeFrm->Show();
		LBMargeFrm->Show();
		break;

	case 8: //Externalites
		if (RBExcel->Checked == true)
			EX->Externalite(Agri);
		else
			QRSortieQuantFrm->Prepare(EXTER, Agri);
		break;

	case 9: //Etat sortie
		ResultatFrm->Agri = Agri; //cf TVChoixEtatFrm
		TVChoixEtatFrm->Show();
		break;

	case 10: //Finances
		if (RBExcel->Checked == true)
			EX->Finance(Agri);
		else
			QRSortieValFrm->Prepare(FINANCE, Agri);
		break;

	case 11: //Immo
		if (RBExcel->Checked == true)
			EX->Immo(Agri);
		else
			QRSortieValFrm->Prepare(IMMO, Agri);
		break;

	case 12: //Tva
		if (RBExcel->Checked == true)
			EX->Tva(Agri);
		else
			QRSortieValFrm->Prepare(TVA, Agri);
		break;

	case 13: //Assolement
		AgriSaisieFrm->Agri = Agri;
		AssolFrm->Agri = Agri;
		AssolFrm->Show();
		break;

	case 14: //Elt Comptable Pérennes
		if (RBExcel->Checked == true)
			ShowMessage("Perenne à faire");
		else
			QRSortieValFrm->Prepare(PERENNE, Agri);
		break;

	case 15: //Les Stocks
		AgriSaisieFrm->Agri = Agri;
		LesStocksFrm->Agri = Agri;
		LesStocksFrm->Show();
		break;

	case 16: //050206
		QRSortieValFrm->Prepare(EMPLT, Agri);
		break;

	case 17:
		QRSortieValFrm->Prepare(AMOR, Agri);
		break;

	}
}

//---------------------------------------------------------------------------
// COURBE
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::BtBnCourbeClick(TObject *Sender)
{
	HelpContext=1390;
	GBComparaison->Visible=false;

	LBGauche->Clear();
	LBDroit->Clear();
	GBGraph->Visible= true;

	LBCompAgriFrm->Visible=false;
	LBSortie->Visible =false;

	GBGraph->Top= 32;
	GBGraph->Left= 152;
	GBGraph->Height= 369;
	GBGraph->Width= 353;
	TVDicoFrm->Origine=RESULTAT;
	TVDicoFrm->Visible= true;

//    Forme0Frm->CreeTVEtat(TVChoixEtatFrm->TV,V_CatEtatSortie,V_EtatSortie);
//    Forme0Frm->CreeTVEtat(TVChoixCompFrm->TV,V_CatSerieComp,V_SerieComp);

//    LBSortie->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::BtAfficheClick(TObject *Sender)
{
	int n;
	ResGraphFrm->Caption=AgriEnCours->NomVC();

	n=LBGauche->Items->Count+LBDroit->Items->Count;
	if(n==0)
	{
		MessageBox(Handle,"Aucun Elément","Problème",MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	if(LBGauche->Items->Count>10)
	{
		MessageBox(Handle,"AXE GAUCHE Trop d'Eléments(MAX=10)","Problème",MB_OK|MB_ICONEXCLAMATION);
		return;
	}

	if(LBDroit->Items->Count>10)
	{
		MessageBox(Handle,"AXE DROIT Trop d'Eléments(MAX=10)","Problème",MB_OK|MB_ICONEXCLAMATION);
		return;
	}
	TVDicoFrm->Visible=false;
//	ResGraphLegendeFrm->Show();
	if(RGNatureG->ItemIndex==0)ResGraphFrm->TypeCourbeG=0;
	else ResGraphFrm->TypeCourbeG=1;
	if(RGNatureD->ItemIndex==0)ResGraphFrm->TypeCourbeD=0;
	else ResGraphFrm->TypeCourbeD=1;
	ResGraphFrm->Origine=0;
	ResGraphFrm->Nature=AGRI;
//CL_Elt *elt;    //110306
//elt=(CL_Elt*)LBGauche->Items->Objects[0];
	ResGraphFrm->Show();
//    GraphiqueFrm->Chart->Title->Text->Text=Agri->Nom;
//    GraphiqueFrm->Demarrer();
}

//BtSupp
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::BtSup1GClick(TObject *Sender)
{
	LBGauche->Items->Delete(LBGauche->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::BtSupToutGClick(TObject *Sender)
{
	LBGauche->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::BtSup1DClick(TObject *Sender)
{
	LBDroit->Items->Delete(LBDroit->ItemIndex);
}
//---------------------------------------------------------------------------

void __fastcall TResultatFrm::BtSupToutDClick(TObject *Sender)
{
	LBDroit->Clear();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::TrouveValeurCourbe(int noFamille,int noCategorie,
		int noItem)
{
	CL_Elt *elt;
	int i;
	for(i=0;i<V_Elt->Nbelt;i++)
	{
		elt=V_Elt->Vecteur[i];
		if( elt->NoFamille ==noFamille
				&& elt->NoCategorie ==noCategorie
				&& elt->NoItem ==noItem )
		{
			LBGauche->Items->AddObject(elt->NomFamille,(TObject*)elt);; // a voir
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::BtBnMonnaieClick(TObject *Sender)
{
	ConversionFrm->Origine=0;
	ConversionFrm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TResultatFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	TVDicoFrm->Close();
	if(SysMonnaie!=SysMonnaieOrigine)
	AgriSaisieFrm->ChangeUniteMonnaie(SysMonnaie,SysMonnaieOrigine);
	SysMonnaie=SysMonnaieOrigine;
	Agri=AgriOrigine; //ne sert sans doute à rien
}
//---------------------------------------------------------------------------

void __fastcall TResultatFrm::LBGaucheClick(TObject *Sender)
{
	ResultatFrm->RGAxe->ItemIndex=0;
}
//---------------------------------------------------------------------------

void __fastcall TResultatFrm::LBDroitClick(TObject *Sender)
{
	ResultatFrm->RGAxe->ItemIndex=1;
}
//---------------------------------------------------------------------------

void __fastcall TResultatFrm::LBGaucheEnter(TObject *Sender)
{
	ResultatFrm->RGAxe->ItemIndex=0;
}
//---------------------------------------------------------------------------

void __fastcall TResultatFrm::LBDroitEnter(TObject *Sender)
{
	ResultatFrm->RGAxe->ItemIndex=1;
}
//---------------------------------------------------------------------------
/// COMPARAISON
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::BtBnComparaisonClick(TObject *Sender)
{
	HelpContext=1460;
	GBComparaison->Visible=true;
	GBGraph->Visible= false;
	LBSortie->Visible =false;

	GBComparaison->Top= 32;
	GBComparaison->Left= 152;
	GBComparaison->Height= 121;
	GBComparaison->Width= 121;

	// pour choisir les agri
	//Forme0Frm->CreeLBToutAgri(LBCompAgriFrm->ChLB); cf FormActivate
	LBCompAgriFrm->Show();
	LBCompAgriFrm->Visible=true;
	TVDicoFrm->Origine=SERIECOMP;

	// pour choisir les SerieComp
	//  mis dans activate
	//Forme0Frm->CreeTVEtat(TVChoixCompFrm->TV,V_CatSerieComp,V_SerieComp);

	// pour choisir les elements à comparer
	/*  mis dans activate
	 ES->IniV_Elt();
	 TVDicoFrm->Origine=SERIECOMP;
	 Forme0Frm->CreeTVToutElt(TVDicoFrm->TV,Agri,false);
	 TVDicoFrm->EstInitialise=false;
	 */
	//  mis dans activate
//    Forme0Frm->CreeTVEtat(TVChoixEtatFrm->TV,V_CatEtatSortie,V_EtatSortie);
//    Forme0Frm->CreeTVEtat(TVChoixCompFrm->TV,V_CatSerieComp,V_SerieComp);
//    LBSortie->SetFocus();
	// 0  un elément 1 un ensemble
	switch(RGUnOuEnsemble->ItemIndex)
	{
		case 0: TVDicoFrm->Visible= true;
		TVChoixCompFrm->Visible= false;
		break;
		case 1: TVDicoFrm->Visible= false;
		TVChoixCompFrm->Visible= true;
		break;

	}
}
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::RGUnOuEnsembleClick(TObject *Sender)
{
	// 0  un elément 1 un ensemble
	LBCompAgriFrm->Show();
	LBCompAgriFrm->Visible=true;
	switch(RGUnOuEnsemble->ItemIndex)
	{
		case 0: TVDicoFrm->Visible= true;
		TVChoixCompFrm->Visible= false;
		break;
		case 1: TVDicoFrm->Visible= false;
		TVChoixCompFrm->Visible= true;
		break;
	}
}
// choix des agriculteurs à comparer
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::RetourDeLBCompAgri(int noFamille,
		int noCategorie,int noItem)
{
	int n,i;
	CL_Agriculteur *agri,*agri0;
	CL_Elt *elt,*eltA;
	float *valeur;
	int nbAgri;
	AnsiString zeNom;
	float zeValeur[N_X];
	//combien de calculs à faire
	// pour déterminer parametres de ProgressBar
	nbAgri=0;
	for( n=0;n<LBCompAgriFrm->ChLB->Items->Count;n++)
	{
		if(LBCompAgriFrm->ChLB->Checked[n]==true)nbAgri++;
	}
	if(nbAgri==1)
	{
		MessageBox(Handle,"Pas d'autre Agriculteur Sélectionné)","Problème",MB_OK|MB_ICONEXCLAMATION);
		return;

	}
	ProgressBar->Position=0;
	ProgressBar->Max=nbAgri;
	if(nbAgri>10)
	{
		MessageBox(Handle,"Pas plus de 10 Eléments","Problème",
				MB_OK|MB_ICONEXCLAMATION);
		return;
	}

	// efface les valeurs les eltA contenus dans LstValeur et LstEltA
	// efface  LstValeur et LstEltA
	if(Global!=ENSEMBLE)
	ViderLesLst();
	ResultatFrm->LBGauche->Clear();
	ResultatFrm->LBDroit->Clear();

	//calcul0  modifie Agri donc le stocker et le remettre en fin
	agri0=Agri;
	ResGraphFrm->AnDebut=0;
	for( n=0;n<LBCompAgriFrm->ChLB->Items->Count;n++)
	{
		if(LBCompAgriFrm->ChLB->Checked[n]==true)
		{
			agri=(CL_Agriculteur *)LBCompAgriFrm->ChLB->Items->Objects[n];
			//...230908
			if(ResGraphFrm->AnDebut==0)
			ResGraphFrm->AnDebut=agri->DefSim->An_0;
			else if(ResGraphFrm->AnDebut!=agri->DefSim->An_0)
			ResGraphFrm->AnDebut=1;//on veut comparer deux décades différentes

			if(agri->Flag=='N')
			{
				AgriSaisieFrm->Calcul0(agri);
				agri->Flag='O';
			}
			//accroche à elt la valeur de l'item sur N_X années
			//    metPcentDansElt()  pour tenir compte des aléas
			for(i=0;i<V_Elt->Nbelt;i++)
			{
				elt=V_Elt->Vecteur[i];
				if( elt->NoFamille ==noFamille
						&& elt->NoCategorie ==noCategorie
						&& elt->NoItem ==noItem )
				{
					//Forme0Frm->Agri=agri;
					Forme0Frm->CompleteElt(elt,agri);//080202
					valeur=new float[N_X];
					zeNom=elt->Nom;
					memcpy(valeur,elt->Valeur,sizeof(float)*N_X);
					memcpy(zeValeur,elt->Valeur,sizeof(float)*N_X);
					eltA=new CL_Elt();
					eltA->Valeur=valeur;
					LstValeur->Add(valeur);
					LstEltA->Add(eltA);
					ResultatFrm->LBGauche->Items->AddObject(agri->NomV(),(TObject*)eltA);
					break;
				}
			}
			ProgressBar->StepBy(1);
		}
	}
	ResGraphFrm->Origine=0; //151002
	ResGraphFrm->Nature=COMPARAISON;
	ResGraphFrm->Caption=zeNom;//!!!!!!!!!!!!!!!!!!!!!!!
	ResGraphFrm->Show();
//    ShowMessage("ResGraphFrm->Show();");
	ProgressBar->Position=0;
	Agri=agri0;
	AgriSaisieFrm->Agri=Agri;

	CreeDico();

}
//--------------------------------------------------------------------------------
void __fastcall TResultatFrm::RetourDeTVChoixComp(CL_EtatSortie *serieComp)
{
	int n,i,j;
	int nbAgri;
	int n0,nbElt;

	CL_Agriculteur *agri,*agri0;
	CL_Elt *elt,*eltAComp,*eltA;
	float *valeur;
	int delta; //ProgressBar
	TStringList *lstNomAgri;
	int noAgri;
// test
	int fait;
	AnsiString nomA1;
	if(serieComp==NULL)return;

	// efface les valeurs les eltA contenus dans LstValeur et LstEltA
	// Clear  LstValeur et LstEltA
	if(Global!=ENSEMBLE)// tjrs vrai!!
	ViderLesLst();//LstValeur et LstEltA

	lstNomAgri=new TStringList;

	nbAgri=0;
	for( n=0;n<LBCompAgriFrm->ChLB->Items->Count;n++)
	{
		if(LBCompAgriFrm->ChLB->Checked[n]==true) nbAgri++;
	}
	if(nbAgri==0)
	{
		MessageBox(Handle,"Aucun Agriculteur","Problème",MB_OK|MB_ICONEXCLAMATION);
		return;

	}

	ProgressBar->Position=0;
	delta=ProgressBar->Max/nbAgri;

	//calcul0  modifie Agri donc le stocker le remettre en fin et le calculer
	agri0=Agri;
	if(LstValeur==NULL)LstValeur=new TList;//cfagridata
	//reperer debut du stockage des valeurs dans LstValeur
	n0=LstValeur->Count;//0 puisqu'aprés ViderLesLst
	// compter les élements dans les comparaisons
	nbElt=0;
	for(i=0;i<serieComp->V_Elt->Nbelt;i++)
	{
		elt=serieComp->V_Elt->Vecteur[i];
		if(elt->NoFamille==FORME)continue;
		nbElt++;
	}

	// vecteur des elt à comparer
	//recherche par agri des éléments a comparer
	//les stocker dans LstValeur

	fait=0;

	for( n=0;n<LBCompAgriFrm->ChLB->Items->Count;n++)
	{
		if(nbAgri==fait)break;
		if(LBCompAgriFrm->ChLB->Checked[n]!=true) continue;

		agri=(CL_Agriculteur *)LBCompAgriFrm->ChLB->Items->Objects[n];
		fait++;
		//creer nom complet: nom +n0 variante
		nomA1=agri->NomV();
		lstNomAgri->Add(nomA1);
		AgriSaisieFrm->Calcul0(agri);
		Forme0Frm->CreeTVToutElt(TVDicoFrm->TV,agri,false);

		for(i=0;i<serieComp->V_Elt->Nbelt;i++)
		{
			eltAComp=serieComp->V_Elt->Vecteur[i];
			if(eltAComp->NoFamille==FORME)continue;
			valeur=new float[N_X];
			memset(valeur,0,sizeof(float)*N_X);
			LstValeur->Add(valeur);

			//rechercher sa valeur
			for(j=0;j<V_Elt->Nbelt;j++)
			{
				elt=V_Elt->Vecteur[j];

				if( elt->NoFamille ==eltAComp->NoFamille
						&& elt->NoCategorie ==eltAComp->NoCategorie
						&& elt->NoItem ==eltAComp->NoItem )
				{
					memcpy(valeur,elt->Valeur,sizeof(float)*N_X);
					eltAComp->Item=elt->Item; //250502
//		            LstValeur->Add(valeur);
					break;
				}
			}
		}
		ProgressBar->StepBy(delta);
	}

	// reprise pour affichage en ordre
	if(LstEltA==NULL)LstEltA =new TList;
	LstEltA->Clear();
	for(int i=0;i<serieComp->V_Elt->Nbelt;i++)
	{
		elt=serieComp->V_Elt->Vecteur[i];

		if(elt->NoFamille==FORME)
		{
			eltA=new CL_Elt(elt);
			eltA->Flag=0; //indique si le nom est à effacer 250502
			LstEltA->Add (eltA);
			continue;
		}
		//Titre nom   eg  Produits
		//  aprés on va avoir les valeurs pour chaque agri
		eltA=new CL_Elt(elt);
		eltA->Flag=0;//indique si le nom est à effacer 250502
		eltA->NoFamille=FORME;
		eltA->NoItem=TITRE;
		LstEltA->Add (eltA);

		//  maintenant on a les valeurs pour chaque agri
		// pour le premier  item du premier agri on commence à n0
		// pour le deuxieme item du premier agri on commence à n0+1
		//etc..
		// pour le premier  item du deuxieme agri on commence à n0    +nbElt
		// pour le deuxieme item du deuxieme agri on commence à n0+1  +nbElt
		//etc..
		//on passe de                 à
		//0 agri1 item1                    0 agri1 item1
		//1       item2                    1 agri2 item1
		//2       item3                    2 agri1 item2
		//3 agri2 item1                    3 agri2 item2
		//4       item2                    4 agri1 item3
		//5       item3                    5 agri2 item3

		j=n0;
		n0++;
		noAgri=0;
		fait=0;
		for( n=0;n<LBCompAgriFrm->ChLB->Items->Count;n++)
		{
			if(nbAgri==fait) break;
			if(LBCompAgriFrm->ChLB->Checked[n]==false) continue;
			fait++;
			valeur=(float*)LstValeur->Items[j];
			eltA=new CL_Elt(elt);
			eltA->Flag=0; //indique si le nom est à effacer 250502

			eltA->Flag=1;//indique si le nom est à effacer 250502
			eltA->Valeur=valeur;
			nomA1=lstNomAgri->Strings[noAgri++];
			eltA->Nom=nomA1.c_str();
			LstEltA->Add (eltA);
			j+=nbElt;
		}
	}
	//FBrouillon->EnCours=SERIECOMP;

	if(RBExcel->Checked==true)
	EX->Comparaison(serieComp,LstEltA,agri0->DefSim->An_0);//An_0 201211
	else
	QRSortieQuantFrm->Comparaison(serieComp,LstEltA,agri);

	// faire le ménage
	delete lstNomAgri;
	for(n=0;n<LstEltA->Count;n++)
	{
		elt=(CL_Elt*)LstEltA->Items[n];

		delete elt;
	}
	LstEltA->Clear();

	Agri=agri0;
	if(Agri==NULL)
	Agri=AgriEnCours; //110407
	AgriSaisieFrm->Calcul0(Agri);
	CreeDico();
	Origine=0;
	ProgressBar->Position=0;
}
//??? A Corriger
// quand on passe dans comparaison
// on revient à courbe les courbes ne correspondent pas au chox effectué!!

//*/
//........
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::FormClose(TObject *Sender,
		TCloseAction &Action)
{
	LBCompAgriFrm->Visible=false;

	TVChoixCompFrm->Visible=false;
	if(Global!=ENSEMBLE)
	{
		ViderLesLst();
		if(LstValeur) {delete LstValeur;LstValeur=NULL;}
		if(LstEltA) {delete LstEltA; LstEltA=NULL;}
	}

}

// efface les valeurs les eltA contenus dans LstValeur et LstEltA
// efface  LstValeur et LstEltA
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::ViderLesLst(void)
{
	int i;
	float *valeur;
	CL_Elt *eltA;
	if(LstValeur==NULL) return;

	for(i=0;i<LstValeur->Count;i++)
	{
		valeur=(float*)LstValeur->Items[i];
		delete []valeur;
	}
	LstValeur->Clear();
	//delete LstValeur;            c'est fait en sortant CloseQuery
	for(i=0;i<LstEltA->Count;i++)
	{
		eltA=(CL_Elt*)LstEltA->Items[i];
		if(eltA->Flag==1)
		free(eltA->Nom);
		delete eltA;
	}
	LstEltA->Clear();
	//delete LstEltA;
}

//---------------------------------------------------------------------------
void __fastcall TResultatFrm::RBEcranClick(TObject *Sender)
{
	RBEcran->Checked= true;
	RBQR->Checked= false;
	RBExcel->Checked= false;

}
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::RBQRClick(TObject *Sender)
{
	RBEcran->Checked= false;
	RBQR->Checked= true;
	RBExcel->Checked= false;
}
//---------------------------------------------------------------------------

void __fastcall TResultatFrm::RBExcelClick(TObject *Sender)
{
	RBEcran->Checked= false;
	RBQR->Checked= false;
	RBExcel->Checked= true;
}
//---------------------------------------------------------------------------

void __fastcall TResultatFrm::BtBnTravailClick(TObject *Sender)
{
	TravCalFrm->Origine=0;
	TravCalFrm->Show();

}
//---------------------------------------------------------------------------

void __fastcall TResultatFrm::GBComparaisonClick(TObject *Sender)
{
//

}
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::BtBnTableurClick(TObject *Sender)
{
	int i;
	CL_Agriculteur *agri;
	CL_AgriEff *agriEff;
	HelpContext=1470;

	QuelExcelCSVFrm->ShowModal();
	if(QuelExcelCSVFrm->Renonce==true) return;

	EX->EnTete();

	if(Global!=ENSEMBLE)
	{
		EX->ResAgri(Agri);
		return;
	}
	Global=AGRI;
	for(i=0;i<Ensemble->V_AgriEff->Nbelt;i++)
	{
		agriEff=Ensemble->V_AgriEff->Vecteur[i];
		agri=agriEff->Agri;

		// sans doute inutile
		if(agri==NULL) continue;

		// pas la peine de se fatiguer si aucun effectif
		if(AgriSaisieFrm->ilYaEffectif(agriEff)==false) continue;

		AgriSaisieFrm->Calcul0(agri);//050901
		EX->ResAgri(agri);
		//GereEnsembleFrm->ProgressBar->StepBy(1);
		delete agri->Resultat;
		agri->Resultat=NULL;

	}
	//revoir pour Agri V_elt
	Global=ENSEMBLE;
	Forme0Frm->CreeTVToutElt(TVDicoFrm->TV,Agri,false);

}
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::RGPrecisionClick(TObject *Sender)
{
	if(RGPrecision->ItemIndex==0)
	{
		Digits=0;
	}
	else
	{
		Digits=2;
	}
}
//---------------------------------------------------------------------------

void __fastcall TResultatFrm::BtBnDicoClick(TObject *Sender)
{
	TVDicoFrm->Show();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TResultatFrm::TexteChaine(void) {
	L_Inconnu = T->TrouveTexte("ResultatFrm", "L_Inconnu");
}
//--------------------------------------------
void TResultatFrm::IniCaption(void) {
	BtAffiche->Caption = LC_BtAffiche;
	BtBnChgtMonnaie->Caption = T->LC_BtAutreAgri;
	RGAxe->Caption = LC_RGAxe;
	BtBnComparaison->Caption = T->LC_GereComparaisonFrm;
	GBComparaison->Caption = T->LC_GereComparaisonFrm;
	BtBnCourbe->Caption = T->LC_BtBnCourbe;
	BtBnDico->Caption = T->LC_BtDico;
	LabDroit->Caption = LC_LabDroit;
	LabGauche->Caption = T->LC_TabSheetG;
	RGAxe->Items->Strings[0] = LabGauche->Caption;
	RGAxe->Items->Strings[1] = LabDroit->Caption;
	RBEcran->Caption = T->LC_RBEcran;
	RBLongueDuree->Caption = LC_LongueDuree;
	GBGraph->Caption = LC_GBGraph;
	GBMonnaie->Caption = LC_GBMonnaie;
	RGNatureG->Caption = T->LC_RGNatureG;
	RGNatureD->Caption = T->LC_RGNatureG;
	RGNatureG->Items->Strings[0] = LC_Courbe;
	RGNatureG->Items->Strings[1] = LC_Histo;
	RGNatureD->Items->Strings[0] = LC_Courbe;
	RGNatureD->Items->Strings[1] = LC_Histo;

	RGUnOuEnsemble->Caption = LC_RGUnOuEnsemble;
	RGUnOuEnsemble->Items->Strings[0] = LC_Un;
	RGUnOuEnsemble->Items->Strings[1] = LC_Serie;
	RGPrecision->Caption = T->LC_RGPrecision;
	RGPrecision->Caption = T->LC_RGPrecision;
	ResultatFrm->Caption = T->LC_BtBnResultat;
	GBSortie->Caption = T->LC_GBSortie;
	GBSortie->Caption = T->LC_GBSortie;
	BtBnStandard->Caption = LC_BtBnStandard;
	BtSup1G->Caption = LC_BtSup1G;
	BtSup1D->Caption = LC_BtSup1G;
	BtSupToutG->Caption = LC_BtSupToutG;
	BtSupToutD->Caption = LC_BtSupToutG;
	BtBnTableur->Caption = LC_BtBnTableur;
	BtBnTravail->Caption = T->LC_TSTravail;

	LBSortie->Items->Strings[0] = LC_Synt;
	LBSortie->Items->Strings[1] = LC_RecDep;
	LBSortie->Items->Strings[2] = LC_RecDepGP;
	LBSortie->Items->Strings[3] = LC_Quant;
	LBSortie->Items->Strings[4] = LC_Ceg;
	LBSortie->Items->Strings[5] = LC_Bilan;
	LBSortie->Items->Strings[6] = LC_Prive;
	LBSortie->Items->Strings[7] = LC_Marges;
	LBSortie->Items->Strings[8] = LC_Exter;
	LBSortie->Items->Strings[9] = LC_Etat;
	LBSortie->Items->Strings[10] = LC_SyntFi;
	LBSortie->Items->Strings[11] = LC_Immo;
	LBSortie->Items->Strings[12] = LC_Tva;
	LBSortie->Items->Strings[13] = LC_Surface;
	LBSortie->Items->Strings[14] = LC_ComptaPer;
	LBSortie->Items->Strings[15] = LC_Stocks;
	LBSortie->Items->Strings[16] = LC_RecapLT;
	LBSortie->Items->Strings[17] = LC_RecapImmo;

	//BtBnRac->Caption=LC_Raccourci;           //181109

}
//--------------------------------------------
void TResultatFrm::TexteCaption(void) {
	LC_BtAffiche = T->TrouveCaption("Resultat", "LC_BtAffiche");
	LC_BtAutreAgri = T->TrouveCaption("CL_Trad", "LC_BtAutreAgri");
	LC_RGAxe = T->TrouveCaption("Resultat", "LC_RGAxe");
	LC_GereComparaisonFrm = T->TrouveCaption("CL_Trad",
			"LC_GereComparaisonFrm");
	LC_BtBnCourbe = T->TrouveCaption("CL_Trad", "LC_BtBnCourbe");
	LC_BtDico = T->TrouveCaption("CL_Trad", "LC_BtDico");
	LC_LabDroit = T->TrouveCaption("Resultat", "LC_LabDroit");
	LC_RBEcran = T->TrouveCaption("CL_Trad", "LC_RBEcran");
	LC_TabSheetG = T->TrouveCaption("CL_Trad", "LC_TabSheetG");
	LC_GBGraph = T->TrouveCaption("Resultat", "LC_GBGraph");
	LC_GBMonnaie = T->TrouveCaption("Resultat", "LC_GBMonnaie");
	LC_RGNatureG = T->TrouveCaption("CL_Trad", "LC_RGNatureG");
	LC_RGUnOuEnsemble = T->TrouveCaption("Resultat", "LC_RGUnOuEnsemble");
	LC_RGPrecision = T->TrouveCaption("CL_Trad", "LC_RGPrecision");
	LC_BtBnResultat = T->TrouveCaption("CL_Trad", "LC_BtBnResultat");
	LC_GBSortie = T->TrouveCaption("CL_Trad", "LC_GBSortie");
	LC_BtBnStandard = T->TrouveCaption("Resultat", "LC_BtBnStandard");
	LC_BtSup1G = T->TrouveCaption("Resultat", "LC_BtSup1G");
	LC_BtSupToutG = T->TrouveCaption("Resultat", "LC_BtSupToutG");
	LC_BtBnTableur = T->TrouveCaption("Resultat", "LC_BtBnTableur");
	LC_TSTravail = T->TrouveCaption("CL_Trad", "LC_TSTravail");
	LC_Un = T->TrouveCaption("Resultat", "LC_Un");
	LC_Serie = T->TrouveCaption("Resultat", "LC_Serie");

	LC_Courbe = T->TrouveCaption("Resultat", "LC_Courbe"); //170206
	LC_Histo = T->TrouveCaption("Resultat", "LC_Histo");

	LC_Synt = T->TrouveCaption("Resultat", "LC_Synt");
	LC_RecDep = T->TrouveCaption("Resultat", "LC_RecDep");
	LC_RecDepGP = T->TrouveCaption("Resultat", "LC_RecDepGP");
	LC_Quant = T->TrouveCaption("Resultat", "LC_Quant");
	LC_Ceg = T->TrouveCaption("Resultat", "LC_Ceg");
	LC_Bilan = T->TrouveCaption("Resultat", "LC_Bilan");
	LC_Prive = T->TrouveCaption("Resultat", "LC_Prive");
	LC_Marges = T->TrouveCaption("Resultat", "LC_Marges");
	LC_Exter = T->TrouveCaption("Resultat", "LC_Exter");
	LC_Etat = T->TrouveCaption("Resultat", "LC_Etat");
	LC_SyntFi = T->TrouveCaption("Resultat", "LC_SyntFi");
	LC_Immo = T->TrouveCaption("Resultat", "LC_Immo");
	LC_Tva = T->TrouveCaption("Resultat", "LC_Tva");
	LC_Surface = T->TrouveCaption("Resultat", "LC_Surface");
	LC_ComptaPer = T->TrouveCaption("Resultat", "LC_ComptaPer");
	LC_Stocks = T->TrouveCaption("Resultat", "LC_Stocks");
	LC_RecapLT = T->TrouveCaption("Resultat", "LC_RecapLT");
	LC_RecapImmo = T->TrouveCaption("Resultat", "LC_RecapImmo");
	LC_LongueDuree = T->TrouveCaption("Resultat", "LC_LongueDuree");
	LC_Raccourci = T->TrouveCaption("Resultat", "LC_Raccourci");

	IniCaption();
}
//--------------------------------------------

bool __fastcall TResultatFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=1390;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

void __fastcall TResultatFrm::BtBnAideClick(TObject *Sender)
{
	HelpContext=1280;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);

}
/* 110512
 //---------------------------------------------------------------------------

 void __fastcall TResultatFrm::BtBnRacClick(TObject *Sender)
 {
 static bool debut=true;
 int n;
 CL_EltRac *eltRac;
 if(LBRac->Visible==false)LBRac->Visible=true;
 else                     LBRac->Visible=false;
 if(debut==false)
 return;
 debut=false;

 RacDefFrm->LireFichier();
 LBRac->Items->Clear();
 for(n=0;n<RacDefFrm->SLstRaccourci->Count;n++)
 {
 eltRac=(CL_EltRac*)RacDefFrm->SLstRaccourci->Objects[n];
 LBRac->AddItem(eltRac->Alias,(TObject*)eltRac);
 }
 }
 //---------------------------------------------------------------------------

 void __fastcall TResultatFrm::LBRacClick(TObject *Sender)
 {
 int n;
 CL_EltRac *eltRac;
 n=LBRac->ItemIndex;
 eltRac=(CL_EltRac*)LBRac->Items->Objects[n];
 if(eltRac==NULL)
 return;
 TraiterEltRac(eltRac);
 }
 //---------------------------------------------------------------------------
 //---------------------------------------------------------------------------
 void TResultatFrm::TraiterEltRac(CL_EltRac *eltRac)
 {
 int n;
 TTreeNode *tN;
 CL_EtatSortie *etat;
 CL_Elt    *eltAComp;
 CL_EtatSortie *serieComp;

 if(eltRac->NoOrigine==STANDARD)//"T_Standard")
 {
 if(eltRac->Famille=="  -")
 {
 n=TrouveLBNo(ResultatFrm->LBSortie,eltRac->Nom);
 if(n==-1) return;

 ResultatFrm->AffUneSortie(n);
 }
 else if(eltRac->NoFamille==ETAT)//"Etats de sortie")
 {
 if(TVChoixEtatFrm->TV->Items->Count==0)
 Forme0Frm->CreeTVEtat(TVChoixEtatFrm->TV,V_CatEtatSortie,V_EtatSortie);
 tN=TrouveTVNo1(TVChoixEtatFrm->TV,eltRac->Categorie,eltRac->Nom);
 etat=(CL_EtatSortie*)tN->Data;
 QRSortieQuantFrm->Etat(etat,ResultatFrm->Agri);
 }
 }
 else if(eltRac->NoOrigine==DICO)//"Dictionnaire")
 {
 //element A Comparer

 if(TVDicoFrm->TV->Items->Count==0)
 ResultatFrm->CreeDico();
 if(eltRac->NoFamille==POSTE)//"Poste")
 {
 tN=TrouveTVNo1(TVDicoFrm->TV,eltRac->Famille,eltRac->Nom);
 if(tN==NULL) return;

 eltAComp=(CL_Elt*)tN->Data;
 ResultatFrm->RetourDeLBCompAgri(eltAComp->NoFamille,eltAComp->NoCategorie,
 eltAComp->NoItem);
 }
 else
 {
 if(eltRac->NoFamille==0)              //Bilan CEG
 tN=TrouveTVNo2(TVDicoFrm->TV,eltRac);
 else
 tN=TrouveTVNo3(TVDicoFrm->TV,eltRac);
 if(tN==NULL) return;

 eltAComp=(CL_Elt*)tN->Data;
 ResultatFrm->RetourDeLBCompAgri(eltAComp->NoFamille,eltAComp->NoCategorie,
 eltAComp->NoItem);

 }

 }
 else if(eltRac->NoOrigine==COMPARAISON)//"Série Comparaisons")
 {
 if(TVChoixCompFrm->TV->Items->Count==0)
 Forme0Frm->CreeTVEtat(TVChoixCompFrm->TV,V_CatSerieComp,V_SerieComp);

 tN=TrouveTVNo1(TVChoixCompFrm->TV,eltRac->Famille,eltRac->Nom);
 if(tN==NULL) return;

 serieComp=(CL_EtatSortie*)tN->Data;
 ResultatFrm->RetourDeTVChoixComp(serieComp);
 }
 if(TVDicoFrm->Visible==true) TVDicoFrm->Visible=false;
 }
 */
//---------------------------------------------------------------------------
int TResultatFrm::TrouveLBNo(TListBox *lB, AnsiString as0) {
	int n;
	AnsiString as;
	for (n = 0; n < lB->Count; n++) {
		as = lB->Items->Strings[n];
		if (as == as0)
			return n;
	}
	ShowMessage(as0 + L_Inconnu);
	return -1;
}
//---------------------------------------------------------------------------
TTreeNode* TResultatFrm::TrouveTVNo1(TTreeView *tV, AnsiString as0,
		AnsiString as1) {
	int i;
	TTreeNode *tN0, *tN1;
	tN0 = tV->Items->Item[0];
	while (1) {
		if (tN0->Text == as0) {
			for (i = 0; i < tN0->Count; i++) {
				tN1 = tN0->Item[i];
				if (tN1->Text == as1)
					return tN1;
			}
		} else {
			tN0 = tN0->getNextSibling();
			if (tN0 == NULL) {
				ShowMessage(as1 + L_Inconnu);
				return NULL;
			}
		}
	}
//    ShowMessage("TrouveTVNo");
}
//---------------------------------------------------------------------------
TTreeNode* TResultatFrm::TrouveTVNo2(TTreeView *tV, CL_EltRac *eltRac) {
	int i; //,j,k,l;
	TTreeNode *tN0, *tN1, *tN2;
	tN0 = tV->Items->Item[0];
	while (1) {
		if (tN0->Text == eltRac->Famille) {
			tN1 = tN0->Item[0];
			while (1) {
				if (tN1->Text == eltRac->Nom)
					return tN1;
				else {
					tN1 = tN1->getNextSibling();
					if (tN1 == NULL) {
						ShowMessage(eltRac->Nom + L_Inconnu);
						return NULL;
					}
				}
			}
		} else {
			tN0 = tN0->getNextSibling();
			if (tN0 == NULL) {
				ShowMessage(eltRac->Famille + L_Inconnu);
				return NULL;
			}
		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
TTreeNode* TResultatFrm::TrouveTVNo3(TTreeView *tV, CL_EltRac *eltRac) {
	int i; //,j,k,l;
	TTreeNode *tN0, *tN1, *tN2;
	tN0 = tV->Items->Item[0];
	while (1) {
		if (tN0->Text == eltRac->Famille) {
			tN1 = tN0->Item[0];
			while (1) {
				if (tN1->Text == eltRac->Categorie) {
					for (i = 0; i < tN1->Count; i++) {
						tN2 = tN1->Item[i];
						if (tN2->Text == eltRac->Nom)
							return tN2;
					}
				} else {
					tN1 = tN1->getNextSibling();
					if (tN0 == NULL) {
						ShowMessage(eltRac->Nom + L_Inconnu);
						return NULL;
					}
				}
			}
		} else {
			tN0 = tN0->getNextSibling();
			if (tN0 == NULL) {
				ShowMessage(eltRac->Famille + L_Inconnu);
				return NULL;
			}
		}
	}

//    ShowMessage("TrouveTVNo");
}
//---------------------------------------------------------------------------

