//---------------------------------------------------------------------------

#pragma hdrstop
#include "Main.h"
#include "SysUnite.h"
#include "Forme0.h"
#include "Forme00.h"
#include "DefProduit.h"
#include "DefBestiaux.h"
#include "DefCalendrier.h"
#include "DefChStruct.h"
#include "DefEtatSortie.h"
#include "DefItem.h"
#include "DefProcedure.h"
#include "DefVariable.h"
#include "DefZone.h"
#include "AgriDefSim.h"
#include "AgriSaisie.h"
#include "AleaPrix.h"
#include "Assol.h"
#include "Atelier.h"
#include "AtelierMarge.h"
#include "AtelierMDetail.h"
#include "Commercialisation.h"
#include "SysUnite.h"
#include "Effacer.h"
#include "Ensemble.h"
#include "Espece.h"
#include "GereAgri.h"
#include "GereAleaPrix.h"
#include "GereAleaRdt.h"
#include "QRSortieQuant.h"
#include "QRSortieVal.h"
#include "FichierLire.h"

#include "AgriAtelierMarge.h"
#include "AtelierMDetailPerenne.h"
#include "ActionRemplacer.h"
#include "AgriClasst.h"
#include "AleaRdt.h"
#include "AideEmpLT.h"
#include "APropos.h"
#include "ChoixMotif.h"
#include "Conversion.h"
#include "CopierDans.h"
#include "EntreChaine.h"
#include "Erreur.h"
#include "ErreurFinSommaire.h"
#include "ErreurImmoSommaire.h"
#include "FenRepart.h"
#include "FenRepartDef.h"
#include "Forme01.h"
#include "GereAtelier.h"
#include "GereCalendrier.h"
#include "GereCatBestiaux.h"
#include "GereCatChStruct.h"
#include "GereCatItem.h"
#include "GereCatProduit.h"
#include "GereCatVariable.h"
#include "GereEnsemble.h"
#include "GereEspece.h"
#include "GereEtat.h"
#include "GereIndic.h"
#include "GereProcedure.h"
#include "GereComparaison.h"
#include "GereCatZone.h"

#include "Indicateur.h"

#include "LBChoix.h"
#include "LBChoixAction.h"
#include "LBChoixBestiaux.h"
#include "LBChoixMC.h"
#include "LBChoixMCInd.h"
#include "LBCompAgri.h"
#include "LBProduit.h"
#include "LBToutAgri.h"
#include "LBToutEnsemble.h"
#include "LBTva.h"
#include "LBChoixMC.h"

//#include "LBChoixMCAction.h"  pas opérationnel
#include "LBConversion.h"
#include "LBMarge.h"
#include "LBSelection.h"
#include "LBSelectionAgri.h"
#include "LBSysUnit.h"
#include "LBTChoix.h"
#include "LBTypeZone.h"
#include "LesDefSim.h"
#include "LesStocks.h"
#include "Motif.h"
#include "Motif2.h"
#include "MvtAnnee.h"
#include "NoteAgri.h"
#include "NoteEnsemble.h"
#include "NouvAgri.h"
#include "QRAtelier.h"
#include "QRCatNom.h"
#include "QRCatNomUnite.h"
#include "QRCatNomTva.h"
#include "QRCatTout.h"
#include "QRGrille00.h"
#include "QRMemo.h"
#include "QRTresoQuant.h"
#include "QRTresoVal.h"
#include "QuelExcelCSV.h"
#include "ResGraph.h"
#include "Resultat.h"
#include "SituDepart.h"
#include "SortieEcran.h"
#include "Tarif.h"
#include "TravCal.h"
#include "TravGraph.h"
#include "Treso.h"
#include "TresoDefOccc.h"
#include "TresoGraph.h"
#include "TresoQouV.h"
#include "TresoRepart.h"
#include "TresoCopieRepart.h"
#include "TresoRes.h"
#include "TriAgri.h"
#include "Tva.h"
#include "TVChoix.h"
#include "TVChoixComp.h"
#include "TVChoixEtat.h"
#include "TVChoixItem.h"
#include "TVChoixMarge.h"
#include "TVDonProcedure.h"
#include "TVPrixChoix.h"
#include "TVRdtChoix.h"
#include "TVVarianteAgri.h"
#include "TVvarianteEns.h"
#include "TVDico.h"
#include "APropos.h"
#include "Outil.h";

#include "TypeAmor.h"
#include "TypeEmpCT.h"
#include "TypeEmpLT.h"
#include "TypePlact.h"
#include "ErreurImmoSommaire.h"
#include "ErreurFinSommaire.h"
#include "EcrireAccess.h"

#include "CL_Trad.h"

extern CL_Trad *T;

extern CL_ES *ES;
//---------------------------------------------------------------------------

#pragma package(smart_init)
//--------------Modifier le 19/08/2010 par Rebaubier William ----------------
//---------------------------------------------------------------------------
/*
 creer SLNomProg     TStringLst triée sur nom des programmes
 contenant nom des programmes
 et objet SLNomVar
 SLNomVar TStringLst triée sur nom des variables
 contenant nom des variables
 et objet ptrTexte
 pointeur sur le texte de la langue

 */
