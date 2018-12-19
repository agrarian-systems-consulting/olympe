//---------------------------------------------------------------------------
#ifndef TVVarianteAgriH
#define TVVarianteAgriH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TTVVarianteAgriFrm: public TForm {
	__published: // Composants gérés par l'EDI
TTreeView	*TV;
	void __fastcall TVDblClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall TVClick(TObject *Sender);

private: // Déclarations de l'utilisateur
	void __fastcall trouveRow(CL_Agriculteur *agri);
public:// Déclarations de l'utilisateur
	void TexteCaption(void);
	CL_Agriculteur *Agri;
	__fastcall TTVVarianteAgriFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTVVarianteAgriFrm *TVVarianteAgriFrm;
//---------------------------------------------------------------------------
#endif
