//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>

#pragma hdrstop
#include "AgriSaisie.h"

#include "InvAniProCha.h"
#include "Troupeau.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------

//  DE Grille
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::DeGrilleMaxi(TStringGrid *grille)
{
	int row;
	int c;
	int n;
	CL_InvAni *invAni;

	for(row=1;row<grille->RowCount;row++)
	{
		invAni=(CL_InvAni*)grille->Objects[0][row];
		for(n=0,c=2;n<N_X;n++,c++)
		{
			if(grille->Cells[c][row]=="")
			invAni->EffMax[n]=SANSBORNE;
			else
			invAni->EffMax[n]=GrilleFloat(c,row);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::DeGrillePrix(TStringGrid *grille)
{
	int row;
	int c;
	int n;
	CL_InvAni *invAni;
	for(row=1;row<grille->RowCount;row++)
	{
		invAni=(CL_InvAni*)grille->Objects[0][row];
		for(n=0,c=2;n<N_X;n++,c++)
		invAni->PrixVenteMoy[n]= GrilleFloat(c,row);
	}
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::DeGrilleAchat(TStringGrid *grille)
{
	int row;
	int c;
	int n;
	CL_InvAni *invAni;
	for(row=1;row<grille->RowCount;row++)
	{
		invAni=(CL_InvAni*)grille->Objects[0][row];
		for(n=0,c=2;n<N_X;n++,c++)
		invAni->AAcheter[n]= GrilleFloat(c,row);
	}
//    CreeLstAchat();
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::DeGrillePrixAchat(TStringGrid *grille)
{
	int row;
	int c;
	int n;
	CL_InvAni *invAni;
	for(row=1;row<grille->RowCount;row++)
	{
		invAni=(CL_InvAni*)grille->Objects[0][row];
		for(n=0,c=2;n<N_X;n++,c++)
		invAni->PrixAchat[n]= GrilleFloat(c,row);
	}
//    CreeLstAchat();
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::DeGrilleValInv(TStringGrid *grille)
{
	int row;
	int c;
	int n;
	CL_InvAni *invAni;
	for(row=1;row<grille->RowCount;row++)
	{
		invAni=(CL_InvAni*)grille->Objects[0][row];
		invAni->Reproducteur=GrilleCar(2,row);
		for(n=0,c=3;n<N_X+1;n++,c++)
		invAni->ValInvMoy[n]= GrilleFloat(c,row);
	}
}

//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::DeGrilleProCha(TStringGrid *grille)
{
	int row;
	int c;
	int n;
	CL_InvAni *invAni;
	for(row=1;row<grille->RowCount;row++)
	{
		invAni=(CL_InvAni*)grille->Objects[0][row];
		for(n=0,c=2;n<N_X;n++,c++)
		{
			invAni->Atelier[n]=(CL_Atelier*)grille->Objects[c][row];
			if(invAni->Atelier[n])
			invAni->NoAtelier[n]=invAni->Atelier[n]->No;
			else
			invAni->NoAtelier[n]=-1;
		}
	}
}
//---------------------------------------------------------------------------
/// pour stocker   invani et les mvt
//le minimum
/// creer LstMvtAni
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::CreeLstMvtAni(void)
{
	int r,col;
	int i;
	int date;
	CL_InvAni* invAni;
	CL_MvtAnnee* mvtAnnee;
	CL_MvtAni* mvtAni;
	//ShowMessage("CreeLstMvtAni");
	//Vide  LstMvtAni;
	if(LstMvtAni==NULL) return;

	for(i=0;i<LstMvtAni->Count;i++)
	{
		mvtAni=(CL_MvtAni *)LstMvtAni->Items[i];
		delete mvtAni;

	}
	LstMvtAni->Count=0;

	for(r=1;r<GrilleMvt->RowCount;r++)
	{
		invAni=(CL_InvAni*)GrilleMvt->Objects[0][r];
		if(invAni==NULL) continue;

		// aucun rapport avec LstMvtAni A déplacer
		memset(invAni->Effectif,0,sizeof(invAni->Effectif));
		memset(invAni->Valeur, 0,sizeof(invAni->Valeur));
		memset(invAni->Vente, 0,sizeof(invAni->Vente));
		memset(invAni->Achat, 0,sizeof(invAni->Achat));
		memset(invAni->ValVente,0,sizeof(invAni->ValVente));
		memset(invAni->ValAchat,0,sizeof(invAni->ValAchat));

		// valeurs initiales
		mvtAnnee=(CL_MvtAnnee*)GrilleMvt->Objects[Col0][r];
		invAni->Effectif[0] =mvtAnnee->Debut;
		invAni->Valeur[0] =mvtAnnee->Debut*invAni->ValInvMoy[0];

		for(col=Col0;col<GrilleMvt->ColCount;col++)
		{
			date=col-Col0;
			mvtAnnee=(CL_MvtAnnee*)GrilleMvt->Objects[col][r];

			//Effectif
			invAni->Effectif[date+1]=mvtAnnee->Fin;
			invAni->Valeur[date+1] =mvtAnnee->Fin*invAni->ValInvMoy[date+1];

			//Vente
			if(mvtAnnee->iVente >0)
			{
				//d'abord la regulation
				i=mvtAnnee->iRegul;
				//VENTE vente décidée par olympe
				//VDECIS vente décidée par l'utilisateur
				if(i>=0)
				{
					mvtAni=new CL_MvtAni(r,date,VENTE,
							mvtAnnee->Vente[i],mvtAnnee->PrixVente[i]);
					LstMvtAni->Add(mvtAni);
					invAni->Vente[date]+=mvtAnnee->Vente[i];
					invAni->ValVente[date]+=mvtAnnee->Vente[i]*mvtAnnee->PrixVente[i];
				}
				for(i=0;i<mvtAnnee->iVente;i++)
				{
					if(i==mvtAnnee->iRegul) continue;

					mvtAni=new CL_MvtAni(r,date,VDECIS,
							mvtAnnee->Vente[i],mvtAnnee->PrixVente[i]);

					LstMvtAni->Add(mvtAni);
					invAni->Vente[date]+=mvtAnnee->Vente[i];
					invAni->ValVente[date]+=mvtAnnee->Vente[i]*mvtAnnee->PrixVente[i];
				}
			}
			//Achat
			if(mvtAnnee->iAchat >0)
			{
				//d'abord les imposés
				i=mvtAnnee->iAchatAuto;
				if(i>=0)
				{
					mvtAni=new CL_MvtAni(r,date,AACHETER,
							mvtAnnee->Achat[i],mvtAnnee->PrixAchat[i]);
					LstMvtAni->Add(mvtAni);
					invAni->Achat[date]+=mvtAnnee->Achat[i];
					invAni->ValAchat[date]+=mvtAnnee->Achat[i]*mvtAnnee->PrixAchat[i];
				}
				for(i=0;i<mvtAnnee->iAchat;i++)
				{
					if(i==mvtAnnee->iAchatAuto) continue;

					mvtAni=new CL_MvtAni(r,date,ACHAT,
							mvtAnnee->Achat[i],mvtAnnee->PrixAchat[i]);
					LstMvtAni->Add(mvtAni);

					invAni->Achat[date]+=mvtAnnee->Achat[i];
					invAni->ValAchat[date]+=mvtAnnee->Achat[i]*mvtAnnee->PrixAchat[i];
				}
			}
			//Naissance
			if(mvtAnnee->Ne>0)
			{
				//mvtAni=new CL_MvtAni(noAnimal,date,NE,
				mvtAni=new CL_MvtAni(r,date,NE,
						mvtAnnee->Ne,0);
				LstMvtAni->Add(mvtAni);
			}
			//Mort
			if(mvtAnnee->Mort>0)
			{
//                mvtAni=new CL_MvtAni(noAnimal,date,MORT,
				mvtAni=new CL_MvtAni(r,date,MORT,
						mvtAnnee->Mort,0);
				LstMvtAni->Add(mvtAni);
			}
			//Sortie
			if(mvtAnnee->iDest>0)
			{
				for(i=0;i<mvtAnnee->iDest;i++)
				{
					mvtAni=new CL_MvtAni(r,date,MVT,
							mvtAnnee->Sortie[i],(float)mvtAnnee->Destin[i]);
					LstMvtAni->Add(mvtAni);
				}
			}
			//recalculé à la lecture
		}
	}
//    pour test
	//EcritLstMvtAni(LstMvtAni);
}
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::EcritLstMvtAni(TList *lstMvtAni)
{
	int i;
	CL_MvtAni* mvtAni;
	ofstream outfile("LstMvtAni.txt");
	AnsiString date;
	TDateTime time;
//bool aFermer;

	time=TDateTime::CurrentDateTime();
	date=time.DateTimeString();

	outfile << date.c_str() <<endl;

	outfile << "n° r type          date Eff Info "<< endl;
	for(i=0;i<lstMvtAni->Count;i++)
	{
		mvtAni=(CL_MvtAni*)lstMvtAni->Items[i];
//        if(mvtAni->Type!=AACHETER) continue;

		outfile << i <<" " << mvtAni->Ligne <<" "<<mvtAni->Type<<" ";

		switch(mvtAni->Type)
		{
			case MVT: outfile <<" MVT        ";break;
			case VENTE: outfile <<" VENTE      ";break;
			case ACHAT: outfile <<" ACHAT      ";break;
			case NE: outfile <<" NE         ";break;
			case MORT: outfile <<" MORT       ";break;
			case BESTIAUX: outfile <<" BESTIAUX   ";break;
			case VDECIS: outfile <<" VDECIS     ";break;
			case AACHETER: outfile <<" AACHETER   ";break;

		}
		outfile << mvtAni->Date<<" "<< mvtAni->Eff<<" "<< mvtAni->Info << endl;
	}
	outfile.close();

	ShowMessage("LstMvtAni.txt   est consultable");
}

//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::CreeLstAchat(void)
{
	/*
	 int i,r,n;
	 CL_InvAni   *invAni;
	 CL_MvtAni*   mvtAni;

	 for(i=0;i<LstAchat->Count;i++)
	 {
	 mvtAni=(CL_MvtAni *)LstAchat->Items[i];
	 delete mvtAni;
	 }
	 LstAchat->Count=0;
	 */
	/*
	 // les grilles ont le meme nombre de lignes et contiennent tjrs invAni
	 for(r=1;r<GrilleMvt->RowCount;r++)
	 {
	 invAni=(CL_InvAni*)GrilleMvt->Objects[0][r];
	 if(invAni==NULL) continue; //troupeau supprimé 200305
	 for(n=0;n<N_X;n++)
	 {
	 if(invAni->AAcheter[n]!=0 ||invAni->PrixAchat[n]!=0)
	 {
	 mvtAni=new CL_MvtAni(r,n,AACHETER,
	 invAni->AAcheter[n],invAni->PrixAchat[n]);
	 LstAchat->Add(mvtAni);

	 }
	 }
	 }
	 */
}

