//---------------------------------------------------------------------------

#ifndef TravGraphH
#define TravGraphH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TTravGraphFrm: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*PanelBas;
	TBitBtn *BtBnQuitter;
	TBitBtn *BtBnImp;
	TBitBtn *BtBnValeur;
	void __fastcall FormResize(TObject *Sender);
	void __fastcall BtImpClick(TObject *Sender);
	void __fastcall BtBnValeurClick(TObject *Sender);
private: // Déclarations utilisateur
	TCanvas *LeCanvas;
	int LaHeight;
	int LaWidth;

	int LEcran,HEcran;
	int XGauche,XDroit;
	int YBas,YHaut;
	float EchelleH;

	int __fastcall Xde(int x);
	int __fastcall Yde(int y);
	void __fastcall TraitHor(int y, int x0,int x1,int width);
	void __fastcall TraitVer(int x, int y0,int y1,int width);
	void __fastcall CoordSPeriodes(void);
	void __fastcall AffDatePeriodes(void);
	void __fastcall AffNbOuv(void);
	void __fastcall AffUnOuv(int n,float hauteur);
	void __fastcall AffBesoins(void);
	void __fastcall Histo(CL_Atelier *atelier,int n,float h,float *bas);
	void __fastcall AffTitre(void);
	void __fastcall Legende(void);

	char *__fastcall ChaineDate(int J);

public:// Déclarations utilisateur
	void __fastcall Dessiner(void);
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_TravGraphFrm;
	AnsiString LC_BtBnCalcul;

	__fastcall TTravGraphFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTravGraphFrm *TravGraphFrm;
//---------------------------------------------------------------------------
#endif
