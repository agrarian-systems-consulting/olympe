#ifndef TConfigurationH
#define TConfigurationH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>

//---------------------------------------------------------------------------
/** Le formulaire de modification des valeurs du fichier de configuration */
class TConfigFrm: public TForm {
	__published: // Composants gérés par l'EDI
TBitBtn	*OK;
	TBitBtn *Annuler;
	TPanel *Panel1;
	TEdit *data_path_edit;
	TEdit *exec_path_edit;
	TLabel *Data_path;
	TLabel *exec_path;
	void __fastcall OKClick(TObject *Sender);
	void __fastcall AnnulerClick(TObject *Sender);
private: // Déclarations utilisateur

public:// Déclarations utilisateur
	__fastcall TConfigFrm();// (TComponent* Owner);
	bool ok;
};
//---------------------------------------------------------------------------
extern PACKAGE TConfigFrm *Config;
//---------------------------------------------------------------------------

#endif

