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

#include "AgriSaisieEnum.h"
#include "AgriSaisie.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//-----------------------------------------------------------------------------
/*
 IniGrille
 VersGrille

 */
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrille(TStringGrid *grille)
{
	switch(LaGrille->Tag)
	{
		case GAssol: VersGrilleAssol(Agri->V_Culture);break;
		case GPerenne: VersGrilleVerger(Agri->V_Verger);break;
		case GVivrier: VersGrilleVivrier(Agri->V_Vivrier);break;
		case GAni : VersGrilleAssol(Agri->V_Animaux);break;
		case GInvAni: MvtAniFrm->VersGrilleInvAni(Agri->V_InvAni);break;
		case GVariable: VersGrilleVariable(Categorie,Agri->V_Variable);break;
		case GProduit: VersGrilleFormule(Agri->V_Produits);break;
		case GCharge: VersGrilleFormule(Agri->V_Charges);break;
		case GChStruct: VersGrilleFormule(Agri->V_ChStruct);break;
		case GExtNeg: VersGrilleFormule(Agri->V_ExtNeg);break;
		case GExtPos: VersGrilleFormule(Agri->V_ExtPos);break;
		case GRecFam: VersGrilleFormule(Agri->V_RecFam);break;
		case GDepFam: VersGrilleFormule(Agri->V_DepFam);break;
		case GEmpLT: VersGrilleEmpLT();break;
		case GEmpCT: VersGrilleEmpCT();break;
		case GSub: VersGrilleSub();break;
		case GPlact: VersGrillePlact();break;
		case GOccc: VersGrilleOccc();break;
		case GFinSom: VersGrilleFinSom();break;
		case GImmo: VersGrilleImmo();break;
		case GPetit: VersGrillePetit();break;
		case GInvSom: VersGrilleInvSom();break;
		case GCreance: VersGrilleCreanceDette(Agri->V_Creance);break;
		case GDette: VersGrilleCreanceDette(Agri->V_Dette);break;
		case GStock: VersGrilleStockIni(Agri->V_StockIni);break;

		case GNotes: ShowMessage("stocker Memo NON définie");break;

		default:ShowMessage("Méthode VersGrille NON définie");
	}
}

