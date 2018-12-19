//---------------------------------------------------------------------------

#ifndef GereIndicH
#define GereIndicH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "GereAtelier.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGereIndicFrm: public TGereAtelierFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall FormActivate(TObject *Sender);void __fastcall TVClick(TObject *Sender);void __fastcall TVDblClick(TObject *Sender);void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);

	void __fastcall BtCatCopierClick(TObject *Sender);void __fastcall BtAtelierCreerClick(TObject *Sender);void __fastcall BtAtelierSupprimerClick(TObject *Sender);void __fastcall BtAtelierCopierClick(TObject *Sender);void __fastcall BtAtelierModifClick(TObject *Sender);void __fastcall BtCatNettoyerClick(TObject *Sender);bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private:
	// Déclarations utilisateur
	CL_Indicateur *Indic;

protected:
	virtual void __fastcall AffAtelier(void);virtual bool __fastcall VerifNomAtelier(AnsiString newNom,int action);virtual bool __fastcall CEstBon(void);virtual void __fastcall StockerOrdre(void);virtual void __fastcall CreeTV(void);

public:
	// Déclarations utilisateur
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_GereIndicFrm;
	AnsiString LC_GBAtelier_A;

	__fastcall TGereIndicFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereIndicFrm *GereIndicFrm;
//---------------------------------------------------------------------------
#endif
