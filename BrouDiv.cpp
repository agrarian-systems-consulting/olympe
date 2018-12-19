//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <stdio.h>
#include <vcl\printers.hpp>
#pragma hdrstop

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "Brouillon.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
//----------------------------------------------------------------------------
void TFBrouillon::ImprimerLesDonnees(void) {
	Demarre();

	Titre1("LES SYSTEMES D'UNITES");
//	SysUniteFrm->ImpSysUnite();
	/*
	 FBrouillon->Titre1("LES CATEGORIES");
	 CategoriesFrm->ImpCategorie("PRODUITS",  V_CatProduit);
	 CategoriesFrm->ImpCategorie("CHARGES",   V_CatCharge);
	 CategoriesFrm->ImpCategorie("IRRIGATION",V_CatEau);

	 FBrouillon->Titre1("LES PRODUITS");
	 ProduitFrm->ImpProduit("LES PRODUITS",V_Produit);

	 FBrouillon->Titre1("LES CHARGES OPERATIONNELLES");
	 ChargeFrm->ImpProduit("LES CHARGES",V_Charge);

	 FBrouillon->Titre1("IRRIGATION");
	 EauFrm->ImpProduit("IRRIGATION",V_Irrigation);

	 FBrouillon->Titre1("AUTRES RECETTES ET DEPENSES");
	 //    RecDepAutreFrm->ImpRecDepAutre("RECETTES",V_RecDiv);
	 //    RecDepAutreFrm->ImpRecDepAutre("DEPENSES",V_DepDiv);

	 FBrouillon->Titre1("LES CHARGES DE STRUCTURE");
	 //    StructureFrm->ImpRecDepAutre("CHARGES",V_ChStruct);


	 FBrouillon->Titre1("FAMILLE");
	 //    FamilleFrm->ImpRecDepAutre("RECETTES",  V_RecFam);
	 //    FamilleFrm->ImpRecDepAutre("DEPENSES",  V_DepFam);

	 FBrouillon->Titre1("TYPOLOGIE");
	 //    TypeFrm->ImpRecDepAutre("TYPES",  V_Type);
	 //    TypeFrm->ImpRecDepAutre("ZONES",  V_Zone);
	 */
	FBrouillon->Show();
}
////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------
/// Systemes d'Unité
//--------------------------------------------------------------------------
void TFBrouillon::SysUnite(CL_SystemeUnite *sysUnit, TColor couleur) {
//size2=10
	TypeImp("Courier", size2, couleur, 'M');
	/*
	 Memo1->SelAttributes->Name= "Courier";
	 Memo1->SelAttributes->Size=size2;// 10;
	 Memo1->SelAttributes->Color= couleur;
	 */
	videAsLambda();

	placer(sysUnit->UUt, 5);
	placer(sysUnit->UTrans, 15);
	placer(sysUnit->UGlobal, 25);
	placer(sysUnit->Ratio, 40, 0);
	placer(sysUnit->RatioG, 50, 0);

	Memo1->Lines->Add(AsLambda.TrimRight());
}
//-------------------------------------------------------------------------
void TFBrouillon::EnTeteSysUnite(TColor couleur) {
	FBrouillon->BtBnExcel->Visible = false;
	TypeImp("Courier", size2, couleur, 'M');
	Blanc();
	videAsLambda();

	placer("Atelier", 5);
	placer("Expl.", 15);
	placer("Région", 25);
	placer("2/1", 38);
	placer("3/2", 47);
	Memo1->Lines->Add(AsLambda.TrimRight());

	videAsLambda();
	placer("1", 5);
	placer("2", 15);
	placer("3", 25);
	Memo1->Lines->Add(AsLambda.TrimRight());
	Blanc();
//    Memo1->SelAttributes->Style=TFontStyles()>>fsBold;
}
//--------------------------------------------------------------------------
/// TVA
//--------------------------------------------------------------------------
void TFBrouillon::Tva(CL_Tva *tva, TColor couleur) {
//size2=10
	TypeImp("Courier", size2, couleur, 'M');
	/*
	 Memo1->SelAttributes->Name= "Courier";
	 Memo1->SelAttributes->Size= size2;//10;
	 Memo1->SelAttributes->Color= couleur;
	 */
	videAsLambda();

	placer(tva->Nom, 10);
	placer(tva->Taux, 30, 2);
	Memo1->Lines->Add(AsLambda.TrimRight());

}
//-------------------------------------------------------------------------
void TFBrouillon::EnTeteTva(TColor couleur) {
	FBrouillon->BtBnExcel->Visible = false;
	TypeImp("Courier", size2, couleur, 'G');
	Blanc();
	videAsLambda();

	placer("Nom", 10);
	placer("Taux", 25);
	Memo1->Lines->Add(AsLambda.TrimRight());
	Blanc();
	Memo1->SelAttributes->Style = TFontStyles() >> fsBold;
}
//--------------------------------------------------------------------------
/// Produits ou Charges
//--------------------------------------------------------------------------
void TFBrouillon::ItemProCha(CL_Item *item, TColor couleur) {
	TypeImp("Courier", size2, couleur, 'M');

	videAsLambda();

	placer(item->Nom, 10);
	placer(item->Categorie->Nom, 30);
	placer(item->SysUnite->UUt, 50);
	placer(item->SysUnite->UTrans, 55);
	placer(item->SysUnite->UGlobal, 60);
	placer(item->Prix, 80, 2);
	placer(SysMonnaie->UTrans, 85);
	placer("/", 85 + SysMonnaie->UTrans.Length());
	placer(item->SysUnite->UTrans, 86 + SysMonnaie->UTrans.Length());

	Memo1->Lines->Add(AsLambda.TrimRight());
}
//-------------------------------------------------------------------------
void TFBrouillon::EnTeteProCharge(TColor couleur) {
	FBrouillon->BtBnExcel->Visible = false;
	TypeImp("Courier", size2, couleur, 'M');
	videAsLambda();

	placer("Nom", 10);
	placer("Catégorie", 30);
	placer("Unités", 55);
	placer("Prix", 75);

	Memo1->Lines->Add(AsLambda.TrimRight());

	videAsLambda();

	placer("Atelier", 47);
	placer("Expl.", 55);
	placer("Région", 60);

	Memo1->Lines->Add(AsLambda.TrimRight());
}
//--------------------------------------------------------------------------
//tva ????
//--------------------------------------------------------------------------
void TFBrouillon::ItemNomTva(CL_Item *item, TColor couleur) {
	TypeImp("Courier", size2, couleur, 'M');

	videAsLambda();

	placer(item->Nom, 10);
	placer(item->Categorie->Nom, 50);
	placer(item->Tva->Nom, 90);

	Memo1->Lines->Add(AsLambda.TrimRight());
}
//-------------------------------------------------------------------------
void TFBrouillon::EnTeteNomTva(TColor couleur) {
	FBrouillon->BtBnExcel->Visible = false;
	TypeImp("Courier", size2, couleur, 'M');
	videAsLambda();

	placer("Nom", 10);
	placer("Catégorie", 50);
	placer("Tva", 90);

	Memo1->Lines->Add(AsLambda.TrimRight());

}
//--------------------------------------------------------------------------
void TFBrouillon::ItemNomUnite(CL_Item *item, TColor couleur) {
	TypeImp("Courier", size2, couleur, 'M');
	videAsLambda();

	placer(item->Nom, 10);
	placer(item->Categorie->Nom, 50);
	placer(item->SysUnite->UTrans, 90);

	Memo1->Lines->Add(AsLambda.TrimRight());
}
//-------------------------------------------------------------------------
void TFBrouillon::EnTeteNomUnite(TColor couleur) {
	FBrouillon->BtBnExcel->Visible = false;
	TypeImp("Courier", size2, couleur, 'M');
	videAsLambda();

	placer("Nom", 10);
	placer("Catégorie", 50);
	placer("Unité", 90);

	Memo1->Lines->Add(AsLambda.TrimRight());

}
//--------------------------------------------------------------------------
void TFBrouillon::ItemNom(CL_Item *item, TColor couleur) {
	TypeImp("Courier", size2, couleur, 'M');
	videAsLambda();

	placer(item->Nom, 10);
	placer(item->Categorie->Nom, 50);

	Memo1->Lines->Add(AsLambda.TrimRight());
}
//-------------------------------------------------------------------------
void TFBrouillon::EnTeteNom(TColor couleur) {
	FBrouillon->BtBnExcel->Visible = false;
	TypeImp("Courier", size2, couleur, 'M');
	videAsLambda();

	placer("Nom", 10);
	placer("Catégorie", 50);

	Memo1->Lines->Add(AsLambda.TrimRight());

}
//--------------------------------------------------------------------------
void TFBrouillon::Espece(CL_Espece *espece, TColor couleur) {
	int n;
	int delta = 5;
	int pos;
	TypeImp("Courier", size2, couleur, 'M');
	videAsLambda();

	placer(espece->Nom, 5);
	placer(espece->DebAmor, 20);
	placer(espece->NbPhase, 25);
	pos = 40;
	for (n = 0; n < espece->NbPhase; n++) {
		placer(espece->Phase[n], pos);
		pos += delta;
	}
	Memo1->Lines->Add(AsLambda.TrimRight());
}
//-------------------------------------------------------------------------
void TFBrouillon::EnTeteEspece(TColor couleur) {
	int n;
	int pos;
	int delta = 5;

	FBrouillon->BtBnExcel->Visible = false;
	TypeImp("Courier", size2, couleur, 'M');
	Blanc();
	videAsLambda();

	placer("Nom", 5);
	placer("Deb Amor.", 15);
	placer("NbAnnees", 25);
	pos = 40;
	for (n = 0; n < 12; n++) {
		placer(n, pos);
		pos += delta;
	}
	Memo1->Lines->Add(AsLambda.TrimRight());

	videAsLambda();
	Blanc();
}
//--------------------------------------------------------------------------

//....
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
void TFBrouillon::ItemNomAnimaux(CL_Item *item, TColor couleur) {
	TypeImp("Courier", size2, couleur, 'M');
	videAsLambda();

	placer(item->Nom, 10);
	placer(item->Categorie->Nom, 30);
	placer(item->Prix, 50, 2);

	Memo1->Lines->Add(AsLambda.TrimRight());
}

//-------------------------------------------------------------------------
void TFBrouillon::EnTeteNomAnimaux(TColor couleur) {
	FBrouillon->BtBnExcel->Visible = false;
	TypeImp("Courier", size2, couleur, 'M');
	videAsLambda();

	placer("Nom", 10);
	placer("Catégorie", 30);
	placer("Unités", 55);
	placer("Prix", 75);

	Memo1->Lines->Add(AsLambda.TrimRight());

	videAsLambda();

	placer("Atelier", 47);
	placer("Expl.", 55);
	placer("Région", 60);

	Memo1->Lines->Add(AsLambda.TrimRight());
}

