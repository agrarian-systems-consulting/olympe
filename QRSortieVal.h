//---------------------------------------------------------------------------

#ifndef QRSortieValH
#define QRSortieValH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <QuickRpt.hpp>
#include <QRCtrls.hpp>

//#include "QRSortieEnum.h"
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
class TQRSortieValFrm: public TForm {
	friend class TQRTresoValFrm;

	__published: // Composants gérés par l'EDI
TQuickRep	*QR;
	TQRBand *TitleBand1;
	TQRBand *ColumnHeaderBand1;
	TQRBand *DetailBand1;
	TQRLabel *NomAgri;
	TQRSysData *QRSysData1;

	TQRLabel *LabAn0;
	TQRLabel *LabAn1;
	TQRLabel *LabAn2;
	TQRLabel *LabAn3;
	TQRLabel *LabAn4;
	TQRLabel *LabAn5;
	TQRLabel *LabAn6;
	TQRLabel *LabAn7;
	TQRLabel *LabAn8;
	TQRLabel *LabAn9;
	TQRLabel *LabAn10;
	TQRLabel *IntituleP;

	TQRLabel *Val0;
	TQRLabel *Val1;
	TQRLabel *Val2;
	TQRLabel *Val3;
	TQRLabel *Val4;
	TQRLabel *Val5;
	TQRLabel *Val6;
	TQRLabel *Val7;
	TQRLabel *Val8;
	TQRLabel *Val9;
	TQRLabel *Val10;

	TQRLabel *TitreEtat;
	TQRLabel *ValeurEn;
	TQRLabel *UniteMonnaie;
	TQRBand *PageFooterBand1;
	TQRSysData *QRSysData2;

	void __fastcall QRNeedData(TObject *Sender, bool &MoreData);
	void __fastcall QRBeforePrint(TCustomQuickRep *Sender,
			bool &PrintReport);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);

public: // Déclarations utilisateur  commun à QRSortieQuant
//    TObjectList *LstCaption;
	// Utilitaire
	class CL_QrDon
	{
	public:
		//donnees courantes
		CL_QrDon(int type,char *nom, float *val,TColor =clBlack,bool avecTrait=false);
		CL_QrDon(int type,char *nom, char *unite,float *val,TColor =clBlack,bool avecTrait=false);
		CL_QrDon(int type,char *nom, char *unite,float *val,int digits, TColor =clBlack,bool avecTrait=false);//170808
		CL_QrDon(int type,char *nom, char *unite,int *val,TColor =clBlack,bool avecTrait=false);
//		CL_QrDon(int type,char *nom, AnsiString unite, float *val,TColor couleur,bool avecTrait=false);
//        CL_QrDon(int type,char *nomFamille,char *nom, char *unite,float *val,TColor =clBlack,bool avecTrait=false);
		CL_QrDon(char *nom,TColor =clBlack);
		CL_QrDon(int type, TColor =clBlack);
		void MiseEnPage(int type,bool avecTrait);
		int Type;
		bool EstTitre;
		bool AvecTrait;
		bool EstBlanc;
		TColor Couleur;
		char *Nom;
		char *Unite;
		float Val[N_X+1];//*Val 270805
		int ValInt[N_X+1];//*ValInt
		int PosNom;
		int Digits;//160808
	};
	// fin class
//    void __fastcall MiseEnPage(int type);
	void __fastcall entreDonnees(int type,char *nom,float *val,TColor couleur=clBlack);
	void __fastcall entreDonnees(int type,char *nom,char *unite,float *val,TColor couleur=clBlack);
	void __fastcall entreDonnees(int type,char *nom,char *unite,float *val,int digits, TColor couleur);//160808
	void __fastcall entreDonnees(int type,char *nom,char *unite,int *val,TColor couleur=clBlack);
	void __fastcall entreDonnees(int type,CL_Elt *elt,TColor clNavy);
	void __fastcall entreBlanc(void);
	void __fastcall entreTitre(char *nom);
	void __fastcall entreTrait(void);

	void __fastcall Prepare(int TypeSortie,CL_Agriculteur *agri);//Resultat

	TObjectList *LstCaption;
	TList *LstDonnees;
	int NLigne;
	void __fastcall DelDonnees(void);
	bool EstVide(float *vecteur,int n_x=N_X);
	bool EstVide(int *vecteur,int n_x=N_X);
	CL_Agriculteur *Agri;
	void __fastcall Initialise(void);
	void __fastcall AffBlanc(void);
	void __fastcall AffTrait(void);

