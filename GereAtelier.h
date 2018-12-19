//---------------------------------------------------------------------------
#ifndef GereAtelierH
#define GereAtelierH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>

#define CREATION 1
#define COPIE    2

//---------------------------------------------------------------------------
class TGereAtelierFrm: public TForm {
	__published: // Composants gérés par l'EDI
TLabel	*LabelModifie;
	TBitBtn *BtBnFermer;
	TTreeView *TV;
	TBitBtn *BtBnQuitter;

	TGroupBox *GBEnsemble;

	TGroupBox *GBCategorie;

	TBitBtn *BtCatCreer;
	TBitBtn *BtCatSupprimer;
	TBitBtn *BtCatNettoyer;
	TBitBtn *BtCatCopier;
	TBitBtn *BtCatModifNom;

	TGroupBox *GBAtelier;

	TBitBtn *BtAtelierSupprimer;
	TBitBtn *BtAtelierCreer;
	TBitBtn *BtAtelierCopier;
	TBitBtn *BtAtelierModifNom;

	TButton *BtClasser;

	TPanel *PClasst;
	TBitBtn *BtClHaut;
	TBitBtn *BtClBas;
	TBitBtn *BtClasstFin;
	TBitBtn *BtBnAlpha;
	TBitBtn *BtBnImp;
	TBitBtn *BtBnExcel;

	void __fastcall FormActivate(TObject *Sender);

	void __fastcall BtBnFermerClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall TVDblClick(TObject *Sender);

	void __fastcall BtBnQuitterClick(TObject *Sender);
	void __fastcall TVClick(TObject *Sender);
	void __fastcall BtClHautClick(TObject *Sender);
	void __fastcall BtClBasClick(TObject *Sender);
	void __fastcall BtBnFermClasstClick(TObject *Sender);

	void __fastcall BtCatCreerClick(TObject *Sender);
	void __fastcall BtCatSupprimerClick(TObject *Sender);
	void __fastcall BtCatNettoyerClick(TObject *Sender);
	void __fastcall BtCatCopierClick(TObject *Sender);
	void __fastcall BtCatModifNomClick(TObject *Sender);

	void __fastcall BtAtelierCreerClick(TObject *Sender);
	void __fastcall BtAtelierSupprimerClick(TObject *Sender);
	void __fastcall BtAtelierCopierClick(TObject *Sender);
	void __fastcall BtAtelierModifClick(TObject *Sender);
	void __fastcall BtClasserClick(TObject *Sender);
	void __fastcall BtBnCopierDansClick(TObject *Sender);
	void __fastcall TVCompare(TObject *Sender, TTreeNode *Node1,
			TTreeNode *Node2, int Data, int &Compare);
	void __fastcall BtBnAlphaClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
	void __fastcall BtBnImpClick(TObject *Sender);
	void __fastcall BtBnExcelClick(TObject *Sender);

protected:
	int No;
	CL_Categorie *Categorie;
	CL_Atelier *Atelier;
	virtual void __fastcall Personnaliser(void);
	virtual void __fastcall BtCatEnabled(bool aff);
	virtual void __fastcall BtAtelierEnabled(bool aff);
	virtual bool __fastcall VerifNomCat(AnsiString newNom,int action);
	virtual void __fastcall CreeTV(void);
	virtual void __fastcall AffAtelier(void);
	virtual bool __fastcall CEstBon(void);
	virtual bool __fastcall VerifNomAtelier(AnsiString newNom,int action);
	virtual void __fastcall StockerOrdre(void);

public: // Déclarations de l'utilisateur
	int Nature;
	int Origine;
	int Message;
	bool OrdreModif;//pour utilisation dans GereIndic

	void TexteChaine(void);
	AnsiString L_NouvCatCopDe;
	AnsiString L_ModifNomCat;
	AnsiString L_PasCatSel;
	AnsiString L_NouvAtelier;
	AnsiString L_AtUtil;
	AnsiString L_ModifNomAt;
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_BtBnAlpha;
	AnsiString LC_AtelierFrm;
	AnsiString LC_RGCat;
	AnsiString LC_GereAtelierFrm;
	AnsiString LC_BtClasser;
	AnsiString LC_BtBnCopier;
	AnsiString LC_BtBnCreer;
	AnsiString LC_BtModifier;
	AnsiString LC_LabelModifie_A;
	AnsiString LC_BtBnEffacer;
	AnsiString LC_BtBnQuitter;
	AnsiString LC_BtBnSupBesTrav;

	__fastcall TGereAtelierFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereAtelierFrm *GereAtelierFrm;
//---------------------------------------------------------------------------
#endif
