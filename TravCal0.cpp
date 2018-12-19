//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "Forme0.h"
#include "Forme01.h"

#include "SortieEcran.h"
#include "ChoixMotif.h"

#include "TravCal.h"
//#include "Graph.h"   //???
#include "CL_SousPeriode.h"
#include "CL_Matrice.h"
#include "CL_BesTravAtelier.h"

#include "TravGraph.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
//   decouper les périodes en sous périodes
void __fastcall TTravCalFrm::EtablirBornes(void)
{
	int n;
	CL_Vecteur<CL_Periode> *v_Periode;
	CL_Periode *periode;
	v_Periode=Calendrier->V_Periode;
	BorneX=v_Periode->Nbelt*2;
	LesBornes=new int[BorneX];

	// calcule la durée des péeiodes
	//etablit periode->J0  debut de la période par rapport au début de la période initiale
	DatePeriode(Calendrier->V_Periode);

	NBorne=0;
	for(n=0;n<v_Periode->Nbelt;n++)
	{
		periode=v_Periode->Vecteur[n];
		LesBornes[NBorne++]=periode->JD;
		LesBornes[NBorne++]=periode->JF;
	}
	// classer les bornes et retirer les doublons
	// bornes classées selon date croissante

	qsort((void *)LesBornes, NBorne, sizeof(int), CmpBornes);

//    LstBornes->Sort(CmpBornes);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	RetirerDoublon();

	// creer les sous périodes
	CreerSousPeriodes();
	//
	CorrespondancePeriodeSousPeriode();
// faire un diagramme
//    Imprimer();
}
//---------------------------------------------------------------------------
bool __fastcall TTravCalFrm::DatePeriode(CL_Vecteur<CL_Periode> *v_Periode)
{
	int n;
	int duree,ecart;
	Word an;
	char chaine[100];
	CL_Periode *periode,*periodeDebut;
	TDateTime dtDeb,dtFin; //,dtDebut;
	an=2001;
	for(n=0;n<v_Periode->Nbelt;n++)
	{
		periode=v_Periode->Vecteur[n];
		periode->ADeb=periode->AFin=an;
		dtDeb = EncodeDate((Word) periode->ADeb, (Word) periode->MDeb,
				(Word)periode->JDeb);
		dtFin = EncodeDate((Word) periode->AFin, (Word) periode->MFin,
				(Word)periode->JFin);
		duree=dtFin-dtDeb;
		if(duree==0)
		{
			sprintf(chaine," La période n° %d a une duree nulle",n);
			ShowMessage(chaine);
			return false;
		}

		if(duree<0)
		{
			duree+=365;
			periode->AFin++;
			periode->Duree=duree;
		}

		if(n==0)
		{
			periodeDebut=periode;
			periodeDebut->JD=0;
			DtDebut=dtDeb; //debut du calendrier
		}
		else
		{
			dtDeb = EncodeDate((Word) periode->ADeb, (Word) periode->MDeb,
					(Word)periode->JDeb);
			ecart=dtDeb-DtDebut;
			if(ecart<0)
			{
				periode->ADeb++;
				periode->AFin++;
				ecart+=365;
			}
			if(ecart >365)
			{
				sprintf(chaine," La période n° %d fait dépasser 365 jours",n);
				ShowMessage(chaine);
				return false;
			}
			periode->JD=ecart;
		}
		periode->JF=periode->JD+duree;
	}
	return true;
}
//--------------------------------------------------------------------------
void __fastcall TTravCalFrm::RetirerDoublon(void)
{
	int i,j;
	int borne,borneApres;
//CL_Borne *borne,*borneAvant;
	for(i=0;i<NBorne;i++)
	{
		borne= LesBornes[i];
		borneApres= LesBornes[i+1];
		if(borne==borneApres)
		{
			for(j=i+1;j<NBorne;j++)
			LesBornes[j]=LesBornes[j+1];
			NBorne--;
		}
	}
}
//--------------------------------------------------------------------------
void __fastcall TTravCalFrm::CreerSousPeriodes(void)
{
	int n;
	CL_SousPeriode *sPeriode;
	int borne1,borne2;
	LstSousPeriodes=new TList;
	for(n=0;n<NBorne-1;n++)
	{
		borne1=LesBornes[n];
		borne2=LesBornes[n+1];
		sPeriode=new CL_SousPeriode(borne1,borne2,Calendrier);
		LstSousPeriodes->Add(sPeriode);
	}
}
//--------------------------------------------------------------------------
void __fastcall TTravCalFrm::CorrespondancePeriodeSousPeriode(void)
{
	int i,j;
	int n;
	int jD,jF;
	int dureePeriode;
	float pcent;
	CL_Periode *periode;
	CL_SousPeriode *sPeriode;
	CL_Vecteur<CL_Periode> *v_Periode;

	v_Periode=Calendrier->V_Periode;
	for(i=0;i<v_Periode->Nbelt;i++)
	{
		periode=v_Periode->Vecteur[i];
		dureePeriode= periode->JF-periode->JD;
		jD=periode->JD;
		jF=periode->JF;
		for(j=0;j<LstSousPeriodes->Count;j++)
		{
			sPeriode=(CL_SousPeriode*)LstSousPeriodes->Items[j];
			if(sPeriode->JD >=jD && sPeriode->JF <=jF)
			{
				n=sPeriode->NPeriode;
				sPeriode->LesPeriodes[n]=periode;
				pcent=(float)(sPeriode->JF-sPeriode->JD)/(float)dureePeriode;
				sPeriode->LesPcent[n]=pcent;
				sPeriode->NPeriode++;
			}
		}
	}
	return;
}

