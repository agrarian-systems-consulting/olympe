//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop
#include "olympedec.h"
#include "olympe.hse"
#include "LesClassesApp.h"
#include "FichierLire.h"

#include "Forme0.h"
#include "Ensemble.h"
#include "NoteEnsemble.h"
#include "AgriSaisie.h"
#include "Resultat.h"
#include "TVDico.h"
#include "LBToutAgri.h"
#include "TVVarianteEns.h"
//#include "Graph.h"   111002
#include "ResGraph.h"

#include "LBSelectionAgri.h"
//#include "ChoixCritere.h"
#include "TriAgri.h"
#include "LBToutEnsemble.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "GereEnsemble.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGereEnsembleFrm *GereEnsembleFrm;

extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TGereEnsembleFrm::TGereEnsembleFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::FormActivate(TObject *Sender)
{
	if(VientDe=="Main")
	{
		VientDe="GereEnsemble";
		LabelModifie->Visible=false;
		copierV_Ensemble();

		RGVarianteClick(this);
		//CreeGrilleAgri(); est applelé par RGVarianteClick

		AgriSaisieFrm->LabelModifie->Visible=false;
		AgriSaisieFrm->Origine=0;
		TrouveEnCours();//??
//		GrilleEnsClick(this);     //?

	}
	ProgressBar->Position=0;
}
//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::copierV_Ensemble(void)
{
	CL_Ensemble *ens;
	ST_NoEnsemble *variante;
	V_EnsDepart=new CL_Vecteur<CL_Ensemble> (V_Ensemble);
	for(int i=0;i<V_EnsDepart->Nbelt;i++)
	V_EnsDepart->Vecteur[i]=new CL_Ensemble( V_Ensemble->Vecteur[i]);
	for(int i=0;i<V_EnsDepart->Nbelt;i++)
	{
		ens=V_EnsDepart->Vecteur[i];
		if(ens->LstVariante->Count==0) continue;
		for(int j=0;j<ens->LstVariante->Count;j++)
		{
			variante=(ST_NoEnsemble*)ens->LstVariante->Items[j];
			variante->Ensemble=V_EnsDepart->trouve(variante->No);
		}
	}
	for(int i=0;i<V_EnsDepart->Nbelt;i++)
	{
		ens=V_EnsDepart->Vecteur[i];
		if(ens->EstVariante==true) continue;
		ens->Ancetre->Ensemble=ens;
		ens->Ancetre->No =ens->No;
		numeroteLesFils(ens,ens->Ancetre,0);
	}
}
//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::numeroteLesFils(CL_Ensemble *ens,ST_NoEnsemble *Ancetre,int nP)
{
	ST_NoEnsemble *variante;
	ens->Ancetre=Ancetre;
	ens->NoVariante=nP;
	if(ens->LstVariante->Count==0) return;

	nP=nP*10;
	for(int i=0;i<ens->LstVariante->Count;i++)
	{
		variante=(ST_NoEnsemble*)ens->LstVariante->Items[i]; // Agri ou agri
		nP++;
		numeroteLesFils(variante->Ensemble,Ancetre,nP);
	}
	return;

}

