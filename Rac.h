//---------------------------------------------------------------------------

#ifndef RacH
#define RacH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include "RacDef.h"

//---------------------------------------------------------------------------
class TRacFrm: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*PanH;
	TPanel *PanB;
	TListBox *LBRac;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall LBRacClick(TObject *Sender);
private: // Déclarations de l'utilisateur
	void VersLBRac(TStringList *sLst);
	void TraiterElt(CL_EltRac *elt0);
	int TrouveLBNo(TListBox *lB,AnsiString as);
	TTreeNode* TrouveTVNo3(TTreeView *tV,CL_EltRac *eltRac);
	TTreeNode* TrouveTVNo1(TTreeView *tV,AnsiString as0,AnsiString as1);
public:// Déclarations de l'utilisateur
	__fastcall TRacFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRacFrm *RacFrm;
//---------------------------------------------------------------------------
#endif
