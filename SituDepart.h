//---------------------------------------------------------------------------

#ifndef SituDepartH
#define SituDepartH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Forme0.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSituDepartFrm: public TForme0Frm {
	__published: // Composants gérés par l'EDI
TLabel	*LabTresoIni;
	TLabel *LabTva;
	TLabel *LabAcompteAout;
	TLabel *LabAcompteNov;
	TLabel *LabAcompteMai;
	TLabel *LabAcompteFevrier;

	TEdit *EdTresoIni;
	TEdit *EdTvaRecue;
	TEdit *EdTvaVersee;
	TEdit *EdAcompteAout;
	TEdit *EdAcompteNov;
	TEdit *EdAcompteFev;
	TEdit *EdAcompteMai;
	TLabel *LabTvaEncaissee;
	TLabel *LabTvaVersee;
	TBitBtn *BtClBas;
	TLabel *LabelModifie;
	void __fastcall EdKeyPress(TObject *Sender, char &Key);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall EdTvaRecueExit(TObject *Sender);
	void __fastcall EdTresoIniExit(TObject *Sender);
	void __fastcall EdTvaVerseeExit(TObject *Sender);
	void __fastcall EdAcompteAoutExit(TObject *Sender);
	void __fastcall EdAcompteNovExit(TObject *Sender);
	void __fastcall EdAcompteFevExit(TObject *Sender);
	void __fastcall EdAcompteMaiExit(TObject *Sender);
	void __fastcall BtClBasClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private: // Déclarations utilisateur
	void __fastcall LocalKeyPress(TObject *Sender, char &Key);
	float __fastcall LireFloat(AnsiString s);
	int Digits;
public:// Déclarations utilisateur
	CL_Agriculteur *Agri;
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_LabAcompteAout;
	AnsiString LC_LabAcompteFevrier;
	AnsiString LC_LabAcompteMai;
	AnsiString LC_LabAcompteNov;
	AnsiString LC_LabelModifie_A;
	AnsiString LC_SituDepartFrm;
	AnsiString LC_LabTresoIni;
	AnsiString LC_BtBnTva;
	AnsiString LC_LabTvaEncaissee;
	AnsiString LC_LabTvaVersee;

	__fastcall TSituDepartFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSituDepartFrm *SituDepartFrm;
//---------------------------------------------------------------------------
#endif