//---------------------------------------------------------------------------
// Assol
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleAssol(void)
{
	int l=0;
//int largeur[] ={20,10,128,48,48,48,48,48,48,48,48,48,48};
	int largeur[] = {20,10,128,72,72,72,72,72,72,72,72,72,72};
	TailleGrille();
	strcpy(TypeCol, "00TNNNNNNNNNNNNNN");

	LaGrille->ColCount=13;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;

	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	VideGrille(LaGrille);
	AffAn();
}
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleAssol(CL_Vecteur<CL_Valeur> *vecteur)
{
	int row,r,nbelt,c,col;
	AnsiString value;
	CL_Valeur* valeur;
	CL_Atelier* atelier;

	LaGrille->RowCount=vecteur->Nbelt+3;
	nbelt=vecteur->Nbelt;

	for( r=0;r<nbelt;r++)
	{
		row=r+1;
		valeur=vecteur->Vecteur[r];
		valeur->Flag='O';
		atelier=valeur->Atelier;
		LaGrille->Objects[0][row]=(TObject*)valeur;
		LaGrille->Cells[0][row]=row;

		LaGrille->Cells[2][row]=atelier->Nom;
		for(c=0,col=3;c<10;c++,col++)
		{
			if(valeur->Valeur[c]!=0)
			LaGrille->Cells[col][row]=Aff(valeur->Valeur[c],2);
		}
	}

}
//---------------------------------------------------------------------------
//Verger
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleVerger(void)
{
	int l=0;
	int largeur[] = {20,10,128,128,64,64,64}; //pour perennes

	TailleGrille();

	LaGrille->ColCount=7;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;

	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	VideGrille(LaGrille);

	LaGrille->Rows[0]->CommaText=".,.,NOM,ESPECE,Surface,Plantation,Arrachage";
}
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleVerger(CL_Vecteur<CL_Verger>*vecteur)
{
	int row,r,nbelt;
	AnsiString value;
	CL_Verger* verger;
	CL_Atelier* atelier;
	CL_Espece* espece;

	LaGrille->RowCount=vecteur->Nbelt+3;
	nbelt=vecteur->Nbelt;

	for( r=0;r<nbelt;r++)
	{
		row=r+1;
		verger=vecteur->Vecteur[r];
		verger->Flag='O';
		atelier=verger->Atelier;
		if(atelier==NULL) continue; //ASUPPRIMER
		espece =V_Espece->trouve (verger->NoEspece);

		LaGrille->Objects[0][row]=(TObject*)verger;
		LaGrille->Cells[0][row]=row;

		LaGrille->Cells[2][row]=atelier->Nom;
		LaGrille->Cells[3][row]=espece->Nom;
		LaGrille->Cells[4][row]=Aff(verger->Surface,2);
		LaGrille->Cells[5][row]=Aff(verger->AnPlant);
		LaGrille->Cells[6][row]=Aff(verger->AnArr);
	}
}
//---------------------------------------------------------------------------
//Vivrier
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleVivrier(void)
{
	int l=0;
	int largeur[] = {20,10,128,128,64,64,64,64}; //pour vivrier

	TailleGrille();
	strcpy(TypeCol, "00TTNN");

	LaGrille->ColCount=7;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;

	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	VideGrille(LaGrille);

	LaGrille->Rows[0]->CommaText=".,.,NOM,Catégorie,Surface,Plantation,Durée";
}
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleVivrier(CL_Vecteur<CL_Verger>*vecteur)
{
	int row,r,nbelt;
	AnsiString value;
	CL_Verger* verger;
	CL_Atelier* atelier;
	int duree;
	LaGrille->RowCount=vecteur->Nbelt+3;
	nbelt=vecteur->Nbelt;

	for( r=0;r<nbelt;r++)
	{
		row=r+1;
		verger=vecteur->Vecteur[r];
		verger->Flag='O';
		atelier=verger->Atelier;
		if(atelier==NULL) continue; //ASUPPRIMER
//        espece =V_Espece->trouve (verger->NoEspece);

		LaGrille->Objects[0][row]=(TObject*)verger;
		LaGrille->Cells[0][row]=row;

		LaGrille->Cells[2][row]=atelier->Nom;
		LaGrille->Cells[3][row]=atelier->Categorie->Nom;
		LaGrille->Cells[4][row]=Aff(verger->Surface,2);
		LaGrille->Cells[5][row]=Aff(verger->AnPlant);
		duree=verger->AnArr-verger->AnPlant;
		LaGrille->Cells[6][row]=Aff(duree);
	}
}
//---------------------------------------------------------------------------
// Inventaire Animaux
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleInvAni(void)
{
	int l=0;
//int largeur[] ={20,10,128,48,48,48,48,48,48,48,48,48,48};
	int largeur[] = {20,10,128,72,48,48,48,48,48,48,48,48,48,48,48};
	TailleGrille();
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
	Memo->Width=LaGrille->Width;

	VideGrille(LaGrille);
	AffAnInvAni();
}
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleInvAni(CL_Vecteur<CL_InvAni> *vecteur)
{
	int row,r,nbelt,c,col;
	AnsiString value;
	CL_InvAni *invAni;
	CL_Item *animal;

	LaGrille->RowCount=vecteur->Nbelt+3;
	nbelt=vecteur->Nbelt;

	for( r=0;r<nbelt;r++)
	{
		row=r+1;
		invAni=vecteur->Vecteur[r];
		invAni->Flag='O';
		animal=invAni->Animal;
		LaGrille->Objects[0][row]=(TObject*)animal;
		LaGrille->Cells[0][row]=row;

		LaGrille->Cells[2][row]=animal->Nom;
		LaGrille->Cells[3][row]=Aff(invAni->ValUnit,0);
		for(c=0,col=4;c<11;c++,col++)
		{
			if(invAni->Effectif[c]!=0)
			LaGrille->Cells[col][row]=Aff(invAni->Effectif[c],0);
		}
	}

}
//-----------------------------------------------------------------------------
//Variables
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleVariable(CL_Categorie *cat,CL_Vecteur<CL_Valeur> *vecteur)
{
	int row,r,nbelt,c,col,nLigne;
	AnsiString value;
	CL_Valeur* valeur;

	nbelt=vecteur->Nbelt;
	nLigne=0;
	for( r=0;r<nbelt;r++)
	{
		valeur=vecteur->Vecteur[r];
		if(valeur->Item->NoCategorie==cat->No) nLigne++;
	}
	LaGrille->RowCount=nLigne+3;

	row=0;
	for( r=0;r<nbelt;r++)
	{
		valeur=vecteur->Vecteur[r];
		if(valeur->Item->NoCategorie!=cat->No) continue;

		row++;
		valeur->Flag='O';

		LaGrille->Objects[0][row]=(TObject*)valeur;
		LaGrille->Cells[0][row]=row;
		if(valeur->Item->Supprimable==false) LaGrille->Cells[1][row]='*';

		LaGrille->Cells[2][row]=valeur->Item->Nom;
		for(c=0,col=3;c<10;c++,col++)
		{
			if(valeur->Valeur[c]!=0)
			LaGrille->Cells[col][row]=Aff(valeur->Valeur[c],2);
		}
	}
}
//-----------------------------------------------------------------------------
//Formule
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleFormule
(CL_Vecteur<CL_Formule> *vecteur)
{
	int row,r,nbelt,c,col;
	AnsiString value;
	CL_Formule *formule;
	CL_Prog *prog;

	LaGrille->RowCount=vecteur->Nbelt+3;
	nbelt=vecteur->Nbelt;

	for( r=0;r<nbelt;r++)
	{
		row=r+1;
		formule=vecteur->Vecteur[r];
		formule->Flag='O';
		LaGrille->Objects[0][row]=(TObject*)formule;
		LaGrille->Cells[0][row]=row;
		// pour éviter plantage si on vient de version 104
		if(formule->Item==NULL) continue;

		LaGrille->Cells[2][row]=formule->Item->Nom;
		if(formule->Origine=='C')LaGrille->Cells[1][row]="C";
		for(c=0,col=3;c<10;c++,col++)
		{
			if(formule->Valeur[c]!=0)
			LaGrille->Cells[col][row]=Aff(formule->Valeur[c],0);
		}
	}
	Memo->Text="";
	if(nbelt)
	{
//        c=2;r=1;
		formule=vecteur->Vecteur[0];
		prog=formule->LesProg[0];
		if(prog)//071200
		{
			if(prog->Reseau)
			ShowMessage("AgriSaisie1 Reseau à ecrire");
			else
			Memo->Text=prog->Source;
		}
	}
}
//---------------------------------------------------------------------------
// EmpLT
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleEmpLT(void)
{
	int l=0;
	//     2   3  4  5  6  7  8  9  10 11
	int largeur[] = {20,10,128,108,48,48,48,48,48,72,72,24};

	TailleGrille();
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

	VideGrille(LaGrille);

	LaGrille->Cells[2][0]="EMPRUNTS";
	LaGrille->Cells[3][0]="Montant";
	LaGrille->Cells[4][0]="Durée 1";
	LaGrille->Cells[5][0]="Taux  1";
	LaGrille->Cells[6][0]="Durée 2";
	LaGrille->Cells[7][0]="Taux  2";
	LaGrille->Cells[8][0]="Type";
	LaGrille->Cells[9][0]="Réalisation";
	LaGrille->Cells[10][0]="Remboursement";
	LaGrille->Cells[11][0]="E/P";
}
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleEmpLT(void)
{
	int row,r,nbelt,c,col,nLigne;
	AnsiString value;
	CL_EmpLT* empLT;
	CL_Vecteur<CL_EmpLT> *vecteur=Agri->V_EmpLT;

	nbelt=vecteur->Nbelt;
	LaGrille->RowCount=nbelt+3;

	row=0;
	for( r=0;r<nbelt;r++)
	{
		empLT=vecteur->Vecteur[r];
		row++;
		empLT->Flag='O';

		LaGrille->Objects[0][row]=(TObject*)empLT;
		LaGrille->Cells[0][row]=row;

		LaGrille->Cells[2][row]= empLT->Nom;
		LaGrille->Cells[3][row]= Aff(empLT->Montant,0);
		LaGrille->Cells[4][row]= Aff(empLT->Duree);
		if(empLT->Taux ==0)LaGrille->Cells[5][row]= Aff('0');
		else LaGrille->Cells[5][row]= Aff(empLT->Taux,2);
		if(empLT->Duree2)
		{
			LaGrille->Cells[6][row]= Aff(empLT->Duree2);
			LaGrille->Cells[7][row]= Aff(empLT->Taux2,2);
		}
		LaGrille->Cells[8][row]= empLT->Type;
		LaGrille->Cells[9][row]= Aff(empLT->MReal,empLT->AReal);
		LaGrille->Cells[10][row]=Aff(empLT->MRemb,empLT->ARemb);
		LaGrille->Cells[11][row]=empLT->Pour;

	}
}
//---------------------------------------------------------------------------
// EmpCT
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleEmpCT(void)
{
	int l=0;
	//     2   3   4  5  6  7  8
	int largeur[] = {20,10,128,108,48,48,72,72,24};

	TailleGrille();
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

	VideGrille(LaGrille);

	LaGrille->Cells[2][0]="EMPRUNTS";
	LaGrille->Cells[3][0]="Montant";
	LaGrille->Cells[4][0]="Taux";
	LaGrille->Cells[5][0]="Type";
	LaGrille->Cells[6][0]="Réalisation";
	LaGrille->Cells[7][0]="Remboursement";
	LaGrille->Cells[8][0]="E/P";
}
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleEmpCT(void)
{
	int row,r,nbelt,c,col,nLigne;
	AnsiString value;
	CL_EmpCT* empCT;
	CL_Vecteur<CL_EmpCT> *vecteur=Agri->V_EmpCT;

	nbelt=vecteur->Nbelt;
	LaGrille->RowCount=nbelt+3;

	row=0;
	for( r=0;r<nbelt;r++)
	{
		empCT=vecteur->Vecteur[r];
		row++;
		empCT->Flag='O';

		LaGrille->Objects[0][row]=(TObject*)empCT;
		LaGrille->Cells[0][row]=row;

		LaGrille->Cells[2][row]= empCT->Nom;
		LaGrille->Cells[3][row]= Aff(empCT->Montant,0);
		LaGrille->Cells[4][row]= Aff(empCT->Taux,2);
		LaGrille->Cells[5][row]= empCT->Type;
		LaGrille->Cells[6][row]= Aff(empCT->MReal,empCT->AReal);
		LaGrille->Cells[7][row]= Aff(empCT->MRemb,empCT->ARemb);
		LaGrille->Cells[8][row]= empCT->Pour;

	}
}
//---------------------------------------------------------------------------
// Subvention
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleSub(void)
{
	int l=0;
	//     2   3   4  5
	int largeur[] = {20,10,128,108,72,48};

	TailleGrille();
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

	VideGrille(LaGrille);

	LaGrille->Cells[2][0]="SUBVENTION";
	LaGrille->Cells[3][0]="Montant";
	LaGrille->Cells[4][0]="Date";
	LaGrille->Cells[5][0]="Durée";
}
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleSub(void)
{
	int row,r,nbelt,c,col,nLigne;
	AnsiString value;
	CL_Sub* sub;
	CL_Vecteur<CL_Sub> *vecteur=Agri->V_Sub;

	nbelt=vecteur->Nbelt;
	LaGrille->RowCount=nbelt+3;

	row=0;
	for( r=0;r<nbelt;r++)
	{
		sub=vecteur->Vecteur[r];
		row++;
		sub->Flag='O';

		LaGrille->Objects[0][row]=(TObject*)sub;
		LaGrille->Cells[0][row]=row;

		LaGrille->Cells[2][row]= sub->Nom;
		LaGrille->Cells[3][row]= Aff(sub->Montant,0);
		LaGrille->Cells[4][row]= Aff(sub->MReal,sub->AReal);
		LaGrille->Cells[5][row]= Aff(sub->Duree);
	}
}
//---------------------------------------------------------------------------
// Placement
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrillePlact(void)
{
	int l=0;
	//     2   3   4  5  6  7  8
	int largeur[] = {20,10,128,108,48,24,72,72,24};

	TailleGrille();
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

	VideGrille(LaGrille);

	LaGrille->Cells[2][0]="PLACEMENTS";
	LaGrille->Cells[3][0]="Montant";
	LaGrille->Cells[4][0]="Taux";
	LaGrille->Cells[5][0]="Type";
	LaGrille->Cells[6][0]="Réalisation";
	LaGrille->Cells[7][0]="Terme";
	LaGrille->Cells[8][0]="E/P";
}
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrillePlact(void)
{
	int row,r,nbelt,c,col,nLigne;
	AnsiString value;
	CL_Plact* plact;
	CL_Vecteur<CL_Plact> *vecteur=Agri->V_Plact;

	nbelt=vecteur->Nbelt;
	LaGrille->RowCount=nbelt+3;

	row=0;
	for( r=0;r<nbelt;r++)
	{
		plact=vecteur->Vecteur[r];
		row++;
		plact->Flag='O';

		LaGrille->Objects[0][row]=(TObject*)plact;
		LaGrille->Cells[0][row]=row;

		LaGrille->Cells[2][row]= plact->Nom;
		LaGrille->Cells[3][row]= Aff(plact->Montant,0);
		LaGrille->Cells[4][row]= Aff(plact->Taux);
		LaGrille->Cells[5][row]= plact->Type;
		LaGrille->Cells[6][row]= Aff(plact->MReal,plact->AReal);
		LaGrille->Cells[7][row]= Aff(plact->MTerme,plact->ATerme);
		LaGrille->Cells[8][row]= plact->Pour;
	}
}
//---------------------------------------------------------------------------
// Ouverture de Crédit
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleOccc(void)
{
//040302
	int l=0;
	//  0   1   2   3  4  5  6
	int largeur[] = {24,128,128,72,72};

	TailleGrille();
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

	VideGrille(LaGrille);
	LaGrille->RowCount=N_X+1;

	for(int r=1;r<LaGrille->RowCount;r++)
	{
//    	LaGrille->Cells[2][r]=r;
		LaGrille->Cells[0][r]=r;
	}
//    AjoutRow=false; cf PrepareEcran

	LaGrille->Cells[0][0]="Exercice";
	LaGrille->Cells[1][0]="Montant";
	LaGrille->Cells[2][0]="%Consommé";
	LaGrille->Cells[3][0]="Taux";
	LaGrille->Cells[4][0]="Frais";
}
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleOccc(void)
{
	int row,r,nbelt,c,col,nLigne;
	AnsiString value;
	CL_Occc* occc;
	CL_Vecteur<CL_Occc> *vecteur=Agri->V_Occc;

	nbelt=vecteur->Nbelt;
//    LaGrille->RowCount=nbelt+3;
	if(nbelt==0)
	{
		for(int n=0;n<N_X;n++)
		{
			row=n+1;
			occc=new CL_Occc;
			occc->Flag='N';
			occc->Ex=n+1;
			Agri->V_Occc->ins(occc);
			LaGrille->Objects[0][row]=(TObject*)occc;
		}
		return;
	}

	row=0;
	for( r=0;r<nbelt;r++)
	{
		occc=vecteur->Vecteur[r];
		row++;
		occc->Flag='O';
		occc->Ex=row; // correction erreur liée à report droit intempestif
					  // ne peut plus se reproduire
		LaGrille->Objects[0][row]=(TObject*)occc;
		LaGrille->Cells[0][row]= Aff(occc->Ex);
		LaGrille->Cells[1][row]= Aff(occc->Montant,0);
		LaGrille->Cells[2][row]= Aff(occc->Pcent,0);
		LaGrille->Cells[3][row]= Aff(occc->Taux,2);
		LaGrille->Cells[4][row]= Aff(occc->Frais,0);
	}
}
//---------------------------------------------------------------------------
// Financement Sommaire
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleFinSom(void)
{
	int l=0;
	int largeur[] = {20,10,128,72,72,72,72,72,72,72,72,72,72,72};
	TailleGrille();
	strcpy(TypeCol, "00TNNNNNNNNNNNNNNN");

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

	VideGrille(LaGrille);
	AffAnPlus1();

	LaGrille->Cells[2][1]="Dette LT";
	LaGrille->Cells[2][2]="Remb Capital LT";
	LaGrille->Cells[2][3]="Interet LT";
	LaGrille->Cells[2][4]="Nouveaux LT";

	LaGrille->Cells[2][5]="Dette CT";
	LaGrille->Cells[2][6]="Remb Capital CT";
	LaGrille->Cells[2][7]="Interet CT";
	LaGrille->Cells[2][8]="Nouveaux CT";
	//aucune saisie col 3 pour row =2 3 4 et row =6 7 8
	for(int r=2;r<5;r++) LaGrille->Cells[3][r]="          -";
	for(int r=6;r<9;r++) LaGrille->Cells[3][r]="          -";
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleFinSom(void)
{
	int row,r,nbelt,c,col,cMax,nLigne;
	CL_FN_Xp1* fN_Xp1;
	CL_Vecteur<CL_FN_Xp1> *vecteur=Agri->V_FinSom;

//    LaGrille->RowCount=vecteur->Nbelt+1;
	nbelt=vecteur->Nbelt;
	if(nbelt==0)
	{
		for(int n=0;n<8;n++)
		{
			row=n+1;
			fN_Xp1=new CL_FN_Xp1;
			//fN_Xp1->Flag='N'; ne sert à rien cf DeGrilleFinSom
			Agri->V_FinSom->ins(fN_Xp1);
			LaGrille->Objects[0][row]=(TObject*)fN_Xp1;
		}
		return;
	}

	for( r=0;r<nbelt;r++)
	{
		row=r+1;
		fN_Xp1=vecteur->Vecteur[r];
		//fN_Xp1->Flag='O'; ne sert à rien cf DeGrilleFinSom
		LaGrille->Objects[0][row]=(TObject*)fN_Xp1;
		LaGrille->Cells[0][row]=row;
		if(row==1 || row==5) {col=3;cMax=N_X+1;}
		else {col=4;cMax=N_X;}

		for(c=0;c<cMax;c++,col++)
		{
			if( fN_Xp1->Valeur[c]!=0)
			LaGrille->Cells[col][row]=Aff(fN_Xp1->Valeur[c],0);
		}
	}
}
//---------------------------------------------------------------------------
// Immo
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleImmo(void)
{
	int l=0;
	//     2   3   4  5  6  7   8  9  10 11
	int largeur[] = {20,10,128,108,72,24,48,64,108,72};

	TailleGrille();
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

	VideGrille(LaGrille);

	LaGrille->Cells[2][0]="IMMOBILISATION";
	LaGrille->Cells[3][0]="V Achat";
	LaGrille->Cells[4][0]="Date";
	LaGrille->Cells[5][0]="Type Amor";
	LaGrille->Cells[6][0]="Durée Amor";
	LaGrille->Cells[7][0]="TVA";
	LaGrille->Cells[8][0]="V Vente";
	LaGrille->Cells[9][0]="Date";
}
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleImmo(void)
{
	int row,r,nbelt,c,col,nLigne;
	AnsiString value;
	CL_Immo* immo;
	CL_Vecteur<CL_Immo> *vecteur=Agri->V_Immo;

	nbelt=vecteur->Nbelt;
	LaGrille->RowCount=nbelt+3;

	row=0;
	for( r=0;r<nbelt;r++)
	{
		immo=vecteur->Vecteur[r];
		row++;
		immo->Flag='O';

		LaGrille->Objects[0][row]=(TObject*)immo;
		LaGrille->Cells[0][row]=row;

		LaGrille->Cells[2][row]= immo->Nom;
		LaGrille->Cells[3][row]= Aff(immo->ValAchat,0);
		LaGrille->Cells[4][row]= Aff(immo->MAchat,immo->AAchat);
		LaGrille->Cells[5][row]= Aff(immo->TypeAmor);
		LaGrille->Cells[6][row]= Aff(immo->Duree);
		LaGrille->Cells[7][row]= immo->Tva->Nom;
		LaGrille->Cells[8][row]= Aff(immo->ValVente,0);
		LaGrille->Cells[9][row]= Aff(immo->MVente,immo->AVente);
	}
}
//---------------------------------------------------------------------------
// Petit matériel
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrillePetit(void)
{
	int l=0;
	//     2   3   4  5  6  7   8  9  10 11
	int largeur[] = {20,10,24,128,72};

	TailleGrille();
	//012345678901
	strcpy(TypeCol, "00NNT");
	LaGrille->ColCount=5;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;
	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	VideGrille(LaGrille);
	LaGrille->RowCount=N_X+1;

	for(int r=1;r<LaGrille->RowCount;r++)
	{
		LaGrille->Cells[2][r]=r;
		LaGrille->Cells[0][r]=r;
	}
//    AjoutRow=false; cf PrepareEcran

	LaGrille->Cells[2][0]="Exercice";
	LaGrille->Cells[3][0]="Valeur";
	LaGrille->Cells[4][0]="TVA";
}
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrillePetit(void)
{
	int row,r,nbelt,c,col,nLigne;
	AnsiString value;
	CL_Petit* petit;
	CL_Vecteur<CL_Petit> *vecteur=Agri->V_Petit;

	nbelt=vecteur->Nbelt;
	if(nbelt==0)
	{
		for(int n=0;n<N_X;n++)
		{
			row=n+1;
			petit=new CL_Petit;
			petit->Flag='N';
			petit->Ex=n+1;
			petit->Tva=TvaImmo;
			petit->NoTva=TvaImmo->No;
			Agri->V_Petit->ins(petit);
			LaGrille->Objects[0][row]=(TObject*)petit;
		}
//        return;
	}

	row=0;
	for( r=0;r<nbelt;r++)
	{
		petit=vecteur->Vecteur[r];
		if(petit==NULL) continue;
		row++;
		petit->Flag='O';

		LaGrille->Objects[0][row]=(TObject*)petit;
		LaGrille->Cells[0][row]=row;

		LaGrille->Cells[2][row]= Aff(petit->Ex);
		LaGrille->Cells[3][row]= Aff(petit->ValAchat,0);
		LaGrille->Cells[4][row]= petit->Tva->Nom;
	}
}
//---------------------------------------------------------------------------
// Investissement Sommaire
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleInvSom(void)
{
	int l=0;
	int largeur[] = {20,10,128,72,72,72,72,72,72,72,72,72,72,72};
	TailleGrille();
	strcpy(TypeCol, "00TNNNNNNNNNNNNNNN");

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

	VideGrille(LaGrille);
	AffAnPlus1();

	LaGrille->Cells[2][1]="V. Résiduelle";
	LaGrille->Cells[2][2]="Amortissement";
	LaGrille->Cells[2][3]="Achat";
	LaGrille->Cells[2][4]="Revente";
	LaGrille->Cells[2][5]="Plus Value";
	LaGrille->Cells[2][6]="Moins Value";
	LaGrille->Cells[2][7]="Production d'Immo";
//	LaGrille->Cells[2][8]="Tva";
	//aucune saisie col 3 sauf pour row =1
	for(int r=2;r<8;r++) LaGrille->Cells[3][r]="          -";
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleInvSom(void)
{
	int row,r,nbelt,c,col,cMax,nLigne;
	CL_FN_Xp1* fN_Xp1;
	CL_Vecteur<CL_FN_Xp1> *vecteur=Agri->V_InvSom;

//    LaGrille->RowCount=vecteur->Nbelt+1;
	nbelt=vecteur->Nbelt;
	if(nbelt==0)
	{
		for(int n=0;n<7;n++) //7
		{
			row=n+1;
			fN_Xp1=new CL_FN_Xp1;
			//fN_Xp1->Flag='N'; inutile cf DEGrilleInvSom
			Agri->V_InvSom->ins(fN_Xp1);
			LaGrille->Objects[0][row]=(TObject*)fN_Xp1;
		}
		return;
	}

	for( r=0;r<nbelt;r++)
	{
		row=r+1;
		fN_Xp1=vecteur->Vecteur[r];
		//fN_Xp1->Flag='O';
		LaGrille->Objects[0][row]=(TObject*)fN_Xp1;
		LaGrille->Cells[0][row]=row;
		if(row==1) {col=3;cMax=N_X+1;}
		else {col=4;cMax=N_X;}

		for(c=0;c<cMax;c++,col++)
		{
			if( fN_Xp1->Valeur[c]!=0)
			LaGrille->Cells[col][row]=Aff(fN_Xp1->Valeur[c],0);
		}
	}
}
//---------------------------------------------------------------------------
// Creances et Dettes
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleCreanceDette(void)
{
	int l=0;
	//     2   3   4  5  6  7  8  9 10 11 12 13 14
	int largeur[] = {20,10,128,64,64,64,64,64,64,64,64,64,64,64,64,64,64};

	TailleGrille();
	//012345678901
	strcpy(TypeCol, "00TTNN");
	LaGrille->ColCount=6;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;
	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	VideGrille(LaGrille);

	LaGrille->Cells[2][0]="PRODUIT";
	LaGrille->Cells[3][0]="Stock O/N";
	LaGrille->Cells[4][0]="Valeur";
	LaGrille->Cells[5][0]="Paiement";
}

//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleCreanceDette(CL_Vecteur<CL_EnCours> *vecteur)
{
	int row,r,nbelt,c,col,nLigne;
	AnsiString value;
	CL_EnCours* enCours;

	nbelt=vecteur->Nbelt;
	LaGrille->RowCount=nbelt+3;

	row=0;
	for( r=0;r<nbelt;r++)
	{
		enCours=vecteur->Vecteur[r];
		row++;
		enCours->Flag='O';

		LaGrille->Objects[0][row]=(TObject*)enCours;
		LaGrille->Cells[0][row]=row;

		LaGrille->Cells[2][row]= enCours->Item->Nom;
		//LaGrille->Cells[3][row]= Aff(enCours->EnStock);
		LaGrille->Cells[3][row]= Aff(enCours->Valeur,0);
		LaGrille->Cells[4][row]= Aff(enCours->MPaie,enCours->APaie);
	}
}
//---------------------------------------------------------------------------
// Stock
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::IniGrilleStockIni(void)
{
	int l=0;
	//     2   3   4  5  6  7  8  9 10 11 12 13 14
	int largeur[] = {20,10,128,64,64,64,64,64,64,64,64,64,64,64,64,64,64};

	TailleGrille();
	//012345678901
	strcpy(TypeCol, "00TNNNNNNNNNNNN");

	LaGrille->ColCount=13;
	LaGrille->FixedRows=1;
	LaGrille->FixedCols=2;
	for(int c=0;c<LaGrille->ColCount;c++)
	{
		LaGrille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	LaGrille->Width=l+6+25;

	VideGrille(LaGrille);

	LaGrille->Cells[2][0]="PRODUIT";
//	LaGrille->Cells[3][0]="Quantité";
//	LaGrille->Cells[4][0]="Taux/an";
	for(int i=0;i<10;i++)
	LaGrille->Cells[i+3][0]="  "+AnsiString(AgriEnCours->DefSim->An_0+i-10);
}
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleStockIni(CL_Vecteur<CL_StockIni> *vecteur)
{
	int row,r,nbelt,c,i;
	AnsiString value;
	CL_StockIni* stock;

	nbelt=vecteur->Nbelt;
	LaGrille->RowCount=nbelt+3;

	row=0;
	for( r=0;r<nbelt;r++)
	{
		stock=vecteur->Vecteur[r];
		row++;
		stock->Flag='O';

		LaGrille->Objects[0][row]=(TObject*)stock;
		LaGrille->Cells[0][row]=row;

		LaGrille->Cells[2][row]= stock->Item->Nom;
		for(i=0,c=3;i<N_X;i++,c++)
		LaGrille->Cells[c][row]= Aff(stock->Quantite[i],0);
		row++;
		LaGrille->Cells[2][row]="   Prix Revient";
		for(i=0,c=3;i<N_X;i++,c++)
		LaGrille->Cells[c][row]= Aff(stock->PrixRevient[i],2);

	}
	LaGrille->RowCount=row+2;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::TailleGrille(void)
{
	//LaGrille->RowHeights[0]=24;
	Grille0->Top=40;

	switch(LaGrille->Tag)
	{
		case GOccc: Grille0->Height=Grille0->DefaultRowHeight*(N_X+2);return;
		case GFinSom:Grille0->Height=Grille0->DefaultRowHeight*(9+1);return;
		case GInvSom:Grille0->Height=Grille0->DefaultRowHeight*(8+1);return;
	}
	if(Memo->Visible==false)
	{
		Grille0->Height=HEcran-130;
		Grille0->Top=40;
	}
	else
	{
		Grille0->Height=HEcran-130-Memo->Height;
		Grille0->Top=40+Memo->Height;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::AffAn(void)
{
	LaGrille->Cells[0][0]="";
	LaGrille->Cells[1][0]="";
	LaGrille->Cells[2][0]="NOM";

	for(int i=0;i<10;i++)
	LaGrille->Cells[i+3][0]="  "+AnsiString(Agri->DefSim->An_0+i);

}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::AffAnPlus1(void)
{
	LaGrille->Cells[0][0]="";
	LaGrille->Cells[1][0]="";
	LaGrille->Cells[2][0]="NOM";

	LaGrille->Cells[3][0]="  "+AnsiString(AgriEnCours->DefSim->An_0-1);
	for(int i=0;i<10;i++)
	LaGrille->Cells[i+4][0]="  "+AnsiString(AgriEnCours->DefSim->An_0+i);

}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::AffAnInvAni(void)
{
	LaGrille->Cells[0][0]="";
	LaGrille->Cells[1][0]="";
	LaGrille->Cells[2][0]="NOM";
	LaGrille->Cells[3][0]="Valeur unitaire";

	LaGrille->Cells[4][0]="  "+AnsiString(AgriEnCours->DefSim->An_0-1);
	for(int i=0;i<11;i++)
	LaGrille->Cells[i+5][0]="  "+AnsiString(AgriEnCours->DefSim->An_0+i);

}
