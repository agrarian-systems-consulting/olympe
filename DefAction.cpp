//---------------------------------------------------------------------------

#include <vcl.h>
#include <algorithm>
#include <iostream>
#include <functional>
using namespace std;

#pragma hdrstop

#include "TVDico.h"
#include "LBChoixMCInd.h"

#include "AgriSaisie.h"
#include "LBChoixAction.h"
#include "ActionRemplacer.h"
#include "CL_Trad.h"

#include "DefAction.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDefActionFrm *DefActionFrm;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TDefActionFrm::TDefActionFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TDefActionFrm::FormActivate(TObject *Sender)
{
	int n;
	CL_Regle *regle;
	CL_Action *action;
	DefGrille();

	//Definir();
	regle=new CL_Regle();
	REdit->Text=regle-> TxtCondition;

	for(n=0;n<regle->LstAction->Count;n++)
	{
		action=(CL_Action*)regle->LstAction->Items[n];
		action->AffGrille(SG,n+1);
	}

//	regle->AffGrille(TStringGrid *SG);
	/* a remettre
	 if(Global!=ENSEMBLE)           // on travaille pour un agri
	 {
	 if(AgriEnCours)
	 AgriSaisieFrm->Calcul0(AgriEnCours);
	 }
	 else //Global=ENSEMBLE         on travaille pour un ensemble
	 {
	 if(EnsembleEnCours)
	 AgriSaisieFrm->CalculEnsemble(EnsembleEnCours);
	 }
	 */
}
//---------------------------------------------------------------------------
void __fastcall TDefActionFrm::SGClick(TObject *Sender)
{
//si colonne 0 choisir action
//si colonne 1 définir ou modifier Action

//               si vide activer  TVAction
//               sinon  activer grille de saisie de l'action
	int c=SG->Col;
	int r=SG->Row;
	CL_Action *action;
	if(r==0) return;
	if(c==0)//definir type action
	{
//        if(SG->Objects[0][r]==NULL)
		LBChoixActionFrm->Show();
	}
	if(c==1) //definir action
	{
		action=(CL_Action*)SG->Objects[0][r];
		if(action==NULL) return; //a voir
		action->SaisieAction();
		//ActionRemplacerFrm->Show();
	}
}
//---------------------------------------------------------------------------
void __fastcall TDefActionFrm::BtDicoClick(TObject *Sender)
{
	TVDicoFrm->Origine=ACTION;
	if(TVDicoFrm->Visible==true)
	TVDicoFrm->Close();
	else
	TVDicoFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TDefActionFrm::BtMotCleClick(TObject *Sender)
{
	LBChoixMCIndFrm->Visible=!LBChoixMCIndFrm->Visible;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TDefActionFrm::DefGrille(void)
{
	int r;
//CL_Act *action;
//CL_Act_Atelier *culture0,*culture1;
	SG->ColWidths[0]=96;
	SG->ColWidths[1]=Width-SG->ColWidths[0]-40;//24;

	SG->RowHeights[0]=24;
	for(r=1;r<SG->RowCount;r++)
	SG->RowHeights[r]=24*2;//*2;
	SG->Cells[0][0]=T->L_Act_Action;//"ACTION";
	SG->Cells[1][0]=T->L_Act_DescAction;//"Description de l'action";
}
//---------------------------------------------------------------------------
void __fastcall TDefActionFrm::BtBnQuitterClick(TObject *Sender)
{
	int rep;
	rep=MessageBox(Handle,T->L_QuitQ.c_str(),T->L_QuitT.c_str(),
			//rep=MessageBox(Handle,"Vous voulez vraiment quitter","QUITTER OLYMPE",
			MB_YESNO|MB_ICONEXCLAMATION);

	if(rep==IDYES) Application->Terminate();

	else return;
}
//---------------------------------------------------------------------------

void __fastcall TDefActionFrm::SGDrawCell(TObject *Sender, int ACol,
		int ARow, TRect &Rect, TGridDrawState State)
{
	int i;
	int NbLigne;
	int hautTexte;
	TMemo *memo;
	TRect R = Rect;
	AnsiString as;
	if(ACol!=1) return;
	if(ARow==0)return;
	if(ARow>3) return; //?????

	//memo=(TMemo*)SG->Objects[ACol][ARow];
	//if(memo==NULL)
	//{
	memo=new TMemo(this);
	memo->Parent=this;
	//    SG->Objects[ACol][ARow]=memo;
	//}
	memo->Lines->Text=SG->Cells[ACol][ARow];

	memo->Width=SG->ColWidths[ACol];
	hautTexte=(Rect.Bottom-Rect.Top)/4;// je prévois en général 4 lignes max si plus devrait roulotter a verfier

	NbLigne=memo->Lines->Count;
	if(NbLigne==0)
	return;

	for (i = 0; i <NbLigne; i++)
	{
		as = memo->Lines->Strings[i];
		R.Top = Rect.Top + i * hautTexte;
		R.Bottom = R.Top + hautTexte;
		SG->Canvas->TextRect(R,R.Left,R.Top,as);
	}
	delete memo;
}
//---------------------------------------------------------------------------
// constructeur pour regle
//---------------------------------------------------------------------------
CL_Regle::CL_Regle(void) {
	CL_Action *action;
	CL_Atelier *culture0, *culture1;
//int n;

	Nom = T->L_Act_Reg1; //"Règle 1");
	No = 1;
	TxtCondition = AnsiString(" N >=2");

	LstAction = new TList;
	/*
	 //action de remplacer
	 n=0;
	 while(1)
	 {
	 culture0=V_Culture->trouve(n++);
	 if(culture0) break;
	 }
	 while(1)
	 {
	 culture1=V_Culture->trouve(n++);
	 if(culture1) break;
	 }
	 */
	//cree action remplacer
	action = new CL_Action(REMPLACER, culture0->No, culture1->No, 20); //remplacer cult0 par cult1 sur 20%surface
	LstAction->Add(action);

	//cree actions bidon pour test
	action = new CL_Action(INVESTIR,
			"Investir  100 000 \n Amortissement 5 ans linéaire ");
	LstAction->Add(action);

	action = new CL_Action(EMPRUNTER,
			"Emprunter LT 50 000\n  taux 6% durée 5 ans");
	LstAction->Add(action);

	action = new CL_Action(ABSORBERSURFACE, "Absorber  25% Surface  ExplB");
	LstAction->Add(action);

	action = new CL_Action(ABSORBERTOTALITE, "AbsorberTotalité 10% ExplC");
	LstAction->Add(action);
}
//---------------------------------------------------------------------------
// constructeur pour test
//---------------------------------------------------------------------------
CL_Action::CL_Action(int nature, char *chaine) {
	Maz();
	Nature = nature;
	Chaine = chaine;
}
//---------------------------------------------------------------------------
// constructeur pour remplacement    A voir
//---------------------------------------------------------------------------
CL_Action::CL_Action(int nature, int Remplacee, int Remplacante, float Pc) {
	Maz();
	Nature = REMPLACER;
	LesInt[0] = Remplacee;
	LesInt[1] = Remplacante;
	LesFloat[0] = Pc;
}
//---------------------------------------------------------------------------
void CL_Action::Maz(void) {
	memset(LesInt, 0, sizeof(LesInt));
	memset(LesFloat, 0, sizeof(LesFloat));
}
//---------------------------------------------------------------------------
AnsiString CL_Action::DonneNom(void) {
	switch (Nature) {
	case REMPLACER:
		return T->L_Act_Remplacer; //"Remplacer";
	case SUPPRIMER:
		return T->L_Act_Supprimer; //"Supprimer";
	case PLANTER:
		return T->L_Act_Planter; //"Planter";
	case ARRACHER:
		return T->L_Act_Arracher; //"Arracher";
	case INVESTIR:
		return T->L_Act_Investir; //"Investir";
	case EMPRUNTER:
		return T->L_Act_Emprunter; //"Emprunter";
	case ABSORBERSURFACE:
		return "Absorber Surface";
	case ABSORBERTOTALITE:
		return "Absorber Totalite";

	default:
		return "???????????";
	}
}
//---------------------------------------------------------------------------
void CL_Action::AffGrille(TStringGrid *SG, int r) {
	SG->Objects[0][r] = (TObject*) this;
	SG->Cells[0][r] = DonneNom();
	SG->Cells[1][r] = DonneDetail();
}
//---------------------------------------------------------------------------
//DonneDetail
//---------------------------------------------------------------------------
AnsiString CL_Action::DonneDetail(void) {
	switch (Nature) {
	case REMPLACER:
		return this->DetailRemplacer();
	default:
		return AnsiString(Chaine);
	}

}
//---------------------------------------------------------------------------
AnsiString CL_Action::DetailRemplacer(void) {
	AnsiString as;
	return as;
	/*
	 AnsiString as;
	 int noCulture0,noCulture1;
	 //CL_Act_Atelier *culture0,*culture1;
	 noCulture0=LesInt[0];
	 noCulture1=LesInt[1];

	 culture0=V_Culture->trouve(noCulture0);
	 culture1=V_Culture->trouve(noCulture1);

	 as=  AnsiString("Remplacer  ")
	 + AnsiString(LesFloat[0])
	 + " %  "
	 +culture0->Nom
	 + "  "
	 +"Par  "
	 +culture1->Nom
	 +"\n                    ";

	 as="Remplacer 10% blé par mais";
	 return as;
	 */
}
//---------------------------------------------------------------------------
//SaisieAction
//---------------------------------------------------------------------------
void CL_Action::SaisieAction(void) {
	switch (Nature) {
	case REMPLACER:
		//           ActionRemplacerFrm->action=this;
		ActionRemplacerFrm->Show();
		break;
	default:
		return;
	}

}
//--------------------------------------------
void TDefActionFrm::IniCaption(void) {
	GBAction->Caption = LC_GBAction;
	GBCondition->Caption = T->LC_GBCondition;
	DefActionFrm->Caption = LC_DefActionFrm;
	BtDico->Caption = T->LC_BtDico;
	LabelModifie->Caption = T->LC_LabelModifie_A;
	BtMotCle->Caption = T->LC_BtMotCle;
	BtBnQuitter->Caption = T->LC_BtBnQuitter;
	LabRegle->Caption = LC_LabRegle;
}
//--------------------------------------------
void TDefActionFrm::TexteCaption(void) {
	LC_GBAction = T->TrouveCaption("DefAction", "LC_GBAction");
	LC_GBCondition = T->TrouveCaption("CL_Trad", "LC_GBCondition");
	LC_DefActionFrm = T->TrouveCaption("DefAction", "LC_DefActionFrm");
	LC_BtDico = T->TrouveCaption("CL_Trad", "LC_BtDico");
	LC_LabelModifie_A = T->TrouveCaption("CL_Trad", "LC_LabelModifie_A");
	LC_BtMotCle = T->TrouveCaption("CL_Trad", "LC_BtMotCle");
	LC_BtBnQuitter = T->TrouveCaption("CL_Trad", "LC_BtBnQuitter");
	LC_LabRegle = T->TrouveCaption("DefAction", "LC_LabRegle");

	IniCaption();

}

/*

 L_Act_Action=           "ACTION";
 L_Act_DescAction=       "Description de l'action";
 L_Act_Reg1=             "Règle 1";
 L_Act_Remplacer=        "Remplacer";
 L_Act_Supprimer=        "Supprimer";
 L_Act_Planter=          "Planter";
 L_Act_Arracher=         "Arracher";
 L_Act_Investir=         "Investir";
 L_Act_Emprunter=        "Emprunter";

 */
