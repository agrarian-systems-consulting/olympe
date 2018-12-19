//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Erreur.h"
#include "LBTva.h"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "FichierLire.h"
#include "LesVecteurs.hse"
#include "TVDico.h"

#include "QRGrille00.h"
#include "Erreur.h"
#include "CL_Trad.h"
#include "NoteAgri.h"
#include "Aide.h"

#include "DefBestiaux.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DefItem"
#pragma resource "*.dfm"
TDefBestiauxFrm *DefBestiauxFrm;

extern CL_ES *ES;
extern CL_Trad *T;

//---------------------------------------------------------------------------
__fastcall TDefBestiauxFrm::TDefBestiauxFrm(TComponent* Owner) :
		TDefItemFrm(Owner) {
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TDefBestiauxFrm::Personnaliser(void)
{
	LabCatVar->Caption=Categorie->Nom;
	Caption=L_MvtTroupeau; //="Mouvements du Troupeau";
	//Caption="Mouvements du Troupeau";

	BtBnTva->Visible=true;
	BtBnUnite->Visible=false;

	Grille0->ColCount=15;
	Grille0->Rows[0]->CommaText=L_Titre;//=".,.,NOM,ValInventaire,Prix/tete,Tva,Origine,Génére,%,Génére,%,Génére,%,Génére,%";
	//Grille0->Rows[0]->CommaText=".,.,NOM,ValInventaire,Prix/tete,Tva,Origine,Génére,%,Génére,%,Génére,%,Génére,%";

	strcpy(TypeCol,"00TNNONNNNNNNN");
	ColNom=2;
	ColTva=5;
//    ColSys=3;
//    ColPrix=4;
	//incomplet le tableau est trés différent

}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TDefBestiauxFrm::IniGrille(TStringGrid *grille)
{
	int c;
//               0  1  2   3  4  5  6  7 8  9  10 11 12 13 14 15
	int largeur[]= {20,10,128,64,64,64,96,40,40,40,40,40,40,40,40,40,40};

	Grille0->Width=0;
	for(c=0;c<Grille0->ColCount;c++)
	{
		Grille0->ColWidths[c]=largeur[c];
		Grille0->Width+=largeur[c];
	}
	Grille0->Width+=30; //place pour l'ascenseur
	Grille0->FixedCols=2;
	Grille0->FixedRows=1;
	AjoutRow=true;

}
//---------------------------------------------------------------------------
bool __fastcall TDefBestiauxFrm::ControleCell(int col,int row)
{
	AnsiString pasDeNom("??????");
	CL_Bestiaux* bestiaux;
	int colNom=2;
	if(RowVide(row)==true )return true;

	bestiaux=(CL_Bestiaux*)LaGrille->Objects[0][row];
	/// nom
	if(col==colNom)
	if(NomCorrect(col,row)==false)return false;

	if(bestiaux==NULL)
	{
		bestiaux=new CL_Bestiaux;
		bestiaux->Flag='N';
		bestiaux->Supprimable=true;
		bestiaux->Categorie=Categorie;
		bestiaux->NoCategorie=Categorie->No;
		LaGrille->Objects[0][row]=(TObject*)bestiaux;
		LaGrille->Cells[0][row]=row;
	}
	else if(bestiaux->Flag!='N')
	bestiaux->Flag='M';

	bestiaux->Nom=LaGrille->Cells[2][row];
	return true;
}

//---------------------------------------------------------------------------
void __fastcall TDefBestiauxFrm::VersGrille(TStringGrid *grille)
{
	int row,r;
	AnsiString value;
	CL_Bestiaux *bestiaux;
	int nLigne=0;
	if(V_Bestiaux==NULL)
	return;
	// nb ligne de la grille
	for( r=0;r<V_Bestiaux->Nbelt;r++)
	{
		bestiaux=V_Bestiaux->Vecteur[r];
		if(bestiaux->Categorie!=Categorie) continue;
		nLigne++;
	}
	grille->RowCount=nLigne+3;
	LaGrille=grille;
	row=1;
	for( r=0;r<V_Bestiaux->Nbelt;r++)
	{
		bestiaux=V_Bestiaux->Vecteur[r];
		bestiaux->Flag='O'; //Flag =O est d'origine peut devenir M si modifié N pour nouveau
		if(bestiaux->Categorie!=Categorie) continue;
		grille->Objects[0][row]=(TObject*)bestiaux;

		grille->Cells[0][row]=row;
		AffBestiaux (row,bestiaux);
		if(bestiaux->Supprimable==false) grille->Cells[1][row]='*';
		row++;
	}
	CellInitiale(2,1);
}

//---------------------------------------------------------------------------
void __fastcall TDefBestiauxFrm::AffBestiaux(int row,CL_Bestiaux *bestiaux)
{
	int n,c;
	LaGrille->Cells[2][row]=bestiaux->Nom;
	LaGrille->Cells[3][row]=Aff(bestiaux->ValInv,2);
	LaGrille->Cells[4][row]=Aff(bestiaux->Prix,2);
	LaGrille->Cells[5][row]=bestiaux->Tva->Nom;
	if(bestiaux->NoOrigine!=-1)
	LaGrille->Cells[6][row]=Aff(bestiaux->NoOrigine);
	for(n=0,c=7;n<4;n++,c+=2)LaGrille->Cells[c][row]=Aff(bestiaux->DonneNo[n]);
	for(n=0,c=8;n<4;n++,c+=2)LaGrille->Cells[c][row]=Aff(bestiaux->DonnePcent[n]);

	LaGrille->Objects[0][row]=(TObject*)bestiaux;
	LaGrille->Objects[ColTva][row]=(TObject*)bestiaux->Tva;

}
//---------------------------------------------------------------------------
void __fastcall TDefBestiauxFrm::BtBnTvaClick(TObject *Sender)
{
	LBTvaFrm->AppelePar="DefBestiauxFrm";
	LBTvaFrm->Show();
}
//---------------------------------------------------------------------------
void __fastcall TDefBestiauxFrm::RetourDeChoixTva (CL_Tva *tva)
{
	int row;
	CL_Item* item;
	row=LaGrille->Row;
	item=(CL_Item*)LaGrille->Objects[0][row];
	if(item==NULL)
	{
		ShowMessage(T->L_NonDef);
		//ShowMessage("Elément non défini");
		return;
	}

	LaGrille->Objects[ColTva][row]=(TObject*)tva;
	LaGrille->Cells[ColTva][row]=tva->Nom;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TDefBestiauxFrm::BtRepBasClick(TObject *Sender)
{
	int row,col;
	AnsiString prix;
	CL_Item *item;
	CL_Tva *tva;
	row=LaGrille->Row;
	col=LaGrille->Col;
	item=(CL_Item*)LaGrille->Objects[0][row];
	if(item==NULL) return;

	switch(col)
	{
		case 3: //valInv
		case 4://prix
		prix=LaGrille->Cells[col][row];
		RepBasPrix(prix,col);
		break;
		case 5://tva
		tva=(CL_Tva*)LaGrille->Objects[ColTva][row];
		RepBasTva(tva);
		break;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TDefBestiauxFrm::VerifGrille(TStringGrid *grille)
{
	int r,n;
	char buf[100];
	CL_Bestiaux *bestiaux;
	AnsiString as;
	CL_Tva *tva;
	ErreurAAfficher=false;
	VerifExistenceNom(grille);

	for(r=1;r<grille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;

		bestiaux=(CL_Bestiaux*)LaGrille->Objects[0][r];

		//val inventaire
		if(grille->Cells[3][r].IsEmpty()==true)
		{
			ErreurAAfficher=true;
			wsprintf(buf,L_PasValInv.c_str(),r);
			//wsprintf(buf,"Pas de Valeur Inventaire ligne %d ",r);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		//prix
		if(grille->Cells[4][r].IsEmpty()==true)
		{
			ErreurAAfficher=true;
			wsprintf(buf,L_PasPrix.c_str(),r);
			//wsprintf(buf,"Pas de Prix ligne %d ",r);
			ErreurFrm->Edit->Lines->Add(buf);
		}
		///tva
		tva=(CL_Tva*)LaGrille->Objects[ColTva][r];
		if(tva==NULL)
		{
			LaGrille->Objects[ColTva][r]=(TObject*)TvaDefaut;
			LaGrille->Cells[ColTva][r]=TvaDefaut->Nom;
		}
		/// Origine
		if(grille->Cells[6][r].IsEmpty()==true )
		bestiaux->NoOrigine=-1;
		else
		{
			n=GrilleInt(6,r);
			if(n>grille->RowCount)
			{
				ErreurAAfficher=true;
				wsprintf(buf,L_PasOrigine.c_str(),r);
				//wsprintf(buf,"Origine Inconnue ligne %d ",r);
				ErreurFrm->Edit->Lines->Add(buf);
				break;
			}
			else if(RowVide(n)==true)
			{
				ErreurAAfficher=true;
				wsprintf(buf,L_PasOrigine.c_str(),r);
				//wsprintf(buf,"Origine Inconnue ligne %d ",r);
				ErreurFrm->Edit->Lines->Add(buf);
				break;
			}
			else if(n==r)
			{
				ErreurAAfficher=true;
				wsprintf(buf,L_OretDest.c_str(),r);
				//wsprintf(buf,"Origine et Destination identiques ligne %d ",r);
				ErreurFrm->Edit->Lines->Add(buf);
				break;
			}
			else
			{
				int n0;
				for(int r0=1;r0<grille->RowCount;r0++)
				{
					if(r0==r) continue;

					n0=GrilleInt(6,r0);
					if(n0==n)
					{
						ErreurAAfficher=true;
						wsprintf(buf,L_MemeOrig.c_str(),r,r0);
						//wsprintf(buf,"lignes %d %d même Origine ",r,r0);
						ErreurFrm->Edit->Lines->Add(buf);
						break;
					}
				}
			}
			bestiaux=(CL_Bestiaux*)LaGrille->Objects[0][r];
			bestiaux->NoOrigine=n;
		}
	}
	if(ErreurAAfficher==true)return false;
	else return true;
}
//------------------------------------------------------------------------------
void __fastcall TDefBestiauxFrm::LireBestiaux(CL_Bestiaux *bestiaux,int row)
{
	int n,c;
	AnsiString value;
	bestiaux->Tva=(CL_Tva*)LaGrille->Objects[ColTva][row];
	bestiaux->NoTva=bestiaux->Tva->No;

	bestiaux->Nom =Grille0->Cells[ColNom][row];
	bestiaux->Categorie =Categorie;
	bestiaux->NoCategorie=Categorie->No;
	bestiaux->ValInv =GrilleFloat(3,row);
	bestiaux->Prix =GrilleFloat(4,row);
	for(n=0,c=7;n<4;n++,c+=2)bestiaux->DonneNo[n]=GrilleInt(c,row);
	for(n=0,c=8;n<4;n++,c+=2)bestiaux->DonnePcent[n]=GrilleFloat(c,row);
}

//---------------------------------------------------------------------------
void __fastcall TDefBestiauxFrm::BtClHautClick(TObject *Sender)
{
	int row,r,r0,r1;
	int c,cX,col;
	int i;
	AnsiString s;
	TObject *object; //,*obTva;//,*obSys;
	int LesCol[5]= {6,7,9,11,13};
	LabelModifie->Visible=true;
	OrdreModif=true;
	row=LaGrille->Row;
	cX=LaGrille->ColCount;
	if(row<=1) return;

	SwapObjet(LaGrille,0,row,row-1);
	/*
	 object=LaGrille->Objects[0][row];
	 LaGrille->Objects[0][row]=LaGrille->Objects[0][row-1];
	 LaGrille->Objects[0][row-1]=object;
	 */

	SwapObjet(LaGrille,ColTva,row,row-1);
	/*
	 obTva=LaGrille->Objects[ColTva][row];
	 LaGrille->Objects[ColTva][row]=LaGrille->Objects[ColTva][row-1];
	 LaGrille->Objects[ColTva][row-1]=obTva;
	 */

	//obSys=LaGrille->Objects[ColSys][row];
	//LaGrille->Objects[ColSys][row]=LaGrille->Objects[ColSys][row-1];
	//LaGrille->Objects[ColSys][row-1]=obSys;
	for(c=0;c<cX;c++)
	{
		SwapAs(LaGrille,c,row,row-1);
		/*
		 s=LaGrille->Cells[c][row];
		 LaGrille->Cells[c][row]=LaGrille->Cells[c][row-1];
		 LaGrille->Cells[c][row-1]=s;
		 */
	}

	LaGrille->Cells[0][row-1] =row-1;
	LaGrille->Cells[0][row] =row;

	r0=row;
	r1=row-1;
	for(r=1;r<LaGrille->RowCount;r++)
	{
		object=LaGrille->Objects[0][r];
		if(object==NULL) continue;
		for(i=0;i<5;i++)
		{
			col=LesCol[i];
//            k=GrilleInt(col,r);
			if (GrilleInt(col,r)==r0)
			LaGrille->Cells[col][r]=Aff(r1);
			else if(GrilleInt(col,r)==r1)
			LaGrille->Cells[col][r]=Aff(r0);
		}
	}
	MarquerLigne(row-1);

}
//---------------------------------------------------------------------------
void __fastcall TDefBestiauxFrm::BtClBasClick(TObject *Sender)
{
	int row,r,r0,r1;
	int c,cX,col;
	int i;
	AnsiString s;
	TObject *object; //,*obTva;//,*obSys;
	int LesCol[5]= {6,7,9,11,13};

	LabelModifie->Visible=true;
	OrdreModif=true;
	row=LaGrille->Row;
	cX=LaGrille->ColCount;

	object=LaGrille->Objects[0][row+1];
	if(object==NULL) return;

	SwapObjet(LaGrille,0,row,row+1);
	/*
	 object=LaGrille->Objects[0][row];
	 LaGrille->Objects[0][row]=LaGrille->Objects[0][row+1];
	 LaGrille->Objects[0][row+1]=object;
	 */
	SwapObjet(LaGrille,ColTva,row,row+1);
	/*
	 obTva=LaGrille->Objects[ColTva][row];
	 LaGrille->Objects[ColTva][row]=LaGrille->Objects[ColTva][row+1];
	 LaGrille->Objects[ColTva][row+1]=obTva;
	 */
	//obSys=LaGrille->Objects[ColSys][row];
	//LaGrille->Objects[ColSys][row]=LaGrille->Objects[ColSys][row+1];
	//LaGrille->Objects[ColSys][row+1]=obSys;
	for(c=0;c<cX;c++)
	{
		SwapAs(LaGrille,c,row,row+1);
		/*
		 s=LaGrille->Cells[c][row];
		 LaGrille->Cells[c][row]=LaGrille->Cells[c][row+1];
		 LaGrille->Cells[c][row+1]=s;
		 */
	}
	LaGrille->Cells[0][row] =row;
	LaGrille->Cells[0][row+1]=row+1;

	r0=row;
	r1=row+1;
	for(r=1;r<LaGrille->RowCount;r++)
	{
		object=LaGrille->Objects[0][r];
		if(object==NULL) continue;
		for(i=0;i<5;i++)
		{
			col=LesCol[i];
//            k=GrilleInt(col,r);
			if (GrilleInt(col,r)==r0)
			LaGrille->Cells[col][r]=Aff(r1);
			else if(GrilleInt(col,r)==r1)
			LaGrille->Cells[col][r]=Aff(r0);
		}
	}

	MarquerLigne(row+1);
//    PosClasst();

}
//---------------------------------------------------------------------------
void __fastcall TDefBestiauxFrm::BtSupClick(TObject *Sender)
{
//    ShowMessage("DefBestiaux");
	CL_Item* item;
	int rep;
	char buf[100];
	int r=LaGrille->Row;
	int i,rSup,k,col;
	int LesCol[5]= {6,7,9,11,13};
	TObject *object; //,*obTva;//,*obSys;

	item=(CL_Item*)LaGrille->Objects[0][r];
	if(item==NULL) return;
	SelLigne();
	if(item->Supprimable==false)
	{
		ShowMessage(L_Utilise);
		//ShowMessage(" UTILISE ");
		DeSelLigne();
		return;
	}
	sprintf(buf,L_AttSupp.c_str(),item->Nom.c_str() );
	//sprintf(buf," Je supprime %s \n Attention à la numérotation \n Vous êtes sur ?",item->Nom.c_str() );
	rep=MessageBox(Handle,buf,T->L_SupT.c_str(),MB_YESNO);
	//rep=MessageBox(Handle,buf,"SUPPRESSION",MB_YESNO);
	if(rep==IDYES)
	{
		item->Flag='S';
		SupprimerLigne();
		LabelModifie->Visible=true;
	}
	DeSelLigne();

	rSup=r;
	for(r=1;r<LaGrille->RowCount;r++)
	{
		object=LaGrille->Objects[0][r];
		if(object==NULL) continue;
		for(i=0;i<5;i++)
		{
			col=LesCol[i];
			k=GrilleInt(col,r);
			if (k > rSup)
			LaGrille->Cells[col][r]=Aff(k-1);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TDefBestiauxFrm::FormCloseQuery(TObject *Sender,
		bool &CanClose)
{
	int rep; //050105
//    if(LBSysUnitFrm->Visible==true)LBSysUnitFrm->Close();
	if(LBTvaFrm->Visible==true)LBTvaFrm->Close();
	DerniereCell();
	if(LabelModifie->Visible==false)return;

	if(VerifGrille(LaGrille)==false)
	{
		CanClose=false;
		if(ErreurAAfficher==true)
		{
			ErreurFrm->Show();
			CanClose=false;
		}
		return;
	}
	rep=MessageBox(Handle,T->L_DonModifQ.c_str(),T->L_Modif.c_str(),
			//rep=MessageBox(Handle,"Données Modifiées\nVoulez vous conserver","MODIFICATION",
			MB_YESNOCANCEL|MB_ICONEXCLAMATION);
	if(rep==ID_YES)
	{
		DeGrille(LaGrille);
		if(OrdreModif==true) StockerOrdreBestiaux(V_Bestiaux); //250805

		ES->ecrireFichier();
		LabelModifie->Visible=false;
	}
	else
	{
		VideGrille(LaGrille);
		VersGrille(LaGrille);
	}

}
//250805
//---------------------------------------------------------------------------
void __fastcall TDefBestiauxFrm:: StockerOrdreBestiaux(CL_Vecteur<CL_Bestiaux> *vecteur)
{
	int i,j;
	int pos=0;
	CL_Bestiaux *bestiaux,*bestiaux0;
	i=0;
	for(int r=1;r<LaGrille->RowCount;r++)
	{
		if(RowVide(r)==true) continue;
		bestiaux=(CL_Bestiaux*)LaGrille->Objects[0][r];
		for(j=pos;j<vecteur->Nbelt;j++)
		{
			bestiaux0=vecteur->Vecteur[j];
			if(bestiaux0->Categorie!=bestiaux->Categorie)continue;

			vecteur->Vecteur[j]=(CL_Bestiaux*)LaGrille->Objects[0][r];
			pos=j+1;
			break;
		}
		i++;
	}
	OrdreModif=false;
}

//---------------------------------------------------------------------------
void __fastcall TDefBestiauxFrm::DeGrille(TStringGrid *grille)
{
	int row;
	AnsiString value;
	CL_Bestiaux *bestiaux;
	for(row=1;row<grille->RowCount;row++)
	{
//		if(RowVide(row)==true) continue;      050105
		bestiaux=(CL_Bestiaux*)grille->Objects[0][row];
		if(bestiaux==NULL) continue;
		switch(bestiaux->Flag)
		{
			case 'O':
			case 'M': //modifié
			bestiaux->Nom=grille->Cells[2][row];
			break;
			case 'N'://nouveau
			bestiaux->Nom =grille->Cells[2][row];
			bestiaux->Categorie=Categorie;
			bestiaux->NoCategorie=Categorie->No;
			V_Bestiaux->ins(bestiaux);
			break;
		}
		LireBestiaux(bestiaux,row);
	}
	for(int i=0;i<V_Bestiaux->Nbelt;i++)
	{
		bestiaux=V_Bestiaux->Vecteur[i];
		if(bestiaux->Flag=='S') {V_Bestiaux->sup(bestiaux);i--;}
	}
}
//---------------------------------------------------------------------------
void TDefBestiauxFrm::TexteChaine(void) {
	L_MvtTroupeau = T->TrouveTexte("DefBestiauxFrm", "L_MvtTroupeau");
	L_Titre = T->TrouveTexte("DefBestiauxFrm", "L_Titre");
	L_PasValInv = T->TrouveTexte("DefBestiauxFrm", "L_PasValInv");
	L_PasPrix = T->TrouveTexte("DefBestiauxFrm", "L_PasPrix");
	L_PasOrigine = T->TrouveTexte("DefBestiauxFrm", "L_PasOrigine");
	L_OretDest = T->TrouveTexte("DefBestiauxFrm", "L_OretDest");
	L_MemeOrig = T->TrouveTexte("DefBestiauxFrm", "L_MemeOrig");
	L_AttSupp = T->TrouveTexte("DefBestiauxFrm", "L_AttSupp");
}
//--------------------------------------------
void TDefBestiauxFrm::IniCaption(void) {
	DefBestiauxFrm->Caption = T->LC_DefBestiauxFrm;

	BtClasser->Caption = T->LC_BtClasser; //090206
	BtBnTva->Caption = T->LC_BtBnTva;
	ChBRepTout->Caption = T->LC_ChBRepTout;

}
//--------------------------------------------
void TDefBestiauxFrm::TexteCaption(void) {
	LC_DefBestiauxFrm = T->TrouveCaption("CL_Trad", "LC_DefBestiauxFrm");

	IniCaption();
}

//-------------------------------------------------------------------------------
void __fastcall TDefBestiauxFrm::BtBnNoteClick(TObject *Sender)
{
//
//020507
	NoteAgriFrm->VientDe="DefBestiaux";//ne pas traduire
	NoteAgriFrm->Categorie=Categorie;
	NoteAgriFrm->Caption=Categorie->Nom;
	NoteAgriFrm->Memo->Text=Categorie->Notes;

	NoteAgriFrm->Show();

}
//---------------------------------------------------------------------------

bool __fastcall TDefBestiauxFrm::FormHelp(WORD Command, int Data,
		bool &CallHelp)
{
	CallHelp=false;
	HelpContext=410;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);
	return true;

}
//---------------------------------------------------------------------------

void __fastcall TDefBestiauxFrm::BtBnAideClick(TObject *Sender)
{
	HelpContext=410;
	AideFrm->AfficherAide(AideFrm->Langue,HelpContext);

}
//---------------------------------------------------------------------------

