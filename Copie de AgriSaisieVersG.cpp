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
//        case GInvAni:   MvtAniFrm->VersGrilleInvAni(Agri->V_InvAni);break;
		case GVariable: VersGrilleVariable(Agri->V_Variable);break;
		case GProduit: VersGrilleFormule(Agri->V_Produits,V_CatProduit);break;
		case GCharge: VersGrilleFormule(Agri->V_Charges,V_CatCharge);break;
		case GChStruct: VersGrilleFormule(Agri->V_ChStruct,V_CatChStruct);break;
		case GExtNeg: VersGrilleFormule(Agri->V_ExtNeg,V_CatExternalite);break;
		case GExtPos: VersGrilleFormule(Agri->V_ExtPos,V_CatExternalite);break;
		case GRecFam: VersGrilleFormule(Agri->V_RecFam,V_CatRecFam);break;
		case GDepFam: VersGrilleFormule(Agri->V_DepFam,V_CatDepFam);break;
		case GRecDiv: VersGrilleFormule(Agri->V_RecDiv,V_CatRecDiv);break;
		case GDepDiv: VersGrilleFormule(Agri->V_DepDiv,V_CatDepDiv);break;
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
		case GPolStock: VersGrillePolStock();break;
		case GPasse: VersGrillePasse();break;
		case GNotes: ShowMessage("stocker Memo NON définie");break;

		default:ShowMessage("Méthode VersGrille NON définie");
	}
}

