//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#include <iostream>
#include <fstream>
#pragma hdrstop
using namespace std;
#include "CL_Trad.h"
#include "Aide.h"

#include "MvtAnnee.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMvtAnneeFrm *MvtAnneeFrm;
extern CL_Trad *T;

/*
 A chaque cellule de la grille Inventaire
 est accrochée une classe CL_MvtAnnee
 qui contient les mouvements de l'année


 AU DEPART RIEN
 entrer  def animaux mettre a NULL les objets de la ligne
 inventaire
 creer mvtAn de N=0 avec Debut=
 choix animal
 afficher les grilles
 si mvtAn=NULL le creer

 aprés Ok
 mettre dans LstMvtAni
 DeGrMvtEntree
 Sortie
 Achat
 Vente
 pb pour ne et mort
 pour l'année N
 appeler mouvt(N)
 qui cree si necessaire mvtAn et informe Debut pour an suivant

 */

//---------------------------------------------------------------------------
__fastcall TMvtAnneeFrm::TMvtAnneeFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TMvtAnneeFrm::FormCreate(TObject *Sender)
{

	GrMvt->Cells[0][0]=L_Debut; //"Début";
	GrMvt->Cells[0][1]=L_Vente;//"Vente";
	GrMvt->Cells[0][2]=L_Achat;//"Achat";
	GrMvt->Cells[0][3]=L_Ne;//"Né";
	GrMvt->Cells[0][4]=L_Mort;//"Mort";
	GrMvt->Cells[0][5]=L_Entree;//"Entrée";
	GrMvt->Cells[0][6]=L_Sortie;//"Sortie";
	GrMvt->Cells[0][7]=L_Fin;//"Fin";
	Col0=3;//colonne ou est affiché la premiére année de simulation
}
//---------------------------------------------------------------------------
/*
 c=col0 correspond à An_0
 Vente achat mort in out sont les mouvements de l'année n  il y a N_X
 Effectif[n] effectif à la fin de l'année n  il y en a N_X+1
 Effectif[0] effectif au début de la simulation fin de An_0-1
 */
/// affiche la fenetre Mouvement
//---------------------------------------------------------------------------
void __fastcall TMvtAnneeFrm::FormActivate(TObject *Sender)
{
	int c,r;
	int an;
	CL_MvtAnnee *mvt;

	//reprendre paramètres de Troupeau
	An_0=TroupeauFrm->An_0;
	GrilleInv=TroupeauFrm->GrilleMvt;
	Agri=TroupeauFrm->Agri;

	r=GrilleInv->Row;
	c=GrilleInv->Col;

	InvAni=(CL_InvAni*)GrilleInv->Objects[0][r];
	N=c-Col0;//si c=col0 je suis en début de la simulation:An_0 N=0
	an=An_0+N;
	Caption=AnsiString(an);
	LabNom->Caption=InvAni->Animal->Nom;

	mvt=(CL_MvtAnnee*)GrilleInv->Objects[c][r];
	AffMvtAnnee(mvt);

}
//---------------------------------------------------------------------------
/*
 BtBnOKClick
 BtBnAnnulClick
 */
