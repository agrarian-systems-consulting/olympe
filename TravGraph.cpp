//---------------------------------------------------------------------------

#include <vcl.h>
#include <Printers.hpp>
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "CL_SousPeriode.h"
#include "Forme0.h"
#include "Forme01.h"
#include "CL_Trad.h"

#include "TravCal.h"
#include "CL_BesTravAtelier.h"

#include "TravGraph.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTravGraphFrm *TravGraphFrm;
TCanvas *LeCanvas;
int LaHeight;
int LaWidth;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TTravGraphFrm::TTravGraphFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::FormResize(TObject *Sender)
{

	LeCanvas=TravGraphFrm->Canvas;
	LaWidth=Width;
	LaHeight=Height-PanelBas->Height;
	Dessiner();

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::Dessiner(void)
{
	//coordonnes de l'ecran d'affichage
	// l'ecran fait 400*276
	// cf papier quadrille
	LEcran=400;
	HEcran=276;

	XGauche=20;
	XDroit= 380;
//    XDroit= 400;

	YBas= 20;// 30;
	YHaut= 220;//230;

	// rectangle(xGauche,yHaut,xDroit,yBas)
	// tout l'ecran blanc
	LeCanvas->Pen->Style=psClear;
	LeCanvas->Brush->Color=clInfoBk;
	LeCanvas->Brush->Style=bsSolid;
	LeCanvas->Rectangle(0,0,LaWidth,LaHeight);

	// haut pour titre
	LeCanvas->Brush->Color=clAqua;
	//                  xGauche yHaut xDroit yBas
	LeCanvas->Rectangle(Xde(0),0,LaWidth,Yde(YHaut+25));

	AffTitre();

	LeCanvas->Font->Size=8;
	//Axes
	TraitHor(YBas,XGauche,XDroit,2);

	TraitVer(XGauche,YBas,YHaut,2);
	TraitVer(XDroit ,YBas,YHaut,2);

	CoordSPeriodes();
	AffDatePeriodes();

	//Nombre ouvrier
//    AffNbOuv();
	// besoins par sous période
	AffBesoins();
	//Nombre ouvrier
	AffNbOuv();
	Legende();
}
//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::CoordSPeriodes(void)
{
	CL_SousPeriode *sPeriode;
	int n;
	float xG;
	// calculer echelle
	// pour se mettre dans zone dont largeur=XGauche-XDroit;
	//prendre derniere sousPériode
	n=TravCalFrm->LstSousPeriodes->Count-1;
	sPeriode=(CL_SousPeriode *)TravCalFrm->LstSousPeriodes->Items[n];
	EchelleH=(XDroit-XGauche)/(float)sPeriode->JF;
	// caculer coordonnes x de chaque sousPeriode
	xG=XGauche;
	for(n=0;n<TravCalFrm->LstSousPeriodes->Count;n++)
	{
		sPeriode=(CL_SousPeriode *)TravCalFrm->LstSousPeriodes->Items[n];
		sPeriode->xG=xG;
		sPeriode->xD=sPeriode->JF*EchelleH+XGauche;
		xG=sPeriode->xD;
	}
}
//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::AffTitre(void)
{
	AnsiString date;
	TDateTime time;
	CL_Agriculteur *agri=TravCalFrm->Agri;
	int an=TravCalFrm->AnSim;
	time=TDateTime::CurrentDateTime();
	date=time.DateTimeString();

	LeCanvas->Brush->Color=clAqua;
//    LeCanvas->Font->Size=8;
	LeCanvas->Font->Name="Arial";
	LeCanvas->Font->Size=7;//8;
	LeCanvas->TextOut(Xde(0),Yde(HEcran),date );
//    LeCanvas->Font->Style=TFontStyles ()>>fsItalic;
	LeCanvas->Font->Style=TFontStyles ()<<fsBold;
	LeCanvas->Font->Size=10;
	// 260902
	LeCanvas->TextOut(Xde(0),Yde(HEcran-8),agri->NomVC());
	LeCanvas->TextOut(Xde(0),Yde(HEcran-18),an);
	LeCanvas->Font->Style=TFontStyles ()>>fsBold;

}
//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::AffDatePeriodes(void)
{
	CL_SousPeriode *sPeriode;
	int n;
	float x;
	int hBar=3;
	int decal;
	char *laDate;
	SetTextAlign(LeCanvas->Handle,TA_LEFT);
	LeCanvas->Brush->Color=clWhite;
	LeCanvas->Pen->Color=clBlack;

	// debut de premiere sous période
	sPeriode=(CL_SousPeriode *)TravCalFrm->LstSousPeriodes->Items[0];
	laDate=ChaineDate(sPeriode->JD);
	x=sPeriode->xG;
	TraitVer(x,YBas,YBas-hBar,2);
	LeCanvas->TextOut(Xde(x),Yde(YBas-1),laDate );

	// fin de chaque sous période
	// une date sur 2 est mise plus bas
	decal=5;
	for(n=0;n<TravCalFrm->LstSousPeriodes->Count;n++)
	{
		sPeriode=(CL_SousPeriode *)TravCalFrm->LstSousPeriodes->Items[n];
		x=sPeriode->xD;
		laDate=ChaineDate(sPeriode->JF);
		TraitVer(x,YBas,YBas-hBar,2);
//        if(n==TravCalFrm->LstSousPeriodes->Count-1)
//            SetTextAlign(LeCanvas->Handle,TA_RIGHT);

		LeCanvas->TextOut(Xde(x),Yde(YBas-decal),laDate );
		if(decal==5)decal=1;
		else decal=5;
//        LeCanvas->TextOut(Xde(x),Yde(YBas-5),laDate );
	}

}
//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::AffNbOuv(void)
{
	int n,y;
	float hauteur;
	AnsiString s;
	int delta;
	LeCanvas->Pen->Style=psClear;
	LeCanvas->Brush->Color=clInfoBk;
	LeCanvas->Brush->Style=bsSolid;

	hauteur=(YHaut-YBas)/TravCalFrm->NbOuv;
	SetTextAlign(LeCanvas->Handle,TA_RIGHT);

	if (TravCalFrm->NbOuv<=5)delta=1; //050302
	else if(TravCalFrm->NbOuv<=10)delta=2;
	else if(TravCalFrm->NbOuv<=25)delta=5;
	else delta=10;

	// 1 ouvrier
	AffUnOuv(1,hauteur);
	n=delta;
	if(n!=1)
	AffUnOuv(n,hauteur);
	while(n<=TravCalFrm->NbOuv)
	{
		n+=delta;
		AffUnOuv(n,hauteur);
	}
	// NbTrav
	LeCanvas->Font->Size=10;
	n=TravCalFrm->NbTrav;
	y=YBas+hauteur*n;
	if(y>YHaut)return;
	s=AnsiString(n);
	TraitHor(y,XGauche,XDroit,5);
	LeCanvas->TextOut(Xde(XGauche-10),Yde(y),s);
}
//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::AffUnOuv(int n,float hauteur)
{
	int y;
	AnsiString s;
	y=YBas+hauteur*n;
	if(y>YHaut)return;
	s=AnsiString(n);
	TraitHor(y,XGauche,XDroit,1);
	LeCanvas->TextOut(Xde(XGauche-10),Yde(y),s);
}
//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::AffBesoins(void)
{
	int c; //comme culture
	int n;
	int nbSousPeriode;
	float dispo,pcentUt;
	float h;
//float *besSousPer;
	float *bas;
	CL_Atelier *atelier;
	CL_BesTravAtelier *besTravAtelier;
//asup
	float ds,ouv;
	static int coul=0;
//    LeCanvas->Brush->Color=clInfoBk;

	LeCanvas->Pen->Style=psSolid;
	LeCanvas->Pen->Width=1;

	nbSousPeriode=TravCalFrm->LstSousPeriodes->Count;
	bas=new float[nbSousPeriode];
	for(n=0;n<nbSousPeriode;n++)bas[n]=YBas;

	for(c=0;c<TravCalFrm->LstBesAtelier->Count;c++)
	{
		besTravAtelier=(CL_BesTravAtelier*)TravCalFrm->LstBesAtelier->Items[c];
		atelier= besTravAtelier->Atelier;

		//pour trouver motif et couleur
		//300902
		if(atelier->Couleur==-1)
		{
			atelier->Couleur=TravCalFrm->LesCouleurs[coul];
//             atelier->Couleur=clRed;
			coul++;if(coul==TravCalFrm->CoulX)coul=0;
		}
		//besSousPer=(float *)TravCalFrm->LstBesSousPer->Items[c];
		for(n=0;n<nbSousPeriode;n++)
		{
			ds=TravCalFrm->DispoSousPer[n];
			ouv=TravCalFrm->NbOuv;

			dispo=TravCalFrm->DispoSousPer[n]*TravCalFrm->NbOuv;
			if(dispo <0.1) continue;
			if(besTravAtelier->besSousPeriode[n]==0) continue;

			pcentUt=besTravAtelier->besSousPeriode[n]/dispo;
			h=(YHaut-YBas)*pcentUt;
			Histo(atelier,n,h,bas);
			bas[n]+=h;
		}
	}
	delete[]bas;
}
//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::Legende(void)
{
	int n;
	float x,y;
	float deltaY=12; //15;
	AnsiString asNom;
	CL_Atelier *atelier;
	CL_BesTravAtelier *besTravAtelier;
	SetTextAlign(LeCanvas->Handle,TA_LEFT);
	LeCanvas->Font->Color=clBlack;
	LeCanvas->Font->Name="Arial";
	LeCanvas->Font->Size=7;//8;

	LeCanvas->Pen->Style=psSolid;
	LeCanvas->Pen->Width =2;
	y=Yde(YHaut+25)-deltaY;

	for(n=0;n<TravCalFrm->LstBesAtelier->Count;n++)
	{
		if(n%3==0)
		{
			x=XGauche;
			y+=deltaY;
		}
		else
		x+=120;
		besTravAtelier=(CL_BesTravAtelier*)TravCalFrm->LstBesAtelier->Items[n];
		atelier=besTravAtelier->Atelier;
		LeCanvas->Pen->Color=clBlack; //(TColor)atelier->Couleur;
		LeCanvas->Pen->Width=1;

		LeCanvas->Brush->Color=(TColor)atelier->Couleur;
		LeCanvas->Brush->Style=(TBrushStyle)atelier->Motif;
		//trait de la couleur de l'élément
		//        xGauche yHaut xDroit yBas
		LeCanvas->Rectangle(Xde(x),y,Xde(x+20),y+deltaY);

		LeCanvas->Brush->Color=clWhite;
		LeCanvas->TextOut(Xde(x+20),y,atelier->Nom);
	}

	LeCanvas->Pen->Color=clBlack;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::Histo(CL_Atelier *atelier,int n,float h,float *bas)
{
	CL_SousPeriode *sPeriode;
	sPeriode=(CL_SousPeriode*)TravCalFrm->LstSousPeriodes->Items[n];
	//   trouver  couleur motif dans atelier
	LeCanvas->Brush->Style=(TBrushStyle) atelier->Motif;
	LeCanvas->Brush->Color=(TColor) atelier->Couleur;
	LeCanvas->Rectangle(Xde(sPeriode->xG),Yde(bas[n]),Xde(sPeriode->xD),Yde(bas[n]+h));
}
//---------------------------------------------------------------------------
char *__fastcall TTravGraphFrm::ChaineDate(int j)
{
	Word Year,jDeb,mDeb;
	static char chaine[50];
	DecodeDate(TravCalFrm->DtDebut+(Word)j, Year, mDeb, jDeb);
	sprintf(chaine,"%3d %3d" ,jDeb,mDeb);
	return chaine;
}
//---------------------------------------------------------------------------
//           UTILITAIRE de CONVERSION
//---------------------------------------------------------------------------
int __fastcall TTravGraphFrm::Xde(int x)
{
	// toutes les coordonnees sont exprimees en fonction d'un ecran 40*27.6
	x=(x*LaWidth)/LEcran;
	return x;
}
//---------------------------------------------------------------------------
int __fastcall TTravGraphFrm::Yde(int y)
{
	int h;
	h=LaHeight-PanelBas->Height;
	y= h-(y*h)/HEcran;

	// toutes les coordonnees sont exprimees en fonction d'un ecran 40*27.6
	// l'axe des y commence en bas
	return y;
}
//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::TraitHor(int y0, int x0,int x1,int width)
{
	LeCanvas->Pen->Style=psSolid;
	LeCanvas->Pen->Width = width;

	LeCanvas->MoveTo(Xde(x0),Yde(y0));
	LeCanvas->LineTo(Xde(x1),Yde(y0));
}
//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::TraitVer(int x0, int y0,int y1,int width)
{
	LeCanvas->Pen->Style=psSolid;
	LeCanvas->Pen->Width =width;

	LeCanvas->MoveTo(Xde(x0),Yde(y0));
	LeCanvas->LineTo(Xde(x0),Yde(y1));
}

//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::BtImpClick(TObject *Sender)
{
	TPrinter *prnt=Printer();

	LeCanvas=prnt->Canvas;
	prnt->Orientation=poLandscape;
	LaWidth= prnt->PageWidth;
	LaHeight= prnt->PageHeight;

	prnt->BeginDoc();
	Dessiner();
	prnt->EndDoc();

	LaWidth=Width;
	LaHeight=Height;
	LeCanvas=TravGraphFrm->Canvas;
}
//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::BtBnValeurClick(TObject *Sender)
{
	TravCalFrm->BtBnCalculClick(this);
}
//---------------------------------------------------------------------------
//--------------------------------------------
void TTravGraphFrm::IniCaption(void) {
	TravGraphFrm->Caption = LC_TravGraphFrm;
	BtBnValeur->Caption = T->LC_BtBnCalcul;
}
//--------------------------------------------
void TTravGraphFrm::TexteCaption(void) {
	LC_TravGraphFrm = T->TrouveCaption("TravGraph", "LC_TravGraphFrm");
	LC_BtBnCalcul = T->TrouveCaption("CL_Trad", "LC_BtBnCalcul");

	IniCaption();

}

