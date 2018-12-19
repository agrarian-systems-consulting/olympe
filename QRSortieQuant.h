//---------------------------------------------------------------------------

#ifndef QRSortieQuantH
#define QRSortieQuantH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "QRSortieVal.h"
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <QuickRpt.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class TQRSortieQuantFrm: public TQRSortieValFrm {
	__published: // Composants gérés par l'EDI
TQRLabel	*NomUnite;
	TQRLabel *Unite;
	void __fastcall QRNeedData(TObject *Sender, bool &MoreData);
	void __fastcall QRBeforePrint(TCustomQuickRep *Sender,
			bool &PrintReport);

public: // Déclarations utilisateur
	void __fastcall Prepare(int TypeSortie,CL_Agriculteur *agri);// Resultat
	void __fastcall Etat(CL_EtatSortie *etat,CL_Agriculteur *agri);
	void __fastcall Comparaison(CL_EtatSortie *serieCompetat,TList *lstElt,CL_Agriculteur *agri);
	__fastcall TQRSortieQuantFrm(TComponent* Owner);
private:// Déclarations utilisateur
	void __fastcall IniDonneesQuantite(CL_Agriculteur *agri);
	void __fastcall IniDQuantCategorie(
			char *nom,
			CL_Vecteur<CL_Categorie> *vCategorie,
			CL_Vecteur<CL_QuanVal> *vQuanVal);
	void __fastcall IniDQuantAnimaux(CL_Agriculteur *agri);
	void __fastcall IniDonneesExter(CL_Agriculteur *agri);
	bool __fastcall CompleteDonnees(void);
	void __fastcall AffDonnees(CL_QrDon *donnees);
	void __fastcall AffAni(CL_QrDon *donnees);
	void __fastcall AffBlanc(void);
	void __fastcall AffTrait(void);
public:
	//void __fastcall Francais(void);
	//void __fastcall Anglais(void);
	void TexteChaine(void);
	AnsiString L_Comp;//comparaison

	//QRResSortieQuant
	AnsiString L_1;
	AnsiString L_2;
	AnsiString L_3;
	AnsiString L_4;
	AnsiString L_5;
	AnsiString L_6;
	AnsiString L_7;
	AnsiString L_8;
	AnsiString L_9;

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_NomUnite;
	AnsiString LC_QRSortieQuantFrm;
	AnsiString LC_Unite;

};
//---------------------------------------------------------------------------
extern PACKAGE TQRSortieQuantFrm *QRSortieQuantFrm;
//---------------------------------------------------------------------------
#endif
