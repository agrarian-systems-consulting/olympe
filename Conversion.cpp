//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"

#include "LBSysUnit.h"
#include "Resultat.h"
#include "LBConversion.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "Conversion.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TConversionFrm *ConversionFrm;
extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TConversionFrm::TConversionFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TConversionFrm::FormCreate(TObject *Sender)
{
	EstInitialise=false;

}
// pourquoi applel de formActivate ???
// d'ou bidule     if(SysMonnaie==NULL )return;

//---------------------------------------------------------------------------
void __fastcall TConversionFrm::FormActivate(TObject *Sender)
{
	int i,j;
	if(SysMonnaie==NULL )return;

	if(EstInitialise==false)
	{
		EstInitialise=true;
		Personnaliser();
		DefinirLesGrilles();
		IniGrille(Grille0);
		VideGrille(Grille0);
		LabelModifie->Visible=false;

		if(Conversion==NULL)
		{
			RG->Enabled=false;
			RG->Items->Strings[0]= SysMonnaie->UTrans;
			RG->Items->Strings[1]="";

			EdMonnaieBase->Text= SysMonnaie->UTrans;
			EdMonnaieSortie->Text="";

			CBFrancEuro->Text= SysMonnaie->UTrans;
		}
		else
		{
			RG->Enabled=true;
			RG->Items->Strings[0]= Conversion->Base->UTrans;
			RG->Items->Strings[1]= Conversion->Sortie->UTrans;

			EdMonnaieBase->Text= Conversion->Base->UTrans;
			EdMonnaieSortie->Text= Conversion->Sortie->UTrans;

			CBFrancEuro->Clear(); //261102
			CBFrancEuro->Items->Add(Conversion->Base->UTrans);
			CBFrancEuro->Items->Add(Conversion->Sortie->UTrans);
			//CBFrancEuro->ItemIndex=1;

			CBFrancEuro->Text= Conversion->Base->UTrans;

			LaGrille->Cells[0][1]=Conversion->Base->UTrans;
			LaGrille->Cells[0][2]=Conversion->Sortie->UTrans;

			if(Conversion->APartirDe==0)//0n part du franc
			{
				for(i=1;i<11;i++) LaGrille->Cells[i][1]="  1";
				for(i=1,j=0; i<11;i++,j++) LaGrille->Cells[i][2]=
				Aff(Conversion->TauxConvFrancVersEuro[j],4);
			}
			else //on part de l'euro
			{
				for(i=1,j=0; i<11;i++,j++) LaGrille->Cells[i][1]=
				Aff(Conversion->TauxConvEuroVersFranc[j],4);
				for(i=1;i<11;i++) LaGrille->Cells[i][2]="  1";
			}

		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// FONCTIONS A PERSONNALISER
//----------------------------------------------------------------------------
void __fastcall TConversionFrm::Personnaliser(void)
{
	strcpy(TypeCol,"TNNNNNNNNNNN");
}
//---------------------------------------------------------------------------
void __fastcall TConversionFrm::DefinirLesGrilles(void)
{
	GrilleX=1;
	Grille0->Tag=0;
	LesGrilles[0]=Grille0;
	LaGrille=Grille0;
}
//-----------------------------------------------------------------------------
void __fastcall TConversionFrm::IniGrille(TStringGrid *grille)
{
	int largeur[11];
	int i,c,l;
	int an;
	largeur[0]=64;
	for(i=1;i<12;i++)largeur[i]=48;

	grille->RowCount=3;
	grille->ColCount=11;
	grille->FixedCols=1;
	grille->FixedRows=1;

	for(c=0;c<grille->ColCount;c++)
	{
		grille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
//    grille->Width=l+40;  //place pour l'ascenseur
	an=2001;

	for(c=1;c<12;c++,an++)
	grille->Cells[c][0]=an;

	AjoutRow=false;
	CellAVerifier=true;
}
//------------------------------------------------------------------------------
void __fastcall TConversionFrm::VersGrille(TStringGrid *grille)
{
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TConversionFrm::CellDebut(void)
{
	/*
	 // mal nommé  appelé quand on entre dans la forme

	 if(Conversion==NULL)
	 {
	 Conversion=new CL_Conversion();
	 CBFrancEuro->Items->Add(SysMonnaie->UUt);
	 CBFrancEuro->Text=SysMonnaie->UUt;
	 }
	 AffGrille();
	 */
}
//---------------------------------------------------------------------------
void __fastcall TConversionFrm::Grille0KeyPress(TObject *Sender, char &Key)
{
	if (Key >='0' && Key <='9') {ModifTaux=true;Conversion->APartirDe=RG->ItemIndex; return;}
	else if(Key=='.') {ModifTaux=true;Conversion->APartirDe=RG->ItemIndex; return;}
	else if(Key==VK_BACK) {ModifTaux=true;Conversion->APartirDe=RG->ItemIndex; return;}
	Key=0;
}
//-----------------------------------------------------------------------------
void __fastcall TConversionFrm::SaisirCell(int col,int row)
{
	int rSaisie;
	if(RG->ItemIndex==0) rSaisie=2;
	else rSaisie=1;

	if(row!=rSaisie) CellModifiable(false);
	else CellModifiable(true);
//	CellAVerifier=true;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TConversionFrm::RetourDeChoix(bool modif)
{
	/*
	 CBFrancEuro->Clear();
	 CBFrancEuro->Items->Add(Conversion->Base->UUt);
	 CBFrancEuro->Items->Add(Conversion->Sortie->UUt);
	 CBFrancEuro->ItemIndex=1;
	 */
	AffGrille();
}
//---------------------------------------------------------------------------
void __fastcall TConversionFrm::AffGrille(void)
{
	int i,j;
	int an=AgriEnCours->DefSim->An_0;

	RG->Enabled=true;
	EdMonnaieBase->Text = Conversion->Base->UTrans;
	EdMonnaieSortie->Text = Conversion->Sortie->UTrans;

	RG->Items->Strings[0]= Conversion->Base->UTrans;
	RG->Items->Strings[1]= Conversion->Sortie->UTrans;

	CBFrancEuro->Clear();
	CBFrancEuro->Items->Add(Conversion->Base->UUt);
	CBFrancEuro->Items->Add(Conversion->Sortie->UUt);
	CBFrancEuro->ItemIndex=1;

//    CBFrancEuro->Items->Add(SysMonnaie->UUt);
//    CBFrancEuro->Text=SysMonnaie->UUt;

	for(i=1;i<11;i++,an++) LaGrille->Cells[i][0]=Aff(an);

	LaGrille->Cells[0][1]=Conversion->Base->UTrans;
	LaGrille->Cells[0][2]=Conversion->Sortie->UTrans;

	if(RG->ItemIndex==0)//0n part du franc
	{
		for(i=1;i<11;i++) LaGrille->Cells[i][1]="  1";
		for(i=1,j=0; i<11;i++,j++) LaGrille->Cells[i][2]=
		Aff(Conversion->TauxConvFrancVersEuro[j],4);
	}
	else //on part de l'euro
	{
		for(i=1,j=0; i<11;i++,j++) LaGrille->Cells[i][1]=
		Aff(Conversion->TauxConvEuroVersFranc[j],4);
		for(i=1;i<11;i++) LaGrille->Cells[i][2]="  1";
	}
}
//---------------------------------------------------------------------------
void __fastcall TConversionFrm::RGClick(TObject *Sender)
{
//comment savois que les taux ont eté modifiés?
//LabelModifie->Visible =true depuis la premiere modif=def de taux
//donc je m'appuie sur GrilleModif qui est mis à true par DerniereCell
	if(ModifTaux==true)
	{
		LireConversion();
		ModifTaux=false;
	}
	AffGrille();
}
//---------------------------------------------------------------------------
void __fastcall TConversionFrm::BtReportDroitClick(TObject *Sender)
{
	RepDroit(LaGrille,4);
	ModifTaux=true;
	Conversion->APartirDe=RG->ItemIndex;
}
//---------------------------------------------------------------------------
bool __fastcall TConversionFrm::Stocker(void)
{
	ES->ecrireFichier();

	//ShowMessage("Stocker A Faire");
	return true;
}
//---------------------------------------------------------------------------

void __fastcall TConversionFrm::LireConversion(void)
{
	int c,r,i;
	float val;
	if(Conversion->APartirDe==1) //on part des euros    1
	{
		r=1;
		for(c=1,i=0;c<11;c++,i++)
		{
			ReAffFloat(c,r,4);
			Conversion->TauxConvEuroVersFranc[i]=GrilleFloat(c,r);
			val=Conversion->TauxConvEuroVersFranc[i];
			if(val==0)val=1;
			Conversion->TauxConvFrancVersEuro[i]=1./val;

		}
	}
	else //on part des francs
	{
		r=2;
		for(c=1,i=0;c<11;c++,i++)
		{
			ReAffFloat(c,r,4);
			Conversion->TauxConvFrancVersEuro[i]=GrilleFloat(c,r);
			val=GrilleFloat(c,r);
			if(val==0) val=1.;
			Conversion->TauxConvEuroVersFranc[i]=1./val;
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TConversionFrm::CBFrancEuroKeyPress(TObject *Sender,
		char &Key)
{
	Key=0;
}
//---------------------------------------------------------------------------

void __fastcall TConversionFrm::BtBnOkClick(TObject *Sender)
{
	if(Conversion==NULL)
	{
		ShowMessage("Pas de monnaie Choisie");
		return;
	}
	else
	{
		if(ModifTaux==true)
		LireConversion();
		if(CBFrancEuro->ItemIndex==0)
		ResultatFrm->AConvertir=false;
		else
		ResultatFrm->AConvertir=true;
	}
	ResultatFrm->Origine=2;
	// pour les elt du bilan 
	Conversion->TauxConvFrancVersEuro[N_X]=Conversion->TauxConvFrancVersEuro[N_X-1];
	Conversion->TauxConvEuroVersFranc[N_X]= Conversion->TauxConvEuroVersFranc[N_X-1];

	Close();
}
//---------------------------------------------------------------------------
void __fastcall TConversionFrm::BtBnAnnulClick(TObject *Sender)
{
	ResultatFrm->AConvertir=false;
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TConversionFrm::BtBnMonnaieClick(TObject *Sender)
{
	LBConversionFrm->ShowModal();

}
//---------------------------------------------------------------------------
//--------------------------------------------
void TConversionFrm::IniCaption(void) {
	LabSortie->Caption = LC_LabSortie;
	BtBnMonnaie->Caption = LC_BtBnMonnaie;
	RG->Caption = LC_RG;
	LabDonnee->Caption = LC_LabDonnee;
	LabChoix->Caption = LC_LabChoix;
	ConversionFrm->Caption = LC_ConversionFrm;
	LabTitre->Caption = LC_LabTitre;
	ChBRepTout->Caption = T->LC_ChBRepTout;
	BtBnAbandon->Caption = LC_Abandon;
}
//--------------------------------------------
void TConversionFrm::TexteCaption(void) {
	LC_LabSortie = T->TrouveCaption("Conversion", "LC_LabSortie");
	LC_BtBnMonnaie = T->TrouveCaption("Conversion", "LC_BtBnMonnaie");
	LC_RG = T->TrouveCaption("Conversion", "LC_RG");
	LC_LabDonnee = T->TrouveCaption("Conversion", "LC_LabDonnee");
	LC_LabChoix = T->TrouveCaption("Conversion", "LC_LabChoix");
	LC_ConversionFrm = T->TrouveCaption("Conversion", "LC_ConversionFrm");
	LC_LabTitre = T->TrouveCaption("Conversion", "LC_LabTitre");
	LC_Abandon = T->TrouveCaption("Conversion", "LC_Abandon");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TConversionFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=1290;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

void __fastcall TConversionFrm::BtBnAideClick(TObject *Sender)
{
	HelpContext=1290;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
}
//---------------------------------------------------------------------------

