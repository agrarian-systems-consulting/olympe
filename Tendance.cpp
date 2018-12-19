//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LireFichier.h"
#include "LesVecteurs.hse"

#include "Erreur.h"
#include "LBTChoix.h"
#include "TVTChoix.h"

#include "GereAleaRdt.h"
#include "GereAleaPrix.h"
#include "TendanceEnum.h"
#include "Tendance.h"

extern CL_ES *ES;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"
#pragma resource "*.dfm"
TTendanceFrm *TendanceFrm;
//---------------------------------------------------------------------------
__fastcall TTendanceFrm::TTendanceFrm(TComponent* Owner) :
		TForme00Frm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::FormCreate(TObject *Sender)
{
	Grille0->FixedColor = (TColor)RGB(17,200,164);
//    Height=Screen->Height;
//    Width=Screen->Width;

	EstInitialise=false;

	Origine=0;//A replacer
}
//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::FormActivate(TObject *Sender)
{
	if(Origine==0)
	{
		Initialiser();
		Origine=1;
	}
}
//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::Initialiser(void)
{
//	if(EstInitialise==false)
//    {
	LaGrille=Grille0;
	LesGrilles[0]=Grille0;
	AjoutRow=true;
	LabTitre->Caption="";
	GrilleX=1;// a augmenter
	Digits=0;

	Grille0->Visible= false;
	// ajout item ds menu leblanc p 171
	LBTChoixFrm->Left= TendanceFrm->Left+TendanceFrm->Width-LBTChoixFrm->Width;
	LBTChoixFrm->Top= TendanceFrm->Top+20;
	Type=PRIX;
	EstInitialise=true;

//    }
}
//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::PrepareEcran(void)
{
	LabelModifie->Visible=false;
	EdNom->Visible=true;
	RGPcentVal->Visible=true;
	BtDonnees->Visible=true;
	//BtDonnees
	switch(LaGrille->Tag)
	{
		case GTProd:
		case GSProd:
		BtDonnees->Caption="Produits"; break;
		case GTCharge:
		case GSCharge:
		BtDonnees->Caption="Charges"; break;
		case GTExter:
		case GSExter:
		BtDonnees->Caption="Externalités"; break;

		default:ShowMessage("PrepareEcran BtDonnees Oubli");
	}
	TVTChoixFrm->Close();
}
//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::BoutFermerClick(TObject *Sender)
{
	if(CEstBon()==false) return;
	LaGrille->Tag=GTClose;
	PrepareEcran();
	Close(); //utilise FormCloseQuery de AgriSaisie
			   //et non celui de Forme00
}
//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::FormCloseQuery(TObject *Sender,bool &CanClose)
{
	if (Tendance==NULL) // Sinon, une fonction va tester Agri et... (sebastien)
	{
		CanClose=true;
		return;
	}
	if(CEstBon()==true)
	{
		CanClose=true;
		/*
		 LBChoixFrm->Visible=false;
		 LBChoixMCFrm->Visible=false;
		 TVChoixFrm->Visible=false;
		 TVChoixEltAgriFrm->Visible=false;
		 */
	}
	else
	CanClose=false;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::Produit(int *nature)
{
	bool rep;

	if(CEstBon()==false) return;
	switch(nature[1])
	{
		case PRODUIT:
		switch(nature[2])
		{
			case TENDANCE:
			V_Tendance=V_TendProd;
			LabTitre->Caption="PRIX: TENDANCE: Produit";
			LaGrille->Tag=GTProd;
			break;
			case SCENARIO:
			V_Tendance=V_ScenProd;
			LabTitre->Caption="PRIX: SCENARIO: Produit";
			LaGrille->Tag=GSProd;
			break;
		}
		break;

		case CHARGE:
		switch(nature[2])
		{
			case TENDANCE:
			V_Tendance=V_TendCharge;
			LabTitre->Caption="PRIX: TENDANCE: Charge";
			LaGrille->Tag=GTCharge;
			break;
			case SCENARIO:
			V_Tendance=V_ScenCharge;
			LabTitre->Caption="PRIX :SCENARIO: Charge";
			LaGrille->Tag=GSCharge;
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
		GereAleaPrixFrm->ReCreeTV=true;
		break;
		case COPIER:
		rep=demanderNom(nature[2],Tendance->Nom);
		if(rep==false) return;
		GereAleaPrixFrm->ReCreeTV=true;
		PrepareEcran();
		IniGrilleTendance();
		break;
	}
	EdNom->Text=Tendance->Nom;
	VersGrille(Grille0);
	CellDebut();
	LaGrille->Visible=true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
bool __fastcall TTendanceFrm::demanderNom(int nature,AnsiString nom)
{
	int n;
	bool rep;
	CL_Tendance *ancTend;
	AnsiString s,asCaption;
	switch(nature)
	{
		case TENDANCE: asCaption="Nouvelle Tendance";break;
		case SCENARIO: asCaption="Nouveau Scénario";break;
	}
	while(1)
	{
		rep=ES->EntrerNom(asCaption, "Donner son Nom", nom);
		if ( rep==true)
		{
			if(nom.Length()==0) continue;
			ancTend=V_Tendance->trouve(nom);
			if(ancTend)
			{
				MessageBox(Handle," Nom déjà donné","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
				continue;
			}
			Tendance->Nom=nom;
			V_Tendance->ins(Tendance);
			EdNom->Text=Tendance->Nom;
			return true;
		}
		else
		delete Tendance;
		Tendance=NULL;
		return false;
	}
}
// supprime toute une tendance!= sup ligne
//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::SupTendance(void)
{
	int rep;
	AnsiString as;
	as="Je supprime "+Tendance->Nom+"  ?";
	rep=MessageBox(Handle,as.c_str(),
			"SUPPRESSION",MB_YESNO|MB_ICONEXCLAMATION);
	if(rep!=IDYES) return;

	//retirer du vecteur
	V_Tendance->sup(Tendance);
	Tendance=NULL;
	PrepareEcran();
	IniGrilleTendance();
// !!!!!!
	GereAleaPrixFrm->ReCreeTV=true;
	GereAleaRdtFrm->ReCreeTV=true;

}
//---------------------------------------------------------------------------
bool __fastcall TTendanceFrm::CEstBon(void)
{
	bool rep;
	DerniereCell();
	if(LabelModifie->Visible==false) return true;

	rep=VerifGrille();
	if(rep==false)
	{
		ErreurFrm->Show();
		return false;
	}
	DesGrilles();
	Stocker();
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::BtDonneesClick(TObject *Sender)
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
		default:ShowMessage(" Oubli BtDonneesClick");break;
	}
	//rendre visible
	TVTChoixFrm->Visible=true;
	/*
	 //rendre visible
	 switch(LaGrille->Tag)
	 {
	 case GAni:
	 case GVariable:
	 case GExtNeg:
	 case GExtPos:
	 case GDepPrive:
	 case GRecPrive:
	 case GImmo:
	 case GPetit:
	 LBChoixFrm->Visible=true;
	 break;
	 default:
	 TVChoixFrm->Visible=true;
	 break;
	 }
	 */
}

//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::BtSupClick(TObject *Sender)
{
	int rep;
	int r=LaGrille->Row;
	CL_Delta *delta;
//bool supprimable;
	TObject *object=LaGrille->Objects[0][r];
	if(object==NULL) return;

	delta = (CL_Delta*) LaGrille->Objects[0][r];
	r=r;//aew
	/*
	 //Grille NON modifiable ?
	 if(	RGModifiable->ItemIndex==0)
	 {
	 MessageBox(Handle,"Données NON Modifiables","ERREUR",MB_ICONSTOP);
	 return;
	 }
	 */
	//supprimable=true;
	rep=MessageBox(Handle," Je supprime la ligne. Vous êtes sur ?","SUPPRESSION",
			MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDNO) return;
	switch( LaGrille->Tag)
	{
		case GTProd:
		case GTCharge:
		case GSProd:
		case GSCharge:
		case GTExter:
		case GSExter:
		delta->Flag='S';break;

		default:ShowMessage("BtSupClick Oubli");
	}
	SupprimerLigne();
	GrilleModif[LaGrille->Tag]=true;
}
//---------------------------------------------------------------------------
void __fastcall TTendanceFrm::RGPcentValClick(TObject *Sender)
{
	ReAffGrilleTendance();
}
//---------------------------------------------------------------------------

// est appelé par Form00->OnCloseQuery
//---------------------------------------------------------------------------
bool __fastcall TTendanceFrm::Stocker(void)
{
	ES->ecrireFichier();
	MazModif();
	LabelModifie->Visible=false;
	return true;
}
//---------------------------------------------------------------------------
//Stocker
void __fastcall TTendanceFrm::BoutAnnulClick(TObject *Sender)
{
	CEstBon();
}
//---------------------------------------------------------------------------

void __fastcall TTendanceFrm::BtBnStockerClick(TObject *Sender)
{
	Stocker();
}
//---------------------------------------------------------------------------

