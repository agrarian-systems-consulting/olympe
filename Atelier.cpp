//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <utilcls.h>

#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"
#include "Erreur.h"
#include "GereAtelier.h"
#include "TVChoixItem.h"
#include "AtelierMDetail.h"
#include "AtelierMDetailPerenne.h"

#include "AtelierMarge.h"
#include "Forme0.h"
#include "Tableur.h"
#include "QuelExcelCSV.h"
#include "LBProduit.h"
#include "NoteAgri.h"
#include "QRAtelier.h"
#include "TVChoixCalendrier.h"
#include "CL_Trad.h"
#include "Outil.h"
#include "Aide.h"

#pragma hdrstop

#include "Atelier.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TAtelierFrm *AtelierFrm;
extern CL_ES *ES;
extern CL_Excel *EX;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TAtelierFrm::TAtelierFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
	if (ES->Verrou == MEDTER) //040205
	{
		BtBnReportDroit->Enabled = false;
		BtBnReportBas->Enabled = false;

		BtBnSupprimer->Enabled = false;
		BtBnReportBas->Enabled = false;
		BtBnProduit->Enabled = false;
		BtBnVideTout->Enabled = false;

		BtBnProduit->Enabled = false;
	}

}
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::FormActivate(TObject *Sender)
{
	int g;
	if(Origine==0)
	{
		Origine=1;
		DefinirLesGrilles();
		for(g=0;g<GrilleX;g++)GrilleModif[g]=false;
		LabelModifie->Visible=false;
		//LBCalendrier->ItemIndex=    LBCalendrierItemIndex;
		PClasst->Visible=false;
	}

}
//-----------------------------------------------------------------------------
void __fastcall TAtelierFrm::AffAtelier(void)
{
	int g;

	if(Atelier->Derobe==true)
	{
		LabAtelier->Caption=Atelier->Nom+L_Derobe; //" DEROBE";
		RGDerobe->ItemIndex=1;//011001
	}
	else
	{
		LabAtelier->Caption=Atelier->Nom;
		RGDerobe->ItemIndex=0;
	}
	LabelModifie->Visible=false;
	// aide
	switch(Nature)
	{
		case CULTURE: HelpContext=42;break;
		case ANIMAUX: HelpContext=43;break;
		case PERENNE: HelpContext=44;break;
		case VIVRIER: HelpContext=45;break;
	}
	switch(Nature) //280307
	{
		case ANIMAUX:
		TSPiedHa->TabVisible=false;
		TSProdPied->TabVisible=false;
		TSChPied->TabVisible=false;
		break;
		case CULTURE:
		case PERENNE:
		case VIVRIER:
		if(ES->Version>=131)
		{
			TSPiedHa->TabVisible=true;
			TSProdPied->TabVisible=true;
			TSChPied->TabVisible=true;
		}
		else
		{
			TSPiedHa->TabVisible=false;
			TSProdPied->TabVisible=false;
			TSChPied->TabVisible=false;
		}
		break;
	}

	CellAVerifier=false;
	for(g=0;g<GrilleX;g++)
	{
		IniGrille(LesGrilles[g]);
		VersGrille(LesGrilles[g]);
	}

	LaGrille=LesGrilles[0]; //commencer par les produits
	CellInitiale(2,1);//pour Forme00 ValueAvant
//    g=LaGrille->Tag;
	PC->ActivePage=TSProduit;
	TS=PC->ActivePage;

	PCChange(this);

	CellAVerifier=true;
}
//---------------------------------------------------------------------------
//Avant  changt de page  verif de page précédente produits charges etc...
//
void __fastcall TAtelierFrm::PCChanging(TObject *Sender, bool &AllowChange)
{
	if(VerifPage()==false)AllowChange=false;
}
//---------------------------------------------------------------------------
// Changt page
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::PCChange(TObject *Sender)
{
	LabelModifie->Visible=false;

	TVChoixItemFrm->Visible=false;
	if(ES->Verrou==MEDTER)
	{
		BtBnProduit->Enabled=false;
		BtBnProduit->Enabled=false;
		AjoutRow=false;
		BtBnReportDroit->Enabled=false;

	}
	else
	{
		BtBnProduit->Enabled=true;
		BtBnProduit->Visible=true;
		AjoutRow=true; //pour tout sauf travail
		BtBnReportDroit->Enabled=true;
	}
	//passage à l'autre page
	if (PC->ActivePage==TSProduit)
	{
		if(ES->Verrou==MEDTER)
		{
			strcpy(TypeCol,"0000000000000000000");
			BtBnVideTout->Enabled=false;
		}
		else
		{
			strcpy(TypeCol,"00000NNNNNNNNNNNNNN");
			BtBnVideTout->Enabled=true;
		}
		LaGrille=GrilleProduits;
		BtBnProduit->Caption=T->L_Produit; //"Produits";
		//  repere la cellule ou on est et valueAvant pour voir si modif cfForme00 Grille0Click
		CellInitiale();

	}
	else if(PC->ActivePage==TSCharge)
	{
		if(ES->Verrou==MEDTER)
		{
			strcpy(TypeCol,"0000000000000000000");
			BtBnVideTout->Enabled=false;
		}
		else
		{
			strcpy(TypeCol,"00000NNNNNNNNNNNNNN");
			BtBnVideTout->Enabled=true;
		}
		LaGrille=GrilleCharges;
		BtBnProduit->Caption=T->L_Charge; //"Charges";
		CellInitiale();
	}
	else if(PC->ActivePage==TSChargeVolume)
	{
		if(ES->Verrou==MEDTER)
		{
			strcpy(TypeCol,"0000000000000000000");
			BtBnVideTout->Enabled=false;
		}
		else
		{
			strcpy(TypeCol,"000000NNNNNNNNNNNNNN"); //??
			BtBnVideTout->Enabled=true;
		}
		//reprendre l'ensemble des produits
		LaGrille=GrilleProduits;
		BtBnProduit->Caption=T->L_Charge;//"Charges";
		// ne pas utiliser DeGrilleItem pour Atelier->V_Produit: Pb si non stocké
		DeGrilleItem(Atelier->V_Produit);

		LaGrille=GrilleChargeVolume;
		VersGrilleVolume(Atelier->V_ChargeVolume);
		CellInitiale();
	}
	else if(PC->ActivePage==TSExternalite)
	{
		if(ES->Verrou==MEDTER)
		{
			strcpy(TypeCol,"0000000000000000000");
			BtBnVideTout->Enabled=false;
		}
		else
		{
			strcpy(TypeCol,"00000NNNNNNNNNNNNNN");
			BtBnVideTout->Enabled=true;
		}
		LaGrille=GrilleExternalite;
		BtBnProduit->Caption=T->L_Exter; //"Externalités";
		CellInitiale();
	}
	else if(PC->ActivePage==TSAvance)
	{
		if(ES->Verrou==MEDTER)
		{
			strcpy(TypeCol,"0000000000000000000");
		}
		else
		{
			strcpy(TypeCol,"0NNNNNNNNNNNNNN"); //031201
		}
		BtBnVideTout->Enabled=false;
		AffTotalCharge(SGAV);
		LaGrille=GrilleAvance;
		BtBnProduit->Enabled=false;
		BtBnReportDroit->Enabled=false; //300902
		CellInitiale();
	}
	else if(PC->ActivePage==TSProdImmo)
	{
		TSProdImmo->Enabled=false;
		if (Nature==PERENNE)TSProdImmo->Enabled=true;
		else if(Nature==CULTURE)TSProdImmo->Enabled=true;

		BtBnProduit->Enabled=false;
		BtBnReportDroit->Enabled=false; //300902
		BtBnVideTout->Enabled=false;
		if(ES->Verrou==MEDTER)
		strcpy(TypeCol,"0000000000000000000");
		else
		strcpy(TypeCol,"0NNNNNNNNNNNNNN");//031201

		AffTotalCharge(SGPI);//230902
		LaGrille=GrilleProdImmo;
		CellInitiale();
	}
	else if(PC->ActivePage==TSTravail)
	{
		BtBnProduit->Enabled=false;
		BtBnVideTout->Enabled=true;
		if(ES->Verrou==MEDTER)
		strcpy(TypeCol,"0000000000000000000");
		else
		strcpy(TypeCol,"0NNNNNNNNNNNNNN");
		LaGrille=GrilleTravail;
		LBCalendrierClick(this);
		AjoutRow=false;
		CellInitiale();
	}
	else if(PC->ActivePage==TSValInv) //220903
	{
		BtBnProduit->Visible=false;
		BtBnVideTout->Enabled=false;
		if(ES->Verrou==MEDTER)
		strcpy(TypeCol,"0000000000000000000");
		else
		strcpy(TypeCol,"0NNNNNNNNNNNNNN");
		LaGrille=GrilleValInv;
		CellInitiale();
	}
	else if(PC->ActivePage==TSPiedHa) //280307
	{
		strcpy(TypeCol,"NNNNNNNNNNNNNNNNNNN");
		BtBnProduit->Visible=false;
		BtBnVideTout->Enabled=true;
		LaGrille=GrillePiedHa;
		CellInitiale();
	}
	else if(PC->ActivePage==TSProdPied) //280307
	{
		strcpy(TypeCol,"00000NNNNNNNNNNNNNN");
		BtBnVideTout->Enabled=true;
		LaGrille=GrilleProdPied;
		BtBnProduit->Caption=T->L_Produit;
		CellInitiale();
	}
	else if(PC->ActivePage==TSChPied) //280307
	{
		strcpy(TypeCol,"00000NNNNNNNNNNNNNN");
		BtBnVideTout->Enabled=true;
		LaGrille=GrilleChPied;
		BtBnProduit->Caption=T->L_Charge;
		CellInitiale();
	}
}
//---------------------------------------------------------------------------
// verif la page et indique si la grille a été modifiée
//---------------------------------------------------------------------------
bool __fastcall TAtelierFrm::VerifPage(void)
{
	ErreurFrm->Edit->Clear();

	DerniereCell();

	if(LabelModifie->Visible==false) return true;

	GrilleModif[LaGrille->Tag]=true;

	if(VerifLaGrille()==false) return false;

	DeLaGrille();
	return true;
}

