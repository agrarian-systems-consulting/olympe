#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LireFichier.h"
#include "LesVecteurs.hse"

#include "TendanceEnum.h"
#include "TVTChoix.h"

#include "GereAleaRdt.h"

#include "Rendement.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Tendance"
#pragma link "AleaPrix"
#pragma resource "*.dfm"
TRendementFrm *RendementFrm;
//---------------------------------------------------------------------------
__fastcall TRendementFrm::TRendementFrm(TComponent* Owner) :
		TTendanceFrm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//void __fastcall TTendanceFrm::PrepareEcran(void) cf Tendance
//void __fastcall TTendanceFrm::BoutFermerClick(TObject *Sender)
//void __fastcall TTendanceFrm::FormCloseQuery(TObject *Sender,bool &CanClose)

//---------------------------------------------------------------------------
void __fastcall TRendementFrm::Produit(int *nature)
{
	bool rep;
	Type=QUANTITE;
	if(CEstBon()==false) return;
	switch(nature[1])
	{
		case PRODUIT:
		switch(nature[2])
		{
			case TENDANCE:
			V_Tendance=V_TendProduction;
			LabTitre->Caption="TENDANCE: Rendement";
			LaGrille->Tag=GTProd;
			break;
			case SCENARIO:
			V_Tendance=V_ScenProduction;
			LabTitre->Caption="SCENARIO: Rendement";
			LaGrille->Tag=GSProd;
			break;
		}
		break;

		case CHARGE:
		switch(nature[2])
		{
			case TENDANCE:
			V_Tendance=V_TendConsommation;
			LabTitre->Caption="TENDANCE: Charge";
			LaGrille->Tag=GTCharge;
			break;
			case SCENARIO:
			V_Tendance=V_ScenConsommation;
			LabTitre->Caption="SCENARIO: Charge";
			LaGrille->Tag=GSCharge;
			break;
		}
		break;
		case EXTER:
		switch(nature[2])
		{
			case TENDANCE:
			V_Tendance=V_TendExternalite;
			LabTitre->Caption="TENDANCE: Externalité";
			LaGrille->Tag=GTExter;
			break;
			case SCENARIO:
			V_Tendance=V_ScenExternalite;
			LabTitre->Caption="SCENARIO: Externalité";
			LaGrille->Tag=GSExter;
			break;
		}
		break;
	}
	switch(AFaire)
	{
		case 0:
		PrepareEcran();
		IniGrilleTendance();
		break;
		case CREER:
		PrepareEcran();
		IniGrilleTendance();
		rep=demanderNom(nature[2],"");
		if(rep==false) return;
		GereAleaRdtFrm->ReCreeTV=true;
//            ReCreeTV=true;
		break;
		case COPIER:
		rep=demanderNom(nature[2],Tendance->Nom);
		if(rep==false) return;
		GereAleaRdtFrm->ReCreeTV=true;
		PrepareEcran();
		IniGrilleTendance();
		break;
	}
	TendanceFrm->V_Tendance=V_Tendance; //!!!
	EdNom->Text=Tendance->Nom;
	VersGrille(Grille0);
	CellDebut();
	LaGrille->Visible=true;
}
//---------------------------------------------------------------------------
//bool __fastcall TTendanceFrm::demanderNom(int nature,AnsiString nom)
//    TendanceFrm->V_Tendance=V_Tendance; permet d'utliser
//void  __fastcall TTendanceFrm::SupTendance(void)
// probleme!!!
//bool __fastcall TTendanceFrm::CEstBon(void)
//---------------------------------------------------------------------------
void __fastcall TRendementFrm::BtDonneesClick(TObject *Sender)
{
	//effacer TV LB si visible
	if(TVTChoixFrm->Visible==true) {TVTChoixFrm->Visible=false;return;}
	TVTChoixFrm->LaGrille=LaGrille;
	//actualiser TV ou LB: on a pu creer des nouveaux éléments
	switch(LaGrille->Tag)
	{
		case GTProd:
		case GSProd:
		CreeTVItem(TVTChoixFrm->TV,V_CatProduit,V_Produit);break;
		case GTCharge:
		case GSCharge:
		CreeTVItem(TVTChoixFrm->TV,V_CatCharge, V_Charge); break;
		case GTExter:
		case GSExter:
		ShowMessage(" Externalite a faire");break;
		default:ShowMessage(" Oubli BtDonneesClick");break;
	}
	//rendre visible
	TVTChoixFrm->Visible=true;
}

//void __fastcall TTendanceFrm::BtSupClick(TObject *Sender)

//void __fastcall TTendanceFrm::RGPcentValClick(TObject *Sender)
//bool __fastcall TTendanceFrm::Stocker(void)
//void __fastcall TTendanceFrm::BoutAnnulClick(TObject *Sender)
//void __fastcall TTendanceFrm::BtBnStockerClick(TObject *Sender)

