//---------------------------------------------------------------------------
#ifndef GereAgriH
#define GereAgriH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <checklst.hpp>
#include <Grids.hpp>

#define CREATION 1
#define COPIE    2
//---------------------------------------------------------------------------
class TGereAgriFrm: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*PanAgri;

	TButton *BtDonnees;
	TButton *BtNouveau;
	TButton *BtCopier;
	TButton *BtSupprimer;
	TButton *BtModifie;
	TButton *BtVariante;

	TBitBtn *BtBnFermer;
	TBitBtn *BtBnQuitter;

	TStringGrid *GrilleAgri;
	TRadioGroup *RGVariante;
	TRadioGroup *RGNote;
	TButton *BtElaguer;
	TRadioGroup *RGClasserCritere;
	TBitBtn *BtBnClasser;
	TBitBtn *BtBnNotes;
	TBitBtn *BtBnAide;

	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);

	void __fastcall BtDonneesClick(TObject *Sender);
	void __fastcall BtNouveauClick(TObject *Sender);
	void __fastcall BtCopierClick(TObject *Sender);
	void __fastcall BtSupprimerClick(TObject *Sender);
	void __fastcall BtModifieClick(TObject *Sender);
	void __fastcall BtVarianteClick(TObject *Sender);

	void __fastcall BtBnQuitterClick(TObject *Sender);

	void __fastcall GrilleAgriClick(TObject *Sender);
	void __fastcall GrilleAgriDblClick(TObject *Sender);
//	void __fastcall BtVarianteNouveauClick(TObject *Sender);

	void __fastcall RGVarianteClick(TObject *Sender);
	void __fastcall RGNoteClick(TObject *Sender);
//    void __fastcall BtBnClasserClick(TObject *Sender);
	void __fastcall BtElaguerClick(TObject *Sender);
	void __fastcall RGClasserCritereClick(TObject *Sender);
	void __fastcall BtBnClasserClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BtBnNotesClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
	void __fastcall BtBnAideClick(TObject *Sender);
private:// Déclarations de l'utilisateur
	int Row;
	int LarColAgri;
	TStringList *S_List;
	bool AvecVariante;
	void __fastcall etablit(int* Cletri,int *cle,int *finCle,int cMax,
			int c,int debut);
	void __fastcall affiche(int* cleTri,int cMax);
	void __fastcall CompareNom(int i,int j);
	void __fastcall Compare(int c,int i,int j);
	int __fastcall finDeAs(int c,int iDeb);

	void __fastcall VideGrille(TStringGrid *grille);
	void __fastcall TrouveEnCours(void);
	void __fastcall TriAgriAlpha(void);

	CL_Agriculteur* __fastcall trouveAncetre(CL_Agriculteur *agri);
	bool __fastcall elagueAgri(CL_Agriculteur *agri);
	bool __fastcall filsSupprimable(CL_Agriculteur *agri);

	AnsiString L_PasAgri;
//    AnsiString L_Utilise;
	AnsiString L_ADesVar;
	AnsiString L_SupQ;
//    AnsiString L_SupT;
	AnsiString L_Elaguer;
	AnsiString L_VarDe;
//    AnsiString L_Agri;
	AnsiString L_NbVar;
	AnsiString L_NoVar;
//	AnsiString L_QuitQ;
//    AnsiString L_QuitT;    

public:// Déclarations de l'utilisateur
	int Origine;
	int Message;
	AnsiString Notes;
	CL_Agriculteur *NouvAgri;
	void __fastcall AffAgri(CL_Agriculteur *agri);
	void __fastcall CreeGrilleAgri(void);
	void __fastcall AffLesVariantes(CL_Agriculteur *agri);
	void __fastcall CreeTVVariante(void);
	void TexteChaine(void);
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_BtClasser;
	AnsiString LC_BtBnClasserAlpha;
	AnsiString LC_RGClasserCritere;
	AnsiString LC_BtBnCopier;
	AnsiString LC_BtCriteres;
	AnsiString LC_BtDonnees;
	AnsiString LC_GereAgriFrm;
	AnsiString LC_BtModifie;
	AnsiString LC_RGNote;
	AnsiString LC_BtNouveau;
	AnsiString LC_BtBnQuitter;
	AnsiString LC_BtBnSupBesTrav;
	AnsiString LC_BtElaguer;
	AnsiString LC_BtVariante;
	AnsiString LC_CltAlpha;
	AnsiString LC_CltAlaDemande;

	__fastcall TGereAgriFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereAgriFrm *GereAgriFrm;
//---------------------------------------------------------------------------
#endif
