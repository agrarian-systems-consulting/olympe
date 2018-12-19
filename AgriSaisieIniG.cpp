//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"

#include "LesVecteurs.hse"
#include "GereAgri.h"
#include "Erreur.h"

#include "MvtAni.h"
#include "CL_Trad.h"

#include "AgriSaisieEnum.h"
#include "AgriSaisie.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//-----------------------------------------------------------------------------
extern CL_Trad *T;
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrille(TStringGrid *grille)
{
	VideGrille(LaGrille);
	switch(grille->Tag)
	{
		case GAssol: IniGrilleAssol(true);break;
		case GPerenne: IniGrilleVerger();break;
		case GVivrier: IniGrilleVivrier();break;
		case GAni : IniGrilleAssol(true);break;
		case GVariable: IniGrilleAssol(true);break;

		case GProduit:
		case GCharge:
		case GChStruct:
		case GExtNeg:
		case GExtPos:
		case GRecFam:
		case GDepFam:
		case GRecDiv:
		case GDepDiv: IniGrilleAssol(false);break;
//     	case GDepDiv:   IniGrilleAssol(true);break;
		case GEmpLT: IniGrilleEmpLT();break;
		case GEmpCT: IniGrilleEmpCT();break;
		case GSub: IniGrilleSub();break;
		case GPlact: IniGrillePlact();break;
		case GOccc: IniGrilleOccc();break;
		case GFinSom: IniGrilleFinSom();break;
		case GImmo: IniGrilleImmo();break;
		case GPetit: IniGrillePetit();break;
		case GInvSom: IniGrilleInvSom();break;

		case GCreance: IniGrilleCreanceDette();break;
		case GDette: IniGrilleCreanceDette();break;
		case GStock: IniGrilleStockIni();break;
		case GPolStock: IniGrillePolStock();break;
		case GPasse: IniGrillePasse();break;
		case GNotes: ShowMessage("stocker Memo NON définie");break;

		default:ShowMessage("Méthode IniGrille NON définie");
	}
}