//---------------------------------------------------------------------------
//FormCloseQuery
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	CanClose=Stocker();
}
//---------------------------------------------------------------------------
bool __fastcall TAtelierFrm::Stocker(void)
{
	int g;
	bool flag;
	//verifier derniere page et lire grille
	if(VerifPage()==false)
	{
		return false;
	}
	if(OrdreModif==true)StockerOrdre();

	flag=false;
	for(g=0;g<GrilleX;g++)
	{
		if(GrilleModif[g]==true)
		{
			flag=true;
			g=GrilleX;
		}
	}
	if(flag==true)
	ES->ecrireFichier();
	return true;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::StockerOrdre(void)
{
	int g=LaGrille->Tag;
	LaGrille=LesGrilles[0]; StockerOrdre1(Atelier->V_Produit);
	LaGrille=LesGrilles[1]; StockerOrdre1(Atelier->V_Charge);
	LaGrille=LesGrilles[2]; StockerOrdre1(Atelier->V_ChargeVolume);
	LaGrille=LesGrilles[3]; StockerOrdre1(Atelier->V_Externalite);
	LaGrille=LesGrilles[g];
	OrdreModif=false;
}
//----------------------------------------------------------------------------
void __fastcall TAtelierFrm::StockerOrdre1(CL_Vecteur<CL_ItemParAtelier> *vecteur)
{
	int i;
	i=0;
	for(int r=1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		vecteur->Vecteur[i]=(CL_ItemParAtelier*)LaGrille->Objects[0][r];
		i++;
	}
}

//--------------------------------------------------------------------------
//BtProduit
//--------------------------------------------------------------------------
void __fastcall TAtelierFrm::BtBnProduitClick(TObject *Sender)
{
	if(LaGrille->Tag==GChProp && LaGrille->Col==2)
	{ //charges proportionnelles au volume
		ChoixProduit();
		return;
	}

	if( TVChoixItemFrm->Visible==true ) {TVChoixItemFrm->Visible=false;return;}

	switch(LaGrille->Tag)
	{
		case GProduit:
		case GProdPied: //280307
		TVChoixItemFrm->Caption=T->L_Produit;//"PRODUITS";
		CreeTVItem(TVChoixItemFrm->TV, V_CatProduit, V_Produit);
		TVChoixItemFrm->Visible=true;
		break;
		case GCharge:
		case GChPied://280307
		TVChoixItemFrm->Caption=T->L_Charge;//"CHARGES";
		CreeTVItem(TVChoixItemFrm->TV, V_CatCharge, V_Charge);
		TVChoixItemFrm->Visible=true;
		break;
		case GChProp:
		TVChoixItemFrm->Caption=T->L_Charge;"CHARGES";
		CreeTVItem(TVChoixItemFrm->TV, V_CatCharge, V_Charge);
		TVChoixItemFrm->Visible=true;
		break;
		case GExter:
		TVChoixItemFrm->Caption=T->L_Exter;//"EXTERNALITES";
		CreeTVItem(TVChoixItemFrm->TV, V_CatExternalite,V_Externalite);
		TVChoixItemFrm->Visible=true;
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::ChoixProduit(void)
{
	int i; //,n;
	CL_ItemParAtelier *itemPA;//, *produitA;
	CL_Item *produit;

	LBProduitFrm->LB->Clear();
	for(i=0;i<Atelier->V_Produit->Nbelt;i++)
	{
		itemPA =Atelier->V_Produit->Vecteur[i];
		produit=itemPA->Item;
		LBProduitFrm->LB->Items->AddObject(produit->Nom,(TObject*)itemPA);
	}
	// le traitement est fait dans LBProduit
	LBProduitFrm->Show();
	return;
}
//---------------------------------------------------------------------------
//Derobe
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::RGDerobeClick(TObject *Sender)
{
	switch(RGDerobe->ItemIndex)
	{
		case 0: Atelier->Derobe=false; break;
		case 1: Atelier->Derobe=true; break;
	}
	if(Atelier->Derobe==true)
	LabAtelier->Caption=Atelier->Nom+"  "+L_Derobe; //" DEROBE";
	else
	LabAtelier->Caption=Atelier->Nom+"        ";
	LabelModifie->Visible=true;//220102
}
//---------------------------------------------------------------------------

//Boutons

//---------------------------------------------------------------------------
// supprime ligne
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::BtBnSupprimerClick(TObject *Sender)
{
	int r=LaGrille->Row;
	CL_ItemParAtelier *itemPA;
	int rep;
	r=r; //aew
	SelLigne();
	itemPA=(CL_ItemParAtelier*)LaGrille->Objects[0][r];
	rep=MessageBox(Handle,T->L_SupQ.c_str(),T->L_SupT.c_str(),MB_YESNO);
	if(rep==IDNO) return;
	if(itemPA) itemPA->Flag='S';
	SupprimerLigne();
	GrilleModif[LaGrille->Tag]=true;
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
//VideTout
//--------------------------------------------------------------------------
void __fastcall TAtelierFrm::BtBnVideToutClick(TObject *Sender)
{
	int c,r;
	CL_ItemParAtelier *itemPA;
	int rep;
	rep=MessageBox(Handle,T->L_SupToutQ.c_str(),L_SupT.c_str(),MB_YESNO);
	if(rep==IDNO) return;
	if(LaGrille!=GrilleTravail)
	{
		for(r=1;r<LaGrille->RowCount;r++)
		{
			itemPA=(CL_ItemParAtelier*)LaGrille->Objects[0][r];
			if(itemPA) itemPA->Flag='S';
		}
		VideGrille(LaGrille);
	}

	if(LaGrille==GrilleTravail)
	{
		for(r=1;r<LaGrille->RowCount;r++)
		{
			for(c=1;c<4;c++)
			LaGrille->Cells[c][r]="";
		}
		EdTotalBesoins->Text="";
	}

	GrilleModif[LaGrille->Tag]=true;
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------

//--------------------------------------------------------------------------
//ReportDroit
//--------------------------------------------------------------------------
void __fastcall TAtelierFrm::BtBnReportDroitClick(TObject *Sender)
{
	int c,c0,colQ;
	int cF,g;
	int r0;
	if(LaGrille==GrilleTravail) colQ=1;
	else if(LaGrille==GrillePiedHa ) colQ=2; //071009
	else colQ=5;
	if(LaGrille->Col <colQ )return;
	c0=LaGrille->Col;
	r0=LaGrille->Row;
	cF=LaGrille->ColCount-1;
	ValueAvant=LaGrille->Cells[cF][r0];
	g=LaGrille->Tag;
	ColM[g]=cF;RowM[g]=r0;
	for(c=c0+1;c<LaGrille->ColCount;c++)
	{
		if(RepPossible(c,r0)==true)
		LaGrille->Cells[c][r0]=LaGrille->Cells[c0][r0];
	}
	LabelModifie->Visible=true;
	GrilleModif[LaGrille->Tag]=true;
}
//--------------------------------------------------------------------------
//ReportBas
//--------------------------------------------------------------------------
void __fastcall TAtelierFrm::BtBnReportBasClick(TObject *Sender)
{
	int r,c0;
	int rF,g;
	int r0;
//int cDepart;
//	if(LaGrille==GrilleTravail) cDepart=0;
//    else                        cDepart=1;

	c0=LaGrille->Col;
	r0=LaGrille->Row;
	rF=LaGrille->RowCount-1;
	ValueAvant=LaGrille->Cells[c0][r0];
	g=LaGrille->Tag;
	ColM[g]=c0;RowM[g]=rF;
	for(r=r0+1;r<LaGrille->RowCount;r++)
	{
		if(RepPossible(c0,r)==true) //041005
		LaGrille->Cells[c0][r]=LaGrille->Cells[c0][r0];
	}
	LabelModifie->Visible=true;
	GrilleModif[LaGrille->Tag]=true;
}
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::BtBnNotesClick(TObject *Sender)
{
	//NoteAgriFrm->VientDe=T->L_Atelier;//"Atelier";
	NoteAgriFrm->VientDe="Atelier";//ne pas traduire
	NoteAgriFrm->Atelier=Atelier;
	NoteAgriFrm->Caption=Atelier->Nom;
	NoteAgriFrm->Memo->Text=Atelier->Notes;

	NoteAgriFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::BtBnImpClick(TObject *Sender)
{
	QRAtelierFrm->Prepare(Atelier);
}

//---------------------------------------------------------------------------
//Marge
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::BtBnMargeClick(TObject *Sender)
{
	if(VerifPage()==false)return;

	switch(Atelier->Nature)
	{
		case PERENNE:
		AtelierMDetailPerenneFrm->Atelier=Atelier;
		AtelierMDetailFrm->Atelier=Atelier;
		AtelierMDetailPerenneFrm->EstInitialise=false;
		AtelierMDetailPerenneFrm->Show();
		break;
		default:
		AtelierMDetailFrm->Atelier=Atelier;
		AtelierMDetailFrm->EstInitialise=false;
		AtelierMDetailFrm->Show();
	}
}
//---------------------------------------------------------------------------
//Excel
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::BtBnExcelClick(TObject *Sender)
{
	QuelExcelCSVFrm->ShowModal();
	if(QuelExcelCSVFrm->Renonce==true) return;
	EX->Atelier(Atelier);
	EX->FermerFichier();
}
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::AffExcel(char *titre,TStringGrid *grille)
{
	if(grille->RowCount<=3) return; //1 pour le titre +2

	EX->Titre(0,titre);
	EX->EcritGrilleFichier(grille,titre);
}

//---------------------------------------------------------------------------
//Recopie Calendrier
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::BtBnRecopCalendrierClick(TObject *Sender)
{
	if(Nature==ANIMAUX)
	Forme0Frm->CreeTVAtelier(TVChoixCalendrierFrm->TV,V_Categorie,V_Animaux);
	else if(Nature==CULTURE)
	Forme0Frm->CreeTVAtelier(TVChoixCalendrierFrm->TV,V_CatCulture,V_Culture);
	else if(Nature==VIVRIER)
	Forme0Frm->CreeTVAtelier(TVChoixCalendrierFrm->TV,V_CatVivrier,V_Vivrier);
	else if(Nature==PERENNE)
	Forme0Frm->CreeTVPerenne(TVChoixCalendrierFrm->TV, V_Espece,V_Perenne);

	TVChoixCalendrierFrm->Show();

}
//---------------------------------------------------------------------------
//#include "Outil.h"
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::BtBnVersExcelClick(TObject *Sender)
{
	OutilFrm->VersExcel(LaGrille,0,0,LaGrille->ColCount,LaGrille->RowCount);
}
//---------------------------------------------------------------------------

void __fastcall TAtelierFrm::BtBnDExcelClick(TObject *Sender)
{
	OutilFrm->DExcel(LaGrille,0,0,LaGrille->ColCount,LaGrille->RowCount);
	LabelModifie->Visible==true;

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TAtelierFrm::TexteChaine(void) {
	L_Derobe = T->TrouveTexte("AtelierFrm", "L_Derobe");
	//210206
	L_TitreProduit = T->TrouveTexte("AtelierFrm", "L_TitreProduit");
	L_TitreVol = T->TrouveTexte("AtelierFrm", "L_TitreVol");
	L_Avant1 = T->TrouveTexte("AtelierFrm", "L_Avant1");
	L_Ent = T->TrouveTexte("AtelierFrm", "L_Ent");
	L_Fam = T->TrouveTexte("AtelierFrm", "L_Fam");
	L_Repro = T->TrouveTexte("AtelierFrm", "L_Repro"); //120109
	L_Autre = T->TrouveTexte("AtelierFrm", "L_Autre");
//    Grille0->
	//180507

}
//--------------------------------------------
void TAtelierFrm::IniCaption(void) {
	LabAvance->Caption = LC_LabAvance;
	AtelierFrm->Caption = T->LC_AtelierFrm;
	LabAtelier->Caption = T->LC_AtelierFrm;
	LabBesoins->Caption = LC_LabBesoins;
	LabCalEnCours->Caption = LC_LabCalEnCours;
	LabDebAmor->Caption = LC_LabDebAmor;
	RGDerobe->Caption = LC_RGDerobe;
	LabDurAmor->Caption = LC_LabDurAmor;
	//[0]TLabel [0]->Caption=LC_[0]TLabel [0];
	LabCalendrier->Caption = LC_LabCalendrier;
	BtBnMarge->Caption = T->LC_BtBnMarge;
	BtBnProduit->Caption = T->LC_BtBnProduit;
	BtBnRecopCal->Caption = LC_BtBnRecopCal;
	BtBnSupBesTrav->Caption = T->LC_BtBnSupBesTrav;
	LabTotal->Caption = LC_LabTotal;
	LabTotDep->Caption = T->LC_LabTotDep;
//    Label1->Caption=T->LC_LabTotDep;
	LabUtilise->Caption = T->LC_LabUtilise;
	Panell->Caption = LC_Panell;

	TSProduit->Caption = T->LC_BtBnProduit;
	TSCharge->Caption = T->LC_LabPCharge;
	TSChargeVolume->Caption = LC_TSChargeVolume;
	TSExternalite->Caption = T->LC_TSExternalite;
	TSAvance->Caption = LC_TSAvance;
	TSValInv->Caption = LC_TSValInv;
	TSProdImmo->Caption = LC_TSProdImmo;
	TSTravail->Caption = T->LC_TSTravail;
	//100206
	ChBRepTout->Caption = T->LC_ChBRepTout;
	BtClasser->Caption = T->LC_BtClasser;
	RGDerobe->Items->Strings[0] = LC_Vrai;
	RGDerobe->Items->Strings[1] = LC_Faux;

	TSPiedHa->Caption = LC_PiedParHa;
	TSProdPied->Caption = LC_ProdParPied;
	TSChPied->Caption = LC_ChargeParPied;
}
//--------------------------------------------
void TAtelierFrm::TexteCaption(void) {
	LC_LabAvance = T->TrouveCaption("Atelier", "LC_LabAvance");
	LC_AtelierFrm = T->TrouveCaption("CL_Trad", "LC_AtelierFrm");
	LC_LabBesoins = T->TrouveCaption("Atelier", "LC_LabBesoins");
	LC_LabCalEnCours = T->TrouveCaption("Atelier", "LC_LabCalEnCours");
	LC_LabPCharge = T->TrouveCaption("CL_Trad", "LC_LabPCharge");
	LC_LabDebAmor = T->TrouveCaption("Atelier", "LC_LabDebAmor");
	LC_RGDerobe = T->TrouveCaption("Atelier", "LC_RGDerobe");
	LC_LabDurAmor = T->TrouveCaption("Atelier", "LC_LabDurAmor");
	LC_LabCalendrier = T->TrouveCaption("Atelier", "LC_LabCalendrier");
	LC_BtBnMarge = T->TrouveCaption("CL_Trad", "LC_BtBnMarge");
	LC_BtBnProduit = T->TrouveCaption("CL_Trad", "LC_BtBnProduit");
	LC_BtBnRecopCal = T->TrouveCaption("Atelier", "LC_BtBnRecopCal");
	LC_BtBnSupBesTrav = T->TrouveCaption("CL_Trad", "LC_BtBnSupBesTrav");
	LC_LabTotal = T->TrouveCaption("Atelier", "LC_LabTotal");
	LC_LabTotDep = T->TrouveCaption("Atelier", "LC_LabTotDep");
	LC_LabUtilise = T->TrouveCaption("CL_Trad", "LC_LabUtilise");
	LC_Panell = T->TrouveCaption("Atelier", "LC_Panell");

//       LC_[0]TLabel [0] =T->TrouveCaption("Atelier" ,"LC_[0]TLabel [0]");
	LC_TSChargeVolume = T->TrouveCaption("Atelier", "LC_TSChargeVolume");
//       LC_TSExternalite =T->TrouveCaption("CL_Trad" ,"LC_TSExternalite");
	LC_TSAvance = T->TrouveCaption("Atelier", "LC_TSAvance");
	LC_TSProdImmo = T->TrouveCaption("Atelier", "LC_TSProdImmo");
//       LC_TSTravail =T->TrouveCaption("CL_Trad" ,"LC_TSTravail");
	LC_TSValInv = T->TrouveCaption("Atelier", "LC_TSValInv");
	LC_Vrai = T->TrouveCaption("Atelier", "LC_Vrai");
	LC_Faux = T->TrouveCaption("Atelier", "LC_Faux");

	LC_PiedParHa = T->TrouveCaption("Atelier", "LC_PiedParHa");
	LC_ProdParPied = T->TrouveCaption("Atelier", "LC_ProdParPied");
	LC_ChargeParPied = T->TrouveCaption("Atelier", "LC_ChargeParPied");

	IniCaption();

}

bool __fastcall TAtelierFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=540;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

