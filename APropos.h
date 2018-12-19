//---------------------------------------------------------------------------
#ifndef AProposH
#define AProposH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TAProposFrm: public TForm {
	__published: // Composants gérés par l'EDI
TLabel	*LabNom1;
	TLabel *LabVersion;
	TLabel *LabInra;
	TImage *Image;
	TLabel *LabComp;
	TLabel *LabDate;
	TLabel *LabLimite;
	void __fastcall FormActivate(TObject *Sender);
private: // Déclarations de l'utilisateur
	AnsiString LC_APropos;
public:// Déclarations de l'utilisateur
	void TexteCaption(void);

	__fastcall TAProposFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAProposFrm *AProposFrm;
//---------------------------------------------------------------------------
#endif
