//---------------------------------------------------------------------------
#ifndef SysUniteH
#define SysUniteH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Forme00.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <OleCtrls.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <DBGrids.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
class TSysUniteFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TLabel	*LabForme;
	TBitBtn *BtReportDroit;
	TBitBtn *BtSup;
	TBitBtn *BtBnVideTout;
	TGroupBox *GBMonnaie;
	TLabel *LabMonnaie;
	TBitBtn *BtBnNotes;
//	void __fastcall BoutAnnulClick(TObject *Sender);

//	void __fastcall BtSupprimeClick(TObject *Sender);
	void __fastcall BtSupClick(TObject *Sender);
	void __fastcall BtReportDroitClick(TObject *Sender);
	void __fastcall BtBnStockerClick(TObject *Sender);
	void __fastcall BtBnVideToutClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtBnNotesClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
//    void __fastcall EdMonnaieClick(TObject *Sender);

private:// Déclarations de l'utilisateur
//        void __fastcall IniCB(void);
	void CreeTable(void);
	void CreeTable2(TStringList *Liste);
//        void CreeTable3(char *lesTitres[],int iX);
	void __fastcall StockerOrdre(CL_Vecteur<CL_SystemeUnite> *vecteur);
	bool __fastcall RepPossible(int c,int r);
	void __fastcall tri(void);
	int compSysUnite(const void *s1,const void *s2);
	void __fastcall FaireTrad(void);

protected:
	virtual void __fastcall DefinirLesGrilles(void);
	virtual void __fastcall Personnaliser(void);
	virtual void __fastcall IniGrille (TStringGrid *grille);
//       virtual void  __fastcall VersGrille  (TStringGrid *grille);
	virtual void __fastcall DeGrille (TStringGrid *grille);
	virtual bool __fastcall ControleCell(int col,int row);
	virtual bool __fastcall Stocker(void);

public:
	virtual void __fastcall VersGrille (TStringGrid *grille);
	AnsiString Notes;
	void TexteChaine(void);

	AnsiString L_Titre1,L_Titre2,L_Titre3,L_Titre4,L_Titre5,L_Titre6;
	AnsiString L_ImpoChg_monnaie;

	AnsiString L_PasUniteAtelier;
	AnsiString L_PasUniteEntreprise;
	AnsiString L_Pas_UniteRegion;
	AnsiString L_PasRatio21;
	AnsiString L_Ratio21Nul;
	AnsiString L_PasRatio31;
	AnsiString L_Ratio31Nul;
	AnsiString L_ErrRatio21;
	AnsiString L_ErrRatio31;
	AnsiString L_PasMonnaie;
	AnsiString L_PlusMonnaie;

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_LabMonnaie;
	AnsiString LC_GBMonnaie;
	AnsiString LC_SysUniteFrm;
	AnsiString LC_LBSysUnitFrm;
//    AnsiString LC_ChBRepTout;
//    AnsiString LC_BtClasser;

	__fastcall TSysUniteFrm(TComponent *Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSysUniteFrm *SysUniteFrm;
//---------------------------------------------------------------------------
#endif
