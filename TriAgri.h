//---------------------------------------------------------------------------

#ifndef TriAgriH
#define TriAgriH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <CheckLst.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TTriAgriFrm: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*PanBas;

	TLabel *Lab1;
	TCheckListBox *ChLB1;
	TPanel *Pan1;
	TBitBtn *BtBnAucun1;
	TBitBtn *BtBnTous1;

	TLabel *Lab2;
	TCheckListBox *ChLB2;
	TPanel *Pan2;
	TBitBtn *BtBnAucun2;
	TBitBtn *BtBnTous2;

	TLabel *Lab3;
	TCheckListBox *ChLB3;
	TPanel *Pan3;
	TBitBtn *BtBnAucun3;
	TBitBtn *BtBnTous3;

	TLabel *Lab4;
	TCheckListBox *ChLB4;
	TPanel *Pan4;
	TBitBtn *BtBnAucun4;
	TBitBtn *BtBnTous4;

	TLabel *Lab5;
	TCheckListBox *ChLB5;
	TPanel *Pan5;
	TBitBtn *BtBnAucun5;
	TBitBtn *BtBnTous5;
	TBitBtn *BtBnOk;
	TBitBtn *BtBnPasOK;
	TBitBtn *BtBnCritere;

	void __fastcall BtBnAucunClick(TObject *Sender);
	void __fastcall BtBnTousClick(TObject *Sender);
	void __fastcall BtBnCritereClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ChLBClickCheck(TObject *Sender);
	void __fastcall BtBnOkClick(TObject *Sender);
	void __fastcall BtBnPasOKClick(TObject *Sender);

private: // Déclarations utilisateur
	TList *LstPan;
	TList *LstLabel;
	TList *LstChLB;
	TList *LstChB;
	bool __fastcall estDejaSelectionne(CL_Agriculteur *agri);
	void __fastcall SelectionTri(void);
	void __fastcall Extraction(void);
	void __fastcall SelectionProcedure(void);

//    __fastcall void IniEcran(void);

public:// Déclarations utilisateur
	AnsiString VientDe;
	bool EstInitialise;//mis à false à lecture d'un autre fichier
	__fastcall void IniEcran(void);

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_BtIndAucun;
	AnsiString LC_TriAgriFrm;
	AnsiString LC_BtBnCritere;
	AnsiString LC_Lab1;
	AnsiString LC_Lab2;
	AnsiString LC_Lab3;
	AnsiString LC_Lab4;
	AnsiString LC_Lab5;
	AnsiString LC_Pan1;
	AnsiString LC_Pan2;
	AnsiString LC_Pan3;
	AnsiString LC_Pan4;
	AnsiString LC_Pan5;
	AnsiString LC_BtIndTous;

	__fastcall TTriAgriFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTriAgriFrm *TriAgriFrm;
//---------------------------------------------------------------------------
#endif
