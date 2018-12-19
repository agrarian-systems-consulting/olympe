//---------------------------------------------------------------------------

#ifndef CL_CommH
#define CL_CommH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>

class CL_Comm {
public:
	CL_Comm();
	CL_Comm(int noItem);
	CL_Item *Item;
	int NoItem;
	float Production[N_X * 2];
	float Reste[N_X * 2];
	float PrixRevient[N_X * 2];

	void InsereProdAvant(float *quantite);
	void InsereProdApres(float *quantite);
	void InserePrixRevientAvant(float *quantite);
	void InserePrixRevientApres(float *quantite);
	void CalculVenteQ(float *vente);
	void CalculVenteV(float *vente);
	void CalculStockQ(float *stock);
	void CalculStockV(float *stock);
};
//---------------------------------------------------------------------------
#endif

