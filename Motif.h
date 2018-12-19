//---------------------------------------------------------------------------

#ifndef MotifH
#define MotifH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TMotifFrm: public TForm {
	__published: // Composants gérés par l'EDI
TStringGrid	*SG;
	TBitBtn *BtBleu;
	TBitBtn *Blanc;
	TBitBtn *Rouge;
	TDrawGrid *DG;
	void __fastcall BtBnQuitterClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall SGDrawCell(TObject *Sender, int ACol, int ARow,
			TRect &Rect, TGridDrawState State);
	void __fastcall BtBleuClick(TObject *Sender);
	void __fastcall BlancClick(TObject *Sender);
	void __fastcall RougeClick(TObject *Sender);
	void __fastcall DGDrawCell(TObject *Sender, int ACol, int ARow,
			TRect &Rect, TGridDrawState State);
private: // Déclarations de l'utilisateur
	int CoulX,MotifX;
	int LesMotifs[7];
	TColor LesCouleurs[20];
	int CoulLigne[200],MotifLigne[200];

public:// Déclarations de l'utilisateur
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_Blanc;
	AnsiString LC_BtBleu;
	AnsiString LC_MotifFrm;
	AnsiString LC_Rouge;

	__fastcall TMotifFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMotifFrm *MotifFrm;
//---------------------------------------------------------------------------
#endif
