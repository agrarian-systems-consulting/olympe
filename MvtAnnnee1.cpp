//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
/*
 #include "Olympe.hse"
 #include "olympedec.h"
 #include "LesClassesApp.h"
 #include "LesVecteurs.hse"
 #include "Forme0.h"
 #include "Forme01.h"

 #include "AgriSaisie.h"
 //#include "LBMvtAni.h"
 //#include "Brouillon.h"
 #include "CL_MvtAnnee.h"
 //#include "InvAni.h"
 */
#include "MvtAnnee.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//  Mouvement
//       il y a grille à gauche de synthese  Grille
//       elle contient des grilles à droite  SGVente...
//           pour les ventes les achats les mvt
/// remplit la fenetre mouvement
/// fait les calculs d'effectif fin
//---------------------------------------------------------------------------
void __fastcall TMvtAnneeFrm::AffMvtAnnee(CL_MvtAnnee *mvtAnnee)
{
	int i;
	int entree,sortie,vente,achat;
	AnsiString blanc=AnsiString("   ");
	/// Grille à gauche
	/// SG... a droite
	GrMvt->EditorMode=true;
	SGVente->EditorMode=true;
	SGAchat->EditorMode=true;
	SGEntree->EditorMode=true;
	SGSortie->EditorMode=true;

	LabMvtModif->Visible=false;

	LabVenteModif->Visible=false;
	LabAchatModif->Visible=false;
	LabSortieModif->Visible=false;
	LabEntreeModif->Visible=false;

	VideGrille(SGVente);
	VideGrille(SGAchat);
	VideGrille(SGEntree);
	VideGrille(SGSortie);

//    Debut=effDeb;
//    GrMvt->Cells[1][0]=effDeb;
	GrMvt->Cells[1][0]=mvtAnnee->Debut;

	//Vente
	vente=0;
	SGVente->FixedCols=0;
//    if(mvtAnnee->iRegul==-1) SGVente->FixedCols=0;
//    else                     SGVente->FixedCols=1;
	for(i=0;i<mvtAnnee->iVente;i++)
	{
		SGVente->Cells[i][0]= mvtAnnee->Vente[i];
		SGVente->Cells[i][1]= mvtAnnee->PrixVente[i];
		vente+=mvtAnnee->Vente[i];
	}
	GrMvt->Cells[1][1]=vente;

	//Achat
	achat=0;
	for(i=0;i<mvtAnnee->iAchat;i++)
	{
		SGAchat->Cells[i][0]= mvtAnnee->Achat[i];
		SGAchat->Cells[i][1]= mvtAnnee->PrixAchat[i];
		achat+=mvtAnnee->Achat[i];
	}
	GrMvt->Cells[1][2]=achat;

	//Naissance
	GrMvt->Cells[1][3]=blanc+mvtAnnee->Ne;

	//Mort
	GrMvt->Cells[1][4]= mvtAnnee->Mort;

	//Entree
	entree=0;
	for(i=0;i<mvtAnnee->iOr;i++)
	{
		SGEntree->Cells[i][0]= mvtAnnee->Entree[i];
//        j=TroupeauFrm->TrouverLigne(mvtAnnee->Origine[i]);
//        SGEntree->Cells[i][1]=j;
		SGEntree->Cells[i][1]=mvtAnnee->Origine[i];
		entree+=mvtAnnee->Entree[i];
	}
	GrMvt->Cells[1][5]=blanc+entree;

	//Sortie
	//mvtAnnee->Fin=mvtAnnee->Debut+entree-sortie+achat-vente+mvtAnnee->Ne-mvtAnnee->Mort;
	sortie=0;
	for(i=0;i<mvtAnnee->iDest;i++)
	{
		SGSortie->Cells[i][0]= mvtAnnee->Sortie[i];
//        j=TroupeauFrm->TrouverLigne(mvtAnnee->Destin[i]);
//        SGSortie->Cells[i][1]=   j;
		SGSortie->Cells[i][1]= mvtAnnee->Destin[i];
		sortie+=mvtAnnee->Sortie[i];
	}
	GrMvt->Cells[1][6]=sortie;

	mvtAnnee->Fin=mvtAnnee->Debut+entree-sortie+achat-vente+mvtAnnee->Ne-mvtAnnee->Mort;

	GrMvt->Cells[1][7]=blanc+mvtAnnee->Fin;

//	if(mvtAnnee->Fin<0)               //230108
//    	CorrigerDeficit(mvtAnnee);
}
//-------------------------------------------------------------------------------
void TMvtAnneeFrm::CorrigerDeficit(CL_MvtAnnee *mvtAnnee) {
	int deficit;
	int i;
	deficit = -mvtAnnee->Fin;
	for (i = 0; i < 3; i++) {
		if (deficit == 0)
			break;

		if (mvtAnnee->Sortie[i] >= deficit) {
			mvtAnnee->Sortie[i] -= deficit;
			deficit = 0;
		} else {
			deficit -= mvtAnnee->Sortie[i];
			mvtAnnee->Sortie[i] = 0;
		}
	}
	AffMvtAnnee(mvtAnnee);
}
//---------------------------------------------------------------------------
void __fastcall TMvtAnneeFrm::VideGrille(TStringGrid *grille)
{
	int c,r;
	for(c=0;c<3;c++)
	{
		for(r=0;r<2;r++)
		{
			grille->Cells[c][r]="";
			grille->Objects[c][r]=NULL;
		}
	}
}
//---------------------------------------------------------------------------
//  choix des animaux destination ou origine ??
//---------------------------------------------------------------------------
void __fastcall TMvtAnneeFrm::LBAnimauxClick(TObject *Sender)
{
	int n;
	int c;
	if(GrilleEnCours==NULL) return;
	c=GrilleEnCours->Col;
	n=LBAnimaux->ItemIndex+1;
	GrilleEnCours->Cells[c][1]=n;

}
/*
 GrilleKeyPress
 GrilleClick
 GrilleSelectCell
 */
