//---------------------------------------------------------------------------
#ifndef AgriSaisieH
#define AgriSaisieH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Forme00.h"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------

class TAgriSaisieFrm: public TForme00Frm {
	friend class TGereEnsembleFrm;
	friend class TTroupeauFrm;
	friend class TResultatFrm;
	friend class TTresoResFrm;

	__published: // Composants gérés par l'EDI
TMainMenu	*MainMenu1;
	TMenuItem *PRODUCTIONS;
	TMenuItem *Assolement;
	TMenuItem *Perennes;
	TMenuItem *Animaux;
	TMenuItem *InventaireAnimaux;
	TMenuItem *VARIABLES;
	TMenuItem *PRODUITS;
	TMenuItem *IMMOBILISATION;
	TMenuItem *Inventaire;
	TMenuItem *PetitMatriel;
	TMenuItem *FINANCES;
	TMenuItem *LongTerme;
	TMenuItem *CourtTerme;
	TMenuItem *Occc;
	TMenuItem *Subvention;
	TMenuItem *Placement;
	TMenuItem *Sommaire;
	TMenuItem *PRIVE;
	TMenuItem *Recettes;
	TMenuItem *Depenses;
	TMenuItem *RESULTATS;
	TMenuItem *CHARGES1;
	TMenuItem *ChargesOpe1;
	TMenuItem *Structure1;
	TMenuItem *EXTERNALITES1;
	TMenuItem *Negatives;
	TMenuItem *Positives;
	TMenuItem *InvSommaire;
	TMenuItem *CreancesDettes1;
	TMenuItem *Creances1;
	TMenuItem *Dettes1;
	TMenuItem *Definition;
	TMenuItem *DIVERS1;
	TMenuItem *Produits1;
	TMenuItem *ChargesDivers;
	TBitBtn *BtBnSup;
	TButton *BtDonnees;
	TButton *BtMotCle;
	TButton *BtDico;

	TBitBtn *BtReportDroit;
	TBitBtn *BtReportBas;
	TBitBtn *BtRecopBas;

	TLabel *LabSais;
	TMemo *Memo;
	TRadioGroup *RGModifiable;
	TBitBtn *BtBnVoir;
	TBitBtn *BtBnVideTout;

	TMenuItem *Vivriers;
	TMenuItem *Tva1;
	TMenuItem *S1;
	TMenuItem *StockInitial;
	TMenuItem *Commercialisation1;
	TLabel *LabEnCours;
	TMenuItem *PolitiqueStockage1;
	TBitBtn *BtRepToutDroit;
	TMenuItem *Tresorerie;
	TMenuItem *Passe;
	TBitBtn *BtBnNotes;
	TBitBtn *BtBnVersExcel;
	TBitBtn *BtBnDExcel;
	TMenuItem *Comparaison;

	void __fastcall FormResize (TObject *Sender);
	void __fastcall BoutFermerClick(TObject *Sender);
	void __fastcall MemoKeyDown (TObject *Sender, WORD &Key,TShiftState Shift);

	void __fastcall BtDonneesClick (TObject *Sender);
	void __fastcall BtMotCleClick (TObject *Sender);

	void __fastcall BtReportDroitClick (TObject *Sender);
	void __fastcall BtRepToutDroitClick(TObject *Sender);

	void __fastcall BtReportBasClick (TObject *Sender);
	void __fastcall BtRecopBasClick (TObject *Sender);
	void __fastcall RecopBasPerenne(void);

	void __fastcall BtBnSupClick (TObject *Sender);

	void __fastcall BoutAnnulClick (TObject *Sender);

	void __fastcall AssolementClick (TObject *Sender);
	void __fastcall AnimauxClick (TObject *Sender);
	void __fastcall PerennesClick (TObject *Sender);
	void __fastcall VivriersClick (TObject *Sender);
	void __fastcall InventaireAnimauxClick(TObject *Sender);

	void __fastcall VariablesClick (TObject *Sender);
	void __fastcall PRODUITSClick (TObject *Sender);
	void __fastcall StructureClick (TObject *Sender);
	void __fastcall ChargesOpeClick (TObject *Sender);
	void __fastcall RecettesPriveClick (TObject *Sender);
	void __fastcall DepensesPriveClick (TObject *Sender);
	void __fastcall LongTermeClick (TObject *Sender);
	void __fastcall NegativesClick (TObject *Sender);
	void __fastcall PositivesClick (TObject *Sender);
	void __fastcall RESULTATSClick (TObject *Sender);

