//---------------------------------------------------------------------------

#ifndef QRAtelierH
#define QRAtelierH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <QuickRpt.hpp>
#include <Qrctrls.hpp>
#include <QRCtrls.hpp>
/*
 #define QRITEM    1
 #define QRTITRE   2
 #define QRTITRE1  3
 #define QRBLANC   4
 #define QRTRAIT   5
 #define QRITEMVOL 6
 */
#define QRDON     1
#define QRBIL     2
#define QRTITRE   3
#define QRTITRE1  4
#define QRBLANC   5
#define QRANI     6
#define QRTRAIT   7
#define QRITEM    8
#define QRITEMVOL 9
//---------------------------------------------------------------------------
class TQRAtelierFrm: public TForm {
	__published: // Composants gérés par l'EDI
TQuickRep	*QR;
	TQRBand *ColumnHeaderBand1;
	TQRBand *TitleBand1;
	TQRSysData *QRSysData;
	TQRLabel *NomAgri;
	TQRLabel *TitreEtat;
	TQRLabel *Nom;
	TQRLabel *Categorie;
	TQRLabel *Unite;
	TQRLabel *Appro;
	TQRLabel *UniteAppro;
	TQRLabel *C0;
	TQRLabel *C1;
	TQRLabel *C2;
	TQRBand *QRBand2;
	TQRLabel *NomPro;
	TQRLabel *NomCat;
	TQRLabel *NomUnite;
	TQRLabel *NomAppro;
	TQRLabel *NomUniteAppro;
	TQRLabel *V0;
	TQRLabel *V1;
	TQRLabel *V2;
	TQRLabel *V3;
	TQRLabel *V4;
	TQRLabel *V5;
	TQRLabel *V6;
	TQRLabel *V7;
	TQRLabel *V8;
	TQRLabel *V9;
	TQRLabel *V10;
	TQRLabel *V11;
	TQRLabel *V12;
	TQRLabel *V13;
	TQRLabel *C3;
	TQRLabel *C4;
	TQRLabel *C5;
	TQRLabel *C6;
	TQRLabel *C7;
	TQRLabel *C8;
	TQRLabel *C9;
	TQRLabel *C10;
	TQRLabel *C11;
	TQRLabel *C12;
	TQRLabel *C13;
	void __fastcall QRNeedData(TObject *Sender, bool &MoreData);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall QRBeforePrint(TCustomQuickRep *Sender,
			bool &PrintReport);
private: // Déclarations utilisateur
	//...
	class CL_QrDon
	{
	public:
		//donnees courantes
		CL_QrDon(int type,CL_ItemParAtelier *itemPA,TColor couleur=clBlack);
		CL_QrDon(int type, char *nom,TColor couleur=clBlack);
		CL_QrDon(int type, TColor =clBlack);

		/*
		 CL_QrDon(int type,char *nom, char *unite,float *val,TColor =clBlack,bool avecTrait=false);
		 CL_QrDon(int type,char *nom, char *unite,int   *val,TColor =clBlack,bool avecTrait=false);
		 CL_QrDon(char *nom,TColor =clBlack);
		 */
		int Type;
		CL_ItemParAtelier *ItemPA;
		char *Nom;
		bool EstTitre;
		bool AvecTrait;
		bool EstBlanc;
		TColor Couleur;
		int PosNom;
	};
	//....
	// fin class
	void __fastcall MaBlanc(void);
	void __fastcall MaBlancCol(void);

	bool __fastcall CompleteDonnees(void);
	void __fastcall entreDonnees(int type,CL_ItemParAtelier *itemPA);
	void __fastcall entreBlanc(void);
	void __fastcall entreTitre(char *nom,TColor couleur=clBlack);

	void __fastcall entreTrait(void);
	void __fastcall Initialise(void);
	void __fastcall DelDonnees(void);
	TObjectList *LstCaption;
	TObjectList *LstCol;
	TList *LstDonnees;
	int NLigne;
	int NbPhase;
	int DebutVal;
	int Digits;

	void __fastcall EnTeteCulture(void);
	void __fastcall EnTetePerenne(CL_Atelier *atelier);
	void __fastcall EnTeteVivrier(void);

	void __fastcall Item (CL_Vecteur<CL_ItemParAtelier> *vecteur);
	void __fastcall ItemVol (CL_Vecteur<CL_ItemParAtelier> *vecteur);

	void __fastcall AffItem(CL_QrDon *donnees);
	void __fastcall AffItemVol(CL_QrDon *donnees);
	void __fastcall AffTitre(CL_QrDon *donnees);

	void __fastcall AffTrait(void);
	void __fastcall AffBlanc(void);

public:// Déclarations utilisateur
	void __fastcall Prepare(CL_Atelier *atelier);

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_Appro;
	AnsiString LC_AtelierFrm;
	AnsiString LC_C0;
	AnsiString LC_C1;
	AnsiString LC_C10;
	AnsiString LC_C11;
	AnsiString LC_C12;
	AnsiString LC_C13;
	AnsiString LC_C2;
	AnsiString LC_C3;
	AnsiString LC_C4;
	AnsiString LC_C5;
	AnsiString LC_C6;
	AnsiString LC_C7;
	AnsiString LC_C8;
	AnsiString LC_C9;
	AnsiString LC_RGCat;
	AnsiString LC_Nom;
	AnsiString LC_NomAgri_A;
	AnsiString LC_NomAppro;
	AnsiString LC_NomCat;
	AnsiString LC_NomPro;
	AnsiString LC_NomUnite;
	AnsiString LC_NomUniteAppro;
	AnsiString LC_TitreEtat;
	AnsiString LC_Unite;
	AnsiString LC_V0;
	AnsiString LC_V1;
	AnsiString LC_V10;
	AnsiString LC_V11;
	AnsiString LC_V12;
	AnsiString LC_V13;
	AnsiString LC_V2;
	AnsiString LC_V3;
	AnsiString LC_V4;
	AnsiString LC_V5;
	AnsiString LC_V6;
	AnsiString LC_V7;
	AnsiString LC_V8;
	AnsiString LC_V9;

	__fastcall TQRAtelierFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQRAtelierFrm *QRAtelierFrm;
//---------------------------------------------------------------------------
#endif
