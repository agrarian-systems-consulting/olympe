//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <values.h>
#include <Printers.hpp>
#pragma hdrstop

#include "Olympe.hse"
#include "Olympedec.h"
#include "LesClassesApp.h"

#include "TVDico.h"
#include "Resultat.h"
#include "Format.h"
#include "Forme01.h"
#include "AgriSaisie.h"

//#include "ResGraphLegende.h"
#include "ResGraph.h"
#include "CL_Trad.h"
#include "Aide.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TResGraphFrm *ResGraphFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TResGraphFrm::TResGraphFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::FormCreate(TObject *Sender)
{
	int n;
	Coul=0;
	LesCouleurs[Coul++]=clRed; //1
	LesCouleurs[Coul++]=clBlue;
	LesCouleurs[Coul++]=clGreen;
	LesCouleurs[Coul++]=clPurple;
	LesCouleurs[Coul++]=clMaroon;//5
	LesCouleurs[Coul++]=clNavy;
	LesCouleurs[Coul++]=clOlive;
	LesCouleurs[Coul++]=clLime;
	LesCouleurs[Coul++]=clFuchsia;
	LesCouleurs[Coul++]=clTeal;//10
	CoulMax=Coul;
	n=0;
	LesMotifs[n++]=bsSolid;
	LesMotifs[n++]=bsHorizontal;
	LesMotifs[n++]=bsVertical;
	LesMotifs[n++]=bsCross;
	LesMotifs[n++]=bsDiagCross;
	LesMotifs[n++]=bsBDiagonal;
	LesMotifs[n++]=bsFDiagonal;
	MotifMax=n;

}
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::FormActivate(TObject *Sender)
{
	if(Origine==0)
	{
//	    Caption=AgriEnCours->NomVC();
		LeCanvas=Canvas;
		TrouveMinMax();
		Origine=1;
	}
	LaWidth=Width-PCGaucheDroit->Width-10;
	LaHeight=Height;

//	Dessiner();

}
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::FormResize(TObject *Sender)
{

//    ShowMessage("FormResize Res");
	TrouveMinMax();
	PCGaucheDroit->Left= ResGraphFrm->Width-PCGaucheDroit->Width-10;
	GBBas->Left= ResGraphFrm->Width-GBBas->Width-10;
	LaWidth=Width-PCGaucheDroit->Width-10;
	LaHeight=Height;
	Dessiner();

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::TrouveMinMax(void)
{
	int nbUnite;
	int digits;

	EditMaxG->Text=" ";
	EditMinG->Text=" ";

	EditMaxD->Text=" ";
	EditMinD->Text=" ";

	if(ResultatFrm->LBGauche->Items->Count>0)
	{
		TrouveMinMax1(ResultatFrm->LBGauche,VMinG,VMaxG);

		digits=0;if(VMaxG<100) digits=2;
		EditMaxG->Text=FloatToStrF((double)VMaxG,ffNumber,7,digits);
		digits=0;if(VMinG<100) digits=2;
		EditMinG->Text=FloatToStrF((double)VMinG,ffNumber,7,digits);

		// prendre des nombres ronds
		UniteG=TrouveUnite('G');

		nbUnite=VMaxG/UniteG;
		VMaxG=(nbUnite+1) *UniteG;

		nbUnite=VMinG/UniteG;
		VMinG=(nbUnite) *UniteG;

		EditMaxG->Text=FloatToStrF((double)VMaxG,ffNumber,7,digits);
		EditMinG->Text=FloatToStrF((double)VMinG,ffNumber,7,digits);
	}
	if(ResultatFrm->LBDroit->Items->Count>0)
	{
		TrouveMinMax1(ResultatFrm->LBDroit, VMinD,VMaxD);

		digits=0;if(VMaxD<100) digits=2;
		EditMaxD->Text=FloatToStrF((double)VMaxD,ffNumber,7,digits);
		digits=0;if(VMinD<100) digits=2;
		EditMinD->Text=FloatToStrF((double)VMinD,ffNumber,7,digits);

		// prendre des nombres ronds
		UniteD=TrouveUnite('D');

		nbUnite=VMaxD/UniteD;
		VMaxD=(nbUnite+1) *UniteD;

		nbUnite=VMinD/UniteD;
		VMinD=(nbUnite) *UniteD;

		EditMaxD->Text=FloatToStrF((double)VMaxD,ffNumber,7,digits);
		EditMinD->Text=FloatToStrF((double)VMinD,ffNumber,7,digits);
	}

}
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::TrouveMinMax1(TListBox *lb,float &vMin,float &vMax)
{
	int i,n;
	CL_Elt *elt;

	vMin=MAXFLOAT;
	vMax=MINFLOAT;

	for(i=0;i<lb->Items->Count;i++)
	{
		elt=(CL_Elt*)lb->Items->Objects[i];
		for(n=0;n<N_X;n++)
		{
			if(elt->Valeur[n] > vMax) vMax=elt->Valeur[n];
			if(elt->Valeur[n] < vMin) vMin=elt->Valeur[n];
		}
	}
	if(vMin>=vMax)
	{
		vMax+=vMin*0.001;
		vMin-=vMax*0.001;
	}
}

//...........
//ScrollBar Axe de Gauche
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::ScrollBarMaxGScroll(TObject *Sender,
		TScrollCode ScrollCode, int &ScrollPos)
{
	if(ScrollCode==scLineUp) VMaxG+=UniteG;
	if(ScrollCode==scLineDown)
	{
		if(VMaxG-UniteG<=VMinG)return;
		VMaxG-=UniteG;
	}
	EditMaxG->Text=VMaxG;
	Dessiner();
}
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::ScrollBarMinGScroll(TObject *Sender,
		TScrollCode ScrollCode, int &ScrollPos)
{
	if(ScrollCode==scLineUp)
	{
		if( VMinG+UniteG>=VMaxG) return;
		VMinG+=UniteG;
	}
	if(ScrollCode==scLineDown) VMinG-=UniteG;

	EditMinG->Text=VMinG;
	Dessiner();
}
//...........
//ScrollBar Axe de Droite
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::ScrollBarMaxDScroll(TObject *Sender,
		TScrollCode ScrollCode, int &ScrollPos)
{
	if(ScrollCode==scLineUp) VMaxD+=UniteD;
	if(ScrollCode==scLineDown)
	{
		if(VMaxD-UniteD<=VMinD)return;
		VMaxD-=UniteD;
	}
	EditMaxD->Text=VMaxD;
	Dessiner();
}
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::ScrollBarMinDScroll(TObject *Sender,
		TScrollCode ScrollCode, int &ScrollPos)
{
	if(ScrollCode==scLineUp)
	{
		if( VMinD+UniteD>=VMaxD) return;
		VMinD+=UniteD;
	}
	if(ScrollCode==scLineDown) VMinD-=UniteD;

	EditMinD->Text=VMinD;
	Dessiner();

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//.........
//---------------------------------------------------------------------------
float __fastcall TResGraphFrm::TrouveUnite(char axe)
{
	int i,j;
	float vMin,vMax;
	int unite;
	if(axe=='G')
	{
		vMin=ValeurDe(EditMinG->Text);
		vMax=ValeurDe(EditMaxG->Text);
	}
	else //axe=D
	{
		vMin=ValeurDe(EditMinD->Text);
		vMax=ValeurDe(EditMaxD->Text);
	}
	i=0;
	unite=(vMax-vMin)*0.05;
	if(unite==0) unite=10;

	while(unite >10)
	{
		unite/=10;
		i++;
	}
	for(j=0;j<i;j++)
	unite*=10;
	return unite;
}
//---------------------------------------------------------------------------
float __fastcall TResGraphFrm::ValeurDe(AnsiString s)
{
	return Forme0Frm->ValeurDe(s);
	/*
	 int c;
	 int n;
	 char car;
	 char chaine[50];
	 s=s.Trim();
	 if(s=="" ||s==" ") return 0.;
	 c=0;
	 for(n=1;n<s.Length()+1;n++)
	 {
	 car=s[n];
	 if     (car>='0' && car<='9')      chaine[c++]  =car;
	 else if(car=='.'  ||  car==',')    chaine[c++] ='.';
	 else if(car=='-'  &&  c==0)        chaine[c++]  ='-';
	 }
	 chaine[c]=0;
	 s=AnsiString(chaine);
	 return s.ToDouble();
	 */
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::Dessiner(void)
{
	int epaisseur;
	//coordonnes de l'ecran d'affichage
	// l'ecran fait 400*276
	// cf papier quadrille
	LEcran=400;
	HEcran=276;

	XGauche=40;
//    XDroit= 370;
	XDroit= 340;

	YBas= 30;
	YHaut= 230;
	Intervalle=(XDroit-XGauche)/N_X;

	LarHisto=(XDroit-XGauche)/(N_X+1);
	LarHisto*=0.9;
	// tout l'ecran clInfoBk
	LeCanvas->Pen->Style=psClear;
	LeCanvas->Brush->Color=clInfoBk;
	LeCanvas->Brush->Style=bsSolid;
	LeCanvas->Rectangle(0,0,LaWidth,LaHeight);
	//Axe Horizontal
	LeCanvas->Brush->Color=clBlack;

	TraitHor(YBas,XGauche,XDroit,2);
	TraitHor(YHaut,XGauche,XDroit,1);

	//Axes Verticaux  Gauche
	epaisseur=1;if(ResultatFrm->LBGauche->Items->Count>0) epaisseur=2;
	TraitVer(XGauche,YBas,YHaut,epaisseur);
	//                Droite
	epaisseur=1;if(ResultatFrm->LBDroit->Items->Count>0) epaisseur=2;
	TraitVer(XDroit ,YBas,YHaut,epaisseur);//1 ou 2

	EchelleVer();
	AffAnnees(AnDebut);

//	AffAnnees(AgriEnCours->DefSim->An_0);
	// switch etc on peut avoir courbe histo histo empilé
	// à drote à gauche

	//LesCourbes ou Histo
	Coul=0;
	Motif=0;
	if(ResultatFrm->LBGauche->Items->Count>0)
	{
		switch(TypeCourbeG)
		{
			case COURBE:
			AffLesCourbes(ResultatFrm->LBGauche,VMinG,VMaxG);break;
			case HISTO:
			AffLesHisto(ResultatFrm->LBGauche,VMinG,VMaxG);break;
		}
	}
	if(ResultatFrm->LBDroit->Items->Count>0)
	{
		switch(TypeCourbeD)
		{
			case COURBE:
			AffLesCourbes(ResultatFrm->LBDroit,VMinD,VMaxD);break;
			case HISTO:
			AffLesHisto(ResultatFrm->LBDroit,VMinD,VMaxD);break;
		}
	}

	//Légende
	Coul=0;
	LeCanvas->Brush->Color=clInfoBk;
	Legende(ResultatFrm->LBGauche,XGauche);
	Legende(ResultatFrm->LBDroit,LEcran/2+XGauche);
}
// attention pour la légende
// y est en coordonnees de l'ecran 0 en haut

//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::Legende(TListBox *lb,float xGauche)
{
	int n;
	float y;
	float deltaY=12; //15;
	float xTrait;
	float lonTrait=40;
	AnsiString asNom;
//CL_Elt *elt;

//float z;
	if(lb->Items->Count==0) return;

	LeCanvas->Font->Color=clBlack;
	LeCanvas->Font->Name="Arial";
	LeCanvas->Font->Size=7;//8;

	LeCanvas->Pen->Style=psSolid;
	LeCanvas->Pen->Width =2;
	xTrait=xGauche+90;
	y=1;
	for(n=0;n<lb->Items->Count;n++)
	{
		LeCanvas->Pen->Color=(TColor)LesCouleurs[Coul++];
//    	elt=(CL_Elt*)lb->Items->Objects[n];
		//trait de la couleur de l'élément
		LeCanvas->MoveTo(Xde(xTrait),y+deltaY/2);
		LeCanvas->LineTo(Xde(xTrait+lonTrait),y+deltaY/2);
		//nom de l'élément
		asNom=lb->Items->Strings[n];
		/*
		 switch(Nature)
		 {
		 case AGRI:        asNom=elt->Donne_Nom();break;
		 case COMPARAISON: asNom=lb->Items->Strings[n];break;

		 }
		 */
		// a imprimer et tester
//        LeCanvas->Pen->Pos(Xde(xGauche),y); // ne donne rien
		LeCanvas->TextOut(Xde(xGauche),y,asNom);
		y+=deltaY;
	}

	LeCanvas->Pen->Color=clBlack;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//           UTILITAIRE de CONVERSION
//---------------------------------------------------------------------------
float __fastcall TResGraphFrm::Xde(float x)
{
	// toutes les coordonnees sont exprimees en fonction d'un ecran 40*27.6
	x=(x*LaWidth)/LEcran;
	return x;
}
//---------------------------------------------------------------------------
float __fastcall TResGraphFrm::Yde(float y)
{
	int h;
//    h=LaHeight-PanelBas->Height;
	h=LaHeight;
	y= h-(y*h)/HEcran;

	// toutes les coordonnees sont exprimees en fonction d'un ecran 40*27.6
	// l'axe des y commence en bas
	return y;
}
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::TraitHor(float y0, float x0,float x1,float width)
{
	LeCanvas->Pen->Style=psSolid;
	LeCanvas->Pen->Width = width;

	LeCanvas->MoveTo(Xde(x0),Yde(y0));
	LeCanvas->LineTo(Xde(x1),Yde(y0));
}
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::TraitVer(float x0, float y0,float y1,float width)
{
	LeCanvas->Pen->Style=psSolid;
	LeCanvas->Pen->Width =width;

	LeCanvas->MoveTo(Xde(x0),Yde(y0));
	LeCanvas->LineTo(Xde(x0),Yde(y1));
}
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::AffAnnees(int an0)
{
	int n;
	float x;
	float hBar=3;
	int an;
	AnsiString nomPolice;
	SetTextAlign(LeCanvas->Handle,TA_CENTER);

	LeCanvas->Brush->Color=clInfoBk;
	LeCanvas->Font->Name="Arial";
	LeCanvas->Font->Size=8; //7;

	x=XGauche+Intervalle/2;
	an=an0;
	for(n=0;n<N_X;n++)
	{
		TraitVer(x,YBas,YBas-hBar,2);
		LeCanvas->TextOut(Xde(x),Yde(YBas-1),an );
		x+=Intervalle;
		an++;
	}
}
/*
 //---------------------------------------------------------------------------
 void __fastcall TResGraphFrm::AffAnnees(int an0)
 {
 int n;
 float x;
 float hBar=3;
 int an;
 AnsiString nomPolice;
 SetTextAlign(LeCanvas->Handle,TA_CENTER);

 LeCanvas->Brush->Color=clInfoBk;
 LeCanvas->Font->Name="Arial";
 LeCanvas->Font->Size=8;//7;

 x=XGauche;
 an=an0;
 for(n=0;n<N_X;n++)
 {
 TraitVer(x,YBas,YBas-hBar,2);
 LeCanvas->TextOut(Xde(x),Yde(YBas-1),an );
 x+=(XDroit-XGauche)/(N_X-1);
 an++;
 }
 }
 */
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::EchelleVer(void)
{
	AnsiString svaleur;
	AnsiString nomPolice;
	AnsiString unite;
	CL_Elt *elt;
	SetTextAlign(LeCanvas->Handle,TA_RIGHT);

	LeCanvas->Brush->Color=clInfoBk;
	LeCanvas->Font->Name="Arial";
	LeCanvas->Font->Size=8; //7;
	LeCanvas->Font->Color=clBlack;

	if(ResultatFrm->LBGauche->Items->Count>0)
	{
		//Unité
		SetTextAlign(LeCanvas->Handle,TA_CENTER);
		elt=(CL_Elt*)ResultatFrm->LBGauche->Items->Objects[0];
		unite=elt->Donne_Unite();
		LeCanvas->Font->Size=10;
		LeCanvas->TextOut(Xde(XGauche),Yde(YHaut+10),unite);

		AxeOrdonnee('G');
	}
	if(ResultatFrm->LBDroit->Items->Count>0)
	{
		//Unite
		SetTextAlign(LeCanvas->Handle,TA_CENTER);
		elt=(CL_Elt*)ResultatFrm->LBDroit->Items->Objects[0];
		unite=elt->Donne_Unite();
		LeCanvas->Font->Size=10;
		LeCanvas->TextOut(Xde(XDroit),Yde(YHaut+10),unite);

		AxeOrdonnee('D');
	}
}
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::AxeOrdonnee(char position)
{
	int x,y;
	float vMin,vMax,val,unite;
	int n,pas;
	float z;
	LeCanvas->Font->Size=8; //7;
	if(position=='G')
	{
		SetTextAlign(LeCanvas->Handle,TA_RIGHT);
		x=XGauche;
		vMin=VMinG;
		vMax=VMaxG;
		unite=UniteG;
	}
	else //D
	{
		SetTextAlign(LeCanvas->Handle,TA_LEFT);
		x=XDroit;
		vMin=VMinD;
		vMax=VMaxD;
		unite=UniteD;
	}
	//bas
	Ordonnee(position,x,YBas+8,vMin);
	//haut
	Ordonnee(position,x,YHaut,vMax);

	n=(vMax-vMin)/unite;
	pas=n/5;
	if(pas==0)pas=1;
	z=unite*(YHaut-YBas)/(vMax-vMin);

	val=vMin+unite*pas;
	y=YBas+pas*z;
	while(1)
	{
		Ordonnee(position,x,y,val);

		y+=pas*z;
		val+=pas*unite;
		if(y>YHaut) break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::Ordonnee(char position,float x,float y,float val)
{
	float larg=3;
	int digits=0;
	AnsiString sValeur;
	float x1,x2;
	if(position=='G') {x1=x-larg; x2=x-2;}
	else {x1=x+larg; x2=x+2;}
	TraitHor(y,x,x1,1);
	sValeur=FloatToStrF((double)val,ffNumber,7,digits);
	LeCanvas->TextOut(Xde(x2),Yde(y),sValeur );
}
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::AffLesCourbes(TListBox *lb,float vMin,float vMax)
{
	int i;
	CL_Elt *elt;
	LeCanvas->Pen->Style=psSolid;
	LeCanvas->Pen->Width =1.75; //2;

	for(i=0;i<lb->Items->Count;i++)
	{
		LeCanvas->Pen->Color=(TColor)LesCouleurs[Coul];
		LeCanvas->Brush->Color=(TColor)LesCouleurs[Coul];
		Coul++;
		elt=(CL_Elt*)lb->Items->Objects[i];
		Courbe(elt->Valeur,vMin,vMax);
	}
	LeCanvas->Pen->Color=clBlack;

}
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::Courbe(float *valeur,float vMin,float vMax)
{
	float x,y;
	int n;
	float delta=1.5;
	TPoint points[N_X];
	x=XGauche+Intervalle/2;
	y=(valeur[0]-vMin)*(YHaut-YBas)/(vMax-vMin)+YBas;
	n=0;
	points[n].x=Xde(x);
	points[n].y=Yde(y);
	LeCanvas->Ellipse(Xde(x-delta),Yde(y+delta),Xde(x+delta),Yde(y-delta));
	for(n=1;n<N_X;n++)
	{
		x+= Intervalle;
		y=(valeur[n]-vMin)*(YHaut-YBas)/(vMax-vMin)+YBas;

		points[n].x=Xde(x);
		points[n].y=Yde(y);
		LeCanvas->Ellipse(Xde(x-delta),Yde(y+delta),Xde(x+delta),Yde(y-delta));
	}
	LeCanvas->Polyline(points,N_X-1);
}

//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::AffLesHisto(TListBox *lb,float vMin,float vMax)
{
	int i;
	CL_Elt *elt;
	float larHisto;
	LeCanvas->Pen->Style=psSolid;
	LeCanvas->Pen->Width =2;
	larHisto=LarHisto/lb->Items->Count;
	for(i=0;i<lb->Items->Count;i++)
	{
		LeCanvas->Pen->Color=clBlack;
		LeCanvas->Brush->Color=(TColor)LesCouleurs[Coul++];
		if(Coul==CoulMax) {Coul=0;Motif++;}
		LeCanvas->Brush->Style=(TBrushStyle)LesMotifs[Motif];
		if(Motif==MotifMax) Motif=0;
		elt=(CL_Elt*)lb->Items->Objects[i];
		Histo(elt->Valeur,vMin,vMax,i,larHisto);
	}
	LeCanvas->Pen->Color=clBlack;

}
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::Histo(float *valeur,float vMin,float vMax,int i,float larHisto)
{
	float x,y;
	int n;
	float ecart=((XDroit-XGauche)/(N_X+1))*0.1;
//	x=XGauche+i*larHisto;
	x=XGauche+ecart+i*larHisto;
	y=(valeur[0]-vMin)*(YHaut-YBas)/(vMax-vMin)+YBas;
	LeCanvas->Rectangle(Xde(x),Yde(y),Xde(x+larHisto),Yde(YBas));

	for(n=1;n<N_X;n++)
	{
//    	x+=(XDroit-XGauche)/(N_X-1);
		x+=Intervalle;
		y=(valeur[n]-vMin)*(YHaut-YBas)/(vMax-vMin)+YBas;
		LeCanvas->Rectangle(Xde(x),Yde(y),Xde(x+larHisto),Yde(YBas));
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::BtTableauClick(TObject *Sender)
{
	int i,nbElt;
	AnsiString titre;
	AnsiString as;
	CL_Elt *elt;
	int an_0=AgriEnCours->DefSim->An_0;
	nbElt=ResultatFrm->LBGauche->Items->Count
	+ResultatFrm->LBDroit->Items->Count;
//    titre=Chart->Title->Text->Text;

	Forme01Frm->Origine=0;
	Forme01Frm->UtilisePar="Graph";
	Forme01Frm->Show();
	// An_0 à voir
	Forme01Frm->IniGrilleStandard(Caption,N_X,nbElt,an_0);
	for(i=0;i<ResultatFrm->LBGauche->Items->Count;i++)
	{
		elt=(CL_Elt*)ResultatFrm->LBGauche->Items->Objects[i];
		as= ResultatFrm->LBGauche->Items->Strings[i];
		Forme01Frm->EcrireLigne(as,elt->Valeur);
	}
	for(i=0;i<ResultatFrm->LBDroit->Items->Count;i++)
	{
		elt=(CL_Elt*)ResultatFrm->LBDroit->Items->Objects[i];
		as= ResultatFrm->LBDroit->Items->Strings[i];
		Forme01Frm->EcrireLigne(as,elt->Valeur);
	}
}
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::BtImpClick(TObject *Sender)
{
	float w,h;
//  TPrinter Prntr = Printer();
//  TRect r = Rect(200,200,Prntr->PageWidth–200,Prntr->PageHeight – 200);
	LeCanvas=Printer()->Canvas;
	Printer()->Orientation=poLandscape;
	Printer()->BeginDoc();
//    LeCanvas=Printer()->Canvas;
	w=LaWidth;
	h=LaHeight;
	LaWidth=Printer()->PageWidth;
	LaHeight=Printer()->PageHeight;
	Dessiner();

	//  Printer()->Canvas->TextRect(r, 200, 200, Memo1->Lines->Text);
	Printer()->EndDoc();
	// je restaure
	LaWidth=w;
	LaHeight=h;
	LeCanvas=Canvas;

}
// Histo ou Courbe
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::SpBtCourbeDClick(TObject *Sender)
{
	TypeCourbeD=COURBE;
	Dessiner();
}
//---------------------------------------------------------------------------

void __fastcall TResGraphFrm::SpBtHistoDClick(TObject *Sender)
{
	TypeCourbeD=HISTO;
	Dessiner();
}
//---------------------------------------------------------------------------

void __fastcall TResGraphFrm::SpBtCourbeGClick(TObject *Sender)
{
	TypeCourbeG=COURBE;
	Dessiner();
}
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::SpBtHistoGClick(TObject *Sender)
{
	TypeCourbeG=HISTO;
	Dessiner();
}
//---------------------------------------------------------------------------

void __fastcall TResGraphFrm::FormClose(TObject *Sender,
		TCloseAction &Action)
{
//    TVDicoFrm->Visible=true;                     //011009
}
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::EdSupDDblClick(TObject *Sender)
{
	BorneSupD=ValeurDe(EdSupD->Text);
}
//---------------------------------------------------------------------------

void __fastcall TResGraphFrm::EdInfDDblClick(TObject *Sender)
{
	BorneInfD=ValeurDe(EdInfD->Text);
}
//---------------------------------------------------------------------------

void __fastcall TResGraphFrm::EdSupGDblClick(TObject *Sender)
{
	BorneSupG=ValeurDe(EdSupG->Text);
}
//---------------------------------------------------------------------------
void __fastcall TResGraphFrm::EdInfGChange(TObject *Sender)
{
	BorneInfG=ValeurDe(EdInfG->Text);

}
//---------------------------------------------------------------------------

void __fastcall TResGraphFrm::ChBBorneClick(TObject *Sender)
{
	float y;
	AnsiString text;
	TCheckBox *chB;
	float borne;
	chB=(TCheckBox*)Sender;
	if(Sender==ChBSupG) text=EdSupG->Text;
	else if(Sender ==ChBInfG) text=EdInfG->Text;
	else if(Sender ==ChBSupD) text=EdSupD->Text;
	else if(Sender ==ChBInfD) text=EdInfD->Text;

	if(text.Length()==0) return;

	if(chB->Checked==false)
	LeCanvas->Brush->Color=clInfoBk;
	else
	LeCanvas->Brush->Color=clBlack;

	borne=ValeurDe(text);
	y=(borne-VMinG)*(YHaut-YBas)/(VMaxG-VMinG)+YBas;
	TraitHor(y,XGauche,XDroit,2);

	LeCanvas->Brush->Color=clBlack;
}
//---------------------------------------------------------------------------
//--------------------------------------------
void TResGraphFrm::IniCaption(void) {
	BtImp->Caption = LC_BtImp;
	GBBornesG->Caption = LC_GBBornesG;
	GBBornesD->Caption = LC_GBBornesG;
	TabSheetD->Caption = LC_TabSheetD;
	GBEchelleG->Caption = LC_GBEchelleG;
	GBEchelleD->Caption = LC_GBEchelleG;
	TabSheetG->Caption = LC_TabSheetG;
	LabMAXG->Caption = LC_LabMAXG;
	LabMAXD->Caption = LC_LabMAXG;
	LabMING->Caption = LC_LabMING;
	LabMIND->Caption = LC_LabMING;
	BtTableau->Caption = LC_BtTableau;
}
//--------------------------------------------
void TResGraphFrm::TexteCaption(void) {
	LC_BtImp = T->TrouveCaption("ResGraph", "LC_BtImp");
	LC_GBBornesG = T->TrouveCaption("ResGraph", "LC_GBBornesG");
	LC_TabSheetD = T->TrouveCaption("ResGraph", "LC_TabSheetD");
	LC_GBEchelleG = T->TrouveCaption("ResGraph", "LC_GBEchelleG");
	LC_TabSheetG = T->TrouveCaption("CL_Trad", "LC_TabSheetG");
	LC_LabMAXG = T->TrouveCaption("ResGraph", "LC_LabMAXG");
	LC_LabMING = T->TrouveCaption("ResGraph", "LC_LabMING");
	LC_BtTableau = T->TrouveCaption("ResGraph", "LC_BtTableau");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TResGraphFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