	void __fastcall RGModifiableClick (TObject *Sender);
	void __fastcall BtDicoClick (TObject *Sender);
	void __fastcall FormCloseQuery (TObject *Sender, bool &CanClose);
	void __fastcall MemoDblClick (TObject *Sender);
	void __fastcall FormCreate (TObject *Sender);
	void __fastcall CourtTermeClick (TObject *Sender);
	void __fastcall SubventionClick (TObject *Sender);
	void __fastcall PlacementClick (TObject *Sender);
	void __fastcall OcccClick (TObject *Sender);
	void __fastcall FinSomClick (TObject *Sender);
	void __fastcall InventaireClick (TObject *Sender);
	void __fastcall PetitClick (TObject *Sender);
	void __fastcall InvSomClick (TObject *Sender);
	void __fastcall CreancesClick(TObject *Sender);
	void __fastcall DetteClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtBnStockerClick(TObject *Sender);
	void __fastcall BtBnVoirClick(TObject *Sender);
	void __fastcall DefinitionClick(TObject *Sender);
	void __fastcall ProduitsDiversClick(TObject *Sender);
	void __fastcall ChargesDiversClick(TObject *Sender);
	void __fastcall Tva1Click(TObject *Sender);
	void __fastcall StockIniClick(TObject *Sender);
	void __fastcall CommercialisationClick(TObject *Sender);
	void __fastcall PolitiqueStockageClick(TObject *Sender);
	void __fastcall BtBnImpClick(TObject *Sender);
	void __fastcall TresorerieClick(TObject *Sender);
	void __fastcall PasseClick(TObject *Sender);
	void __fastcall BtBnVideToutClick(TObject *Sender);
	void __fastcall BtBnNotesClick(TObject *Sender);
	void __fastcall Grille0Click(TObject *Sender);
	void __fastcall BtBnVersExcelClick(TObject *Sender);
	void __fastcall BtBnDExcelClick(TObject *Sender);
	bool __fastcall FormHelp(WORD Command, int Data, bool &CallHelp);
	void __fastcall ComparaisonClick(TObject *Sender);

private: // Déclarations de l'utilisateur
//    cf AgriSaisieEnum.h

	void __fastcall TAgriSaisieFrm::correction(void);////////

	int LEcran,HEcran;
	int HauteurMemo;
	bool EstInitialise;
	CL_Categorie *Categorie;
	//AgriSaisie
	void __fastcall TailleGrille (void);
	bool __fastcall CEstBon (void);
	void __fastcall AffAn (int col0);
	void __fastcall AffAnPlus1 (void);
	void __fastcall AffAnInvAni (void);

	void __fastcall PossibleModifier (bool modifiable);
	void __fastcall AffFormule (CL_Vecteur<CL_Formule>*vecteur,
			CL_Vecteur<CL_Categorie>*vCat );
	void __fastcall CompleteFormule (void);
	void __fastcall iniElt(CL_Elt *elt,int noFamille);
	void __fastcall completeElt(CL_Elt *eltG,CL_Elt *eltD,CL_Item *item);

	void __fastcall CompleteFormule2 (CL_Vecteur<CL_Formule>*vFormule);

	void __fastcall CalcFormule (CL_Vecteur<CL_Formule>*vecteur,int an);
//    void __fastcall CalcStock        (CL_Vecteur<CL_Formule>*vecteur);

	//AgriSaisieVersG
	void __fastcall IniGrille(TStringGrid *grille);
	void __fastcall IniGrilleAssol (bool possible);
	void __fastcall IniGrilleVerger (void);
	void __fastcall IniGrilleVivrier(void);
	void __fastcall IniGrilleInvAni(void);
	void __fastcall IniGrilleVariable(void);

	void __fastcall IniGrilleEmpLT (void);
	void __fastcall IniGrilleEmpCT (void);
	void __fastcall IniGrilleSub (void);
	void __fastcall IniGrillePlact (void);
	void __fastcall IniGrilleOccc (void);
	void __fastcall IniGrilleFinSom (void);
	void __fastcall IniGrilleImmo (void);
	void __fastcall IniGrillePetit (void);
	void __fastcall IniGrilleInvSom (void);
	void __fastcall IniGrilleCreanceDette(void);
	void __fastcall IniGrilleStockIni(void);
	void __fastcall IniGrillePolStock(void);
	void __fastcall IniGrillePasse(void);

	//AgriSaisie1
	void __fastcall VersGrilleAssol (CL_Vecteur<CL_Valeur> *vecteur);
	void __fastcall VersGrilleVerger (CL_Vecteur<CL_Verger>*vecteur);
	void __fastcall VersGrilleVivrier (CL_Vecteur<CL_Verger>*vecteur);
//    void __fastcall VersGrilleInvAni  (CL_Vecteur<CL_InvAni> *vecteur);

	void __fastcall VersGrilleVariable(CL_Vecteur<CL_Valeur> *vecteur);
	void __fastcall VersGrilleFormule(CL_Vecteur<CL_Formule> *vecteur,
			CL_Vecteur<CL_Categorie> *vCat );

