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
void CL_Compil::ReEcritFormule(CL_Prog *prog) {
	static int n;
//bool     TestCompil;

	if (prog == NULL)
		return;

	Reseau = prog->Reseau;
	Arbre = prog->Arbre;

	//pour test
	if (Arbre != NULL) {
		ofstream outfile("compil.txt"); //!!!!!
		ecrireArbre(outfile);
		outfile.close();
	}
	//

	if (Reseau) {
		//ecrireReseau(); //pour test
		TxtReseau = AnsiString("");
		reEcritReseau(0, 0);
		prog->Source = TxtReseau;
	} else if (Arbre) {
		reEcritArbre(Arbre->BrancheX - 1);
		prog->Source = TxtArbre;
		n++;
	}
}
//---------------------------------------------------------------------------
void CL_Compil::reEcritReseau(int i, int prec) {
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
		reEcritArbre(maille.branche);
		TxtReseau += TxtArbre;
		TxtReseau += ")";

		//conclusion du SI      -1 pour ne pas écrire SINON
		reEcritReseau(maille.apG, -1);
		TxtReseau += "\r\n";

		reEcritReseau(maille.apD, maille.code);
		break;
	case NUM:
		switch (prec) {
		case SI:
			TxtReseau += nomSymbole(SINON);
			TxtReseau += " ";
			break;
			//default: TxtReseau+=nomSymbole(SI);break;
		}
		reEcritArbre(maille.branche);
		TxtReseau += TxtArbre;
		reEcritReseau(maille.apG, maille.code);
		break;
	case PONT:
		return;
	}
}
//---------------------------------------------------------------------------
void CL_Compil::reEcritArbre(int n) {
	LongTxtMax = 90;
	TxtArbre = AnsiString(" ");
	//les années  !!!
	if (n >= 0) //271004
		deLArbre(n, -1);
	if (TxtArbre.Length() > 100)
		Decoupe('+', 1, TxtArbre.Length());
//	Compiler(TxtArbre.c_str());
}
//---------------------------------------------------------------------------
bool CL_Compil::deLArbre(int n, int opPrec) {
	int ex;
	AnsiString as;
	ST_Branche branche;
	AnsiString message;
	bool avecPar;
	char op;
	int digits = 2;
	AnsiString blanc = AnsiString("  ");
	bool rep;

	branche = Arbre->LesBranches[n];
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
			if (branche.date == 100)
				TxtArbre += AnsiString("(N)");
			else if (branche.date > 100) {
				ex = branche.date - 100;
				TxtArbre += AnsiString("(") + AnsiString(ex) + AnsiString(")");

			} else {
				as = AnsiString("(N-");
				as += AnsiString(branche.date);
				as += AnsiString(")  ");
				TxtArbre += as;
			}
		}
		//date eventuelle
		break;

	case 'N':
		TxtArbre += "N ";
		break;

	case AN:
		TxtArbre += nomSymbole(AN) + AnsiString(" "); //"AN ";
		break;

	case SIGMA: //010302
		ecritSigma(branche.arg[0], branche.arg[1]);
		//date eventuelle
		break;

	case TOTSUR:
		TxtArbre += nomSymbole(TOTSUR) + AnsiString(" "); //"TOTAL_Culture  ";
		break;

	case '+': //voir pour( )
	case '-':
		avecPar = parenthese(opPrec);
		if (avecPar == true)
			TxtArbre += "( ";
		//branche gauche
		deLArbre(branche.arg[0], branche.code);
		TxtArbre += " " + AnsiString(op) + " ";
		//branche droite
		rep = deLArbre(branche.arg[1], branche.code);
		if (rep == false) //240505
				{
			int l;
			l = TxtArbre.Length();
			TxtArbre.Delete(l - 2, 2);
		}
		if (avecPar == true)
			TxtArbre += ") ";
		break;

	case '*':
	case '/':
		//branche gauche
		deLArbre(branche.arg[0], branche.code);

		TxtArbre += blanc + AnsiString(op) + blanc;

		//branche droite
		deLArbre(branche.arg[1], branche.code);
		break;
	case '<':
	case '>':
	case '#':
	case '=':
		//branche gauche
		deLArbre(branche.arg[0], branche.code);

		TxtArbre += blanc + AnsiString(op) + blanc;
		//branche droite
		deLArbre(branche.arg[1], branche.code);
		break;

	case MUNAIRE:
		TxtArbre += " - ";
		deLArbre(branche.arg[0], branche.code);
		break;

	case ET:
		//branche gauche
		deLArbre(branche.arg[0], branche.code);
		TxtArbre += AnsiString(" ") + nomSymbole(ET) + AnsiString(" "); //" ET ";
		//branche droite
		deLArbre(branche.arg[1], branche.code);
		break;

	case OU:
		//branche gauche
		deLArbre(branche.arg[0], branche.code);
		TxtArbre += AnsiString(" ") + nomSymbole(OU) + AnsiString(" ");
		//TxtArbre+=" OU ";
		//branche droite
		deLArbre(branche.arg[1], branche.code);
		break;

	case INFEG:
		//branche gauche
		deLArbre(branche.arg[0], branche.code);
		TxtArbre += " <= ";
		//branche droite
		deLArbre(branche.arg[1], branche.code);
		break;

	case SUPEG:
		//branche gauche
		deLArbre(branche.arg[0], branche.code);
		TxtArbre += " >= ";
		//branche droite
		deLArbre(branche.arg[1], branche.code);
		break;

	case LOG:
		TxtArbre += " LOG( ";
		deLArbre(branche.arg[0], branche.code);
		TxtArbre += ")";
		break;

	case EXP:
		TxtArbre += " EXP( ";
		deLArbre(branche.arg[0], branche.code);
		TxtArbre += ")";
		break;

	default:
		message = AnsiString("Oubli dans Arbre  ") + branche.code;
		ShowMessage(message);
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
bool CL_Compil::parenthese(int opPrec) {
	switch (opPrec) {
	case -1:
		return false; //premiere branche
	case '+':
	case '-':
	case MUNAIRE:
		return false;

	case '*':
	case '/':
	case '<':
	case '>':
	case '#':
	case '=':
	case ET:
	case OU:
	case INFEG:
	case SUPEG:
	case LOG:
	case EXP:
		return true;
	default:
		ShowMessage("Oubli CompFormule");
		return true;
	}
}
//---------------------------------------------------------------------------
void CL_Compil::ecritElt(int noFam, int noCat, int noItem) {
//int n;
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
	else if (elt->NoFamille == MVT)
		as = AnsiString(elt->NomFamille) + " : " + elt->NomCat + " : "
//             +elt->NomFamille+" : " +elt->Nom;
				+ elt->NomTypeMvtAni(elt->NoType) + " : " + elt->Nom;
	else
		as = AnsiString(elt->NomFamille) + " : " + elt->NomCat + " : "
				+ elt->Nom;
	TxtArbre += as;
}
//---------------------------------------------------------------------------
CL_Elt *CL_Compil::trouveElt(int noFam, int noCat, int noItem) {
	int i;
	CL_Elt *elt;
	int noType;
	if (noFam != MVT) {
		for (i = 0; i < V_Elt->Nbelt; i++) {
			elt = V_Elt->Vecteur[i];
			if (elt->NoFamille == noFam
			//&& elt->NoCategorie==noCat  //inutile et idiot il peut changer de catégorie???
					&& elt->NoItem == noItem)
				return elt;
		}
	} else {
		//je n'avais prévu ... voirCompilateur unIdent
		noType = noCat;
		for (i = 0; i < V_Elt->Nbelt; i++) {
			elt = V_Elt->Vecteur[i];

			//if(   elt->NoFamille==  noFam
			//  && elt->NoType   ==  noType
			//   && elt->NoItem==     noItem)
			if (elt->NoFamille == noFam) {
				if (elt->NoType == noType) {
					if (elt->NoItem == noItem) {
						return elt;
					}
				}
			}
		}
	}
	return NULL;
}
//---------------------------------------------------------------------------
void CL_Compil::ecritSigma(int noFam, int noCat) {
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
	/*
	 if(TxtArbre.Length()+as.Length() <LongTxtMax)
	 TxtArbre+=as;
	 else
	 {
	 TxtArbre+=AnsiString("\n")+as;
	 n=TxtArbre.Length()%90;
	 LongTxtMax=(n+1)*90;
	 }
	 */
}
//---------------------------------------------------------------------------
void CL_Compil::Decoupe(char op, int n0, int nMax) {
	int n, n1;
	char car;
//char opSuivant;
	if (nMax - n0 <= 100)
		return;
	n1 = n0;
	//if(op=='*')    //a faire
	for (n = n0; n < nMax; n++) {
		car = TxtArbre[n];
		if (car == '(') {
			trouveParFermante(n);
			continue;
		}
		if (car == op) {
			//découpe ici en n1
			n1 = n;
			TxtArbre[n - 1] = '\n';
			if (op == '+' && (n - n0) >= 100) {
				Decoupe('*', n0, n);
				if ((nMax - n) < 100)
					return;
			}
		}
	}
	if (op == '+' && (nMax - n1 >= 100))
		Decoupe('*', n1, nMax);
}
//---------------------------------------------------------------------------
void CL_Compil::trouveParFermante(int &n0) {
	int n, nMax;
	int nParFerm = 0;
	int nParOuv = 1;
	char car;
	for (n = n0 + 1; n < nMax; n++) {
		car = TxtArbre[n];
		if (car == '(')
			nParOuv++;
		if (car == ')') {
			nParFerm++;
			if (nParFerm == nParOuv) {
				n0 = n;
				return;
			}
		}
	}
}

