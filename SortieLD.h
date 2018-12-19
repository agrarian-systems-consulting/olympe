//---------------------------------------------------------------------------

#ifndef SortieLDH
#define SortieLDH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TSortieLDFrm: public TForm {
	__published: // Composants gérés par l'EDI
TStringGrid	*SG;
	TPanel *PanB;
	TBitBtn *BtBnMoin10;
	TBitBtn *BtBnPlus10;
	TRadioGroup *RGPrecision;
	TBitBtn *BtBnVersExcel;
	void __fastcall BtBnPlus10Click(TObject *Sender);
	void __fastcall BtBnMoin10Click(TObject *Sender);
	void __fastcall SGDrawCell(TObject *Sender, int ACol, int ARow,
			TRect &Rect, TGridDrawState State);
	void __fastcall BtBnVersExcelClick(TObject *Sender);
private: // Déclarations de l'utilisateur
	void AffQuantite(int noSerie,CL_AgriRes *resultat);
	int AffQuantiteDetail(int rowDeb,AnsiString titre,int noSerie,
			CL_Vecteur<CL_Categorie>*vCategorie,
			CL_Vecteur<CL_QuanVal>*vQuanVal);

	void AffValeur(int noSerie,CL_AgriRes *resultat);
	int AffValeurDetail(int rowDeb,AnsiString titre,AnsiString titreTotal,int noSerie,
			CL_Vecteur<CL_Categorie> *vCategorie,
			CL_Vecteur<CL_QuanVal> *vProduit,
			float *total,
			CL_Vecteur<CL_QuanVal> *vCatTot);
	int AffValeurResultat(int rowDeb,AnsiString titre,int noSerie,float *valeur);
	int AffImmo(int rowDeb,CL_AgriRes *resultat,int noSerie);
	int AffEmprunt(int rowDeb,CL_AgriRes *resultat,int noSerie);
	int AffTva(int rowDeb,AnsiString titre,AnsiString titre1,int noSerie,float *valeur);

	void AffCeg(int noSerie,CL_AgriRes *resultat);
	void AffCegTitre(void);
	void AffCegValeur(int noSerie,CL_AgriRes *resultat);

	void VideGrille(void);

	AnsiString Aff(float x,int digits);
	void AffVal(int c0,int r,float *valeur,int digits=0);

public:// Déclarations de l'utilisateur
	void DimGrille(int nature);
	void Aff(int nature);
	CL_Agriculteur *Agri;
	int Nature;
	__fastcall TSortieLDFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSortieLDFrm *SortieLDFrm;
//---------------------------------------------------------------------------
#endif