	void __fastcall VersGrilleFormule (CL_Vecteur<CL_Formule> *vecteur);
	void __fastcall VersGrilleEmpLT (void);
	void __fastcall VersGrilleEmpCT (void);
	void __fastcall VersGrilleSub (void);
	void __fastcall VersGrillePlact (void);
	void __fastcall VersGrilleOccc (void);
	void __fastcall VersGrilleFinSom (void);
	void __fastcall VersGrilleImmo (void);
	void __fastcall VersGrillePetit (void);
	void __fastcall VersGrilleInvSom (void);
	void __fastcall VersGrilleStockIni (CL_Vecteur<CL_StockIni> *vecteur);
	void __fastcall VersGrilleCreanceDette(CL_Vecteur<CL_EnCours> *vecteur);
	void __fastcall VersGrillePolStock(void);
	void __fastcall VersGrillePasse(void);

	//AgriSaisie2
	bool __fastcall ControleCellFloat (int col0,int col,int row,int digits);
	bool __fastcall ControleCellVerger (int col,int row);
	bool __fastcall ControleCellVivrier (int col,int row);
	bool __fastcall ControleCellInvAni (int col,int row);
	bool __fastcall ControleCellFormule (int col,int row);
	bool __fastcall CreeProg (CL_Formule *formule,int n);
	bool __fastcall ControleCellEmpLT (int col,int row);
	bool __fastcall ControleCellEmpCT (int col,int row);
	bool __fastcall ControleCellSub (int col,int row);
	bool __fastcall ControleCellPlact (int col,int row);
	bool __fastcall ControleCellOccc (int col,int row);
	bool __fastcall ControleCellImmo (int col,int row);
	bool __fastcall ControleCellPetit (int col,int row);
	bool __fastcall ControleCellCreanceDette (int col,int row);
	bool __fastcall ControleCellStockIni (int col,int row);

	bool __fastcall VerifGrille (void);
	bool __fastcall VerifGrilleNom (void);
	bool __fastcall VerifGrilleVerger (void);
	bool __fastcall VerifGrilleVivrier (void);
	bool __fastcall VerifGrilleFormule (void);
	bool __fastcall VerifGrilleEmpLT (void);
	bool __fastcall VerifEmpLT (int row);
	bool __fastcall VerifDateEmpLT (int row);
	bool __fastcall VerifGrilleEmpCT (void);
	bool __fastcall VerifEmpCT (int row);
	bool __fastcall VerifGrilleSub (void);
	bool __fastcall VerifSub (int row);
	bool __fastcall VerifGrillePlact (void);
	bool __fastcall VerifPlact (int row);
	bool __fastcall VerifGrilleOccc (void);
	bool __fastcall VerifGrilleFinSom (void);
	bool __fastcall VerifGrilleImmo (void);
	bool __fastcall VerifImmo(int row);
	bool __fastcall VerifGrillePetit (void);
	bool __fastcall VerifGrilleInvSom (void);
	bool __fastcall VerifGrilleCreanceDette(void);
	bool __fastcall VerifGrilleStockIni (void);
	bool __fastcall VerifGrillePolStock (void);

	void __fastcall DeGrilleValeur (CL_Vecteur<CL_Valeur> *vecteur);
	void __fastcall DeGrilleVerger (CL_Vecteur<CL_Verger> *vecteur);
	void __fastcall DeGrilleVivrier (CL_Vecteur<CL_Verger> *vecteur);
	void __fastcall DeGrilleInvAni (CL_Vecteur<CL_InvAni> *vecteur);
	void __fastcall DeGrilleFormule (CL_Vecteur<CL_Formule> *vecteur);
	void __fastcall DeGrilleEmpLT (void);
	void __fastcall DeGEmpLT (int row);
	void __fastcall DeGrilleEmpCT (void);
	void __fastcall DeGEmpCT (int row);
	void __fastcall DeGrilleSub (void);
	void __fastcall DeGSub (int row);
	void __fastcall DeGrillePlact (void);
	void __fastcall DeGPlact (int row);

	void __fastcall DeGrilleOccc (void);
	void __fastcall DeGrilleFinSom (void);
	void __fastcall DeGrilleImmo (void);
	void __fastcall DeGImmo (int row);
	void __fastcall DeGrillePetit (void);
	void __fastcall DeGrilleInvSom (void);
	void __fastcall DeGrilleCrDette (CL_Vecteur <CL_EnCours> *vecteur);
	void __fastcall DeGrilleStockIni (CL_Vecteur <CL_StockIni> *vecteur);
	void __fastcall DeGrillePolStock (void);
	void __fastcall DeGrillePasse(void);

	//AgriSaisie2
	void __fastcall StockerOrdre(void);
	void __fastcall StOrdreValeur(CL_Vecteur<CL_Valeur> *vecteur);
	void __fastcall StOrdreVerger(CL_Vecteur<CL_Verger> *vecteur);
	void __fastcall StOrdreFormule(CL_Vecteur<CL_Formule> *vecteur);
	void __fastcall StOrdreEmpLT(void);
	void __fastcall StOrdreEmpCT(void);
	void __fastcall StOrdreSub(void);
	void __fastcall StOrdrePlact(void);
	void __fastcall StOrdreStockIni (CL_Vecteur<CL_StockIni> *vecteur);
	void __fastcall StOrdreCrDette (CL_Vecteur<CL_EnCours> *vecteur);