//---------------------------------------------------------------------------
// Assol
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleAssol(bool possible)
{
	int l=0;
//int largeur[] ={20,10,128,72,72,72,72,72,72,72,72,72,72};
	int largeur[] = {20,10,128,128,64,64,64,64,64,64,64,64,64,64};

	if(possible==true) //saisie assolement etc..
	strcpy(TypeCol, "0000NNNNNNNNNNNNNNN");
	else//formule
	strcpy(TypeCol, "0000000000000000000");
	LaGrille->ColCount=14;//13
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;

	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	TailleGrille();

	AffAn(4);
}
//---------------------------------------------------------------------------
//Verger
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleVerger(void)
{
	int l=0;
	int largeur[] = {20,10,128,128,64,64,64}; //pour perennes

	strcpy(TypeCol, "0000NNNNNNNNNNNNNNN");
	LaGrille->ColCount=7;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;

	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;
	TailleGrille();

	LaGrille->Rows[0]->CommaText=L_TitrePer;
	//LaGrille->Rows[0]->CommaText=".,.,NOM,ESPECE,Surface,Plantation,Arrachage";
}
//---------------------------------------------------------------------------
//Vivrier
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleVivrier(void)
{
	int l=0;
	int largeur[] = {20,10,128,128,64,64,64,64}; //pour vivrier

	strcpy(TypeCol, "0000NNN");

	LaGrille->ColCount=7;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;

	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	TailleGrille();

	LaGrille->Rows[0]->CommaText=L_TitreViv;
	//LaGrille->Rows[0]->CommaText=".,.,NOM,Catégorie,Surface,Plantation,Durée";
}
//---------------------------------------------------------------------------
// Inventaire Animaux
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleInvAni(void)
{
	int l=0;
//int largeur[] ={20,10,128,48,48,48,48,48,48,48,48,48,48};
	int largeur[] = {20,10,128,72,48,48,48,48,48,48,48,48,48,48,48};

	strcpy(TypeCol, "00TNNNNNNNNNNNNNNNNN");

	LaGrille->ColCount=15;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;

	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	TailleGrille();

	AffAnInvAni();
}
//---------------------------------------------------------------------------
// a supprimer
// Variable
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleVariable(void)
{
	int l=0;
//int largeur[] ={20,10,128,72,72,72,72,72,72,72,72,72,72};
	int largeur[] = {20,10,128,64,64,64,64,64,64,64,64,64,64};

	strcpy(TypeCol, "000NNNNNNNNNNNNNNN");
	LaGrille->ColCount=13;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;

	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	TailleGrille();

	AffAn(3);
}
//---------------------------------------------------------------------------
// EmpLT
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleEmpLT(void)
{
	int l=0;
//int n,i;
//TStringList *lst;
	//     2   3  4  5  6  7  8  9  10 11
	int largeur[] = {20,10,128,108,48,48,48,48,48,72,72,24};

	//012345678901
	strcpy(TypeCol, "00TNNNNNTNNT");
	LaGrille->ColCount=12;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;
	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	TailleGrille();
	/*100206
	 n=LstNom->IndexOf("LstNomGrilleEmpLT");
	 lst=(TStringList*)LstNom->Objects[n];

	 for(i=0;i<10;i++)
	 LaGrille->Cells[i+2][0]=lst->Strings[i];
	 */
	LaGrille->Cells[2][0]=L_EMP; //"EMPRUNTS";
	LaGrille->Cells[3][0]=L_Montant;//"Montant";
	LaGrille->Cells[4][0]=L_Dur1;//"Durée 1";
	LaGrille->Cells[5][0]=L_Taux1;//"Taux  1";
	LaGrille->Cells[6][0]=L_Dur2;//"Durée 2";
	LaGrille->Cells[7][0]=L_Taux2;//"Taux  2";
	LaGrille->Cells[8][0]=L_Type;"Type";
	LaGrille->Cells[9][0]=L_Real;//"Réalisation";
	LaGrille->Cells[10][0]=L_Remb;//"Remboursement";
	LaGrille->Cells[11][0]=L_EouP;//"E/P";

}
//---------------------------------------------------------------------------
// EmpCT
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleEmpCT(void)
{
	int l=0;
	//     2   3   4  5  6  7  8
	int largeur[] = {20,10,128,108,48,48,72,72,24};

	//0123456789
	strcpy(TypeCol, "00TNNTNNT");
	LaGrille->ColCount=9;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;
	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	TailleGrille();

	LaGrille->Rows[0]->CommaText=L_TitreEmp;
//	LaGrille->Rows[0]->CommaText=".,.,EMPRUNTS,Montant,Taux,Type,Réalisation,Remboursement,E/P"
	/*
	 LaGrille->Cells[2][0]="EMPRUNTS";
	 LaGrille->Cells[3][0]="Montant";
	 LaGrille->Cells[4][0]="Taux";
	 LaGrille->Cells[5][0]="Type";
	 LaGrille->Cells[6][0]="Réalisation";
	 LaGrille->Cells[7][0]="Remboursement";
	 LaGrille->Cells[8][0]="E/P";
	 */
}
//---------------------------------------------------------------------------
// Subvention
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleSub(void)
{
	int l=0;
	//     2   3   4  5
	int largeur[] = {20,10,128,108,72,48};

	//012345
	strcpy(TypeCol, "00TNNN");
	LaGrille->ColCount=6;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;
	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	TailleGrille();

	LaGrille->Rows[0]->CommaText=L_TitreSub;
//	LaGrille->Rows[0]->CommaText=".,.,SUBVENTION,Montant,Date,Durée";
	/*
	 LaGrille->Cells[2][0]="SUBVENTION";
	 LaGrille->Cells[3][0]="Montant";
	 LaGrille->Cells[4][0]="Date";
	 LaGrille->Cells[5][0]="Durée";
	 */
}
//---------------------------------------------------------------------------
// Placement
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrillePlact(void)
{
	int l=0;
	//     2   3   4  5  6  7  8
	int largeur[] = {20,10,128,108,48,24,72,72,24};

	//0123456789
	strcpy(TypeCol, "00TNNTNNT");
	LaGrille->ColCount=9;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;
	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	TailleGrille();

	LaGrille->Rows[0]->CommaText=L_TitrePlact;
	//LaGrille->Rows[0]->CommaText=".,.,PLACEMENTS,Montant,Taux,Type,Réalisation,Terme,E/P";
	/*
	 LaGrille->Cells[2][0]="PLACEMENTS";
	 LaGrille->Cells[3][0]="Montant";
	 LaGrille->Cells[4][0]="Taux";
	 LaGrille->Cells[5][0]="Type";
	 LaGrille->Cells[6][0]="Réalisation";
	 LaGrille->Cells[7][0]="Terme";
	 LaGrille->Cells[8][0]="E/P";
	 */
}
//---------------------------------------------------------------------------
// Ouverture de Crédit
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleOccc(void)
{
//040302
	int l=0;
	//  0   1   2   3  4  5  6
	int largeur[] = {36,128,128,72,72};
	int an=Agri->DefSim->An_0;
	//0123456
	strcpy(TypeCol, "0NNNNN");
	LaGrille->ColCount=5;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=1;
	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	TailleGrille();

	LaGrille->RowCount=N_X+1;

	for(int r=1;r<LaGrille->RowCount;r++)
	{
		LaGrille->Cells[0][r]=an++; //130103
	}
	LaGrille->Rows[0]->CommaText=L_TitreOccc;
	//L_TitreOccc="Exercice,Montant,%Consommé,Taux,Frais";
	/*
	 LaGrille->Cells[0][0]="Exercice";
	 LaGrille->Cells[1][0]="Montant";
	 LaGrille->Cells[2][0]="%Consommé";
	 LaGrille->Cells[3][0]="Taux";
	 LaGrille->Cells[4][0]="Frais";
	 */
}
//---------------------------------------------------------------------------
// Financement Sommaire
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleFinSom(void)
{
//int i,n;
	int l=0;
	int largeur[] = {20,10,128,72,72,72,72,72,72,72,72,72,72,72};
//TStringList* lst;
	strcpy(TypeCol, "000NNNNNNNNNNNNNNN");

	LaGrille->ColCount=14;
	LaGrille->RowCount=9;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;

	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	TailleGrille();

	AffAnPlus1();
	/*100206
	 n=LstNom->IndexOf("LstNomFinSom");
	 lst=(TStringList*)LstNom->Objects[n];

	 for(i=0;i<8;i++)
	 {
	 LaGrille->Cells[2][i+1]=lst->Strings[i];
	 }
	 */

	LaGrille->Cells[2][1]=L_DetteLT; //"Dette LT";
	LaGrille->Cells[2][2]=L_RembCapLT;"Remb Capital LT";
	LaGrille->Cells[2][3]=L_IntLT;//"Interet LT";
	LaGrille->Cells[2][4]=L_NouvLT;//"Nouveaux LT";

	LaGrille->Cells[2][5]=L_DetteCT;//"Dette CT";
	LaGrille->Cells[2][6]=L_RembCapCT;//"Remb Capital CT";
	LaGrille->Cells[2][7]=L_IntCT;//"Interet CT";
	LaGrille->Cells[2][8]=L_NouvCT;//"Nouveaux CT";

	//aucune saisie col 3 pour row =2 3 4 et row =6 7 8
	for(int r=2;r<5;r++) LaGrille->Cells[3][r]="          -";
	for(int r=6;r<9;r++) LaGrille->Cells[3][r]="          -";
}
//---------------------------------------------------------------------------
// Immo
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleImmo(void)
{
	int l=0;
	//     2   3   4  5  6  7   8  9  10 11
	int largeur[] = {20,10,128,108,72,24,48,64,108,72};

	//012345678901
	strcpy(TypeCol, "00TNNTNTNN");
	LaGrille->ColCount=10;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;
	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	TailleGrille();
	LaGrille->Rows[0]->CommaText=L_TitreImmo;
	//L_TitreImmo=".,.,IMMOBILISATION,V Achat,Date,Type Amor,Durée Amor,TVA,V Vente,Date";

	/*
	 LaGrille->Cells[2][0]="IMMOBILISATION";
	 LaGrille->Cells[3][0]="V Achat";
	 LaGrille->Cells[4][0]="Date";
	 LaGrille->Cells[5][0]="Type Amor";
	 LaGrille->Cells[6][0]="Durée Amor";
	 LaGrille->Cells[7][0]="TVA";
	 LaGrille->Cells[8][0]="V Vente";
	 LaGrille->Cells[9][0]="Date";
	 */
}
//---------------------------------------------------------------------------
// Petit matériel
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrillePetit(void)
{
	int l=0;
	//     2   3   4  5  6  7   8  9  10 11
	int largeur[] = {20,10,48,128,72};

	//012345678901
	strcpy(TypeCol, "000N0");
	LaGrille->ColCount=5;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;
	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	TailleGrille();

	LaGrille->RowCount=N_X+1;

	for(int r=1;r<LaGrille->RowCount;r++)
	{
		LaGrille->Cells[2][r]=r;
		LaGrille->Cells[0][r]=r;
	}
//    AjoutRow=false; cf PrepareEcran
	LaGrille->Rows[0]->CommaText=L_TitrePetit;

	//L_TitrePetit=".,.,Exercice,Valeur,TVA";
	/*
	 LaGrille->Cells[2][0]="Exercice";
	 LaGrille->Cells[3][0]="Valeur";
	 LaGrille->Cells[4][0]="TVA";
	 */
}
//---------------------------------------------------------------------------
// Investissement Sommaire
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleInvSom(void)
{
	int l=0;
	int largeur[] = {20,10,128,72,72,72,72,72,72,72,72,72,72,72};
	strcpy(TypeCol, "000NNNNNNNNNNNNNNN");

	LaGrille->ColCount=14;
	LaGrille->RowCount=8;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;

	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	TailleGrille();

	AffAnPlus1();

	LaGrille->Cells[2][1]=L_V_Resid; //"V. Résiduelle";
	LaGrille->Cells[2][2]=L_Amor;//"Amortissement";
	LaGrille->Cells[2][3]=L_Achat;//"Achat";
	LaGrille->Cells[2][4]=L_Revente;//"Revente";
	LaGrille->Cells[2][5]=L_PlusVal;//"Plus Value";
	LaGrille->Cells[2][6]=L_MoinsVal;//"Moins Value";
	LaGrille->Cells[2][7]=L_ProdImmo;//"Production d'Immo";
//	LaGrille->Cells[2][8]="Tva";
	//aucune saisie col 3 sauf pour row =1
	for(int r=2;r<8;r++) LaGrille->Cells[3][r]="          -";
}
//---------------------------------------------------------------------------
// Creances et Dettes
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleCreanceDette(void)
{
	int l=0;
	//     2   3   4  5  6  7  8  9 10 11 12 13 14
	int largeur[] = {20,10,128,64,64,64,64,64,64,64,64,64,64,64,64,64,64};

	//012345678901
	strcpy(TypeCol, "00TTNN");
	LaGrille->ColCount=5;//6;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;
	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	TailleGrille();

	LaGrille->Rows[0]->CommaText=L_TitreCrDette;

	//L_TitreCrDette=".,.,PRODUIT,Valeur,Paiement";

	/*
	 LaGrille->Cells[2][0]="PRODUIT";
	 //LaGrille->Cells[3][0]="Stock O/N";
	 LaGrille->Cells[3][0]="Valeur";
	 LaGrille->Cells[4][0]="Paiement";
	 */
}

