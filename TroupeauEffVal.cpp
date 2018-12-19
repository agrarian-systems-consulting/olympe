//---------------------------------------------------------------------------

#pragma hdrstop

//#include "TroupeauEffVal.h"
#include "Troupeau.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
void __fastcall TTroupeauFrm::CompleteInvAni(void)
{
	int r,col,i,j;
	int n;
	int eff;
	float val;
	CL_InvAni *invAni;
	CL_MvtAnnee *mvtAnnee;
//float valInv;
	for(r=1;r<GrilleMvt->RowCount;r++)
	{
		invAni=(CL_InvAni*)GrilleMvt->Objects[0][r];
		if(invAni==NULL) continue;
		for(col=Col0;col<GrilleMvt->ColCount;col++)
		{
			n=col-Col0;
			mvtAnnee=(CL_MvtAnnee*)GrilleMvt->Objects[col][r];

			if(n==0)
			invAni->Effectif[0] =mvtAnnee->Debut;

			invAni->Effectif[n+1]=mvtAnnee->Fin;
			invAni->Valeur[n+1] =invAni->Effectif[n+1]*invAni->ValInvMoy[n+1];

			// achat
			eff=0;
			val=0;
			for(i=0;i<mvtAnnee->iAchat;i++)
			{
				eff+=mvtAnnee->Achat[i];
				val+=mvtAnnee->Achat[i]*mvtAnnee->PrixAchat[i];
			}
			invAni->Achat[n]= eff;
			invAni->ValAchat[n]= val;

			// vente
			eff=0;
			val=0;
			for(i=0;i<mvtAnnee->iVente;i++)
			{
				eff+=mvtAnnee->Vente[i];
				val+=mvtAnnee->Vente[i]*mvtAnnee->PrixVente[i];
			}
			invAni->Vente[n]= eff;
			invAni->ValVente[n]= val;

		}
		for(j=0;j<N_X+1;j++)
		invAni->Valeur[j]=invAni->ValInvMoy[j]*invAni->Effectif[j];
	}
}

