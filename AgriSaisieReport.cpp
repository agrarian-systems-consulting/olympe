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
#include "Compilateur.h"

#include "AgriSaisieEnum.h"
#include "AgriSaisie.h"
#include "MvtAni.h"

extern CL_Compil *Compil;

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
/*
 CellDebut
 SaisirCell
 ReportDroit
 RecopBas
 */
//A SUPPRIMER
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::CellDebut(void)
{
//int g=LaGrille->Tag;

//	CellAVerifier=false;

//    LaGrille->Col=3;
//    LaGrille->Row=1;
	RepereCellEC(LaGrille->Col,LaGrille->Row);
	ShowMessage("CellDebut");
//	CellModifiable(true);   //261103???
//    ColM[g]=LaGrille->Col;
//    RowM[g]=LaGrille->Row;

//	CellAVerifier=true;//261103???
//   	ValueAvant=LaGrille->Cells[ColM[g]][RowM[g]];
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::SaisirCell(int col,int row)
{
	switch(LaGrille->Tag)
	{
		case GProduit:
		case GCharge:
		case GChStruct:
		case GRecDiv:
		case GDepDiv:
		case GRecFam:
		case GDepFam:
		case GExtNeg:
		case GExtPos: SaisirCellFormule(col,row);break;
		default: return;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::SaisirCellFormule(int col,int row)
{
	int colQ=4;
	CL_Formule *formule;
	CL_Prog *prog;
	int n;

//	CellModifiable(true);
	CellModifiable(false);
	if(col<colQ) return;

	formule=(CL_Formule*)LaGrille->Objects[0][row];

	if(formule)
	{
		n=col-colQ;
		prog=formule->LesProg[n];
		if(prog) Memo->Text=prog->Source;
		else Memo->Text="";
	}
	else Memo->Text="";
	Memo->SetFocus();
}
//---------------------------------------------------------------------------
//BtReportDroitClick
// peut etre enabled=false Donc toutes les grilles ne sont pas examinées
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::BtReportDroitClick(TObject *Sender)
{
	switch(LaGrille->Tag)
	{
		case GAssol:
		case GAni:
		case GVariable: RepDroitAssol(2); break; //variable

		case GExtNeg:
		case GExtPos:
		case GProduit:
		case GCharge:
		case GChStruct:
		case GRecDiv:
		case GDepDiv:
		case GRecFam:
		case GDepFam: RepDroitFormule(); break;

		case GEmpLT: RepDroitEmpLT();break;
		case GFinSom: RepDroitFinSom(); break;
		case GInvSom: RepDroitInvSom(); break;

//        case GCreance:
//        case GDette:    RepDroitCreance();   break;

		case GStock: RepDroitStockIni(); break;
		case GPasse: RepDroitAssol(0,0); break;
		default:ShowMessage("AgriSaisieReport RepDroit Oubli");break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RepDroitAssol(int digits,int colQ)
{
	int c,c0;
	int r0;
//AnsiString as;
	if(LaGrille->Col <colQ )return;
	LabelModifie->Visible=true;//071101
	//GrilleModif[LaGrille->Tag]=true;
	c0=LaGrille->Col;
	r0=LaGrille->Row;
	ReAffFloat(c0,r0,digits);
	for(c=c0+1;c<LaGrille->ColCount;c++)
	{
		if(RepPossible(c,r0)==false) continue;

		LaGrille->Cells[c][r0]=LaGrille->Cells[c0][r0];
	}
}
/*
 //---------------------------------------------------------------------------
 void __fastcall TAgriSaisieFrm::RepDroitInvAni(void)
 voir MvtAni
 */
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RepDroitFormule(void)
{
	int c,c0,colQ=4;
	int r0;
	int n,n0;
	bool rep;
	CL_Formule *formule;
	CL_Prog *prog;
	if(LaGrille->Col <colQ )return;
	c0=LaGrille->Col;
	r0=LaGrille->Row;
	n0=c0-colQ;
	formule=(CL_Formule*)LaGrille->Objects[0][r0];
	prog=formule->LesProg[n0];

	if(prog==NULL)
	{
		rep=CreeProg(formule,n0);
		if(rep==false) return;
		prog=formule->LesProg[n0];
		Compil->JeTraite=formule->Nom;
		Compil->Calculer(prog->Reseau,prog->Arbre,n0,n0+1,formule->Valeur);
	}
	for(n=n0+1;n<N_X;n++)
	{
		if(formule->LesProg[n]==NULL)
		formule->LesProg[n]=prog;
		else if(ChBRepTout->Checked==true)
		formule->LesProg[n]=prog;

		Compil->JeTraite=formule->Nom;
		Compil->Calculer(prog->Reseau,prog->Arbre,n,n+1,formule->Valeur);
	}
	LabelModifie->Visible=true;

	for(c=c0+1;c<LaGrille->ColCount;c++)
	{
		n=c-colQ;
		LaGrille->Cells[c][r0]=Aff(formule->Valeur[n],0);
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RepDroitEmpLT(void)
{
	int colReal=9;
	int colRemb=colReal+1;
	int row=LaGrille->Row;
	int m,a;
	AnsiString type=GrilleChaine(8,row);

	if(LaGrille->Col !=colReal && LaGrille->Col !=colRemb)return;

	GrilleMoisAn(colReal,row,m,a);
	switch(type[2])
	{
		case 'm':m+=1; break;
		case 't':m+=3; break;
		case 's':m+=6; break;
		case 'a':m+=12; break;
	}
	if(m>12) {m-=12;a++;}
	LaGrille->Cells[colRemb][row]=Aff(m,a);
	LabelModifie->Visible=true;

}
// r0=2 3 4 r0= 6 7 8 aucune saisie
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RepDroitFinSom(void)
{
	int c,c0,colQ=3;
	int r0;
	c0=LaGrille->Col;
	r0=LaGrille->Row;
	if(LaGrille->Col <colQ )return;
	if(c0==3)
	{
		if(!(r0==1 || r0==5)) return;
	}
	ReAffFloat(c0,r0,0);
	for(c=c0+1;c<LaGrille->ColCount;c++)
	{
		if(RepPossible(c,r0)==false ) continue;

		LaGrille->Cells[c][r0]=LaGrille->Cells[c0][r0];
	}

}
// r0!=1 aucune saisie
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RepDroitInvSom(void)
{
	int c,c0,colQ=3;
	int r0;
	c0=LaGrille->Col;
	r0=LaGrille->Row;
	if(LaGrille->Col <colQ )return;
	if(c0==3)
	{
		if(r0!=1 ) return;
	}
	ReAffFloat(c0,r0,0);
	for(c=c0+1;c<LaGrille->ColCount;c++)
	{
		if(RepPossible(c,r0)==false) continue;

		LaGrille->Cells[c][r0]=LaGrille->Cells[c0][r0];
	}
	LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RepDroitCreance(void)
{
	int colPaie=5,colLiv=6;
	int row=LaGrille->Row;
	int m,a;
	AnsiString type=GrilleChaine(8,row);

	if(LaGrille->Col !=colPaie && LaGrille->Col !=colLiv)return;
	if(LaGrille->Col ==colPaie)
	{
		GrilleMoisAn(colPaie,row,m,a);
		LaGrille->Cells[colLiv][row]=Aff(m,a);
	}
	else //if(LaGrille->Col ==colLiv)
	{
		GrilleMoisAn(colLiv,row,m,a);
		LaGrille->Cells[colPaie][row]=Aff(m,a);
	}
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RepDroitStockIni(void)
{
	int c,c0,colQ=3;
	int r0;
	c0=LaGrille->Col;
	r0=LaGrille->Row;
	if(LaGrille->Col <colQ )return;
	ReAffFloat(c0,r0,0);
	for(c=c0+1;c<LaGrille->ColCount;c++)
	{
		if(RepPossible(c,r0)==false) continue;
		LaGrille->Cells[c][r0]=LaGrille->Cells[c0][r0];
	}
	LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::BtRepToutDroitClick(TObject *Sender)
{
// Report Tout a Droite
	switch(LaGrille->Tag)
	{
		case GAssol:
		case GAni:
		case GVariable: RepDroitToutAssol(2); break; //variable

		case GExtNeg:
		case GExtPos:
		case GProduit:
		case GCharge:
		case GChStruct:
		case GRecDiv:
		case GDepDiv:
		case GRecFam:
		case GDepFam: RepDroitToutFormule(); break;

		case GPasse: RepDroitToutAssol(2); break;//variable
		default:ShowMessage("AgriSaisieReport RepDroit Oubli");break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RepDroitToutAssol(int digits)
{
	int c,c0,colQ=4;
	int r,r0;
	if(LaGrille->Col <colQ )return;
	LabelModifie->Visible=true; //071101
	//GrilleModif[LaGrille->Tag]=true;
	c0=LaGrille->Col;
	r0=LaGrille->Row;
	ReAffFloat(c0,r0,digits);
	for(r=r0;r<LaGrille->RowCount;r++)
	{
		if(LaGrille->Cells[colQ-1][r]=="") continue;
		for(c=c0+1;c<LaGrille->ColCount;c++)
		{
			if(RepPossible(c,r)==false) continue;

			LaGrille->Cells[c][r]=LaGrille->Cells[c0][r];
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RepDroitToutFormule(void)
{
	int c,c0,colQ=4;
	int r,r0;
	int n,n0;
	bool rep;
	CL_Formule *formule;
	CL_Prog *prog;
	if(LaGrille->Col <colQ )return;
	c0=LaGrille->Col;
	r0=LaGrille->Row;
	for(r=r0;r<LaGrille->RowCount;r++) //120905
	{
		n0=c0-colQ;
		formule=(CL_Formule*)LaGrille->Objects[0][r];
		if(formule==NULL) break; //310805
		prog=formule->LesProg[n0];

		if(prog==NULL)
		{
			rep=CreeProg(formule,n0);
			if(rep==false) return;
			prog=formule->LesProg[n0];
			Compil->JeTraite=formule->Nom;
			Compil->Calculer(prog->Reseau,prog->Arbre,n0,n0+1,formule->Valeur);
		}
		if(ChBRepTout->Checked==true)
		{
			for(n=n0+1;n<N_X;n++)
			{
				formule->LesProg[n]=prog;
				Compil->JeTraite=formule->Nom;
				Compil->Calculer(prog->Reseau,prog->Arbre,n,n+1,formule->Valeur);
			}
			LabelModifie->Visible=true;

		}
		for(c=c0+1;c<LaGrille->ColCount;c++)
		{
			n=c-colQ;
			LaGrille->Cells[c][r]=Aff(formule->Valeur[n],0);
		}
	}
}
//---------------------------------------------------------------------------
//Report BAS une colonne
// Recop BAS ligne
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::BtReportBasClick(TObject *Sender)
{
	switch(LaGrille->Tag)
	{
		case GAssol: RepBasAssol();break;
		case GPerenne: RepBasPerenne();break;
		case GEmpLT: RepBasLT(); break;
		case GEmpCT: RepBasCT(); break;
		case GStock: RepBasStockIni();break;
		case GPetit: RepBasPetit(); break;
		case GOccc: RepBasOccc(); break;
		case GPolStock: RepBasPolStock();break;
		case GImmo: RepBasImmo();break;
		case GPasse: RepBasCol(3);break; //interdit de recopier pour col<3
		case GCreance:
		case GDette: RepBasCol(3); break;

		default:ShowMessage("AgriSaisieReport RepBas Oubli");break;

	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RepBasAssol(void)
{
	int r;
	AnsiString as;
	int colQ=4;
	int row=LaGrille->Row;
	int col=LaGrille->Col;

	if(col<colQ) return;

	for(r=row+1;r<LaGrille->RowCount;r++)
	{
		as=LaGrille->Cells[2][r];
		if(as.IsEmpty()==true) continue;

		if(RepPossible(col,r)==false) continue;
		LaGrille->Cells[col][r]=LaGrille->Cells[col][row];
		LabelModifie->Visible=true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RepBasPerenne(void)
{
	int r;
	AnsiString as;
	int colQ=2;
	int row=LaGrille->Row;
	int col=LaGrille->Col;
	ShowMessage("RepBasPerenne");
	if(col<colQ) return;

	for(r=row+1;r<LaGrille->RowCount;r++)
	{
		as=LaGrille->Cells[2][r];
		if(as.IsEmpty()==true) continue;

		if(RepPossible(col,r)==false) continue;
		LaGrille->Cells[col][r]=LaGrille->Cells[col][row];
		LabelModifie->Visible=true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RepBasLT(void)
{
//n'est utilisé que pour EmpLT ???
	int row=LaGrille->Row;
	int col=LaGrille->Col;
	int r,rMax;
	AnsiString s=LaGrille->Cells[col][row];
//AnsiString as;
	// si rien à recopier  ...
	if(s.IsEmpty() ) return;

	if(LaGrille->Tag==GImmo && col==7) {RepBasTvaImmo(col,row);return;}
	if(LaGrille->Tag==GPetit && col==4) {RepBasTvaPetit(col,row);return;}

	if( LaGrille->Tag==GOccc) rMax=N_X+1;
	else if(LaGrille->Tag==GPetit) rMax=N_X+1;
	else rMax=LaGrille->RowCount-2;

	for(r=row+1;r<rMax;r++)
	{
		//as=LaGrille->Cells[col][r];
		//if(as.Length()>1 && ChBRepTout->Checked==false) continue;
		if(RepPossible(col,r)==false) continue;

		LaGrille->Cells[col][r]=s;
		//LabelModifie->Visible=true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RepBasCT(void)
{
	int r;
	AnsiString as;
	int colQ=2;
	int row=LaGrille->Row;
	int col=LaGrille->Col;

	if(col<colQ) return;

	for(r=row+1;r<LaGrille->RowCount;r++)
	{
		as=LaGrille->Cells[2][r];
		if(as.IsEmpty()==true) continue;

		if(RepPossible(col,r)==false) continue;
		LaGrille->Cells[col][r]=LaGrille->Cells[col][row];
		LabelModifie->Visible=true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RepBasImmo(void)
{
	int row=LaGrille->Row;
	int col=LaGrille->Col;
	int r; //rMax;
	AnsiString s=LaGrille->Cells[col][row];
	CL_Immo *immoPere,*immo;
	immoPere=(CL_Immo*)LaGrille->Objects[0][row];
	if(immoPere==NULL)
	{
		ShowMessage(L_ErrPasImmo);
		//ShowMessage("Pas d'Immobilisation à reporter");
		return;
	}
	switch(col)
	{
		case 0:
		case 1:
		case 2:
		case 3:
		ShowMessage(L_ErrRepImpo);
		//ShowMessage("Report impossible dans cette colonne");
		case 4:
		case 5:
		case 6:
		case 8:
		case 9:
		for(r=row+1;r<LaGrille->RowCount;r++)
		{
			if(RowVide(r)==true) continue;
			if(RepPossible(col,r)==false) continue;

			LaGrille->Cells[col][r]=s;
		}
		LabelModifie->Visible=true;
		break;
		case 7:
		for(r=row+1;r<LaGrille->RowCount;r++)
		{
			if(RowVide(r)==true) continue;
			if(RepPossible(col,r)==false) continue;

			LaGrille->Cells[col][r]=s;
			immo=(CL_Immo*)LaGrille->Objects[0][r];
			immo->Tva= immoPere->Tva;
			immo->NoTva= immoPere->NoTva;
		}
		LabelModifie->Visible=true;
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RepBasStockIni(void)
{
//n'est utilisé que pour EmpLT ???
	int row=LaGrille->Row;
	int col=LaGrille->Col;
	int r;
	int colNom=2;
	AnsiString s=LaGrille->Cells[col][row];

	if(col==colNom) return;

	for(r=row+1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;

		if(RepPossible(col,r)==false) continue;
		LaGrille->Cells[col][r]=s;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RepBasOccc(void)
{
//n'est utilisé que pour EmpLT ???
	int row=LaGrille->Row;
	int col=LaGrille->Col;
	int r;
	AnsiString s;
	float montant,pcent,taux,frais;
	if(col==6)
	{
		ShowMessage(L_ErrIntCal);
		//ShowMessage("Le montant des interets est calculé !!");
		return;
	}
	montant=GrilleFloat(1,row); //101002
	pcent= GrilleFloat(2,row);
	taux= GrilleFloat(3,row);
	frais=montant*(pcent/100)*(taux/100);
	LaGrille->Cells[4][row]=Aff(frais,0);

	s=LaGrille->Cells[col][row];
	for(r=row+1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;

		if(RepPossible(col,r)==false) continue;
		LaGrille->Cells[col][r]=s;

		montant=GrilleFloat(1,r); //101002
		pcent= GrilleFloat(2,r);
		taux= GrilleFloat(3,r);
		frais=montant*(pcent/100)*(taux/100);
		LaGrille->Cells[4][r]=Aff(frais,0);

	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RepBasPolStock(void)
{
	int r;
	int col=LaGrille->Col;
	int row=LaGrille->Row;
	AnsiString s=LaGrille->Cells[col][row];

	if(col<4) return;

	LabelModifie->Visible=true;

	for(r=row+1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		if(RepPossible(col,r)==false) continue;

		LaGrille->Cells[col][r]=s;
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::BtRecopBasClick(TObject *Sender)
{
	int row=LaGrille->Row;
	int r,c,rMax;
	int c0;
	float montant,pcent,taux,frais;
	if (LaGrille->Tag==GPerenne)
	{
		RecopBasPerenne();
		return;
	}

	if (LaGrille->Tag==GOccc) {rMax=N_X+1;c0=1;}
	else if(LaGrille->Tag==GPetit) {rMax=N_X+1;c0=3;}
	else if(LaGrille->Tag==GPolStock) {rMax=LaGrille->RowCount;c0=4;}
	else {rMax=LaGrille->RowCount-2;c0=3;} //-2 ou -3

	if (LaGrille->Tag==GImmo) RepBasTvaImmo(7,row);
	else if(LaGrille->Tag==GPetit) RepBasTvaPetit(4,row);

	if (LaGrille->Tag==GOccc)
	{
		montant=GrilleFloat(1,row);
		pcent= GrilleFloat(2,row);
		taux= GrilleFloat(3,row);
		frais=montant*(pcent/100)*(taux/100);
		LaGrille->Cells[4][row]=Aff(frais,0);
	}

	for(c=c0;c<LaGrille->ColCount;c++)
	{
		if(LaGrille->Cells[c][row].IsEmpty() )continue;
		LabelModifie->Visible=true;
		for(r=row+1;r<rMax;r++)
		{
			if(RepPossible(c,r)==false) continue;

			LaGrille->Cells[c][r]=LaGrille->Cells[c][row];
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RecopBasPerenne(void)
{
	int row,r;
	int col;
	row=LaGrille->Row;
	for(r=row+1;r<LaGrille->RowCount;r++)
	{
		if(LaGrille->Cells[2][r]=="")break;
		for(col=2;col<LaGrille->ColCount;col++)
		{
			if(RepPossible(col,r)==false) continue;
			LaGrille->Cells[col][r]=LaGrille->Cells[col][row];
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RepBasTvaImmo(int col,int row)
{
	int r;
	CL_Immo *immo1,*immo2;
//AnsiString as;
	immo1=(CL_Immo*)LaGrille->Objects[0][row];
	for(r=row+1;r<LaGrille->RowCount-2;r++)
	{
		//as=LaGrille->Cells[col][r];
		//if(as.Length()>1 && ChBRepTout->Checked==false) continue;

		if(RepPossible(col,r)==false ) continue;

		immo2=(CL_Immo*)LaGrille->Objects[0][r];
		immo2->Tva=immo1->Tva;
		LaGrille->Cells[col][r]=LaGrille->Cells[col][row];
		//LabelModifie->Visible=true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RepBasTvaPetit(int col,int row)
{
	int r;
	CL_Petit *petit1,*petit2;
	AnsiString as;
	petit1=(CL_Petit*)LaGrille->Objects[0][row];
	for(r=row+1;r<LaGrille->RowCount;r++)
	{
		//as=LaGrille->Cells[col][r];
		//if(as.Length()>1 && ChBRepTout->Checked==false) continue;
		if(RepPossible(col,r)==false) continue;

		petit2=(CL_Petit*)LaGrille->Objects[0][r];
		petit2->Tva=petit1->Tva;
		LaGrille->Cells[col][r]=LaGrille->Cells[col][row];
		//LabelModifie->Visible=true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RepBasPetit(void)
{
	int r;
	int colVal=3;
	CL_Petit *petit1,*petit2;
	AnsiString as;
	int row=LaGrille->Row;
	int col=LaGrille->Col;
	if(col!=colVal) return;

	petit1=(CL_Petit*)LaGrille->Objects[0][row];
	for(r=row+1;r<LaGrille->RowCount;r++)
	{
		//as=LaGrille->Cells[col][r];
		//if(as.Length()>1 && ChBRepTout->Checked==false) continue;
		if(RepPossible(col,r)==false) continue;

		petit2=(CL_Petit*)LaGrille->Objects[0][r];
		petit2->ValAchat=petit1->ValAchat;
		LaGrille->Cells[col][r]=LaGrille->Cells[col][row];
		//LabelModifie->Visible=true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::RepBasCol(int colQ)
{
	int r;
//int colVal=3;
//CL_Petit *petit1,*petit2;
	AnsiString as;
	int row=LaGrille->Row;
	int col=LaGrille->Col;
	if(col<colQ) return;

	for(r=row+1;r<LaGrille->RowCount;r++)
	{
		if(LaGrille->Objects[0][r]==NULL)continue;
		if(RepPossible(col,r)==false) continue;
		LaGrille->Cells[col][r]=LaGrille->Cells[col][row];
		LabelModifie->Visible=true;
	}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::MemoKeyDown(TObject *Sender, WORD &Key,
		TShiftState Shift)
{
	//pour obliger DeniereCell cf Forme00 à passer dans ControleCellFormule
	if(Key==13)//Enter
	ControleCellFormule(Grille0->Col,Grille0->Row);
	ValueAvant="modifié";
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
void __fastcall TAgriSaisieFrm::MemoDblClick(TObject *Sender)
{
	ControleCellFormule(Grille0->Col,Grille0->Row);
//	ValueAvant="modifié";
	ValueAvant=LaGrille->Cells[Grille0->Col][Grille0->Row];
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
/*
 L_ErrPasImmo=         "Pas d'Immobilisation à reporter";
 L_ErrRepImpo=         "Report impossible dans cette colonne";
 L_ErrIntCal=          "Le montant des interets est calculé !!";

 */
