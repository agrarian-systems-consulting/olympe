//---------------------------------------------------------------------------

#ifndef DefEtatSortieH
#define DefEtatSortieH
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
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TDefEtatSortieFrm: public TDefItemFrm {
	__published: // Composants gérés par l'EDI
TBitBtn	*BtBnResultat;
	TRadioGroup *RGModifiable;
	TPanel *PanG;
	TBitBtn *BtBnDico;
	TListBox *LBService;
	TBitBtn *BtBnAide;
	TColorDialog *ColorDialog;
	void __fastcall BtSupClick(TObject *Sender);
	void __fastcall LBServiceClick(TObject *Sender);
	void __fastcall RGModifiableClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall BtBnResultatClick(TObject *Sender);
	void __fastcall BtBnDicoClick(TObject *Sender);
	void __fastcall BtBnVideToutClick(TObject *Sender);
	void __fastcall BtBnNoteClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
	void __fastcall BtBnAideClick(TObject *Sender);
	void __fastcall Grille0DrawCell(TObject *Sender, int ACol, int ARow,
			TRect &Rect, TGridDrawState State);
	void __fastcall Grille0KeyPress(TObject *Sender, char &Key);
private: // Déclarations de l'utilisateur
	void __fastcall PlaceEltForme(CL_Elt *elt);
	void __fastcall Inserer(void);

	AnsiString L_Titre;
	AnsiString L_Titre2;
	AnsiString L_SupQ;
	AnsiString L_Sup;
	AnsiString L_ModifQ;
	AnsiString L_Modif;
	AnsiString L_EffaceQ;
	AnsiString L_Efface;
	AnsiString L_Conserve;

protected:
//	CL_Categorie  *Categorie;
	virtual void __fastcall Personnaliser(void);
	virtual void __fastcall IniGrille (TStringGrid *grille);
	virtual void __fastcall VersGrille (TStringGrid *grille);
	virtual void __fastcall DeGrille (TStringGrid *grille);
	virtual bool __fastcall ControleCell(int col,int row);
	virtual void __fastcall SaisirCell(int col,int row);

public:// Déclarations de l'utilisateur
	CL_EtatSortie *EtatSortie;
	CL_Agriculteur *Agri;
	void __fastcall AffEtatSortie(void);

	void TexteChaine(void);

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_BtDico;
	AnsiString LC_DefEtatSortieFrm;
	AnsiString LC_RGModifiable;
	AnsiString LC_BtBnResultat;
	AnsiString LC_BtBnDico;
	AnsiString LC_LabelModifie;
	AnsiString LC_Inserer;
	AnsiString LC_SupLigne;
	AnsiString LC_LigneVide;
	AnsiString LC_Trait;
	AnsiString LC_Titre;

	void __fastcall PossibleModifier(bool modifiable);
	__fastcall TDefEtatSortieFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TDefEtatSortieFrm *DefEtatSortieFrm;
//---------------------------------------------------------------------------
#endif
