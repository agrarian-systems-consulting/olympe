//---------------------------------------------------------------------------

#ifndef QRCatNomH
#define QRCatNomH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <QuickRpt.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class TQRCatNomFrm: public TForm {
	__published: // Composants gérés par l'EDI
TQuickRep	*QR;
	TQRBand *ColumnHeaderBand1;
	TQRLabel *Nom;
	TQRBand *PageFooterBand1;
	TQRSysData *QRSysData1;
	TQRBand *TitleBand1;
	TQRSysData *QRSysData2;
	TQRLabel *NomAgri;
	TQRLabel *TitreEtat;
	TQRBand *DetailBand1;
	TQRLabel *Sup;
	TQRLabel *NomPro;
	void __fastcall QRNeedData(TObject *Sender, bool &MoreData);
	void __fastcall QRBeforePrint(TCustomQuickRep *Sender,
			bool &PrintReport);
private: // Déclarations utilisateur
	class CL_QrDon
	{
	public:
		CL_QrDon(char *nom);
		CL_QrDon(CL_Item *item);
		CL_QrDon(int symbole);
		CL_QrDon(CL_Atelier *atelier);

		int Type;
		char *Nom;
		CL_Item *Item;
		CL_Atelier *Atelier;
	};
//    TList *LstDonnees;
//    int    NLigne;
	void __fastcall entreDonnees(char *nom);
	void __fastcall entreDonnees(CL_Item *item);
	void __fastcall entreDonnees(CL_Atelier *atelier);

	void __fastcall blanc(void);
	bool __fastcall CompleteDonnees(void);
	void __fastcall DelDonnees(void);
	void __fastcall AffBlanc(void);
	void __fastcall AffTitre(char *nom);
	void __fastcall AffItem(CL_Item *item);
	void __fastcall AffAtelier(CL_Atelier *atelier);

public:// Déclarations utilisateur
	TList *LstDonnees;
	int NLigne;
	void __fastcall Prepare(CL_Agriculteur *agri,char *titre,
			CL_Vecteur<CL_Categorie> *vCategorie,CL_Vecteur<CL_Item> *vItem);
	void __fastcall PrepareAtelier(CL_Agriculteur *agri,char *titre,
			CL_Vecteur<CL_Categorie> *vCategorie,CL_Vecteur<CL_Atelier> *vItem);
	void __fastcall PreparePerenne(CL_Agriculteur *agri,char *titre,
			CL_Vecteur<CL_Espece> *vEspece,CL_Vecteur<CL_Atelier> *vAtelier);

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_Nom;
	AnsiString LC_NomAgri_A;
	AnsiString LC_NomPro;
	AnsiString LC_QRCatNomFrm;
	AnsiString LC_Sup;
	AnsiString LC_TitreEtat;

	__fastcall TQRCatNomFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQRCatNomFrm *QRCatNomFrm;
//---------------------------------------------------------------------------
#endif
