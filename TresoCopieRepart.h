//---------------------------------------------------------------------------

#ifndef TresoCopieRepartH
#define TresoCopieRepartH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TTresoCopieRepartFrm: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*PanB;
	TBitBtn *BtBnFermer;
	TBitBtn *BtBnQuitter;
	TStringGrid *GrilleAgri;
	void __fastcall BtBnQuitterClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall GrilleAgriDblClick(TObject *Sender);
private: // Déclarations de l'utilisateur
	int Row;
	void __fastcall VideGrille(TStringGrid *grille);

	void __fastcall CreeGrilleAgri(void);
	void __fastcall AffAgri(CL_Agriculteur *agri);
	void __fastcall AffLesVariantes(CL_Agriculteur *agri);
	void __fastcall CopierRepart(CL_Agriculteur *agri);

public:// Déclarations de l'utilisateur

	void TexteChaine(void);

	AnsiString L_Repart;
	AnsiString L_NbVar;
	AnsiString L_NoVar;
	AnsiString L_PasRep;
	AnsiString L_RecopRepDe;
	AnsiString L_RecopRep;

	CL_Agriculteur *AgriEnCours;
	__fastcall TTresoCopieRepartFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTresoCopieRepartFrm *TresoCopieRepartFrm;
//---------------------------------------------------------------------------
#endif