	void __fastcall StOrdreImmo(void);

	void __fastcall MazNFlagCat(void);
	void __fastcall MazOFlagCat(CL_Agriculteur* agriTotal);
	void __fastcall MazOFlagCat1(CL_Vecteur<CL_QuanVal> *vecteur);
	//AgriSaisieAgrege agrege à replacer
	int TypeAgreg;
	bool __fastcall MetDans(CL_Agriculteur *agri,CL_Agriculteur *agriTotal,float *ponderation);
	bool __fastcall AgregeValeur(float *ponderation,
			CL_Vecteur<CL_Valeur> *vecteur,
			CL_Vecteur<CL_Valeur> *vecteurTot);
	CL_Valeur* __fastcall trouveValeur( CL_Vecteur<CL_Valeur> *vecteurTot,
			CL_Atelier *atelier);
	bool __fastcall AgregeVerger(float *ponderation,
			CL_Vecteur<CL_Verger> *vecteur,
			CL_Vecteur<CL_Verger> *vecteurTot);
	bool __fastcall AgregeInvAni(float *ponderation,
			CL_Vecteur<CL_InvAni> *vecteur,
			CL_Vecteur<CL_InvAni> *vecteurTot);
	bool __fastcall AgregeInvAni(float *ponderation,
			TList *lstTroupeaux,
			TList *lstTroupeauxTot);
	CL_Troupeau* __fastcall TrouveTroupeauTot(CL_Troupeau*troupeau, TList *lstTroupeauxTot);
	CL_MvtAni* __fastcall TrouveMvtAni(TList *lst,CL_MvtAni *mvtAni0);

	bool __fastcall AgregeVariable(float *ponderation,
			CL_Agriculteur *agri,
			CL_Agriculteur *agriTot);
	void _fastcall MoyenneVariable(int *effectifTot,CL_Agriculteur *agriTot);

	bool __fastcall AgregeFormule(float *ponderation,
			CL_Vecteur<CL_Formule> *vecteur,
			CL_Vecteur<CL_Formule> *vecteurTot,
			bool avecFormule);

	CL_Formule* __fastcall TrouveFormule(CL_Formule *formule,
			CL_Vecteur<CL_Formule> *vecteurTot);

	void __fastcall AgregeCompleteFormule(CL_Vecteur<CL_Formule> *vecteur);

	bool __fastcall AgregeEmprunt(float *ponderation,CL_Agriculteur *agri,
			CL_Agriculteur *agriTot);

	bool __fastcall AgregeImmo(float *ponderation,CL_Agriculteur *agri,
			CL_Agriculteur *agriTot);

	bool __fastcall AgregeSubvention(float *ponderation,
			CL_Vecteur<CL_Sub> *vecteur,
			CL_Vecteur<CL_Sub> *vecteurTot);

	CL_Sub* __fastcall TrouveSub( CL_Vecteur<CL_Sub> *vecteurTot,
			CL_Sub *sub);

	bool __fastcall AgregeTresoIni(float *ponderation,CL_Agriculteur *agri,
			CL_Agriculteur *agriTot);

	CL_Verger* __fastcall TrouveVerger(CL_Verger *verger,
			CL_Vecteur<CL_Verger> *vecteurTot);

	void __fastcall EnsembleTotalise(CL_AgriRes* resAgri,
			CL_AgriRes* resTotal,int *effectif);
	bool __fastcall ilYaEffectif(CL_AgriEff *agriEff);
//Ensemble
	void __fastcall EnsTotQuanVal(CL_Vecteur<CL_QuanVal> *vecteurA,
			CL_Vecteur<CL_QuanVal> *vecteurT,int *effectif);
	void __fastcall EnsTotQuanVal2(CL_Vecteur<CL_QuanVal> *vecteurA,
			CL_Vecteur<CL_QuanVal> *vecteurT,int *effectif);
	void __fastcall EnsTotEmp(CL_TotEmp* totEmpA,CL_TotEmp* totEmpT,int *effectif);
	void __fastcall EnsTotImmo(CL_TotImmo *totImmoA,CL_TotImmo *totImmoT,int *effectif);
	void __fastcall EnsTotSub(CL_TotSub* totSubA,CL_TotSub* totSubT,int *effectif);

	void __fastcall EnsTotEnCours(CL_TotEnCours *totECA,CL_TotEnCours *totECT,int *effectif);

	void __fastcall EnsTotSoldeCumul(CL_AgriRes* resAgri,CL_AgriRes* resTotal,int *effectif);

	void __fastcall EnsTotFloat(float *valA,float *valT,int *effectif,int n=N_X);
	void __fastcall EnsTotTva(CL_TvaEnt *Tva,CL_TvaEnt *TvaTot, int *effectif);
	void __fastcall EnsembleSurface(CL_Agriculteur *agri,CL_Agriculteur *agriTotal,int *effectif);

