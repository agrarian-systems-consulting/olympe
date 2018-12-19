//---------------------------------------------------------------------------

#ifndef SorRapPrepH
#define SorRapPrepH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>

class CL_Raccourci {
public:
	AnsiString Alias;
};
//---------------------------------------------------------------------------
class TSorRapPrepFrm: public TForm {
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
	TBitBtn *BtBnStocker;
	TBitBtn *BtBnClose;
	TLabel *LabelModifie;
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
	void __fastcall BtBnStockerClick(TObject *Sender);
	void __fastcall TVChange(TObject *Sender, TTreeNode *Node);
private: // Déclarations de l'utilisateur
	void VersSG(void);
	void DeSG(void);
	void TailleSG(int r);

public:// Déclarations de l'utilisateur
	TStringList *SLstRaccourci;
	void RetourDeTVDico(char *NomFamille,char* NomCategorie,char* NomItem);
	__fastcall TSorRapPrepFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSorRapPrepFrm *SorRapPrepFrm;
//---------------------------------------------------------------------------
#endif
