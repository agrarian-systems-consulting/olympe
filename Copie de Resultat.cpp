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

#include "Resultat.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TResultatFrm *ResultatFrm;

extern CL_Excel *EX;
extern CL_ES *ES;
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

		Forme0Frm->CreeTVToutElt(TVDicoFrm->TV,Agri,false);
		AjouteEtat(TVDicoFrm->TV);
		TVDicoFrm->Agri=Agri;//230103
		if(Global!=ENSEMBLE)
		{
			//prépare eléments pour comparaison
			Forme0Frm->CreeTVEtat(TVChoixCompFrm->TV,V_CatSerieComp,V_SerieComp);
			Forme0Frm->CreeLBToutAgri(LBCompAgriFrm->ChLB);
			for(i=0;i<LBCompAgriFrm->ChLB->Items->Count;i++)
			{
				agri=(CL_Agriculteur*)LBCompAgriFrm->ChLB->Items->Objects[i];
				if(agri==Agri)
				{
					LBCompAgriFrm->ChLB->Checked[i]=true;
					break;
				}
			}
		}
		TVDicoFrm->Origine=RESULTAT; //meme effet que SERIECOMP;
//        TVDicoFrm->VientDe="Resultat";
		//si Global=ENSEMBLE  CalculResultatEnsemble s'est chargé du travail
		if(Global!=ENSEMBLE)
		{
			//ES->IniV_Elt();
			//Forme0Frm->CreeTVToutElt(TVDicoFrm->TV,Agri,false);
			TVDicoFrm->EstInitialise=false;
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
	switch(n)
	{
		case 0: //Synthese
		if(RBQR->Checked==true)
		QRSortieValFrm->Prepare(SYNTHESE,Agri);
		if(RBExcel->Checked==true)
		EX->Synthese(Agri);
		break;
		case 1://Valeurs
		if(RBEcran->Checked==true)
		{
			SortieEcranFrm->Demarre();
			SortieEcranFrm->Valeur(Agri);
			SortieEcranFrm->Show();
		}
		if(RBQR->Checked==true)
		QRSortieValFrm->Prepare(VALEUR,Agri);
		if(RBExcel->Checked==true)
		EX->Valeur(Agri);
		break;

		case 2: //grands postes
		if(RBEcran->Checked==true)
		{
			SortieEcranFrm->Demarre();
			SortieEcranFrm->Valeur(Agri);
			SortieEcranFrm->Show();
		}
		if(RBQR->Checked==true)
		QRSortieValFrm->Prepare(TRESO,Agri);
		if(RBExcel->Checked==true)
		EX->Valeur(Agri);
// à faire                EX->Treso(Agri);
		break;

		case 3://Quantités
		if(RBExcel->Checked==true)
		EX->Quantite(Agri);
		else
		QRSortieQuantFrm->Prepare(QUANTITE,Agri);
		break;

		case 4://ceg
		if(RBExcel->Checked==true)
		EX->Ceg(Agri);
		else
		QRSortieValFrm->Prepare(CEG,Agri);
		break;

		case 5://Bilan
		if(RBExcel->Checked==true)
		EX->Bilan(Agri);
		else
		QRSortieValFrm->Prepare(BILAN,Agri);
		break;

		case 6://Privé
		if(RBExcel->Checked==true)
		EX->Famille(Agri);
		else
		QRSortieValFrm->Prepare(FAMILLE,Agri);
		break;

		case 7://Marge
		//TVChoixMargeFrm->Show();
		LBMargeFrm->Show();
		break;

		case 8://Externalites
		if(RBExcel->Checked==true)
		EX->Externalite(Agri);
		else
		QRSortieQuantFrm->Prepare(EXTER,Agri);
		break;

		case 9://Etat sortie
		ResultatFrm->Agri=Agri;//cf TVChoixEtatFrm
		TVChoixEtatFrm->Show();
		break;

		case 10://Finances
		if(RBExcel->Checked==true)
		EX->Finance(Agri);
		else
		QRSortieValFrm->Prepare(FINANCE,Agri);
		break;

		case 11://Immo
		if(RBExcel->Checked==true)
		EX->Immo(Agri);
		else
		QRSortieValFrm->Prepare(IMMO,Agri);
		break;

		case 12://Tva
		if(RBExcel->Checked==true)
		EX->Tva(Agri);
		else
		QRSortieValFrm->Prepare(TVA,Agri);
		break;

		case 13://Assolement
		AgriSaisieFrm->Agri=Agri;
		AssolFrm->Agri=Agri;
		AssolFrm->Show();
		break;

		case 14://Elt Comptable Pérennes
		if(RBExcel->Checked==true)
		ShowMessage("Perenne à faire");
		else
		QRSortieValFrm->Prepare(PERENNE,Agri);
		break;

		case 15://Les Stocks
		AgriSaisieFrm->Agri=Agri;
		LesStocksFrm->Agri=Agri;
		LesStocksFrm->Show();
		break;

	}
}

//---------------------------------------------------------------------------
// COURBE
//---------------------------------------------------------------------------
void __fastcall TResultatFrm::BtBnCourbeClick(TObject *Sender)
{
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
//    BtOuvrir->Tag=0;
	n=LBGauche->Items->Count+LBDroit->Items->Count;
	if(n==0)
	{
		MessageBox(Handle,"Aucun Elément)","Problème",MB_OK|MB_ICONEXCLAMATION);
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
	for( n=0;n<LBCompAgriFrm->ChLB->Items->Count;n++)
	{
		if(LBCompAgriFrm->ChLB->Checked[n]==true)
		{
			agri=(CL_Agriculteur *)LBCompAgriFrm->ChLB->Items->Objects[n];
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
//    GraphiqueFrm->Chart->Title->Text->Text=zeNom; 111002
//    GraphiqueFrm->Demarrer();                     111002
//    ResultatFrm->BtAfficheClick(this);
	ResGraphFrm->Origine=0;//151002
	ResGraphFrm->Nature=COMPARAISON;
	ResGraphFrm->Show();

	ProgressBar->Position=0;
//    ViderLesLst();
	Agri=agri0;
	AgriSaisieFrm->Agri=Agri;
	Forme0Frm->CreeTVToutElt(TVDicoFrm->TV,Agri,false);

}
// choix de l'élément à comparer
//---------------------------------------------------------------------------
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
	EX->Comparaison(serieComp,LstEltA,An_0);
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

	AgriSaisieFrm->Calcul0(agri0);
	Forme0Frm->CreeTVToutElt(TVDicoFrm->TV,agri0,false);
	Agri=agri0;
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