	void __fastcall EnsTotCeg(CL_AgriRes* resAgri,
			CL_AgriRes* resTotal,int *effectif);

	void __fastcall EnsTotBilan(CL_AgriRes* resAgri,
			CL_AgriRes* resTotal,int *effectif);

	void __fastcall CalculQuantite(CL_Agriculteur *agri);
	void __fastcall EtablitPcent(CL_AgriDefSim *defSim,int tOUs,CL_Tendance *tend);
	void __fastcall trouveTend(CL_Agriculteur *agri);
	void __fastcall sansEnchainement(CL_Tendance *tend);
	void __fastcall avecEnchainement(CL_AgriDefSim *defSim,CL_Tendance *tendance);

	void __fastcall trouveDelta(CL_Item *item,CL_Tendance *tendance,float *pcent);
	void __fastcall trouveDeltaAtelier(CL_Atelier *atelier,CL_Item *item,
			CL_Tendance *tendance,float *pcent);
	void CompleteEtatSortie(void);

	void __fastcall CalculAtelier (CL_Atelier *atelier,
			CL_Vecteur<CL_ItemParAtelier> *vecteurIPA,
			CL_Vecteur<CL_QuanVal> *vecteurRes,
			float *surface, int nbPhase,
			CL_Tendance *tendance );
	void __fastcall CalculAtelierVol (CL_Atelier *atelier,
			CL_Vecteur<CL_ItemParAtelier> *vecteurIPA,
			CL_Vecteur<CL_QuanVal> *vecteurRes,
			float *surface, int nbPhase,
			CL_Tendance *tendProd,CL_Tendance *tendCharge);
	void __fastcall CalculAtelierPied (CL_Atelier *atelier,
			CL_Vecteur<CL_ItemParAtelier> *vProdPied,
			float *piedHa,
			CL_Vecteur<CL_QuanVal> *vecteurRes,
			float *surface,int nbPhase,CL_Tendance *tendance);

	void __fastcall CalculVerger(CL_Vecteur<CL_ItemParAtelier> *vecteurIPA,
			CL_Vecteur<CL_QuanVal> *vecteurRes,
			CL_Verger *verger,
			CL_Tendance *tendance);

	void __fastcall CalculVergerPied (CL_Vecteur<CL_ItemParAtelier> *vProdPied,
			float *piedHa,
			CL_Vecteur<CL_QuanVal> *vecteurRes,
			CL_Verger *verger,
			CL_Tendance *tendance);

	void __fastcall CalculVergerVol (CL_Vecteur<CL_ItemParAtelier> *vecteurIPA,
			CL_Vecteur<CL_QuanVal> *vecteurRes,
			CL_Verger *verger,
			CL_Tendance *tendProd,CL_Tendance *tendCharge);
	void __fastcall CalculTroupeaux(CL_Agriculteur *agri,CL_AgriRes *resultat);
	void __fastcall CalculDuTroupeau(CL_Agriculteur *agri,CL_Troupeau *troupeau,CL_AgriRes *resultat);
	void __fastcall AccrochePasse(TList *lstPasse,CL_Arbre *arbre);

	// avances stocks
	void __fastcall CalculAvance(CL_Agriculteur *agri);
	void __fastcall trouveAvance(float *avance,CL_Atelier *atelier,int mOuv );

	void __fastcall CalculStock(CL_Agriculteur *agri);

	void __fastcall CalculProdImmo(CL_Agriculteur *agri);

	void __fastcall CalculAnimaux(CL_Agriculteur *agri);

	void __fastcall CalculValeur(CL_Agriculteur *agri,int an);
	void __fastcall CalculValeurAnimaux(CL_Agriculteur *agri);

	void __fastcall CalculTva(CL_TvaEntIni *tvaIni,CL_TvaEnt *tva);

	void __fastcall CalculTreso(CL_Agriculteur *agri,int an);

	void __fastcall TotalValeur(CL_Vecteur<CL_Formule>*vFormule,
			CL_Vecteur<CL_QuanVal>*vProduits,
			float *total,
			CL_Vecteur<CL_QuanVal>*vCatTot,
			float *totTva,
			int an);

	void __fastcall TotalValeurProduction(CL_Agriculteur *agri, int an);
	/*
	 void __fastcall TotalValeurProduction(CL_Vecteur<CL_Formule>*vFormule,
	 CL_Vecteur<CL_QuanVal>*vProduits,
	 float *total,
	 CL_Vecteur<CL_QuanVal>*vCatTot,
	 float *totTva);
	 //int an);
	 */
	CL_QuanVal* __fastcall TAgriSaisieFrm::TrouveQuanVal(CL_Vecteur<CL_QuanVal>*vProduit,
			CL_Item *item);

