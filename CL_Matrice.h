//---------------------------------------------------------------------------

#ifndef CL_MatriceH
#define CL_MatriceH
//---------------------------------------------------------------------------
class CL_Matrice {
public:
	CL_Matrice(int i, int j);
	CL_Matrice(CL_Matrice *origine);
	~CL_Matrice();
	int iX, jX;
	float *X;
//    float **X;
	//private:
	bool EstVide(void);
	void ecrireFichier(FILE *fichier);
	void lireFichier(FILE *fichier);
	float val(int i, int j);
	void vaut(int i, int j, float val);

};
/*
 template <class T>class Matrice
 {
 public:
 Matrice(int i,int j);
 ~Matrice();
 int iX,jX;
 float **T;
 };

 void test(void);
 */
#endif
