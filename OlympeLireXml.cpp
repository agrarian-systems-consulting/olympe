//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("DebutXml.cpp", DebutXmlFrm);
USEFORM("LireXml.cpp", LireXmlFrm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	try {
		Application->Initialize();
		Application->CreateForm(__classid(TDebutXmlFrm), &DebutXmlFrm);
		Application->CreateForm(__classid(TLireXmlFrm), &LireXmlFrm);
		Application->Run();
	} catch (Exception &exception) {
		Application->ShowException(&exception);
	} catch (...) {
		try {
			throw Exception("");
		} catch (Exception &exception) {
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
