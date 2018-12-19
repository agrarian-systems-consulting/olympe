//---------------------------------------------------------------------------

#ifndef DefCalendrierH
#define DefCalendrierH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "DefItem.h"
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TDefCalendrierFrm: public TDefItemFrm {
	__published: // Composants gérés par l'EDI
TRadioGroup	*RGDef;
	TBitBtn *BtBnAide;
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall RGDefClick(TObject *Sender);
	void __fastcall BtRepBasClick(TObject *Sender);
	void __fastcall BtRecopBasClick(TObject *Sender);
	void __fastcall BtSupClick(TObject *Sender);
	void __fastcall BtBnVideToutClick(TObject *Sender);
	void __fastcall BtBnNoteClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
	void __fastcall BtBnAideClick(TObject *Sender);
private: // Déclarations de l'utilisateur
	void __fastcall CompleteGrille(CL_Periode *periode,int row);
	bool __fastcall VerifCoherence(TStringGrid *grille);

	void EffBesTrav(CL_Atelier *atelier,int newPeriodeX);
	void EffBesTrav2(CL_BesTrav *besTrav,int newPeriodeX,int nbPhase);

	AnsiString L_Periode;
	AnsiString L_Debut;
	AnsiString L_Fin;
	AnsiString L_HJ;
	AnsiString L_Dispo;
	AnsiString L_Jours;
	AnsiString L_JDispo;
	AnsiString L_HDispo;
	AnsiString L_PasNom;
	AnsiString L_Plus100;
	AnsiString L_CarInval;
	AnsiString L_PasDeb;
	AnsiString L_PasFin;
	AnsiString L_PasHparJour;
	AnsiString L_DispoBizarre;
	AnsiString L_Duree0;
	AnsiString L_Duree365;
	AnsiString L_Rajout;
	AnsiString L_PerDef;
//    AnsiString L_Utilise;
	AnsiString L_SupQ;
//	AnsiString L_Sup;

protected:
	//Forme00
	virtual bool __fastcall ControleCell(int col,int row);
	//DefItem
	virtual void __fastcall Personnaliser(void);
	virtual void __fastcall IniGrille (TStringGrid *grille);
	virtual void __fastcall VersGrille (TStringGrid *grille);
	virtual bool __fastcall VerifGrille(TStringGrid *grille);
	virtual void __fastcall DeGrille (TStringGrid *grille);
	virtual void __fastcall SupprimerLigne(int r);

public:// Déclarations de l'utilisateur
	CL_Calendrier *Calendrier;
	void TexteChaine(void);
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_DefCalendrierFrm;
	AnsiString LC_RGDef;
	AnsiString LC_PerDeFParUt;
	AnsiString LC_PerDefMois;
	AnsiString LC_PerDefQuinz;

	__fastcall TDefCalendrierFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDefCalendrierFrm *DefCalendrierFrm;
//---------------------------------------------------------------------------
#endif