//---------------------------------------------------------------------------
bool CL_Trad::LireTraduction(AnsiString asNature, char langue) {
	int i, n, nSL;
	int noTexte;
	char chaine[1000]; //270706
	char *fin;
	char nomProg[100];
	char nomVar[100];
	char texte[100];
	char *ptrNomProg;
	char *ptrNomVar;
	char *ptrTexte;
	AnsiString asProg, asProg0, as;
	FILE *FichierLire;
	int noLangue;
	int toto;
//static AnsiString asCurDir="debut";
	// pour signaler erreurs eventuelles  sera fermé par Main::FormActivate
	//Erreur=false; avant premier appel dans main 170203

	switch (langue) {
	case 'F':
		noLangue = 1;
		break;
	case 'E':
		noLangue = 2;
		break;
	case 'S':
		noLangue = 3;
		break;
	case 'N':
		noLangue = 4;
		break;
	case 'P':
		noLangue = 5;
		break;
	case 'X':
		noLangue = 6;
		break;
	default:
		noLangue = 1;
	}
	SLNomProg = new TStringList;
	SLNomProg->Sorted = true;

	asProg0 = AnsiString("aaa");
	//les noms des programmes eg: AgriAtelierMarge sont stockés
	// dans la StringList  SLNomProg
	// cette SL contient un objet une StringList SLNomVar qui contient les textes
	// quand je lis un nouveau programme je crée une nouvelle SL associée au programme
	// au début j'initialise le nom du programme asProg0 à un nom que je ne rencontrerai pas
	//  aaa
	// au premier nom de programme rencontré je crée la SLNomVar pour ce programme
//........
	/*
	 if(asCurDir=="debut")
	 {
	 asCurDir=GetCurrentDir();
	 }
	 */
	if (asNature == "Texte") {
		as = MainForm->AsDirOlympe + AnsiString("\\OlympeTxt.csv");
		FichierLire = fopen(as.c_str(), "r");
		//FichierLire =   fopen("OlympeTxt.csv", "r");
		FichierErreur = fopen("OlympeTxtErreur.txt", "w");
		if (FichierLire == NULL) {
			ShowMessage(" Pas De Fichier OlympeTxt.csv");
			return false;
		}
	} else if (asNature == "Caption") {
		as = MainForm->AsDirOlympe + AnsiString("\\OlympeCaption.csv");
		FichierLire = fopen(as.c_str(), "r");
		//FichierLire =   fopen("OlympeCaption.csv", "r");
		if (FichierLire == NULL) {
			ShowMessage(" Pas De Fichier OlympeCaption.csv");
			return false;
		}
	}
	while (1) {
		fin = fgets(chaine, sizeof(chaine), FichierLire);
		if (fin == NULL)
			break;

		//ligne vide ou ligne commence par / est ignorée
		if (chaine[0] == '\n' || chaine[0] == '/')
			continue;

		//nomProg
		n = 0;
		i = 0;
		while (chaine[n] != ';')
			nomProg[i++] = chaine[n++];
		nomProg[i] = 0;

		asProg = AnsiString(nomProg);
		if (asProg == "ErreurImmoSommaireFrm")
			toto = 1;
		if (asProg != asProg0) {
			asProg0 = asProg;
			nSL = TrouveDansSLNomProg(asProg);
			if (nSL == -1) {
				SLNomVar = new TStringList;
				SLNomVar->Sorted = true;
				ptrNomProg = new char[strlen(nomProg) + 1];
				strcpy(ptrNomProg, nomProg);
				SLNomProg->AddObject(ptrNomProg, (TObject*) SLNomVar);
			} else {
				//as=SLNomProg->Strings[nSL];
				SLNomVar = (TStringList*) SLNomProg->Objects[nSL];
			}
//            continue;//270706
		}

		//nomVar
		n++;
		i = 0;
		while (chaine[n] != ';')
			nomVar[i++] = chaine[n++];
		nomVar[i] = 0;
		ptrNomVar = new char[strlen(nomVar) + 1];
		strcpy(ptrNomVar, nomVar);

		//Texte  trouver le texte de la langue
		noTexte = 1;
		while (1) {
			n++;
			i = 0;
			while (chaine[n] != ';' && chaine[n] != '\n')
				texte[i++] = chaine[n++];
			texte[i] = 0;

			if (noTexte == noLangue)
				break;
			noTexte++;
			// attention si pas trouvé
			if (noTexte > noLangue) {
				Erreur = true;
				fprintf(FichierErreur, "Manque traduction %s  %s", nomProg,
						nomVar);
				strcpy(texte, "inconnu");
				break;
			}
		}

		ptrTexte = new char[strlen(texte) + 1];
		strcpy(ptrTexte, texte);

		SLNomVar->AddObject(ptrNomVar, (TObject*) ptrTexte);
		i = SLNomVar->Count; //pour test
	}
	fclose(FichierLire);
	return true;
}
//---------------------------------------------------------------------------
int CL_Trad::TrouveDansSLNomProg(AnsiString asProg) {
	int i;
//AnsiString as;
	for (i = 0; i < SLNomProg->Count; i++) {
		//as=SLNomProg->Strings[i];
		if (asProg == SLNomProg->Strings[i]) {
			//as=SLNomProg->Strings[i];
			return i;
		}
	}
	return -1;
}
//---------------------------------------------------------------------------
AnsiString CL_Trad::TrouveTexte(AnsiString nomProg, AnsiString nomVar) {
	int i, j;
	AnsiString as;
	char *chaine;

	i = SLNomProg->IndexOf(nomProg);
	if (i == -1) {
		Erreur = true;
		fprintf(FichierErreur, "NomProg inconnu: %s \n", nomProg);
		return "INCONNU";
	}
	SLNomVar = (TStringList*) SLNomProg->Objects[i];

	j = SLNomVar->IndexOf(nomVar);
	if (j == -1) {
		Erreur = true;
		fprintf(FichierErreur, "NomVar inconnu %s  %s\n", nomProg, nomVar);
		return AnsiString("INCONNU");
	}
	chaine = (char*) SLNomVar->Objects[j];
	return AnsiString(chaine);
}
//---------------------------------------------------------------------------
AnsiString CL_Trad::TrouveCaption(AnsiString nomProg, AnsiString nomVar) {
	int i, j;
	AnsiString as;
	char *chaine;

	i = SLNomProg->IndexOf(nomProg);
	if (i == -1) {
		Erreur = true;
		fprintf(FichierErreur, "NomProg inconnu %s \n", nomProg);
		return "INCONNU";
	}
	SLNomVar = (TStringList*) SLNomProg->Objects[i];

	j = SLNomVar->IndexOf(nomVar);
	if (j == -1) {
		Erreur = true;
		fprintf(FichierErreur, "NomVar inconnu %s  %s\n", nomProg, nomVar);
		return AnsiString("INCONNU");
	}
	chaine = (char*) SLNomVar->Objects[j];
	return AnsiString(chaine);
//    return TrouveTexte(nomProg,nomVar);
}
//utilisé dans FichierUtil
//---------------------------------------------------------------------------
char* CL_Trad::TrouveChaine(AnsiString nomProg, AnsiString nomVar) {
	int i, j;
	AnsiString as;
	char *chaine;
	char *ptrTexte;
	i = SLNomProg->IndexOf(nomProg);
	if (i == -1) {
		Erreur = true;
		fprintf(FichierErreur, "NomProg inconnu %s \n", nomProg);
		return "INCONNU";
	}
	SLNomVar = (TStringList*) SLNomProg->Objects[i];

	j = SLNomVar->IndexOf(nomVar);
	if (j == -1) {
		Erreur = true;
		fprintf(FichierErreur, "NomVar inconnu %s  %s\n", nomProg, nomVar);
		return "INCONNU";
	}
	chaine = (char*) SLNomVar->Objects[j];
	ptrTexte = new char[strlen(chaine) + 1];
	strcpy(ptrTexte, chaine);
	return ptrTexte;
}

