//---------------------------------------------------------------------------

#pragma hdrstop
#include "CL_Trad.h"

#include "Troupeau.h"

//#include "Troupeau1.h"
extern CL_Trad *T;

//---------------------------------------------------------------------------

#pragma package(smart_init)
// eviter des fonctions lourdes de Forme00
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::Grille0Click(TObject *Sender)
{
	if(LaGrille!=GrilleMvt) return;
	// utilisé seult pour afficher Mvt Animaux
	if(GrilleMvt->Col>=Col0)
	MvtAnneeFrm->Show();
	return;//pour eviter  passage dans Grille0Click de Forme00
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::Grille0KeyPress(TObject *Sender, char &Key)
{
//150406
	if(Key==11 || Key==22)//CtrlV  Coller
	{
		Key=0;
		LireClipBoard();
		CellModif=true;LabelModifie->Visible=true;
		return;
	}
	if(Key==3) //CtrlC    Copier
	{
//        ShowMessage(AnsiString(CDebSel)+"  "+RDebSel+"  "+CFinSel+"  "+RFinSel);
		Key=0;
		if(CDebSel==CFinSel && RDebSel==RFinSel )return;
		EcrireClipBoard();
		return;
	}
	if(Key==26) //CtrlZ Restaurer
	{
		Restaurer();
		//ShowMessage(AnsiString(LaGrille->Tag));
	}

	//280306

	if (TypeCol[LaGrille->Col]=='0') {Key=0; return;} //290302

	if (TypeCol[LaGrille->Col]!='N') {LabelModifie->Visible=true; return;}
	else if(Key >='0' && Key <='9') {LabelModifie->Visible=true; return;}
	else if(Key=='-') {LabelModifie->Visible=true; return;}
	else if(Key=='.') {LabelModifie->Visible=true; return;}
	else if(Key==VK_BACK) {LabelModifie->Visible=true; return;}
	Key=0;
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::GrilleInvValKeyPress(TObject *Sender,
		char &Key)
{
	if(LaGrille->Col<2) {Key=0; return;} //290302

	if(LaGrille->Col==2)
	{
		if(Key=='O'||Key=='o') {Key='O';LabelModifie->Visible=true;return;}
		if(Key=='N'||Key=='n') {Key='N';LabelModifie->Visible=true;return;}
		Key=0;return;
	}
	if (Key >='0' && Key <='9') {LabelModifie->Visible=true; return;}
	else if(Key=='-') {LabelModifie->Visible=true; return;}
	else if(Key=='.') {LabelModifie->Visible=true; return;}
	else if(Key==VK_BACK) {LabelModifie->Visible=true; return;}

}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::Personnaliser(void)
{
//a garder sinon message de FOrme00
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::DefinirLesGrilles(void)
{
	int g;
	AjoutRow=false;

	LesGrilles[0]=GrilleMaxi;
	LesGrilles[1]=GrillePrix;
	LesGrilles[2]=GrilleValInv;
	LesGrilles[3]=GrilleAchat;
	LesGrilles[4]=GrillePrixAchat;

	LesGrilles[5]=GrilleMvt;
	LesGrilles[6]=GrilleProCha;
	GrilleX=7;
	for(g=0;g<GrilleX;g++)LesGrilles[g]->Tag=g;

}
//---------------------------------------------------------------------------

//         INIGRILLE

//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::IniGrille(TStringGrid *grille)
{
	if (grille==GrilleMvt) IniGrilleMvt(grille);
	else if(grille==GrilleValInv) IniGrilleValInv(grille);
	else if(grille==GrilleMaxi) IniGrilleNum(grille,48);
	else IniGrilleNum(grille,64);
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::IniGrilleMvt(TStringGrid *grille)
{
	int l=0;
	int largeur[] = {20,128,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48};
	// T alpha N numérique 0 non modifiable
	strcpy(TypeCol, "00000000000000000000");

	grille->ColCount=13;
	grille->RowCount=TroupeauEnCours->V_InvAni->Nbelt+1;
	grille->FixedRows=1;
	grille->FixedCols=1;

	for(int c=0;c<grille->ColCount;c++)
	{
		grille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	grille->Width=l+6+25;

	VideGrille(grille);
	grille->Cells[1][0]=T->LC_Nom; //"NOM";
	grille->Cells[2][0]=T->LC_Debut;//"Début";

	for(int i=0;i<10;i++)
	grille->Cells[i+3][0]="  "+AnsiString(An_0+i);
	TVMvtValeur->FullExpand();
	TVMvtEffectif->FullExpand();
}
//---------------------------------------------------------------------------
//  Grille Numérique pour
//          Maxi
//          Valeur de Vente
//          Valeur d'inventaire
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::IniGrilleNum(TStringGrid *grille,int larCol)
{
	int l=0;
	int largeur[] = {20,128,64,64,64,64,64,64,64,64,64,64,64,64};

	// T alpha N numérique 0 non modifiable
	strcpy(TypeCol, "00NNNNNNNNNNNNNNNNN");

	grille->ColCount=12;
	grille->RowCount=TroupeauEnCours->V_InvAni->Nbelt+1;
	grille->FixedRows=1;
	grille->FixedCols=1;

	for(int c=0;c<2;c++)
	{
		grille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	for(int c=2;c<grille->ColCount;c++)
	{
		grille->ColWidths[c]=larCol;
		l+=larCol;
	}
	grille->Width=l+6+25;

	VideGrille(grille);
	grille->Cells[1][0]=T->LC_Nom;

	for(int i=0;i<10;i++)
	grille->Cells[i+2][0]="  "+AnsiString(An_0+i);

}
//---------------------------------------------------------------------------
//  Grille Numérique pour
//          Valeur d'inventaire
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::IniGrilleValInv(TStringGrid *grille)
{
	int l=0;
	int largeur[] = {20,128,20,64,64,64,64,64,64,64,64,64,64,64,64};
	int larCol=64;
	// T alpha N numérique 0 non modifiable
	strcpy(TypeCol, "00TNNNNNNNNNNNNNNNNN");

	grille->ColCount=14;
	grille->RowCount=TroupeauEnCours->V_InvAni->Nbelt+1;
	grille->FixedRows=1;
	grille->FixedCols=1;

	for(int c=0;c<3;c++)
	{
		grille->ColWidths[c]=largeur[c];
		l+=largeur[c];
	}
	for(int c=3;c<grille->ColCount;c++)
	{
		grille->ColWidths[c]=larCol;
		l+=larCol;
	}
	grille->Width=l+6+25;

	VideGrille(grille);
	grille->Cells[1][0]=T->LC_Nom; //"NOM";
	grille->Cells[2][0]="Repro O/N";//  a faire

	grille->Cells[3][0]=T->LC_Debut;//"début";
	for(int i=0;i<10;i++)
	grille->Cells[i+4][0]="  "+AnsiString(An_0+i);

}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::IniTSNature(void)
{
	int n;
	CL_Categorie *cat;
	CL_Troupeau *troupeau;

	// affiche nom troupeau
	LBTroupeau->Clear();
	for(n=0;n<Agri->LstTroupeaux->Count;n++)
	{
		troupeau=(CL_Troupeau*)Agri->LstTroupeaux->Items[n];
		cat=troupeau->CatBestiaux;
		LBTroupeau->Items->AddObject(cat->Nom,(TObject*)troupeau);
	}
	LBTroupeau->Items->AddObject("[...]",NULL);
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::IniTSResultats(void)
{
	int n;
	CL_Categorie *cat;
	CL_Troupeau *troupeau;

	// affiche nom troupeau
	ChLBTroupeau->Clear();
	for(n=0;n<Agri->LstTroupeaux->Count;n++)
	{
		troupeau=(CL_Troupeau*)Agri->LstTroupeaux->Items[n];
		cat=troupeau->CatBestiaux;
		ChLBTroupeau->Items->AddObject(cat->Nom,(TObject*)troupeau);
		if(troupeau==TroupeauEnCours)
		ChLBTroupeau->Checked[n]=true;
	}
	TVResultat->FullExpand();
	/*
	 TTreeNode* noeud;
	 for( n=0;n<TVResultat->Items->Count;n++)
	 {
	 noeud=TVResultat->Items->Item[n];
	 noeud->Expand(true);
	 }
	 */
}

//          VERSGRILLE

//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::VersGrille(TStringGrid *grille)
{
	LaGrille=grille;
	if (grille==GrilleMaxi) VersGrilleMaxi(grille);
	else if(grille==GrillePrix) VersGrillePrix(grille);
	else if(grille==GrilleValInv) VersGrilleValInv(grille);
	else if(grille==GrilleMvt) VersGrilleMvt(grille);
	else if(grille==GrilleProCha) VersGrilleProCha(grille);

	else if(grille==GrilleAchat) VersGrilleAchat(grille);
	else if(grille==GrillePrixAchat) VersGrillePrixAchat(grille);
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::VersGrilleMaxi(TStringGrid *grille)
{
	int r,row;
	int c;
	int n;
	CL_Vecteur<CL_InvAni> *vecteur;
	CL_InvAni *invAni;
	CL_Item *animal;

	vecteur=TroupeauEnCours->V_InvAni;

	for(r=0;r<vecteur->Nbelt;r++)
	{
		row=r+1;
		invAni=vecteur->Vecteur[r];
		animal=invAni->Animal;
		if(animal==NULL) continue;
		grille->Objects[0][row]=(TObject*)invAni;
		grille->Cells[0][row]=row;

		grille->Cells[1][row]=animal->Nom;
		for(n=0,c=2;n<N_X;n++,c++)
		{
			if(invAni->EffMax[n]==SANSBORNE)continue;
			if(invAni->EffMax[n]==0) {grille->Cells[c][row]="  0";continue;}

			grille->Cells[c][row]=Aff(invAni->EffMax[n]);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::VersGrillePrix(TStringGrid *grille)
{
	int r,row;
	int c;
	int n;
	CL_Vecteur<CL_InvAni> *vecteur;
	CL_InvAni *invAni;
	CL_Item *animal;

	vecteur=TroupeauEnCours->V_InvAni;

	for(r=0;r<vecteur->Nbelt;r++)
	{
		row=r+1;
		invAni=vecteur->Vecteur[r];
		animal=invAni->Animal;
		grille->Objects[0][row]=(TObject*)invAni;
		grille->Cells[0][row]=row;
		grille->Cells[1][row]=animal->Nom;

		for(n=0,c=2;n<N_X;n++,c++)
		{
//			grille->Cells[c][row]=Aff(animal->Prix);
			grille->Cells[c][row]=Aff(invAni->PrixVenteMoy[n]);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::VersGrilleValInv(TStringGrid *grille)
{
	int r,row;
	int c;
	int n;
	CL_Vecteur<CL_InvAni> *vecteur;
	CL_InvAni *invAni;
	CL_Item *animal;

	vecteur=TroupeauEnCours->V_InvAni;

	for(r=0;r<vecteur->Nbelt;r++)
	{
		row=r+1;
		invAni=vecteur->Vecteur[r];
		animal=invAni->Animal;
		grille->Objects[0][row]=(TObject*)invAni;
		grille->Cells[0][row]=row;
		grille->Cells[1][row]=animal->Nom;
		grille->Cells[2][row]=invAni->Reproducteur; //O/N

		for(n=0,c=3;n<N_X+1;n++,c++)
		{
			grille->Cells[c][row]=Aff(invAni->ValInvMoy[n]);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TTroupeauFrm::VersGrilleAchat(TStringGrid *grille)
{
	int r,row;
	int c;
	int n;
//int i;
	CL_Vecteur<CL_InvAni> *vecteur;
	CL_InvAni *invAni;
	CL_Item *animal;
//CL_MvtAni   *mvtAni;

	vecteur=TroupeauEnCours->V_InvAni;
//affiche les noms
	for(r=0;r<vecteur->Nbelt;r++)
	{
		row=r+1;
		invAni=vecteur->Vecteur[r];
		animal=invAni->Animal;
		grille->Objects[0][row]=(TObject*)invAni;
		grille->Cells[0][row]=row;
		grille->Cells[1][row]=animal->Nom;
	}
//230305
	/*
	 //a partie de LstAchat  calcule   invAni->AAcheter  invAni->PrixAchat
	 for(i=0;i<LstAchat->Count;i++)
	 {
	 mvtAni=(CL_MvtAni *)LstAchat->Items[i];
	 r=mvtAni->Ligne-1;
	 invAni=vecteur->Vecteur[r];
	 if(invAni==NULL) continue;

	 invAni->AAcheter[mvtAni->Date]=mvtAni->Eff;
	 invAni->PrixAchat[mvtAni->Date]=mvtAni->Info;
	 }
	 */
	for(row=1;row<grille->RowCount;row++)
	{
		invAni=(CL_InvAni*)grille->Objects[0][row];
		for(n=0,c=2;n<N_X;n++,c++)
		{
			grille->Cells[c][row]=Aff(invAni->AAcheter[n]);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::VersGrillePrixAchat(TStringGrid *grille)
{
	int r,row;
	int c;
	int n;
	CL_Vecteur<CL_InvAni> *vecteur;
	CL_InvAni *invAni;
	CL_Item *animal;

	vecteur=TroupeauEnCours->V_InvAni;

	for(r=0;r<vecteur->Nbelt;r++)
	{
		row=r+1;
		invAni=vecteur->Vecteur[r];
		animal=invAni->Animal;
		grille->Objects[0][row]=(TObject*)invAni;
		grille->Cells[0][row]=row;
		grille->Cells[1][row]=animal->Nom;

		for(n=0,c=2;n<N_X;n++,c++)
		{
			grille->Cells[c][row]=Aff(invAni->PrixAchat[n]);
		}
	}
}

//---------------------------------------------------------------------------
//  Voir TroupeauMvt
/*
 void __fastcall TTroupeauFrm::VersGrilleMvt(TStringGrid *grille)
 {
 }
 */
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::VersGrilleProCha(TStringGrid *grille)
{
	int r,row;
	int c;
	int n;
	CL_Vecteur<CL_InvAni> *vecteur;
	CL_InvAni *invAni;
	CL_Item *animal;

	/*test
	 for(r=1;r<GrilleMvt->RowCount;r++)
	 {
	 invAni=(CL_InvAni*)GrilleMvt->Objects[0][r];
	 }
	 fin test
	 */

	vecteur=TroupeauEnCours->V_InvAni;

	for(r=0;r<vecteur->Nbelt;r++)
	{
		row=r+1;
		invAni=vecteur->Vecteur[r];
		animal=invAni->Animal;
		grille->Objects[0][row]=(TObject*)invAni;
		grille->Cells[0][row]=row; //n0 de la ligne

		grille->Cells[1][row]=animal->Nom;
		for(n=0,c=2;n<N_X;n++,c++)
		{
			grille->Objects[c][row]=(TObject*)invAni->Atelier[n];
			if(invAni->Atelier[n])
			grille->Cells[c][row]=invAni->Atelier[n]->Nom;

		}
	}
}