	void __fastcall TotVProdComm(CL_Vecteur<CL_QuanVal>*vProduit);
	void __fastcall TotVProdPolStock(CL_Vecteur<CL_QuanVal>*vProduit);
	void __fastcall TotVFormule(CL_Vecteur<CL_Formule>*vFormule,
			CL_Vecteur<CL_QuanVal>*vProduit);

	void __fastcall CalculIndicateur(int n);

	void __fastcall SaisirCellA(int col,int row);
	void __fastcall SaisirCellVivrier(int col,int row);
	void __fastcall SaisirCellInvAni(int col,int row);
	void __fastcall SaisirCellFormule(int col,int row);
	// ?? saisirCellModifiable pour LT CT Sub
	void __fastcall SaisirCellModifiable(int col,int row);
	void __fastcall SaisirCellOccc(int col,int row);
	void __fastcall SaisirCellFinSom(int col,int row);
	void __fastcall SaisirCellImmo(int col,int row);
	void __fastcall SaisirCellPetit(int col,int row);
	void __fastcall SaisirCellInvSom(int col,int row);
	void __fastcall SaisirCellCreanceDette(int col,int row);
	void __fastcall SaisirCellStockIni(int col,int row);
	void __fastcall SaisirCellPolStock (int col,int row);

	//AgriSaisieTotal
	void __fastcall TotalLT (void);
	void __fastcall TotalCT (void);
	void __fastcall TotalOCCC (void);
	void __fastcall TotalFinSom (void);
	void __fastcall TotaliserEmp (void);
	void __fastcall TotaliserEmpPrive (void);

	void __fastcall TotalSub (void);
	void __fastcall TotalPlact (void);
	void __fastcall TotalImmo (void);
	void __fastcall TotalImmoPetit(void);
	void __fastcall TotalImmoSom (void);
	void __fastcall TotaliserImmo (void);
	void __fastcall TotalEnCours (CL_Agriculteur *agri);
	int __fastcall CalculExercice(int aReal,int mReal,int an_0,int mois_0);

	void __fastcall VoirSiVide(CL_TotEmp *totEmp);
// agriConversion
	void __fastcall ConvertirQuanVal (float *taux,CL_Vecteur<CL_QuanVal> *vecteur);
	void __fastcall ConvertirQuanVal2 (float *taux,CL_Vecteur<CL_QuanVal> *vecteur);
	void __fastcall ConvertirValeur (float *taux,float *total,int n_x=N_X);
	void __fastcall ConvertirTotEmp (float *taux,CL_TotEmp *totEmp);
	void __fastcall ConvertirTotImmo (float *taux,CL_TotImmo *totImmo);
	void __fastcall ConvertirTotEnCours(float *taux,CL_TotEnCours *totEnCours);
	void __fastcall ConvertirTva (float *taux, CL_TvaEnt *tva);

	void __fastcall ChangeUniteMonnaie2(CL_SystemeUnite *deMonnaie,CL_SystemeUnite *enMonnaie,
			CL_Vecteur<CL_Item> *vecteur);
//agriSaisieVoir
	void __fastcall VoirStockIni(void);
//prepareEcran
	void __fastcall PrepareEcran (void);
	void __fastcall GrilleVisible(void);
	void __fastcall MemoVisible(void);
	void __fastcall BoutonVisible(void);
	void __fastcall BoutonIntitule(void);
	void __fastcall ReportPossible(void);
	void __fastcall AjoutRowPossible(void);
	void __fastcall CelluleModifiable(void);
	void __fastcall Titre(void);
//traduction

//	AnsiString L_Culture;
	AnsiString L_Perenne;
	AnsiString L_Animaux;
	AnsiString L_Pluri;
	AnsiString L_Variable;
//	AnsiString L_Produit;
//	AnsiString L_Charge; 
	AnsiString L_ChOpe;
	AnsiString L_ChStruct;
	AnsiString L_RecDiv;
	AnsiString L_DepDiv;
	AnsiString L_ExtNeg;
	AnsiString L_ExtPos;
	AnsiString L_RecPriv;
	AnsiString L_DepPriv;
	AnsiString L_EmpLT;
	AnsiString L_EmpCT;
	AnsiString L_Sub;
	AnsiString L_Occc;
	AnsiString L_Plact;
	AnsiString L_EmpSom;
	AnsiString L_Immo;
	AnsiString L_Tva;
	AnsiString L_Petit;
	AnsiString L_ImmoRap;
	AnsiString L_PolStock;
	AnsiString L_PasProd;
	AnsiString L_StockIni;
	AnsiString L_Stocks;
	AnsiString L_Creance;
	AnsiString L_Dettes;
	AnsiString L_Passe;
	AnsiString L_PasDon;
	AnsiString L_DonPasse;
	AnsiString L_ResDe;
	AnsiString L_Att;
	AnsiString L_DonNonModif;
//    AnsiString L_Err;
	AnsiString L_LiNonSup;
//    AnsiString L_Impo;
//	AnsiString L_LiSupQ;
//    AnsiString L_Sup;
	AnsiString L_QuitAgri;

//    AnsiString L_Total;
	AnsiString L_Moy;
	AnsiString L_Surface;

