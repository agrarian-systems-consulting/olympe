//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"
#include "QRGrille00.h"

#include "Erreur.h"
#include "CL_Matrice.h"
#include "CL_Trad.h"
#include "NoteAgri.h"
#include "Aide.h"

#include "DefCalendrier.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DefItem"
#pragma resource "*.dfm"
TDefCalendrierFrm *DefCalendrierFrm;
extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TDefCalendrierFrm::TDefCalendrierFrm(TComponent* Owner) :
		TDefItemFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TDefCalendrierFrm::Personnaliser(void)
{
	LabCatVar->Caption=Calendrier->Nom;
	BtBnTva->Visible=false;
	BtBnUnite->Visible=false;
	BtBnVideTout->Visible=true; //310306

//    strcpy(TypeCol,"00000NNNNN");
	strcpy(TypeCol,"00TNNNNNNN");//230804
	ColNom=2;
}
//---------------------------------------------------------------------------
//IniGrille
//---------------------------------------------------------------------------
void __fastcall TDefCalendrierFrm::IniGrille(TStringGrid *grille)
{
//               0  1   2  3  4  5  6  7  8  9
	int largeur[]= {20,10,128,64,64,64,64,64,64,64};
	int c;
	int nbCol;

	nbCol=10;
	grille->Cells[0][0]=".";
	grille->Cells[1][0]=".";
	grille->Cells[2][0]=L_Periode; //="Période";
	grille->Cells[3][0]=L_Debut;//="Debut inclus";
	grille->Cells[4][0]=L_Fin;//"Fin   exclus";
	grille->Cells[5][0]=L_HJ;//="  h/j";
	grille->Cells[6][0]=L_Dispo;//=" %Dispo";
	grille->Cells[7][0]=L_Jours;//=" Jours";
	grille->Cells[8][0]=L_JDispo;//=" Jours Dispo";
	grille->Cells[9][0]=L_HDispo;//=" Heures Dispo";

	grille->ColCount=nbCol;
	grille->Width=0;
	for(c=0;c<nbCol;c++)
	{
		grille->ColWidths[c]=largeur[c];
		grille->Width+=largeur[c];
	}
	grille->Width+=30; //place pour l'ascenseur
	grille->FixedCols=2;
	grille->FixedRows=1;
	AjoutRow=true;
}
//---------------------------------------------------------------------------
//VersGrille
//---------------------------------------------------------------------------
void __fastcall TDefCalendrierFrm::VersGrille(TStringGrid *grille)
{
	int row,r;
	AnsiString value;
	CL_Periode *periode;
	int nLigne=0;
	CL_Vecteur<CL_Periode> *vPeriode;
	vPeriode=Calendrier->V_Periode;
	// nb ligne de la grille
	for( r=0;r<vPeriode->Nbelt;r++)
	{
		periode=vPeriode->Vecteur[r];
		nLigne++;
	}
	grille->RowCount=nLigne+3;
	LaGrille=grille;
	row=1;
	for( r=0;r<vPeriode->Nbelt;r++)
	{
		periode=vPeriode->Vecteur[r];
		periode->Flag='O';
		grille->Objects[0][row]=(TObject*)periode;

		grille->Cells[0][row]=row;
		if(periode->Supprimable==false) grille->Cells[1][row]='*';
		LaGrille->Cells[2][row]=periode->Nom;
		LaGrille->Cells[3][row]=AffJourMois(periode->JDeb,periode->MDeb);
		LaGrille->Cells[4][row]=AffJourMois(periode->JFin,periode->MFin);
		LaGrille->Cells[5][row]=Aff(periode->HpJ,2);
		LaGrille->Cells[6][row]=Aff(periode->PcentDispo);
		LaGrille->Cells[7][row]=Aff(periode->Duree);
		LaGrille->Cells[8][row]=Aff(periode->JDispo,0);
		LaGrille->Cells[9][row]=Aff(periode->HDispo,0);
		row++;
	}
	CellInitiale(2,1);
}

