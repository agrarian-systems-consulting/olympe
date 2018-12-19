//---------------------------------------------------------------------------
#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <sysutils.hpp>
#include <AppEvnts.hpp>
//1#include "Configuration.h"
#include <Graphics.hpp>

#include "HtmlHelp.h"
//#include "c:\XMLProg\LibXmlComps.hpp"
//#include "c:\XMLProg\LibXmlParser.hpp"
//#include "Excel_97_SRVR.h"
//#include <OleServer.hpp>
//---------------------------------------------------------------------------
class TMainForm: public TForm {
	friend class TAProposFrm;
	__published: // Composants gérés par l'EDI
TMainMenu	*MainMenu1;
	TMenuItem *Fichier1;
	TMenuItem *Nouveau;
	TMenuItem *Ouvrir;
	TMenuItem *Enregistrer;
	TMenuItem *Enregistrersous;
	TMenuItem *APropos;
	TMenuItem *Prfrences1;
	TMenuItem *Aide1;
	TMenuItem *ImporterDonneesCSV;
	TMenuItem *LireDonGlob;

	TPrintDialog *PrintDialog;
	TOpenDialog *OpenDialog;
	TSaveDialog *SauverSous;

	TBitBtn *BoutFermer;
	TBitBtn *BtBnEffacer;
	TBitBtn *BtBnNotes;

	TButton *BtUnite;
	TButton *BtTVA;
	TButton *BtZoneType;
	TButton *BtIndicateur;
	TButton *BtEtatSortie;
	TButton *BtAutreAgri;
	TButton *BtAgriEnCours;
	TButton *BtAutreEnsemble;
	TButton *BtEnsEnCours;
	TButton *Test;
	TButton *BtPhase;
	TPanel *PanUniTva;
	TPanel *PanIndic;

	TGroupBox *GBAgri;
	TGroupBox *GBEnsemble;
	TGroupBox *GBAtelier;
	TGroupBox *GBProduction;
	TGroupBox *GBAlea;
	TListBox *LBAlea;
	TListBox *LBProduction;
	TButton *BtComparaison;
	TImage *ImInra;
	TBitBtn *BtBnXml;
	TOpenDialog *OpenDialogXml;
	TGroupBox *GBLangue;
	TComboBox *CBLangue;
	TImage *ImFleche1;
	TImage *ImFleche2;
	TGroupBox *GBDefinition;
	TGroupBox *GBItemAtelier;
	TListBox *LBItemAtelier;
	TGroupBox *GBItemAgri;
	TListBox *LBItemEntreprise;
	TGroupBox *GBItemFamille;
	TListBox *LBItemFamille;
	TGroupBox *GBDivers;
	TListBox *LBItemDivers;
	TImage *ImFleche3;
	TImage *ImFleche4;
	TImage *ImFleche5;
	TMenuItem *LireAccess;
	TMenuItem *EcrireAccess;

	void __fastcall ImprimanteClick(TObject *Sender);
	void __fastcall QuitterClick(TObject *Sender);
	void __fastcall OuvrirClick(TObject *Sender);
	void __fastcall EnregistrersousClick(TObject *Sender);
	void __fastcall EnregistrerClick(TObject *Sender);
	void __fastcall StockerNomFichier(void);
	void __fastcall EspecesClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall AProposClick(TObject *Sender);
	void __fastcall NouveauClick(TObject *Sender);

	void __fastcall FormActivate(TObject *Sender);
	void __fastcall ImprimerToutClick(TObject *Sender);

	void __fastcall EnTestClick(TObject *Sender);
	void __fastcall BtAutreAgriClick(TObject *Sender);
	void __fastcall BtIndicateurClick(TObject *Sender);
	void __fastcall BtEtatSortieClick(TObject *Sender);
	void __fastcall BtUniteClick(TObject *Sender);
	void __fastcall BtZoneTypeClick(TObject *Sender);
	void __fastcall BtTVAClick(TObject *Sender);
	void __fastcall BtAgriEnCoursClick(TObject *Sender);
	void __fastcall LBProductionClick(TObject *Sender);
	void __fastcall LBDefinitionClick(TObject *Sender);
	void __fastcall BtAutreEnsembleClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall LBAleaClick(TObject *Sender);
	void __fastcall StockageClick(TObject *Sender);
	void __fastcall BtBnNettoyerClick(TObject *Sender);
	void __fastcall BtBnNotesClick(TObject *Sender);
	void __fastcall TestClick(TObject *Sender);
	void __fastcall Prfrences1Click(TObject *Sender);
	void __fastcall BtEnsEnCoursClick(TObject *Sender);
	void __fastcall LBItemDiversClick(TObject *Sender);
	void __fastcall LBItemAtelierClick(TObject *Sender);
	void __fastcall LBItemEntrepriseClick(TObject *Sender);
	void __fastcall LBItemFamilleClick(TObject *Sender);
	void __fastcall LBItemAtelierExit(TObject *Sender);
	void __fastcall LBItemEntrepriseExit(TObject *Sender);
	void __fastcall LBItemFamilleExit(TObject *Sender);
	void __fastcall LBItemDiversExit(TObject *Sender);
	void __fastcall LBProductionExit(TObject *Sender);
	void __fastcall LBAleaExit(TObject *Sender);
	void __fastcall BtComparaisonClick(TObject *Sender);
	void __fastcall BtBnXmlClick(TObject *Sender);
	void __fastcall CBLangueChange(TObject *Sender);
	void __fastcall Aide1Click(TObject *Sender);
	void __fastcall ImporterDonneesCSVClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
	void __fastcall LireAccessClick(TObject *Sender);
	void __fastcall EcrireAccessClick(TObject *Sender);
	void __fastcall ImpDeltaClick(TObject *Sender);
	void __fastcall BoutFermerClick(TObject *Sender);
//	void __fastcall RGExcelClick(TObject *Sender);

private:// Déclarations de l'utilisateur
	void __fastcall AppException(TObject *Sender, Exception *E);
//	void __fastcall AppException(TObject *Sender, SysUtils::Exception *E);
	bool __fastcall VerifFichier(void);
	/** On se précipite pour sauver dans une variable globale
	 le répertoire courant, qui doit être celui d'olympe.exe */
//1    string GetOlympeDir ();
//    Configuration * conf;
	AnsiString AsHistorique;
	void EmpecherGrosBug(void);
//    void TexteEtCaption(void);
	void AdapterEcran(void);
	void LigneCommande(void);
	TForm *GereDefFrm;