private:// Déclarations utilisateur
	bool __fastcall CompleteDonnees();
	void __fastcall AffDonnees(CL_QrDon *donnees);
	void __fastcall AffBilan(CL_QrDon *donnees);

	void __fastcall IniDonneesSynthese(CL_Agriculteur *agri);
	void __fastcall IniDonneesCeg(CL_Agriculteur *agri);
	void __fastcall IniDonneesBilan(CL_Agriculteur *agri);
	void __fastcall IniDonneesPrive(CL_Agriculteur *agri);
	void __fastcall IniDonneesTreso(CL_Agriculteur *agri);
	void __fastcall IniDonneesTresoGrandsPostes(CL_Agriculteur *agri);
	void __fastcall IniDTresoCategorie(
			char *titre,
			char *intTitTotal,
			CL_Vecteur<CL_Categorie> *vCategorie,
			CL_Vecteur<CL_QuanVal> *vProduit,
			float *total,
			CL_Vecteur<CL_QuanVal> *vCatTot);
	void __fastcall IniDTresoCategorieGP(
			char *titre,
			char *intTitTotal,
			CL_Vecteur<CL_Categorie> *vCategorie,
			CL_Vecteur<CL_QuanVal> *vProduit,
			float *total,
			CL_Vecteur<CL_QuanVal> *vCatTot);
	void __fastcall IniDTresoAnimaux(CL_Agriculteur *agri);
	void __fastcall IniDTresoAnimauxGP(CL_Agriculteur *agri);
	void __fastcall IniDTresoImmo(CL_AgriRes *resultat);
	void __fastcall IniDTresoEmprunt(CL_AgriRes *resultat);
	void __fastcall IniDTresoPlact(CL_AgriRes *resultat);

	void __fastcall IniDonneesAnimaux(CL_Agriculteur *agri);

	void __fastcall IniDonneesTva(CL_Agriculteur *agri);
	void __fastcall IniDonneesFinance(CL_Agriculteur *agri);
	void __fastcall IniDFinance(CL_TotEmp *totEmp,float *versement,char *nomEmprunt);
	void __fastcall IniDonneesImmo(CL_Agriculteur *agri);
	void __fastcall IniDImmo(CL_AgriRes *resultat,CL_TotImmo *immo,char *titre);
	void __fastcall IniDImmoPetit(CL_AgriRes *resultat,CL_TotImmo *immo,char *titre);
	void __fastcall IniDImmoSom(CL_AgriRes *resultat,CL_TotImmo *immo,char *titre);
	void __fastcall IniDonneesPerenne(CL_Agriculteur *agri);
	void __fastcall IniDonneesRecapEmpLT(CL_Agriculteur *agri);

	void __fastcall IniDonneesRecapImmo(CL_Agriculteur *agri);