//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::BtEffectifClick(TObject *Sender)
{
	int r=GrilleEns->Row;
	if(V_Ensemble->Nbelt==0)return;
	EnsembleFrm->Ensemble=(CL_Ensemble*)GrilleEns->Objects[0][r];
	EnsembleEnCours=EnsembleFrm->Ensemble;

	EnsembleFrm->AFaire=VOIR;
	EnsembleFrm->VoirEnsemble();
	EnsembleFrm->Show();
	EnsembleFrm->LabelModifie->Visible=false;
}
//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::BtResulClick(TObject *Sender)
{
	int r=GrilleEns->Row;
//CL_AgriEff *agriEff;//
//CL_Agriculteur *agri;

	if(V_Ensemble->Nbelt==0)return;

	Global=ENSEMBLE;
	EnsembleFrm->Ensemble=(CL_Ensemble*)GrilleEns->Objects[0][r];
	EnsembleEnCours=EnsembleFrm->Ensemble;
	ResultatFrm->Ensemble=EnsembleFrm->Ensemble;

//    agriEff=EnsembleFrm->Ensemble->V_AgriEff->Vecteur[0];
//    agri=agriEff->Agri;
	// pour connaitre l'annee de debut de la simulation
	// il faudra faire le test dans la definition des ensembles

	AgriSaisieFrm->CalculEnsemble(EnsembleFrm->Ensemble);

	ResultatFrm->Origine=0;
	ResultatFrm->Agri=EnsembleFrm->Ensemble->Total;

	TVDicoFrm->Complet=false;//pour n'afficher que les élt presents chez l'agri
	TVDicoFrm->Agri=EnsembleFrm->Ensemble->Total;

//    GraphiqueFrm->An_0=agri->DefSim->An_0;  111002
	ResultatFrm->Caption=EnsembleEnCours->Nom+"  "+
	EnsembleEnCours->NoVariante;

	AgriSaisieFrm->Caption=ResultatFrm->Caption;//240405
	ResultatFrm->Show();
	ResultatFrm->PresenterResultat();
	EnsembleFrm->LabelModifie->Visible=false;

}
//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::BtNouveauClick(TObject *Sender)
{
	bool rep;
	AnsiString newNom;
	char buf[100];
	CL_Ensemble *ens;
	while(1)
	{
		//rep=ES->EntrerNom("Nouvel Ensemble","",newNom);
		rep=ES->EntrerNom(L_NouvEns,"",newNom);
		if(rep==false) return;

		ens=V_Ensemble->trouve(newNom);
		if(ens)
		{
			sprintf(buf," %s  L_Existe.c_str()",newNom);
			//sprintf(buf," %s  Existe déjà",newNom);
			ShowMessage(buf);
		}
		else break;
	}
	EnsembleFrm->LabEnsemble->Caption=newNom;
	EnsembleFrm->Ensemble=new CL_Ensemble; //081001
	EnsembleFrm->Ensemble->Nom=newNom;//081001

	LBSelectionAgriFrm->VientDe="GereEnsemble";
	LBSelectionAgriFrm->Show();
	/*
	 EnsembleFrm->AFaire=CREER;

	 EnsembleFrm->AffGrilleVide();
	 Forme0Frm->CreeLBToutAgri(LBToutAgriFrm->ChLB);

	 LBToutAgriFrm->Show();
	 EnsembleFrm->Show();
	 EnsembleFrm->LabelModifie->Visible=true;
	 */
}
//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::SelectionManuelle(void)
{
	EnsembleFrm->AFaire=CREER;

	EnsembleFrm->AffGrilleVide();
	Forme0Frm->CreeLBToutAgri(LBToutAgriFrm->ChLB);
	LBToutAgriFrm->VientDe="GereEnsemble";
	LBToutAgriFrm->Show();
	EnsembleFrm->Show();
	EnsembleFrm->LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::SelectionTri(void)
{
	EnsembleFrm->AFaire=CREER;

	EnsembleFrm->AffGrilleVide();

	TriAgriFrm->VientDe="SelectionTri";
	TriAgriFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::SelectionAddition(void)
{
	EnsembleFrm->AFaire=CREER;

	EnsembleFrm->AffGrilleVide();
	LBToutEnsembleFrm->VientDe="SelectionAddition";
	LBToutEnsembleFrm->CreeLB();
	LBToutEnsembleFrm->BtBnVisible(true);
	LBToutEnsembleFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::Extraction(void)
{
	EnsembleFrm->AFaire=CREER;

	EnsembleFrm->AffGrilleVide();

	LBToutEnsembleFrm->VientDe="Extraction";
	LBToutEnsembleFrm->CreeLB();
	LBToutEnsembleFrm->BtBnVisible(false);
	LBToutEnsembleFrm->Show();

	TriAgriFrm->VientDe="Extraction";
	TriAgriFrm->Show();

}
//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::BtCopierClick(TObject *Sender)
{
	AnsiString newNom;
	char buf[100];
	CL_Ensemble *ens;
	AnsiString nomOrigine;
	bool rep;
	int r=GrilleEns->Row;

	if(V_Ensemble->Nbelt==0)return;

	EnsembleFrm->Ensemble=(CL_Ensemble*)GrilleEns->Objects[0][r];

	nomOrigine=EnsembleFrm->Ensemble->Nom;
	newNom=nomOrigine;
	while(1)
	{
		//rep=ES->EntrerNom("A Copier sous","",newNom);
		rep=ES->EntrerNom(L_ACopierSous,"",newNom);
		if(rep==false) return;
		if(newNom==nomOrigine) return;

		ens=V_Ensemble->trouve(newNom);
		if(ens)
		{
			//sprintf(buf," %s  Existe déjà",newNom);
			sprintf(buf," %s  L_Existe.c_str()",newNom);
			ShowMessage(buf);
		}
		else break;
	}
	//140602
	ens=new CL_Ensemble(EnsembleFrm->Ensemble);
	ens->Nom=newNom;
	EnsembleFrm->Ensemble=ens;
	EnsembleEnCours=ens;
	EnsembleFrm->LabEnsemble->Caption=ens->Nom;
	V_Ensemble->ins(ens);//c'est fait dans Ensemble Stocker A VOIR
	//....
	EnsembleFrm->AFaire=COPIER;
	EnsembleFrm->VoirEnsemble();
	EnsembleFrm->Show();
	EnsembleFrm->LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::BtSupprimerClick(TObject *Sender)
{
	int r=GrilleEns->Row;
	if(V_Ensemble->Nbelt==0)return;

	EnsembleFrm->Ensemble=(CL_Ensemble*)GrilleEns->Objects[0][r];
	if(EnsembleFrm->Ensemble==NULL) return;
	EnsembleEnCours=EnsembleFrm->Ensemble;

	EnsembleFrm->AFaire=SUPPRIMER;
	EnsembleFrm->VoirEnsemble();
	EnsembleFrm->Show();
	EnsembleFrm->EffaceEnsemble();
}
//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::BtRenommeClick(TObject *Sender)
{
	AnsiString newNom;
	char buf[100];
	CL_Ensemble *ens;
	AnsiString nomOrigine;
	bool rep;
	int r=GrilleEns->Row;
	if(V_Ensemble->Nbelt==0)return;

	EnsembleFrm->Ensemble=(CL_Ensemble*)GrilleEns->Objects[0][r];
	EnsembleEnCours=EnsembleFrm->Ensemble;

	nomOrigine=EnsembleFrm->Ensemble->Nom;
	newNom=nomOrigine;
	while(1)
	{
		rep=ES->EntrerNom("Modifier le Nom en  ","",newNom);
		if(rep==false) return;
		if(newNom==nomOrigine) return;

		ens=V_Ensemble->trouve(newNom);
		if(ens)
		{
			//sprintf(buf," %s  Existe déjà",newNom);
			sprintf(buf," %s  L_Existe.c_str()",newNom);
			ShowMessage(buf);
		}
		else break;
	}
//    EnsembleFrm->EdNomEnsemble->Text=newNom;
	EnsembleFrm->LabEnsemble->Caption=newNom;
	EnsembleFrm->Ensemble->Nom=newNom;//300902
	EnsembleFrm->AFaire=MODIFIER;
	EnsembleFrm->VoirEnsemble();
	EnsembleFrm->Show();
	EnsembleFrm->LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::BtVarianteClick(TObject *Sender)
{
	ShowMessage("A reprendre");
	//remettre btVarianteClick
}
/*
 int n;
 CL_Ensemble *ensemble;
 int r=GrilleEns->Row;
 ensemble=(CL_Ensemble*)GrilleEns->Objects[0][r];
 EnsembleEnCours=EnsembleFrm->Ensemble;

 if(ensemble==NULL)
 {
 ShowMessage("Pas de choix d'ensemble");
 return;
 }

 TVVarianteEnsFrm->Ensemble=ensemble;//agri->Ancetre;
 Forme0Frm->CreeTVVarianteEnsemble(TVVarianteEnsFrm->TV,ensemble->Ancetre->Ensemble);
 TVVarianteEnsFrm->Show();
 /*
 NouvAgriFrm->Origine=0;
 NouvAgriFrm->AFaire=VARIANTE;
 NouvAgriFrm->Agri=agri->Ancetre;
 NouvAgriFrm->Show();
 //
 }
 */

//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::FormClose(TObject *Sender,
		TCloseAction &Action)
{
	int rep;
	NoteEnsembleFrm->Close();

	if(LabelModifie->Visible==true)
	{
		rep=MessageBox(Handle,T->L_DonModifQ.c_str(),T->L_DonModifT.c_str(),
				//rep=MessageBox(Handle,"Données Modifiées\nVoulez vous conserver","MODIFICATION",
				MB_YESNO|MB_ICONEXCLAMATION);
		LabelModifie->Visible=false;
		switch(rep)
		{
			case IDYES:
			ES->ecrireFichier();
			V_EnsDepart->purge();
			delete V_EnsDepart;
			break;
			case IDNO:
			V_Ensemble->purge();
			delete V_Ensemble;
			V_Ensemble=V_EnsDepart;
			break;
		}
	}
	else
	return;

}

//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::RGVarianteClick(TObject *Sender)
{
	if(RGVariante->ItemIndex==0) //variantes visibles
	AvecVariante=true;
	else
	AvecVariante=false;
	CreeGrilleEns();
}
//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::RGNoteClick(TObject *Sender)
{
	if(RGNote->ItemIndex==0) //Note visible
	NoteEnsembleFrm->Show();
	else
	NoteEnsembleFrm->Close();
}
//----------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::CreeGrilleEns(void)
{
	CL_Ensemble *ens; //, *ancetre;
	AnsiString s;
	int c,r,i;
	int nbEns=0;
	if(AvecVariante==false)
	{
		for(i=0;i<V_Ensemble->Nbelt;i++)
		{
			ens=V_Ensemble->Vecteur[i];
			if(ens->EstVariante==false) nbEns++;
		}
	}
	VideGrille(GrilleEns);
	// nb row
	if(V_Ensemble->Nbelt==0)GrilleEns->RowCount=2;
	else
	{
		if(AvecVariante==false) GrilleEns->RowCount=nbEns+1;
		else GrilleEns->RowCount=V_Ensemble->Nbelt+1;
	}
	GrilleEns->ColCount=3;
	//en tete
	r=0;

	c=0;
	GrilleEns->ColWidths[c]=120;
	//GrilleEns->Cells[c][r]="Ensemble";
	GrilleEns->Cells[c][r]=L_Ens;

	c=1;
	GrilleEns->ColWidths[c]=40;
	GrilleEns->Cells[c][r]=L_NbVar;//"Nb Var";

	c=2;
	GrilleEns->ColWidths[c]=40;
	GrilleEns->Cells[c][r]=L_NoVar;//"N° Var";
	TriAlphaEnsemble();

	//ens
	r=1;
	for(i=0;i<V_Ensemble->Nbelt;i++)
	{
		ens=V_Ensemble->Vecteur[i];
		if(ens->EstVariante==true) continue;

		ens->Ancetre->Ensemble=ens;
		ens->Ancetre->No =ens->No;
		if(AvecVariante==false)
		AffEns(ens,r);
		else
		r=AffLesVariantes( ens,ens->Ancetre,r,0);
		r++;
	}
	GrilleEns->Visible=true;
}
//-----------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::VideGrille(TStringGrid *grille)
{
	for(int r=1;r<grille->RowCount;r++)
	{
		grille->Objects[0][r]=NULL;
		for(int c=0;c<grille->ColCount;c++) grille->Cells[c][r]="";
	}
}
//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::AffEns(CL_Ensemble *ens,int r)
{
	AnsiString s;
	int nbVariante;

	GrilleEns->Objects[0][r]=(TObject*)ens;
	GrilleEns->Cells[0][r]=ens->Nom;
	nbVariante=0;
	CombienDeVariante(ens,nbVariante);
	GrilleEns->Cells[1][r]=nbVariante;
}
//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::CombienDeVariante(CL_Ensemble *ens,int &n)
{
	ST_NoEnsemble *variante;
	if(ens->LstVariante->Count==0) return;

	n+=ens->LstVariante->Count;
	for(int i=0;i<ens->LstVariante->Count;i++)
	{
		variante=(ST_NoEnsemble*)ens->LstVariante->Items[i];
		if(variante->Ensemble==NULL) continue; //220501
		CombienDeVariante(variante->Ensemble,n);
	}
}
//---------------------------------------------------------------------------
int __fastcall TGereEnsembleFrm::AffLesVariantes(CL_Ensemble *ens,ST_NoEnsemble *ancetre,
		int r,int nP)
{
	ST_NoEnsemble *variante;
	ens->Ancetre=ancetre;
	AffEns(ens,r);
	ens->NoVariante=nP;
	GrilleEns->Cells[2][r]=AnsiString(nP);
	if(ens->LstVariante->Count==0) return r;

	nP=nP*10;
	for(int i=0;i<ens->LstVariante->Count;i++)
	{
		variante=(ST_NoEnsemble*)ens->LstVariante->Items[i];
		r++;
		nP++;
		if(variante->Ensemble==NULL) continue; //à vérifier

		r=AffLesVariantes(variante->Ensemble,ancetre,r,nP);
	}
	return r;
}
// je selectionne l'ensemble En cours
//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::GrilleEnsClick(TObject *Sender)
{
	TGridRect selection;
	int cX=GrilleEns->ColCount;
	int r=GrilleEns->Row;
	CL_Ensemble *ensemble;
	ensemble=(CL_Ensemble*)GrilleEns->Objects[0][r];
	EnsembleEnCours=ensemble;
	NoteEnsembleFrm->Ensemble=ensemble;
	if(RGNote->ItemIndex==0)
	NoteEnsembleFrm->Show();
	selection.Left=0;
	selection.Right=cX;
	selection.Top=r;
	selection.Bottom=r;
	GrilleEns->Selection=selection;

}
//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::TrouveEnCours(void)
{
	TGridRect selection;
	int cX=GrilleEns->ColCount;
	int r;
	CL_Ensemble *ensemble;
	bool trouve=false;

	for(r=0;r<GrilleEns->RowCount;r++)
	{
		ensemble=(CL_Ensemble*)GrilleEns->Objects[0][r];
		if(ensemble==NULL) continue;
		if(ensemble==EnsembleEnCours) {trouve=true; break;}
	}
	if(trouve==false) return;

	NoteEnsembleFrm->Ensemble=ensemble;
	if(RGNote->ItemIndex==0)
	NoteEnsembleFrm->Show();
	selection.Left=0;
	selection.Right=cX;
	selection.Top=r;
	selection.Bottom=r;
	GrilleEns->Selection=selection;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::TriAlphaEnsemble(void)
{
	int i,j;
	CL_Ensemble *ens,*ens0;
	for(i=0;i<V_Ensemble->Nbelt;i++)
	{
		ens0=V_Ensemble->Vecteur[i];
		if(ens0->EstVariante==true) continue;

		for(j=i+1;j<V_Ensemble->Nbelt;j++)
		{
			ens=V_Ensemble->Vecteur[j];
			if(ens->EstVariante==true) continue;

			if(ens->Nom.AnsiCompare(ens0->Nom)<0)
			{
				V_Ensemble->Vecteur[i]=ens;
				V_Ensemble->Vecteur[j]=ens0;
				ens0=ens;
			}
		}
	}
}
// cree une exploitation total par addition pondérée des composants ses exploitations individuelles
//---------------------------------------------------------------------------
void __fastcall TGereEnsembleFrm::BtUneExpClick(TObject *Sender)
{
	int r=GrilleEns->Row;
//CL_AgriEff *agriEff;
	CL_Agriculteur *agri;

	if(V_Ensemble->Nbelt==0)return;
	// on cree une exploitation total
	Global=TOTAL;

	EnsembleFrm->Ensemble=(CL_Ensemble*)GrilleEns->Objects[0][r];

//    agriEff=EnsembleFrm->Ensemble->V_AgriEff->Vecteur[0];
	// pour connaitre l'annee de debut de la simulation
	// il faudra faire le test dans la definition des ensembles
	AgriSaisieFrm->TypeAgreg=TOTAL;
	agri=AgriSaisieFrm->Agrege(EnsembleFrm->Ensemble);//!!!!!!!!!!!!!!
	if(agri==NULL) return;

	AgriSaisieFrm->Agri=agri;

	NoteAgriFrm->Close();
	AgriSaisieFrm->Origine=0;
	AgriSaisieFrm->Show();
}
//crée une exlotation moyenne
//---------------------------------------------------------------------------

void __fastcall TGereEnsembleFrm::BtUneMoyClick(TObject *Sender)
{
	int r=GrilleEns->Row;
//CL_AgriEff *agriEff;
	CL_Agriculteur *agri;

	if(V_Ensemble->Nbelt==0)return;
	// on cree une exploitation total
	Global=MOYENNE;

	EnsembleFrm->Ensemble=(CL_Ensemble*)GrilleEns->Objects[0][r];

//    agriEff=EnsembleFrm->Ensemble->V_AgriEff->Vecteur[0];
	// pour connaitre l'annee de debut de la simulation
	// il faudra faire le test dans la definition des ensembles
	AgriSaisieFrm->TypeAgreg=MOYENNE;
	agri=AgriSaisieFrm->Agrege(EnsembleFrm->Ensemble);//!!!!!!!!!!!!!!
	if(agri==NULL) return;

	AgriSaisieFrm->Agri=agri;

	NoteAgriFrm->Close();
	AgriSaisieFrm->Origine=0;
	AgriSaisieFrm->Show();
}
//---------------------------------------------------------------------------
void TGereEnsembleFrm::TexteChaine(void) {
	L_Existe = T->TrouveCaption("GereEnsemble", "L_Existe");
	L_Ens = T->TrouveCaption("GereEnsemble", "L_Ens");
	L_NbVar = T->TrouveCaption("GereEnsemble", "L_NbVar");
	L_NoVar = T->TrouveCaption("GereEnsemble", "L_NoVar");
	L_ACopierSous = T->TrouveCaption("GereEnsemble", "L_ACopierSous");

}

//--------------------------------------------
void TGereEnsembleFrm::IniCaption(void) {
	BtUneMoy->Caption = LC_BtUneMoy;
	BtUneExp->Caption = LC_BtUneExp;
	BtCopier->Caption = T->LC_BtBnCopier;
	BtEffectif->Caption = T->LC_BtEffectif;
	GereEnsembleFrm->Caption = T->LC_GereEnsembleFrm;
	LabelModifie->Caption = T->LC_LabelModifie_A;
	RGNote->Caption = T->LC_BtBnNotes;
	BtNouveau->Caption = T->LC_BtNouveau;
	BtRenomme->Caption = LC_BtRenomme;
	BtResultat->Caption = T->LC_BtBnResultat;
	BtSupprimer->Caption = T->LC_BtBnSupBesTrav;
	RGVariante->Caption = T->LC_BtVariante;

	//100206
	RGVariante->Items->Strings[0] = T->LC_Visible;
	RGVariante->Items->Strings[1] = T->LC_NonVisible;
	RGNote->Items->Strings[0] = T->LC_Visible;
	RGNote->Items->Strings[1] = T->LC_NonVisible;

}
//--------------------------------------------
void TGereEnsembleFrm::TexteCaption(void) {
	LC_BtUneMoy = T->TrouveCaption("GereEnsemble", "LC_BtUneMoy");
	LC_BtUneExp = T->TrouveCaption("GereEnsemble", "LC_BtUneExp");
	LC_BtBnCopier = T->TrouveCaption("CL_Trad", "LC_BtBnCopier");
	LC_BtEffectif = T->TrouveCaption("CL_Trad", "LC_BtEffectif");
	LC_GereEnsembleFrm = T->TrouveCaption("CL_Trad", "LC_GereEnsembleFrm");
	LC_LabelModifie_A = T->TrouveCaption("CL_Trad", "LC_LabelModifie_A");
	LC_BtBnNotes = T->TrouveCaption("CL_Trad", "LC_BtBnNotes");
	LC_BtNouveau = T->TrouveCaption("CL_Trad", "LC_BtNouveau");
	LC_BtRenomme = T->TrouveCaption("GereEnsemble", "LC_BtRenomme");
	LC_BtBnResultat = T->TrouveCaption("CL_Trad", "LC_BtBnResultat");
	LC_BtBnSupBesTrav = T->TrouveCaption("CL_Trad", "LC_BtBnSupBesTrav");
	LC_BtVariante = T->TrouveCaption("CL_Trad", "LC_BtVariante");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TGereEnsembleFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=1690;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

void __fastcall TGereEnsembleFrm::BtBnAideClick(TObject *Sender)
{
	HelpContext=1690;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
}
//---------------------------------------------------------------------------

