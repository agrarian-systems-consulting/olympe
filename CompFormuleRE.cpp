//---------------------------------------------------------------------------
#include <vcl.h>
#include <values.h>
#pragma hdrstop
#include "Olympe.hse"
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include "Forme0.h"
#include "AgriSaisie.h"
#include "Erreur.h"

#include "Compilateur.h"

//#include "CompCalcul.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
/*
 class CL_Prog
 {
 public:
 CL_Prog();
 CL_Prog(CL_Prog *prog);
 AnsiString Source;
 CL_Arbre  *Arbre;
 CL_Reseau *Reseau;
 };
 Reécrit Source à partir Reseau et Arbre
 des noms ont pu changer
 */
//---------------------------------------------------------------------------
void CL_Compil::ReEcritFormuleRE(CL_Prog *prog, TRichEdit *Re) {
	RE = Re;
	Reseau = prog->Reseau;
	Arbre = prog->Arbre;
	if (Reseau) {
//        ecrireReseau();
		TxtReseau = AnsiString("");
		reEcritReseauRE(0, 0);
		prog->Source = TxtReseau;
	} else if (Arbre) {
		reEcritArbreRE(Arbre->BrancheX - 1);
		prog->Source = TxtArbre;
	}
}
//---------------------------------------------------------------------------
void CL_Compil::reEcritReseauRE(int i, int prec) {
	ST_Maille maille;
	maille = Reseau->LesMailles[i];
	switch (maille.code) {
	case SI:
		switch (prec) {
		case SI:
			TxtReseau += nomSymbole(SINONSI);
			break;
		default:
			TxtReseau += nomSymbole(SI);
			TxtReseau += "        ";
			break;
		}
		TxtReseau += "(";
		reEcritArbreRE(maille.branche);
		TxtReseau += TxtArbre;
		TxtReseau += ")\n";
		//conclusion du SI      -1 pour ne pas écrire SINON
		reEcritReseauRE(maille.apG, -1);
		TxtReseau += "\r\n";
		//
		reEcritReseauRE(maille.apD, maille.code);
		break;
	case NUM:
		switch (prec) {
		case SI:
			TxtReseau += nomSymbole(SINON);
			TxtReseau += "  \n";
			break;
			//default: TxtReseau+=nomSymbole(SI);break;
		}
		reEcritArbreRE(maille.branche);
		TxtReseau += TxtArbre;
		reEcritReseauRE(maille.apG, maille.code);
		break;
	case PONT:
		return;
	}
}
//---------------------------------------------------------------------------
void CL_Compil::reEcritArbreRE(int n) {
	TxtArbre = AnsiString(" ");

	//les années  !!!
	deLArbre(n, -1);
}
//---------------------------------------------------------------------------
void CL_Compil::deLArbreRE(int i, int opPrec) {
	AnsiString as;
	ST_Branche branche;
	AnsiString message;
	bool avecPar;
	char op;
	int digits = 2;
	branche = Arbre->LesBranches[i];
	op = branche.code;
	switch (branche.code) {
	case NOMBRE:
		as = FloatToStrF((double) branche.valeur, ffNumber, 7, digits);
		if (branche.arg[0] == '%')
			as += "%";
		TxtArbre += as;
		break;

	case IDENT:
		ecritElt(branche.arg[0], branche.arg[1], branche.arg[2]); //131103
		if (branche.date != 0) {
			as = AnsiString("(N-");
			as += AnsiString(branche.date);
			as += AnsiString(")  ");
			TxtArbre += as;
		}
		//date eventuelle
		break;

	case SIGMA: //010302
		ecritSigma(branche.arg[0], branche.arg[1]);
		//date eventuelle
		break;

	case '+': //voir pour( )
	case '-':
		avecPar = parenthese(opPrec);
		if (avecPar == true)
			TxtArbre += "( ";
		deLArbre(branche.arg[0], branche.code);
		if (avecPar == false)
			TxtArbre += "\r\n    "; //110601
		TxtArbre += " " + AnsiString(op) + " ";
		deLArbre(branche.arg[1], branche.code);
		if (avecPar == true)
			TxtArbre += ") ";
		break;

	case '*':
	case '/':
		deLArbre(branche.arg[0], branche.code);
		TxtArbre += "\n " + AnsiString(op) + " ";
		deLArbre(branche.arg[1], branche.code);
		break;
	case '<':
	case '>':
	case '#':
	case '=':

		deLArbre(branche.arg[0], branche.code);
		TxtArbre += " " + AnsiString(op) + " ";
		deLArbre(branche.arg[1], branche.code);
		break;

	case MUNAIRE:
		TxtArbre += " - ";
		deLArbre(branche.arg[0], branche.code);
		break;

	case ET:
		deLArbre(branche.arg[0], branche.code);
		TxtArbre += " ET ";
		deLArbre(branche.arg[1], branche.code);
		break;

	case OU:
		deLArbre(branche.arg[0], branche.code);
		TxtArbre += " OU ";
		deLArbre(branche.arg[1], branche.code);
		break;

	case INFEG:
		deLArbre(branche.arg[0], branche.code);
		TxtArbre += " <= ";
		deLArbre(branche.arg[1], branche.code);
		break;

	case SUPEG:
		deLArbre(branche.arg[0], branche.code);
		TxtArbre += " >+ ";
		deLArbre(branche.arg[1], branche.code);

	default:
		message = AnsiString("Oubli deLArbre") + branche.code;
		ShowMessage(message);
		return;
	}
}
/*
 //---------------------------------------------------------------------------
 bool CL_Compil::parentheseRE(int opPrec)
 {
 switch(opPrec)
 {
 case -1:
 return false;//premiere branche
 case '+':
 case '-':
 case MUNAIRE:
 return false;

 case '*':
 case '/':
 case '<':
 case '>':
 case '#':
 case  '=':
 case ET:
 case OU:
 case INFEG:
 case SUPEG:
 return true;
 default:
 ShowMessage ("Oubli CompFormule");
 return true;
 }
 }
 */