public:
	AnsiString L_1;
	AnsiString L_2;
	AnsiString L_3;
	AnsiString L_4;
	AnsiString L_5;
	AnsiString L_6;
	AnsiString L_7;
	AnsiString L_8;
	AnsiString L_9;
	AnsiString L_10;
	AnsiString L_11;
	AnsiString L_12;
	AnsiString L_13;
	AnsiString L_14;
	AnsiString L_15;
	AnsiString L_16;
	AnsiString L_17;
	AnsiString L_18;
	AnsiString L_19;
	AnsiString L_20;
	AnsiString L_21;
	AnsiString L_22;
	AnsiString L_23;
	AnsiString L_24;
	AnsiString L_25;
	AnsiString L_26;
	AnsiString L_27;
	AnsiString L_28;
	AnsiString L_29;
	AnsiString L_30;
	AnsiString L_31;
	AnsiString L_32;
	AnsiString L_33;
	AnsiString L_34;
	AnsiString L_35;
	AnsiString L_36;
	AnsiString L_37;
	AnsiString L_38;
	AnsiString L_39;
	AnsiString L_40;
	AnsiString L_41;
	AnsiString L_42;
	AnsiString L_43;
	AnsiString L_44;
	AnsiString L_45;
	AnsiString L_46;
	AnsiString L_47;
	AnsiString L_48;
	AnsiString L_49;
	AnsiString L_50;
	AnsiString L_51;
	AnsiString L_52;
	AnsiString L_53;
	AnsiString L_54;
	AnsiString L_55;
	AnsiString L_56;
	AnsiString L_57;
	AnsiString L_58;
	AnsiString L_59;
	AnsiString L_60;
	AnsiString L_61;
	AnsiString L_62;
	AnsiString L_63;
	AnsiString L_64;
	AnsiString L_65;
	AnsiString L_66;
	AnsiString L_67;
	AnsiString L_68;
	AnsiString L_69;
	AnsiString L_70;
	AnsiString L_71;
	AnsiString L_72;
	AnsiString L_73;
	AnsiString L_74;
	AnsiString L_75;
	AnsiString L_76;
	AnsiString L_77;
	AnsiString L_78;
	AnsiString L_79;
	AnsiString L_80;
	AnsiString L_81;
	AnsiString L_82;
	AnsiString L_83;
	AnsiString L_84;
	AnsiString L_85;
	AnsiString L_86;
	AnsiString L_87;
	AnsiString L_88;
	AnsiString L_89;
	AnsiString L_90;
	AnsiString L_91;
	AnsiString L_92;
	AnsiString L_93;
	AnsiString L_94;
	AnsiString L_95;
	AnsiString L_96;
	AnsiString L_97;
	AnsiString L_98;
	AnsiString L_99;
	AnsiString L_100;
	AnsiString L_101;
	AnsiString L_102;
	AnsiString L_103;
	AnsiString L_104;
	AnsiString L_105;
	AnsiString L_106;
	AnsiString L_107;
	AnsiString L_108;
	AnsiString L_109;
	AnsiString L_110;
	AnsiString L_111;
	AnsiString L_112;
	AnsiString L_113;
	AnsiString L_114;
	AnsiString L_115;
	AnsiString L_116;
	AnsiString L_117;
	AnsiString L_118;
	AnsiString L_119;
	AnsiString L_120;
	AnsiString L_121;
	AnsiString L_122;
	AnsiString L_123;
	AnsiString L_124;
	AnsiString L_125;
	AnsiString L_126;
	AnsiString L_127;
	AnsiString L_128;

	void TexteChaine(void);

//    void __fastcall Francais(void);
//    void __fastcall Anglais(void);

	void TexteCaption(void);
	void IniCaption(void);

	AnsiString LC_IntituleP;
	AnsiString LC_LabAn0;
	AnsiString LC_LabAn1;
	AnsiString LC_LabAn10;
	AnsiString LC_LabAn2;
	AnsiString LC_LabAn3;
	AnsiString LC_LabAn4;
	AnsiString LC_LabAn5;
	AnsiString LC_LabAn6;
	AnsiString LC_LabAn7;
	AnsiString LC_LabAn8;
	AnsiString LC_LabAn9;
	AnsiString LC_NomAgri;
	AnsiString LC_QRSortieValFrm;
	AnsiString LC_TitreEtat;
	AnsiString LC_UniteMonnaie;
	AnsiString LC_Val0;
	AnsiString LC_Val1;
	AnsiString LC_Val10;
	AnsiString LC_Val2;
	AnsiString LC_Val3;
	AnsiString LC_Val4;
	AnsiString LC_Val5;
	AnsiString LC_Val6;
	AnsiString LC_Val7;
	AnsiString LC_Val8;
	AnsiString LC_Val9;
	AnsiString LC_ValeurEn;
	//220206
	AnsiString L_AnnuInt;
	AnsiString L_NouvEmpLT;
	AnsiString L_CapDuLT;

	__fastcall TQRSortieValFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TQRSortieValFrm *QRSortieValFrm;
//---------------------------------------------------------------------------
#endif
