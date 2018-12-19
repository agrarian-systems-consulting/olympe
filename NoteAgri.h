//---------------------------------------------------------------------------
#ifndef NoteAgriH
#define NoteAgriH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TNoteAgriFrm: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*Panel1;
	TMemo *Memo;
	TPanel *PanBas;
	TBitBtn *BtBnFermer;
	TBitBtn *BtBnAnnule;
	TBitBtn *BtBnVideTout;
	TBitBtn *BtBnImp;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall MemoChange(TObject *Sender);
	void __fastcall BtBnAnnuleClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall BtBnVideToutClick(TObject *Sender);
	void __fastcall BtBnImpClick(TObject *Sender);
protected: // Déclarations de l'utilisateur
	bool Modif;
public:// Déclarations de l'utilisateur
	CL_Categorie *Categorie;
	CL_Calendrier *Calendrier;
	CL_Atelier *Atelier;
	CL_Agriculteur *Agri;
	CL_Ensemble *Ensemble;
	CL_Tendance *Tendance;
	CL_Indicateur *Indicateur;
	CL_EtatSortie *EtatSortie;

	AnsiString VientDe;
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_BtBnNotes;
	AnsiString LC_Panel1;

	__fastcall TNoteAgriFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TNoteAgriFrm *NoteAgriFrm;
//---------------------------------------------------------------------------
#endif
