//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Main.h"
#include "AgriSaisieEnum.h"
#include "AgriSaisie.h"
#include "InvAni.h"
#include "CL_Trad.h"
#include "Aide.h"
#include "LBChoix.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLBChoixFrm *LBChoixFrm;
extern CL_Trad *T;

// utilisé dans AgriSaisie
//---------------------------------------------------------------------------
__fastcall TLBChoixFrm::TLBChoixFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TLBChoixFrm::FormActivate(TObject *Sender)
{
	LaGrille= AgriSaisieFrm->LaGrille;
//    if(LaGrille==NULL) return;   //bug mysterieux
	Memo= AgriSaisieFrm->Memo;
	Top= LaGrille->Top+40;
}
//---------------------------------------------------------------------------
void __fastcall TLBChoixFrm::LBClick(TObject *Sender)
{
//int n;
//int rep;
//CL_Valeur  *valeur;
//CL_Item    *item;

	if(AgriSaisieFrm->RGModifiable->ItemIndex==0)return;
	switch(LaGrille->Tag)
	{
		case GAni:
		case GVariable:
		LBClickValeur();break;
		case GExtNeg:
		case GExtPos:
		case GRecDiv:
		case GDepDiv:
		case GRecFam:
		case GDepFam:
		LBClickFormule();break;
		case GImmo:
		LBClickTvaImmo();break;
		case GPetit:
		LBClickTvaPetit();break;
		default:ShowMessage("LBChoix Oubli");break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TLBChoixFrm::LBClickValeur(void)
{
	int n;
	int rep;
	CL_Valeur *valeur;
	CL_Item *item;
	int r=LaGrille->Row;
	int c=LaGrille->Col;
	AnsiString s;
	if(c!=2) return;

	n=LB->ItemIndex;
	s=LB->Items->Strings[n];
	if(s=="[...]")
	{
		switch(LaGrille->Tag)
		{
			case GAni: MainForm->NouvelleDefinition(ANIMAUX); break;
			case GVariable:MainForm->NouvelleDefinition(VARIABLE);break;
			case GRecFam: MainForm->NouvelleDefinition(RECFAM);break;
			case GDepFam: MainForm->NouvelleDefinition(DEPFAM);break;
			case GDepDiv: MainForm->NouvelleDefinition(DEPDIV);break;
			case GRecDiv: MainForm->NouvelleDefinition(RECDIV);break;
			default:ShowMessage("Oubli LBClickFormule");

		}
		return;
	}
	valeur=(CL_Valeur*)LaGrille->Objects[0][r];

	if(valeur==NULL)
	{
		valeur=new CL_Valeur();
		valeur->Flag='N';
		LaGrille->Objects[0][r]=(TObject*)valeur;
		LaGrille->Cells[0][r]=r;
	}
	else
	{
		rep=MessageBox(Handle,"A Remplacer ?"," ATTENTION",MB_YESNO|MB_ICONEXCLAMATION);
		if(rep==ID_NO) return;
	}

	if(valeur->Flag!='N')valeur->Flag='M';

	item=(CL_Item*)LB->Items->Objects[n];
	valeur->NoItem= item->No;
	valeur->Item= item;
	LaGrille->Cells[2][r]=item->Nom;

	LaGrille->SetFocus();

}
//---------------------------------------------------------------------------
void __fastcall TLBChoixFrm::LBClickFormule(void)
{
	int n;
	int rep;
	CL_Formule *formule;
	CL_Item *item;
	int r=LaGrille->Row;
	int c=LaGrille->Col;
	AnsiString s;

	if(c!=2) return;
	n=LB->ItemIndex;
	s=LB->Items->Strings[n];
	if(s=="[...]")
	{
		LBChoixFrm->Visible=false;
		switch(LaGrille->Tag)
		{
			case GExtNeg:
			case GExtPos: MainForm->NouvelleDefinition(EXTPOS); break;
			case GRecFam: MainForm->NouvelleDefinition(RECFAM); break;
			case GDepFam: MainForm->NouvelleDefinition(DEPFAM); break;
			case GDepDiv: MainForm->NouvelleDefinition(DEPDIV); break;
			case GRecDiv: MainForm->NouvelleDefinition(RECDIV); break;
			default:ShowMessage("Oubli LBClickFormule");
		}
		return;
	}

	formule=(CL_Formule*)LaGrille->Objects[0][r];

	if(formule==NULL)
	{
		formule=new CL_Formule();
		formule->Flag='N';
		LaGrille->Objects[0][r]=(TObject*)formule;
		LaGrille->Cells[0][r]=r;
	}
	else
	{
		if(formule->Origine=='C')
		MessageBox(Handle,"Calculé"," NON MODIFIABLE",MB_OK|MB_ICONSTOP);
		else
		{
			rep=MessageBox(Handle,"A Remplacer ?"," ATTENTION",MB_YESNO|MB_ICONEXCLAMATION);
			if(rep==ID_NO) return;
		}
	}

	if(formule->Flag!='N')formule->Flag='M';

	item=(CL_Item*)LB->Items->Objects[n];
	formule->No =item->No;
	formule->Item =item;
	switch(LaGrille->Tag)
	{
		//case GExtNeg:
		//case GExtPos:MainForm->ExternaliteClick(this);break;
		//300512 TP
		case GExtNeg: formule->NoFamille=EXTNEG;break;
		case GExtPos: formule->NoFamille=EXTPOS;break;
		//--
		case GProduit: formule->NoFamille=PRODUIT; break;
		case GCharge: formule->NoFamille=CHARGE; break;
		case GChStruct:formule->NoFamille=CHSTRUCT; break;
		case GRecDiv: formule->NoFamille=RECDIV; break;
		case GDepDiv: formule->NoFamille=DEPDIV; break;
		case GRecFam: formule->NoFamille=RECFAM; break;
		case GDepFam: formule->NoFamille=DEPFAM; break;

		default: ShowMessage("Oubli LBChoix");
	}

	LaGrille->Cells[2][r]=formule->Item->Nom;
	//tp 300512
	if ((LaGrille->Tag == GExtNeg) || (LaGrille->Tag == GExtPos))
	LaGrille->Cells[3][r]=formule->Item->Categorie->Nom;
	//--
	LaGrille->SetFocus();

}
//---------------------------------------------------------------------------
void __fastcall TLBChoixFrm::LBClickTvaImmo(void)
{
	int n;
	CL_Tva *tva;
	CL_Immo *immo;
//CL_Petit *petit;
	int r=LaGrille->Row;
	int c=LaGrille->Col;
	AnsiString s;
	int colTva=7;
	if(c!=colTva) return;
	n=LB->ItemIndex;
	s=LB->Items->Strings[n];
	if(s=="[...]")
	{
		MainForm->BtTVAClick(this);
		return;
	}
	immo=(CL_Immo*)LaGrille->Objects[0][r];

	if(immo==NULL)return;

	if(immo->Flag!='N')immo->Flag='M';

	tva=(CL_Tva*)LB->Items->Objects[n];
	immo->NoTva= tva->No;
	immo->Tva= tva;
	LaGrille->Cells[colTva][r]=tva->Nom;

	LaGrille->SetFocus();

}
//---------------------------------------------------------------------------
void __fastcall TLBChoixFrm::LBClickTvaPetit(void)
{
	int n;
	CL_Tva *tva;
	CL_Petit *petit;
//CL_Petit *petit;
	int r=LaGrille->Row;
	int c=LaGrille->Col;
	AnsiString s;
	int colTva=4;
	if(c!=colTva) return;

	n=LB->ItemIndex;
	s=LB->Items->Strings[n];
	if(s=="[...]")
	{
		MainForm->BtTVAClick(this);
		return;
	}
	petit=(CL_Petit*)LaGrille->Objects[0][r];

	if(petit==NULL)return;

	if(petit->Flag!='N')petit->Flag='M';

	tva=(CL_Tva*)LB->Items->Objects[n];
	petit->NoTva= tva->No;
	petit->Tva= tva;
	LaGrille->Cells[colTva][r]=tva->Nom;

	LaGrille->SetFocus();

}
//--------------------------------------------
void TLBChoixFrm::IniCaption(void) {
	LBChoixFrm->Caption = LC_LBChoixFrm;
}
//--------------------------------------------
void TLBChoixFrm::TexteCaption(void) {
	LC_LBChoixFrm = T->TrouveCaption("LBChoix", "LC_LBChoixFrm");

	IniCaption();
}
//--------------------------------------------

bool __fastcall TLBChoixFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

