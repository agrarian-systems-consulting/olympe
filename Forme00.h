//---------------------------------------------------------------------------
#ifndef Forme00H
#define Forme00H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Forme0.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <OleCtrls.hpp>
#include <ActnList.hpp>

#define COLMAX    40
#define GRILLEMAX 40

#define EXISTE   0
#define NOUVEAU  1
#define STOCKE   2
#define SUPPRIME 3

//---------------------------------------------------------------------------
class TForme00Frm: public TForme0Frm {
	__published: // Composants g�r�s par l'EDI
TStringGrid	*Grille0;
	TButton *BtClasser;
	TBitBtn *BtBnStocker;
	TPanel *PClasst;
	TBitBtn *BtClHaut;
	TBitBtn *BtClBas;
	TBitBtn *BtBnFermClasst;
	TBitBtn *BtBnImp;
	TCheckBox *ChBRepTout;
	TBitBtn *BtBnExcel;
	TActionList *ActionList1;
	TPanel *PanHaut;
	TLabel *LabelModifie;
	void __fastcall FormCreate (TObject *Sender);
	void __fastcall BoutFermerClick(TObject *Sender);

	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall Grille0Click(TObject *Sender);
//	void __fastcall BoutEditClick(TObject *Sender);

	void __fastcall Grille0KeyPress(TObject *Sender, char &Key);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall BtClasserClick(TObject *Sender);
	void __fastcall BtClBasClick(TObject *Sender);
	void __fastcall BtClHautClick(TObject *Sender);
	void __fastcall BtBnFermClasstClick(TObject *Sender);
	void __fastcall BtBnStockerClick(TObject *Sender);
	void __fastcall BtBnExcelClick(TObject *Sender);
	void __fastcall BtBnImpClick(TObject *Sender);
//    void __fastcall Grille0MouseDown(TObject *Sender, TMouseButton Button,
//          TShiftState Shift, int X, int Y);
//    void __fastcall Grille0MouseUp(TObject *Sender, TMouseButton Button,
//          TShiftState Shift, int X, int Y);
//    void __fastcall Grille0MouseMove(TObject *Sender, TShiftState Shift,
//          int X, int Y);//140407
//    void __fastcall XLClick(TObject *Sender);

//    void __fastcall BtHaut(void);
//    void __fastcall BtBas(void);
protected:// D�clarations de l'utilisateur
	void __fastcall DemarrerClasst(void);
//    void __fastcall PosClasst(void);
	bool __fastcall DemarreExcel(void);
	void __fastcall RepereCellEC(int col,int row);

public:
	/**le boulot a �t� fait*/
	bool EstInitialise;
	/**qt� de grilles*/
	int GrilleX;
	AnsiString TitreGrille;
	/**valeurs possibles :
	 T : texte
	 N : num�rique
	 0 : rien � saisir
	 */
	char TypeCol[COLMAX];
	TStringGrid* LesGrilles[GRILLEMAX ];
	TStringGrid* LaGrille;
	/**grille x a �t� modifi�e*/
	bool GrilleModif[GRILLEMAX ];
	/**on a interverti des lignes
	 disponible pour 1 seule grille - � g�n�raliser ? */
	bool OrdreModif;
	/**myst�re ?*/
	bool AutreDonnee; //pour eviter apres ErreurFrm->Show de utiliser VersGrille
	/**la derni�re colonne visit�e*/
	int ColM[COLMAX];
	/**la derni�re ligne visit�e*/
	int RowM[COLMAX];
	/**tampon pour une cellule, avant saisie*/
	AnsiString ValueAvant;
// modif 261103
	int ColEC,RowEC;
	int CDebSel,CFinSel;
	int RDebSel,RFinSel;

	bool CellModif;
	/**inutilis�*/
	TStringList *CCRow; //pour copier dans popup
	/**inutilis�*/
	AnsiString CCCell; //
	TGridRect PlageCellules;
	bool __fastcall CellVide(int col,int row);
	/**si FALSE, court-circuite le controle de saisie
	 et les contraintes diverses*/
	bool CellAVerifier;
	/**pour ajouter des lignes
	 certaines grilles ne sont pas extensibles
	 ex : saisie rapide des emprunts */
	bool AjoutRow;

	/**les conversions -> chaine pour l'affichage */
	AnsiString Aff(float x,int digits=0);
	AnsiString Aff(int x);
	AnsiString Aff(char c);
	AnsiString Aff(int x1,int x2);
	AnsiString Aff0(float x,int digits=0); //avec zero affich� et non blanc
	AnsiString AffJourMois(int jour,int mois);

