//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "AgriSaisie.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "SituDepart.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme0"
#pragma resource "*.dfm"
TSituDepartFrm *SituDepartFrm;
extern CL_ES *ES;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TSituDepartFrm::TSituDepartFrm(TComponent* Owner) :
		TForme0Frm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TSituDepartFrm::FormActivate(TObject *Sender)
{
	int digits=0;
	int an0=Agri->DefSim->An_0;
	IntToStr(an0);
	LabTvaEncaissee->Caption= "Tva Encaissée "+IntToStr(an0-1);
	LabTvaVersee->Caption= "Tva Versée "+IntToStr(an0-1);

	LabAcompteMai->Caption= "Acompte Mai "+ IntToStr(an0-1);
	LabAcompteAout->Caption= "Acompte Aout "+IntToStr(an0-1);
	LabAcompteNov->Caption= "Acompte Nov "+ IntToStr(an0-1);
	LabAcompteFevrier->Caption= "Acompte Fév "+ IntToStr(an0);

	EdTresoIni->Text= FloatToStrF(Agri->TresoIni,ffNumber,7,digits);
	EdTvaRecue->Text= FloatToStrF(Agri->TvaEntIni->Recu,ffNumber,7,digits);
	EdTvaVersee->Text= FloatToStrF(Agri->TvaEntIni->Verse,ffNumber,7,digits);

	EdAcompteMai->Text= FloatToStrF(Agri->TvaEntIni->AcompteMai,ffNumber,7,digits);
	EdAcompteAout->Text= FloatToStrF(Agri->TvaEntIni->AcompteAout,ffNumber,7,digits);
	EdAcompteNov->Text= FloatToStrF(Agri->TvaEntIni->AcompteNov,ffNumber,7,digits);
	EdAcompteFev->Text= FloatToStrF(Agri->TvaEntIni->AcompteFev,ffNumber,7,digits);
	LabelModifie->Visible=false;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TSituDepartFrm::EdKeyPress(TObject *Sender,
		char &Key)
{
	LocalKeyPress(this,Key);
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TSituDepartFrm::EdTresoIniExit(TObject *Sender)
{
	Agri->TresoIni=LireFloat(EdTresoIni->Text);
	EdTresoIni->Text= FloatToStrF(Agri->TresoIni,ffNumber,7,Digits);
}
//---------------------------------------------------------------------------
void __fastcall TSituDepartFrm::EdTvaRecueExit(TObject *Sender)
{
	Agri->TvaEntIni->Recu=LireFloat(EdTvaRecue->Text);
	EdTvaRecue->Text= FloatToStrF(Agri->TvaEntIni->Recu,ffNumber,7,Digits);
}
//---------------------------------------------------------------------------
void __fastcall TSituDepartFrm::EdTvaVerseeExit(TObject *Sender)
{
	Agri->TvaEntIni->Verse=LireFloat(EdTvaVersee->Text);
	EdTvaVersee->Text= FloatToStrF(Agri->TvaEntIni->Verse,ffNumber,7,Digits);

}
//les acomptes
//---------------------------------------------------------------------------
void __fastcall TSituDepartFrm::EdAcompteMaiExit(TObject *Sender)
{
	Agri->TvaEntIni->AcompteMai=LireFloat(EdAcompteMai->Text);
	EdAcompteMai->Text= FloatToStrF(Agri->TvaEntIni->AcompteMai,ffNumber,7,Digits);
}
//---------------------------------------------------------------------------
void __fastcall TSituDepartFrm::EdAcompteAoutExit(TObject *Sender)
{
	Agri->TvaEntIni->AcompteAout=LireFloat(EdAcompteAout->Text);
	EdAcompteAout->Text= FloatToStrF(Agri->TvaEntIni->AcompteAout,ffNumber,7,Digits);
}
//---------------------------------------------------------------------------
void __fastcall TSituDepartFrm::EdAcompteNovExit(TObject *Sender)
{
	Agri->TvaEntIni->AcompteNov=LireFloat(EdAcompteNov->Text);
	EdAcompteNov->Text= FloatToStrF(Agri->TvaEntIni->AcompteNov,ffNumber,7,Digits);
}
//---------------------------------------------------------------------------
void __fastcall TSituDepartFrm::EdAcompteFevExit(TObject *Sender)
{
	Agri->TvaEntIni->AcompteFev=LireFloat(EdAcompteFev->Text);
	EdAcompteFev->Text= FloatToStrF(Agri->TvaEntIni->AcompteFev,ffNumber,7,Digits);
}
//---------------------------------------------------------------------------
void __fastcall TSituDepartFrm::BtClBasClick(TObject *Sender)
{
	float val;
	val=LireFloat(EdAcompteMai->Text);

	Agri->TvaEntIni->AcompteMai= val;
	Agri->TvaEntIni->AcompteAout= val;
	Agri->TvaEntIni->AcompteNov= val;
	Agri->TvaEntIni->AcompteFev= val;

	EdAcompteMai->Text= FloatToStrF(Agri->TvaEntIni->AcompteMai,ffNumber,7,Digits);
	EdAcompteAout->Text= FloatToStrF(Agri->TvaEntIni->AcompteAout,ffNumber,7,Digits);
	EdAcompteNov->Text= FloatToStrF(Agri->TvaEntIni->AcompteNov,ffNumber,7,Digits);
	EdAcompteFev->Text= FloatToStrF(Agri->TvaEntIni->AcompteFev,ffNumber,7,Digits);

	LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TSituDepartFrm::LocalKeyPress(TObject *Sender, char &Key)
{

	if (Key >='0' && Key <='9') return;
//    else if(Key=='-')                     return;
	else if(Key=='.') return;
	else if(Key==VK_BACK) return;
	Key=0;
}
//copie modifiée de forme00 GrilleFloat
//---------------------------------------------------------------------------
float __fastcall TSituDepartFrm::LireFloat(AnsiString s)
{
	int n,c;
	char car;
	char chaine[20];
	int point=0;
	s=s.Trim();
	if(s=="" ||s=="."||s=="-") return 0.;
	c=0;
	for(n=1;n<s.Length()+1;n++)
	{
		car=s[n];
		if (car>='0' && car<='9') chaine[c++] =car;
		else if(car=='.' ||car==',')
		{
			if(point==0) {chaine[c++] ='.';point++;}
		}
		else if(car=='-' && c==0) chaine[c++] ='-';
	}
	chaine[c]=0;
	s=AnsiString(chaine);
	return s.ToDouble();
}

//---------------------------------------------------------------------------
void __fastcall TSituDepartFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	if(LabelModifie->Visible==false) return;

	ES->ecrireFichier();
	AgriSaisieFrm->Calcul0(Agri);
//
}
//---------------------------------------------------------------------------

//--------------------------------------------
void TSituDepartFrm::IniCaption(void) {
	LabAcompteAout->Caption = LC_LabAcompteAout;
	LabAcompteFevrier->Caption = LC_LabAcompteFevrier;
	LabAcompteMai->Caption = LC_LabAcompteMai;
	LabAcompteNov->Caption = LC_LabAcompteNov;
	LabelModifie->Caption = T->LC_LabelModifie_A;
	SituDepartFrm->Caption = LC_SituDepartFrm;
	LabTresoIni->Caption = LC_LabTresoIni;
	LabTva->Caption = T->LC_BtBnTva;
	LabTvaEncaissee->Caption = LC_LabTvaEncaissee;
	LabTvaVersee->Caption = LC_LabTvaVersee;
}
//--------------------------------------------
void TSituDepartFrm::TexteCaption(void) {
	LC_LabAcompteAout = T->TrouveCaption("SituDepart", "LC_LabAcompteAout");
	LC_LabAcompteFevrier = T->TrouveCaption("SituDepart",
			"LC_LabAcompteFevrier");
	LC_LabAcompteMai = T->TrouveCaption("SituDepart", "LC_LabAcompteMai");
	LC_LabAcompteNov = T->TrouveCaption("SituDepart", "LC_LabAcompteNov");
	LC_LabelModifie_A = T->TrouveCaption("CL_Trad", "LC_LabelModifie_A");
	LC_SituDepartFrm = T->TrouveCaption("SituDepart", "LC_SituDepartFrm");
	LC_LabTresoIni = T->TrouveCaption("SituDepart", "LC_LabTresoIni");
	LC_BtBnTva = T->TrouveCaption("CL_Trad", "LC_BtBnTva");
	LC_LabTvaEncaissee = T->TrouveCaption("SituDepart", "LC_LabTvaEncaissee");
	LC_LabTvaVersee = T->TrouveCaption("SituDepart", "LC_LabTvaVersee");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TSituDepartFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

