//---------------------------------------------------------------------------

#ifndef QuelExcelCSVH
#define QuelExcelCSVH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TQuelExcelCSVFrm: public TForm {
	__published: // Composants gérés par l'EDI
TEdit	*EdNomExcel;
	TBitBtn *BtBnParcourir;
	TBitBtn *BtBnAnnuler;
	TOpenDialog *ODExcel;
	TRadioGroup *RG;
	TBitBtn *BtBnOK;
	TBitBtn *BtBnAide;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtBnParcourirClick(TObject *Sender);
	void __fastcall BtBnAnnulerClick(TObject *Sender);
	void __fastcall BtBnOKClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
	void __fastcall BtBnAideClick(TObject *Sender);
	//void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:// Déclarations utilisateur
public:// Déclarations utilisateur
	bool Renonce;

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_RG;
	AnsiString LC_QuelExcelCSVFrm;
	AnsiString LC_BtBnParcourir;

	AnsiString LC_AEcrire;
	AnsiString LC_ALaSuite;
	AnsiString LC_Maz;
	AnsiString LC_AutreF;

	__fastcall TQuelExcelCSVFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQuelExcelCSVFrm *QuelExcelCSVFrm;
//---------------------------------------------------------------------------
#endif