	void __fastcall MarquerLigne(int row);
	void __fastcall MarquerCell(int col,int row);
	// car alpha y compris �� � ..
	int isalnumA(unsigned char c);
	/**ligne vide ?*/
	bool __fastcall RowVide(int row,int c0=1);
	/**ajouter une ligne vide - si (AjoutRow)*/
	void __fastcall AjouterRow(void);
	/**verrou sur cellule*/
	void __fastcall CellModifiable(bool modifiable);
	/**...*/
	void __fastcall SupprimerLigne(int rASupprimer=1);
	/**tout mettre � blanc*/
	void __fastcall VideLesGrilles(void);
	/**vide une grille*/
	void __fastcall VideGrille(TStringGrid *grille);
	/**grille a �t� modifi�e*/
	bool __fastcall IlYaGrilleModif(void);
	/**pour raffraichir la grille avec valeurs du vecteur
	 et perdre les modifications*/
	void __fastcall MazModif(void);
	/**apelle le contr�le de saisie si la cellule est modifi�e*/
	bool __fastcall DerniereCell(void);
	void __fastcall CellInitiale(int col,int row);
	void __fastcall CellInitiale(void);

	/** sym�triques de Aff*/
	float __fastcall GrilleFloat(int col,int row);
	int __fastcall GrilleInt(int col,int row);
	char __fastcall GrilleCar(int col,int row);
	AnsiString __fastcall GrilleChaine(int col,int row);
	bool __fastcall GrilleMoisAn(int col,int row,int &mois,int &an);
	bool __fastcall GrilleJourMois(int col,int row,int &jour,int &mois);

	/**indique les caract�res autoris�s dans une saisie*/
	bool __fastcall GrilleCarPermis(int col,int row,char &type,char *permis);

	//
	void __fastcall SwapObjet(TStringGrid *laGrille,int col,int row0,int row1);
	void __fastcall SwapAs(TStringGrid *laGrille,int col,int row0,int row1);
	/**sp�cial grilles emprunt � long terme*/
	bool __fastcall GrilleEmpLTType(int col,int row,char &remb,char &freq);

	/**formatage des donn�es dans la grille (espaces entre chiffres,
	 nombre de chiffres apr�s la virgule*/
	void __fastcall ReAffFloat(int col, int row,int digits);
	void __fastcall ReAffInt(int col, int row);
	void __fastcall ChangePrecision(TStringGrid *SG,int digits,int c0,int r0);

	/**teste la pr�sence de doublons sur une colonne dans la grille*/
	bool __fastcall Doublon(TStringGrid* grille,int col,int row);
	/**s�lection d'une ligne*/
	void __fastcall SelLigne(void);
	/**d�s�lection de la m�me*/
	void __fastcall DeSelLigne(void);
	bool __fastcall RepPossible(int c,int r);
	void __fastcall RepDroit(TStringGrid *grille,int digits=0);

	// A Personnaliser
	/**initialisation*/
	virtual void __fastcall DefinirLesGrilles(void);
	/**inititalisation*/
	virtual void __fastcall Personnaliser(void);
	/**construit la grille (colonnes : titre, largeur)*/
	virtual void __fastcall IniGrille (TStringGrid *grille);
	/**remplir la grille avec des valeurs*/
	virtual void __fastcall VersGrille (TStringGrid *grille);
	/**d�verse le contenu de la grille dans les objets d'un vecteur*/
	virtual void __fastcall DeGrille (TStringGrid *grille);
	/**red�fini dans les formulaires d�riv�s*/
	virtual void __fastcall SaisirCell (int col,int row);
	virtual bool __fastcall ControleCell(int col,int row);
	virtual bool __fastcall ControleGrille(void);
	/**nous place sur la premi�re cellule �ditable
	 renseigne ValueAvant*/
	virtual void __fastcall CellDebut(void);
	/**invoqu� par le bouton 'Fermer'
	 assure le controle de la derni�re saisie le cas �ch�ant
	 et enregistre le vecteur modifi� / ou d'origine
	 */
	virtual bool __fastcall Stocker(void);
//public:		// D�clarations de l'utilisateur

	__fastcall TForme00Frm(TComponent* Owner);

	void TexteChaine(void);
	void TexteCaption(void);
	void IniCaption(void);
//private:
protected:
	// copier coller annuler
	int LireClipBoard(void);
	int EcrireClipBoard(void);
	int Restaurer(void);
	int ColCB,RowCB;//CB comme ClipBoard
	bool MouseActive;
	TStringList *SLRestaurer;

private:
//        AnsiString L_DonModifQ;
//        AnsiString L_DonModifT;
	AnsiString L_ErrDate;
//       AnsiString L_Erreur;
	AnsiString L_ErrMois;
	AnsiString L_ErrAn;
	AnsiString L_ErrNbJour;
	AnsiString L_NomDonne;

	AnsiString LC_BtClasser;
	AnsiString LC_Forme00Frm;
	AnsiString LC_LabelModifie_A;
	AnsiString LC_ChBRepTout;
};
//---------------------------------------------------------------------------
extern PACKAGE TForme00Frm *Forme00Frm;
//---------------------------------------------------------------------------
#endif

