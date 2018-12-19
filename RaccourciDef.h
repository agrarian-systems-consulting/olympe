//---------------------------------------------------------------------------

#ifndef RaccourciDefH
#define RaccourciDefH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <fstream>
#include <iostream>

//---------------------------------------------------------------------------
class TRaccourciDefFrm: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*PanH;
	TPanel *PanB;
	TStringGrid *SG;
	TPanel *PanD;
	TTreeView *TV;
	TGroupBox *GBClasser;
	TBitBtn *BtBnClBas;
	TBitBtn *BtBnClHaut;
	TBitBtn *BtSup;
	TBitBtn *BtBnVideTout;
	TBitBtn *BtBnSave;
	TBitBtn *BtBnClose;
	TLabel *LabelModifie;
	TButton *Button1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall SGClick(TObject *Sender);
	void __fastcall SGKeyPress(TObject *Sender, char &Key);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall BtBnVideToutClick(TObject *Sender);
	void __fastcall BtSupClick(TObject *Sender);
	void __fastcall BtBnClBasClick(TObject *Sender);
	void __fastcall BtBnClHautClick(TObject *Sender);
	void __fastcall BtBnSaveClick(TObject *Sender);
	void __fastcall TVChange(TObject *Sender, TTreeNode *Node);
private: // Déclarations de l'utilisateur
	void VersSG(void);
	void DeSG(void);
	void TailleSG(int r);
	void EcrireFichier(void);
	void LireFichier(void);

public:// Déclarations de l'utilisateur
	TStringList *SLstRaccourci;
	void RetourDeTVDico(char *NomFamille,char* NomCategorie,char* NomItem);
	__fastcall TRaccourciDefFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRaccourciDefFrm *RaccourciDefFrm;
//---------------------------------------------------------------------------
#endif
