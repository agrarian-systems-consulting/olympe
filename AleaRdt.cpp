//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"

#include "TendanceEnum.h"
#include "GereAleaRdt.h"
#include "TVRdtChoix.h"
#include "CL_Trad.h"
#include "NoteAgri.h"

#include "AleaPrix.h"
#include "Aide.h"
#include "AleaRdt.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AleaPrix"
#pragma resource "*.dfm"

TAleaRdtFrm *AleaRdtFrm;

extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TAleaRdtFrm::TAleaRdtFrm(TComponent* Owner) :
		TAleaPrixFrm(Owner) {
}
//---------------------------------------------------------------------------
//void __fastcall TAleaPrixFrm::PrepareEcran(void) cf Tendance
//void __fastcall TAleaPrixFrm::BoutFermerClick(TObject *Sender)
//void __fastcall TAleaPrixFrm::FormCloseQuery(TObject *Sender,bool &CanClose)
//---------------------------------------------------------------------------
//void __fastcall TAleaRdtFrm::FormCloseQuery(TObject *Sender,bool &CanClose)
/*
 //---------------------------------------------------------------------------
 void __fastcall TAleaRdtFrm::Produit(int *nature)
 {
 LabelModifie->Visible=false;
 LabNom->Visible=true;
 RGPcentVal->Visible=true;
 BtDonnees->Visible=true;

 //	if(CEstBon()==false) return;
 LabTitre->Caption=Tendance->Nom;

 switch(nature[1])
 {
 case PRODUIT:
 BtDonnees->Caption="Produits";
 switch(nature[2])
 {
 case TENDANCE:
 LaGrille->Tag=GTProd;
 break;
 case SCENARIO:
 LaGrille->Tag=GSProd;
 break;
 }
 break;

 case CHARGE:
 BtDonnees->Caption="Charges";
 switch(nature[2])
 {
 case TENDANCE:
 LaGrille->Tag=GTCharge;
 break;
 case SCENARIO:
 LaGrille->Tag=GSCharge;
 break;
 }
 break;
 case EXTER:
 BtDonnees->Caption="Externalités";
 switch(nature[2])
 {
 case TENDANCE:
 LaGrille->Tag=GTExter;
 break;
 case SCENARIO:
 LaGrille->Tag=GSExter;
 break;
 }
 break;
 }
 IniGrilleTendance();
 //    LabNom->Caption=Tendance->Nom;
 VideGrille(Grille0);
 VersGrille(Grille0);
 LaGrille->Visible=true;
 }
 */
//---------------------------------------------------------------------------
//bool __fastcall TAleaPrixFrm::demanderNom(int nature,AnsiString nom)
//    AleaPrixFrm->V_Tendance=V_Tendance; permet d'utliser
//void  __fastcall TAleaPrixFrm::SupTendance(void)
// probleme!!!
//bool __fastcall TAleaPrixFrm::CEstBon(void)
//---------------------------------------------------------------------------
void __fastcall TAleaRdtFrm::BtDonneesClick(TObject *Sender)
{
	//effacer TV LB si visible
	if(TVRdtChoixFrm->Visible==true) {TVRdtChoixFrm->Visible=false;return;}
	TVRdtChoixFrm->LaGrille=LaGrille;
	//actualiser TV ou LB: on a pu creer des nouveaux éléments
	switch(LaGrille->Tag)
	{
		case GTProd:
		case GSProd:
		CreeTVItem(TVRdtChoixFrm->TV,V_CatProduit,V_Produit);break;
		case GTCharge:
		case GSCharge:
		CreeTVItem(TVRdtChoixFrm->TV,V_CatCharge, V_Charge); break;
		case GTExter:
		case GSExter:
		CreeTVItem(TVRdtChoixFrm->TV,V_CatExternalite, V_Externalite); break;
		default:ShowMessage(" Oubli BtDonneesClick");break;
	}
	//rendre visible
	TVRdtChoixFrm->Visible=true;
}
//----------------------------------------------------------------------------
bool __fastcall TAleaRdtFrm::Stocker(void)
{
	int r;
	CL_Delta *delta;

	if(LabelModifie->Visible==false) return true;
	if(Tendance) //230502
	{
		Tendance->V_Delta->Nbelt=0;
		for(r=1;r<LaGrille->RowCount;r++)
		{
			delta=(CL_Delta*)LaGrille->Objects[0][r];
			if(delta==NULL) continue;

			Tendance->V_Delta->insSans(delta);
		}
	}
	ES->ecrireFichier();
	MazModif();
	LabelModifie->Visible=false;

	return true;
}
//---------------------------------------------------------------------------
//void __fastcall TAleaPrixFrm::BtSupClick(TObject *Sender)
//void __fastcall TAleaPrixFrm::RGPcentValClick(TObject *Sender)
//void __fastcall TAleaPrixFrm::BoutAnnulClick(TObject *Sender)
//void __fastcall TAleaPrixFrm::BtBnStockerClick(TObject *Sender)
//---------------------------------------------------------------------------
/*
 CL_Vecteur<CL_Atelier>      *V_Culture;
 CL_Vecteur<CL_Atelier>      *V_Animaux;
 CL_Vecteur<CL_Atelier>      *V_Vivrier;

 CL_Vecteur<CL_Espece>       *V_Espece;
 CL_Vecteur<CL_Atelier>      *V_Perenne;
 */

