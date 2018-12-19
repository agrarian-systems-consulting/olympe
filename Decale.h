/*
 QV004  formule d‚calage
 */

//void calcul_j0_j9_n0(int a_action,int duree,int &0,int &j9,int &n0);
/*-------------------------------------------------------------------------*/
/*
 a_deb=An_0 -DEBUT       90= 93-3
 duree=4

 if(a_achat <= a_deb)       88 <= 90
 {
 n0=a_deb - a_achat;    n0=90-88=2
 j0=0;                 j0=0
 }
 j9 = a_achat + immo->duree + 1 -a_deb;  88 + 5  -90= 3

 n0        j9

 n= 0  1  2  3  4
 ________________
 ³88³89³90³91³92³                            materiel
 ________________
 j=       0  1  2  3  4  5  6  7  8  9
 _______________________________
 ³90³91³92³93³94³96³96³97³98³99³       simulation
 _______________________________

 else
 {
 n0=0;
 j0=a_achat- a_deb;    j0=94-90=4
 }
 n=  0  1  2  3  4
 ________________
 ³94³95³96³97³98³          materiel
 ________________
 j=       0  1  2  3  4  5  6  7  8  9
 ÚÄÄÂÄÄÂÄÄÂÄÄÂÄÄÂÄÄÂÄÄÂÄÄÂÄÄÂÄÄ¿
 ³90³91³92³93³94³96³96³97³98³99³       simulation
 ÀÄÄÁÄÄÁÄÄÁÄÄÁÄÄÁÄÄÁÄÄÁÄÄÁÄÄÁÄÄÙ
 j9 = a_achat + immo->duree + 1 -a_deb;  94 + 5  -90= 9


 */
/*-------------------------------------------------------------------------*/
void calcul_j0_j9_n0(int a_action, int duree, int &j0, int &j9, int &n0) {
	int a_deb;
	int DEBUT = 0; // A VOIR
	a_deb = An_0 - DEBUT;
	if (a_action <= a_deb) {
		n0 = a_deb - a_action;
		j0 = 0;
	} else {
		n0 = 0;
		j0 = a_action - a_deb;
	}

	j9 = a_action + duree + 1 - a_deb;
	if (j9 > N_X - 1)
		j9 = N_X - 1;
}