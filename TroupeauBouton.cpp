//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop
#include "TVChoixAniProCha.h"
#include "QRSortieVal.h"
#include "QRSortieQuant.h"
#include "Tableur.h"

#include "Troupeau.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
extern CL_ES *ES;
extern CL_Excel *EX;

//---------------------------------------------------------------------------
//           Les BOUTONS  sauf ceux de TroupeauMvt
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtBnSupClick(TObject *Sender)
{
	int n;
	int rep;
	CL_Troupeau *troupeau;
	n=LBTroupeau->ItemIndex;
	if(n==-1) return;
	troupeau=(CL_Troupeau*)LBTroupeau->Items->Objects[n];

	rep=MessageBox(Handle,"A effacer ?",troupeau->CatBestiaux->Nom.c_str(),
			MB_YESNO|MB_ICONEXCLAMATION);

	if(rep!=IDYES) return;

	delete troupeau;
	VideLesGrilles(); //200305
	Agri->LstTroupeaux->Delete(n);
	LstMvtAni=NULL;//181004
	IniTSNature();
	LabelModifie->Visible=true;
//    if(Agri->TroupeauEnCours==
	Agri->TroupeauEnCours=NULL;//?????
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtBnStockerClick(TObject *Sender)
{
	//verif et stocker avant de passer à la suite
	if (DernierePage==TSNature)
	{
		; //ShowMessage("A faire");
	}
	else if(DernierePage==TSMaxi)
	{
		DeGrilleMaxi(GrilleMaxi);
		LaGrille=GrilleMvt;
		ASimuler=true;
	}
	else if(DernierePage==TSPrix)
	{
		DeGrillePrix(GrillePrix);
		LaGrille=GrilleMvt;
		ASimuler=true;
	}
	else if(DernierePage==TSValInv)
	{
		DeGrilleValInv(GrilleValInv);
		LaGrille=GrilleMvt;
		ASimuler=true;
	}
	else if(DernierePage==TSAchat)
	{
		DeGrilleAchat(GrilleAchat);
		// je cree ici  CreeLstAchat();
		//CreeLstMvtAni();
		LaGrille=GrilleMvt;
		ASimuler=true;
	}
	else if(DernierePage==TSPrixAchat)
	{
		DeGrillePrixAchat(GrillePrixAchat);
		//CreeLstMvtAni();
		LaGrille=GrilleMvt;
		ASimuler=true;
	}
	else if(DernierePage==TSMouvement)
	{
		//TroupeauEnCours->VideLstMvtAni();
		//CreeLstMvtAni();
	}
	else if(DernierePage==TSProCha) DeGrilleProCha(GrilleProCha);

//	CreeLstMvtAni();
//    ES->ecrireFichier();
	LabelModifie->Visible=false;
}
//---------------------------------------------------------------------------
//TSNature
// si plusieurs troupeaux choix du troupeau
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::LBTroupeauClick(TObject *Sender)
{
	int n;
	AnsiString s;
	n=LBTroupeau->ItemIndex;
	s=LBTroupeau->Items->Strings[n];
	if(s=="[...]")
	{
		LBChoixBestiauxFrm->Show();
		return;
	}
	TroupeauEnCours=(CL_Troupeau*)LBTroupeau->Items->Objects[n];
	Agri->TroupeauEnCours=TroupeauEnCours;
	Debuter();
	LBTroupeau->ItemIndex=n;
}
//---------------------------------------------------------------------------
//TSProCha
// produits et charges cf TVChoixAniProChaFrm
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtBnProchaClick(TObject *Sender)
{
	CreeTVAtelier (TVChoixAniProChaFrm->TV, V_CatAnimaux,V_Animaux);
	TVChoixAniProChaFrm->LaGrille=LaGrille;
	TVChoixAniProChaFrm->Show();

}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtBnRienClick(TObject *Sender)
{
	int r=LaGrille->Row;
	int c=LaGrille->Col;
	if(c<2) return;

	LaGrille->Objects[c][r]=NULL;
	LaGrille->Cells[c][r]="";

	LabelModifie->Visible=true;

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtBnSansBorneClick(TObject *Sender)
{
	int c,r;
	int n;
	CL_InvAni *invAni;
	c=GrilleMaxi->Col;
	r=GrilleMaxi->Row;
	invAni=(CL_InvAni*)GrilleMaxi->Objects[0][r];
	n=c-2;
	if(n<0)return;
	if(r==0)return;
	invAni->EffMax[n]=SANSBORNE;
	GrilleMaxi->Cells[c][r]="";
	LabelModifie->Visible=true;

}

//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtReportDroitClick(TObject *Sender)
{
	/*
	 if     (DernierePage==TSNature)
	 {
	 ;//a faire
	 }
	 */
	if (DernierePage==TSMaxi) BtRepDroitNum();
	else if(DernierePage==TSPrix) BtRepDroitNum();
	else if(DernierePage==TSValInv) BtRepDroitNum();
	else if(DernierePage==TSAchat) BtRepDroitNum();
	else if(DernierePage==TSPrixAchat) BtRepDroitNum();
//	else if(DernierePage==TSMouvement) ShowMessage("A faire");
	else if(DernierePage==TSProCha) BtRepDroitProCha();

	LabelModifie->Visible==false;

}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtRepDroitNum(void)
{
	int c,c0,r0;
	if(c0<2) return;
	c0=LaGrille->Col;
	r0=LaGrille->Row;
	for(c=c0+1;c<LaGrille->ColCount;c++)
	{
		if(RepPossible(c,r0)==false) continue;
		LaGrille->Cells[c][r0]=LaGrille->Cells[c0][r0];
	}
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtRepDroitProCha(void)
{
	int c,c0,r0;
	c0=LaGrille->Col;
	r0=LaGrille->Row;
	//ReAffFloat(c0,r0,digits);
	for(c=c0+1;c<LaGrille->ColCount;c++)
	{
		if(RepPossible(c,r0)==false) continue;
		LaGrille->Cells[c][r0]=LaGrille->Cells[c0][r0];
		LaGrille->Objects[c][r0]=LaGrille->Objects[c0][r0];
	}
}
//---------------------------------------------------------------------------

void __fastcall TTroupeauFrm::BtReportBasClick(TObject *Sender)
{
	if (DernierePage==TSMaxi) BtRepBasNum();
	else if(DernierePage==TSPrix) BtRepBasNum();
	else if(DernierePage==TSValInv) BtRepBasNum();
	else if(DernierePage==TSAchat) BtRepBasNum();
	else if(DernierePage==TSPrixAchat) BtRepBasNum();
//	else if(DernierePage==TSMouvement) ShowMessage("A faire");
	else if(DernierePage==TSProCha) BtRepBasProCha();

	LabelModifie->Visible==false;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtRepBasNum(void)
{
	int r,c0,r0;
	if(c0<2) return;
	c0=LaGrille->Col;
	r0=LaGrille->Row;
	for(r=r0+1;r<LaGrille->RowCount;r++)
	{
		if(RepPossible(c0,r)==false) continue;
		LaGrille->Cells[c0][r]=LaGrille->Cells[c0][r0];
	}
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::BtRepBasProCha(void)
{
	int r,c0,r0;
	c0=LaGrille->Col;
	r0=LaGrille->Row;
	//ReAffFloat(c0,r0,digits);
	for(r=r0+1;r<LaGrille->RowCount;r++)
	{
		if(RepPossible(c0,r)==false) continue;
		LaGrille->Cells[c0][r]=LaGrille->Cells[c0][r0];
		LaGrille->Objects[c0][r]=LaGrille->Objects[c0][r0];
	}
}
//---------------------------------------------------------------------------
// Resultats
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::TVResultatClick(TObject *Sender)
{
	int n;
	TTreeView *TV=(TTreeView*)Sender;
	TTreeNode *noeud;
	CL_Troupeau *troupeau;
	bool coche[100];
	if(TV!=TVResultat)
	{
		for(n=0;n<ChLBTroupeau->Count;n++)
		coche[n]=ChLBTroupeau->Checked[n];
		for(n=0;n<ChLBTroupeau->Count;n++)
		{
			troupeau=(CL_Troupeau*)ChLBTroupeau->Items->Objects[n];
			if(troupeau!=TroupeauEnCours)
			ChLBTroupeau->Checked[n]=false;
		}
	}
	noeud=TV->Selected;
	n=noeud->AbsoluteIndex;
	if(TV==TVMvtValeur)n+=3;
	switch(n)
	{
		case 1:EnsembleEffectif(QUANTITE,ACHAT); break;
		case 2:EnsembleEffectif(QUANTITE,VENTE); break;
		case 4:EnsembleEffectif(VALEUR, ACHAT); break;
		case 5:EnsembleEffectif(VALEUR, VENTE); break;
		case 6:EnsembleEffectif(VALINV, 0); break; //le second sans importance

		case 8:ProChaQ();break;
		case 9:ProChaV();break;
	}
	if(TV!=TVResultat)
	{
		for(n=0;n<ChLBTroupeau->Count;n++)
		ChLBTroupeau->Checked[n]=coche[n];
	}
}
//---------------------------------------------------------------------------
//        effectifs quantite valeur inventaire Ensemble
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::EnsembleEffectif(int qOuV,int aOuV)
{
	int i,j,n,nbElt;
	int flag;
	float total[N_X+1],totalRepro[N_X+1],totalAutre[N_X+1];

	CL_Troupeau *troupeau;
	CL_InvAni *invAni;
	CL_Vecteur<CL_InvAni> *vecteur;

	//compter nbElt à mettre dans grille
	nbElt=0;
	for(i=0;i<ChLBTroupeau->Count;i++)
	{
		troupeau=(CL_Troupeau*)ChLBTroupeau->Items->Objects[i];
		if(ChLBTroupeau->Checked[i]==true)
		nbElt+=troupeau->V_InvAni->Nbelt;
	}
	Forme01Frm->Origine=0;
	Forme01Frm->Show();

	memset(total,0,sizeof(float)*(N_X+1));
	if(qOuV==QUANTITE)
	{
		if(aOuV==ACHAT)
		{
//             Forme01Frm->IniGrilleStandard("Effectifs Achetés",N_X,nbElt,An_0);
			Forme01Frm->IniGrilleStandard(LC_EffAchat,N_X,nbElt,An_0);
			flag=0;
		}
		else //VENTE
		{
			Forme01Frm->IniGrilleStandard(LC_EffVente,N_X,nbElt,An_0);
			flag=1;
		}
	}
	else if(qOuV==VALEUR)
	{
		if(aOuV==ACHAT)
		{
			Forme01Frm->IniGrilleStandard(LC_ValAchat,N_X,nbElt+1,An_0);
			flag=2;
		}
		else //VENTE
		{
			Forme01Frm->IniGrilleStandard(LC_ValVente,N_X,nbElt+1,An_0);
			flag=3;
		}
	}
	else //VALINV
	{
		Forme01Frm->IniGrilleStandard(LC_ValInv,N_X+1,nbElt+3,An_0);
		flag=4;
		memset(total,0,sizeof(float)*(N_X+1));
		memset(totalRepro,0,sizeof(float)*(N_X+1));
		memset(totalAutre,0,sizeof(float)*(N_X+1));
	}
	for(i=0;i<ChLBTroupeau->Count;i++)
	{
		troupeau=(CL_Troupeau*)ChLBTroupeau->Items->Objects[i];
		if(ChLBTroupeau->Checked[i]==true)
		{
			vecteur=troupeau->V_InvAni;

			for(j=0;j<vecteur->Nbelt;j++)
			{
				invAni=vecteur->Vecteur[j];
				switch(flag)
				{
					case 0:
					Forme01Frm->EcrireLigne(invAni->Animal->Nom,invAni->Achat);
					break;
					case 1:
					Forme01Frm->EcrireLigne(invAni->Animal->Nom,invAni->Vente);
					break;
					case 2:
					Forme01Frm->EcrireLigne(invAni->Animal->Nom,invAni->ValAchat);
					for(n=0;n<N_X+1;n++) total[n]+=invAni->ValAchat[n];
					break;
					case 3:
					Forme01Frm->EcrireLigne(invAni->Animal->Nom,invAni->ValVente);
					for(n=0;n<N_X+1;n++) total[n]+=invAni->ValVente[n];
					break;
					case 4:
					Forme01Frm->EcrireLigne(invAni->Animal->Nom,invAni->Valeur);
					for(n=0;n<N_X+1;n++) total[n]+=invAni->Valeur[n];
					if(invAni->Reproducteur=='O')
					for(n=0;n<N_X+1;n++) totalRepro[n]+=invAni->Valeur[n];
					else
					for(n=0;n<N_X+1;n++) totalAutre[n]+=invAni->Valeur[n];
					break;
				}
			}
		}
	}

	if(flag==2||flag==3)
	{
		Forme01Frm->EcrireLigne("Total",total);
	}
	if(flag==4)
	{
		Forme01Frm->EcrireLigne("Total",total);
		Forme01Frm->EcrireLigne("Total Reproducteur",totalRepro);
		Forme01Frm->EcrireLigne("Total Autres",totalAutre);
	}
	Forme01Frm->LaGrille->Row=1;
}
//---------------------------------------------------------------------------
//        Produits Charges
//---------------------------------------------------------------------------

void __fastcall TTroupeauFrm::ProChaQ(void)
{
	int i;
	CL_Troupeau *troupeau;
	Agri->Resultat->Maz();
	AgriSaisieFrm->MazNFlagCat(); //pour repérer les catégories à imprimer si sortie
	AgriSaisieFrm->trouveTend(Agri);
	for(i=0;i<ChLBTroupeau->Count;i++)
	{
		troupeau=(CL_Troupeau*)ChLBTroupeau->Items->Objects[i];
		if(ChLBTroupeau->Checked[i]==true)
		AgriSaisieFrm->CalculDuTroupeau(Agri,troupeau,Agri->Resultat);
	}
	if(RBExcel->Checked==true)
	EX->Quantite(Agri);
	else
	QRSortieQuantFrm->Prepare(QUANTITE,Agri);
}
//-------------------------------------------------------------------------
void __fastcall TTroupeauFrm::ProChaV(void)
{
	int i;
	CL_Troupeau *troupeau;
	Agri->Resultat->Maz();
	AgriSaisieFrm->MazNFlagCat(); //pour repérer les catégories à imprimer si sortie
	AgriSaisieFrm->trouveTend(Agri);
	for(i=0;i<ChLBTroupeau->Count;i++)
	{
		troupeau=(CL_Troupeau*)ChLBTroupeau->Items->Objects[i];
		if(ChLBTroupeau->Checked[i]==true)
		{
			AgriSaisieFrm->CalculDuTroupeau(Agri,troupeau,Agri->Resultat);
			AgriSaisieFrm->CalculValeurAnimaux(Agri);
		}
	}

	if(RBQR->Checked==true)
	QRSortieValFrm->Prepare(ANIMAUX,Agri);
	if(RBExcel->Checked==true)
	EX->Valeur(Agri);

}
//---------------------------------------------------------------------------

