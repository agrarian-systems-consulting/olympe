//---------------------------------------------------------------------------

#ifndef AgriClasstH
#define AgriClasstH
#include <Buttons.hpp>
#include <CheckLst.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
#include <iostream>
#include <map.h>
using namespace std;
typedef map<string, CL_Agriculteur*> MapAgri;
typedef MapAgri::iterator ItAgri;
typedef pair<const string, CL_Agriculteur*> PairAgri;
#include <iostream>
#include <fstream>

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <CheckLst.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TAgriClasstFrm: public TForm {
	__published: // Composants gérés par l'EDI
TGroupBox	*CleDeClassif;
	TCheckListBox *ChLBCatTypeZone;
	TPanel *PCleDeClassif;
	TBitBtn *BtClHautLB;
	TBitBtn *BtClBasLB;
	TGroupBox *GBOrdreTri;
	TStringGrid *LaGrille;
	TPanel *Panel1;
	TBitBtn *BtBnClHautLaGrille;
	TBitBtn *BtBnClBasLaGrille;
	TLabel *LabelModifie;
	TPanel *PBas;
	TBitBtn *BtOK;
	TBitBtn *BtIgnore;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtClLBClick(TObject *Sender);
	void __fastcall BtBnClLaGrilleClick(TObject *Sender);
	void __fastcall BtBnOkClick(TObject *Sender);
	void __fastcall BtOKClick(TObject *Sender);
	void __fastcall BtIgnoreClick(TObject *Sender);
	void __fastcall ChLBCatTypeZoneClickCheck(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
	void __fastcall FormCreate(TObject *Sender);

private: // Déclarations de l'utilisateur
	bool ChLBCatTypeZoneEstCree;
	void CreerChLBCatTypeZone();

	void __fastcall MarquerCell(int col,int row);
	void __fastcall Classer(void);

public:// Déclarations de l'utilisateur
	AnsiString LC_AgriClasstFrm;
	AnsiString LC_CleDeClassif;
	AnsiString LC_LabelModifie_A;
	AnsiString LC_GBOrdreTri;

	void IniCaption(void);
	void TexteCaption(void);

	void __fastcall AffGrille(void);
	int __fastcall CompteColonne(void);
	AnsiString VientDe;
	void __fastcall ClasserAlpha(void);
	__fastcall TAgriClasstFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAgriClasstFrm *AgriClasstFrm;
//---------------------------------------------------------------------------
#endif