	bool __fastcall HelpHook( Word command, int Data,bool &CallHelp);

//    void __fastcall ChoisirLangue(void);

	AnsiString L_PasMemoire;
	AnsiString L_DateLim;
	AnsiString L_FinTest;
	AnsiString L_AOuvrir;
	AnsiString L_Ecran;
	AnsiString L_Affichage;
	AnsiString L_Inco;
//    AnsiString L_QuitterQ;
//    AnsiString L_QuitterT;
	AnsiString L_Ouvrir;
	AnsiString L_Nouveau;
	AnsiString L_EcraserQ;
	AnsiString L_EcraseFic;
	AnsiString L_SauverSous;
	AnsiString L_PasFicOuv;
//    AnsiString L_Impo;
	AnsiString L_Fichier;
	AnsiString L_PasAgri;
	AnsiString L_PasEnsemble;
	AnsiString L_NouvDef;
	AnsiString L_StocPermis;
	AnsiString L_Fich;
	AnsiString L_Note;

//	void __fastcall CaptionDesFiches(void);

	AnsiString LC_Enregistrer;
	AnsiString LC_Fichier1;
	AnsiString LC_APropos;
	AnsiString LC_Nouveau;
	AnsiString LC_Ouvrir;
	AnsiString LC_GBAgri;
	AnsiString LC_GBAlea;
	AnsiString LC_GBAtelier;
	AnsiString LC_BtAutreAgri;
	AnsiString LC_LabZone;
	AnsiString LC_GereComparaisonFrm;
	AnsiString LC_Prfrences1;
	AnsiString LC_GBDefinition;
	AnsiString LC_DIVERS1;
	AnsiString LC_Label11;
	AnsiString LC_LabFleche5;
	AnsiString LC_CreancesDettes1;
	AnsiString LC_Enregistrersous;
	AnsiString LC_BtEnsEnCours;
	AnsiString LC_GBEnsemble;
	AnsiString LC_DefEtatSortieFrm;
	AnsiString LC_BtBnAscii;
	AnsiString LC_BtBnXml;
	AnsiString LC_LabIndicateur;
	AnsiString LC_BtBnEffacer;
	AnsiString LC_BtBnNotes;
	AnsiString LC_PanClassif;
	AnsiString LC_EspeceFrm;
	AnsiString LC_GBItemAtelier;
	AnsiString LC_GBItemAgri;
	AnsiString LC_GBItemFamille;
	AnsiString LC_LabProcedure;
	AnsiString LC_PRODUCTIONS;
	AnsiString LC_BtBnQuitter;
	AnsiString LC_Test;
	AnsiString LC_BtBnTva;
	AnsiString LC_BtBnUnite;
	AnsiString LC_BtAgriEnCours;
	AnsiString LC_Atelier;

	AnsiString LC_Produits;
	AnsiString LC_Charges;
	AnsiString LC_Exter;
	AnsiString LC_Troupeaux;
	AnsiString LC_PerTrav;

	AnsiString LC_ChStruct;
	AnsiString LC_DepDiv;
	AnsiString LC_RecDiv;

	AnsiString LC_RecFam;
	AnsiString LC_DepFam;

	AnsiString LC_Var;

	AnsiString LC_Cultures;
	AnsiString LC_Animaux;
	AnsiString LC_Perennes;
	AnsiString LC_Pluri;

	AnsiString LC_Prix;
	AnsiString LC_Quant;
	AnsiString LC_Divers;
	AnsiString LC_LireDonGlob;
	AnsiString LC_ImportDon;
	AnsiString LC_LireAccess;
	AnsiString LC_EcrireAccess;
	AnsiString LC_DefRaccourci;

public:// Déclarations de l'utilisateur
	char Langue;
	AnsiString AsCodeLangue;//FESNPT  210610
	TStringList *SLstLangue;//Français  English
	AnsiString Notes;//020507
	unsigned short AnLimite,MoisLimite;
	AnsiString AsDirOlympe;
	AnsiString AsExcelExt;
	void __fastcall NouvelleDefinition(int nature);
	void TexteChaine(void);
	void TexteCaption(void);
	void TexteEtCaption(void);
	void IniCaption(void);
	__fastcall TMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
