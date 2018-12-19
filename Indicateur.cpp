//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "Olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "FichierLire.h"
#include "Brouillon.h"
#include "GereIndic.h"
#include "Erreur.h"
#include "Forme0.h"
#include "Forme01.h"
#include "DefEtatSortie.h"
#include "Compilateur.h"
#include "TVDico.h"
#include "LBChoixMC.h"
#include "Resultat.h"
//#include "Graph.h"111002
#include "ResGraph.h"
//#include "Brouillon.h"
#include "SortieEcran.h"  //a supprimer
#include "QRMemo.h"

#include "AgriSaisie.h"
#include "CL_Trad.h"
#include "NoteAgri.h"
#include "Aide.h"

#include "Indicateur.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme0"
#pragma resource "*.dfm"
TIndicateurFrm *IndicateurFrm;
extern CL_ES *ES;
extern CL_Compil *Compil;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TIndicateurFrm::TIndicateurFrm(TComponent* Owner) :
		TForme0Frm(Owner) {
//ShowMessage("Indicateur");
}
//---------------------------------------------------------------------------
void __fastcall TIndicateurFrm::FormActivate(TObject *Sender)
{
//bool complet=false;
	if(Origine==0)
	{
		GereIndicFrm->Origine=2;
		Origine=1; //cf courbe
		//ES->AgriEnCours=AgriEnCours;
		ES->IniV_Elt();//060105
		Forme0Frm->CreeTVToutElt(TVDicoFrm->TV,AgriEnCours,true);//010506
		if(AgriEnCours)
		CompleteV_Elt(AgriEnCours);

	}
}
//---------------------------------------------------------------------------
void __fastcall TIndicateurFrm::AffIndicateur(void)
{
	bool comp=Indicateur->Compile;
	bool calc=Indicateur->Calcule;

	Compil->ReEcritFormule(Indicateur->Prog);
	Edit->Text=Indicateur->Prog->Source;
	LabIndicateur->Caption=Indicateur->Nom;
//    EdIndicateur->Text=Indicateur->Nom;
	// Annule les effets de EditChange

	LabelModifie->Visible=false;
	//300902
	if(Indicateur->Supprimable==false) LabSupprimable->Visible=true;
	else LabSupprimable->Visible=false;
	Indicateur->Compile=comp;
	Indicateur->Calcule=calc;

//    PossibleModifier(false);

}
//---------------------------------------------------------------------------
//             choix d'un elt
//---------------------------------------------------------------------------
void __fastcall TIndicateurFrm::BtBnDicoClick(TObject *Sender)
{
	TVDicoFrm->Complet=true;
	if(TVDicoFrm->Visible==true)
	TVDicoFrm->Close();
	else
	{
		//rustine 110306
		TVDicoFrm->BtBnRafraichirClick(this);
		TVDicoFrm->Show();
	}
}
//---------------------------------------------------------------------------
//             choix d'un mot cle
//---------------------------------------------------------------------------
void __fastcall TIndicateurFrm::BtBnMotCleClick(TObject *Sender)
{
//	LBChoixMCIndFrm->Visible=!LBChoixMCIndFrm->Visible;
	LBChoixMCFrm->Visible=!LBChoixMCFrm->Visible;
}
//---------------------------------------------------------------------------
// modif possible oui non
//---------------------------------------------------------------------------
void __fastcall TIndicateurFrm::RGModifiableClick(TObject *Sender)
{
	if(RGModifiable->ItemIndex==0)
	{
		RGModifiable->Color=clRed;
		Edit->ReadOnly=true;
	}
	else
	{
		RGModifiable->Color=clLime;
		Edit->ReadOnly=false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TIndicateurFrm::PossibleModifier(bool modifiable)
{
	if(modifiable==false)
	{
		RGModifiable->ItemIndex=0;
		RGModifiable->Color=clRed;
		Edit->ReadOnly=true;
	}
	else
	{
		RGModifiable->ItemIndex=1;
		RGModifiable->Color=clLime;
		Edit->ReadOnly=false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TIndicateurFrm::BtBnStockerClick(TObject *Sender)
{
//	Stocker();
}
//---------------------------------------------------------------------------
bool __fastcall TIndicateurFrm::Compiler(void)
{
	Compil->Erreur=false;
	Compil->Compiler(Edit->Text.c_str());
	//test ////////
//ofstream outfile("compil.txt");//!!!!!
//Compil->ecrireArbre(outfile );
	// ///////////
	if(Compil->Erreur==false)//il n'y a pas d'erreur
	{
		delete Indicateur->Prog->Arbre; Indicateur->Prog->Arbre=NULL;
		delete Indicateur->Prog->Reseau;Indicateur->Prog->Reseau=NULL;
		Indicateur->Prog->Arbre=new CL_Arbre(Compil->Arbre);
		if(Compil->Reseau->MailleX)
		Indicateur->Prog->Reseau=new CL_Reseau(Compil->Reseau);
		Indicateur->Compile=true;
		return true;
	}
	else
	return false;
}
//-----------------------------------------------------------------------
void __fastcall TIndicateurFrm::BtBnResultatClick(TObject *Sender)
{
	bool rep;
	AnsiString titre;
	ErreurFrm->Close();
	rep=Calculer();
	if(rep==false) return;

	Forme01Frm->Origine=0;
	Forme01Frm->UtilisePar="indicateur";
	titre=AnsiString("Indicateur: ")+Indicateur->Nom;
	Forme01Frm->Show();
	Forme01Frm->IniGrilleStandard(titre,10,1,AgriEnCours->DefSim->An_0);
	Forme01Frm->EcrireLigne(Indicateur->Nom,Indicateur->Valeur);
}
//---------------------------------------------------------------------------
bool __fastcall TIndicateurFrm::Calculer(void)
{
	char flag;
	if(Indicateur->Compile==false)
	{
		if(Compiler()==false )return false;
		else Indicateur->Compile=true;
	}
	if(AgriEnCours==NULL) //130302
	{
		ShowMessage("Pas d'agriculteur sélectionné");
		return false;
	}
	//rustine
	//dans TAgriSaisieFrm::Calcul0  j'ai mis indic->Flag =true/false
	//	    V_Indicateur->FlagMisA(false);
	//nécessité de le conserver
	// sinon on peut stocker une nouvelle fois
	flag=Indicateur->Flag;
	AgriSaisieFrm->Calcul0(AgriEnCours);//130302
	//ES->IniV_Elt(); c'est fait ds calcul0 ??               //060105
	//if(AgriEnCours)
	//CompleteV_Elt(AgriEnCours);

	Forme0Frm->CreeTVToutElt(TVDicoFrm->TV,AgriEnCours,true);
	Forme0Frm->CreeTVIndicateur(GereIndicFrm->TV);
	Indicateur->Flag=flag;

	/*//........
	 int n;
	 ST_Branche branche;
	 char chaine[100];
	 CL_Arbre *Arbre=Indicateur->Prog->Arbre;
	 ErreurFrm->Edit->Lines->Add("Arbre");
	 for(n=0;n<Arbre->BrancheX;n++)
	 {
	 branche=Arbre->LesBranches[n];

	 sprintf(chaine,"%3d %3d     %3d  %3d   %6.2f",
	 n,branche.code,branche.arg[0],branche.arg[1],branche.arg[2],
	 branche.valeur);
	 ErreurFrm->Edit->Lines->Add(chaine);
	 }
	 ErreurFrm->Show();

	 //........*/
	Compil->Calculer(Indicateur->Prog->Reseau,Indicateur->Prog->Arbre,0,N_X,Indicateur->Valeur);
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TIndicateurFrm::BtBnCourbeClick(TObject *Sender)
{
	if(Calculer()==false) return;

	Elt.Nom=Indicateur->Nom.c_str();
	Elt.Valeur=Indicateur->Valeur;

	ResultatFrm->LBGauche->Clear();
	ResultatFrm->LBGauche->Items->AddObject(Elt.Nom,(TObject*)&Elt);

	ResGraphFrm->AnDebut=AgriEnCours->DefSim->An_0; //230908
	ResGraphFrm->Origine=0;//151002
	ResGraphFrm->Show();
//
//   GraphiqueFrm->Demarrer();  111002

}
//---------------------------------------------------------------------------
void __fastcall TIndicateurFrm::EditChange(TObject *Sender)
{
	LabelModifie->Visible=true;
	if(Indicateur==NULL) return; //170902
	Indicateur->Compile=false;
	Indicateur->Calcule=false;
}
//------------------------------------------------------------------------------
//121201
/*
 int rep;
 if(LabelModifie->Visible==true)
 {
 rep=MessageBox(Handle,T->L_DonModifQ.c_str(),T->L_Modif.c_str(),//"MODIFICATION",
 //rep=MessageBox(Handle,L_DonModifQ.c_str()"Données Modifiées\nVoulez vous conserver","MODIFICATION",
 MB_YESNOCANCEL|MB_ICONEXCLAMATION);
 if(rep==ID_YES)
 {
 if(Compiler()==false) { CanClose=false;return;}

 if( Indicateur->Flag==NOUVEAU)
 {
 V_Indicateur->ins(Indicateur);
 ES->IniV_Elt();                //060105
 if(AgriEnCours)
 CompleteV_Elt(AgriEnCours);
 Forme0Frm->CreeTVToutElt(TVDicoFrm->TV,AgriEnCours,true);
 Forme0Frm->CreeTVIndicateur(GereIndicFrm->TV);
 }
 }
 else
 return;
 }

 //stockage
 //    Indicateur->Prog->Source=Edit->Text;
 //    ES->ecrireFichier();

 Edit->Modified=false;
 LabelModifie->Visible=false;

 CanClose=true;
 TVDicoFrm->Visible=false;
 LBChoixMCFrm->Visible=false;

 }
 */
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TIndicateurFrm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	int rep;
	CanClose=false;
	if(LabelModifie->Visible==true)
	{
		rep=MessageBox(Handle,T->L_DonModifQ.c_str(),T->L_Modif.c_str(), //"MODIFICATION",
				//rep=MessageBox(Handle,L_DonModifQ.c_str()"Données Modifiées\nVoulez vous conserver","MODIFICATION",
				MB_YESNOCANCEL|MB_ICONEXCLAMATION);
		if(rep==ID_YES)
		{
			if(Compiler()==false) {CanClose=false;return;}

			if( Indicateur->Flag==NOUVEAU)
			{
				V_Indicateur->ins(Indicateur);
				ES->IniV_Elt(); //060105
				if(AgriEnCours)
				CompleteV_Elt(AgriEnCours);
				Forme0Frm->CreeTVToutElt(TVDicoFrm->TV,AgriEnCours,true);
				Forme0Frm->CreeTVIndicateur(GereIndicFrm->TV);
				Indicateur->Flag=EXISTE;
			}
		}
		else
		{
			CanClose=true;
			return;
		}
	}

	//stockage
//    Indicateur->Prog->Source=Edit->Text;
//    ES->ecrireFichier();

	Edit->Modified=false;
	LabelModifie->Visible=false;

	CanClose=true;
	TVDicoFrm->Visible=false;
	LBChoixMCFrm->Visible=false;

}
/*
 //inutile
 //---------------------------------------------------------------------------
 void __fastcall TIndicateurFrm::Stocker(void)
 {
 ShowMessage("qui appelle stocker Indicateur");
 if(Indicateur==NULL) return;

 if(Edit->Modified==false) return;

 if(Compiler()==false) return;

 if( Indicateur->Flag==true)
 V_Indicateur->ins(Indicateur);

 //stockage
 Indicateur->Prog->Source=Edit->Text;
 ES->ecrireFichier();
 Edit->Modified=false;
 LabelModifie->Visible=false;

 return ;
 }
 */
//---------------------------------------------------------------------------
void __fastcall TIndicateurFrm::BtBnImpClick(TObject *Sender)
{
	AnsiString s;
	int n;
	QRMemoFrm->NomAgri->Caption=AgriEnCours->Nom;
	QRMemoFrm->TitreEtat->Caption=AnsiString("Indicateur: ")+ Indicateur->Nom;

	QRMemoFrm->RE->Lines->Clear();
	for(n=0;n<Edit->Lines->Count;n++)
	{
		s=Edit->Lines->Strings[n];
		QRMemoFrm->RE->Lines->Add(s);
	}
	QRMemoFrm->QR->Preview();
}
//---------------------------------------------------------------------------
void __fastcall TIndicateurFrm::EditMouseDown(TObject *Sender,
		TMouseButton Button, TShiftState Shift, int X, int Y)
{
//	Edit->SelStart=Edit->Text.Length(); //121103
}
//---------------------------------------------------------------------------

void __fastcall TIndicateurFrm::EditEnter(TObject *Sender)
{
	Edit->SelStart=Edit->Text.Length(); //121103

}
//---------------------------------------------------------------------------

void __fastcall TIndicateurFrm::BtBnVideToutClick(TObject *Sender)
{
	int repMB;
	if(RGModifiable->ItemIndex==0) return; //310105

	repMB=MessageBox(Handle,"j'efface tout ?","NETTOYER",MB_YESNO|MB_ICONQUESTION);
	if(repMB==IDNO) return;

	Edit->Clear();
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------

//--------------------------------------------
void TIndicateurFrm::IniCaption(void) {
	BtBnCourbe->Caption = T->LC_BtBnCourbe;
	BitBtn1->Caption = T->LC_BtDico;
	LabIndicateur->Caption = T->LC_LabIndicateur;
	IndicateurFrm->Caption = T->LC_GBAtelier_A;
	RGModifiable->Caption = T->LC_RGModifiable;
	LabelModifie->Caption = T->LC_LabelModifie_A;
	BtBnMotCle->Caption = T->LC_BtMotCle;
	BtBnResultat->Caption = T->LC_BtBnResultat;
	LabSupprimable->Caption = T->LC_LabUtilise;
	RGModifiable->Items->Strings[0] = T->LC_Oui;
	RGModifiable->Items->Strings[1] = T->LC_Non;

}
//--------------------------------------------
void TIndicateurFrm::TexteCaption(void) {
	LC_BtBnCourbe = T->TrouveCaption("CL_Trad", "LC_BtBnCourbe");
	LC_BtDico = T->TrouveCaption("CL_Trad", "LC_BtDico");
	LC_LabIndicateur = T->TrouveCaption("CL_Trad", "LC_LabIndicateur");
	LC_GBAtelier_A = T->TrouveCaption("CL_Trad", "LC_GBAtelier_A");
	LC_RGModifiable = T->TrouveCaption("CL_Trad", "LC_RGModifiable");
	LC_LabelModifie_A = T->TrouveCaption("CL_Trad", "LC_LabelModifie_A");
	LC_BtMotCle = T->TrouveCaption("CL_Trad", "LC_BtMotCle");
	LC_BtBnResultat = T->TrouveCaption("CL_Trad", "LC_BtBnResultat");
	LC_LabUtilise = T->TrouveCaption("CL_Trad", "LC_LabUtilise");

	IniCaption();

}
//---------------------------------------------------------------------------

void __fastcall TIndicateurFrm::BtBnNotesClick(TObject *Sender)
{
//020507
	NoteAgriFrm->VientDe="Indicateur";//ne pas traduire
	NoteAgriFrm->Indicateur=Indicateur;
	NoteAgriFrm->Memo->Text=Indicateur->Notes;
	NoteAgriFrm->Caption=Indicateur->Nom;

	NoteAgriFrm->Show();

}
//---------------------------------------------------------------------------

bool __fastcall TIndicateurFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=1790;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

void __fastcall TIndicateurFrm::BtBnAideClick(TObject *Sender)
{
	HelpContext=1790;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);

}
//---------------------------------------------------------------------------

