//---------------------------------------------------------------------------

#ifndef FenRepartDefH
#define FenRepartDefH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Forme0.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include <Grids.hpp>

//---------------------------------------------------------------------------
class TFenRepartDefFrm: public TForme0Frm {
	__published: // Composants gérés par l'EDI
TGroupBox	*GBCode;
	TEdit *EdCode;
	TStringGrid *LaGrille;
	TLabel *LabelModifie;
	TEdit *EdTotPcent;
	TLabel *LabTotPcent;
	TBitBtn *BtBn100;
	TBitBtn *BtBnEgal;
	TBitBtn *BtBn0;
	TGroupBox *GBCategorie;
	TEdit *EdCategorie;
	TBitBtn *BtBnMaz;
	TBitBtn *BtBnACopier;
	TBitBtn *BtBnReste;
	TBitBtn *BtBnCopier;
	TBitBtn *BtBnCopieRepart;
	TBitBtn *BtBnSup;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall LaGrilleKeyPress(TObject *Sender, char &Key);
	void __fastcall BtBnEgalClick(TObject *Sender);
	void __fastcall BtBn100Click(TObject *Sender);
	void __fastcall BtBn0Click(TObject *Sender);
	void __fastcall EdCodeKeyPress(TObject *Sender, char &Key);
	void __fastcall BtBnMazClick(TObject *Sender);
	void __fastcall LaGrilleSelectCell(TObject *Sender, int ACol, int ARow,
			bool &CanSelect);
	void __fastcall BtBnACopierClick(TObject *Sender);
	void __fastcall BtBnResteClick(TObject *Sender);
	void __fastcall BtBnCopierClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall BtBnCopieRepartClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
	//TP
	void __fastcall LaGrilleSetEditText(TObject *Sender,
			int ACol, int ARow, const AnsiString Value);
private:// Déclarations de l'utilisateur

//	void __fastcall EffaceGrille(void);
	void __fastcall Demarre(void);
	void __fastcall AffTotal(void);
	int __fastcall VerifTotal(void);
	int __fastcall VerifCode(void);
	int __fastcall CodeExiste(void);
	void __fastcall MajTV(void);
	AnsiString ACopier;
	int Traitement;
public:// Déclarations de l'utilisateur
	CL_Repart *Repart,*Repart0;
	CL_Categorie *Categorie;
	void __fastcall Affiche(void);
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_BtBn0;
	AnsiString LC_BtBnMaz;
	AnsiString LC_BtBn100;
	AnsiString LC_BtBnEgal;
	AnsiString LC_BtBnACopier;
	AnsiString LC_RGCat;
	AnsiString LC_GBCode;
	AnsiString LC_BtBnCopier;
	AnsiString LC_BtBnCopieRepart;
	AnsiString LC_BtBnReste;
	AnsiString LC_LabelModifie;
	AnsiString LC_FenRepartDefFrm;
	AnsiString LC_BtBnSupBesTrav;
	AnsiString LC_LabTotPcent;

	__fastcall TFenRepartDefFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFenRepartDefFrm *FenRepartDefFrm;
//---------------------------------------------------------------------------
#endif
