// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'hh_funcs.pas' rev: 6.00

#ifndef hh_funcsHPP
#define hh_funcsHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <FileCtrl.hpp>	// Pascal unit
#include <Registry.hpp>	// Pascal unit
#include <ShellAPI.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit
//-- user supplied -----------------------------------------------------------

namespace Hh_funcs {
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum THostType {
	htHHAPI, htKeyHHexe, htHHexe
};
#pragma option pop

#pragma option push -b-
enum TPrefixType {
	ptNone, ptIE3, ptIE4
};
#pragma option pop

typedef void __fastcall (*THelpProcCallback1)(int Data);

typedef void __fastcall (*THelpProcCallback2)(int Data, int X, int Y);

class DELPHICLASS THookHelpSystem;
class PASCALIMPLEMENTATION THookHelpSystem : public System::TObject
{
	typedef System::TObject inherited;

private:
	Forms::THelpEvent FOldHelpEvent;
	AnsiString FChmFile;
	AnsiString FWinDef;
	THostType FHostType;
#pragma pack(push, 1)
	Types::TPoint FPopupXY;
#pragma pack(pop)

	bool __fastcall HelpHook(Word Command, int Data, bool &CallHelp);

public:
	THelpProcCallback1 HelpCallback1;
	THelpProcCallback2 HelpCallback2;
	bool FOKToCallOldHelpEvent;
	__fastcall THookHelpSystem(AnsiString aDefChmFile, AnsiString aDefWinDef, THostType aHostType);
	__fastcall virtual ~THookHelpSystem(void);
	int __fastcall HelpContext(unsigned aContextId);
	int __fastcall HelpTopic(AnsiString aTopic);
	int __fastcall HelpTopic2(AnsiString aChmFile, AnsiString aTopic, AnsiString aWinDef);
	int __fastcall HelpTopic3(AnsiString aChmPath);
	__property AnsiString ChmFile = {read=FChmFile, write=FChmFile};
	__property AnsiString WinDef = {read=FWinDef, write=FWinDef};
	__property THostType HostType = {read=FHostType, write=FHostType, nodefault};
};

class DELPHICLASS TDLogFile;
class PASCALIMPLEMENTATION TDLogFile : public System::TObject
{
	typedef System::TObject inherited;

private:
	AnsiString FFilename;
	bool FDebugMode;
	bool FTimeStamp;
	bool FHeaderDump;
	bool FAppendMode;

public:
	__fastcall TDLogFile(AnsiString aFilename, bool aDebugMode, bool aTimeStamp, bool aHeaderDump, bool aAppendMode);
	__fastcall virtual ~TDLogFile(void);
	void __fastcall CopyLogTo(AnsiString aNewFilename);
	void __fastcall DebugOut(AnsiString msgStr, const System::TVarRec * Args, const int Args_Size);
	void __fastcall DebugOut2(AnsiString msgStr, const System::TVarRec * Args, const int Args_Size);
	void __fastcall ReportError(AnsiString errStr, const System::TVarRec * Args, const int Args_Size);
	void __fastcall Show(void);
	void __fastcall Reset(void);
	AnsiString __fastcall GetLogDir();
	__property AnsiString Filename = {read=FFilename, write=FFilename};
	__property bool DebugMode = {read=FDebugMode, write=FDebugMode, nodefault};
	__property bool HeaderDump = {read=FHeaderDump, write=FHeaderDump, nodefault};
	__property bool AppendMode = {read=FAppendMode, write=FAppendMode, nodefault};
};

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE bool _hhInstalled;
extern PACKAGE AnsiString _hhVerStr;
extern PACKAGE Word _hhMajVer;
extern PACKAGE Word _hhMinVer;
extern PACKAGE Word _hhBuildNo;
extern PACKAGE Word _hhSubBuildNo;
extern PACKAGE AnsiString _hhFriendlyVerStr;
extern PACKAGE bool _ieInstalled;
extern PACKAGE AnsiString _ieVerStr;
extern PACKAGE AnsiString _ieFriendlyVerStr;
extern PACKAGE AnsiString _RunDir;
extern PACKAGE AnsiString _ModulePath;
extern PACKAGE AnsiString _ModuleDir;
extern PACKAGE AnsiString _ModuleName;
extern PACKAGE TDLogFile* _HHDbgObj;
#define HOST_HHEXE "HH.EXE"
#define HOST_KEYHHEXE "KeyHH.EXE"
#define HH_PREFIX_IE4 "ms-its:"
#define HH_PREFIX_IE3 "mk:@MSITStore:"
static const Shortint HH_ERR_AllOK = 0x0;
static const Shortint HH_ERR_HHNotInstalled = 0x1;
static const Shortint HH_ERR_KeyHHexeNotFound = 0x2;
static const Shortint HH_ERR_HHexeNotFound = 0x3;
extern PACKAGE System::ResourceString _st_HH_ERR_HHNotInstalled;
#define Hh_funcs_st_HH_ERR_HHNotInstalled System::LoadResourceString(&Hh_funcs::_st_HH_ERR_HHNotInstalled)
extern PACKAGE System::ResourceString _st_HH_ERR_KeyHHexeNotFound;
#define Hh_funcs_st_HH_ERR_KeyHHexeNotFound System::LoadResourceString(&Hh_funcs::_st_HH_ERR_KeyHHexeNotFound)
extern PACKAGE System::ResourceString _st_HH_ERR_HHexeNotFound;
#define Hh_funcs_st_HH_ERR_HHexeNotFound System::LoadResourceString(&Hh_funcs::_st_HH_ERR_HHexeNotFound)
extern PACKAGE System::ResourceString _st_HH_ERR_Unknown;
#define Hh_funcs_st_HH_ERR_Unknown System::LoadResourceString(&Hh_funcs::_st_HH_ERR_Unknown)
extern PACKAGE System::ResourceString _st_GLE_FileNotFound;
#define Hh_funcs_st_GLE_FileNotFound System::LoadResourceString(&Hh_funcs::_st_GLE_FileNotFound)
extern PACKAGE System::ResourceString _st_GLE_PathNotFound;
#define Hh_funcs_st_GLE_PathNotFound System::LoadResourceString(&Hh_funcs::_st_GLE_PathNotFound)
extern PACKAGE System::ResourceString _st_GLE_AccessDenied;
#define Hh_funcs_st_GLE_AccessDenied System::LoadResourceString(&Hh_funcs::_st_GLE_AccessDenied)
extern PACKAGE System::ResourceString _st_GLE_InsufficientMemory;
#define Hh_funcs_st_GLE_InsufficientMemory System::LoadResourceString(&Hh_funcs::_st_GLE_InsufficientMemory)
extern PACKAGE System::ResourceString _st_GLE_MediaIsWriteProtected;
#define Hh_funcs_st_GLE_MediaIsWriteProtected System::LoadResourceString(&Hh_funcs::_st_GLE_MediaIsWriteProtected)
extern PACKAGE System::ResourceString _st_GLE_DeviceNotReady;
#define Hh_funcs_st_GLE_DeviceNotReady System::LoadResourceString(&Hh_funcs::_st_GLE_DeviceNotReady)
extern PACKAGE System::ResourceString _st_GLE_FileInUse;
#define Hh_funcs_st_GLE_FileInUse System::LoadResourceString(&Hh_funcs::_st_GLE_FileInUse)
extern PACKAGE System::ResourceString _st_GLE_DiskFull;
#define Hh_funcs_st_GLE_DiskFull System::LoadResourceString(&Hh_funcs::_st_GLE_DiskFull)
extern PACKAGE System::ResourceString _st_GLE_WindowsVersionIncorrect;
#define Hh_funcs_st_GLE_WindowsVersionIncorrect System::LoadResourceString(&Hh_funcs::_st_GLE_WindowsVersionIncorrect)
extern PACKAGE System::ResourceString _st_GLE_NotAWindowsOrMSDosProgram;
#define Hh_funcs_st_GLE_NotAWindowsOrMSDosProgram System::LoadResourceString(&Hh_funcs::_st_GLE_NotAWindowsOrMSDosProgram)
extern PACKAGE System::ResourceString _st_GLE_CorruptFileOrDisk;
#define Hh_funcs_st_GLE_CorruptFileOrDisk System::LoadResourceString(&Hh_funcs::_st_GLE_CorruptFileOrDisk)
extern PACKAGE System::ResourceString _st_GLE_CorruptRegistry;
#define Hh_funcs_st_GLE_CorruptRegistry System::LoadResourceString(&Hh_funcs::_st_GLE_CorruptRegistry)
extern PACKAGE System::ResourceString _st_GLE_GeneralFailure;
#define Hh_funcs_st_GLE_GeneralFailure System::LoadResourceString(&Hh_funcs::_st_GLE_GeneralFailure)
extern PACKAGE bool _DebugMode;
extern PACKAGE int __fastcall MessageBox2(AnsiString aMsg, unsigned Uflags);
extern PACKAGE void __fastcall ShowMessage2(AnsiString aMsg);
extern PACKAGE bool __fastcall YNBox2(AnsiString aMsg);
extern PACKAGE void __fastcall HHShowError(int err);
extern PACKAGE void __fastcall HHCloseAll(void);
extern PACKAGE int __fastcall HHDisplayTopic(AnsiString aChmFile, AnsiString aTopic, AnsiString aWinDef, THostType aHostType);
extern PACKAGE int __fastcall HHTopic(AnsiString aCHMPath, THostType aHostType);
extern PACKAGE int __fastcall HHHelpContext(AnsiString aChmFile, unsigned aContextID, AnsiString aWinDef, THostType aHostType);
extern PACKAGE int __fastcall HHContext(AnsiString aChmPath, int aContextId, THostType aHostType);
extern PACKAGE AnsiString __fastcall HHFormat(AnsiString aChmFile, AnsiString aTopic, AnsiString aWinDef, TPrefixType aPrefixType);
extern PACKAGE void __fastcall HHSlitCmdStr(AnsiString s, AnsiString &aChmFile, AnsiString &aTopic, AnsiString &aWinDef);
extern PACKAGE void __fastcall HHSplitCmdStr(AnsiString s, AnsiString &aChmFile, AnsiString &aTopic, AnsiString &aWinDef);
extern PACKAGE void __fastcall DosToUnix(AnsiString &filename);
extern PACKAGE void __fastcall UnixToDos(AnsiString &filename);
extern PACKAGE int __fastcall StrPosC(const AnsiString s, const AnsiString find);
extern PACKAGE int __fastcall StrPosI(const AnsiString s, const AnsiString find);
extern PACKAGE int __fastcall StrRepC(AnsiString &s, const AnsiString find, const AnsiString repl);
extern PACKAGE int __fastcall StrRepI(AnsiString &s, const AnsiString find, const AnsiString repl);
extern PACKAGE int __fastcall StrRepIA(AnsiString &s, const AnsiString find, const AnsiString repl);
extern PACKAGE int __fastcall StrRepCA(AnsiString &s, const AnsiString find, const AnsiString repl);
extern PACKAGE void __fastcall StripL(AnsiString &s, char c);
extern PACKAGE void __fastcall StripR(AnsiString &s, char c);
extern PACKAGE void __fastcall StripLR(AnsiString &s, char c);
extern PACKAGE AnsiString __fastcall MkStr(char c, int count);
extern PACKAGE AnsiString __fastcall BoolToYN(bool b);
extern PACKAGE AnsiString __fastcall GetWinDir();
extern PACKAGE AnsiString __fastcall GetWinSysDir();
extern PACKAGE AnsiString __fastcall GetWinTempDir();
extern PACKAGE AnsiString __fastcall GetFileVer(AnsiString aFilename, Word &aV1, Word &aV2, Word &aV3, Word &aV4);
extern PACKAGE AnsiString __fastcall GetFileVerStr(AnsiString aFilename);
extern PACKAGE AnsiString __fastcall GetIEVer(Word &V1, Word &V2, Word &V3, Word &V4);
extern PACKAGE int __fastcall VerCompare(Word va1, Word va2, Word va3, Word va4, Word vb1, Word vb2, Word vb3, Word vb4);
extern PACKAGE AnsiString __fastcall GetHHFriendlyVer();
extern PACKAGE int __fastcall Check_IE_Version(int x1, int x2, int x3, int x4);
extern PACKAGE int __fastcall Check_WMP_Version(int x1, int x2, int x3, int x4);
extern PACKAGE AnsiString __fastcall GetIEFriendlyVer();
extern PACKAGE int __fastcall Check_HH_Version(int x1, int x2, int x3, int x4);
extern PACKAGE bool __fastcall ShellExec(AnsiString aFilename, AnsiString aParams);
extern PACKAGE AnsiString __fastcall GetLastErrorStr();
extern PACKAGE AnsiString __fastcall GetRegStr(HKEY rootkey, const AnsiString key, const AnsiString dataName);
extern PACKAGE bool __fastcall RegKeyNameExists(HKEY rootkey, const AnsiString key, const AnsiString dataName);
extern PACKAGE void __fastcall PutRegStr(HKEY rootkey, const AnsiString key, const AnsiString name, const AnsiString value);
extern PACKAGE bool __fastcall IsDirWritable(AnsiString aDir);
extern PACKAGE bool __fastcall DirExists(AnsiString dirName);
extern PACKAGE void __fastcall DebugOut(AnsiString msgStr, const System::TVarRec * Args, const int Args_Size);
extern PACKAGE void __fastcall DebugOut2(AnsiString msgStr, const System::TVarRec * Args, const int Args_Size);
extern PACKAGE void __fastcall ShowDebugFile(void);
extern PACKAGE void __fastcall ResetDebugFile(void);
extern PACKAGE void __fastcall ReportError(AnsiString errStr, const System::TVarRec * Args, const int Args_Size);

} /* namespace Hh_funcs */
using namespace Hh_funcs;
#pragma option pop	// -w-
#pragma option pop	// -Vx
#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// hh_funcs
