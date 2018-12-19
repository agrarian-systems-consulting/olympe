//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "CL_SousPeriode.h"
#include "TravCal.h"
#include <Printers.hpp>
#include "TravGraph.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTravGraphFrm *TravGraphFrm;
TCanvas *LeCanvas;

//---------------------------------------------------------------------------
__fastcall TTravGraphFrm::TTravGraphFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::FormResize(TObject *Sender)
{
	LeCanvas=Canvas;
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

	YBas= 30;
	YHaut= 230;

	// rectangle(xGauche,yHaut,xDroit,yBas)
	// tout l'ecran blanc
	Canvas->Pen->Style=psClear;
	Canvas->Brush->Color=clInfoBk;
	Canvas->Brush->Style=bsSolid;
	Canvas->Rectangle(0,0,Width,Height);

	// haut pour titre
	Canvas->Brush->Color=clAqua;
	Canvas->Rectangle(Xde(0),0,Width,Yde(YHaut+10));

	AffTitre();

	Canvas->Font->Size=8;
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
}
//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::CoordSPeriodes(void)
{
	CL_SousPeriode *sPeriode;
	int n;
	int jF;
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
//AnsiString nom;
	CL_Item *critere;
	TDateTime time;
	CL_Agriculteur *agri=TravCalFrm->Agri;
	int an=agri->DefSim->An_0+TravCalFrm->AnSim;
//int n;
	time=TDateTime::CurrentDateTime();
	date=time.DateTimeString();
	// 260902
	/*
	 nom= agri->Nom+"  "+AnsiString(agri->NoVariante);
	 for(int i=0;i<agri->LstCritere->Count;i++)
	 {
	 critere=(CL_Item*)agri->LstCritere->Items[i];
	 nom=nom+"  ";
	 nom=nom+critere->Nom;
	 }
	 */

//    Canvas->Font->Style=TFontStyles ()<<fsItalic;
	Canvas->Brush->Color=clAqua;
	Canvas->Font->Size=8;
	Canvas->TextOut(Xde(0),Yde(HEcran),date );

//    Canvas->Font->Style=TFontStyles ()>>fsItalic;
	Canvas->Font->Style=TFontStyles ()<<fsBold;
	Canvas->Font->Size=12;
	// 260902
	Canvas->TextOut(Xde(0),Yde(HEcran-10),agri->NomVC());
	Canvas->TextOut(Xde(0),Yde(HEcran-20),an);
	Canvas->Font->Style=TFontStyles ()>>fsBold;

}
//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::AffDatePeriodes(void)
{
	CL_SousPeriode *sPeriode;
	int n;
	int JF;
	float x;
	int hBar=3;
	int decal=5;
	char *laDate;
	SetTextAlign(Canvas->Handle,TA_LEFT);
	Canvas->Brush->Color=clWhite;

	// debut de premiere sous période
	sPeriode=(CL_SousPeriode *)TravCalFrm->LstSousPeriodes->Items[0];
	laDate=ChaineDate(sPeriode->JD);
	x=sPeriode->xG;
	TraitVer(x,YBas,YBas-hBar,2);
	Canvas->TextOut(Xde(x),Yde(YBas-1),laDate );

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
//            SetTextAlign(Canvas->Handle,TA_RIGHT);

		Canvas->TextOut(Xde(x),Yde(YBas-decal),laDate );
		if(decal==5)decal=1;
		else decal=5;
//        Canvas->TextOut(Xde(x),Yde(YBas-5),laDate );
	}

}
//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::AffNbOuv(void)
{
	int n,y;
	float hauteur;
	AnsiString s;
	Canvas->Pen->Style=psClear;
	Canvas->Brush->Color=clInfoBk;
	Canvas->Brush->Style=bsSolid;

	hauteur=(YHaut-YBas)/TravCalFrm->NbOuv;
	SetTextAlign(Canvas->Handle,TA_RIGHT);
	for(n=0;n<TravCalFrm->NbOuv;n++)
	{
		y=YBas+hauteur*(n+1);
		s=AnsiString(n+1);
		TraitHor(y,XGauche,XDroit,1);
		Canvas->TextOut(Xde(XGauche-10),Yde(y),s);
	}
}
//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::AffBesoins(void)
{
	int c; //comme culture
	int n;
	int nbSousPeriode;
	float dispo,pcentUt;
	float h;
	float *besSousPer;
	float *bas;
	CL_Atelier *atelier;
	static int coul=0;
//    Canvas->Brush->Color=clInfoBk;

	Canvas->Pen->Style=psSolid;
	Canvas->Pen->Width=1;

	nbSousPeriode=TravCalFrm->LstSousPeriodes->Count;
	bas=new float[nbSousPeriode];
	for(n=0;n<nbSousPeriode;n++)bas[n]=YBas;

	for(c=0;c<TravCalFrm->LstBesSousPer->Count;c++)
	{
		//pour trouver motif et couleur
		atelier=(CL_Atelier*)TravCalFrm->LstAtelier->Items[c];
		//300902
		if(atelier->Couleur==-1)
		{
			atelier->Couleur=TravCalFrm->LesCouleurs[coul];
//             atelier->Couleur=clRed;
			coul++;if(coul==TravCalFrm->CoulX)coul=0;
		}
		besSousPer=(float *)TravCalFrm->LstBesSousPer->Items[c];
		for(n=0;n<nbSousPeriode;n++)
		{
			dispo=TravCalFrm->DispoSousPer[n]*TravCalFrm->NbOuv;
			if(dispo==0) continue;
			if(besSousPer[n]==0) continue;

			pcentUt=besSousPer[n]/dispo;
			h=(YHaut-YBas)*pcentUt;
			Histo(atelier,n,h,bas);
			bas[n]+=h;
		}
	}
	delete[]bas;
}
//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::Histo(CL_Atelier *atelier,int n,float h,float *bas)
{
	CL_SousPeriode *sPeriode;
	sPeriode=(CL_SousPeriode*)TravCalFrm->LstSousPeriodes->Items[n];
	//   trouver  couleur motif dans atelier
	Canvas->Brush->Style=(TBrushStyle) atelier->Motif;
	Canvas->Brush->Color=(TColor) atelier->Couleur;
	Canvas->Rectangle(Xde(sPeriode->xG),Yde(bas[n]),Xde(sPeriode->xD),Yde(bas[n]+h));
}
//---------------------------------------------------------------------------
char *__fastcall TTravGraphFrm::ChaineDate(int j)
{
	Word Year,jDeb,mDeb,jFin,mFin;
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
//    x=(x*Screen->Width)/40;
	x=(x*Width)/LEcran;
	return x;
}
//---------------------------------------------------------------------------
int __fastcall TTravGraphFrm::Yde(int y)
{
	int h;
	h=Height-PanelBas->Height;
	y= h-(y*h)/HEcran;

	// toutes les coordonnees sont exprimees en fonction d'un ecran 40*27.6
	// l'axe des y commence en bas
//    y= Height-(y*Height)/HEcran;
	return y;
}
//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::TraitHor(int y0, int x0,int x1,int width)
{
	Canvas->Pen->Style=psSolid;
	Canvas->Pen->Width = width;

	Canvas->MoveTo(Xde(x0),Yde(y0));
	Canvas->LineTo(Xde(x1),Yde(y0));
}
//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::TraitVer(int x0, int y0,int y1,int width)
{
	Canvas->Pen->Style=psSolid;
	Canvas->Pen->Width =width;

	Canvas->MoveTo(Xde(x0),Yde(y0));
	Canvas->LineTo(Xde(x0),Yde(y1));
}

//---------------------------------------------------------------------------
void __fastcall TTravGraphFrm::BtImpClick(TObject *Sender)
{
	int w,h;
	TCanvas *canv;
	TPrinter *prnt=Printer();
	prnt->BeginDoc();
	prnt->Orientation=poLandscape;
	h=prnt->PageHeight;
	w=prnt->PageWidth;

	prnt->Canvas->TextOut(w/2,h/2,"Bonjour");
	prnt->EndDoc();
	//   Print();
}
//---------------------------------------------------------------------------

