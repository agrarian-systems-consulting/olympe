#include <vcl.h>
#include <stdio.h>

#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"
#include "Erreur.h"

#pragma hdrstop

#include "Atelier.h"

extern CL_ES *ES;
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//VERIFICATION
//----------------------------------------------------------------------------
// verif des grilles
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
bool __fastcall TAtelierFrm::VerifLesGrilles(void)
{
	int g;
	bool correct;
	correct=true;
	for(g=0;g<GrilleX;g++)
	{
		LaGrille=LesGrilles[g];
		switch(LaGrille->Tag)
		{
			case GProduit:
			case GCharge:
			case GChProp:
			case GPiedHa: //270307
			case GExter:
			case GTravail: correct=VerifGrille();break;// verif et stock
			case GAvance: correct=true; break;// on ne saisit que du numérique
			case GPImmo: correct=VerifProdImmo();break;
			case GValInv: correct=true;
		}
	}
	return correct;
}
//----------------------------------------------------------------------------
bool __fastcall TAtelierFrm::VerifLaGrille(void)
{
	bool correct;
	correct=true;
	switch(LaGrille->Tag)
	{
		case GProduit:
		case GCharge:
		case GChProp:
		case GExter:
		case GProdPied: //280307
		case GChPied:
		case GTravail: correct=VerifGrille();break;// verif et stock
		case GAvance: correct=true; break;// on ne saisit que du numérique
		case GPImmo: correct=VerifProdImmo();break;
		case GValInv: correct=true;
		case GPiedHa: correct=true;
	}
	return correct;
}
//----------------------------------------------------------------------------
bool __fastcall TAtelierFrm::VerifGrille(void)
{
	int row,g;
	bool correct=true,rep;
	char buf[100];

	g=LaGrille->Tag;
	rep=ControleCell(ColM[g],RowM[g]);
	if(rep==false)
	{
		correct=false;
		sprintf(buf,L_ErrPasQant.c_str(),LaGrille->Name.c_str(),RowM[g]);
		//sprintf(buf,"%s ligne n°:%2d Pas de Quantité",LaGrille->Name.c_str(),RowM[g]);
		ErreurFrm->Edit->Lines->Add(buf);
	}
	if(LaGrille==GrilleTravail)
	{
		if(BesTrav==NULL) return true;

		BesTrav->lireGrille(GrilleTravail);
		if(Atelier->V_BesTrav->trouve(BesTrav->No)==NULL)
		Atelier->V_BesTrav->insSans(BesTrav);
		return true;
	}
	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		if(LaGrille->Cells[2][row].IsEmpty())
		{
			correct=false;
			sprintf(buf,L_ErrPasNom.c_str(),LaGrille->Name.c_str(),row);
			//sprintf(buf,"%s ligne n°:%2d Pas de NOM ",LaGrille->Name.c_str(),row);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		else if(LaGrille==GrilleChargeVolume)
		{
			if( LaGrille->Cells[2][row].IsEmpty()==false //produit
					&& LaGrille->Cells[3][row].IsEmpty()==false// charge prop
					&& IlYaQuantite(row)==false)
			{
				correct=false;
				sprintf(buf,L_ErrPasQant.c_str(),LaGrille->Name.c_str(),row);
				ErreurFrm->Edit->Lines->Add(buf);
			}
		}

	}
	return correct;
}
//-----------------------------------------------------------------------------
bool __fastcall TAtelierFrm::IlYaQuantite(int row)
{
	int colQ=5;
	for(int c=colQ;c<LaGrille->ColCount;c++)
	{
		if(LaGrille->Cells[c][row].IsEmpty()==false)
		return true;
	}
	return false;
}
//----------------------------------------------------------------------------
// retourne correct=true/false
// soit rien  DurAmor=0  DebAmor=0
// soit valeurs correctes
//----------------------------------------------------------------------------
bool __fastcall TAtelierFrm::VerifProdImmo(void)
{
	int debAmor,durAmor;
	int c,r;
	AnsiString s;
	bool correct=true;
	bool ilYaDonnee=false;
	// si rien dans la grille ok
	// sinon verifier que debut et durée d'amortissement sont informés
	for(r=1;r<3;r++)
	{
		for(c=1;c<LaGrille->ColCount;c++)
		{
			s=LaGrille->Cells[c][r].Trim();
			if(s.IsEmpty()==false) {ilYaDonnee=true;c=LaGrille->ColCount;r=3;}
		}
	}
	if(ilYaDonnee==false) return true;

	debAmor=EdDebAmor->Text.ToIntDef(-999);
	if(debAmor==-999)
	{
		ErreurFrm->Edit->Lines->Add(L_ProdImmo);
		ErreurFrm->Edit->Lines->Add(L_ErrPasDebAmor);
		//ErreurFrm->Edit->Lines->Add("Production d'Immo");
		//ErreurFrm->Edit->Lines->Add("pas de DEBUT d'amortissement");
		correct=false;
	}
	durAmor=EdDurAmor->Text.ToIntDef(-999);
	if(durAmor==-999||durAmor==0)
	{
		ErreurFrm->Edit->Lines->Add(L_ProdImmo);
		ErreurFrm->Edit->Lines->Add(L_ErrPasDurAmor);
		//ErreurFrm->Edit->Lines->Add("Production d'Immo");
		//ErreurFrm->Edit->Lines->Add("pas de DUREE d'amortissement");
		correct=false;
	}
	if(correct==true)
	{
		Atelier->DurAmor=durAmor;
		Atelier->DebAmor=debAmor;
	}
	return correct;

}
//***************************************************************************
// CONTROLE
//ControleCell est appelé par Grille0Click cf Forme00
//---------------------------------------------------------------------------
bool __fastcall TAtelierFrm::ControleCell(int col,int row)
{
	bool rep;
	//Si on ne saisit que du numérique
	if(LaGrille==GrilleAvance) return true;
	if(LaGrille==GrilleProdImmo) return true;
	if(LaGrille==GrilleTravail) {TotaliseTravail(); return true;}
	if(LaGrille==GrilleValInv) return true;

	if(LaGrille==GrillePiedHa) return true;
	if(LaGrille==GrilleProdPied) return true;
	if(LaGrille==GrilleChPied) return true;

	if(LaGrille==GrilleChargeVolume)
	rep=ControleCellVolume(col,row);
	else
	rep=ControleCellItem(col,row);
	return rep;
}
//----------------------------------------------------------------------------
bool __fastcall TAtelierFrm::ControleCellItem(int col,int row)
{
	AnsiString value;
	AnsiString pasDeNom("??????");
	int colProduit=2;
	CL_ItemParAtelier *itemPA;
	if(RowVide(row)==true )return true;

	itemPA=(CL_ItemParAtelier *)LaGrille->Objects[0][row];
	if(itemPA==NULL)
	{
//!!        MessageBox(Handle,L_ErrPasProd.c_str(),L_Err.c_str(),MB_OK|MB_ICONEXCLAMATION);
//!!        Application->MessageBox("Pas de Produit","ERREUR",MB_OK|MB_ICONEXCLAMATION);
		MessageBox(Handle,"Pas de Produit","ERREUR",MB_OK|MB_ICONEXCLAMATION);
		return false;
	}
	if(col==colProduit)
	{
		if(LaGrille->Cells[colProduit][row].IsEmpty()==true)
		{
			Application->MessageBox(L_ErrPasProd.c_str(),L_Err.c_str(),MB_OK|MB_ICONEXCLAMATION);
			//Application->MessageBox("Pas de Produit","ERREUR",MB_OK|MB_ICONEXCLAMATION);
			ColM[LaGrille->Tag]=colProduit;
			RowM[LaGrille->Tag]=row;
			LaGrille->Cells[col][row]="";
			return false;
		}
		//pas de controle de numericité cf Grille0KeyPress
	}

	// nouveau ou modifié
	if(itemPA->Flag!='N')itemPA->Flag='M';
	return true;
}
//----------------------------------------------------------------------------
bool __fastcall TAtelierFrm::ControleCellVolume(int col,int row)
{
	AnsiString value;
	AnsiString pasDeNom("??????");
	CL_ItemParAtelier *itemPA;
	int colAppro=3;
	if(RowVide(row)==true )return true;

	itemPA=(CL_ItemParAtelier *)LaGrille->Objects[0][row];

	if(col>=5)
	{
		if( LaGrille->Cells[col][row].IsEmpty()==false
				&& LaGrille->Cells[colAppro][row].IsEmpty()==true)
		{
			Application->MessageBox(L_ErrPasProd.c_str(),L_Err.c_str(),MB_OK|MB_ICONEXCLAMATION);
			//Application->MessageBox("Pas de Produit","ERREUR",MB_OK|MB_ICONEXCLAMATION);
			ColM[LaGrille->Tag]=colAppro;
			RowM[LaGrille->Tag]=row;
			LaGrille->Cells[col][row]="";
			return false;
		}
		//pas de controle de numericité cf Grille0KeyPress
	}
	// nouveau ou modifié
	if(itemPA->Flag!='N')itemPA->Flag='M';
	return true;
}
//----------------------------------------------------------------------------
void __fastcall TAtelierFrm::TotaliseTravail(void)
{
	int row,col;
	float totCol,total,val;
	total=0;
	for(col=1;col<LaGrille->ColCount;col++)
	{
		totCol=0;
		for(row=1;row<LaGrille->RowCount-1;row++)
		{
			val=GrilleFloat(col,row);
			totCol+=val;
		}
		LaGrille->Cells[col][row]=Aff(totCol,2);
		total+=totCol;
	}
	EdTotalBesoins->Text=AnsiString(total);

}
// ne set plus !! ??
//----------------------------------------------------------------------------
void __fastcall TAtelierFrm::DesGrilles(void)
{
	int g=LaGrille->Tag;
	LaGrille=LesGrilles[0]; DeGrilleItem(Atelier->V_Produit);
	LaGrille=LesGrilles[1]; DeGrilleItem(Atelier->V_Charge);
	LaGrille=LesGrilles[2]; DeGrilleVolume(Atelier->V_ChargeVolume);
	LaGrille=LesGrilles[3]; DeGrilleItem(Atelier->V_Externalite);
	LaGrille=LesGrilles[4]; DeGrilleAvanceStock(Atelier->V_Avance);
	LaGrille=LesGrilles[5]; DeGrilleProdImmo();
	LaGrille=LesGrilles[7]; DeGrilleInvAni();
	//8 PiedHa    280307
	LaGrille=LesGrilles[9]; DeGrilleItem(Atelier->V_ProdPied);
	LaGrille=LesGrilles[10]; DeGrilleItem(Atelier->V_ChPied);

	LaGrille=LesGrilles[g];
}
//----------------------------------------------------------------------------
void __fastcall TAtelierFrm::DeLaGrille(void)
{
	switch(LaGrille->Tag)
	{
		case GProduit: DeGrilleItem(Atelier->V_Produit);break;
		case GCharge: DeGrilleItem(Atelier->V_Charge);break;
		case GChProp: DeGrilleVolume(Atelier->V_ChargeVolume);break;
		case GExter: DeGrilleItem(Atelier->V_Externalite);break;
		case GTravail: break;
		case GAvance: DeGrilleAvanceStock(Atelier->V_Avance);break;
		case GPImmo: DeGrilleProdImmo();break;
		case GValInv: DeGrilleInvAni();break;
		//290307
		case GPiedHa: DeGrillePiedHa(Atelier->PiedHa);break;
		case GProdPied: DeGrilleItem(Atelier->V_ProdPied);break;
		case GChPied: DeGrilleItem(Atelier->V_ChPied);break;
	}
}
//----------------------------------------------------------------------------