/// dans grille Mouvement
/// reprend le contenu des sous grilles vente achat etc aprés verif
///  et le met dans MvtAnnee (attaché à la cellule)
/// remplit grille de gauche (synthèse)
/// dans la grille inventaire
/// met dans la cellule à gauche( l'année d'après) l'effectif
/// MaJMvtAnnee
/// MvtAnnee est global et defini dans BtBnOKClick
/// pour tous les mouvements on connait effectif destination
///   ->rechercher et mettre à jour les mvtAnne
//---------------------------------------------------------------------------
void __fastcall TMvtAnneeFrm::BtBnOKClick(TObject *Sender)
{
	int effFin,effSortie;
///ofstream outfile("mvtAnnee.txt");
	int r,c;
	CL_MvtAnnee *mvt;
	CL_MvtAnnee *mvtTest;
	//230108
	mvtTest=(CL_MvtAnnee*)TroupeauFrm->GrilleMvt->Objects[Col0][3];

	if(LabMvtModif->Visible==false) return;
	TroupeauFrm->Erreur=false;

	TroupeauFrm->LabelModifie->Visible=true;

	// la  nouvelle information est dans GrilleMvt: je mets à zero MvtAnnee
	//pour verifier l'existence de prix
	// voir si controle à faire dans GrMvtClick

	c=N+3;
	r=TroupeauFrm->GrilleMvt->Row;
	mvt=(CL_MvtAnnee*)GrilleInv->Objects[c][r];
	MajMvt(mvt);

	effSortie= GrMvt->Cells[1][6].ToIntDef(0);
	effFin= GrMvt->Cells[1][7].ToIntDef(0);

	if(effFin<0 ||effSortie<0)
	{
		ShowMessage("IMPOSSIBLE Effectif négatif");
		TroupeauFrm->Erreur=true;
	}
	if(TroupeauFrm->Erreur==true) return;

	TroupeauFrm->Erreur=false;
	if(N+1>=N_X) return;

	/// de cette categorie des effectifs sont partis ailleurs
	/// j'annule ce qui est lié à ce MvtAni
	/// je mets a jour
	TroupeauFrm->Simuler();
	TroupeauFrm->AffEffectifs();
}
//---------------------------------------------------------------------------
void TMvtAnneeFrm::TexteChaine(void) {

	L_Debut = T->TrouveTexte("MvtAnneeFrm", "L_Debut");
	L_Vente = T->TrouveTexte("MvtAnneeFrm", "L_Vente");
	L_Achat = T->TrouveTexte("MvtAnneeFrm", "L_Achat");
	L_Ne = T->TrouveTexte("MvtAnneeFrm", "L_Ne");
	L_Mort = T->TrouveTexte("MvtAnneeFrm", "L_Mort");
	L_Entree = T->TrouveTexte("MvtAnneeFrm", "L_Entree");
	L_Sortie = T->TrouveTexte("MvtAnneeFrm", "L_Sortie");
	L_Fin = T->TrouveTexte("MvtAnneeFrm", "L_Fin");
}

//---------------------------------------------------------------------------/*
void TMvtAnneeFrm::IniCaption(void) {
	LabAchat->Caption = T->LC_LabAchat;
	BitBtn1->Caption = T->LC_RG;
	LabEffEntree->Caption = LC_LabEffEntree;
	LabEffSortie->Caption = LC_LabEffEntree;
	LabEffVente->Caption = LC_LabEffEntree;
	LabEffAchat->Caption = LC_LabEffEntree;
	LabEntree->Caption = LC_LabEntree;
	LabVenteModif->Caption = T->LC_LabelModifie;
	LabAchatModif->Caption = T->LC_LabelModifie;
	LabEntreeModif->Caption = T->LC_LabelModifie;
	LabSortieModif->Caption = T->LC_LabelModifie;
	LabMvtModif->Caption = T->LC_LabelModifie;
	MvtAnneeFrm->Caption = T->LC_MvtAnneeFrm;
	LabPrixVente->Caption = T->LC_GBPrix;
	LabPrixAchat->Caption = T->LC_GBPrix;
	LabSortie->Caption = LC_LabSortie;
	LabDestin->Caption = LC_LabDestin;
	LabVente->Caption = T->LC_BtBnVenteQ;
	LabOrig->Caption = LC_LabOrig;
}
//--------------------------------------------
void TMvtAnneeFrm::TexteCaption(void) {
	LC_LabAchat = T->TrouveCaption("CL_Trad", "LC_LabAchat");
	LC_RG = T->TrouveCaption("CL_Trad", "LC_RG");
	LC_LabEffEntree = T->TrouveCaption("MvtAnnee", "LC_LabEffEntree");
	LC_LabEntree = T->TrouveCaption("MvtAnnee", "LC_LabEntree");
	LC_LabelModifie = T->TrouveCaption("CL_Trad", "LC_LabelModifie");
	LC_MvtAnneeFrm = T->TrouveCaption("CL_Trad", "LC_MvtAnneeFrm");
	LC_GBPrix = T->TrouveCaption("CL_Trad", "LC_GBPrix");
	LC_LabSortie = T->TrouveCaption("MvtAnnee", "LC_LabSortie");
	LC_LabDestin = T->TrouveCaption("MvtAnnee", "LC_LabDestin");
	LC_BtBnVenteQ = T->TrouveCaption("CL_Trad", "LC_BtBnVenteQ");
	LC_LabOrig = T->TrouveCaption("MvtAnnee", "LC_LabOrig");

	IniCaption();

}
//--------------------------------------------

bool __fastcall TMvtAnneeFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=570;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

