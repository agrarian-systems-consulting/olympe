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

//#include "Graph.h"   //???
#include "CL_SousPeriode.h"
#include "CL_Matrice.h"
#include "CL_BesTravAtelier.h"

#include "TravCal.h"
//#include "TravGraph.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//#pragma resource "*.dfm"
//---------------------------------------------------------------------------
bool __fastcall TTravCalFrm::VerifCompletude(void)
{
	bool rep;
	int repMB;
	bool erreur;
	erreur=false;
	ErreurFrm->Edit->Clear();
	ErreurFrm->Edit->Lines->Add(Calendrier->Nom.c_str());

	rep=Completude(Agri->V_Culture); if(rep==false)erreur=true;
	rep=Completude(Agri->V_Animaux); if(rep==false)erreur=true;
	rep=Completude(Agri->V_Verger); if(rep==false)erreur=true;
	rep=Completude(Agri->V_Vivrier); if(rep==false)erreur=true;

	if(erreur==false)
	return true;

	else
	{
//		Forme00Frm->AutreDonnee=false; //pour eviter effacement cf forme00Activate  260509

		ErreurFrm->Show();
//" A executer ?"
		repMB=MessageBox(Handle,L_A_Executer.c_str(),"DONNEES INCOMPLETES",
				MB_YESNO|MB_ICONEXCLAMATION);
		if(repMB==IDYES)
		return true;
		else
		return false;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TTravCalFrm::Completude(CL_Vecteur<CL_Valeur>*vecteur)
{
	int c,i;
	bool trouve,rep;
	CL_Valeur *valeur;
	CL_Atelier *atelier;
	CL_BesTrav *besTrav;
	CL_Matrice *matBesoins;
	AnsiString as;
	rep=true;
	for(c=0;c<vecteur->Nbelt;c++)
	{
		valeur=vecteur->Vecteur[c];
		atelier=valeur->Atelier;
		trouve=false;

		//chercher matrice des besoins
		for(i=0;i<atelier->V_BesTrav->Nbelt;i++)
		{
			besTrav=atelier->V_BesTrav->Vecteur[i];
			if(besTrav->Calendrier==Calendrier)
			{
				trouve=true;
				matBesoins=besTrav->Besoins;
				if(matBesoins->EstVide()==true)
				{

					as=atelier->Nom+"  "+" tous les besoins sont nuls";
					ErreurFrm->Edit->Lines->Add(as.c_str());
					rep=false;
				}
			}
		}
		if(trouve==false)
		{
			as=atelier->Nom+"\tPas de Besoins en travail";
			ErreurFrm->Edit->Lines->Add(as.c_str());
			rep=false;
		}
	}
	return rep;
}
//---------------------------------------------------------------------------
bool __fastcall TTravCalFrm::Completude(CL_Vecteur<CL_Verger>*vecteur)
{
	int c,i;
	bool trouve,rep;
	CL_Verger *verger;
	CL_Atelier *atelier;
	CL_BesTrav *besTrav;
	CL_Matrice *matBesoins;
	AnsiString as;
	rep=true;
	for(c=0;c<vecteur->Nbelt;c++)
	{
		verger=vecteur->Vecteur[c];
		atelier=verger->Atelier;
		trouve=false;

		//chercher matrice des besoins
		for(i=0;i<atelier->V_BesTrav->Nbelt;i++)
		{
			besTrav=atelier->V_BesTrav->Vecteur[i];
			if(besTrav->Calendrier==Calendrier)
			{
				trouve=true;
				matBesoins=besTrav->Besoins;
				if(matBesoins->EstVide()==true)
				{

					as=atelier->Nom+"  "+" tous les besoins sont nuls";
					ErreurFrm->Edit->Lines->Add(as.c_str());
					rep=false;
				}
			}
		}
		if(trouve==false)
		{
			as=atelier->Nom+"\t"+"Pas de Besoins en travail";
			ErreurFrm->Edit->Lines->Add(as.c_str());
			rep=false;
		}
	}
	return rep;
}
//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::CalculBesPeriode(int noAn)
{

	//creer matrice pour mettre les besoins par période
	//rechercher le nb ligne: culture animaux perennes qui ont besoins en travail
	//   définis pour le calendrier en cours
	//   Calendrier provient de LB  dans TravCal

	LstBesAtelier= new TList;
	//cultures animaux
	CalculBesAnnuelles(Agri->V_Culture,noAn);//090306
	CalculBesAnnuelles(Agri->V_Animaux,noAn);
	// verger vivrier
	CalculBesPerennes(Agri->V_Verger,noAn);
	CalculBesPerennes(Agri->V_Vivrier,noAn);
	//total besoins +...
	CalculDispo();
}
//cultures animaux
//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::CalculBesAnnuelles(CL_Vecteur<CL_Valeur>*vecteur,int noAn)
{
	int c,i,j,n;
	int per;
	int an;
	bool trouve;
	float tot;
	int nbPeriode,nbSousPeriode;
	CL_Valeur *valeur;
	CL_Atelier *atelier;
	CL_BesTrav *besTrav;
	CL_Matrice *matBesoins;

	CL_Periode *periode;
	CL_SousPeriode *sPeriode;
	float pcent;

	float surface[3];
	float *besParPer;
	CL_BesTravAtelier *besTravAtelier;
//test a sup
//float besPer[20];
	an=noAn;//CBAn->ItemIndex;
	nbPeriode=Calendrier->V_Periode->Nbelt;
	besParPer=new float[nbPeriode];// a deleter
	nbSousPeriode=LstSousPeriodes->Count;

	// pour chaque culture  c comme culture
	for(c=0;c<vecteur->Nbelt;c++)
	{
		valeur=vecteur->Vecteur[c];
		atelier=valeur->Atelier;
		trouve=false;

		//chercher matrice des besoins
		for(i=0;i<atelier->V_BesTrav->Nbelt;i++)
		{
			besTrav=atelier->V_BesTrav->Vecteur[i];
			if(besTrav->Calendrier==Calendrier)
			{
				matBesoins=besTrav->Besoins;
				trouve=true;
				break;
			}
		}
		if(trouve==false) continue;

		//tenir compte des travaux faits l'année d'avant et l'année d'après
		if(an==0) surface[0]=valeur->Valeur[an];
		else surface[0]=valeur->Valeur[an-1];

		surface[1]=valeur->Valeur[an];

		if(an==N_X-1) surface[2]=valeur->Valeur[an];
		else surface[2]=valeur->Valeur[an+1];

		for(i=0,tot=0;i<3;i++)tot+=surface[i];
		if(tot==0) continue;

		besTravAtelier=new CL_BesTravAtelier(atelier,nbSousPeriode);
		LstBesAtelier->Add(besTravAtelier);
		//j'ai trouvé la matrice des besoins
		// colonne phases -1 0 1
		//ligne periodes

		//pour chaque période
		// calcul des besoins de la culture c à période i

		memset(besParPer,0,sizeof(float)*nbPeriode);
//        memset(besPer,0,sizeof(besPer));
		for(per=0;per<matBesoins->iX;per++)
		{
			//float val,bes;

			for(j=0;j<3;j++)// année avant pendant après
			{
				besParPer[per]+=surface[j]*matBesoins->val(per,2-j);
//110109                besPer[per]+=surface[j]*matBesoins->val(per,2-j);
			}
		}
		// répartir dans les sous périodes et conserver grace à LstBesSousPer
//        besSousPer=new float[nbSousPeriode];  // a deleter
//        memset(besSousPer,0,sizeof(float)*nbSousPeriode);

		for(n=0;n<LstSousPeriodes->Count;n++)
		{
			sPeriode=(CL_SousPeriode *)LstSousPeriodes->Items[n];
			for(int i=0;i<sPeriode->NPeriode;i++)
			{
				periode=sPeriode->LesPeriodes[i];
				pcent= sPeriode->LesPcent[i];
				//j=periode->No;  idiot->gros problème
//                besTravAtelier->besSousPeriode[n]+=besParPer[j]*pcent;
				besTravAtelier->besSousPeriode[n]+=besParPer[n]*pcent;
			}
		}
//        LstBesSousPer->Add(besSousPer);
	}

	delete []besParPer;
	return;
}
//verger vivrier
//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::CalculBesPerennes(CL_Vecteur<CL_Verger>*vecteur,int noAn)
{
	int c,i,j,n;
	int per;
	int an;
	bool trouve;
	int nbPeriode,nbSousPeriode;
	CL_Verger *verger;
	CL_Atelier *atelier;
	CL_BesTrav *besTrav;
	CL_Matrice *matBesoins;

	CL_Periode *periode;
	CL_SousPeriode *sPeriode;
	float pcent;

	float surface;
	int phase;
	float *besParPer;
	CL_BesTravAtelier *besTravAtelier;

//test
//float besPer[100];
	an=noAn;//CBAn->ItemIndex;
	nbPeriode=Calendrier->V_Periode->Nbelt;
	besParPer=new float[nbPeriode];// a deleter   c'est fait
	nbSousPeriode=LstSousPeriodes->Count;

	// pour chaque culture  c comme culture
	for(c=0;c<vecteur->Nbelt;c++)
	{
		verger=vecteur->Vecteur[c];
		atelier=verger->Atelier;
		trouve=false;

		//chercher matrice des besoins
		for(i=0;i<atelier->V_BesTrav->Nbelt;i++)
		{
			besTrav=atelier->V_BesTrav->Vecteur[i];
			if(besTrav->Calendrier==Calendrier)
			{
				matBesoins=besTrav->Besoins;
				trouve=true;
				break;
			}
		}
		if(trouve==false) continue;

		surface=verger->SurfaceAn[an];
		phase=verger->Phase[an];

		if(surface==0) continue;
		// pb   on peut trouver plusieurs fois le meme atelier
		// si plantation à date différente

		besTravAtelier=new CL_BesTravAtelier(atelier,nbSousPeriode);
		LstBesAtelier->Add(besTravAtelier);
		// a deleter c'est fait dans CalculBesPeriode

		//pour chaque période
		// calcul des besoins de la pérenne c à période i

		memset(besParPer,0,sizeof(float)*nbPeriode);
//        memset(besPer,0,sizeof(besPer));
		for(per=0;per<matBesoins->iX;per++)
		{
			besParPer[per]+=surface*matBesoins->val(per,phase);
//            besPer[per]+=surface*matBesoins->val(per,phase);
		}
		// répartir dans les sous périodes et conserver

		for(n=0;n<LstSousPeriodes->Count;n++)
		{
			sPeriode=(CL_SousPeriode *)LstSousPeriodes->Items[n];

			for(int i=0;i<sPeriode->NPeriode;i++)
			{
				periode=sPeriode->LesPeriodes[i];
				pcent= sPeriode->LesPcent[i];
				//j=periode->No;  idiot->gros problème
//!!!!!!                besTravAtelier->besSousPeriode[n]+=besParPer[j]*pcent;
				besTravAtelier->besSousPeriode[n]+=besParPer[n]*pcent;
			}
		}
	}

	delete []besParPer;
}
//---------------------------------------------------------------------------
void __fastcall TTravCalFrm::CalculDispo(void)
{
	int c,p,n,j;
	int nbPeriode,nbSousPeriode;
	int nbOuv;
	float *dispoParPer;
//float *besSousPer;
	float pcent;
	CL_Periode *periode;
	CL_SousPeriode *sPeriode;
	CL_BesTravAtelier *besTravAtelier;

	nbSousPeriode=LstSousPeriodes->Count;
	TotBesSousPer=new float[nbSousPeriode];// a deleter
	memset(TotBesSousPer,0,sizeof(float)*nbSousPeriode);
	DispoSousPer=new float[nbSousPeriode];
	memset(DispoSousPer,0,sizeof(float)*nbSousPeriode);
	TravNec=new float[nbSousPeriode];
	memset(TravNec,0,sizeof(float)*nbSousPeriode);

	//Calcul du total des besoins par sous période
//    for(c=0;c<LstBesSousPer->Count;c++)

	for(c=0;c<LstBesAtelier->Count;c++)
	{
		besTravAtelier=(CL_BesTravAtelier*)LstBesAtelier->Items[c];
		for(p=0;p<nbSousPeriode;p++)
		TotBesSousPer[p]+=besTravAtelier->besSousPeriode[p];
	}

	//Disponible par sous Periode
	nbPeriode=Calendrier->V_Periode->Nbelt;
	dispoParPer=new float[nbPeriode];
	memset(dispoParPer,0,sizeof(float)*nbPeriode);
	for( j=0;j<Calendrier->V_Periode->Nbelt;j++)
	{
		periode=Calendrier->V_Periode->Vecteur[j];
		dispoParPer[j]=periode->HDispo;
	}

	for(n=0;n<LstSousPeriodes->Count;n++)
	{
		sPeriode=(CL_SousPeriode *)LstSousPeriodes->Items[n];
		for(int i=0;i<sPeriode->NPeriode;i++)
		{
			periode=sPeriode->LesPeriodes[i];
			pcent= sPeriode->LesPcent[i];
			DispoSousPer[n]=periode->HDispo*pcent; //241108
		}
	}

	//Nb de travailleurs par sous periodes
	NbOuv=0;
	for(n=0;n<LstSousPeriodes->Count;n++)
	{
		if(DispoSousPer[n]<1) continue; //if(DispoSousPer[n]==0)
		TravNec[n]=TotBesSousPer[n]/DispoSousPer[n];
		nbOuv=TravNec[n]+1;
		if(NbOuv<nbOuv) NbOuv=nbOuv;
	}

}

