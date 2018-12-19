//---------------------------------------------------------------------------

#ifndef AniInvH
#define AniInvH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TMvtAniFrm: public TForm {
	__published: // Composants gérés par l'EDI
TStringGrid	*Grille;
	TLabel *LabNom;
	TBitBtn *BtBnOK;
	TLabel *LabDest;
	TLabel *LabOrig;
	TMaskEdit *MEdOrig;
	TMaskEdit *MEdDest;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormKeyPress(TObject *Sender, char &Key);
	void __fastcall GrilleClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall GrilleSelectCell(TObject *Sender, int ACol, int ARow,
			bool &CanSelect);
	void __fastcall BtBnOKClick(TObject *Sender);
private: // Déclarations utilisateur
	TStringGrid *GrilleAgri;
	int N;
	float Debut;
	int RowPrec;
	CL_InvAni *InvAni;
	float __fastcall EffFin(void);

public:// Déclarations utilisateur
	__fastcall TMvtAniFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMvtAniFrm *MvtAniFrm;
//---------------------------------------------------------------------------
#endif
