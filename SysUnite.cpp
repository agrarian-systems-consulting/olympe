//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"
#include "Brouillon.h"
#include "Erreur.h"
#include "ReClasse.h"
#include "QRGrille00.h"
#include "Main.h"
#include "CL_Trad.h"
#include "NoteAgri.h"

#include "Aide.h"
#include "SysUnite.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Forme00"    //
#pragma resource "*.dfm"

/* TODO : pret pour import d'excel */

TSysUniteFrm *SysUniteFrm;
// Les extern
extern CL_ES *ES;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TSysUniteFrm::TSysUniteFrm(TComponent* Owner) :
		TForme00Frm(Owner) //
{
}
//---------------------------------------------------------------------------
void __fastcall TSysUniteFrm::FormCreate(TObject *Sender)
{
//020507
	Notes="";
}
//---------------------------------------------------------------------------
void __fastcall TSysUniteFrm::FormActivate(TObject *Sender)
{
	int g;
	if(EstInitialise==false)
	{
		Personnaliser();
		DefinirLesGrilles();

		for(int g=0;g<GrilleX;g++)
		IniGrille(LesGrilles[g]); // nb col,row, non défilable

		CellDebut();
//	    for(int g=0;g<GrilleX;g++) GrilleModif[g]=false;
//	    for(int g=0;g<GrilleX;g++) VersGrille(LesGrilles[g]);

		AjoutRow= true;
		LabelModifie->Visible=false;

		LaGrille=LesGrilles[0];
		g=LaGrille->Tag;
		if(g>COLMAX)
		{
			ShowMessage("Forme00 g>ColMax");
		}
//	   	ValueAvant=LaGrille->Cells[ColM[g]][RowM[g]];
		EstInitialise=true;
		VideLesGrilles();
		AutreDonnee=true;
	}

	//    VideLesGrilles();  ???
	//    CellDebut();
	if(PClasst->Visible==true)
	{
		BtBnFermClasstClick(this);
		PClasst->Visible=false;
	}
	if(AutreDonnee==true) //defini par stocker
	{
		VideLesGrilles(); // 230202
//        for(g=0;g<GrilleX;g++) GrilleModif[g]=false;
		for(g=0;g<GrilleX;g++) VersGrille(LesGrilles[g]);
		CellDebut();
	}
//..........
//    ValueAvant=LaGrille->Cells[ColM[g]][RowM[g]];  //la grille est vide ->bug
}

//---------------------------------------------------------------------------/////// Boutons /////////////////////////////////////////////////////////////
/////// Boutons /////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------
//void __fastcall TSysUniteFrm::BtClasserClick(TObject *Sender)
//---------------------------------------------------------------------------
void __fastcall TSysUniteFrm::BtBnStockerClick(TObject *Sender)
{
	Stocker();
}
//---------------------------------------------------------------------------

// test sur item==NULL pour des effacements de données non complétement définies
//---------------------------------------------------------------------------
void __fastcall TSysUniteFrm::BtSupClick(TObject *Sender)
{
	int r=LaGrille->Row;
	CL_SystemeUnite* item;
	int rep;
	item=(CL_SystemeUnite*)LaGrille->Objects[0][r];
	if(item==NULL) return;
	SelLigne();
	if(item!= NULL && item->Supprimable==false)
	{
//    	ShowMessage(" UTILISE ");
		ShowMessage(T->L_Utilise);
		return;
	}
//	rep=MessageBox(Handle," Je supprime Vous êtes sur ?","SUPPRESSION",MB_YESNO);
	rep=MessageBox(Handle,T->L_SupQ.c_str(),T->L_SupT.c_str(),MB_YESNO);
	if(rep==IDYES)
	{
		if(item!=NULL) item->Flag='S';
		SupprimerLigne();
	}
	DeSelLigne();
}