//---------------------------------------------------------------------------
// DeGrille  à item   produit charge irrigation
//------------------------------------------------------------------------------
void __fastcall TAtelierFrm::DeGrilleItem (CL_Vecteur<CL_ItemParAtelier> *vecteur)
{
	int row,n,c;
	CL_ItemParAtelier *itemPA;
	float *qtePhase;
	int colQ=5;
	int g;
	g=LaGrille->Tag;
	if(GrilleModif[g]==false) return;

	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;

		itemPA=(CL_ItemParAtelier *)LaGrille->Objects[0][row];

		switch(itemPA->Flag)
		{
			case 'O': //origine
//                break;
			case 'M'://modifié
			delete itemPA->QtePhase; itemPA->QtePhase=NULL;
			qtePhase =new float[Atelier->NbPhase];
			for(n=0,c=colQ;n<Atelier->NbPhase;n++,c++)
			{
				if(LaGrille->Cells[c][row].IsEmpty() )
				qtePhase[n]=0;
				else
				qtePhase[n]=GrilleFloat(c,row);
			}
			itemPA->QtePhase=qtePhase;
			itemPA->Flag='O';
			break;
			case 'N': //nouveau
			qtePhase =new float[Atelier->NbPhase];
			for(n=0,c=colQ;n<Atelier->NbPhase;n++,c++)
			{
				if(LaGrille->Cells[c][row].IsEmpty() )
				qtePhase[n]=0;
				else
				qtePhase[n]=GrilleFloat(c,row);
			}
			itemPA->QtePhase=qtePhase;
			vecteur->ins(itemPA);
			itemPA->Flag='O';

		}
	}

	if(vecteur->Nbelt==0) return;
	// supprimer les éléments de vecteur qui ne sont plus dans la grille
	for(int i=0;i<vecteur->Nbelt;i++)
	{
		itemPA=vecteur->Vecteur[i];
		if( itemPA->Flag=='S') {vecteur->sup(itemPA);i--;}
	}
}
//---------------------------------------------------------------------------
// DeGrille itemPA   charge prop au volume
//------------------------------------------------------------------------------
void __fastcall TAtelierFrm::DeGrilleVolume(CL_Vecteur<CL_ItemParAtelier> *vecteur)
{
	int row,n,c;
	AnsiString value;
	CL_ItemParAtelier *itemPA;
	float *qtePhase;
	int colQ=6;
	int g;

	g=LaGrille->Tag;
	if(GrilleModif[g]==false) return;

	for(row=1;row<LaGrille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;

		itemPA=(CL_ItemParAtelier *)LaGrille->Objects[0][row];

		switch(itemPA->Flag)
		{
			case 'O': //origine
//                break;
			case 'M'://modifié
			// le nb phase a pu changer
			delete itemPA->QtePhase; itemPA->QtePhase=NULL;
			qtePhase =new float[Atelier->NbPhase];
			for(n=0,c=colQ;n<Atelier->NbPhase;n++,c++)
			{
				if(LaGrille->Cells[c][row].IsEmpty() )
				qtePhase[n]=0;
				else
				qtePhase[n]=GrilleFloat(c,row);
			}
			itemPA->QtePhase=qtePhase;
			itemPA->Flag='O';
			break;
			case 'N': //nouveau
			qtePhase =new float[Atelier->NbPhase];
			for(n=0,c=colQ;n<Atelier->NbPhase;n++,c++)
			{
				if(LaGrille->Cells[c][row].IsEmpty() )
				qtePhase[n]=0;
				else
				qtePhase[n]=GrilleFloat(c,row);
			}
			itemPA->QtePhase=qtePhase;
			vecteur->ins(itemPA);
			itemPA->Flag='O';
		}
	}
	if(vecteur->Nbelt==0) return;
	// supprimer les éléments de vecteur qui ne sont plus dans la grille
	for(int i=0;i<vecteur->Nbelt;i++)
	{
		itemPA=vecteur->Vecteur[i];
		if( itemPA->Flag=='S') {vecteur->sup(itemPA);i--;}
	}
}
//------------------------------------------------------------------------------
// avance stock
//------------------------------------------------------------------------------
void __fastcall TAtelierFrm::DeGrilleAvanceStock(CL_Vecteur<CL_EEF> *vecteur)
{
	int g;
	int col,row;
	int r0;
	float val,val0;
	CL_EEF *eEF;
	g=LaGrille->Tag;
	if(GrilleModif[g]==false) return;

	vecteur->purge();
	for(col=1;col<LaGrille->ColCount; col++)
	{
		r0=1;
		val0= GrilleFloat(col,1);
		for(row=2;row<LaGrille->RowCount;row++)
		{
			val= GrilleFloat(col,row);
			if(val==val0) continue;

			if(val0==0) continue;

			eEF=new CL_EEF(col,r0,row-1,val0);
			vecteur->ins(eEF);
			r0=row;
			val0=val;
		}
		if(val0!=0)
		{
			eEF=new CL_EEF(col,r0,row-1,val0);
			vecteur->ins(eEF);
		}
	}
}
//------------------------------------------------------------------------------
// Production d'Immobilisation
//------------------------------------------------------------------------------
void __fastcall TAtelierFrm::DeGrilleProdImmo(void)
{
	int g;
	int col,row;
	int c;
	g=LaGrille->Tag;
	if(GrilleModif[g]==false) return;

	// entreprise
	row=1;
	if(RowVide(row)==true)
	{
		Atelier->PImmoExiste=false;
		if(Atelier->ProdImmo)
		{
			delete []Atelier->ProdImmo;
			Atelier->ProdImmo=NULL;
		}
	}
	else
	{
		Atelier->PImmoExiste=true;
		if(Atelier->ProdImmo)
		{
			delete []Atelier->ProdImmo;
		}
		Atelier->ProdImmo=new float[Atelier->NbPhase];
		for(col=1,c=0;col<LaGrille->ColCount;col++,c++)
		Atelier->ProdImmo[c]=GrilleFloat(col,row);

	}
	// famille
	row=2;
	if(RowVide(row)==true)
	{
		Atelier->PImmoFamExiste=false;
		if(Atelier->ProdImmoFam)
		{
			delete []Atelier->ProdImmoFam;
			Atelier->ProdImmoFam=NULL;
		}
	}
	else
	{
		Atelier->PImmoFamExiste=true;
		if(Atelier->ProdImmoFam)
		{
			delete []Atelier->ProdImmoFam;
		}
		Atelier->ProdImmoFam=new float[Atelier->NbPhase];
		for(col=1,c=0;col<LaGrille->ColCount;col++,c++)
		Atelier->ProdImmoFam[c]=GrilleFloat(col,row);

	}

}

