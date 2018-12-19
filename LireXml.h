//---------------------------------------------------------------------------

#ifndef LireXmlH
#define LireXmlH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "LibXmlComps.hpp"
#include "LibXmlParser.hpp"

#include "LesClassesApp.h"
#include "LesVecteurs.hse"

//---------------------------------------------------------------------------
class TLireXmlFrm: public TForm {
	__published: // Composants gérés par l'EDI
	void __fastcall FormActivate(TObject *Sender);
private:
	// Déclarations de l'utilisateur
public:
	// Déclarations de l'utilisateur
	void __fastcall Scanner(void);void __fastcall LireLesSystemesUnite(AnsiString balise);void __fastcall LireLesTva(AnsiString balise);void __fastcall LireLesTvaDefaut(AnsiString balise);

	void __fastcall LireLesItems(AnsiString balise) {};void __fastcall LireLesItems(AnsiString balise,
			CL_Vecteur<CL_Categorie> *vCat,
			CL_Vecteur<CL_Item> *vItem);

	void __fastcall LireItem(AnsiString balise,
			CL_Categorie *cat,CL_Vecteur<CL_Item> *vItem);

	CL_SystemeUnite* TrouveSystemeUnite(AnsiString UUt);

	void __fastcall LireLesBestiaux(AnsiString balise,
			CL_Vecteur<CL_Categorie> *vCat,
			CL_Vecteur<CL_Bestiaux> *vBestiaux);void __fastcall LireBestiaux(AnsiString balise,
			CL_Categorie *cat,CL_Vecteur<CL_Bestiaux> *vBestiaux);

	void __fastcall LireLesCalendriers(AnsiString balise,
			CL_Vecteur<CL_Calendrier> *vCat);

	void __fastcall LireCalendrier(AnsiString balise,CL_Calendrier *calendrier);void __fastcall LirePeriodeBorne(AnsiString asValue,int &x,int &y);void __fastcall LireLesEspeces(AnsiString balise);void __fastcall LirePhase(AnsiString as,int* phase);

	void __fastcall LireLesAteliers(AnsiString balise,
			CL_Vecteur<CL_Categorie> *vCat,
			CL_Vecteur<CL_Atelier> *vAtelier);void __fastcall LireAtelier(AnsiString balise,
			CL_Categorie *cat,CL_Espece *espece,
			CL_Vecteur<CL_Atelier> *vAtelier);void __fastcall LireProChaAtelier(AnsiString as,CL_Atelier *atelier,
			CL_Vecteur<CL_ItemParAtelier> *vItemPA);CL_Item* __fastcall TrouveItem(AnsiString as,
			AnsiString asNomCat,AnsiString asNomItem);void __fastcall LireChaVolAtelier(AnsiString as,CL_Atelier *atelier,
			CL_Vecteur<CL_ItemParAtelier> *vItemPA);

	void __fastcall LireLesIndicateurs(AnsiString balise);

	__fastcall TLireXmlFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLireXmlFrm *LireXmlFrm;
//---------------------------------------------------------------------------
#endif
