//---------------------------------------------------------------------------

#pragma hdrstop

#include "CL_Repart.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
CL_Repart::CL_Repart() {
	Nom = "";
	for (int i = 0; i < 36; i++)
		Pcent[i] = 0.;
}
//---------------------------------------------------------------------------
CL_Repart::CL_Repart(CL_Repart *source) {
	Nom = source->Nom;
	NoCategorie = source->NoCategorie;
	Categorie = source->Categorie;
	for (int i = 0; i < 36; i++)
		Pcent[i] = source->Pcent[i];
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int CL_Repart::Cmp(CL_Repart *source) {
	return (Nom.AnsiCompare(source->Nom));
}
//---------------------------------------------------------------------------
float CL_Repart::Total(void) {
	int i;
	float total;
	total = 0.;
	for (i = 0; i < 36; i++)
		total += Pcent[i];
	return total;
}
//---------------------------------------------------------------------------
void CL_Repart::GrilleEcrire(TStringGrid* sg, float valTot) {
	int i, r, c;
	for (c = 1, i = 0; c < 4; c++)
		for (r = 1; r < 13; r++)
			sg->Cells[c][r] = Aff(Pcent[i++]);

	if (sg->ColCount < 7)
		return;

	for (c = 4, i = 0; c < 7; c++)
		for (r = 1; r < 13; r++)
			sg->Cells[c][r] = Aff(valTot * Pcent[i++] / 100., 0);
}
//---------------------------------------------------------------------------
AnsiString CL_Repart::Aff(float x) {
	int y;
	if (x == 0)
		return AnsiString(" "); //"" ou " "      ????
	y = x;
	if (y == x)
		return FloatToStrF((double) x, ffNumber, 7, 0);
	else
		return FloatToStrF((double) x, ffNumber, 7, 2);
}
//---------------------------------------------------------------------------
AnsiString CL_Repart::Aff(float x, int digits) {
	if (x == 0)
		return AnsiString(" "); //"" ou " "      ????
	return FloatToStrF((double) x, ffNumber, 7, digits);
}
//---------------------------------------------------------------------------
void CL_Repart::GrilleLire(TStringGrid* SG) {
	int c, r, i;
	i = 0;
	for (c = 1; c < 4; c++) {
		for (r = 1; r < 13; r++)
			Pcent[i++] = LireCell(SG, c, r);
	}
}
//---------------------------------------------------------------------------
float CL_Repart::LireCell(TStringGrid* SG, int col, int row) {
	return as2float(SG->Cells[col][row]);
}
//---------------------------------------------------------------------------
float CL_Repart::as2float(AnsiString as) {
	int n, c;
	char car;
	char chaine[20];

	as = as.Trim();
	n = as.Length();
	if (n == 0)
		return 0.;
	c = 0;
	for (n = 0; n < as.Length(); n++) {
		car = as[n + 1];
		if (car >= '0' && car <= '9')
			chaine[c++] = car;
		else if (car == '.')
			chaine[c++] = car;
	}
	chaine[c] = 0;
	return atof(chaine);
}

