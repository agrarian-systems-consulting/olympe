//---------------------------------------------------------------------------

#ifndef GereCatItemH
#define GereCatItemH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGereCatItemFrm: public TForm {
	__published: // Composants gérés par l'EDI
TListBox	*LB;
	TBitBtn *BtBnFermer;
	TBitBtn *BtBnQuitter;
	TLabel *LabelModifie;
	TGroupBox *GBEnsemble;
	TBitBtn *BtBnImp;
	TGroupBox *GBCategorie;
	TBitBtn *BtBnCreer;
	TButton *BtSupprimer;
	TButton *BtModifier;
	TBitBtn *BtBnCopier;
	TButton *BtClasser;
	TPanel *PClasst;
	TBitBtn *BtClHaut;
	TBitBtn *BtClBas;
	TBitBtn *BtBnFermClasst;
	TButton *BtClAlpha;
	TBitBtn *BtBnAide;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall LBClick(TObject *Sender);
	void __fastcall BtBnCreerClick(TObject *Sender);
	void __fastcall BtSupprimerClick(TObject *Sender);
	void __fastcall BtModifierNomClick(TObject *Sender);
	void __fastcall BtBnQuitterClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall BtBnImpClick(TObject *Sender);
	void __fastcall BtClasserClick(TObject *Sender);
	void __fastcall BtClHautClick(TObject *Sender);
	void __fastcall BtClBasClick(TObject *Sender);
	void __fastcall BtBnFermClasstClick(TObject *Sender);
	void __fastcall BtBnCopierClick(TObject *Sender);
	void __fastcall BtClAlphaClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
	void __fastcall BtBnAideClick(TObject *Sender);
private: // Déclarations de l'utilisateur
	void RegleProbleme(void);///??? Affreux
protected:
	bool OrdreModif;
	int No;
	CL_Categorie *Categorie;

	virtual void __fastcall Personnaliser(void);
	virtual bool __fastcall NouvelleCategorie(void);
//	virtual void __fastcall VerifNomCat(AnsiString newNom,int action);
	virtual bool __fastcall VerifNomCat(AnsiString newNom,int action);//230804
	virtual void __fastcall StockerOrdre(CL_Vecteur<CL_Categorie> *vecteur);

public:// Déclarations de l'utilisateur
	int Origine;
	int Nature;
	void TexteChaine(void);

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString L_PasSel;
	AnsiString L_Impo;
	AnsiString L_ModifNom;
	AnsiString L_NouvCat;
	AnsiString L_RienACop;
	AnsiString L_Prob;
	AnsiString L_PasNom;
	AnsiString L_Existe;
	AnsiString L_Erreur;
	AnsiString L_JSup;
	AnsiString L_Sup;
	AnsiString L_Modif;
	AnsiString L_Prod;
	AnsiString L_ChOp;
	AnsiString L_CleClass;
	AnsiString L_Ani;
	AnsiString L_ChStruct;
	AnsiString L_RecDiv;
	AnsiString L_DepDiv;
	AnsiString L_RecFam;
	AnsiString L_DepFam;
	AnsiString L_Var;
	AnsiString L_Exter;
	AnsiString L_CopieDe;

	AnsiString LC_BtBnAlpha;
	AnsiString LC_BtClasser;
	AnsiString LC_BtBnCopier;
	AnsiString LC_BtBnCreer;
	AnsiString LC_BtBnFermer;
	AnsiString LC_GereCatItemFrm;
	AnsiString LC_BtModifier;
	AnsiString LC_LabelModifie_A;
	AnsiString LC_BtBnQuitter;
	AnsiString LC_BtBnSupBesTrav;

	__fastcall TGereCatItemFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereCatItemFrm *GereCatItemFrm;
//---------------------------------------------------------------------------
#endif
