//---------------------------------------------------------------------------

#ifndef MatriceH
#define MatriceH
//---------------------------------------------------------------------------
template<class T> class Matrice {
public:
	Matrice(int i, int j);
	~Matrice();
	int iX, jX;
	float **T;
};

void test(void);
#endif
