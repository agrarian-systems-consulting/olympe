//                                 OLYMPEDEC.h
//                          Classes données
#ifndef olympe_dec
#define olympe_dec

#define N_X      10   //années de simulation
#define N_PHASE  40   //14 nb de phase pour pérennes
#define LONNOM  200
#define PRODUIT         0
#define CHARGE          1
#define IRRIGATION      2
#define EXTPOS          3
#define EXTNEG          4
#define RECDIV          5
#define DEPDIV          6
#define TYPEEXP         7
#define ZONE            8
#define CHSTRUCT        9
#define RECFAM         10
#define DEPFAM         11
#define PRIX           12
#define SURFACE        13
#define ANIMAUX        14
#define CULTURE        15
#define PERENNE         16
#define VIVRIER        17
#define AGRI           18
#define INDIC          19
#define ETAT           20
#define EXTER          21
#define QPRODUIT       22
#define QCHARGE        23
#define PPRODUIT       24
#define PCHARGE        25
#define SOLDE          26
#define SOLDECUMUL     27
#define COMPARAISON    28
#define PROCEDURE      29

#define CATPRODUIT     30
#define CATCHARGE      31
#define CATVAR         32

#define MVT            40
#define VENTE          41
#define ACHAT          42
#define NE             43
#define MORT           44
#define BESTIAUX       45
#define VDECIS         46       //vente décision par l'utilisateur  100304 troupeau
#define AACHETER       47

#define CEG            50
#define BILAN          51
#define TRESO          52
#define FAMILLE        53
#define SYNTHESE       54

#define POSTE          100
#define MARGE          101
#define FORME          102
#define TRAIT          103
#define BLANC          104
#define TITRE          105
#define EBE            106
#define CAF            107

#define CATEGORIE      110
#define ITEM           111
#define ATELIER        112
#define ESPECE         113
#define AGRICULTEUR    114
#define ETATSORTIE     115
#define INDICATEUR     116
#define SYSUNITE       117
#define TVA            118
#define VARIABLE       119
#define DICO           120
#define VALEUR         121
#define QUANTITE       122
#define VERGER         123
#define RESULTAT       124
#define SERIECOMP      125
#define CALENDRIER     126
// NouvAgri Ensemble
#define CREER          130
#define COPIER         131
#define MODIFIER       132
#define VOIR           133
#define VARIANTE       134
#define SUPPRIMER      135

#define FINANCE        140
#define IMMO           141
#define AVANCE         142
#define STOCK          143
#define PRODIMMO       144
#define EMP            145
#define EMPLT          146
#define EMPCT          147
#define PETITMAT       148
#define EMPPRIVE       149
#define SUBVENTION     1490
#define AMOR           150

#define VALRESID       151
#define VALACHAT       152
#define VALBRUT        153

#define ANNUITE        155
#define REMB           156
#define INTERET        157
#define NOUVEMP        158
#define DETTE          159

#define EFF            160
#define EFFV           161
#define EFFA           162
#define VALV           163
#define VALA           164
#define VALINV         165

#define ACTION         170
#define AMORDETAIL     171
#define OCCC           191

#define IDENT          310  //cf compilateur.h
#define SANSBORNE      999999
//Aleas                                Agri->TypeAlea=
#define  SANS          0
#define  TENDANCE      1
#define  ENCHDEF       2
#define  ENCHALEA      3
#define  MCARLO        4
#define  SCENARIO      5
//                                    Agri->TypeAgreg=
//#define  SANS          0
#define  TOTAL         1
#define  MOYENNE       2
#define  ENSEMBLE      3
//                     ES->Verrou
#define STANDARD       0
#define MEDTER         1
#endif

