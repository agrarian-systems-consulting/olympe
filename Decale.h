/*
 QV004  formule d�calage
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
 �88�89�90�91�92�                            materiel
 ________________
 j=       0  1  2  3  4  5  6  7  8  9
 _______________________________
 �90�91�92�93�94�96�96�97�98�99�       simulation
 _______________________________

 else
 {
 n0=0;
 j0=a_achat- a_deb;    j0=94-90=4
 }
 n=  0  1  2  3  4
 ________________
 �94�95�96�97�98�          materiel
 ________________
 j=       0  1  2  3  4  5  6  7  8  9
 �����������������������������Ŀ
 �90�91�92�93�94�96�96�97�98�99�       simulation
 �������������������������������
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