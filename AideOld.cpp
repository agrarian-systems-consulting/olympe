//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "HtmlHelp.h"

#include "Aide.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAideFrm *AideFrm;
//---------------------------------------------------------------------------
//  INCLURE DANS LE PROJET  hh.pas  hh_funcs.pas D6OnHelpFix.pas

#define HHPathRegKey "CLSID\\{adb880a6-d8ff-11cf-9377-00aa003b7a11}\\InprocServer32"
typedef HWND WINAPI (*HTML_HELP_PROC)(HWND, LPCSTR, UINT, DWORD_PTR);
HANDLE HHLibrary = 0; // handle to the loaded hhctrl.ocx, 0 if not loaded
HTML_HELP_PROC Mon_HtmlHelp; // function pointer for the HtmlHelp() function. Note
// that you cannot name it HtmlHelp because that would
// create a conflict with the declaration in htmlhelp.h

//---------------------------------------------------------------------------
__fastcall TAideFrm::TAideFrm(TComponent* Owner) :
		TForm(Owner) {
}
//------------------------------------------------------------------------------
void __fastcall TAideFrm::FormCreate(TObject *Sender)
{
	EstCree=false;
}
//---------------------------------------------------------------------------
void TAideFrm::AfficherAide(char langue, int HelpContextId) {
	bool rep;
	HWND H;
	Langue = langue;

	// le premier A modifier si nécessaire   cf D Snoeck
	if (HelpContextId == 0)
		HelpContextId = 140;
	if (EstCree == false) {
		rep = Initialiser(langue);
		if (rep == false)
			return;
		EstCree = true;
	}
	// le premier A modifier si nécessaire   cf D Snoeck
	//*********************
	H = GetDesktopWindow();
	m_hWindow = Mon_HtmlHelp(H, AsNomFichAide.c_str(), HH_HELP_CONTEXT,
			HelpContextId);

}
//---------------------------------------------------------------------------
bool TAideFrm::Initialiser(char langue) {
	//construire le nom du ficher d'aide
	switch (langue) {
	case 'F':
//        	AsNomFichAide= ExtractFilePath(ParamStr(0)) + "olympe.chm";break;
		AsNomFichAide = ExtractFilePath(ParamStr(0)) + "olympeAide.chm";
		break;
	case 'E':
		AsNomFichAide = ExtractFilePath(ParamStr(0)) + "olympeHelp.chm";
		break;

	default:
		// a faire
		AsNomFichAide = ExtractFilePath(ParamStr(0)) + "olympeAide.chm";
		break;
	}
	AsNomFichAide = ExpandFileName(AsNomFichAide);

	// s'assurer de l'existence du fichier

	if (FileExists(AsNomFichAide) == false) {
		ShowMessage("Pas de Fichier d'aide\n" + AsNomFichAide);
		return false;
	}

	//Vérifier l'existence de  HTML Help library
	// sortir si n'existe pas
	if (ChargerHtmlHelp() == false) {
		ShowMessage("HTML Help n'est pas installé sur ce PC");
		return false;
	}

	// With dynamic loading it's advised to use HH_INITIALIZE. See the comments
	// for OnClose for more information on why...

	Mon_HtmlHelp(NULL, NULL, HH_INITIALIZE, (DWORD) & m_Cookie);
	EstCree = true;
	return true;
}
//--------------------------------------------------------------------------------------------------
void TAideFrm::Fermer(void) {
	if (EstCree == false)
		return;

	Mon_HtmlHelp(0, NULL, HH_CLOSE_ALL, 0);
	if (HHLibrary != 0) {
		Mon_HtmlHelp(NULL, NULL, HH_UNINITIALIZE, (DWORD) m_Cookie);
		::FreeLibrary(HHLibrary);
		HHLibrary = 0;
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool TAideFrm::ChargerHtmlHelp(void) {
	HKEY HHKey;
	DWORD PathSize = 255;
	char Path[255];
	bool existe = false;

	if (::RegOpenKeyExA(HKEY_CLASSES_ROOT, HHPathRegKey, 0, KEY_QUERY_VALUE,
			(void **) &HHKey) == ERROR_SUCCESS) {
		if (::RegQueryValueExA(HHKey, "", NULL, NULL, (LPBYTE) Path, &PathSize)
				== ERROR_SUCCESS) {
			HHLibrary = ::LoadLibrary(Path);
			if (HHLibrary != 0) {
				Mon_HtmlHelp = (HTML_HELP_PROC) ::GetProcAddress(HHLibrary,
						"HtmlHelpA");
				if (Mon_HtmlHelp == NULL) {
					::FreeLibrary(HHLibrary);
					HHLibrary = 0;
				} else
					existe = true;
			}
		}
		::RegCloseKey(HHKey);
	}
	return existe; //R;
}
//---------------------------------------------------------------------------

