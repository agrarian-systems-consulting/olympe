//---------------------------------------------------------------------------

#ifndef SortieEcranH
#define SortieEcranH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSortieEcranFrm: public TForm {
	__published: // Composants gérés par l'EDI
TRichEdit	*Memo1;
	TPanel *Panel1;
	TBitBtn *BitBtn1;
	void __fastcall BtBnImprimerClick(TObject *Sender);
private: // Déclarations utilisateur
	int size0,size1,size2;
	int LarTrait;
	AnsiString AsLambda;
	AnsiString AsBlanc;
	AnsiString Marge1,Marge2,Marge3;
	int posNom,posUnite,posVal,delta;

	void EnTeteDate(void);
	void TypeImp(char *police,int size,TColor couleur,char style);
	bool EstVide(float *vecteur);

//	void Titre1(char *titre,                 TColor=clBlack);
	void Titre2(char *titre, TColor=clBlack);
	void Titre3(char *titre, TColor=clBlack);
	void An(int an0, TColor=clBlack);
	void Total(AnsiString nom, float *valeur,TColor=clBlack);
	void Trait(void);
	void Blanc(int nli=1, TColor=clBlack);

//    void placer(AnsiString ss,int pos);
	void placer(float val,int pos, int apresVirgule);

	void Resultat(AnsiString nom, float *valeur, TColor=clBlack);
	void Resultat(AnsiString nom, int *valeur, TColor=clBlack);

//    AnsiString __fastcall TexteCaption(CL_Agriculteur *agri);
//    void  Valeur(CL_Agriculteur *agri);
	void CategorieV(
			char *titre,
			CL_Vecteur<CL_Categorie> *vCategorie,
			CL_Vecteur<CL_QuanVal> *vProduit,
			float *total,
			CL_Vecteur<CL_QuanVal> *vCatTot);

public:// Déclarations utilisateur
	CL_Agriculteur *Agri;
	void Demarre(void);
	void Valeur(CL_Agriculteur *agri);
	void Titre1(char *titre, TColor=clBlack);

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_SortieEcranFrm;

	__fastcall TSortieEcranFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSortieEcranFrm *SortieEcranFrm;
//---------------------------------------------------------------------------
#endif
