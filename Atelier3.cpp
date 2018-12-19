#include <vcl.h>
#include <stdio.h>

#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"
#include "GereCalendrier.h"
#include "CL_Matrice.h"
#include "CL_BesTrav.h"
#pragma hdrstop

#include "Espece.h"
#include "AtelierMDetailPerenne.h"

#include "CL_Trad.h"
#include "Atelier.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
extern CL_Trad *T;

//-----------------------------------------------------------------------------
//SAISIE
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::SaisirCell(int col,int row)
{
	if (LaGrille==GrilleChargeVolume) SaisirCellVolume(col,row);
}
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::SaisirCellVolume(int col,int row)
{
	int colTV=4;
	int colProd= 2;
	if (col==colTV ) BtBnProduit->Caption=T->L_Charge; //"Charges";
	else if (col==colProd) BtBnProduit->Caption=T->L_Produit;//"Production";
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::LBCalendrierClick(TObject *Sender)
{
	int n;
	AnsiString s;
	CL_Calendrier *calendrier;
	CL_Periode *periode;
	CL_BesTrav *BesTrav1;
	float totHeure,totHeureAn[N_PHASE+1]; //180108
	n=LBCalendrier->ItemIndex;
	s=LBCalendrier->Items->Strings[n];

	if(s=="[...]")
	{
		if(VerifPage()==false)return;

		//GereCalendrierFrm->Origine=0;
		GereCalendrierFrm->Show();
		return;
	}

	// exception on peut définir à la suite plusieurs séries de besoin
	// sans sortir de la grille donc qans appeler les mécanismes tradi
//    if(GrilleModif[GrilleTravail->Tag]==true)
	if(CellModif==true)
	{
		CellModif=false;
		//ShowMessage("Modif LBCalendrierClick");
		BesTrav->lireGrille(GrilleTravail);
		if(Atelier->V_BesTrav->trouve(BesTrav->No)==NULL)
		Atelier->V_BesTrav->insSans(BesTrav);
		CreeLBTravail();
	}
	GrilleModif[GrilleTravail->Tag]=false;
	BesTrav=NULL;

	VideGrille(GrilleTravail);

	//je prends le calendrier à afficher
	calendrier=(CL_Calendrier*)LBCalendrier->Items->Objects[n];
	//il comprend des périodes??
	if(calendrier->V_Periode->Nbelt==0)
	{
		ShowMessage(L_ErrCal); //"ce Calendrier n'a pas de périodes définies");
		return;
	}
	LabCalEnCours->Caption=calendrier->Nom;
	n=calendrier->V_Periode->Nbelt +2; //!!!
	GrilleTravail->RowCount=n;
	// les périodes du Calendrier
	for(n=0;n<calendrier->V_Periode->Nbelt;n++)
	{
		periode=calendrier->V_Periode->Vecteur[n];
		GrilleTravail->Cells[0][n+1]=periode->Nom;
	}
	GrilleTravail->Cells[0][n+1]=L_TotAn; //"     Total Annuel";
	EdTotalBesoins->Text="";
	//je cherche les besoins en travail de la culture pour ce calendrier
	BesTrav=Atelier->V_BesTrav->trouve(calendrier->No);
	if(BesTrav)
	{
		//j'ai trouvé Mais je vérifie qu'il y a bien le meme nombre de période
		//sinon je bricole à charge pour l'utilisateur de vérifier
		if(BesTrav->NbPeriodeCal!=calendrier->V_Periode->Nbelt)//110604
		{
			BesTrav1=new CL_BesTrav(Atelier->NbPhase,calendrier);
			Atelier->V_BesTrav->remplace(BesTrav,BesTrav1);
			BesTrav1->CopieValeur(BesTrav);
			BesTrav=BesTrav1;
			GrilleModif[GrilleTravail->Tag]=false;
		}
		else
		// c'est ok
		{
			//innovation l'objet sait s'écrire
			BesTrav->ecrireGrille(GrilleTravail);
			BesTrav->Totalise(totHeure,totHeureAn);
			if(Atelier->Espece)
			totHeure=AtelierMDetailPerenneFrm->TotalHeure(Atelier->Espece,totHeureAn);
			EdTotalBesoins->Text=AnsiString(totHeure);
			GrilleModif[GrilleTravail->Tag]=false;
		}
	}
	else
	BesTrav=new CL_BesTrav(Atelier->NbPhase,calendrier);
	ColM[GTravail]=1; //200902
//??    CellInitiale(2,1);//a voir
//    ValueAvant=GrilleTravail->Cells[1][1];

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TAtelierFrm::BtBnSupBesTravClick(TObject *Sender)
{
	int rep;
	rep=MessageBox(Handle,L_SupQ.c_str(),L_SupT.c_str(),MB_YESNO);
	//rep=MessageBox(Handle,L_SupQ" Je supprime Vous êtes sur ?",L_SupT"SUPPRESSION",MB_YESNO);
	if(rep==IDNO) return;
	Atelier->V_BesTrav->sup(BesTrav);
	BesTrav=NULL;
	VideGrille(GrilleTravail);
	CreeLBTravail();
}