//---------------------------------------------------------------------------
void CL_Compil::ecritEltRE(int noFam, int noCat, int noItem) {
	CL_Elt *elt;
	AnsiString as, asFam;
	elt = trouveElt(noFam, noCat, noItem);
	if (elt == NULL) {
		as = AnsiString("ecritElt elt=NULL noItem=") + "  " + noItem;
		ShowMessage(as);
		TxtArbre += ""; //030303
		return;
//    	 ShowMessage("ecritElt elt=NULL");TxtArbre="";return;}//210502
	}
	if (noCat == -1)
		as = AnsiString(elt->NomFamille) + " : " + elt->Nom;
	else
		as = AnsiString(elt->NomFamille) + " : " + elt->NomCat + " : "
				+ elt->Nom;
	TxtArbre += as;
}
/*
 //---------------------------------------------------------------------------
 CL_Elt *CL_Compil:: trouveElt(int noFam,int noCat,int noItem)
 {
 int i;
 CL_Elt *elt;

 for(i=0;i<V_Elt->Nbelt;i++)
 {
 elt=V_Elt->Vecteur[i];
 if(   elt->NoFamille==  noFam
 //           && elt->NoCategorie==noCat  //inutile et idiot il peut chager de catégorie???
 && elt->NoItem==     noItem)
 return elt;
 }
 return NULL;
 }
 */
//---------------------------------------------------------------------------
void CL_Compil::ecritSigmaRE(int noFam, int noCat) {
	CL_Elt *elt;
	int i;
	AnsiString as;
	as = "";
	for (i = 0; i < V_Elt->Nbelt; i++) {
		elt = V_Elt->Vecteur[i];
		if (elt->NoFamille == noFam && elt->NoCategorie == noCat) {
			as = AnsiString(
					"TOTAL ( " + AnsiString(elt->NomFamille) + " : "
							+ elt->NomCat + " )");
			break;
		}
	}
	TxtArbre += as;
}

