//---------------------------------------------------------------------------

#ifndef AgriAtelierMargeH
#define AgriAtelierMargeH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TAgriAtelierMargeFrm: public TForm {
	__published: // Composants gérés par l'EDI
TPanel	*Panel1;
	TBitBtn *BtBnImp;
	TBitBtn *BtBnExcel;
	TBitBtn *BoutFermer;
	TBitBtn *BtBnQuitter;
	TStringGrid *Grille;
	TPanel *Panel2;
	TLabel *LabNomAtelier;
	TButton *BtSyntDetail;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtSyntDetailClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtBnQuitterClick(TObject *Sender);
	void __fastcall BtBnImpClick(TObject *Sender);
	void __fastcall BtBnExcelClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);

private: // Déclarations utilisateur
	float TotProd[N_X];
	float TotCharge[N_X];
	float Marge[N_X];

	void __fastcall Calcul(void);
	void __fastcall AffDetail(void);
	void __fastcall AffSynthese(void);

//    AnsiString L_Produit;
	AnsiString L_TotProd;
	//AnsiString L_Charge;
	AnsiString L_TotCharge;
//	AnsiString L_Marge;
	AnsiString L_Detail;
	AnsiString L_Synthese;
	AnsiString L_QuitQ;
	AnsiString L_QuitM;
	//Caption
	void IniCaption(void);
	AnsiString LC_LabNomAtelier;
	AnsiString LC_AgriAtelierMargeFrm;
	AnsiString LC_BtBnQuitter;
	AnsiString LC_BtSyntDetail;

public:// Déclarations utilisateur
	bool Arret;
	bool Detail;
	CL_Agriculteur *Agri;
	CL_Atelier *Atelier;
	CL_Vecteur<CL_QuanVal> *V_Produit;
	CL_Vecteur<CL_QuanVal> *V_Charge;
	CL_Vecteur<CL_QuanVal> *V_Exter;
	void TexteChaine(void);
	void TexteCaption(void);

	__fastcall TAgriAtelierMargeFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAgriAtelierMargeFrm *AgriAtelierMargeFrm;
//---------------------------------------------------------------------------
#endif