//---------------------------------------------------------------------------
void __fastcall TMvtAnneeFrm::GrMvtKeyPress(TObject *Sender, char &Key)
{
//Entree Sortie est calculé
	switch(GrMvt->Row)
	{
		case 0:Key=0; return; //Debut
		case 1:Key=0;SGVente->SetFocus(); return;//Vente
		case 2:Key=0;SGAchat->SetFocus(); return;//Achat
		case 3:Key=0; return;//né      non modifiable
		case 5:Key=0;return;//origine non modifiable
		case 6:Key=0;SGSortie->SetFocus();return;//sortie
		case 7:Key=0;return;//fin
	}
	//4 mort
	if(Key >='0' && Key <='9') {LabMvtModif->Visible=true; return;}
	if(Key==VK_BACK) {LabMvtModif->Visible=true; return;}

	Key=0;
}
/// click sur grille gauche calcule l'effectif total
//---------------------------------------------------------------------------
void TMvtAnneeFrm::MajMvt(CL_MvtAnnee *mvt) {
	int entree, sortie, dispo, effVente, effAchat;
	int i;
	AnsiString blanc = AnsiString("   ");
	CL_MvtAnnee *mvtTest;
	//230108
	mvtTest = (CL_MvtAnnee*) TroupeauFrm->GrilleMvt->Objects[Col0][3];

	if (LabMvtModif->Visible == false)
		return;

	// la  nouvelle information est dans GrilleMvt: je mets à zero MvtAnnee
	//MvtAnnee->Maz();

	///reprend ce qui est dans les grille de droite en faisant total
	DeSGVente(mvt, effVente);
	DeSGAchat(mvt, effAchat);
	if (DeSGEntree(mvt, entree) == false)
		return;
	if (DeSGSortie(mvt, sortie) == false)
		return;
	// tient compte du mvt automatique vers cat suivante
	// il existe dans la grille
	// il faudra le calculer et le réafficher

	/// pas de total à faire
	mvt->Ne = GrMvt->Cells[1][3].ToIntDef(0);
	mvt->Mort = GrMvt->Cells[1][4].ToIntDef(0);

	// ce qui passe dans cat suivante
	if (mvt->SortieTout[0] == true) {
		dispo = mvt->Dispo(0); //0 car SortieTout=true  explication à compléter
		SGSortie->Cells[0][0] = dispo;
		DeSGSortie(mvt, sortie);
	}

	/// calcule le nombre d'animaux compte tenu des mouvements
	mvt->Solde();
	/// Reaffiche  Grille Sortie

	VideGrille(SGSortie);
	sortie = 0;
	for (i = 0; i < mvt->iDest; i++) {
		SGSortie->Cells[i][0] = mvt->Sortie[i];
//        j=TroupeauFrm->TrouverLigne(MvtAnnee->Destin[i]);
//        SGSortie->Cells[i][1]=   j;
		SGSortie->Cells[i][1] = mvt->Destin[i];
		sortie += mvt->Sortie[i];
	}
	/*
	 GrMvt->Cells[1][1]=IntToStr(effVente);
	 GrMvt->Cells[1][2]=IntToStr(effAchat);
	 GrMvt->Cells[1][5]=IntToStr(entree);
	 GrMvt->Cells[1][6]=IntToStr(sortie);
	 GrMvt->Cells[1][7]=IntToStr(MvtAnnee->Fin);
	 */
	GrMvt->Cells[1][1] = effVente;
	GrMvt->Cells[1][2] = blanc + effAchat;
	GrMvt->Cells[1][5] = blanc + entree;
	GrMvt->Cells[1][6] = sortie;
	GrMvt->Cells[1][7] = blanc + mvt->Fin;

//	LabMvtModif->Visible=false;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TMvtAnneeFrm::GrMvtClick(TObject *Sender)
{
	int vente,achat,entree,sortie,debut,ne,mort,solde;
	int c;
	AnsiString blanc=AnsiString("   ");
	CL_MvtAnnee *mvtTest;
	if(LabMvtModif->Visible==false) return;
	//230108
	mvtTest=(CL_MvtAnnee*)TroupeauFrm->GrilleMvt->Objects[Col0][3];

	///reprend ce qui est dans les grille de droite en faisant total
	//Vente
	vente=0;
	for(c=0;c<3;c++)
	vente+= SGVente->Cells[c][0].ToIntDef(0);
	//Achat
	achat=0;
	for(c=0;c<3;c++)
	achat+= SGAchat->Cells[c][0].ToIntDef(0);
	//Entrée
	entree=0;
	for(c=0;c<3;c++)
	entree+= SGEntree->Cells[c][0].ToIntDef(0);
	//Sortie
	sortie=0;
	for(c=0;c<3;c++)
	sortie+= SGSortie->Cells[c][0].ToIntDef(0);
	debut= GrMvt->Cells[1][0].ToIntDef(0);
	ne= GrMvt->Cells[1][3].ToIntDef(0);
	mort= GrMvt->Cells[1][4].ToIntDef(0);

	solde=debut-vente+achat+ne-mort+entree-sortie;
	GrMvt->Cells[1][1]=vente;
	GrMvt->Cells[1][2]=blanc +achat;
	GrMvt->Cells[1][5]=blanc +entree;
	GrMvt->Cells[1][6]=sortie;
	GrMvt->Cells[1][7]=blanc+ solde;

//	LabMvtModif->Visible=false;
}
//---------------------------------------------------------------------------
void __fastcall TMvtAnneeFrm::GrMvtSelectCell(TObject *Sender, int ACol,
		int ARow, bool &CanSelect)
{
	if(ACol==0) CanSelect=false;
	if(ARow==0) CanSelect=false;
}

//---------------------------------------------------------------------------
/*
 SGKeyDown
 SGKeyPress
 SGExit
 */
//---------------------------------------------------------------------------
void __fastcall TMvtAnneeFrm::SGKeyDown(TObject *Sender, WORD &Key,
		TShiftState Shift)
{
	TLabel *lab;
	if (Sender==SGVente) lab=LabVenteModif;
	else if(Sender==SGAchat) lab=LabAchatModif;
	else if(Sender==SGEntree) lab=LabEntreeModif;
	else if(Sender==SGSortie) lab=LabSortieModif;
	if(Key==VK_DELETE) {lab->Visible=true;return;}
//
}
//---------------------------------------------------------------------------
void __fastcall TMvtAnneeFrm::SGKeyPress(TObject *Sender, char &Key)
{
	TLabel *lab;
	if (Sender==SGVente) lab=LabVenteModif;
	else if(Sender==SGAchat) lab=LabAchatModif;
	else if(Sender==SGEntree) lab=LabEntreeModif;
	else if(Sender==SGSortie) lab=LabSortieModif;
	if(Key >='0' && Key <='9') {lab->Visible=true;return;}
	if(Key==VK_BACK) return;
	Key=0;
}
//---------------------------------------------------------------------------
void __fastcall TMvtAnneeFrm::SGExit(TObject *Sender)
{
	int c;
	int eff;
	int tot;
	int row=5;
	TStringGrid *grille;
	TLabel *lab;
	if(Sender==SGVente)
	{
		row=1;
		grille=SGVente;
		lab=LabVente;
	}
	else if(Sender==SGAchat)
	{
		row=2;
		grille=SGAchat;
		lab=LabAchat;
	}
	else if(Sender==SGEntree)
	{
		row=5;
		grille=SGEntree;
		lab=LabEntree;
	}
	else if(Sender==SGSortie)
	{
		row=6;
		grille=SGSortie;
		lab=LabSortie;
	}

	if(lab->Visible==false) return;
	LabMvtModif->Visible=true;
	tot=0;
	for(c=0;c<3;c++)
	{
		eff= grille->Cells[c][0].ToIntDef(0);
		tot+=eff;
	}
	GrMvt->Cells[1][row]=IntToStr(tot);
	GrMvtClick(this);
}
//---------------------------------------------------------------------------
/*
 DeSGVente
 DeSGAchat
 DeSGEntree
 DeSGSortie
 */
//---------------------------------------------------------------------------
void __fastcall TMvtAnneeFrm::DeSGVente(CL_MvtAnnee *mvt,int &total)
{
	int c;
	int i;
	int eff;
	int prix;
	total=0;
//    if(LabVenteModif->Visible==false) return true;
	mvt->iVente=0;
	for(c=0;c<3;c++)
	{
		eff= SGVente->Cells[c][0].ToIntDef(0);
		if( eff==0 ) continue;
		prix= SGVente->Cells[c][1].ToIntDef(-999); ///!!
		if( prix==-999) prix=0;
		i=mvt->iVente++;
		mvt->Vente[i]=eff;
		mvt->PrixVente[i]=prix;
		total+=eff;
	}
}
/*
 if(total >  MvtAnnee->Debut)
 {
 GrMvt->Cells[1][6]="?";
 GrMvt->Cells[1][7]="?";

 ShowMessage("Animaux vendus  >effectif Debut");
 return false;
 }
 */
//---------------------------------------------------------------------------
void __fastcall TMvtAnneeFrm::DeSGAchat(CL_MvtAnnee *mvt,int &total)
{
	int c;
	int i;
	int eff;
	int prix;
//    row=2;
	total=0;
//    if(LabAchatModif->Visible==false) return true;

	mvt->iAchat=0;
	for(c=0;c<3;c++)
	{
		eff= SGAchat->Cells[c][0].ToIntDef(0);
		if( eff==0 ) continue;
		prix= SGAchat->Cells[c][1].ToIntDef(-999); ///!!
		if( prix==-999) prix=0;
		i=mvt->iAchat++;
		mvt->Achat[i]=eff;
		mvt->PrixAchat[i]=prix;
		total+=eff;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TMvtAnneeFrm::DeSGEntree(CL_MvtAnnee *mvt,int &total)
{
	int c,r;
	int i;
	int eff;
	int rOrigine;
	int noDest,col;
	CL_MvtAnnee *mvtOrigine;

	total=0;
	r=TroupeauFrm->Grille0->Row;
	col=TroupeauFrm->GrilleMvt->Col;
	mvt->iOr=0;
	for(c=0;c<3;c++)
	{
		if(SGEntree->Cells[c][1].Length()==0) continue;
		rOrigine= SGEntree->Cells[c][1].ToIntDef(-999); ///!!
		if( rOrigine==-999)
		{
			ShowMessage("Pas d'origine");
			return false;
		}
		if( rOrigine<1 || rOrigine>GrilleInv->RowCount-1)
		{
			ShowMessage("Origine Inconnue");
			return false;
		}
		if( rOrigine==GrilleInv->Row)
		{
			ShowMessage("On tourne en rond");
			return false;
		}
		eff= SGEntree->Cells[c][0].ToIntDef(0);
		mvt->Entree[c]=eff;
		mvt->Origine[c]=rOrigine;
		mvt->iOr=c+1;
		/*
		 mvtOrigine=(CL_MvtAnnee*)TroupeauFrm->GrilleMvt->Objects[col][rOrigine];
		 for(i=0;i<3;i++)
		 {
		 if(mvtOrigine->Destin[i]==r)
		 {
		 mvtOrigine->Sortie[i]=eff;
		 goto SUITE;
		 }
		 }
		 i=mvtOrigine->iDest++;
		 mvtOrigine->Sortie[i]=eff;
		 mvtOrigine->Destin[i]=r;
		 SUITE:
		 */
	}

	return true;
}
//---------------------------------------------------------------------------
// calcule le total des sorties
// si mvt automatique il y a un MvtAnnee->SortieTout[c]==true
//  la colonne 0 Mvt->Sortie[0]  est résérvée à l'effectif calculé automatiquement
//
//---------------------------------------------------------------------------
bool __fastcall TMvtAnneeFrm::DeSGSortie(CL_MvtAnnee *mvt,int &total)
{
	int c;
	int eff;
	int rDest;
	total=0;
	for(c=0;c<3;c++)
	{
		// les effectifs qui vont dans la classe suivante
		// seront calculées par Mvt->Solde()
		if(SGSortie->Cells[c][1].Length()==0) continue;

		rDest= SGSortie->Cells[c][1].ToIntDef(-999);///!!
		if( rDest==-999)
		{
			ShowMessage("Pas de destination");
			return false;
		}
		if( rDest<1 || rDest>GrilleInv->RowCount-1) //3 071107
		{
			ShowMessage("Destination Inconnue");
			return false;
		}
		if( rDest==GrilleInv->Row)
		{
			ShowMessage("On tourne en rond");
			return false;
		}
		eff= SGSortie->Cells[c][0].ToIntDef(0);

		mvt->Sortie[c]=eff;
		mvt->Destin[c]=rDest;
		mvt->iDest=c+1;
		total+=eff;

	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TMvtAnneeFrm::SGEntreeEnter(TObject *Sender)
{
	GrilleEnCours=SGEntree;
}
//---------------------------------------------------------------------------
void __fastcall TMvtAnneeFrm::SGSortieEnter(TObject *Sender)
{
	GrilleEnCours=SGSortie;
}

