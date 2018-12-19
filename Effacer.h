//---------------------------------------------------------------------------

#ifndef EffacerH
#define EffacerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <CheckLst.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TEffacerFrm: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*PanUnite;
	TPanel *PanIndic;
	TGroupBox *GBAgri;
	TGroupBox *GBEnsemble;
	TCheckListBox *ChLBUnite;
	TCheckListBox *ChLBIndEtat;
	TCheckBox *ChBAgri;
	TCheckBox *ChBEnsemble;
	TBitBtn *BtBnFermer;
	TBitBtn *BtBnEffacer;
	TLabel *LabInd;
	TGroupBox *GBAlea;
	TCheckListBox *ChLBAlea;
	TGroupBox *GBProduction;
	TCheckListBox *ChLBAtelier;
	TGroupBox *GBDefinition;
	TCheckListBox *ChLBDef;
	TBitBtn *BtDefAucun;
	TBitBtn *BtDefTous;
	TBitBtn *BtProAucun;
	TBitBtn *BtProTous;
	TBitBtn *BtIndAucun;
	TBitBtn *BtIndTous;
	TGroupBox *GBTypologie;
	TCheckBox *ChBClassif;
	TCheckBox *ChBTypoAgri;
	TButton *Button1;

	void __fastcall BtBnOKClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
//    void __fastcall BtBnPasOKClick(TObject *Sender);
	void __fastcall BtBnFermerClick(TObject *Sender);
	void __fastcall BtDefAucunClick(TObject *Sender);
	void __fastcall BtDefTousClick(TObject *Sender);
	void __fastcall BtProAucunClick(TObject *Sender);
	void __fastcall BtProTousClick(TObject *Sender);
	void __fastcall BtIndAucunClick(TObject *Sender);
	void __fastcall BtIndTousClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
	void __fastcall Button1Click(TObject *Sender);
private:// Déclarations utilisateur
	void __fastcall cocher(void);
	void __fastcall effacer(void);
	void __fastcall avantEffacerIndic(void);
	AnsiString L_NettoyerQ;
	AnsiString L_NettoyerT;
public:// Déclarations utilisateur
	void TexteChaine(void);
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_GBAgri;
	AnsiString LC_GBAlea;
	AnsiString LC_BtIndAucun;
	AnsiString LC_LabZone;
	AnsiString LC_LabInd;
	AnsiString LC_GBDefinition;
	AnsiString LC_Label11;
	AnsiString LC_EffacerFrm;
	AnsiString LC_ChBEnsemble;
	AnsiString LC_GBEnsemble;
	AnsiString LC_BtBnEffacer;
	AnsiString LC_PanClassif;
	AnsiString LC_PRODUCTIONS;
	AnsiString LC_BtIndTous;

	AnsiString LC_ChOpe;
	AnsiString LC_Exter;
	AnsiString LC_Troupeaux;
	AnsiString LC_PerTrav;
	AnsiString LC_ChStruct;
	AnsiString LC_DepDiv;
	AnsiString LC_RecDiv;
	AnsiString LC_RecFam;
	AnsiString LC_DepFam;
	AnsiString LC_Var;

	AnsiString LC_Cultures;
	AnsiString LC_Animaux;
	AnsiString LC_Phases;
	AnsiString LC_Perennes;
	AnsiString LC_Vivriers;

	AnsiString LC_Agri;
	AnsiString LC_Ensemble;
	AnsiString LC_Classif;
	AnsiString LC_TypoAgri;

	AnsiString LC_Prix;
	AnsiString LC_Quantite;

	AnsiString LC_Indic;
	AnsiString LC_Etat;
	AnsiString LC_Comp;
	AnsiString LC_Typologie;
	__fastcall TEffacerFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEffacerFrm *EffacerFrm;
//---------------------------------------------------------------------------
#endif