//---------------------------------------------------------------------------
// Assol
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleAssol(CL_Vecteur<CL_Valeur> *vecteur)
{
	int row,r,nbelt,c,col;
	AnsiString value;
	CL_Valeur* valeur;
	CL_Atelier* atelier;
	int col0=4;

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
		LaGrille->Cells[3][row]=atelier->Categorie->Nom;
		for(c=0,col=col0;c<10;c++,col++)
		{
			LaGrille->Cells[col][row]=Aff(valeur->Valeur[c],2);
		}
	}

	CellInitiale();
}
//---------------------------------------------------------------------------
//Verger
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
	CellInitiale();

}
//---------------------------------------------------------------------------
//Vivrier
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
	CellInitiale();
}
//---------------------------------------------------------------------------
// Inventaire Animaux
//-----------------------------------------------------------------------------
//Variables
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleVariable(CL_Vecteur<CL_Valeur> *vecteur)
{
	int row,r,nbelt,c,col;
	AnsiString value;
	CL_Valeur* valeur;

	nbelt=vecteur->Nbelt;
	LaGrille->RowCount=vecteur->Nbelt+3;

	row=0;
	for( r=0;r<nbelt;r++)
	{
		valeur=vecteur->Vecteur[r];

		row++;
		valeur->Flag='O';

		LaGrille->Objects[0][row]=(TObject*)valeur;
		LaGrille->Cells[0][row]=row;
//		if(valeur->Item->Supprimable==false) LaGrille->Cells[1][row]='*';

		LaGrille->Cells[2][row]=valeur->Item->Nom;
		LaGrille->Cells[3][row]=valeur->Item->Categorie->Nom;
		for(c=0,col=4;c<10;c++,col++)
		{
			if(valeur->Valeur[c]!=0)
			LaGrille->Cells[col][row]=Aff(valeur->Valeur[c],2);
		}
	}
	CellInitiale();
}
//-----------------------------------------------------------------------------
//Formule
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleFormule(
		CL_Vecteur<CL_Formule> *vecteur,
		CL_Vecteur<CL_Categorie> *vCat )
{
	int i,n;
	int row,c,col;
	AnsiString value;
	CL_Categorie *categorie;
	CL_Formule *formule;
	CL_Prog *prog0;
	int colQ=4;
//!!??
//	formule=Agri->V_ChStruct->Vecteur[0];

	prog0=NULL;
	LaGrille->RowCount=vecteur->Nbelt+3;
	row=0;
	for(n=0;n<vCat->Nbelt;n++)
	{
		categorie=vCat->Vecteur[n];

		for( i=0;i<vecteur->Nbelt;i++)
		{
			formule=vecteur->Vecteur[i];
			// pour éviter plantage si on vient de version 104
			if(formule->Item==NULL) continue;
			if(formule->Item->Categorie==categorie)
			{
				row++;
				if(row==1) prog0=formule->LesProg[0];
				formule->Flag='O';
				LaGrille->Objects[0][row]=(TObject*)formule;
				LaGrille->Cells[0][row]=row;

				LaGrille->Cells[2][row]=formule->Item->Nom;
				LaGrille->Cells[3][row]=formule->Item->Categorie->Nom;
				if(formule->Origine=='C')LaGrille->Cells[1][row]="C";
				for(c=0,col=4;c<10;c++,col++)
				{
					if(formule->Valeur[c]!=0)
					LaGrille->Cells[col][row]=Aff(formule->Valeur[c],0);
				}
			}
		}
	}

	CellInitiale();

	Memo->Text="";
	// à l'affichage de la grille se mettre en col 3 row 1
	if(prog0)
	{
		LaGrille->Col=colQ;
		LaGrille->Row=1;
		Memo->Text=prog0->Source;
	}
//    CellInitiale();

}
//---------------------------------------------------------------------------
// EmpLT
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleEmpLT(void)
{
	int row,r,nbelt;
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
	CellInitiale();

}
//---------------------------------------------------------------------------
// EmpCT
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleEmpCT(void)
{
	int row,r,nbelt;
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
	CellInitiale();
}
//---------------------------------------------------------------------------
// Subvention
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleSub(void)
{
	int row,r,nbelt;
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
	CellInitiale();
}
//---------------------------------------------------------------------------
// Placement
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrillePlact(void)
{
	int row,r,nbelt;
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
	CellInitiale();
}
//---------------------------------------------------------------------------
// Ouverture de Crédit
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleOccc(void)
{
	int row,r,nbelt;
	AnsiString value;
	CL_Occc* occc;
	CL_Vecteur<CL_Occc> *vecteur=Agri->V_Occc;
	int an=Agri->DefSim->An_0; //131003

	nbelt=vecteur->Nbelt;
//    LaGrille->RowCount=nbelt+3;
	if(nbelt==0)
	{
		for(int n=0;n<N_X;n++)
		{
			row=n+1;
			occc=new CL_Occc();
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
//        LaGrille->Cells[0][row]= Aff(occc->Ex);
		LaGrille->Cells[0][row]= Aff(an++);
		LaGrille->Cells[1][row]= Aff(occc->Montant,0);
		LaGrille->Cells[2][row]= Aff(occc->Pcent,0);
		LaGrille->Cells[3][row]= Aff(occc->Taux,2);
		LaGrille->Cells[4][row]= Aff(occc->Frais,0);
	}
	CellInitiale();
}
//---------------------------------------------------------------------------
// Financement Sommaire
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleFinSom(void)
{
	int row,r,nbelt,c,col,cMax;
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
	CellInitiale();

}
//---------------------------------------------------------------------------
// Immo
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleImmo(void)
{
	int row,r,nbelt;
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
	CellInitiale();
}
//---------------------------------------------------------------------------
// Petit matériel
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrillePetit(void)
{
	int row,r,nbelt;
	AnsiString value;
	CL_Petit* petit;
	CL_Vecteur<CL_Petit> *vecteur=Agri->V_Petit;

	nbelt=vecteur->Nbelt;
	if(nbelt==0)
	{
		for(int n=0;n<N_X;n++)
		{
			row=n+1;
			petit=new CL_Petit();
			petit->Flag='N';
			petit->Tva=TvaImmo;
			petit->NoTva=TvaImmo->No;
			Agri->V_Petit->ins(petit);
			LaGrille->Objects[0][row]=(TObject*)petit;
		}
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

		LaGrille->Cells[2][row]= Aff(r+Agri->DefSim->An_0); //130303
		LaGrille->Cells[3][row]= Aff(petit->ValAchat,0);
		LaGrille->Cells[4][row]= petit->Tva->Nom;
	}
	CellInitiale();
}
//---------------------------------------------------------------------------
// Investissement Sommaire
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleInvSom(void)
{
	int row,r,nbelt,c,col,cMax;
	CL_FN_Xp1* fN_Xp1;
	CL_Vecteur<CL_FN_Xp1> *vecteur=Agri->V_InvSom;

//    LaGrille->RowCount=vecteur->Nbelt+1;
	nbelt=vecteur->Nbelt;
	if(nbelt==0)
	{
		for(int n=0;n<7;n++) //7
		{
			row=n+1;
			fN_Xp1=new CL_FN_Xp1();
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
		LaGrille->Cells[col][row]=Aff(fN_Xp1->Valeur[c],0);
	}
	CellInitiale();

}
//---------------------------------------------------------------------------
// Creances et Dettes
//-----------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrilleCreanceDette(CL_Vecteur<CL_EnCours> *vecteur)
{
	int row,r,nbelt;
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
	CellInitiale();

}
//---------------------------------------------------------------------------
// Stock
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrillePolStock(void)
{
	int i;
	int r;
//CL_QuanVal  *quanVal;
//CL_Item     *item;
	CL_PolStock *polStock;
	r=1;
	for(i=0;i<Agri->V_PolStock->Nbelt;i++,r++)
	{
		polStock=Agri->V_PolStock->Vecteur[i];
		polStock->AffRow(LaGrille,r);
	}
	LaGrille->RowCount=r+2;
	AjoutRow=true;
	CellInitiale();
}
//---------------------------------------------------------------------------
// stocks initiaux
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
		LaGrille->Cells[0][row]=(row+1)/2;

		LaGrille->Cells[2][row]= stock->Item->Nom;
		for(i=0,c=3;i<N_X;i++,c++)
		LaGrille->Cells[c][row]= Aff(stock->Quantite[i],0);
		row++;
		LaGrille->Cells[2][row]="   Prix Revient";
		for(i=0,c=3;i<N_X;i++,c++)
		LaGrille->Cells[c][row]= Aff(stock->PrixRevient[i],2);

	}
	LaGrille->RowCount=row+2;
	CellInitiale();
}
//---------------------------------------------------------------------------
// Passe
//------------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::VersGrillePasse(void)
{
	int c,i,r,an;
	int nbElt;
	CL_Elt *elt;
	LabelModifie->Visible=false;
	nbElt=0;
	for(i=0;i<V_Elt->Nbelt;i++)
	{
		elt=V_Elt->Vecteur[i];
		if(elt->Passe)
		nbElt++;
	}
	if(nbElt==0)
	{
		MessageBox(Handle,"","Aucune Donnée à introduire",MB_ICONEXCLAMATION);
		return;
	}

	LaGrille->RowCount=nbElt+1;
	OrdreModif=false;

	an=Agri->DefSim->An_0-5;
	c=3;
	for(i=0;i<5;i++)
	LaGrille->Cells[c+i][0]=Aff(an+i); //AnsiString(an+i);

	r=0;
	for(i=0;i<V_Elt->Nbelt;i++)
	{
		elt=V_Elt->Vecteur[i];
		if(elt->Passe==NULL) continue;

		r++;
		LaGrille->Objects[0][r]=(TObject*)elt;
		LaGrille->Cells[0][r]=elt->NomFamille;
		LaGrille->Cells[1][r]=elt->NomCat;
		LaGrille->Cells[2][r]=elt->Nom;
		for(c=0;c<5;c++)
		LaGrille->Cells[c+3][r]=Aff(elt->Passe[c],0);
	}
	CellInitiale();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::AffAn(int col0)
{
	int i;
	int col;
	LaGrille->Cells[0][0]="";
	LaGrille->Cells[1][0]="";
	LaGrille->Cells[2][0]="NOM";
	if(col0==4)
	LaGrille->Cells[3][0]="Catégorie";

	for(i=0,col=col0;i<10;i++,col++)
	LaGrille->Cells[col][0]="  "+AnsiString(Agri->DefSim->An_0+i);

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
