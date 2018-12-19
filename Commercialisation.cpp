//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "olympedec.h"
#include "Olympe.hse"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"
#include "Forme0.h"
#include "Forme01.h"

#include "TVChoixProduit.h"
#include "CL_Comm.h"
#include "AgriSaisie.h"
#include "CL_Trad.h"
#include "Aide.h"

#include "Commercialisation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCommercialisationFrm *CommercialisationFrm;

extern CL_ES *ES;
extern CL_Trad *T;
//---------------------------------------------------------------------------
__fastcall TCommercialisationFrm::TCommercialisationFrm(TComponent* Owner) :
		TForm(Owner) {
}
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::FormCreate(TObject *Sender)
{
	EstInitialise=false;
}
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::FormActivate(TObject *Sender)
{
	int c;
	int an;
	if(EstInitialise==false)
	{
		IniGrille();
		LstComm= new TList;
		EstInitialise=true;
		Item=NULL;
	}

	if(Origine==0)
	{
		//retirer ce qui n'est pas produit ou en stock à l'origine
		// ça peut arriver si l'assolement est modifié
		AgriSaisieFrm->PurgeLstQuantPrix();
		VideLesGrilles();
		CommEnCours=NULL;
		GrilleEnCours=NULL;
//        Item=NULL;

		Agri=AgriEnCours;
		An_0=Agri->DefSim->An_0;
		an=An_0-10;
		for(c=1;c<21;c++,an++)
		GrilleProd->Cells[c][0]="  "+AnsiString(an);
		an=An_0;
		for(c=1;c<11;c++,an++)
		GrilleComm->Cells[c][0]="  "+AnsiString(an);
		GrilleProd->Tag=0;
		GrilleComm->Tag=0;
		// pour les produits de l'agriculteur
		// cree CL_Comm où mettre Production Reste PrixRevient
		IniLstComm();

		//cree CBAn où choisir l'année dont on va créer/modifier
		//la commercialisation
		CBAn->Clear();
		CBAn->Text=L_Annee;//"Année";
		an=An_0-10;
		for(int i=0;i<20;i++,an++)CBAn->Items->Add(an);
		CBAn->ItemIndex=10;

		// pour pouvoir recopier
		CBAnCopie->Clear();
		CBAnCopie->Text=L_Annee;//"Année";
		an=An_0-10;
		for(int i=0;i<20;i++,an++)CBAnCopie->Items->Add(an);
		CBAnCopie->ItemIndex=10;
		ColOuCopier=11;

		// on se place au début de la simulation
		AnProd=An_0;
		ColComm=1;
		ColProd=11;
		if(Item) LabProduit->Caption=Item->Nom+"  "+Item->SysUnite->UTrans;
		else LabProduit->Caption="";
		//MarquerCell(ColProd,0);
		Origine=1;
	}
	/*
	 int i;
	 CL_Comm *comm;
	 CL_QuantPrix *quantPrix;
	 for(i=0;i<LstComm->Count;i++)
	 {
	 comm=(CL_Comm*)LstComm->Items[i];
	 }
	 for(i=0;i<Agri->LstQuantPrix->Count;i++)
	 {
	 quantPrix=(CL_QuantPrix*)Agri->LstQuantPrix->Items[i];
	 }
	 */
}
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	int i;
	CL_Comm *comm;
	if(LabelModifie->Visible==true)
	{
		if(VerifAnnee()==false) CanClose=false;
		else if( OnPeutStocker()==false) CanClose=false;
	}

	for(i=0;i<LstComm->Count;i++)
	{
		comm=(CL_Comm*)LstComm->Items[i];
		if(comm)delete comm;
	}

}
//---------------------------------------------------------------------------
bool __fastcall TCommercialisationFrm::OnPeutStocker(void)
{
	int n,rep;
	if(CommEnCours==NULL) return true; //070403
	for(n=0;n<N_X*2;n++)
	{
//    	if(CommEnCours->Reste[n]!=0)  020403
		if(CommEnCours->Reste[n]>1)
		{
			rep=MessageBox(Handle,L_Message.c_str(),L_MessT.c_str(),MB_YESNO|MB_ICONQUESTION);
			//rep=MessageBox(Handle,"Tout n'est pas vendu","Je Stocke ?",MB_YESNO|MB_ICONQUESTION);
			if(rep==ID_NO) return false;
			else
			{
				AjouterInvendu();
				break;
			}
		}
	}
	ES->ecrireFichier();
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::AjouterInvendu(void)
{
	int i,n;
	int anProd,anComm;
	CL_Item *item;
	CL_QuantPrix *quantPrix;
	int an_0=Agri->DefSim->An_0;
	anComm=an_0+N_X; //comme si ils étaient vendus aprés
	item=CommEnCours->Item;
	for(i=0;i<Agri->LstQuantPrix->Count;i++)
	{
		quantPrix=(CL_QuantPrix*)Agri->LstQuantPrix->Items[i];
		if(quantPrix->NoItem!=item->No) continue;
		if(quantPrix->AnComm!=anComm) continue;

		Agri->LstQuantPrix->Items[i]=NULL;
	}
	Agri->LstQuantPrix->Pack();

	for(n=0;n<N_X*2;n++)
	{
		if(CommEnCours->Reste[n]==0) continue;

		anProd=an_0+n-10;
		quantPrix=new CL_QuantPrix(item,anProd,anComm,CommEnCours->Reste[n],0);
		Agri->LstQuantPrix->Add(quantPrix);
		CommEnCours->Reste[n]==0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::BtBnQuitterClick(TObject *Sender)
{
	int rep;
	rep=MessageBox(Handle,T->L_QuitQ.c_str(),T->L_QuitT.c_str(),
			//rep=MessageBox(Handle,"Vous voulez vraiment quitter","QUITTER OLYMPE",
			MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDYES) Application->Terminate();
	else return;
}
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::IniGrille(void)
{
	int n,r;
	LabelModifie->Visible=false;
//    GrilleProd->Rows[0]->CommaText=L_TitreG;
	GrilleProd->Rows[0]->CommaText=".,Production,  Val Inventaire,  Reste";
	GrilleProd->Cells[0][1]="Production";
	GrilleProd->Cells[0][2]="Val Inventaire";
	GrilleProd->Cells[0][3]="Reste";
	GrilleProd->LeftCol=11;

	//Commercialisation
	// 8 possibilités de commercialiser
	for(n=1,r=1;n<=8;n++)
	{
		GrilleComm->Cells[0][r++]= AnsiString(n)+L_Quant; //"   Quantité";
		GrilleComm->Cells[0][r++]=L_Prix;//"    Prix";
		GrilleComm->Cells[0][r++]=L_Valeur;//"    Valeur";
	}
}
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::VideLesGrilles(void)
{
	VideGrille(GrilleProd);
	VideGrille(GrilleComm);
}
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::VideGrille(TStringGrid *grille)
{
	int r,c;
	for(r=1;r<grille->RowCount;r++)
	for(c=1;c<grille->ColCount;c++)
	grille->Cells[c][r]="";
}
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::IniLstComm(void)
{
	int i;
	CL_StockIni *stockIni;
	CL_Comm *comm;
	CL_QuantPrix *quantPrix;
	V_Produit->FlagMisA('N');
	// pour tout ce qui est produit quantite prixrevient reste

	// d'abord pour les produits dont il y a des stocks initiaux
	for(i=0;i<Agri->V_StockIni->Nbelt;i++)
	{
		stockIni=Agri->V_StockIni->Vecteur[i];
		// ce qui est produit pendant la simulation
		comm=TrouveComm(stockIni->Item);
		//ce qui a été produit avant et qui est en stock
		comm->InsereProdAvant(stockIni->Quantite);
		comm->InserePrixRevientAvant(stockIni->PrixRevient);
		stockIni->Item->Flag='O';
	}
	// puis pour les produits dont on déjà defini des ventes
	for(i=0;i<Agri->LstQuantPrix->Count;i++)
	{
		quantPrix=(CL_QuantPrix*)Agri->LstQuantPrix->Items[i];
		if(quantPrix->Item->Flag=='O') continue;

		comm=TrouveComm(quantPrix->Item);
//        comm->InsereProdAvant(quantPrix->Quantite);
//        comm->InserePrixRevientAvant(quantPrix->PrixRevient);
		quantPrix->Item->Flag='O';

	}

}
//---------------------------------------------------------------------------
CL_Comm* __fastcall TCommercialisationFrm::TrouveComm(CL_Item *item)
{
	int i,n;
	CL_AgriRes *agriRes;
	CL_QuanVal *quanVal;
	CL_Comm *comm;
	CL_FN_Xp1 *prixRevient;
	for(i=0;i<LstComm->Count;i++)
	{
		comm=(CL_Comm*)LstComm->Items[i];
		if(comm->Item==item)
		return comm;
	}
	// si il y a des stocks initiaux ils seront introduits aprés
	// au retour dans IniLstComm
	comm= new CL_Comm(item->No);
	agriRes=Agri->Resultat;
	for(i=0;i<agriRes->V_Produit->Nbelt;i++)
	{
		quanVal=agriRes->V_Produit->Vecteur[i];
		if(quanVal->Item==item)
		{
			comm->Item=item;
			comm->InsereProdApres(quanVal->Qte);
			prixRevient=Agri->V_PrixRevient->trouve(item->No); //si NULL !!
			if(prixRevient)
			comm->InserePrixRevientApres(prixRevient->Valeur);
			else
			for(n=N_X;n<N_X+10;n++)
			comm->PrixRevient[n]=item->Prix;
			break;
		}
	}

	LstComm->Add(comm);
	return comm;
}
//---------------------------------------------------------------------------
// verifier si tout est vendu et stocker avant de choisir l'autre produit
//Choix du Produit
//Extraction
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::BtBnProduitClick(TObject *Sender)
{
	if(VerifAnnee()==false) return;
	if(LabelModifie->Visible==true)
	if(OnPeutStocker()==false) return;

	Forme0Frm->CreeTVProduitComm(TVChoixProduitFrm->TV,V_CatProduit,
			Agri->V_Produits,Agri->V_StockIni);
	TVChoixProduitFrm->Show();
	TVChoixProduitFrm->Visible=true;
	//va determiner Item
}
//---------------------------------------------------------------------------
// on vient de choisr un nouvel Item
//   on trouve CommEnCours  CL_Comm
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::RetourDeTVChoixProduit(void)
{
	int i,n;
	CL_QuantPrix *quantPrix;
	VideLesGrilles();
	if(Item==NULL)
	{
		LabProduit->Caption="";
		return;
	}
	// le seul endroit ? où il est défini
	CommEnCours=TrouveComm(Item);
	memcpy(CommEnCours->Reste,CommEnCours->Production,sizeof(CommEnCours->Reste));
	//calcul ce qui reste
	for(i=0;i<Agri->LstQuantPrix->Count;i++)
	{
		quantPrix=(CL_QuantPrix*)Agri->LstQuantPrix->Items[i];
		if(quantPrix->NoItem==Item->No)
		{
			n=quantPrix->AnProd-An_0+10;
			if(quantPrix->AnComm>=An_0+10) continue;

			CommEnCours->Reste[n]-=quantPrix->Quant;
		}
	}
	LabProduit->Caption=Item->Nom+"  "+Item->SysUnite->UTrans;
	VersGrilleProd();

	AnProd=CBAn->ItemIndex+An_0-10;
	ColProd=CBAn->ItemIndex+1;

	MarquerCell(ColProd,0);
	VersGrilleComm();

	LabelModifie->Visible=false;
}
//---------------------------------------------------------------------------
// on a choisi Item
// on en a déduit CommEnCours

//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::VersGrilleProd(void)
{
	int c,j;

	for(c=1,j=0;c<21;c++,j++)
	{
		GrilleProd->Cells[c][1]=Aff(CommEnCours->Production[j],0);
		GrilleProd->Cells[c][2]=Aff(CommEnCours->PrixRevient[j],0);
		GrilleProd->Cells[c][3]=Aff(CommEnCours->Reste[j],0);
	}
}
//---------------------------------------------------------------------------
// reprend lst accrochée à GrilleProd->Objects[ColProd][0];
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::VersGrilleComm(void)
{
	int i;
	int c,r;
	int delta,digits;
	int p;
	CL_QuantPrix *quantPrix;
	//AnProd et ColProd dont définis à l'origine et modifiés par CBAnClick
	VideGrille(GrilleComm);
	// je suis dans l'année de production AnProd donc
	// elle correspond a la colonne ColProd de la grille GrilleProd
	//                              ColComm              GrilleComm
	r=1;

	for(i=0;i<Agri->LstQuantPrix->Count;i++)
	{
		quantPrix=(CL_QuantPrix*)Agri->LstQuantPrix->Items[i];
		if(quantPrix->NoItem!=Item->No) continue;
		if(quantPrix->AnProd!=AnProd) continue;

		delta=quantPrix->AnComm - quantPrix->AnProd;
		c=ColComm+delta;
		GrilleComm->Cells[c][r]= Aff(quantPrix->Quant,0);
		p=quantPrix->Prix;
		if(p==quantPrix->Prix)digits=0;
		else digits=2;
		GrilleComm->Cells[c][r+1]=Aff(quantPrix->Prix,digits);
		GrilleComm->Cells[c][r+2]=Aff(quantPrix->Quant*quantPrix->Prix,0);
		r+=3;
	}

}

//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::GrilleProdEnter(TObject *Sender)
{
	GrilleEnCours=GrilleProd;
	BtBnReportDroit->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::GrilleCommEnter(TObject *Sender)
{
	GrilleEnCours=GrilleComm;
	BtBnReportDroit->Enabled=false;
}
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::BtBnReportDroitClick(
		TObject *Sender)
{
	int c,c0;
	int r0;
	AnsiString as;
	if(CommEnCours==NULL)
	{
		ShowMessage(L_PasProd.c_str()); //"Vous n'avez pas choisi de Produit");
		return;
	}

	c0=GrilleProd->Col;
	r0=GrilleProd->Row;
	LabelModifie->Visible=true;
	GrilleProd->Tag=1;

	for(c=c0+1;c<GrilleProd->ColCount;c++)
	{
		as=GrilleProd->Cells[c][r0];
		if(as.Length()>1 && ChBRepTout->Checked==false) continue;

		GrilleProd->Cells[c][r0]=GrilleProd->Cells[c0][r0];
	}
}
//---------------------------------------------------------------------------
//fait le calcul q*p si on est sur ligne valeur
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::GrilleCommSelectCell(
		TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
	float quantite,prix,valeur;

	if(ARow%3==0)
	{
		quantite=GrilleFloat(GrilleComm,ACol,ARow-2);
		prix= GrilleFloat(GrilleComm,ACol,ARow-1);
		valeur=quantite*prix;
		GrilleComm->Cells[ACol][ARow]=Aff(valeur,0);
	}
	else
	{
		// pas de verif automatique c'est à l'utilisateur de le faire ->avecVerif=false
		CalculAffReste(ColProd,false);
	}
}
//---------------------------------------------------------------------------
// calcule et affiche le reste
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::CalculAffReste(int colProd, bool avecVerif)
{
	float qProd,totVente,reste;
	AnsiString as;
	qProd=CommEnCours->Production[colProd-1];
	totVente=TotVente(qProd,avecVerif);
	reste=qProd-totVente;
	GrilleProd->Cells[colProd][3]=Aff(reste,0);
	CommEnCours->Reste[colProd-1]=reste;
	if(reste <0)
	{
		//MessageBox(Handle,as.c_str(),T->L_Impo.c_str(),MB_ICONSTOP);
		MessageBox(Handle,"vente > production",T->L_Impo.c_str(),MB_ICONSTOP);
	}

}
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::GrilleProdSelectCell(
		TObject *Sender, int ACol, int ARow, bool &CanSelect)
{
	if(ARow==2 && ACol>=11 ) CanSelect=true;
	else CanSelect=false;
}
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::CBAnClick(TObject *Sender)
{
	bool rep;
	if(LabelModifie->Visible==true)
	{
		rep=VerifAnnee();
		if(rep==false)
		{
			CBAn->ItemIndex--;
			return;
		}
	}

	AnProd=CBAn->ItemIndex+An_0-10;
	ColProd=CBAn->ItemIndex+1;
	if(AnProd<=An_0) ColComm=1;
	else ColComm=AnProd-An_0+1;
	if(CBAn->ItemIndex<10)
	GrilleProd->LeftCol=ColProd;
	else
	GrilleProd->LeftCol=11;
	MarquerCell(ColProd,0);

	if(Item==NULL) return;

	VersGrilleComm();
}
// utlisé à chaque fois que l'on change d'année de production
// ET SI labelModifie->Visible=true
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::AutreAnnee(void)
{
	bool rep;
	if(LabelModifie->Visible==true)
	{
		rep=VerifAnnee();
		if(rep==false) return;
	}

	AnProd=GrilleProd->Col-1+An_0-10;
	ColProd=GrilleProd->Col;
//    MarquerCell(ColProd,1);
	if(AnProd<=An_0) ColComm=1;
	else ColComm=AnProd-An_0+1;
	/*
	 if(CBAn->ItemIndex<10)
	 GrilleProd->LeftCol=CBAn->ItemIndex+1;
	 else
	 GrilleProd->LeftCol=11;
	 */
	VersGrilleComm();
}
//---------------------------------------------------------------------------
// utilisé à chaque fois que l'on change d'année de production
//                                AffStock CopierAnnee
// ET SI labelModifie->Visible=true
//---------------------------------------------------------------------------
bool __fastcall TCommercialisationFrm::VerifAnnee(void)
{
	int i;
	int c,r;
	float quant,prix,totQuant;
	float prixRevient[N_X]; //il est délà dans CommEnCours mais il peut changer
	int anComm;
	int iProd;//exercice de production
	int rep;
	CL_QuantPrix *quantPrix;
	AnsiString as;

	if(LabelModifie->Visible==false) return true;

	// a t on modifie GrilleProd ?
	if(GrilleProd->Tag==1)
	{
		for(c=11,i=0;c<GrilleProd->ColCount;c++,i++)
		prixRevient[i]=GrilleFloat(GrilleProd,c,2);
		CommEnCours->InserePrixRevientApres(prixRevient);
	}

	// a t on modifie GrilleComm ?
	if(GrilleComm->Tag==1)
	{
		// verifier si on a vendu + ou - que produit
		as=L_TotVendu;//("Total Vendu  ");;
		// signaler si vente > Disponible ->avecVerif=false
		iProd=ColProd-1;
		totQuant=TotVente(CommEnCours->Production[iProd],false);
		if(totQuant<CommEnCours->Production[iProd])
		{
			as+=AnsiString(totQuant)+" < \n  "+L_TotProduit+CommEnCours->Production[iProd];
			//as+=AnsiString(totQuant)+" < \n"+" Total Produit"+CommEnCours->Production[iProd];
			rep=MessageBox(Handle,as.c_str(),L_Continuer.c_str(),MB_YESNO|MB_ICONQUESTION);
			//rep=MessageBox(Handle,as.c_str(),"On continue ?",MB_YESNO|MB_ICONQUESTION);
			if(rep==IDNO) return false;
		}
		else if(totQuant>CommEnCours->Production[iProd]+1) // verif à 1 pres  020403
		{
			as+=AnsiString(totQuant)+
			" > +\n "+L_TotProduit+CommEnCours->Production[iProd];
			MessageBox(Handle,as.c_str(),T->L_Impo.c_str(),MB_ICONSTOP);
			//MessageBox(Handle,as.c_str(),"Impossible !",MB_ICONSTOP);
			return false;
		}
		CalculAffReste(ColProd,false);
		//AnProd est défini en Cliquant sur l'année
		//retire tous les éléments pour cet Item et AnProd
		NettoieLstQuantPrix(Item,AnProd);
		// les mettre

		if(ColProd<=10)ColComm=1;
		else ColComm=ColProd-10;
		for(c=ColComm;c<GrilleComm->ColCount;c++)
		{
			totQuant=0;
			anComm=An_0+c-1;
			for(r=1;r<GrilleComm->RowCount;r+=3)
			{
				quant=GrilleFloat(GrilleComm,c,r);
				prix= GrilleFloat(GrilleComm,c,r+1);
				if(quant==0) continue;
				quantPrix=new CL_QuantPrix(Item,AnProd,anComm,quant,prix);
				Agri->LstQuantPrix->Add(quantPrix);
			}
		}
	}
	GrilleComm->Tag=0;
	GrilleProd->Tag=0;
	return true;
}
//---------------------------------------------------------------------------
float __fastcall TCommercialisationFrm::TotVente(float qProd,bool avecVerif)
{
	int c,r;
	float quant,totQuant;
	totQuant=0;
	for(c=ColComm;c<GrilleComm->ColCount;c++)
	{
		for(r=1;r<GrilleComm->RowCount;r+=3)
		{
			quant=GrilleFloat(GrilleComm,c,r);
			if(avecVerif==true)
			{
				if(quant>qProd) qProd-=quant;
				else {quant=qProd;qProd=0;totQuant+=quant;break;}
			}
			else
			totQuant+=quant;
		}
	}
	return totQuant;
}
//---------------------------------------------------------------------------
// utilisé à chaque fois que l'on change de produit
//                                ou que l'on sort
// ET SI labelModifie->Visible=true
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::NettoieLstQuantPrix(CL_Item *item,int anProd)
{
	int i;
	CL_QuantPrix *quantPrix;
	for(i=0;i<Agri->LstQuantPrix->Count;i++)
	{
		quantPrix=(CL_QuantPrix*)Agri->LstQuantPrix->Items[i];
		if(quantPrix->NoItem!=item->No) continue;
		if(quantPrix->AnProd!=anProd) continue;

		Agri->LstQuantPrix->Items[i]=NULL;
	}
	Agri->LstQuantPrix->Pack();
}
//---------------------------------------------------------------------------
// tableau récapitulatif
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::BtBnVenteQClick(TObject *Sender)
{
	AffVente(QUANTITE);
}
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::BtBnVenteValClick(TObject *Sender)
{
	AffVente(VALEUR);
}
//---------------------------------------------------------------------------
// les ventes de tous les produits indiqués cf RetourDeTVChoix
// QouV   QUANTITE ou VALEUR
// VouS   VENTE    ou STOCK
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::AffVente(int QouV)
{
	int i,j;
	int nbElt;
	float total[N_X];
	float vente[N_X];
	CL_Item *item;
	CL_Comm *comm;
	if(CommEnCours==NULL)
	{
		ShowMessage(L_PasProd); //"Vous n'avez pas choisi de Produit");
		return;
	}
	if(VerifAnnee()==false) return;

	nbElt=LstComm->Count;
	memset(total,0,sizeof(total));
	// en tete
	Forme01Frm->Show();

	if(QouV==QUANTITE)
	Forme01Frm->IniGrilleStandard(L_QVendu,N_X,nbElt+1,An_0);
	//Forme01Frm->IniGrilleStandard("Quantités Vendues",N_X,nbElt+1,An_0);
	else if(QouV==VALEUR)
	Forme01Frm->IniGrilleStandard(L_VVendu,N_X,nbElt+1,An_0);
	//Forme01Frm->IniGrilleStandard("Valeur des Ventes",N_X,nbElt+1,An_0);

	for(i=0;i<LstComm->Count;i++)
	{
		comm=(CL_Comm*)LstComm->Items[i];
		item=V_Produit->trouve(comm->NoItem);
		memset(vente,0,sizeof(vente));
		if(QouV==QUANTITE)
		{
			comm->CalculVenteQ(vente);
			Forme01Frm->EcrireLigne(item->Nom,vente);
			//for(j=0;j<N_X;j++) total[j]+=vente[j];
		}
		else if(QouV==VALEUR)
		{
			comm->CalculVenteV(vente);
			Forme01Frm->EcrireLigne(item->Nom,vente);
			for(j=0;j<N_X;j++) total[j]+=vente[j];
		}
	}
	if(QouV==VALEUR)
	Forme01Frm->EcrireLigne(T->L_Total,total);
	//Forme01Frm->EcrireLigne("Total",total);
}
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::BtBnStockQClick(TObject *Sender)
{
	AffStock(QUANTITE);
}
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::BtBnStockValClick(TObject *Sender)
{
	AffStock(VALEUR);
}
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::AffStock(int QouV)
{
	int i,j;
	int nbElt;
	float total[N_X+1];
	float stock[N_X*2];
	CL_Item *item;
	CL_Comm *comm;
	if(CommEnCours==NULL)
	{
		ShowMessage(L_PasProd); //"Vous n'avez pas choisi de Produit");
		return;
	}
	if(VerifAnnee()==false) return;

	// en tete
	nbElt=LstComm->Count;
	Forme01Frm->Show();

	if(QouV==QUANTITE)
	Forme01Frm->IniGrilleStandard(L_StockQ,N_X+1,nbElt+1,An_0);
	//Forme01Frm->IniGrilleStandard("Stock en Quantité",N_X+1,nbElt+1,An_0);
	if(QouV==VALEUR)
	Forme01Frm->IniGrilleStandard(L_StockV, N_X+1,nbElt+1,An_0);
	//Forme01Frm->IniGrilleStandard("Stock en Valeur",  N_X+1,nbElt+1,An_0);

	memset(total,0,sizeof(total));
	memset(stock,0,sizeof(stock));
	for(i=0;i<LstComm->Count;i++)
	{
		comm=(CL_Comm*)LstComm->Items[i];
		memset(stock,0,sizeof(total));
		item=V_Produit->trouve(comm->NoItem);
		if(QouV==QUANTITE)
		{
			comm->CalculStockQ(stock);
			Forme01Frm->EcrireLigne(item->Nom,&stock[9]);
			//for(j=0;j<N_X+1;j++) total[j]+=stock[j+N_X-1];
		}
		else if(QouV==VALEUR)
		{
			comm->CalculStockV(stock);
			Forme01Frm->EcrireLigne(item->Nom,&stock[9]);
			for(j=0;j<N_X+1;j++) total[j]+=stock[j+N_X-1];
		}
	}
	if(QouV==VALEUR)
	Forme01Frm->EcrireLigne(T->L_Total,total);

}

//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::BtBnCopierClick(TObject *Sender)
{
// on est dans l'année   AnProd   cf CBAnClick
// on veut recopier vers ColOuCopier   cf CBAnCopie
	int i;
	int anDest;
	CL_QuantPrix *quantPrix,*qP;
	if(CommEnCours==NULL)
	{
		ShowMessage(L_PasProd); //"Vous n'avez pas choisi de Produit");
		return;
	}

	if(LabelModifie->Visible==true)
	{
		if(VerifAnnee()==false) return;
	}

	if(ColOuCopier==ColProd)
	{
		ShowMessage(L_MemeAn); //"l'année où copier est la même");
		return;
	}
	anDest=AnProd+(ColOuCopier-ColProd);
	NettoieLstQuantPrix(Item,anDest);
	for(i=0;i<Agri->LstQuantPrix->Count;i++)
	{
		quantPrix=(CL_QuantPrix*)Agri->LstQuantPrix->Items[i];
		if(quantPrix->NoItem!=Item->No) continue;
		if(quantPrix->AnProd!=AnProd) continue;
		qP=new CL_QuantPrix(quantPrix);
		qP->AnProd+=ColOuCopier-ColProd;
		qP->AnComm+=ColOuCopier-ColProd;
		Agri->LstQuantPrix->Add(qP);
	}
	LabelModifie->Visible=true;
	GrilleComm->Tag=1;

	CalculAffReste(ColOuCopier,false);
}
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::BtBnCopieToutClick(TObject *Sender)
{
// on est dans l'année   AnProd   cf CBAnClick
// on veut recopier vers ColOuCopier   cf CBAnCopie
// prendre lstACopier
// le recopier dans lst de ColOuCopier
	int i,r,c,k;
	int anDest;
	CL_QuantPrix *quantPrix,*qP;
	float qProd,reste;
	float quant,totVente;

	if(CommEnCours==NULL)
	{
		ShowMessage(L_PasProd); //"Vous n'avez pas choisi de Produit");
		return;
	}

	if(LabelModifie->Visible==true)

	if(VerifAnnee()==false) return;

	// c =ColOuCopier      ce qui est en ColProd
	for(c=ColProd+1;c<N_X+10+1;c++)
	{
		totVente=0;
		qProd=CommEnCours->Production[c];

		anDest=AnProd+(c-ColProd);
		NettoieLstQuantPrix(Item,anDest);
		for(i=0;i<Agri->LstQuantPrix->Count;i++)
		{
			quantPrix=(CL_QuantPrix*)Agri->LstQuantPrix->Items[i];
			if(quantPrix->NoItem!=Item->No) continue;
			if(quantPrix->AnProd!=AnProd) continue;

			qP=new CL_QuantPrix(quantPrix);
			qP->AnProd+=c-ColProd;
			qP->AnComm+=c-ColProd;
			if(qP->Quant >quant )
			{	qP->Quant=qProd;qProd=0;}

			Agri->LstQuantPrix->Add(qP);
		}
		LabelModifie->Visible=true;
		GrilleComm->Tag=1;
//    	CalculAffReste(c,true);
		/*	    totVente=0;

		 qProd=CommEnCours->Production[c];
		 for(k=ColComm;k<GrilleComm->ColCount;k++)
		 {
		 for(r=1;r<GrilleComm->RowCount;r+=3)
		 {
		 quant=GrilleFloat(GrilleComm,k,r);
		 if(quant>qProd)   { quant=qProd;qProd=0;totVente+=quant;goto FIN; }
		 else              { qProd-=quant;totVente+=quant;}
		 }
		 }
		 FIN: ;
		 reste=qProd;//-totVente;
		 */
		GrilleProd->Cells[c][3]=Aff(qProd,0);
		CommEnCours->Reste[c-1]=qProd;
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::CBAnCopieClick(TObject *Sender)
{
	ColOuCopier=CBAnCopie->ItemIndex+1;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Util Grille
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::GrilleKeyPress(TObject *Sender,
		char &Key)
{
	int c,r;
//    if(GrilleComm->Focused()==true)
	if(GrilleEnCours==NULL) {Key=0;return;}
	if(GrilleEnCours==GrilleProd)
	{
		r=GrilleProd->Row;
		c=GrilleProd->Col;
		if(r==1) {Key=0;AutreAnnee();return;} //!!!!!! ?????
		if(r!=2) {Key=0;return;}
		if(c<ColComm) {Key=0;return;}
	}
	if(GrilleEnCours==GrilleComm)
	{
		if(GrilleComm->Row%3==0) {Key=0;return;} //la valeur est calculée

		c=GrilleComm->Col;
		if(c<ColComm)
		{
			ShowMessage(L_PasVenteAvt); //"Pas de vente avant la production\n à discuter");
			Key=0;
			return;
		}
	}
	LabelModifie->Visible=true;
	GrilleEnCours->Tag=1; //pour signaler que la grille a été modifiée
	if(Key >='0' && Key <='9') return;
	else if(Key=='.') return;
	else if(Key==VK_BACK) return;
	Key=0;
}
//-----------------------------------------------------------
AnsiString __fastcall TCommercialisationFrm::Aff(float x, int digits) {
	if (x == 0)
		return AnsiString(""); //"" ou " "      ????
	return FloatToStrF((double) x, ffNumber, 7, digits);
}
//-----------------------------------------------------------
float __fastcall TCommercialisationFrm::GrilleFloat(TStringGrid *grille,int col,int row)
{
	int n,c;
	AnsiString s;
	char car;
	char chaine[20];
	int point=0;
	if(grille->Cells[col][row].IsEmpty()==true) return 0.;
	s=grille->Cells[col][row];
	s=s.Trim();
	if(s=="" ||s=="."||s=="-") return 0.;
	c=0;
	for(n=1;n<s.Length()+1;n++)
	{
		car=s[n];
		if (car>='0' && car<='9') chaine[c++] =car;
		else if(car=='.' ||car==',')
		{
			if(point==0) {chaine[c++] ='.';point++;}
		}
		else if(car=='-' && c==0) chaine[c++] ='-';
	}
	chaine[c]=0;
	s=AnsiString(chaine);
	return s.ToDouble();
}
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::MarquerCell(int col,int row)
{
	TGridRect selection;
	row=3;
	selection.Left=col; //col-1
	selection.Right=col;
	selection.Top=0;
	selection.Bottom=row;
	GrilleProd->Selection=selection;
}
//---------------------------------------------------------------------------
void __fastcall TCommercialisationFrm::RgSupprimeClick(TObject *Sender)
{
	int i;
	int rep;
	AnsiString as;
	CL_QuantPrix *quantPrix;
	switch(RgSupprime->ItemIndex)
	{
		case 0:as=L_Eff+Item->Nom;break;
		case 1:as=L_EffTt;break;
		//case 0:as=AnsiString("J'efface ")+Item->Nom;break;
		//case 1:as=AnsiString(" J'efface Tout ");break;
		default:
		return;
	}

	rep=MessageBox(Handle,as.c_str(),L_Ok.c_str(),MB_YESNO|MB_ICONEXCLAMATION);
	if(rep==IDNO)
	{
		RgSupprime->ItemIndex=-1;
		return;
	}

	switch(RgSupprime->ItemIndex)
	{
		case 0:
		for(i=0;i<Agri->LstQuantPrix->Count;i++)
		{
			quantPrix=(CL_QuantPrix*)Agri->LstQuantPrix->Items[i];
			if(quantPrix->NoItem==Item->No)
			{
				delete quantPrix;
				Agri->LstQuantPrix->Items[i]=NULL;
			}
		}
		VideLesGrilles();
		Agri->LstQuantPrix->Pack();
		break;
		case 1:
		for(i=0;i<Agri->LstQuantPrix->Count;i++)
		{
			quantPrix=(CL_QuantPrix*)Agri->LstQuantPrix->Items[i];
			delete quantPrix;
		}
		Agri->LstQuantPrix->Clear();
		break;
	}
	LabelModifie->Visible=false;
	RgSupprime->ItemIndex=-1;
}
//---------------------------------------------------------------------------

void __fastcall TCommercialisationFrm::BtBnResteClick(TObject *Sender)
{
	float qProd,totVente,reste;
	int c,r;
	c=GrilleComm->Col;
	r=GrilleComm->Row;

	qProd=CommEnCours->Production[ColProd-1];
	totVente=TotVente(qProd,false);
	reste=qProd-totVente;
	GrilleComm->Cells[c][r]=Aff(reste,0);

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TCommercialisationFrm::TexteChaine(void) {
	L_Annee = T->TrouveTexte("CommercialisationFrm", "L_Annee");
	L_Message = T->TrouveTexte("CommercialisationFrm", "L_Message");
	L_MessT = T->TrouveTexte("CommercialisationFrm", "L_MessT");
	L_TitreG = T->TrouveTexte("CommercialisationFrm", "L_TitreG");
	L_Quant = T->TrouveTexte("CommercialisationFrm", "L_Quant");
	L_Prix = T->TrouveTexte("CommercialisationFrm", "L_Prix");
	L_Valeur = T->TrouveTexte("CommercialisationFrm", "L_Valeur");
	L_PasProd = T->TrouveTexte("CommercialisationFrm", "L_PasProd");
	L_TotVendu = T->TrouveTexte("CommercialisationFrm", "L_TotVendu");
	L_TotProduit = T->TrouveTexte("CommercialisationFrm", "L_TotProduit");
	L_Continuer = T->TrouveTexte("CommercialisationFrm", "L_Continuer");
//	L_Impo              =T->TrouveTexte("CommercialisationFrm","L_Impo");
	L_QVendu = T->TrouveTexte("CommercialisationFrm", "L_QVendu");
	L_VVendu = T->TrouveTexte("CommercialisationFrm", "L_VVendu");
	L_StockQ = T->TrouveTexte("CommercialisationFrm", "L_StockQ");
	L_StockV = T->TrouveTexte("CommercialisationFrm", "L_StockV");
	L_MemeAn = T->TrouveTexte("CommercialisationFrm", "L_MemeAn");
	L_PasVenteAvt = T->TrouveTexte("CommercialisationFrm", "L_PasVenteAvt");
	L_Eff = T->TrouveTexte("CommercialisationFrm", "L_Eff");
	L_EffTt = T->TrouveTexte("CommercialisationFrm", "L_EffTt");
	L_Ok = T->TrouveTexte("CommercialisationFrm", "L_Ok");
}
//---------------------------------------------------------------------------
void TCommercialisationFrm::IniCaption(void) {
	LabAnnee->Caption = LC_LabAnnee;
	CommercialisationFrm->Caption = T->LC_Commercialisation1;
	BtBnCopieTout->Caption = LC_BtBnCopieTout;
	BtBnCopier->Caption = T->LC_BtBnCopier_A;
	LabProduit->Caption = LC_LabProduit;
	LabelModifie->Caption = T->LC_LabelModifie_A;
	BtBnProduit->Caption = T->LC_BtBnProduit;
	LabQuant->Caption = LC_LabQuant;
	BtBnQuitter->Caption = T->LC_BtBnQuitter;
	ChBRepTout->Caption = T->LC_ChBRepTout;
	BtBnReste->Caption = LC_BtBnReste;
	BtBnStockQ->Caption = T->LC_S1;
	BtBnStockVal->Caption = T->LC_S1;
	RgSupprime->Caption = T->LC_BtBnSupBesTrav;
	LabVal->Caption = T->LC_LabVal;
	BtBnVenteQ->Caption = T->LC_BtBnVenteQ;
	BtBnVenteVal->Caption = T->LC_BtBnVenteQ;
	RgSupprime->Items->Strings[0] = LC_EnCours;
	RgSupprime->Items->Strings[1] = LC_Tout;
}
//--------------------------------------------
void TCommercialisationFrm::TexteCaption(void) {
	LC_LabAnnee = T->TrouveCaption("Commercialisation", "LC_LabAnnee");
	LC_Commercialisation1 = T->TrouveCaption("CL_Trad",
			"LC_Commercialisation1");
	LC_BtBnCopieTout = T->TrouveCaption("Commercialisation",
			"LC_BtBnCopieTout");
	LC_BtBnCopier_A = T->TrouveCaption("CL_Trad", "LC_BtBnCopier_A");
	LC_LabProduit = T->TrouveCaption("Commercialisation", "LC_LabProduit");
	LC_LabelModifie_A = T->TrouveCaption("CL_Trad", "LC_LabelModifie_A");
	LC_BtBnProduit = T->TrouveCaption("CL_Trad", "LC_BtBnProduit");
	LC_LabQuant = T->TrouveCaption("Commercialisation", "LC_LabQuant");
	LC_BtBnQuitter = T->TrouveCaption("CL_Trad", "LC_BtBnQuitter");
	LC_ChBRepTout = T->TrouveCaption("CL_Trad", "LC_ChBRepTout");
	LC_BtBnReste = T->TrouveCaption("Commercialisation", "LC_BtBnReste");
	LC_S1 = T->TrouveCaption("CL_Trad", "LC_S1");
	LC_BtBnSupBesTrav = T->TrouveCaption("CL_Trad", "LC_BtBnSupBesTrav");
	LC_LabVal = T->TrouveCaption("CL_Trad", "LC_LabVal");
	LC_BtBnVenteQ = T->TrouveCaption("CL_Trad", "LC_BtBnVenteQ");
	LC_EnCours = T->TrouveCaption("Commercialisation", "LC_EnCours");
	LC_Tout = T->TrouveCaption("Commercialisation", "LC_Tout");
	;

	IniCaption();

}

bool __fastcall TCommercialisationFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=0;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

