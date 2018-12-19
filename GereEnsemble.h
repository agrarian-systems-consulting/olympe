//---------------------------------------------------------------------------
#ifndef GereEnsembleH
#define GereEnsembleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TGereEnsembleFrm: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*PanEnsemble;
	TButton *BtSupprimer;
	TButton *BtCopier;
	TButton *BtNouveau;
	TButton *BtRenomme;
	TButton *BtEffectif;
	TBitBtn *BtBnFermer;
	TButton *BtResultat;
	TRadioGroup *RGVariante;
	TStringGrid *GrilleEns;
	TLabel *LabelModifie;
	TRadioGroup *RGNote;
	TProgressBar *ProgressBar;
	TButton *BtUneExp;
	TButton *BtUneMoy;
	TBitBtn *BtBnAide;
	void __fastcall BtEffectifClick(TObject *Sender);
	void __fastcall BtNouveauClick(TObject *Sender);
	void __fastcall BtCopierClick(TObject *Sender);
	void __fastcall BtSupprimerClick(TObject *Sender);
	void __fastcall BtRenommeClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtResulClick(TObject *Sender);
	void __fastcall BtVarianteClick(TObject *Sender);
	void __fastcall RGVarianteClick(TObject *Sender);
	void __fastcall GrilleEnsClick(TObject *Sender);
	void __fastcall RGNoteClick(TObject *Sender);
	void __fastcall BtUneExpClick(TObject *Sender);
	void __fastcall BtUneMoyClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
	void __fastcall BtBnAideClick(TObject *Sender);
private: // Déclarations de l'utilisateur
	bool EstInitialise;
	bool AvecVariante;
	int ItemIndex;

	void __fastcall VideGrille(TStringGrid *grille);
	void __fastcall AffEns(CL_Ensemble *ens,int r);
	void __fastcall CombienDeVariante(CL_Ensemble *ens,int &n);
	int __fastcall AffLesVariantes(CL_Ensemble *ens,ST_NoEnsemble *ancetre,int r,int nP);
//    void __fastcall Tri(void);
//    void __fastcall CompareNom(int i,int j);
	CL_Vecteur<CL_Ensemble> *V_EnsDepart;
//    void __fastcall majLstVariante(void);
	void __fastcall copierV_Ensemble(void);
	void __fastcall numeroteLesFils(CL_Ensemble *ens,ST_NoEnsemble *Ancetre,int nP);
	void __fastcall TriAlphaEnsemble(void);

public:// Déclarations de l'utilisateur
	AnsiString VientDe;
	void __fastcall CreeGrilleEns(void);
	void __fastcall TrouveEnCours(void);
	void __fastcall SelectionManuelle(void);
	void __fastcall SelectionTri(void);
	void __fastcall SelectionAddition(void);
	void __fastcall Extraction(void);

	void TexteChaine(void);
	AnsiString L_NouvEns;
	AnsiString L_Existe;// Existe déjà
	AnsiString L_Ens;
	AnsiString L_NbVar;
	AnsiString L_NoVar;
	AnsiString L_ACopierSous;//"A Copier sous"

	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_BtUneMoy;
	AnsiString LC_BtUneExp;
	AnsiString LC_BtBnCopier;
	AnsiString LC_BtEffectif;
	AnsiString LC_GereEnsembleFrm;
	AnsiString LC_LabelModifie_A;
	AnsiString LC_BtBnNotes;
	AnsiString LC_BtNouveau;
	AnsiString LC_BtRenomme;
	AnsiString LC_BtBnResultat;
	AnsiString LC_BtBnSupBesTrav;
	AnsiString LC_BtVariante;

	__fastcall TGereEnsembleFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereEnsembleFrm *GereEnsembleFrm;
//---------------------------------------------------------------------------
#endif