//---------------------------------------------------------------------------
// ControleCell appelé par Grill0Click cf Forme00
//---------------------------------------------------------------------------
bool __fastcall TDefCalendrierFrm::ControleCell(int col,int row)
{
	AnsiString pasDeNom("??????");
	CL_Periode* periode;
	char chaine[100];
	bool rep;
	if(RowVide(row)==true )return true;

	periode=(CL_Periode*)LaGrille->Objects[0][row];
	if(periode==NULL)
	{
		periode=new CL_Periode();
		periode->Flag='N';
		periode->Supprimable=true;
		LaGrille->Objects[0][row]=(TObject*)periode;
		LaGrille->Cells[0][row]=row;
		GrilleModif[LaGrille->Tag]=true;
	}
	else if(periode->Flag!='N')
	periode->Flag='M';

	switch(col)
	{
		case 2:
		if(LaGrille->Cells[2][row].IsEmpty()
				||pasDeNom.AnsiCompare(LaGrille->Cells[2][row])==0)
		{
			sprintf(chaine,L_PasNom.c_str(),LaGrille->Name.c_str(),row);
			//sprintf(chaine," %s row=%d Pas de nom",LaGrille->Name.c_str(),row);
			ShowMessage(chaine);
			LaGrille->Row=row;
			LaGrille->Col=2;
			LaGrille->Cells[2][row]=pasDeNom;
			return false;
		}
		else if(Doublon(LaGrille,2,row)==true) return false;
		periode->Nom=LaGrille->Cells[2][row];
		break;
		case 3:
		GrilleJourMois(3,row,periode->JDeb,periode->MDeb);
		CompleteGrille(periode,row);
		break;
		case 4:
		rep=GrilleJourMois(4,row,periode->JFin,periode->MFin);
		if(rep==false) return false;
		CompleteGrille(periode,row);
		break;
		case 5: //h/j
		ReAffFloat(col,row,2);
		periode->HpJ=GrilleFloat(col,row);
		CompleteGrille(periode,row);
		break;
		case 6://%Dispo
		ReAffFloat(col,row,0);
		periode->PcentDispo=GrilleFloat(col,row);
		periode->JDispo=periode->Duree*periode->PcentDispo/100.;
		LaGrille->Cells[8][row]=Aff(periode->JDispo);
		//if(periode->PcentDispo==0) return;
		periode->JDispo=periode->Duree*periode->PcentDispo/100.;
		LaGrille->Cells[8][row]=Aff(periode->JDispo);
		periode->HDispo=periode->JDispo*periode->HpJ;
		LaGrille->Cells[9][row]=Aff(periode->HDispo);
		//CompleteGrille(periode,row);
		break;
		case 8://JDispo
		ReAffFloat(col,row,0);
		periode->JDispo=GrilleFloat(col,row);
		periode->PcentDispo=periode->JDispo/periode->Duree*100.;
		LaGrille->Cells[6][row]=Aff(periode->PcentDispo);
		if(periode->PcentDispo>=100)
		{
			ShowMessage(L_Plus100);
			//ShowMessage("Plus de 100% disponible");
		}
		else
		{
			periode->HDispo=periode->JDispo*periode->HpJ;
			LaGrille->Cells[9][row]=Aff(periode->HDispo);
		}
		break;
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TDefCalendrierFrm::CompleteGrille(CL_Periode *periode,int row)
{
	/*
	 if(DureePeriode(periode)==false)return;
	 LaGrille->Cells[7][row]=Aff(periode->Duree);
	 */
	if(periode->CalculDuree()==false)return;
	LaGrille->Cells[7][row]=Aff(periode->Duree);
	periode->CalculDispo();

	if(periode->PcentDispo==0) return;
//    periode->JDispo=periode->Duree*periode->PcentDispo/100.;
	LaGrille->Cells[8][row]=Aff(periode->JDispo);

	if(periode->HpJ==0) return;
//    periode->HDispo=periode->JDispo*periode->HpJ;
	LaGrille->Cells[9][row]=Aff(periode->HDispo);
}
//---------------------------------------------------------------------------
bool __fastcall TDefCalendrierFrm::VerifGrille(TStringGrid *grille)
{
//int g;
	char buf[100];
	bool correct=true;
	CL_Periode *periode;
	int n;
	AnsiString as;
	char car;
	// il n y a pas de doublon
	//verif de la derniere cellule
	for(int r=1;r<grille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		periode=(CL_Periode*)LaGrille->Objects[0][r];
		if(periode->Nom.IsEmpty()==true)
		{
			correct=false;
			wsprintf(buf,L_PasNom.c_str(),LaGrille->Name.c_str(),r);
			//sprintf(chaine," %s row=%d Pas de nom",LaGrille->Name.c_str(),row);
			grille->Col=2;
			grille->Row=r;
			ErreurFrm->Edit->Lines->Add(buf);
		}
		else
		{
			for(n=1;n<=periode->Nom.Length();n++)
			{
				car=periode->Nom[n];
				if(car==' ')continue;
				if(isalnumA(car)==1) continue;

				correct=false;
				wsprintf(buf,L_CarInval.c_str(),as.c_str(),r);
				//wsprintf(buf,"Caractère Invalide dans %s ligne %d ",as.c_str(),r);
				grille->Col=2;
				grille->Row=r;
				ErreurFrm->Edit->Lines->Add(buf);

			}
		}
		if(periode->JDeb==0 ||periode->MDeb==0)
		{
			correct=false;
			wsprintf(buf,L_PasDeb.c_str(),r);
			//wsprintf(buf,"Pas de Debut ligne %d ",r);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		if(periode->JFin==0 ||periode->MFin==0)
		{
			correct=false;
			wsprintf(buf,L_PasFin.c_str(),r);
			//wsprintf(buf,"Pas de Fin ligne %d ",r);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		if(periode->HpJ==0 )
		{
			correct=false;
			wsprintf(buf,L_PasHparJour.c_str(),r);
			//wsprintf(buf,"Pas d'heure par jour ligne %d ",r);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		if(periode->PcentDispo==0 ||periode->PcentDispo>100)
		{
			correct=false;
			wsprintf(buf,L_DispoBizarre.c_str(),r);
			//wsprintf(buf,"% Dispo bizarre  ligne %d ",r);
			ErreurFrm->Edit->Lines->Add(buf);
		}
	}
	if(correct==false) return false;
	correct=VerifCoherence(grille);

	return correct;
}
// a simplifier cest la copie quasi conforme de CalTrav DatePeriode
//---------------------------------------------------------------------------
bool __fastcall TDefCalendrierFrm::VerifCoherence(TStringGrid *grille)
{
	int r;
	int duree,ecart;
	Word an;
	char chaine[100];
	CL_Periode *periode,*periodeDebut;
	TDateTime dtDeb,dtFin,dtDebut;
	an=2001;
	periodeDebut=NULL;
	for(r=1;r<grille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;

		periode=(CL_Periode*)grille->Objects[0][r];
		periode->ADeb=periode->AFin=an;
		dtDeb = EncodeDate((Word) periode->ADeb, (Word) periode->MDeb,
				(Word)periode->JDeb);
		dtFin = EncodeDate((Word) periode->AFin, (Word) periode->MFin,
				(Word)periode->JFin);
		duree=dtFin-dtDeb;
		if(duree==0)
		{
			sprintf(chaine,L_Duree0.c_str(),r);
			//sprintf(chaine," La période ligne %d a une duree nulle",r);
			ShowMessage(chaine);
			return false;
		}

		if(duree<0)
		{
			duree+=365;
			periode->AFin++;
			periode->Duree=duree;
		}

		if(periodeDebut==NULL)
		{
			periodeDebut=periode;
			periodeDebut->JD=0;
			dtDebut=dtDeb; //debut du calendrier
		}
		else
		{
			dtDeb = EncodeDate((Word) periode->ADeb, (Word) periode->MDeb,
					(Word)periode->JDeb);
			ecart=dtDeb-dtDebut;
			if(ecart<0)
			{
				periode->ADeb++;
				periode->AFin++;
				ecart+=365;
			}
			if(ecart >365)
			{
				sprintf(chaine,L_Duree365.c_str(),r);
				//sprintf(chaine," La période ligne %d fait dépasser 365 jours",r);
				ShowMessage(chaine);
				return false;
			}
			periode->JD=ecart;
		}
		periode->JF=periode->JD+duree;
	}
	return true;
}
//-----------------------------------------------------------------------------
void __fastcall TDefCalendrierFrm::DeGrille(TStringGrid *grille)
{
	CL_Vecteur<CL_Periode> *vPeriode;
	CL_Periode *periode;
	vPeriode=Calendrier->V_Periode;
	vPeriode->Nbelt=0; //011001
	for(int r=1;r<grille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		periode=(CL_Periode*)LaGrille->Objects[0][r];

		if(periode->Flag=='S')continue; //011001

		if(periode->Flag=='N')vPeriode->ins(periode);
		else vPeriode->insSans(periode);

	}
}
//-----------------------------------------------------------------------------

void __fastcall TDefCalendrierFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	DerniereCell();
	if(LabelModifie->Visible==false) return;

	ErreurFrm->Edit->Clear();
	//ControleCell(LaGrille->Col,LaGrille->Row);
	if(VerifGrille(Grille0)==true)
	{
		DeGrille(Grille0);
		ES->ecrireFichier();
		LabelModifie->Visible=false;
		CanClose=true;
	}
	else
	{
		CanClose=false;
		AutreDonnee=false; //pour eviter effacement cf forme00Activate
		ErreurFrm->Show();
	}
}
//---------------------------------------------------------------------------
//definition des périodes manuel mensuel quinzaine
//---------------------------------------------------------------------------
void __fastcall TDefCalendrierFrm::RGDefClick(TObject *Sender)
{
	int i,j;
	int rep;
	CL_Periode *periode;
	if(Calendrier->V_Periode!=0)
	{
		rep=MessageBox(Handle,L_Rajout.c_str(),L_PerDef.c_str(),MB_YESNO|MB_ICONQUESTION);
		//rep=MessageBox(Handle,"Voulez vous rajouter des périodes ?","PERIODES DEJA DEFINIES",MB_YESNO|MB_ICONQUESTION);
		if(rep==IDNO) return;
	}

	switch(RGDef->ItemIndex)
	{
		case 0: break; //l'utilisateur définit ses périodes
		case 1:
		for(i=1;i<=12;i++)
		{
			periode=new CL_Periode();
			periode->Nom=NomMois(i);
			periode->JDeb=1;
			periode->MDeb=i;
			periode->JFin=1;
			periode->MFin=periode->MDeb+1;
			periode->AFin=0;
			if(periode->MFin>12)
			{
				periode->MFin=1;
				periode->AFin=1;
			}
			periode->CalculDuree();
			Calendrier->V_Periode->ins(periode);
		}
		VersGrille(Grille0);
		LabelModifie->Visible=true;
		break;
		case 2:
		for(i=1;i<=12;i++)
		{
			for(j=0;j<2;j++)
			{
				periode=new CL_Periode();
				periode->Nom=NomMois(i)+"  "+AnsiString(j+1);
				periode->AFin=0;
				if(j==0)
				{
					periode->JDeb=1;
					periode->MDeb=i;
					periode->JFin=15;
					periode->MFin=i;
				}
				else
				{
					periode->JDeb=15;
					periode->MDeb=i;
					periode->JFin=1;
					periode->MFin=i+1;
				}
				if(periode->MFin>12)
				{
					periode->MFin=1;
					periode->AFin=1;
				}
				periode->CalculDuree();
				Calendrier->V_Periode->ins(periode);
			}
		}
		VersGrille(Grille0);
		LabelModifie->Visible=true;
		break;
	}
}
//---------------------------------------------------------------------------
// report bas 1 colonne
//---------------------------------------------------------------------------
void __fastcall TDefCalendrierFrm::BtRepBasClick(TObject *Sender)
{
	int r,row,col;
	AnsiString as,asDest;
	CL_Periode *periode;
	LabelModifie->Visible=true;
	row=LaGrille->Row;
	col=LaGrille->Col;
	periode=(CL_Periode*)LaGrille->Objects[0][row];

	if(periode==NULL) return;
	as=LaGrille->Cells[col][row];
	for(r=LaGrille->Row+1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;

		asDest=LaGrille->Cells[col][r];
		if(asDest.Length()>1 && ChBRepTout->Checked==false)continue;

		LaGrille->Cells[col][r]=as;
		//calcule jours dispo...
		ControleCell(col,r);
	}
}
//---------------------------------------------------------------------------
// report bas  colonne  n°  5 6
//---------------------------------------------------------------------------
void __fastcall TDefCalendrierFrm::BtRecopBasClick(TObject *Sender)
{
	int col=LaGrille->Col;
	LabelModifie->Visible=true;
	LaGrille->Col=5;BtRepBasClick(this);
	LaGrille->Col=6;BtRepBasClick(this);
	LaGrille->Col=col;

}
//---------------------------------------------------------------------------
//supprime un ligne
//---------------------------------------------------------------------------
void __fastcall TDefCalendrierFrm::BtSupClick(TObject *Sender)
{
	int r=LaGrille->Row;
	CL_Periode* periode;
	int rep;
	char buf[100];
	periode=(CL_Periode*)LaGrille->Objects[0][r];
	if(periode==NULL) return;
	SelLigne();
	if(periode->Supprimable==false)
	{
		ShowMessage(T->L_Utilise);
		//ShowMessage(" UTILISE ");
		DeSelLigne();
		return;
	}
	sprintf(buf,L_SupQ.c_str(),periode->Nom.c_str() );
	//sprintf(buf," Je supprime %s \n Vous êtes sur ?",periode->Nom.c_str() );
	rep=MessageBox(Handle,buf,L_SupQ.c_str(),MB_YESNO);
	//rep=MessageBox(Handle,buf,"SUPPRESSION",MB_YESNO);
	if(rep==IDYES)
	{
		periode->Flag='S';
		SupprimerLigne(r); //140406
		LabelModifie->Visible=true;
	}
	DeSelLigne();

}
//---------------------------------------------------------------------------
void __fastcall TDefCalendrierFrm::BtBnVideToutClick(TObject *Sender)
{
	int i;
	int r; //=LaGrille->Row;
	CL_Periode* periode;
	int newPeriodeX=0;
	//poser question
	for(r=1;r<LaGrille->RowCount;r++)
	{
		periode=(CL_Periode*)LaGrille->Objects[0][r];
		if(periode==NULL) continue;
		if(periode->Supprimable==false) {newPeriodeX++; continue;}

		periode->Flag='S';
		SupprimerLigne(r);r--;
		LabelModifie->Visible=true;
	}
	//for(r=1;r<LaGrille->RowCount;r++)
	//    periode=(CL_Periode*)LaGrille->Objects[0][r];
	for(i=0;i<V_Culture->Nbelt;i++) EffBesTrav(V_Culture->Vecteur[i],newPeriodeX);
	for(i=0;i<V_Animaux->Nbelt;i++) EffBesTrav(V_Animaux->Vecteur[i],newPeriodeX);
	for(i=0;i<V_Perenne->Nbelt;i++) EffBesTrav(V_Perenne->Vecteur[i],newPeriodeX);
	for(i=0;i<V_Vivrier->Nbelt;i++) EffBesTrav(V_Vivrier->Vecteur[i],newPeriodeX);

}
//---------------------------------------------------------------------------
void __fastcall TDefCalendrierFrm::SupprimerLigne(int r0)
{
	int r;
	for(r=r0;r<LaGrille->RowCount;r++)
	{
		LaGrille->Rows[r] =LaGrille->Rows[r+1];
		LaGrille->Objects[0][r]=LaGrille->Objects[0][r+1];
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TDefCalendrierFrm::EffBesTrav(CL_Atelier *atelier, int newPeriodeX) {
	int n;
	CL_BesTrav *besTrav;

	for (n = 0; n < atelier->V_BesTrav->Nbelt; n++) {
		besTrav = atelier->V_BesTrav->Vecteur[n];
		if (besTrav->Calendrier == Calendrier) {
			EffBesTrav2(besTrav, newPeriodeX, atelier->NbPhase);
			break;
		}
	}
}
//---------------------------------------------------------------------------
void TDefCalendrierFrm::EffBesTrav2(CL_BesTrav *besTrav, int newPeriodeX,
		int nbPhase) {
	int i, j;
	int periodeX;
	float z;
	CL_Calendrier *calendrier;
	CL_Periode *periode;
	CL_Matrice *newBesoins;
	int iNew;
	newBesoins = new CL_Matrice(newPeriodeX, nbPhase);

	calendrier = besTrav->Calendrier;
	periodeX = calendrier->V_Periode->Nbelt;

	iNew = 0;
	for (i = 0; i < periodeX; i++) {
		periode = calendrier->V_Periode->Vecteur[i];
		if (periode->Supprimable == true)
			continue;

		for (j = 0; j < nbPhase; j++) {
			z = besTrav->Besoins->val(i, j);
			newBesoins->vaut(iNew, j, z);
		}
		iNew++;
	}
	besTrav->Besoins = newBesoins;
	besTrav->NbPeriodeCal = iNew;
}
/*
 //---------------------------------------------------------------------------
 void  TDefCalendrierFrm::EffBesTrav2(CL_BesTrav *besTrav,,int newPeriodeX,int nbPhase)
 {
 int i,j,k;
 int nbLibre;
 int periodeX;
 float z;
 bool estLibre[50];
 CL_Calendrier *calendrier;
 CL_Periode *periode;
 calendrier=besTrav->Calendrier;
 periodeX=calendrier->V_Periode->Nbelt;

 for(i=0;i<periodeX;i++)estLibre[i]=false;
 nbLibre=0;

 for(i=0;i<periodeX;i++)
 {
 periode=calendrier->V_Periode->Vecteur[i];
 if(periode->Supprimable==true)
 {
 estLibre[i]=true;
 nbLibre++;
 }
 else
 {
 if(nbLibre==0) continue;
 //j est une ligne
 for(j=0;j<periodeX;j++)
 {
 if(estLibre[j]==true)
 {
 for(k=0;k<nbPhase;k++)
 {
 z=besTrav->Besoins->val(i,k);
 besTrav->Besoins->vaut(i,j,z);
 }
 }
 estLibre[i]=true;
 }
 }
 }
 }
 */
//---------------------------------------------------------------------------
void TDefCalendrierFrm::TexteChaine(void) {
	L_Periode = T->TrouveTexte("DefCalendrierFrm", "L_Periode");
	L_Debut = T->TrouveTexte("DefCalendrierFrm", "L_Debut");
	L_Fin = T->TrouveTexte("DefCalendrierFrm", "L_Fin");
	L_HJ = T->TrouveTexte("DefCalendrierFrm", "L_HJ");
	L_Dispo = T->TrouveTexte("DefCalendrierFrm", "L_Dispo");
	L_Jours = T->TrouveTexte("DefCalendrierFrm", "L_Jours");
	L_JDispo = T->TrouveTexte("DefCalendrierFrm", "L_JDispo");
	L_HDispo = T->TrouveTexte("DefCalendrierFrm", "L_HDispo");
	L_PasNom = T->TrouveTexte("DefCalendrierFrm", "L_PasNom");
	L_Plus100 = T->TrouveTexte("DefCalendrierFrm", "L_Plus100");
	L_CarInval = T->TrouveTexte("DefCalendrierFrm", "L_CarInval");
	L_PasDeb = T->TrouveTexte("DefCalendrierFrm", "L_PasDeb");
	L_PasFin = T->TrouveTexte("DefCalendrierFrm", "L_PasFin");
	L_PasHparJour = T->TrouveTexte("DefCalendrierFrm", "L_PasHparJour");
	L_DispoBizarre = T->TrouveTexte("DefCalendrierFrm", "L_DispoBizarre");
	L_Duree0 = T->TrouveTexte("DefCalendrierFrm", "L_Duree0");
	L_Duree365 = T->TrouveTexte("DefCalendrierFrm", "L_Duree365");
	L_Rajout = T->TrouveTexte("DefCalendrierFrm", "L_Rajout");
	L_PerDef = T->TrouveTexte("DefCalendrierFrm", "L_PerDef");
	L_SupQ = T->TrouveTexte("DefCalendrierFrm", "L_SupQ");

}
//--------------------------------------------
void TDefCalendrierFrm::IniCaption(void) {
	DefCalendrierFrm->Caption = LC_DefCalendrierFrm;
	RGDef->Caption = LC_RGDef;
	ChBRepTout->Caption = T->LC_ChBRepTout;
	BtClasser->Caption = T->LC_BtClasser;
	RGDef->Items->Strings[0] = LC_PerDeFParUt;
	RGDef->Items->Strings[1] = LC_PerDefMois;
	RGDef->Items->Strings[2] = LC_PerDefQuinz;
	BtBnQuitter->Caption = T->LC_BtBnQuitter;
}
//--------------------------------------------
void TDefCalendrierFrm::TexteCaption(void) {
	LC_DefCalendrierFrm = T->TrouveCaption("DefCalendrier",
			"LC_DefCalendrierFrm");
	LC_RGDef = T->TrouveCaption("DefCalendrier", "LC_RGDef");
	LC_PerDeFParUt = T->TrouveCaption("DefCalendrier", "LC_PerDeFParUt");
	LC_PerDefMois = T->TrouveCaption("DefCalendrier", "LC_PerDefMois");
	LC_PerDefQuinz = T->TrouveCaption("DefCalendrier", "LC_PerDefQuinz");
	IniCaption();

}

void __fastcall TDefCalendrierFrm::BtBnNoteClick(TObject *Sender)
{
//
	NoteAgriFrm->VientDe="DefCalendrier";//ne pas traduire
	NoteAgriFrm->Calendrier=Calendrier;
	NoteAgriFrm->Caption=Calendrier->Nom;
	NoteAgriFrm->Memo->Text=Calendrier->Notes;

	NoteAgriFrm->Show();

}
//---------------------------------------------------------------------------

bool __fastcall TDefCalendrierFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=420;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

void __fastcall TDefCalendrierFrm::BtBnAideClick(TObject *Sender)
{
	HelpContext=420;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);

}
//---------------------------------------------------------------------------

