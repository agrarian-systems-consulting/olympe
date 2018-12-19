//---------------------------------------------------------------------------

#ifndef LBToutEnsembleH
#define LBToutEnsembleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <CheckLst.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TLBToutEnsembleFrm: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*PBas;
	TBitBtn *BtBnOK;
	TBitBtn *BtBnPasOK;
	TCheckListBox *ChLB;
	TBitBtn *BtBnTous;
	TBitBtn *BtBnAucun;
	void __fastcall BtBnOKClick(TObject *Sender);
	void __fastcall BtBnPasOKClick(TObject *Sender);
	void __fastcall BtBnTousClick(TObject *Sender);
	void __fastcall BtBnAucunClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private: // Déclarations utilisateur
	void __fastcall SelectionAddition(void);

public:// Déclarations utilisateur
	AnsiString VientDe;
	void __fastcall Extraction(void);
	void __fastcall CreeLB(void);
	void __fastcall BtBnVisible(bool visible);
public:
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_BtIndAucun;
	AnsiString LC_GereEnsembleFrm;
	AnsiString LC_BtIndTous;

	__fastcall TLBToutEnsembleFrm(TComponent* Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TLBToutEnsembleFrm *LBToutEnsembleFrm;
//---------------------------------------------------------------------------
#endif