//---------------------------------------------------------------------------
//VideNonUtilisés
//---------------------------------------------------------------------------
void __fastcall TSysUniteFrm::BtBnVideToutClick(TObject *Sender)
{
	int r;
	int rep;
	bool ilYaModif;
	CL_SystemeUnite* item;
//    rep=MessageBox(Handle,"j'efface tous les éléments INUTILISES ?","NETTOYER",MB_YESNO|MB_ICONQUESTION);
	rep=MessageBox(Handle,T->L_SupInutQ.c_str(),T->L_SupInutT.c_str(),MB_YESNO|MB_ICONQUESTION);
	if(rep==IDNO) return;

	ilYaModif=false;
	for(r=1;r<LaGrille->RowCount;r++)
	{
		item=(CL_SystemeUnite*)LaGrille->Objects[0][r];
		if(item==NULL) continue;

		if(item->Supprimable!=false) V_SystemeUnite->sup(item);
		ilYaModif=true;
	}
	if(ilYaModif==false) return;

	VideGrille(LaGrille);
	VersGrille(LaGrille);
	LabelModifie->Visible=true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
///////////// 1 ////////////////////////////////////////////////////////////
///////////// 1 ////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
// FONCTIONS A PERSONNALISER
//----------------------------------------------------------------------------
void __fastcall TSysUniteFrm::Personnaliser(void)
{
//pour l'impression
	TitreGrille=LabForme->Caption;
	strcpy(TypeCol,"00TTTNNT");
//    CBMonnaie->Enabled=false;

}
//---------------------------------------------------------------------------
void __fastcall TSysUniteFrm::DefinirLesGrilles(void)
{
	GrilleX=1;
	Grille0->Tag=0;
	LesGrilles[0]=Grille0;
	LaGrille=Grille0;
}
//-----------------------------------------------------------------------------
void __fastcall TSysUniteFrm::IniGrille(TStringGrid *grille)
{
	int l=0;
	int largeur[]= {20,10,64,64,64,64,64,64}; //150302
	int c;
//      2  unite UTILISATION
//      3        TRANSACTION
//      4        ratio T/U

	grille->ColCount=8;
	grille->FixedCols=2;
	grille->FixedRows=1;

//largeur première colonne            //largeur standard =64 pixels
	for(c=0;c<grille->ColCount;c++)
	{
		grille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	grille->Width=l+40; //place pour l'ascenseur

	// attention col row
	/*    grille->Cells[2][0]="1 Atelier";
	 grille->Cells[3][0]="2 Entreprise";
	 grille->Cells[4][0]="3 Région";
	 grille->Cells[5][0]="ratio 2/1";
	 grille->Cells[6][0]="ratio 3/2";
	 grille->Cells[7][0]="Monnaie";                 //150302
	 */
	grille->Cells[2][0]=L_Titre1;
	grille->Cells[3][0]=L_Titre2;
	grille->Cells[4][0]=L_Titre3;
	grille->Cells[5][0]=L_Titre4;
	grille->Cells[6][0]=L_Titre5;
	grille->Cells[7][0]=L_Titre6;
	AjoutRow=true;
	CellAVerifier=true;
}
//------------------------------------------------------------------------------
void __fastcall TSysUniteFrm::VersGrille(TStringGrid *grille)
{
	int row,r;
	AnsiString value;
	CL_SystemeUnite *sys;
	CL_Vecteur<CL_SystemeUnite> *vecteur;
	vecteur=V_SystemeUnite;
	grille->RowCount=vecteur->Nbelt+3;
	OrdreModif=false;
	for(r=0;r<vecteur->Nbelt;r++)
	{
		row=r+1;
		sys=vecteur->Vecteur[r];
		sys->Flag='O';
		grille->Objects[0][row]=(TObject*)sys;
		grille->Cells[0][row]=row;
		if(sys->Supprimable==false) grille->Cells[1][row]='*';
		grille->Cells[2][row]=sys->UUt;
		grille->Cells[3][row]=sys->UTrans;
		grille->Cells[4][row]=sys->UGlobal;
		grille->Cells[5][row]=Aff(sys->Ratio,3);
		grille->Cells[6][row]=Aff(sys->RatioG,3);
		if(sys==SysMonnaie)
		{
			grille->Cells[7][row]="  O";
			LabMonnaie->Caption=sys->UTrans;
		}
		else
		grille->Cells[7][row]="  N";
	}
//    IniCB();
	CellInitiale(2,1);
}
/*
 //---------------------------------------------------------------------------
 void __fastcall TSysUniteFrm::IniCB(void)
 {
 int i;
 CL_SystemeUnite *sysUnit;
 for(i=0;i<V_SystemeUnite->Nbelt;i++)
 {
 sysUnit=V_SystemeUnite->Vecteur[i];
 if(sysUnit->Monnaie=='o')sysUnit->Monnaie='O';
 if(sysUnit->Monnaie!='O') continue;

 }
 }
 */
//-----------------------------------------------------------------------------
//void  __fastcall TSysUniteFrm::CellDebut(void)
//cf Forme00
//---------------------------------------------------------------------------
//void  __fastcall TSysUniteFrm::SaisirCell(int col,int row)
//cf Forme00
///////////// 2 ////////////////////////////////////////////////////////////
///////////// 2 ////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
bool __fastcall TSysUniteFrm::ControleCell(int col,int row)
{
	int r;
	AnsiString value;
	AnsiString pasDeNom("??????");
	CL_SystemeUnite *sys;
	char car;
	if(RowVide(row)==true )return true;

	// nouveau ou modifié ?
	LabelModifie->Visible=true;
	sys=(CL_SystemeUnite*)LaGrille->Objects[0][row];
	if(sys==NULL)
	{
		sys=new CL_SystemeUnite();
		sys->Flag='N';
		LaGrille->Objects[0][row]=(TObject*)sys;
		LaGrille->Cells[0][row]=row;
	}
	else if(sys->Flag!='N')
	sys->Flag='M';
	if(col==7)
	{
		car=GrilleCar(7,row);
		if(car=='O' ||car=='o')
		{
			if(SysMonnaie && sys!=SysMonnaie && V_Produit->Nbelt!=0)
			{
//                ShowMessage("Impossible de changer de monnaie/n Provisoirement");
				ShowMessage(L_ImpoChg_monnaie);
			}
			else
			{
				SysMonnaie=sys;
				LabMonnaie->Caption=SysMonnaie->UTrans;
				for(r=1;r<LaGrille->RowCount;r++)
				if(LaGrille->Cells[7][r]!="")LaGrille->Cells[7][r]="  N";
				LaGrille->Cells[7][row]="  O";
			}
		}
	}
	return true;
}
//------------------------------------------------------------------------------
void __fastcall TSysUniteFrm::DeGrille(TStringGrid *grille)
{
	int row,r;
	CL_SystemeUnite *sys;
	CL_Vecteur<CL_SystemeUnite> *vecteur;
//char chaine[100];

	vecteur=V_SystemeUnite;
	LaGrille=grille;
	for(row=1;row<grille->RowCount;row++)
	{
		if(RowVide(row)==true) continue;
		sys=(CL_SystemeUnite*)grille->Objects[0][row];
		if(sys==NULL) continue;
		switch(sys->Flag)
		{
			//case 'O':                                    //origine
			//    break;
			case 'N'://nouveau
			vecteur->ins(sys);
//                break;
			case 'O'://origine
			case 'M'://modifie
			sys->UUt =GrilleChaine(2,row);//grille->Cells[2][row];
			sys->UTrans =GrilleChaine(3,row);//grille->Cells[3][row];
			sys->UGlobal=GrilleChaine(4,row);//grille->Cells[4][row];
			sys->Ratio =GrilleFloat(5,row);
			sys->RatioG =GrilleFloat(6,row);
			sys->Monnaie=GrilleCar(7,row);
			if(sys->Monnaie=='O')
			{
				if(SysMonnaie && sys!=SysMonnaie && V_Produit->Nbelt!=0)
				{
					LaGrille->Cells[7][row]="  N";
					ShowMessage(L_ImpoChg_monnaie);
					//ShowMessage("Impossible de changer de monnaie\n Provisoirement !");
				}
				else
				{
					for(r=1;r<grille->RowCount;r++)LaGrille->Cells[7][r]="  N";
					LaGrille->Cells[7][row]="  O";
					SysMonnaie=sys;
					LabMonnaie->Caption=SysMonnaie->UTrans;
				}
			}
			break;
		}
		sys->Flag='O';
	}
	for(int i=0;i<vecteur->Nbelt;i++)
	{
		sys=vecteur->Vecteur[i];
		if(sys->Flag=='S') {vecteur->sup(sys);i--;}
	}
}
//---------------------------------------------------------------------------
// verif et Stocke
//---------------------------------------------------------------------------
bool __fastcall TSysUniteFrm::Stocker(void)
{
	bool correct=true;
	char buf[100];
	float ratio;
	AnsiString UUt,UTrans,UGlobal;
	char car;
	int nbSysMonnaie=0;

	ErreurFrm->Edit->Clear();

	DerniereCell();
	if(LabelModifie->Visible==false)

	if(LabelModifie->Visible==false) return true;

	for(int r=1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		if(CellVide(2,r))
		{
			correct=false;
//            wsprintf(buf,"Pas d'Unité Atelier ligne %d ",r);
			wsprintf(buf,L_PasUniteAtelier.c_str(),r);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		if(CellVide(3,r))
		{
			correct=false;
//            wsprintf(buf,"Pas d'Unité Entreprise ligne %d ",r);
			wsprintf(buf,L_PasUniteEntreprise.c_str(),r);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		if(CellVide(4,r))
		{
			correct=false;
//            wsprintf(buf,"Pas d'Unité Régionligne %d ",r);
			wsprintf(buf,L_Pas_UniteRegion.c_str(),r);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		if(CellVide(5,r))
		{
			correct=false;
//            wsprintf(buf,"Pas de Ratio 2/1 ligne %d " ,r);
			wsprintf(buf,L_PasRatio21.c_str() ,r);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		else
		{
			ratio =GrilleFloat(5,r);
			if(ratio==0)
			{
				correct=false;
				wsprintf(buf,L_Ratio21Nul.c_str() ,r);
//                wsprintf(buf,"Ratio 2/1 =0 !!ligne %d " ,r);
				ErreurFrm->Edit->Lines->Add(buf);
			}
		}

		if(CellVide(6,r))
		{
			correct=false;
			wsprintf(buf,L_Ratio31Nul.c_str() ,r);
			//wsprintf(buf,"Pas de Ratio 3/2 ligne %d " ,r);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		else
		{
			ratio =GrilleFloat(6,r);
			if(ratio==0)
			{
				correct=false;
				wsprintf(buf,L_Ratio31Nul.c_str() ,r);
//                wsprintf(buf,"Ratio 3/2 =0 !!ligne %d " ,r);
				ErreurFrm->Edit->Lines->Add(buf);
			}
		}
		car=GrilleCar(7,r);
		if(car=='O' ||car=='o')
		{
			LaGrille->Cells[7][r]="  O";
			nbSysMonnaie++;
		}
		else LaGrille->Cells[7][r]="  N";
		UUt =GrilleChaine(2,r);
		UTrans =GrilleChaine(3,r);
		UGlobal=GrilleChaine(4,r);
		if(UUt==UTrans && GrilleFloat(5,r)!=1)
		{
			wsprintf(buf,L_ErrRatio21.c_str(),r);
			wsprintf(buf," ligne %d le ratio 2/1 n'est pas égal à 1",r);
			ErreurFrm->Edit->Lines->Add(buf);
			correct=false;
		}
		if(UTrans==UGlobal && GrilleFloat(6,r)!=1)
		{
			wsprintf(buf,L_ErrRatio31.c_str(),r);
			wsprintf(buf," ligne %d le ratio 3/2 n'est pas égal à 1",r);
			ErreurFrm->Edit->Lines->Add(buf);
			correct=false;
		}
	}
	if(nbSysMonnaie==0)
	{
		wsprintf(buf,L_PasMonnaie.c_str());
//        wsprintf(buf,"Pas d'Unité Monétaire");
		ErreurFrm->Edit->Lines->Add(buf);
		correct=false;
	}
	if(nbSysMonnaie>1)
	{
		wsprintf(buf,L_PlusMonnaie.c_str());
//        wsprintf(buf,"Une seule Unité Monétaire possible !");
		ErreurFrm->Edit->Lines->Add(buf);
		correct=false;
	}

//.......................
	if(correct==false)
	{
		ErreurFrm->Show();
		return false;
	}
	else
	{
		DeGrille(LaGrille);
		if(OrdreModif==true) StockerOrdre(V_SystemeUnite);
		ES->ecrireFichier();
		LabelModifie->Visible=false;
		return true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSysUniteFrm:: StockerOrdre(CL_Vecteur<CL_SystemeUnite> *vecteur)
{
	int i,r;
	i=0;
	for(r=1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		vecteur->Vecteur[i]=(CL_SystemeUnite*)LaGrille->Objects[0][r];
		i++;
	}
	OrdreModif=false;
}
//---------------------------------------------------------------------------
void __fastcall TSysUniteFrm::BtReportDroitClick(TObject *Sender)
{
	int r=LaGrille->Row;
	int c=LaGrille->Col;
	if(LaGrille->Cells[2][r].IsEmpty()==true) return;
	switch(c)
	{
		case 2:
		if(RepPossible(3,r)==true)
		{
			LaGrille->Cells[3][r]=LaGrille->Cells[2][r];
			LaGrille->Cells[5][r]=1;
		}
		if(RepPossible(4,r)==true)
		{
			LaGrille->Cells[4][r]=LaGrille->Cells[2][r];
			LaGrille->Cells[6][r]=1;
		}
		break;
		case 3:
		if(RepPossible(4,r)==true)
		{
			LaGrille->Cells[4][r]=LaGrille->Cells[3][r];
			LaGrille->Cells[6][r]=1;
		}
		break;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TSysUniteFrm::RepPossible(int c,int r)
{
	AnsiString as;
	as=LaGrille->Cells[c][r];
	if(as.Length()>1 && ChBRepTout->Checked==false) return false;

	LabelModifie->Visible=true;
	return true;
}
//---------------------------------------------------------------------------
//A REVOIR

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TSysUniteFrm::tri(void)
{
	int i,j,n;
	int iMin;
	CL_SystemeUnite *sys,*sysMin,*sysJ;
	int r;
	n=LaGrille->RowCount;
	//commencer à ligne n° 2   la 1 c'est l'unité monétaire
	//il y 2 lignes blanches en bas
	//pas intéressant es unités classiques ha q ..se retouvent éparpillées
	for(i=2;i<n-4;i++)
	{
		iMin=i;
		sysMin=(CL_SystemeUnite*)LaGrille->Objects[0][i];
		if(sysMin==NULL) continue;
		for(j=i+1;j<n;j++)
		{
			sysJ=(CL_SystemeUnite*)LaGrille->Objects[0][j];
			if(sysJ==NULL) continue;

			if(sysMin->UUt.AnsiCompareIC(sysJ->UUt)>0)
			{
				sysMin=sysJ;
				iMin=j;
			}
		}
		sys=(CL_SystemeUnite*)LaGrille->Objects[0][iMin];
		LaGrille->Objects[0][iMin]=LaGrille->Objects[0][i];
		LaGrille->Objects[0][i]=(TObject*)sys;
	}
	for(r=1;r<LaGrille->RowCount;r++)
	{
		sys=(CL_SystemeUnite*)LaGrille->Objects[0][r];
		if(sys==NULL) continue;
		LaGrille->Cells[2][r]=sys->UUt;
		LaGrille->Cells[3][r]=sys->UTrans;
		LaGrille->Cells[4][r]=sys->UGlobal;
		LaGrille->Cells[5][r]=Aff(sys->Ratio,3);
		LaGrille->Cells[6][r]=Aff(sys->RatioG,3);
	}
}
/*
 //---------------------------------------------------------------------------
 int TSysUniteFrm::compSysUnite(const void *s1,const void *s2)
 {
 CL_SystemeUnite *sys1=(CL_SystemeUnite *)s1;
 CL_SystemeUnite *sys2=(CL_SystemeUnite *)s2;

 return (sys1->UUt.AnsiCompareIC(sys2->UUt)<0)
 }
 */
//---------------------------------------------------------------------------
void TSysUniteFrm::TexteChaine(void) {
	L_Titre1 = T->TrouveTexte("SysUniteFrm", "L_Titre1");
	L_Titre2 = T->TrouveTexte("SysUniteFrm", "L_Titre2");
	L_Titre3 = T->TrouveTexte("SysUniteFrm", "L_Titre3");
	L_Titre4 = T->TrouveTexte("SysUniteFrm", "L_Titre4");
	L_Titre5 = T->TrouveTexte("SysUniteFrm", "L_Titre5");
	L_Titre6 = T->TrouveTexte("SysUniteFrm", "L_Titre6");
	L_ImpoChg_monnaie = T->TrouveTexte("SysUniteFrm", "L_ImpoChg_monnaie");

	L_PasUniteAtelier = T->TrouveTexte("SysUniteFrm", "L_PasUniteAtelier");
	L_PasUniteEntreprise = T->TrouveTexte("SysUniteFrm",
			"L_PasUniteEntreprise");
	L_Pas_UniteRegion = T->TrouveTexte("SysUniteFrm", "L_Pas_UniteRegion");
	L_PasRatio21 = T->TrouveTexte("SysUniteFrm", "L_PasRatio21");
	L_Ratio21Nul = T->TrouveTexte("SysUniteFrm", "L_Ratio21Nul");
	L_PasRatio31 = T->TrouveTexte("SysUniteFrm", "L_PasRatio31");
	L_Ratio31Nul = T->TrouveTexte("SysUniteFrm", "L_Ratio31Nul");
	L_ErrRatio21 = T->TrouveTexte("SysUniteFrm", "L_ErrRatio21");
	L_ErrRatio31 = T->TrouveTexte("SysUniteFrm", "L_ErrRatio31");
	L_PasMonnaie = T->TrouveTexte("SysUniteFrm", "L_PasMonnaie");
	L_PlusMonnaie = T->TrouveTexte("SysUniteFrm", "L_PlusMonnaie");
}
/*
 L_Titre1="1 Atelier";
 L_Titre2="2 Entreprise";
 L_Titre3="3 Région";
 L_Titre4="ratio 2/1";
 L_Titre5="ratio 3/2";
 L_Titre6="Monnaie";
 L_ImpoChg_monnaie="Impossible de changer de monnaie/n Provisoirement";

 L_PasUniteAtelier=    "Pas d'Unité Atelier ligne %d ";
 L_PasUniteEntreprise= "Pas d'Unité Entreprise ligne %d ";
 L_Pas_UniteRegion=    "Pas d'Unité Région ligne %d ";
 L_PasRatio21=         "Pas de Ratio 2/1 ligne %d ";
 L_Ratio21Nul=         "Ratio 2/1 =0 !!ligne %d ";
 L_PasRatio31=         "Pas de Ratio 3/2 ligne %d ";
 L_Ratio31Nul=         "Ratio 3/2 =0 !!ligne %d ";
 L_ErrRatio21=         " ligne %d le ratio 2/1 n'est pas égal à 1";
 L_ErrRatio31=         " ligne %d le ratio 3/2 n'est pas égal à 1" ;
 L_PasMonnaie=         "Pas d'Unité Monétaire";
 L_PlusMonnaie=        "Une seule Unité Monétaire possible !";
 }
 //---------------------------------------------------------------------------
 void TSysUniteFrm::Anglais(void)
 {
 //    L_Utilise="USED";
 //    L_SupMBQ=" I delete, Are you sure?";
 //    L_SupMBT="DELETE";
 //    L_SupInutMBQ="I delete all UNUSED items?";
 //    L_SupInutMBT="CLEAR";

 L_Titre1="1 Activity";
 L_Titre2="2 Farm";
 L_Titre3="3 Region";
 L_Titre4="ratio 2/1";
 L_Titre5="ratio 3/2";
 L_Titre6="Currency";

 L_ImpoChg_monnaie=    "Unable to change the currency/n Temporarily";
 L_PasUniteAtelier=    "No Unit Activity at line %d ";
 L_PasUniteEntreprise= "No Unit Farm at line %d ";
 L_Pas_UniteRegion=    "No Unit Region at line %d ";
 L_PasRatio21=         "No Ratio 2/1 at line %d ";
 L_Ratio21Nul=         "Ratio 2/1 =0 at line %d ";
 L_PasRatio31=         "No Ratio 2/1 at line %d ";
 L_Ratio31Nul=         "Ratio 2/1 =0 at line %d ";
 L_ErrRatio21=         "line %d : the ratio 2/1 is different from 1";
 L_ErrRatio31=         "line %d : the ratio 3/2 is different from 1" ;
 L_PasMonnaie=         "No Currency Unit";
 L_PlusMonnaie=        "Only One currency Unit allowed !";
 }
 //---------------------------------------------------------------------------
 */

//--------------------------------------------
void TSysUniteFrm::IniCaption(void) {
	LabMonnaie->Caption = LC_LabMonnaie;
	GBMonnaie->Caption = LC_GBMonnaie;
	SysUniteFrm->Caption = LC_SysUniteFrm;
	LabForme->Caption = T->LC_LBSysUnitFrm;
	ChBRepTout->Caption = T->LC_ChBRepTout;
	BtClasser->Caption = T->LC_BtClasser;
}
//--------------------------------------------
void TSysUniteFrm::TexteCaption(void) {
	LC_LabMonnaie = T->TrouveCaption("SysUnite", "LC_LabMonnaie");
	LC_GBMonnaie = T->TrouveCaption("SysUnite", "LC_GBMonnaie");
	LC_SysUniteFrm = T->TrouveCaption("SysUnite", "LC_SysUniteFrm");
	LC_LBSysUnitFrm = T->TrouveCaption("CL_Trad", "LC_LBSysUnitFrm");
//       LC_ChBRepTout=T->TrouveCaption("CL_Trad" ,"LC_ChBRepTout");//070206
	IniCaption();

}
//--------------------------------------------

void __fastcall TSysUniteFrm::BtBnNotesClick(TObject *Sender)
{
//
	NoteAgriFrm->VientDe="SysUnite";//ne pas traduire
	NoteAgriFrm->Memo->Text=Notes;
	NoteAgriFrm->Caption=Caption;

	NoteAgriFrm->Show();

}
//---------------------------------------------------------------------------

bool __fastcall TSysUniteFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp = false;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

