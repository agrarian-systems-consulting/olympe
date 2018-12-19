//---------------------------------------------------------------------------

#ifndef DefCL_CommH
#define DefCL_CommH
class CL_Comm {
public:
	CL_Comm();
	CL_Comm(int noItem);
	int NoItem;
	float Production[N_X * 2];
	float QVente[N_X];
	float VVente[N_X];
	float PrixRevient[N_X * 2];
	float Stock[N_X + 1];
	void InsereProdAvant(float *quantite);
	void InsereProdApres(float *quantite);
	void InserePrixRevientAvant(float *quantite);
	void InserePrixRevientApres(float *quantite);
	void CalculStock(void);
};

//---------------------------------------------------------------------------
#endif