	AnsiString L_ErrDateAn;
	AnsiString L_ErrEmpDur;
	AnsiString L_ErrSub;
	AnsiString L_ErrAm;

	AnsiString L_TitrePer;
	AnsiString L_TitreViv;
	AnsiString L_TitreEmp;
	AnsiString L_TitreSub;
	AnsiString L_TitrePlact;
	AnsiString L_TitreOccc;
	AnsiString L_TitreImmo;
	AnsiString L_TitrePetit;
	AnsiString L_TitreCrDette;
	AnsiString L_TitrePolStock;
	AnsiString L_TitrePasse;
	AnsiString L_Nom;

	AnsiString L_LesAteliers;

	//PrepareEcran
	AnsiString L_Dico;
	AnsiString L_MotCle;
	AnsiString L_Assol;
	AnsiString L_Mvt;
	//report
	AnsiString L_ErrPasImmo;
	AnsiString L_ErrRepImpo;
	AnsiString L_ErrIntCal;
	//report
	AnsiString L_Modifie;
	//Verif
	AnsiString L_ErrPasNom;
	AnsiString L_ErrPasSurf;
	AnsiString L_ErrPasDatePlant;
	AnsiString L_ErrArrach;
	AnsiString L_ErrDurTropL;
	AnsiString L_ErrPasMontant;
	AnsiString L_ErrPasDuree;
	AnsiString L_ErrPasDur2;
	AnsiString L_ErrPasTaux;
	AnsiString L_ErrPasTaux2;
	AnsiString L_ErrDurSup50;
	AnsiString L_ErrPasTypEmp;
	AnsiString L_ErrPasDateReal;
	AnsiString L_ErrPasDateRembEmp;
	AnsiString L_ErrPasEPEmp;
	AnsiString L_ErrIntEmpCT;
	AnsiString L_ErrPbDate;
	AnsiString L_ErrTypePlact;
	AnsiString L_ErrPasDateTerme;
	AnsiString L_LT;
//    AnsiString L_CT;
	AnsiString L_ErrPasValNeuf;
	AnsiString L_ErrPasDateAchat;
	AnsiString L_ErrPasTypAmor;
	AnsiString L_ErrPasDurAmor;
	AnsiString L_ErrPasVal;
	AnsiString L_ErrPasDate;
	//VersG
	AnsiString L_PrixRevient;
	//AnsiString L_PasDonAInt;
	//AnsiString L_Cat;
	//videTout
	AnsiString L_JeffToutQ;
//    AnsiString L_JeffToutT;
	//voir
	AnsiString L_Vente;
	AnsiString L_EvolStock;

protected:
	virtual bool __fastcall ControleCell(int col,int row);
	virtual void __fastcall CellDebut(void);
	virtual void __fastcall SaisirCell(int col,int row);
	virtual bool __fastcall Stocker(void);
	virtual void __fastcall DesGrilles(void);
	virtual void __fastcall VersGrille(TStringGrid *grille);

public:// Déclarations de l'utilisateur

	int Origine;
	CL_Agriculteur *Agri;
	void __fastcall Calcul0(CL_Agriculteur *agri);
	void __fastcall FaireCompta(CL_AgriRes *resultat,int an);
	void __fastcall TrouveDonneesAnterieures(CL_Agriculteur *agri);
	void __fastcall TrouveDonneesAnterieures(TList *lstPasse,CL_Vecteur<CL_Formule> *vecteur);

	void __fastcall CalculEnsemble(CL_Ensemble *ensemble);
	CL_Agriculteur* __fastcall Agrege(CL_Ensemble *ensemble);

	//AgriSaisie3
	void __fastcall RepDroitAssol (int digits,int colQ=3);

	void __fastcall RepDroitFormule (void);
	void __fastcall RepDroitEmpLT (void);
	void __fastcall RepDroitFinSom (void);
	void __fastcall RepDroitInvSom (void);
	void __fastcall RepDroitCreance (void);
	void __fastcall RepDroitStockIni (void);

	void __fastcall RepDroitToutAssol(int digits);
	void __fastcall RepDroitToutFormule(void);

	void __fastcall RepBasAssol(void);
	void __fastcall RepBasPerenne(void);
	void __fastcall RepBasLT(void);
	void __fastcall RepBasCT(void);
	void __fastcall RepBasStockIni(void);
	void __fastcall RepBasImmo(void);
	void __fastcall RepBasPetit(void);
	void __fastcall RepBasOccc(void);
	void __fastcall RepBasPolStock(void);

	void __fastcall RepBasTvaImmo (int col,int row);
	void __fastcall RepBasTvaPetit (int col,int row);
	void __fastcall RepBasCol(int colQ);