//--------------------------------------------------------------------------
//Pour Test à court circuiter une fois mis au point
void __fastcall TTravCalFrm::Imprimer(void)
{
	int n;
	CL_Periode *periode;
	CL_Vecteur<CL_Periode> *v_Periode;
	int borne;
	CL_SousPeriode *sPeriode;
	char chaine[100];
	float pcent;
	Word Year,jDeb,mDeb,jFin,mFin;

	v_Periode=Calendrier->V_Periode;
	SortieEcranFrm->Memo1->Clear();
	SortieEcranFrm->Memo1->Lines->Add("Périodes");
	for(n=0;n<v_Periode->Nbelt;n++)
	{
		periode=v_Periode->Vecteur[n];
		sprintf(chaine,"%3d %3d   %3d %3d %4d    %3d %3d %4d   %3d %3d %3d",
				n,periode->No,
				periode->JDeb,periode->MDeb,periode->ADeb,
				periode->JFin,periode->MFin,periode->AFin,
				periode->JD,periode->JF,
				periode->Duree);
		SortieEcranFrm->Memo1->Lines->Add(chaine);
	}
	SortieEcranFrm->Memo1->Lines->Add("");

	SortieEcranFrm->Memo1->Lines->Add("Bornes");
	for(n=0;n<NBorne;n++)
	{
		borne=LesBornes[n];
		sprintf(chaine,"%3d    %3d    ",n,borne);
		SortieEcranFrm->Memo1->Lines->Add(chaine);
	}
	SortieEcranFrm->Memo1->Lines->Add("");

	SortieEcranFrm->Memo1->Lines->Add("Sous Périodes");
	for(n=0;n<LstSousPeriodes->Count;n++)
	{
		sPeriode=(CL_SousPeriode *)LstSousPeriodes->Items[n];
		DecodeDate(DtDebut+(Word)sPeriode->JD, Year, mDeb, jDeb);
		DecodeDate(DtDebut+(Word)sPeriode->JF, Year, mFin, jFin);
		sprintf(chaine,"%3d    %3d   %3d   %3d %3d  %3d %3d",
				n,sPeriode->JD,sPeriode->JF,jDeb,mDeb,jFin,mFin);
		SortieEcranFrm->Memo1->Lines->Add(chaine);
		for(int i=0;i<sPeriode->NPeriode;i++)
		{

			periode=sPeriode->LesPeriodes[i];
			pcent= sPeriode->LesPcent[i];

			sprintf(chaine, "     %3d    %3d  %6.5f",
					i,periode->No,pcent);
			SortieEcranFrm->Memo1->Lines->Add(chaine);
		}
	}
	SortieEcranFrm->Memo1->Lines->Add("");

	SortieEcranFrm->Show();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::BtBnLegendeClick(TObject *Sender)
{
	int n;
	int coul,motif;
//int NAtelier,AtelierX;
	CL_Legende *legende;
	CL_Atelier *atelier;
	CL_BesTravAtelier *besTravAtelier;
	if(LstBesAtelier==NULL) return;//101005
	//GB->Clear();
	if(LstLegende==NULL)
	LstLegende=new TList;
	LstLegende->Clear();
	/*
	 Canvas->Pen->Width=1;
	 //    Canvas->Pen->Color=clBlack;
	 //	Canvas->Brush->Color=clBlack;
	 GB->Canvas->Pen->Color=clRed;
	 Canvas->Brush->Color=clRed;
	 Canvas->Rectangle(GB->Left,GB->Top,GB->Left+GB->Width,GB->Top+GB->Height);
	 return;
	 */
	for(n=0,coul=0,motif=0;n<LstBesAtelier->Count;n++)
	{
		besTravAtelier=(CL_BesTravAtelier*)LstBesAtelier->Items[n];
		atelier=besTravAtelier->Atelier;
		if(atelier->Couleur==-1)
		{
			atelier->Couleur=LesCouleurs[coul];
			coul++;
			if(coul==CoulX)coul=0;

			motif=0;
			atelier->Motif=LesMotifs[motif];
		}
		if(atelier->Motif==-1)
		{
			atelier->Motif=LesMotifs[motif];
			motif++; if(motif==MotifX) motif=0;
		}
//ShowMessage(AnsiString(atelier->Couleur)+ "  "+atelier->Motif);
		legende=new CL_Legende(n,atelier->Nom,atelier->Couleur,clInfoBk);
		LstLegende->Insert(n,legende);
		legende=new CL_Legende(n,atelier->Nom,atelier->Couleur,atelier->Motif);
		LstLegende->Insert(n,legende);
	}
}
//---------------------------------------------------------------------------

void __fastcall TTravCalFrm::RecCouleurMouseDown(TObject *Sender,
		TMouseButton Button, TShiftState Shift, int X, int Y)
{
	int n;
	bool trouve;
	CL_Legende *legende;
	CL_Atelier *atelier;
	CL_BesTravAtelier *besTravAtelier;
	trouve=false;
	for(n=0;n<LstLegende->Count;n++)
	{
		legende=(CL_Legende*)LstLegende->Items[n];
		if(Sender==legende->Couleur)
		{
			trouve=true;
			break;
		}
	}
	if(trouve==false) return;
	besTravAtelier=(CL_BesTravAtelier*)LstBesAtelier->Items[n];
	atelier=besTravAtelier->Atelier;
	if(ColorDialog->Execute())
	{
		legende->Couleur->Brush->Color = ColorDialog->Color;
		legende->Motif->Brush->Style = (TBrushStyle)LesMotifs[0]; //ColorDialog->Color;
		legende->Ensemble->Brush->Color = ColorDialog->Color;
		atelier->Couleur=(int)ColorDialog->Color;
		BtBnLegendeClick(this);
	}
}

//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::RecMotifMouseDown(TObject *Sender,
		TMouseButton Button, TShiftState Shift, int X, int Y)
{
	int n;
	bool trouve;
//POINT p,q;
//TShape     *couleur,*ensemble;
	CL_Atelier *atelier;
	CL_BesTravAtelier *besTravAtelier;
	trouve=false;
	for(n=0;n<LstLegende->Count;n++)
	{
		Legende=(CL_Legende*)LstLegende->Items[n];
		if(Sender==Legende->Motif)
		{
			trouve=true;
			break;
		}
	}
	if(trouve==false) return;
	besTravAtelier=(CL_BesTravAtelier*)LstBesAtelier->Items[n];
	atelier=besTravAtelier->Atelier;

	//atelier=(CL_Atelier*)LstBesAtelier->Items[n];
	ChoixMotifFrm->Atelier=atelier;
	ChoixMotifFrm->Show();
	/*
	 legende->Couleur->Brush->Color = ColorDialog->Color;
	 //        legende->Motif->Brush->Color = ColorDialog->Color;
	 legende->Ensemble->Brush->Color = ColorDialog->Color;
	 atelier->Couleur=(int)ColorDialog->Color;
	 */
}
// appelé par ChoixMotif d'ou Legende et non legende
//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::DessineMotif(int n)
{
//    if(n>0)n++;

	Legende->Motif->Brush->Color= clWhite;//clBlack;
	Legende->Motif->Brush->Style= (TBrushStyle)LesMotifs[n];
	Legende->Ensemble->Brush->Style= (TBrushStyle)LesMotifs[n];
}
//---------------------------------------------------------------------------

