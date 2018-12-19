#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "CL_Trad.h"

#include "LesVecteurs.hse"
#include "AgriSaisieEnum.h"
#include "AgriSaisie.h"
extern CL_Trad *T;

//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::BtBnVideToutClick(TObject *Sender)
{
	int repMB;
	int i;
	CL_FN_Xp1 *FN_Xp1;
	CL_Petit * petit;
	repMB=MessageBox(Handle,L_JeffToutQ.c_str(),T->L_EffaceT.c_str(),MB_YESNO|MB_ICONQUESTION);
	//repMB=MessageBox(Handle,"j'efface tout ?","EFFACER TOUT LE TABLEAU",MB_YESNO|MB_ICONQUESTION);
	if(repMB==IDNO) return;
	LabelModifie->Visible=true;
	switch(LaGrille->Tag)
	{
		case GAssol: Agri->V_Culture->purge();break;
		case GPerenne: Agri->V_Verger->purge(); break;
		case GVivrier: Agri->V_Vivrier->purge();break;

		case GAni: Agri->V_Animaux->purge();break;

		case GVariable: Agri->V_Variable->purge();break;
		case GChStruct: Agri->V_ChStruct->purge();break;
		case GRecDiv: Agri->V_RecDiv->purge(); break;
		case GDepDiv: Agri->V_DepDiv->purge();break;
		case GRecFam: Agri->V_RecFam->purge();break;
		case GDepFam: Agri->V_DepFam->purge();break;
		case GExtNeg: Agri->V_ExtNeg->purge();break;
		case GExtPos: Agri->V_ExtPos->purge();break;
		case GEmpLT: Agri->V_EmpLT->purge(); break; //???
		case GEmpCT: Agri->V_EmpCT->purge();break;
		case GSub: Agri->V_Sub->purge();break;
		case GPlact: Agri->V_Plact->purge();break;

		case GOccc: Agri->V_Occc->purge();break;
		case GFinSom:
		for(i=0;i<Agri->V_FinSom->Nbelt;i++)
		{
			FN_Xp1=Agri->V_FinSom->Vecteur[i];
			memset(FN_Xp1->Valeur,0,sizeof(FN_Xp1->Valeur));
		}
		break;
		case GImmo: Agri->V_Immo->purge();break;
		case GPetit:
		for(i=0;i<Agri->V_Petit->Nbelt;i++)
		{
			petit=Agri->V_Petit->Vecteur[i];
			petit->ValAchat=0;
		}
		break;
		case GInvSom:
		for(i=0;i<Agri->V_InvSom->Nbelt;i++)
		{
			FN_Xp1=Agri->V_InvSom->Vecteur[i];
			memset(FN_Xp1->Valeur,0,sizeof(FN_Xp1->Valeur));
		}
		break;
		case GCreance: Agri->V_Creance->purge();break;
		case GDette: Agri->V_Dette->purge();break;
		case GStock: Agri->V_StockIni->purge();break;
		case GPolStock: PurgeLstQuantPrix();break;
		default: ShowMessage("AgriSaisieVideTout Oubli");
	}
	IniGrille(LaGrille);
	VersGrille(LaGrille);
}
//---------------------------------------------------------------------------

/*
 L_JeffToutQ=          "j'efface tout ?";
 L_JeffToutT=          "EFFACER TOUT LE TABLEAU";

 */