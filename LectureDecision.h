//---------------------------------------------------------------------------

#ifndef LectureDecisionH
#define LectureDecisionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "Olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TLectureDecisionFrm: public TForm {
	__published: // Composants gérés par l'EDI
TRichEdit	*RE;
	TOpenDialog *OpenDialog1;
	TBitBtn *BtBnFichierDecision;
	void __fastcall BtBnFichierDecisionClick(TObject *Sender);
private: // Déclarations de l'utilisateur
	FILE *FichCSV;

	void LireFichierCsv(CL_Agriculteur *agri);
	bool Erreur;
public:// Déclarations de l'utilisateur

	void Lecture(void);
	void VerifNomAgri(char *chaine, CL_Agriculteur *agri);
	void LireCultures(CL_Agriculteur *agri);

	__fastcall TLectureDecisionFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLectureDecisionFrm *LectureDecisionFrm;
//---------------------------------------------------------------------------
#endif