//---------------------------------------------------------------------------
void CL_Trad::CreeTxtDialogue(void) {
	TexteChaine();
	MainForm->TexteChaine();
	ES->TexteChaine();
	LBChoixMCFrm->TraduireMotCle();

	SysUniteFrm->TexteChaine();
	Forme0Frm->TexteChaine();
	Forme01Frm->TexteChaine();
	Forme00Frm->TexteChaine();
	DefProduitFrm->TexteChaine();
	DefBestiauxFrm->TexteChaine();
	DefCalendrierFrm->TexteChaine();
	DefChStructFrm->TexteChaine();
	DefEtatSortieFrm->TexteChaine();
	DefItemFrm->TexteChaine();
	DefProcedureFrm->TexteChaine();
	DefVariableFrm->TexteChaine();
	DefZoneFrm->TexteChaine();

	AgriDefSimFrm->TexteChaine();
	AgriSaisieFrm->TexteChaine();
	AgriAtelierMargeFrm->TexteChaine();

	AleaPrixFrm->TexteChaine();
	AleaRdtFrm->TexteChaine();

	AssolFrm->TexteChaine();
	AtelierFrm->TexteChaine();
	AtelierMargeFrm->TexteChaine();
	AtelierMDetailFrm->TexteChaine();
	AtelierMDetailPerenneFrm->TexteChaine();

	CommercialisationFrm->TexteChaine();
	EcrireAccessFrm->TexteChaine();
	EffacerFrm->TexteChaine();
	EnsembleFrm->TexteChaine();
	EspeceFrm->TexteChaine();
	//LesTitres  FichierElt

	GereAgriFrm->TexteChaine();
	GereAleaPrixFrm->TexteChaine();
	GereAtelierFrm->TexteChaine();
	GereEtatFrm->TexteChaine();
	GereEnsembleFrm->TexteChaine();

	NouvAgriFrm->TexteChaine();
	OutilFrm->TexteChaine();
	QRSortieQuantFrm->TexteChaine();
	QRSortieValFrm->TexteChaine();

	GereCatItemFrm->TexteChaine();
	TVDicoFrm->TexteChaine();
	TravCalFrm->TexteChaine(); //040306
	TresoFrm->TexteChaine();

	GereCalendrierFrm->TexteChaine();

	LBSelectionAgriFrm->TexteChaine();
	MvtAnneeFrm->TexteChaine();
	TroupeauFrm->TexteChaine();
	ErreurImmoSommaireFrm->TexteChaine();
	ErreurFinSommaireFrm->TexteChaine();
//      TresoCopieRepartFrm->TexteChaine();
}
//---------------------------------------------------------------------------
void CL_Trad::TexteChaine(void) {
	L_Erreur = TrouveTexte("CL_Trad", "L_Erreur");
	L_DonModifQ = TrouveTexte("CL_Trad", "L_DonModifQ");
	L_DonModifT = TrouveTexte("CL_Trad", "L_DonModifT");

	L_Utilise = TrouveTexte("CL_Trad", "L_Utilise");
//    L_Supp=             "SUPPRESSION";

	L_Modif = TrouveTexte("CL_Trad", "L_Modif");

	L_SupQ = TrouveTexte("CL_Trad", "L_SupQ");
	L_SupT = TrouveTexte("CL_Trad", "L_SupT");
	L_SupInutQ = TrouveTexte("CL_Trad", "L_SupInutQ");

	L_SupInutT = TrouveTexte("CL_Trad", "L_SupInutT");

	L_EffaceQ = TrouveTexte("CL_Trad", "L_EffaceQ");
	L_EffaceT = TrouveTexte("CL_Trad", "L_EffaceT");
	L_SupToutQ = TrouveTexte("CL_Trad", "L_SupToutQ");
	L_SupLiQ = TrouveTexte("CL_Trad", "L_SupLiQ");

	L_QuitQ = TrouveTexte("CL_Trad", "L_QuitQ");
	L_QuitT = TrouveTexte("CL_Trad", "L_QuitT");

	L_Charge = TrouveTexte("CL_Trad", "L_Charge");
	L_ChStruct = TrouveTexte("CL_Trad", "L_ChStruct");
	L_DepDiv = TrouveTexte("CL_Trad", "L_DepDiv");
	L_RecDiv = TrouveTexte("CL_Trad", "L_RecDiv");
	L_Culture = TrouveTexte("CL_Trad", "L_Culture");
	L_Animaux = TrouveTexte("CL_Trad", "L_Animaux");
	L_Perenne = TrouveTexte("CL_Trad", "L_Perenne");
	L_Vivrier = TrouveTexte("CL_Trad", "L_Vivrier");
	L_Tendance = TrouveTexte("CL_Trad", "L_Tendance");
	L_Scenario = TrouveTexte("CL_Trad", "L_Scenario");

	//CompAnalex
	L_PasFinComm = TrouveTexte("CL_Trad", "L_PasFinComm");
	L_CarInco = TrouveTexte("CL_Trad", "L_CarInco");
	L_NbLong = TrouveTexte("CL_Trad", "L_NbLong");
	L_PasDeNom = TrouveTexte("CL_Trad", "L_PasDeNom");

	L_ParFerm = TrouveTexte("CL_Trad", "L_ParFerm");
	L_ParOuv = TrouveTexte("CL_Trad", "L_ParOuv");
	L_2Point = TrouveTexte("CL_Trad", "L_2Point");
	L_Inco = TrouveTexte("CL_Trad", "L_Inco");
	L_IdentInco = TrouveTexte("CL_Trad", "L_IdentInco");

	L_Proc_PasDon = TrouveTexte("CL_Trad", "L_Proc_PasDon");
	L_Probleme = TrouveTexte("CL_Trad", "L_Probleme");
	L_Inconnu = TrouveTexte("CL_Trad", "L_Inconnu");

	L_Poste = TrouveTexte("CL_Trad", "L_Poste");
	L_Ceg = TrouveTexte("CL_Trad", "L_Ceg");
	L_Bilan = TrouveTexte("CL_Trad", "L_Bilan");
	L_Immobilisation = TrouveTexte("CL_Trad", "L_Immobilisation");
	L_Subvention = TrouveTexte("CL_Trad", "L_Subvention");
	L_Tva = TrouveTexte("CL_Trad", "L_Tva");
	L_Emprunt = TrouveTexte("CL_Trad", "L_Emprunt");
	L_Emprunt_LT = TrouveTexte("CL_Trad", "L_Emprunt_LT");
	L_Emprunt_CT = TrouveTexte("CL_Trad", "L_Emprunt_CT");
	L_Emprunt_Prive = TrouveTexte("CL_Trad", "L_Emprunt_Prive");
	L_Mvt_Animaux = TrouveTexte("CL_Trad", "L_Mvt_Animaux");

	L_Nom = TrouveTexte("CL_Trad", "L_Nom");
	L_Cat = TrouveTexte("CL_Trad", "L_Cat");
	L_Fam = TrouveTexte("CL_Trad", "L_Fam");
	L_Nat = TrouveTexte("CL_Trad", "L_Nat");

	L_Produit = TrouveTexte("CL_Trad", "L_Produit");
	L_ChfProd = TrouveTexte("CL_Trad", "L_ChfProd");
	L_Exter = TrouveTexte("CL_Trad", "L_Exter");

	L_Effectifs = TrouveTexte("CL_Trad", "L_Effectifs");
	L_Eff_Vendus = TrouveTexte("CL_Trad", "L_Eff_Vendus");
	L_Eff_Achetes = TrouveTexte("CL_Trad", "L_Eff_Achetes");
	L_Val_Ventes = TrouveTexte("CL_Trad", "L_Val_Ventes");
	L_Val_Achats = TrouveTexte("CL_Trad", "L_Val_Achats");
	L_Val_Inv = TrouveTexte("CL_Trad", "L_Val_Inv");

	//DefAction
	L_Act_Action = TrouveTexte("CL_Trad", "L_Act_Action");
	L_Act_DescAction = TrouveTexte("CL_Trad", "L_Act_DescAction");

	L_Act_Reg1 = TrouveTexte("CL_Trad", "L_Act_Reg1");
	L_Act_Remplacer = TrouveTexte("CL_Trad", "L_Act_Remplacer");
	L_Act_Supprimer = TrouveTexte("CL_Trad", "L_Act_Supprimer");
	L_Act_Planter = TrouveTexte("CL_Trad", "L_Act_Planter");
	L_Act_Arracher = TrouveTexte("CL_Trad", "L_Act_Arracher");
	L_Act_Investir = TrouveTexte("CL_Trad", "L_Act_Investir");
	L_Act_Emprunter = TrouveTexte("CL_Trad", "L_Act_Emprunter");

	L_Emp_Lt = TrouveTexte("CL_Trad", "L_Emp_Lt");
	L_Emp_Total = TrouveTexte("CL_Trad", "L_Emp_Total");
	L_Emp_Ct = TrouveTexte("CL_Trad", "L_Emp_Ct");
	L_Emp_Sub = TrouveTexte("CL_Trad", "L_Emp_Sub");
	L_Emp_Plact = TrouveTexte("CL_Trad", "L_Emp_Plact");
	L_Emp_Immo = TrouveTexte("CL_Trad", "L_Emp_Immo");

	L_Avt1 = TrouveTexte("CL_Trad", "L_Avt1");

	L_TotalM = TrouveTexte("CL_Trad", "L_TotalM");
	L_Total = TrouveTexte("CL_Trad", "L_Total");

	L_Agri = TrouveTexte("CL_Trad", "L_Agri");
	L_Atelier = TrouveTexte("CL_Trad", "L_Atelier");
	L_NonDef = TrouveTexte("CL_Trad", "L_NonDef");
	L_Impo = TrouveTexte("CL_Trad", "L_Impo");
	L_Marge = TrouveTexte("CL_Trad", "L_Marge");
	L_MargeHeure = TrouveTexte("CL_Trad", "L_MargeHeure");
	L_PasUnite = TrouveTexte("CL_Trad", "L_PasUnite");
	//100602
	L_CatAElt = TrouveTexte("CL_Trad", "L_CatAElt");

}
//---------------------------------------------------------------------------
void CL_Trad::CreeTxtCaption(void) {
	TexteCaption();
//    ActionRemplacerFrm->TexteCaption();  plante mais pourquoi ??
	AgriAtelierMargeFrm->TexteCaption();
	AgriClasstFrm->TexteCaption();
	AgriDefSimFrm->TexteCaption();
	AgriSaisieFrm->TexteCaption();
//??    AideEmpLTFrm->TexteCaption();
	AleaPrixFrm->TexteCaption();
	AleaRdtFrm->TexteCaption();

	AProposFrm->TexteCaption();
	AtelierFrm->TexteCaption();
	AtelierMDetailFrm->TexteCaption();
	AtelierMDetailPerenneFrm->TexteCaption();
	ChoixMotifFrm->TexteCaption();
//    CL_TradFrm->TexteCaption();
	CommercialisationFrm->TexteCaption();
//    ConfigurationFrm->TexteCaption();
	ConversionFrm->TexteCaption();
	CopierDansFrm->TexteCaption();
	DefActionFrm->TexteCaption();
	DefCalendrierFrm->TexteCaption();
	DefChStructFrm->TexteCaption();
	DefChProduitFrm->TexteCaption();
	DefEtatSortieFrm->TexteCaption();

	DefItemFrm->TexteCaption();
	DefProcedureFrm->TexteCaption();
	DefProduitFrm->TexteCaption();

	EffacerFrm->TexteCaption();
	EnsembleFrm->TexteCaption();
	EntreChaineFrm->TexteCaption();
	ErreurFrm->TexteCaption();
	ErreurFinSommaireFrm->TexteCaption();
	ErreurImmoSommaireFrm->TexteCaption();
	EspeceFrm->TexteCaption();
	FenRepartFrm->TexteCaption();
	FenRepartDefFrm->TexteCaption();
	Forme00Frm->TexteCaption();
	Forme01Frm->TexteCaption();
	GereAgriFrm->TexteCaption();
	GereAleaPrixFrm->TexteCaption();
	GereAleaRdtFrm->TexteCaption();
	GereAtelierFrm->TexteCaption();
	GereCalendrierFrm->TexteCaption();
	GereCatBestiauxFrm->TexteCaption();
	GereCatChStructFrm->TexteCaption();
	GereCatItemFrm->TexteCaption();
	GereCatProduitFrm->TexteCaption();
	GereCatVariableFrm->TexteCaption();
	GereEnsembleFrm->TexteCaption();
	GereEspeceFrm->TexteCaption();
	GereEtatFrm->TexteCaption();
	GereIndicFrm->TexteCaption();
	GereProcedureFrm->TexteCaption();
	GereComparaisonFrm->TexteCaption();
	GereCatZoneFrm->TexteCaption();
	IndicateurFrm->TexteCaption();
	LBChoixFrm->TexteCaption();
	LBChoixActionFrm->TexteCaption();
	LBChoixBestiauxFrm->TexteCaption();
	LBChoixMCFrm->TexteCaption();
	LBChoixMCIndFrm->TexteCaption();
	LBCompAgriFrm->TexteCaption();
	LBProduitFrm->TexteCaption();
	LBToutAgriFrm->TexteCaption();
	LBToutEnsembleFrm->TexteCaption();
	LBTvaFrm->TexteCaption();

//    LBChoixMCActionFrm->TexteCaption();  pas operationnel
	LBConversionFrm->TexteCaption();
	LBMargeFrm->TexteCaption();
	LBSelectionAgriFrm->TexteCaption();
	LBSysUnitFrm->TexteCaption();
	LBTChoixFrm->TexteCaption();
	LBTypeZoneFrm->TexteCaption();
	LesDefSimFrm->TexteCaption();
	LesStocksFrm->TexteCaption();
	MainForm->TexteCaption(); // afaire
	MotifFrm->TexteCaption();
	Motif2Frm->TexteCaption();
	MvtAnneeFrm->TexteCaption();
	NoteAgriFrm->TexteCaption();
	NoteEnsembleFrm->TexteCaption();
	NouvAgriFrm->TexteCaption();
	QRAtelierFrm->TexteCaption();
	QRCatNomFrm->TexteCaption();
	QRCatNomTvaFrm->TexteCaption();
	QRCatNomUniteFrm->TexteCaption();
	QRCatToutFrm->TexteCaption();
	QRGrille00Frm->TexteCaption();
	QRMemoFrm->TexteCaption();
	QRSortieQuantFrm->TexteCaption();
	QRSortieValFrm->TexteCaption();
	QRTresoQuantFrm->TexteCaption();
	QRTresoValFrm->TexteCaption();
	QuelExcelCSVFrm->TexteCaption();
	ResGraphFrm->TexteCaption();
	ResultatFrm->TexteCaption();
	SituDepartFrm->TexteCaption();
	SortieEcranFrm->TexteCaption();
	SysUniteFrm->TexteCaption();
	TarifFrm->TexteCaption();
	TravCalFrm->TexteCaption();
	TravGraphFrm->TexteCaption();
	TresoFrm->TexteCaption();
	TresoDefOcccFrm->TexteCaption();
	TresoGraphFrm->TexteCaption();
	//    TresoQouVFrm->TexteCaption();  //pas utilisé ??
	TresoRepartFrm->TexteCaption();
	TresoResFrm->TexteCaption();
	TriAgriFrm->TexteCaption();
	TroupeauFrm->TexteCaption();
	TvaFrm->TexteCaption();
	TVChoixFrm->TexteCaption();
	TVChoixCompFrm->TexteCaption();
	//TVChoixEtatFrm->TexteCaption(); rien à traduire
	//TVChoixItemFrm->TexteCaption();
	//TVChoixMargeFrm->TexteCaption();
//    TVDonProcedureFrm->TexteCaption();  //en test à introduire
	//TVPrixChoixFrm->TexteCaption();
	//TVRdtChoixFrm->TexteCaption();
	//TVVarianteAgriFrm->TexteCaption();       //a faire   ??
	//TVVarianteEnsFrm->TexteCaption();        // a faire ??
	DefZoneFrm->TexteCaption();
	DefBestiauxFrm->TexteCaption();
	DefVariableFrm->TexteCaption();

	TypeAmorFrm->TexteCaption();
	TypeEmpCTFrm->TexteCaption();
	TypeEmpLTFrm->TexteCaption();
	TypePlactFrm->TexteCaption();

}
//--------------------------------------------------------------------------
void CL_Trad::TexteCaption(void) {
	LC_BtBnAlpha = TrouveTexte("CL_Trad", "LC_BtBnAlpha");
	LC_LabAchat = TrouveTexte("CL_Trad", "LC_LabAchat");
	LC_GBAgri = TrouveTexte("CL_Trad", "LC_GBAgri");
	LC_AleaRdtFrm = TrouveTexte("CL_Trad", "LC_AleaRdtFrm");
	LC_GBAlea = TrouveTexte("CL_Trad", "LC_GBAlea");
	LC_GBAn = TrouveTexte("CL_Trad", "LC_GBAn");
	LC_Assolement = TrouveTexte("CL_Trad", "LC_Assolement");
	LC_AtelierFrm = TrouveTexte("CL_Trad", "LC_AtelierFrm");
	LC_GBAtelier = TrouveTexte("CL_Trad", "LC_GBAtelier");
	LC_BtIndAucun = TrouveTexte("CL_Trad", "LC_BtIndAucun");
	LC_BtAutreAgri = TrouveTexte("CL_Trad", "LC_BtAutreAgri");
	LC_RG = TrouveTexte("CL_Trad", "LC_RG");
	LC_RGCat = TrouveTexte("CL_Trad", "LC_RGCat");
	LC_LabPCharge = TrouveTexte("CL_Trad", "LC_LabPCharge");
	LC_BtClasser = TrouveTexte("CL_Trad", "LC_BtClasser");
	LC_LabZone = TrouveTexte("CL_Trad", "LC_LabZone");
	LC_GBCode = TrouveTexte("CL_Trad", "LC_GBCode");
	LC_Commercialisation1 = TrouveTexte("CL_Trad", "LC_Commercialisation1");
	LC_GereComparaisonFrm = TrouveTexte("CL_Trad", "LC_GereComparaisonFrm");
	LC_GBCondition = TrouveTexte("CL_Trad", "LC_GBCondition");
	LC_BtBnCopier = TrouveTexte("CL_Trad", "LC_BtBnCopier");
	LC_BtBnCopier_A = TrouveTexte("CL_Trad", "LC_BtBnCopier_A");
	LC_BtBnCourbe = TrouveTexte("CL_Trad", "LC_BtBnCourbe");
	LC_BtBnCreer = TrouveTexte("CL_Trad", "LC_BtBnCreer");
	LC_GBDefinition = TrouveTexte("CL_Trad", "LC_GBDefinition");
	LC_ChargesDivers = TrouveTexte("CL_Trad", "LC_ChargesDivers");
	LC_BtDico = TrouveTexte("CL_Trad", "LC_BtDico");
	LC_BtBnDico = TrouveTexte("CL_Trad", "LC_BtBnDico");
	LC_DIVERS1 = TrouveTexte("CL_Trad", "LC_DIVERS1");
	LC_BtDonnees = TrouveTexte("CL_Trad", "LC_BtDonnees");
	LC_Label11 = TrouveTexte("CL_Trad", "LC_Label11");
	LC_RBEcran = TrouveTexte("CL_Trad", "LC_RBEcran");
	LC_BtEffectif = TrouveTexte("CL_Trad", "LC_BtEffectif");
	LC_CreancesDettes1 = TrouveTexte("CL_Trad", "LC_CreancesDettes1");
	LC_BtEnsEnCours = TrouveTexte("CL_Trad", "LC_BtEnsEnCours");
	LC_ChBEnsemble = TrouveTexte("CL_Trad", "LC_ChBEnsemble");
	LC_GBEnsemble = TrouveTexte("CL_Trad", "LC_GBEnsemble");
	LC_ErreurFrm = TrouveTexte("CL_Trad", "LC_ErreurFrm");
	LC_DefEtatSortieFrm = TrouveTexte("CL_Trad", "LC_DefEtatSortieFrm");
	LC_TSExternalite = TrouveTexte("CL_Trad", "LC_TSExternalite");
	LC_BtBnFermer = TrouveTexte("CL_Trad", "LC_BtBnFermer");
	LC_TabSheetG = TrouveTexte("CL_Trad", "LC_TabSheetG");
	LC_Immo = TrouveTexte("CL_Trad", "LC_Immo");
	LC_LabIndicateur = TrouveTexte("CL_Trad", "LC_LabIndicateur");
	LC_GBAtelier_A = TrouveTexte("CL_Trad", "LC_GBAtelier_A");
	LC_IntituleP = TrouveTexte("CL_Trad", "LC_IntituleP");
	LC_LabNom = TrouveTexte("CL_Trad", "LC_LabNom");
	LC_LabSais = TrouveTexte("CL_Trad", "LC_LabSais");
	LC_GereAgriFrm = TrouveTexte("CL_Trad", "LC_GereAgriFrm");
	LC_GereEnsembleFrm = TrouveTexte("CL_Trad", "LC_GereEnsembleFrm");
	LC_LabelModifie = TrouveTexte("CL_Trad", "LC_LabelModifie");
	LC_BtBnMarge = TrouveTexte("CL_Trad", "LC_BtBnMarge");
	LC_BtModifier = TrouveTexte("CL_Trad", "LC_BtModifier");
	LC_RGModifiable = TrouveTexte("CL_Trad", "LC_RGModifiable");
	LC_LabelModifie_A = TrouveTexte("CL_Trad", "LC_LabelModifie_A");
	LC_BtMotCle = TrouveTexte("CL_Trad", "LC_BtMotCle");
	LC_MvtAnneeFrm = TrouveTexte("CL_Trad", "LC_MvtAnneeFrm");
	LC_DefBestiauxFrm = TrouveTexte("CL_Trad", "LC_DefBestiauxFrm");
	LC_RGNatureG = TrouveTexte("CL_Trad", "LC_RGNatureG");
	LC_BtBnEffacer = TrouveTexte("CL_Trad", "LC_BtBnEffacer");
	LC_Nom = TrouveTexte("CL_Trad", "LC_Nom");
	LC_NomAgri = TrouveTexte("CL_Trad", "LC_NomAgri");
	LC_NomAgri_A = TrouveTexte("CL_Trad", "LC_NomAgri_A");
	LC_NomPro = TrouveTexte("CL_Trad", "LC_NomPro");
	LC_NomUnite = TrouveTexte("CL_Trad", "LC_NomUnite");
	LC_BtBnNotes = TrouveTexte("CL_Trad", "LC_BtBnNotes");
	LC_BtNouveau = TrouveTexte("CL_Trad", "LC_BtNouveau");
	LC_Occc = TrouveTexte("CL_Trad", "LC_Occc");
	LC_PanClassif = TrouveTexte("CL_Trad", "LC_PanClassif");
	LC_PetitMatriel = TrouveTexte("CL_Trad", "LC_PetitMatriel");
	LC_EspeceFrm = TrouveTexte("CL_Trad", "LC_EspeceFrm");
	LC_RGPrecision = TrouveTexte("CL_Trad", "LC_RGPrecision");
	LC_GBPrix = TrouveTexte("CL_Trad", "LC_GBPrix");
	LC_LabProcedure = TrouveTexte("CL_Trad", "LC_LabProcedure");
	LC_PRODUCTIONS = TrouveTexte("CL_Trad", "LC_PRODUCTIONS");
	LC_LabPProduit = TrouveTexte("CL_Trad", "LC_LabPProduit");
	LC_BtBnProduit = TrouveTexte("CL_Trad", "LC_BtBnProduit");
//       LC_TLabel =      TrouveTexte("CL_Trad" ,"LC_TLabel");
	LC_GBQuantite = TrouveTexte("CL_Trad", "LC_GBQuantite");
	LC_BtBnQuitter = TrouveTexte("CL_Trad", "LC_BtBnQuitter");
	LC_BtBnRafraichir = TrouveTexte("CL_Trad", "LC_BtBnRafraichir");
	LC_Produits1 = TrouveTexte("CL_Trad", "LC_Produits1");
	LC_Definition = TrouveTexte("CL_Trad", "LC_Definition");
	LC_ChBRepTout = TrouveTexte("CL_Trad", "LC_ChBRepTout");
	LC_RESULTATS = TrouveTexte("CL_Trad", "LC_RESULTATS");
	LC_BtBnResultat = TrouveTexte("CL_Trad", "LC_BtBnResultat");
	LC_GBSortie = TrouveTexte("CL_Trad", "LC_GBSortie");
	LC_S1 = TrouveTexte("CL_Trad", "LC_S1");
	LC_Structure1 = TrouveTexte("CL_Trad", "LC_Structure1");
	LC_BtBnSupBesTrav = TrouveTexte("CL_Trad", "LC_BtBnSupBesTrav");
	LC_BtSyntDetail = TrouveTexte("CL_Trad", "LC_BtSyntDetail");
	LC_LBSysUnitFrm = TrouveTexte("CL_Trad", "LC_LBSysUnitFrm");
	LC_TauxTva = TrouveTexte("CL_Trad", "LC_TauxTva");
	LC_TitreEtat = TrouveTexte("CL_Trad", "LC_TitreEtat");
	LC_LabTotal = TrouveTexte("CL_Trad", "LC_LabTotal");
	LC_LabTotPcent = TrouveTexte("CL_Trad", "LC_LabTotPcent");
	LC_BtIndTous = TrouveTexte("CL_Trad", "LC_BtIndTous");
	LC_TSTravail = TrouveTexte("CL_Trad", "LC_TSTravail");
	LC_Tresorerie = TrouveTexte("CL_Trad", "LC_Tresorerie");
	LC_LBChoixBestiauxFrm = TrouveTexte("CL_Trad", "LC_LBChoixBestiauxFrm");
	LC_BtBnTva = TrouveTexte("CL_Trad", "LC_BtBnTva");
	LC_DefZoneFrm = TrouveTexte("CL_Trad", "LC_DefZoneFrm");
	LC_Unite = TrouveTexte("CL_Trad", "LC_Unite");
	LC_UniteMonnaie = TrouveTexte("CL_Trad", "LC_UniteMonnaie");
	LC_BtBnUnite = TrouveTexte("CL_Trad", "LC_BtBnUnite");
	LC_LabUtilise = TrouveTexte("CL_Trad", "LC_LabUtilise");
	LC_Val0 = TrouveTexte("CL_Trad", "LC_Val0");
	LC_Val1 = TrouveTexte("CL_Trad", "LC_Val1");
	LC_Val10 = TrouveTexte("CL_Trad", "LC_Val10");
	LC_Val11 = TrouveTexte("CL_Trad", "LC_Val11");
	LC_Val2 = TrouveTexte("CL_Trad", "LC_Val2");
	LC_Val3 = TrouveTexte("CL_Trad", "LC_Val3");
	LC_Val4 = TrouveTexte("CL_Trad", "LC_Val4");
	LC_Val5 = TrouveTexte("CL_Trad", "LC_Val5");
	LC_Val6 = TrouveTexte("CL_Trad", "LC_Val6");
	LC_Val7 = TrouveTexte("CL_Trad", "LC_Val7");
	LC_Val8 = TrouveTexte("CL_Trad", "LC_Val8");
	LC_Val9 = TrouveTexte("CL_Trad", "LC_Val9");
	LC_LabVal = TrouveTexte("CL_Trad", "LC_LabVal");
	LC_ValeurEn = TrouveTexte("CL_Trad", "LC_ValeurEn");
	LC_BtBnCalcul = TrouveTexte("CL_Trad", "LC_BtBnCalcul");
	LC_VARIABLES = TrouveTexte("CL_Trad", "LC_VARIABLES");
	LC_BtVariante = TrouveTexte("CL_Trad", "LC_BtVariante");
	LC_BtBnVenteQ = TrouveTexte("CL_Trad", "LC_BtBnVenteQ");
	//100206
	LC_Visible = TrouveTexte("CL_Trad", "LC_Visible");
	LC_NonVisible = TrouveTexte("CL_Trad", "LC_NonVisible");

	LC_EP = TrouveTexte("CL_Trad", "LC_EP");
	LC_Entreprise = TrouveTexte("CL_Trad", "LC_Entreprise");
	LC_Prive = TrouveTexte("CL_Trad", "LC_Prive");

	//010508
	LC_Oui = TrouveTexte("CL_Trad", "LC_Oui");
	LC_Non = TrouveTexte("CL_Trad", "LC_Non");
	LC_Debut = TrouveTexte("CL_Trad", "LC_Debut");
}