//------------------------------------------------------------------------------
// Production d'Immobilisation
//------------------------------------------------------------------------------
void __fastcall TAtelierFrm::DeGrilleInvAni(void)
{
	int g;
	g=LaGrille->Tag;
	if(GrilleModif[g]==false) return;

	Atelier->ValInvRepro=GrilleFloat(1,0);
	Atelier->ValInvAutre=GrilleFloat(1,1);
}
//------------------------------------------------------------------------------
// PiedHa
//------------------------------------------------------------------------------
void __fastcall TAtelierFrm::DeGrillePiedHa(float *piedHa)
{
	int g;
	int col,row;
	int i;
	g=LaGrille->Tag;
	if(GrilleModif[g]==false) return;

	row=1;
	for(col=1,i=0;col<LaGrille->ColCount; col++,i++)
	{
		piedHa[i]= GrilleFloat(col,row);
	}
}

/*
 L_ErrPasQant=       "%s ligne n°:%2d Pas de Quantité";
 L_ErrPasNom=        "%s ligne n°:%2d Pas de NOM ";
 L_ProdImmo=         "Production d'Immo";
 L_ErrPasDebAmor=    "pas de DEBUT d'amortissement";
 L_ErrPasDurAmor=    "pas de DUREE d'amortissement":
 L_ErrPasProd=       "Pas de Produit";
 L_Err=              "ERREUR";

 */
