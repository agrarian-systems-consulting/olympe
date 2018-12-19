//---------------------------------------------------------------------------

#ifndef DefActionH
#define DefActionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>

#include "Olympe.hse"
#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"

//---------------------------------------------------------------------------

class CL_Action {
public:
	Action(void);
	CL_Action(int nature, int NoCultRemplacee, int NoCultRemplacante,
			float Pcent);
	CL_Action(int nature, char *chaine);
	int Nature;
	int LesInt[10];
	float LesFloat[10];
	char *Chaine;

	void Maz(void);
	void AffGrille(TStringGrid *SG, int r);
	AnsiString DonneNom(void);
	AnsiString DonneDetail(void);
	AnsiString DetailRemplacer(void);

	void SaisieAction(void);
	AnsiString SaisieRemplacer(void);

};
enum {
	REMPLACER = 1,
	PLANTER,
	ARRACHER,
	INVESTIR,
	EMPRUNTER,
	ABSORBERSURFACE,
	ABSORBERTOTALITE
};

class CL_Regle {
public:
	CL_Regle(void);

	int No;
	AnsiString Nom;
	AnsiString TxtCondition;
	CL_Arbre *Arbre;
	TList *LstAction;
};

class TDefActionFrm: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*PanHaut;
	TPanel *PanBas;
	TBitBtn *BtSortir;
	TLabel *LabelModifie;
	TGroupBox *GBCondition;
	TGroupBox *GBAction;
	TStringGrid *SG;
	TBitBtn *BtDico;
	TBitBtn *BtMotCle;
	TRichEdit *REdit;
	TBitBtn *BtBnQuitter;
	TLabel *LabRegle;
	void __fastcall SGClick(TObject *Sender);
	void __fastcall BtDicoClick(TObject *Sender);
	void __fastcall BtMotCleClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtBnQuitterClick(TObject *Sender);
	void __fastcall SGDrawCell(TObject *Sender, int ACol, int ARow,
			TRect &Rect, TGridDrawState State);
private: // Déclarations de l'utilisateur
	void __fastcall TDefActionFrm::DefGrille(void);

public:// Déclarations de l'utilisateur
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_GBAction;
	AnsiString LC_GBCondition;
	AnsiString LC_DefActionFrm;
	AnsiString LC_BtDico;
	AnsiString LC_LabelModifie_A;
	AnsiString LC_BtMotCle;
	AnsiString LC_BtBnQuitter;
	AnsiString LC_LabRegle;

	__fastcall TDefActionFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDefActionFrm *DefActionFrm;
//---------------------------------------------------------------------------
#endif
