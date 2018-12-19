//---------------------------------------------------------------------------
#ifndef ChoixCritereH
#define ChoixCritereH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TChoixCritereFrm: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*Panel2;
	TListBox *LBCritere;
	TListBox *LBCritereNR;
	TButton *BtEntrer;
	TButton *BtToutEntrer;
	TButton *BtSortir;
	TButton *BtToutSortir;
	TButton *BtOK;
	TButton *BtAnnul;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *LabelModifie;
	void __fastcall BtEntrerClick(TObject *Sender);
	void __fastcall BtToutEntrerClick(TObject *Sender);
	void __fastcall BtSortirClick(TObject *Sender);
	void __fastcall BtToutSortirClick(TObject *Sender);
	void __fastcall BtAnnulClick(TObject *Sender);
	void __fastcall BtOKClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private: // Déclarations de l'utilisateur
	TList *LstR,*LstNR;

public:// Déclarations de l'utilisateur
	AnsiString VientDe;
	__fastcall TChoixCritereFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TChoixCritereFrm *ChoixCritereFrm;
//---------------------------------------------------------------------------
#endif
