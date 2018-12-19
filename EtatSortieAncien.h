//---------------------------------------------------------------------------
#ifndef EtatSortieAncienH
#define EtatSortieAncienH
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
#include <ActnList.hpp>
//---------------------------------------------------------------------------
//TStringList *TSFamille;

//----------------------------------------------------------------------------
class TEtatSortieFrm: public TForme00Frm {
	__published: // Composants gérés par l'EDI
TLabel	*LabEtatSortie;

	TListBox *LBService;
	TRadioGroup *RGModifiable;
	TLabel *LabDonnee;
	TBitBtn *BtSup;
	TBitBtn *BtBnResultat;
	TBitBtn *BtBnDico;
	TLabel *LabNom;
//	void __fastcall BoutEditClick(TObject *Sender);

//	void __fastcall TVChoixDblClick(TObject *Sender);

	void __fastcall LBServiceClick(TObject *Sender);
//	void __fastcall BtClasserClick(TObject *Sender);
	void __fastcall RGModifiableClick(TObject *Sender);
	void __fastcall BtBnStockerClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtSupClick(TObject *Sender);
	void __fastcall BoutFermerClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall BtBnResultatClick(TObject *Sender);
	void __fastcall BtBnDicoClick(TObject *Sender);
private:
	void __fastcall Inserer(void);
	void __fastcall Supprimer(void);
	void __fastcall Blanc(void);
	void __fastcall Trait(void);
	void __fastcall Titre(void);

public:

	CL_EtatSortie *EtatSortie;
	CL_Agriculteur *Agri;
	void __fastcall Personnaliser(void);
	void __fastcall DefinirLesGrilles(void);
	void __fastcall IniGrille(TStringGrid *grille);
	void __fastcall CellDebut(void);
	void __fastcall SaisirCell(int col,int row);
	bool __fastcall ControleCell(int col,int row);
	void __fastcall VersGrille(TStringGrid *grille);
	void __fastcall DesGrilles(void);
	void __fastcall AffEtatSortie(void);
	bool __fastcall Stocker(void);

	void __fastcall CreeTVChoix(TTreeView *tVChoix);

	void __fastcall Branche(TTreeView *tVChoix, TTreeNode *tn1);

	void __fastcall Branche(TTreeView *tVChoix, TTreeNode *tn1,int noFamille,
			CL_Vecteur<CL_Categorie> *v_Cat,CL_Vecteur<CL_Item> *v_Prod);

	void __fastcall Branche(TTreeView *tVChoix, TTreeNode *tn1,int noFamille,
			CL_Vecteur<CL_Item> *v_Prod);
	void __fastcall PlaceEltForme(CL_Elt *elt);
	void __fastcall PossibleModifier(bool modifiable);

	__fastcall TEtatSortieFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEtatSortieFrm *EtatSortieFrm;
//---------------------------------------------------------------------------
#endif