	void __fastcall CalculSurfaceVerger(CL_Verger *verger);
	void __fastcall CalculSurfaceVivrier(CL_Verger *vivrier);

	//Conversion
	void __fastcall Convertir(CL_AgriRes *resultat, float *taux);
	void __fastcall ChangeUniteMonnaie(CL_SystemeUnite *deMonnaie,CL_SystemeUnite *enMonnaie);
	//MargeAtelier
//    void __fastcall MargeAtelier(CL_Atelier *atelier);
	void __fastcall MargeAtelier(void);
	void __fastcall MargeCultAni(
			CL_Atelier *atelier,
			CL_Vecteur<CL_Valeur> *vAtelier,
			CL_Vecteur<CL_QuanVal>*vProduit,
			CL_Vecteur<CL_QuanVal>*vCharge,
			CL_Vecteur<CL_QuanVal>*vExter );
	void __fastcall MargePerViv(
			CL_Atelier *atelier,
			CL_Vecteur<CL_Verger> *vAtelier,
			CL_Vecteur<CL_QuanVal>*vProduit,
			CL_Vecteur<CL_QuanVal>*vCharge,
			CL_Vecteur<CL_QuanVal>*vExter );

	void __fastcall MargeBestiaux(AnsiString nom,
			CL_Vecteur<CL_QuanVal> *vProduit,
			CL_Vecteur<CL_QuanVal> *vCharge);

	void __fastcall MargeBestiaux2(CL_Vecteur<CL_QuanVal>*vProCha,
			float *valeur,CL_Item *item);

	void __fastcall CalculProChaDuTroupeau(CL_Troupeau *troupeau,
			CL_Vecteur<CL_QuanVal> *vProduit,
			CL_Vecteur<CL_QuanVal> *vCharge);

	void __fastcall PurgeLstQuantPrix(void);
	void TexteChaine(void);

	void IniCaption(void);
	void TexteCaption(void);
	//...

	AnsiString L_DetteLT;
	AnsiString L_RembCapLT;
	AnsiString L_IntLT;
	AnsiString L_NouvLT;

	AnsiString L_DetteCT;
	AnsiString L_RembCapCT;
	AnsiString L_IntCT;
	AnsiString L_NouvCT;
	AnsiString L_V_Resid;
	AnsiString L_Amor;
	AnsiString L_Achat;
	AnsiString L_Revente;
	AnsiString L_PlusVal;
	AnsiString L_MoinsVal;
	AnsiString L_ProdImmo;

	AnsiString L_EMP;
	AnsiString L_Montant;
	AnsiString L_Dur1;
	AnsiString L_Taux1;
	AnsiString L_Dur2;
	AnsiString L_Taux2;
	AnsiString L_Type;
	AnsiString L_Real;
	AnsiString L_Remb;
	AnsiString L_EouP;

	//...
	AnsiString LC_PRODUITS;
	AnsiString LC_AgriSaisieFrm;
	AnsiString LC_Animaux;
	AnsiString LC_Assolement;
	AnsiString LC_LabPCharge;
	AnsiString LC_Commercialisation1;
	AnsiString LC_CourtTerme;
	AnsiString LC_Creances1;
	AnsiString LC_Definition;
	AnsiString LC_ChargesDivers;
	AnsiString LC_Dettes1;
	AnsiString LC_BtDico;
	AnsiString LC_DIVERS1;
	AnsiString LC_BtDonnees;
	AnsiString LC_CreancesDettes1;
	AnsiString LC_EXTERNALITES1;
	AnsiString LC_FINANCES;
	AnsiString LC_InvSommaire;
	AnsiString LC_IMMOBILISATION;
	AnsiString LC_Inventaire;
	AnsiString LC_LabSais;
	AnsiString LC_LongTerme;
	AnsiString LC_RGModifiable;
	AnsiString LC_BtMotCle;
	AnsiString LC_Negatives;
	AnsiString LC_Occc;
	AnsiString LC_ChargesOpe1;
	AnsiString LC_Passe;
	AnsiString LC_Perennes;
	AnsiString LC_PetitMatriel;
	AnsiString LC_Placement;
	AnsiString LC_Vivriers;
	AnsiString LC_PolitiqueStockage1;
	AnsiString LC_Positives;
	AnsiString LC_PRIVE;
	AnsiString LC_PRODUCTIONS;
	AnsiString LC_Produits1;
	AnsiString LC_RESULTATS;
	AnsiString LC_S1;
	AnsiString LC_StockInitial;
	AnsiString LC_Structure1;
	AnsiString LC_Subvention;
	AnsiString LC_Tva1;
	AnsiString LC_Tresorerie;
	AnsiString LC_InventaireAnimaux;
	AnsiString LC_VARIABLES;
	AnsiString LC_BtBnVoir;
	AnsiString LC_QuitterAgri;

	__fastcall TAgriSaisieFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAgriSaisieFrm *AgriSaisieFrm;
//---------------------------------------------------------------------------
#endif