//---------------------------------------------------------------------------
// Stock
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrillePolStock(void)
{
	int l=0;
	int largeur[]= {20,64,64,64,64,64,64,64};
	int c;
	strcpy(TypeCol, "0000NNNN");
	LaGrille->ColCount =8;
	LaGrille->FixedCols=1;
	LaGrille->FixedRows=1;

	for(c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+25; //place pour l'ascenseur

	TailleGrille();
	LaGrille->Rows[0]->CommaText=L_TitrePolStock;
	//L_TitrePolStock=".,Produit,Prix,Unité,%Stocké,Maxi Stockable,%Augmentation Prix,%Décote";

	/*
	 // attention col row
	 LaGrille->Cells[1][0]="Produit";
	 LaGrille->Cells[2][0]="Prix";
	 LaGrille->Cells[3][0]="Unité";
	 LaGrille->Cells[4][0]="%Stocké";
	 LaGrille->Cells[5][0]="Maxi Stockable";
	 LaGrille->Cells[6][0]="%Augmentation Prix";
	 LaGrille->Cells[7][0]="%Décote";

	 */
	AjoutRow=true; //200802
	CellAVerifier=true;
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleStockIni(void)
{
	int l=0;
	//     2   3   4  5  6  7  8  9 10 11 12 13 14
	int largeur[] = {20,10,128,64,64,64,64,64,64,64,64,64,64,64,64,64,64};

	//012345678901
	strcpy(TypeCol, "000NNNNNNNNNNNNN");

	LaGrille->ColCount=13;
	LaGrille->RowCount=5;//100602
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;
	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	TailleGrille();

	LaGrille->Cells[2][0]="PRODUIT";
	LaGrille->Cells[2][0]=T->L_Produit.UpperCase(); //"PRODUIT";
//	LaGrille->Cells[3][0]="Quantité";
//	LaGrille->Cells[4][0]="Taux/an";
	for(int i=0;i<10;i++)
	LaGrille->Cells[i+3][0]="  "+AnsiString(AgriEnCours->DefSim->An_0+i-10);
}
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrillePasse(void)
{
	int l=0;
	int largeur[]= {128,128,128,64,64,64,64,64}; //191103
	int c;
	strcpy(TypeCol, "000NNNNNNNNNNNNN");

	LaGrille->ColCount=8;
	LaGrille->FixedCols=0;
	LaGrille->FixedRows=1;

	for(c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+40; //place pour l'ascenseur

	// attention col row
	TailleGrille();
	LaGrille->Rows[0]->CommaText=L_TitrePasse;
	//L_TitrePasse="Famille,Categorie,Nom";
	/*
	 LaGrille->Cells[0][0]="Famille";
	 LaGrille->Cells[1][0]="Categorie";
	 LaGrille->Cells[2][0]="Nom";
	 */
	AjoutRow=false;
	CellAVerifier=true;
}

//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TailleGrille(void)
{
	Grille0->Top=40;

	if(Memo->Visible==false)
	{
		Grille0->Height=HEcran-130; //150506
		Grille0->Top=40;
	}
	else
	{
		Grille0->Height=HEcran-130-Memo->Height;
		Grille0->Top=40+Memo->Height;
		Memo->Width=Grille0->Width;
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::AffAnPlus1(void)
{
	LaGrille->Cells[0][0]="";
	LaGrille->Cells[1][0]="";
	LaGrille->Cells[2][0]=L_Nom; //"NOM";

	LaGrille->Cells[3][0]="  "+AnsiString(AgriEnCours->DefSim->An_0-1);
	for(int i=0;i<10;i++)
	LaGrille->Cells[i+4][0]="  "+AnsiString(AgriEnCours->DefSim->An_0+i);

}

/*
 L_TitrePer=          ".,.,NOM,ESPECE,Surface,Plantation,Arrachage";
 L_TitreViv=          ".,.,NOM,Catégorie,Surface,Plantation,Durée";
 L_TitreEmp=          ".,.,EMPRUNTS,Montant,Taux,Type,Réalisation,Remboursement,E/P";
 L_TitreSub=          ".,.,SUBVENTION,Montant,Date,Durée";
 L_TitrePlact=        ".,.,PLACEMENTS,Montant,Taux,Type,Réalisation,Terme,E/P";
 L_TitreOccc=         "Exercice,Montant,%Consommé,Taux,Frais";
 L_TitreImmo=         ".,.,IMMOBILISATION,V Achat,Date,Type Amor,Durée Amor,TVA,V Vente,Date";
 L_TitrePetit=        ".,.,Exercice,Valeur,TVA";
 L_TitreCrDette=      ".,.,PRODUIT,Valeur,Paiement";
 L_TitrePolStock=     ".,Produit,Prix,Unité,%Stocké,Maxi Stockable,%Augmentation Prix,%Décote";
 L_TitrePasse=        "Famille,Categorie,Nom";
 L_Nom=               "NOM";
 */

