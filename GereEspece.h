//---------------------------------------------------------------------------

#ifndef GereEspeceH
#define GereEspeceH
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
class TGereEspeceFrm: public TGereAtelierFrm {
	__published: // Composants gérés par l'EDI
	void __fastcall FormActivate(TObject *Sender);void __fastcall TVClick(TObject *Sender);void __fastcall TVDblClick(TObject *Sender);

	void __fastcall BtCatSupprimerClick(TObject *Sender);void __fastcall BtCatCopierClick(TObject *Sender);void __fastcall BtCatModifNomClick(TObject *Sender);

	void __fastcall BtAtelierCreerClick(TObject *Sender);void __fastcall BtCatCreerClick(TObject *Sender);void __fastcall BtAtelierCopierClick(TObject *Sender);bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);void __fastcall BtBnImpClick(TObject *Sender);void __fastcall BtBnExcelClick(TObject *Sender);

private:
	// Déclarations de l'utilisateur
	void __fastcall modifQtePhase(CL_Atelier *atelier);void __fastcall modifQtePhase1(CL_Vecteur<CL_ItemParAtelier>*vecteur,int nb1,int nb2);

protected:
	CL_Espece *Espece;virtual void __fastcall Personnaliser(void);

	virtual bool __fastcall VerifNomCat(AnsiString newNom,int action);virtual bool __fastcall VerifNomAtelier(AnsiString newNom,int action);virtual void __fastcall StockerOrdre(void);virtual void __fastcall AffAtelier(void);

public:
	// Déclarations de l'utilisateur
	void __fastcall RetourDeDefEspece(void);
	void TexteCaption(void);
	void IniCaption(void);
	AnsiString LC_GereEspeceFrm;

	__fastcall TGereEspeceFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGereEspeceFrm *GereEspeceFrm;
//---------------------------------------------------------------------------
#endif
