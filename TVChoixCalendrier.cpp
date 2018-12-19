//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Atelier.h"
#include "CL_Matrice.h"
#include "CL_Matrice.h"
#include "CL_Trad.h"
#include "TVChoixCalendrier.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TVChoix"
#pragma resource "*.dfm"
TTVChoixCalendrierFrm *TVChoixCalendrierFrm;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TTVChoixCalendrierFrm::TTVChoixCalendrierFrm(TComponent* Owner) :
		TTVChoixFrm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TTVChoixCalendrierFrm::TVDblClick(TObject *Sender)
{
	int n;
	int rep;
	TTreeNode *elt;
	CL_Atelier *atelier,*atelier0;
	CL_Calendrier *calendrier0;
	CL_Periode *periode;
	CL_BesTrav *besTrav,*besTrav0;
	float totHeure,totHeureAn[20];

	elt=TV->Selected;

	if(elt==NULL) return;
	if(elt->Level==0) return;
	if(elt->Text=="[...]") return;

	atelier0=(CL_Atelier*)elt->Data;
	// je choisis l'atelier dont je veux copier le calendrier

	n=AtelierFrm->LBCalendrier->ItemIndex;
	calendrier0=(CL_Calendrier*)AtelierFrm->LBCalendrier->Items->Objects[n];
	//je sais pour quel type de calendrier(nom, nb periodes, jours dispo..) je veux recopier
	if(calendrier0==NULL)
	{
		ShowMessage("Pas de calendrier à copier");
		return;
	}
	besTrav0=atelier0->V_BesTrav->trouve(calendrier0->No);
	// je connais les besoins en travail a recopier( heures par periode du calendrier)
	if(besTrav0==NULL)
	{
		ShowMessage("Pas de besoins en travail");
		return;
	}

	if(besTrav0->NbPeriodeCal!=calendrier0->V_Periode->Nbelt)
	{
		ShowMessage("Incohérence dans le nombre de périodes");
		return;
	}
	// le copier et l'introduire dans l'atelier en cours
	// verifier qu'il n'existe pas

	atelier= AtelierFrm->Atelier;

	//il faut recopier les besoins de atelier0 dans atelier (celui qui est affiché)
	for(n=0;n<atelier->V_BesTrav->Nbelt;n++)
	{
		besTrav=atelier->V_BesTrav->Vecteur[n];
		if(besTrav->Calendrier==calendrier0)
		{
			rep=MessageBox(Handle," Il existe déjà !  Je Remplace?","A REMPLACER",MB_YESNO);
			if(rep==IDNO) return;
			else
			{
				atelier->V_BesTrav->sup(besTrav);
				Forme00Frm->VideGrille(AtelierFrm->GrilleTravail); //180105
			}
		}
	}
	besTrav=new CL_BesTrav(besTrav0);
	atelier->V_BesTrav->insSans(besTrav);

	for(n=0;n<calendrier0->V_Periode->Nbelt;n++) //180105
	{
		periode=calendrier0->V_Periode->Vecteur[n];
		AtelierFrm->GrilleTravail->Cells[0][n+1]=periode->Nom;
	}

	//l'afficher
	besTrav->ecrireGrille(AtelierFrm->GrilleTravail);
	besTrav->Totalise(totHeure,totHeureAn);
//    if(Atelier->Espece)
//        totHeure=AtelierMDetailPerenneFrm->TotalHeure(Atelier->Espece,totHeureAn);
	AtelierFrm->EdTotalBesoins->Text=AnsiString(totHeure);

	AtelierFrm->BesTrav=besTrav;//211204
	AtelierFrm->GrilleModif[AtelierFrm->GrilleTravail->Tag]=true;
	AtelierFrm->LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------
//--------------------------------------------
void TTVChoixCalendrierFrm::TexteCaption(void) {
	TVChoixCalendrierFrm->Caption = T->LC_GBAtelier;
}
//--------------------------------------------
void TTVChoixCalendrierFrm::IniCaption(void) {
	LC_GBAtelier = T->TrouveCaption("CL_Trad", "LC_GBAtelier");
}
//--------------------------------------------