//--------------------------------------------
void TAleaRdtFrm::TexteCaption(void) {
	AleaRdtFrm->Caption = T->LC_AleaRdtFrm;
	LC_Pcent = T->TrouveCaption("AleaPrix", "LC_Pcent");
	LC_Valeur = T->TrouveCaption("AleaPrix", "LC_Valeur");

	IniCaption();

}
//--------------------------------------------
void TAleaRdtFrm::IniCaption(void) {
	LC_AleaRdtFrm = T->TrouveCaption("CL_Trad", "LC_AleaRdtFrm");
	RGPcentVal->Items->Strings[0] = LC_Pcent;
	RGPcentVal->Items->Strings[1] = LC_Valeur;

}
//------------------------------------------------------------------

void __fastcall TAleaRdtFrm::BtBnNotesClick(TObject *Sender)
{
//020507
	NoteAgriFrm->VientDe="AleaRdt";//ne pas traduire
	NoteAgriFrm->Tendance=Tendance;
	NoteAgriFrm->Caption=Tendance->Nom;
	NoteAgriFrm->Memo->Text=Tendance->Notes;

	NoteAgriFrm->Show();

}
//---------------------------------------------------------------------------

void __fastcall TAleaRdtFrm::RGPrecisionClick(TObject *Sender)
{
	int row,c,col;
	float rdt,base;
	CL_Delta *delta;
	if(RGPrecision->ItemIndex==0)
	Digits=0;
	else
	Digits=2;
	//..........  210908
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		delta=(CL_Delta*)LaGrille->Objects[0][row];
		if (delta==NULL) continue;

		base=delta->Rdt; //160112
		for(c=0,col=5;c<delta->NMax;c++,col++)//240907
		{
			switch(GrilleALire)
			{
				case 0: //saisie en pcent
				delta->Pcent[c]=GrilleFloat(col,row);
				break;
				case 1://saisie en valeur
				rdt =GrilleFloat(col,row);
				delta->Pcent[c]=(rdt*100)/base;
				break;
			}
		}
		delta->Flag='O';
	}
	//....
	VideGrille(Grille0);
	VersGrille(Grille0);

}
//---------------------------------------------------------------------------

bool __fastcall TAleaRdtFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=1740;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

void __fastcall TAleaRdtFrm::BtReportDroitClick(TObject *Sender)
{
	int c,c0,colQ=5;
	int r0;
	AnsiString as;
	int g;
	if(LaGrille->Col <colQ )return;
	if(RGPrecision->ItemIndex==0) DigitsRdt=0;
	else DigitsRdt=2;
	g=LaGrille->Tag;
	GrilleModif[g]=true;
	LabelModifie->Visible=true;

	c0=LaGrille->Col;
	r0=LaGrille->Row;
	ReAffFloat(c0,r0,DigitsRdt);
	for(c=c0+1;c<LaGrille->ColCount;c++)
	{
		if(ChBRepTout->Checked==false)
		{
			if(CellVide(c,r0)==false) continue;
		}
		LaGrille->Cells[c][r0]=LaGrille->Cells[c0][r0];
	}

}
//---------------------------------------------------------------------------

