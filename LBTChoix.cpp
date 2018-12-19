//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "CL_Trad.h"

#include "TendanceEnum.h"
#include "GereAleaPrix.h"
#include "Aide.h"
#include "AleaPrix.h"

#include "LBTChoix.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "LBChoix"
#pragma resource "*.dfm"
TLBTChoixFrm *LBTChoixFrm;

extern CL_ES *ES;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TLBTChoixFrm::TLBTChoixFrm(TComponent* Owner) :
		TLBChoixFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TLBTChoixFrm::FormActivate(TObject *Sender)
{
	LaGrille= AleaPrixFrm->LaGrille;
	AleaPrixFrm->RepChoix=ABANDON;
//ShowMessage("TLBTChoixFrm");
	switch(LaGrille->Tag)
	{
		case GTProd:
		case GTCharge:
		Caption="Les Tendances";break;
		case GSProd:
		case GSCharge:
		Caption="Les Scénarios";break;
		default:ShowMessage("LBTChoix Oubli");break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TLBTChoixFrm::LBClick(TObject *Sender)
{

	switch(LaGrille->Tag)
	{
		case GTProd:
		case GTCharge:
		case GSProd:
		case GSCharge:
		LBClickTendance();break;
		default:ShowMessage("LBTChoix Oubli");break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TLBTChoixFrm::LBClickTendance(void)
{
	int n;
	bool rep;
	CL_Tendance *tendance;
	AnsiString s,nom;

	n=LB->ItemIndex;
	s=LB->Items->Strings[n];
	if(s=="[...]")
	{
		while(1)
		{
			rep=ES->EntrerNom("Nouvelle Tendance", "Donner son Nom", nom);
			if ( rep==true)
			{
				if(nom.Length()==0) continue;
				tendance=GereAleaPrixFrm->V_Tendance->trouve(nom);
				if(tendance)
				{
					MessageBox(Handle," Nom déjà donné","IMPOSSIBLE",MB_OK|MB_ICONSTOP);
					continue;
				}
				tendance=new CL_Tendance;
				tendance->Nom=nom;
				GereAleaPrixFrm->V_Tendance->ins(tendance);
				AleaPrixFrm->LabNom->Caption=tendance->Nom;
				AleaPrixFrm->RepChoix=NOUVEAU;
				break;
			}
			else
			{
				AleaPrixFrm->RepChoix=ABANDON;
				Close();
				break;
			}
		}
	}
	else
	{
		tendance=(CL_Tendance*)LB->Items->Objects[n];
		AleaPrixFrm->LabNom->Caption=tendance->Nom;
		AleaPrixFrm->RepChoix=EXISTE;
	}
	AleaPrixFrm->Tendance=tendance;
	Close();
}
//---------------------------------------------------------------------------
//--------------------------------------------
void TLBTChoixFrm::IniCaption(void) {
	LBTChoixFrm->Caption = LC_LBTChoixFrm;
}
//--------------------------------------------
void TLBTChoixFrm::TexteCaption(void) {
	LC_LBTChoixFrm = T->TrouveCaption("LBTChoix", "LC_LBTChoixFrm");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TLBTChoixFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

