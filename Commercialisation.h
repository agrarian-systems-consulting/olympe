//---------------------------------------------------------------------------

#ifndef CommercialisationH
#define CommercialisationH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
class CL_Comm;
//---------------------------------------------------------------------------
class TCommercialisationFrm: public TForm {
	__published: // Composants gérés par l'EDI
TLabel	*LabProduit;
	TStringGrid *GrilleProd;
	TStringGrid *GrilleComm;
	TLabel *LabelModifie;
	TBitBtn *BtBnProduit;
	TComboBox *CBAn;
	TLabel *LabAnnee;
	TPanel *PanBas;
	TBitBtn *BtBnQuitter;
	TBitBtn *BoutFermer;
	TCheckBox *ChBRepTout;
	TBitBtn *BtBnReportDroit;
	TComboBox *CBAnCopie;
	TBitBtn *BtBnCopier;
	TBitBtn *BtBnCopieTout;
	TLabel *LabQuant;
	TLabel *LabVal;
	TBitBtn *BtBnVenteQ;
	TBitBtn *BtBnStockQ;
	TBitBtn *BtBnVenteVal;
	TBitBtn *BtBnStockVal;
	TBitBtn *BtBnReste;
	TRadioGroup *RgSupprime;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall BtBnProduitClick(TObject *Sender);
	void __fastcall BtBnQuitterClick(TObject *Sender);
	void __fastcall GrilleKeyPress(TObject *Sender, char &Key);
	void __fastcall GrilleProdSelectCell(TObject *Sender, int ACol,
			int ARow, bool &CanSelect);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall GrilleCommSelectCell(TObject *Sender, int ACol,
			int ARow, bool &CanSelect);
	void __fastcall CBAnClick(TObject *Sender);
	void __fastcall BtBnVenteQClick(TObject *Sender);
	void __fastcall BtBnVenteValClick(TObject *Sender);
	void __fastcall GrilleProdEnter(TObject *Sender);
	void __fastcall GrilleCommEnter(TObject *Sender);
	void __fastcall BtBnReportDroitClick(TObject *Sender);
	void __fastcall BtBnStockQClick(TObject *Sender);
	void __fastcall BtBnStockValClick(TObject *Sender);
	void __fastcall BtBnCopierClick(TObject *Sender);
	void __fastcall CBAnCopieClick(TObject *Sender);
	void __fastcall BtBnCopieToutClick(TObject *Sender);
	void __fastcall RgSupprimeClick(TObject *Sender);
	void __fastcall BtBnResteClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
private: // Déclarations utilisateur
	bool EstInitialise;
	void __fastcall IniGrille(void);
	void __fastcall VideGrille(TStringGrid *grille);
	AnsiString __fastcall Aff(float x,int digits);
	float __fastcall GrilleFloat(TStringGrid *grille,int col,int row);
	void __fastcall MarquerCell(int col,int row);
	float __fastcall TotVente(float qProd,bool avecVerif);
	void __fastcall CalculAffReste(int colProd,bool avecTest);
	void __fastcall AutreAnnee(void);

//    CL_Agriculteur *Agri;
	int An_0;
	int AnProd;
	int ColProd;
	int ColComm;
	int ColOuCopier;
	TList *LstComm;
	CL_Comm *CommEnCours;
	void __fastcall IniLstComm(void);
	TStringGrid *GrilleEnCours;
	bool __fastcall OnPeutStocker(void);
	bool __fastcall VerifAnnee(void);
	void __fastcall NettoieLstQuantPrix(CL_Item *item,int anProd);
	CL_Comm* __fastcall TrouveComm(CL_Item *item);

	void __fastcall VersGrilleComm(void);
	void __fastcall VersGrilleProd(void);
	CL_FN_Xp1 * __fastcall TrouveVS(TList *lstVS,CL_Item *item);
	void __fastcall AffVente(int QouV);

	void __fastcall VidelstVS(TList *lstVS);
	void __fastcall AffStock(int QouV);
	void __fastcall AjouterInvendu(void);

//    void __fastcall EtablirStockIni(void);

	float TotQuant[20];

	AnsiString L_Annee;
	AnsiString L_Message;
	AnsiString L_MessT;
//    AnsiString L_QuitQ;
//    AnsiString L_QuitT;
	AnsiString L_TitreG;
	AnsiString L_Quant;
	AnsiString L_Prix;
	AnsiString L_Valeur;
	AnsiString L_PasProd;
	AnsiString L_TotVendu;
	AnsiString L_TotProduit;
	AnsiString L_Continuer;
//    AnsiString L_Impo;
	AnsiString L_QVendu;
	AnsiString L_VVendu;
//    AnsiString L_Total;
	AnsiString L_StockQ;
	AnsiString L_StockV;
	AnsiString L_MemeAn;
	AnsiString L_PasVenteAvt;
	AnsiString L_Eff;
	AnsiString L_EffTt;
	AnsiString L_Ok;

public:// Déclarations utilisateur
	int Origine;
	CL_Agriculteur *Agri;//utilise par CL_Comm friend ??
	void __fastcall RetourDeTVChoixProduit(void);
	void __fastcall VideLesGrilles(void);
	CL_Item *Item;
	void TexteChaine(void);
	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_LabAnnee;
	AnsiString LC_Commercialisation1;
	AnsiString LC_BtBnCopieTout;
	AnsiString LC_BtBnCopier_A;
	AnsiString LC_LabProduit;
	AnsiString LC_LabelModifie_A;
	AnsiString LC_BtBnProduit;
	AnsiString LC_LabQuant;
	AnsiString LC_BtBnQuitter;
	AnsiString LC_ChBRepTout;
	AnsiString LC_BtBnReste;
	AnsiString LC_S1;
	AnsiString LC_BtBnSupBesTrav;
	AnsiString LC_LabVal;
	AnsiString LC_BtBnVenteQ;
	AnsiString LC_EnCours;
	AnsiString LC_Tout;

	__fastcall TCommercialisationFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCommercialisationFrm *CommercialisationFrm;
//---------------------------------------------------------------------------
#endif
