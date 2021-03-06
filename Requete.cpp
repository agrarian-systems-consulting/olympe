//---------------------------------------------------------------------------
#include <vcl.h>
#include <clx.h>
#pragma hdrstop
#include "olympedec.h"
#include "LesClassesApp.h"
#include "LesVecteurs.hse"

//#include "DefVecteur.h"
#include "Main.h"
#include "FichierLire.h"
#include "AgriClasst.h"

#include "LireAccess.h"

//--------------modifier le 17/08/2010-------------------------------

AnsiString query;

bool requete_R_Alea_Repart(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Repart;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}

bool requete_R_Alea_RepartDetail(TADOQuery *adoQuery, int idRepart) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM RepartDetail ";
	query += "WHERE IdRepart = " + IntToStr(idRepart) + ";";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}

bool requete_R_SystemeUnite(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT SystemeUnite.IdSysUnit, SystemeUnite.UAte, SystemeUnite.UEnt, SystemeUnite.UGlobal, SystemeUnite.Ratio21, SystemeUnite.Ratio32, SystemeUnite.Monnaie ";
	query += "FROM SystemeUnite;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}

bool requete_R_AteAvance(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Ate_Avance ";
	query += "ORDER BY IdAteliers, IdAteSousCateg, Item;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}

bool requete_R_AteImmo(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Ate_ImmoProd ";
	query += "ORDER BY IdAteliers, IdAteSousCateg, Item, IdList;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}

bool requete_R_AteBesTrav(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Ate_BesTrav.NbPhase, Ate_BesTrav.NbPeriodeCal, Ate_BesTrav_Item.* ";
	query +=
			"FROM Ate_BesTrav INNER JOIN Ate_BesTrav_Item ON (Ate_BesTrav.IdDefinitions = Ate_BesTrav_Item.IdDefinitions) AND (Ate_BesTrav.IdDefCateg = Ate_BesTrav_Item.IdDefCateg) AND (Ate_BesTrav.IdAteSousCateg = Ate_BesTrav_Item.IdAteSousCateg) AND (Ate_BesTrav.IdAteliers = Ate_BesTrav_Item.IdAteliers) ";
	query +=
			"ORDER BY Ate_BesTrav_Item.IdAteliers, Ate_BesTrav_Item.IdAteSousCateg, Ate_BesTrav_Item.idDefCateg, iX, jX;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}

/*
 bool requete_R_AteBesTrav(TADOQuery *adoQuery)
 {
 adoQuery->SQL->Clear();
 query = "SELECT * "  ;
 query +="FROM Ate_BesTrav ";
 query +="ORDER BY IdAteliers, IdAteSousCateg, idDefCateg;";
 try
 {
 adoQuery->SQL->Add(query);
 adoQuery->ExecSQL();
 adoQuery->Active=true;
 adoQuery->Open();
 return true;
 }
 catch (Exception &e)
 {
 return false;
 }
 }
 */

bool requete_R_AteBesTravItem(TADOQuery *adoQuery, int _idAteliers,
		int _idAteSousCateg, int _idDefCateg) {

	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Ate_BesTrav_Item ";
	query += "WHERE IdAteliers = " + IntToStr(_idAteliers)
			+ " AND IdAteSousCateg = " + IntToStr(_idAteSousCateg)
			+ " AND IdDefCateg = " + IntToStr(_idDefCateg) + " ";
	query += "ORDER BY iX, jX;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_Agri(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Agri.IdAgri, Agri.Nom, Agri.NoVariante, Agri.OrVar, Agri.Notes, Agri.An_0, Agri.OrSerie, Agri.NoSerie, Agri.NbAnSim ";
	query += "FROM Agri ";
	query += "ORDER BY Agri.IdAgri;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}

bool requete_R_Agri_RepartItem(TADOQuery *adoQuery, int noAgri) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Agri_RepartItem ";
	query += " WHERE NoAgri = " + IntToStr(noAgri);
	query += " ORDER BY NoFamille, IdRepartItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}

bool requete_R_Agri_Animaux(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Agri_Animaux ";
	query += "ORDER BY Agri_Animaux.NoAgri, Agri_Animaux.NoAteSousCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}

bool requete_R_Agri_Assol(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT *";
	query += " FROM Agri_Assol";
	query += " ORDER BY NoAgri, NoAteSousCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}

bool requete_R_Agri_EnCoursCreance(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Agri_EnCoursCreance.NoAgri, Agri_EnCoursCreance.NoItem, Agri_EnCoursCreance.Valeur, Agri_EnCoursCreance.MPaie, Agri_EnCoursCreance.APaie, Agri_EnCoursCreance.NoFamille ";
	query += "FROM Agri_EnCoursCreance ";
	query += "ORDER BY Agri_EnCoursCreance.NoAgri, Agri_EnCoursCreance.NoItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_Agri_Critere(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Agri_Critere.NoAgri, Def_Critere.IdDefCateg, Def_Critere.IdDefItem ";
	query +=
			"FROM Def_Critere INNER JOIN Agri_Critere ON Def_Critere.IdDefItem = Agri_Critere.NoCritere ";
	query +=
			"ORDER BY Agri_Critere.NoAgri, Def_Critere.IdDefCateg, Def_Critere.IdDefItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_Agri_DefSim(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Agri_DefSim.NoAgri, Agri_DefSim.An_0, Agri_DefSim.NbAnSim, Agri_DefSim.MDeb, Agri_DefSim.AnCalage, Agri_DefSim.TypeAlea, Agri_DefSim.NoPrixProd, Agri_DefSim.NoPrixCharge, Agri_DefSim.NoQProd, Agri_DefSim.NoQCharge, Agri_DefSim.NoQExt, Agri_DefSim.TouSPrixProd, Agri_DefSim.TouSPrixCharge, Agri_DefSim.TouSQProd, Agri_DefSim.TouSQCharge, Agri_DefSim.TouSQExt, Agri_DefSim.Chaine ";
	query += "FROM Agri_DefSim ";
	query += "ORDER BY Agri_DefSim.NoAgri;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_Agri_EnCoursDette(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Agri_EnCoursDette.NoItem, Agri_EnCoursDette.Valeur, Agri_EnCoursDette.NoAgri, Agri_EnCoursDette.MPaie, Agri_EnCoursDette.APaie, Agri_EnCoursDette.NoFamille ";
	query += "FROM Agri_EnCoursDette;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}

bool requete_R_Agri_EmpCT(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Agri_EmpCT.NoAgri, Agri_EmpCT.NoItem, Agri_EmpCT.Nom, Agri_EmpCT.Montant, Agri_EmpCT.Taux, Agri_EmpCT.Type, Agri_EmpCT.AReal, Agri_EmpCT.MReal, Agri_EmpCT.MRemb, Agri_EmpCT.Pour ";
	query += "FROM Agri_EmpCT ";
	query += "ORDER BY Agri_EmpCT.NoAgri, Agri_EmpCT.NoItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_Agri_EmpLT(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Agri_EmpLT.NoAgri, Agri_EmpLT.NoItem, Agri_EmpLT.Nom, Agri_EmpLT.Montant, Agri_EmpLT.Duree, Agri_EmpLT.Duree2, Agri_EmpLT.Taux, Agri_EmpLT.Taux2, Agri_EmpLT.Type, Agri_EmpLT.AReal, Agri_EmpLT.MReal, Agri_EmpLT.ARemb, Agri_EmpLT.MRemb, Agri_EmpLT.Pour ";
	query += "FROM Agri_EmpLT ";
	query += "ORDER BY Agri_EmpLT.NoAgri, Agri_EmpLT.NoItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_Agri_FinanceGlobal(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Agri_FinanceGlobal.NoAgri, Agri_FinanceGlobal.NoItem, Agri_FinanceGlobal.An1, Agri_FinanceGlobal.An2, Agri_FinanceGlobal.An3, Agri_FinanceGlobal.An4, Agri_FinanceGlobal.An5, Agri_FinanceGlobal.An6, Agri_FinanceGlobal.An7, Agri_FinanceGlobal.An8, Agri_FinanceGlobal.An9, Agri_FinanceGlobal.An10 ";
	query += "FROM Agri_FinanceGlobal ";
	query += "ORDER BY Agri_FinanceGlobal.NoAgri, Agri_FinanceGlobal.NoItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_FormuleCharge(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Agri_Formule ";
	query += "WHERE (((Agri_Formule.IdList)=2)) ";
	query +=
			"ORDER BY Agri_Formule.NoAgri, Agri_Formule.NoItem, Agri_Formule.IdList, Agri_Formule.NoItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_Agri_FormuleArbre(TADOQuery *adoQuery, int _noAgri,
		int _noFormule, int _noItem, int _idList) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += " FROM Agri_FormuleArbre ";
	query += " WHERE NoAgri = " + IntToStr(_noAgri) + "AND NoFormule = "
			+ _noFormule;
	query += " AND NoItem = " + IntToStr(_noItem) + "AND IdList = " + _idList;

	query += " ORDER BY NoAn, NoBranche;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_Agri_FormuleChStruct(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Agri_Formule ";
	query += "WHERE (((Agri_Formule.IdList)=3)) ";
	query +=
			"ORDER BY Agri_Formule.NoAgri, Agri_Formule.NoItem, Agri_Formule.IdList;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_FormuleDepDiv(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Agri_Formule ";
	query += "WHERE (((Agri_Formule.IdList)=5)) ";
	query +=
			"ORDER BY Agri_Formule.NoAgri, Agri_Formule.NoItem, Agri_Formule.IdList;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_FormuleDepFam(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Agri_Formule ";
	query += "WHERE (((Agri_Formule.IdList)=7)) ";
	query += "ORDER BY NoAgri, NoItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_FormuleExtNeg(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Agri_Formule ";
	query += "WHERE (((Agri_Formule.IdList)=9)) ";
	query += "ORDER BY Agri_Formule.NoAgri, Agri_Formule.NoItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_FormuleExtPos(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Agri_Formule ";
	query += "WHERE (((Agri_Formule.IdList)=8)) ";
	query += "ORDER BY Agri_Formule.NoAgri, Agri_Formule.NoItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_FormuleProduit(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Agri_Formule ";
	query += "WHERE (((Agri_Formule.IdList)=1)) ";
	query +=
			"ORDER BY Agri_Formule.NoAgri, Agri_Formule.NoItem, Agri_Formule.IdList;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_FormuleRecFam(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Agri_Formule ";
	query += "WHERE (((Agri_Formule.IdList)=6)) ";
	query +=
			"ORDER BY Agri_Formule.NoAgri, Agri_Formule.NoItem, Agri_Formule.IdList;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_FormuleRecDiv(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Agri_Formule ";
	query += "WHERE (((Agri_Formule.IdList)=4)) ";
	query +=
			"ORDER BY Agri_Formule.NoAgri, Agri_Formule.NoItem, Agri_Formule.IdList;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_FormuleStockIni(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Agri_Formule ";
	query += "WHERE (((Agri_Formule.IdList)=11)) ";
	query +=
			"ORDER BY Agri_Formule.NoAgri, Agri_Formule.NoItem, Agri_Formule.IdList;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_Immo(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Agri_Immo.NoAgri, Agri_Immo.NoItem, Agri_Immo.Nom, Agri_Immo.NoTva, Agri_Immo.ValAchat, Agri_Immo.AAchat, Agri_Immo.MAchat, Agri_Immo.AVente, Agri_Immo.MVente, Agri_Immo.TypeAmor, Agri_Immo.Duree, Agri_Immo.ValVente ";
	query += "FROM Agri_Immo ";
	query += "ORDER BY Agri_Immo.NoAgri, Agri_Immo.NoItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_LstSer(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT Agri.OrSerie, Agri.IdAgri, Agri.NoSerie ";
	query += "FROM Agri ";
	query += "WHERE (((Agri.NoSerie)>0)) ";
	query += "ORDER BY Agri.OrSerie, Agri.IdAgri, Agri.NoSerie;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_ImmoGlobal(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Agri_ImmoGlobal.NoAgri, Agri_ImmoGlobal.NoItem, Agri_ImmoGlobal.An1, Agri_ImmoGlobal.An2, Agri_ImmoGlobal.An3, Agri_ImmoGlobal.An4, Agri_ImmoGlobal.An5, Agri_ImmoGlobal.An6, Agri_ImmoGlobal.An7, Agri_ImmoGlobal.An8, Agri_ImmoGlobal.An9, Agri_ImmoGlobal.An10 ";
	query += "FROM Agri_ImmoGlobal ";
	query += "ORDER BY Agri_ImmoGlobal.NoAgri, Agri_ImmoGlobal.NoItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_LstVar(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT Agri.OrVar, Agri.IdAgri ";
	query += "FROM Agri ";
	query += "WHERE (((Agri.OrVar)>0) AND ((Agri.NoSerie)=0)) ";
	query += "ORDER BY Agri.OrVar, Agri.IdAgri;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_Occc(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Agri_Occc.NoAgri, Agri_Occc.Ex, Agri_Occc.Montant, Agri_Occc.Pcent, Agri_Occc.Taux, Agri_Occc.Frais ";
	query += "FROM Agri_Occc; ";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_Perenne(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Agri_Perenne.NoAgri, Agri_Perenne.NoAteSousCateg, Agri_Perenne.AnPlant, Agri_Perenne.AnArr, Agri_Perenne.Surface ";
	query += "FROM Agri_Perenne ";
	query += "ORDER BY Agri_Perenne.NoAgri, Agri_Perenne.NoAteSousCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_Petit(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Agri_Petit.NoAgri, Agri_Petit.NoItem, Agri_Petit.ValAchat, Agri_Petit.NoTva ";
	query += "FROM Agri_Petit";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_Plact(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Agri_Plact.NoAgri, Agri_Plact.NoItem, Agri_Plact.Nom, Agri_Plact.Montant, Agri_Plact.Taux, Agri_Plact.Type, Agri_Plact.AReal, Agri_Plact.MReal, Agri_Plact.ATerme, Agri_Plact.MTerme, Agri_Plact.Pour ";
	query += "FROM Agri_Plact ";
	query += "ORDER BY Agri_Plact.NoAgri, Agri_Plact.NoItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_Polstock(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Agri_PolStock.NoAgri, Agri_PolStock.NoItem, Agri_PolStock.Prix, Agri_PolStock.IdSysUnit, Agri_PolStock.PcentStock, Agri_PolStock.MaxiStockable, Agri_PolStock.PcentDecote ";
	query += "FROM Agri_PolStock";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_StockIni(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Agri_StockIni.NoAgri, Agri_StockIni.NoItem, Agri_StockIni.An1, Agri_StockIni.An2, Agri_StockIni.An3, Agri_StockIni.An4, Agri_StockIni.An5, Agri_StockIni.An6, Agri_StockIni.An7, Agri_StockIni.An8, Agri_StockIni.An9, Agri_StockIni.An10 ";
	query += "FROM Agri_StockIni ";
	query += "ORDER BY Agri_StockIni.NoAgri, Agri_StockIni.NoItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

//--TP 2012
bool requete_R_Agri_TroupeauAgri(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT DISTINCT Agri_Troupeau.NoAgri, Agri_Troupeau.NoCatBestiau";
	query += " FROM Agri_Troupeau;";

	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_TroupeauInvAni(TADOQuery *adoQuery, int noAgri,
		int noCatBestiau) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += " FROM Agri_Troupeau";
	query += " WHERE NoAgri = " + IntToStr(noAgri) + " AND NoCatbestiau = "
			+ IntToStr(noCatBestiau);
	query += " ORDER BY NoItem;";

	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_Agri_TroupeauInvAniEff(TADOQuery *adoQuery, int noAgri,
		int noCatBestiau, int noItem) {
	adoQuery->SQL->Clear();

	query = "SELECT *";
	query += " FROM Agri_TroupeauEff";
	query += " WHERE ((NoAgri=" + IntToStr(noAgri) + ")";
	query += " AND (NoCatBestiau=" + IntToStr(noCatBestiau) + ")";
	query += " AND (NoItem=" + IntToStr(noItem) + "));";

	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
bool requete_R_Agri_TroupeauInvAniVal(TADOQuery *adoQuery, int noAgri,
		int noCatBestiau, int noItem) {
	adoQuery->SQL->Clear();

	query = "SELECT Agri_TroupeauVal.*";
	query += " FROM Agri_TroupeauVal";
	query += " WHERE ((Agri_TroupeauVal.NoAgri=" + IntToStr(noAgri) + ")";
	query += " AND (Agri_TroupeauVal.NoCatBestiau=" + IntToStr(noCatBestiau)
			+ ")";
	query += " AND (Agri_TroupeauVal.NoItem=" + IntToStr(noItem) + "));";

	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
bool requete_R_Agri_TroupeauInvAniVente(TADOQuery *adoQuery, int noAgri,
		int noCatBestiau, int noItem) {
	adoQuery->SQL->Clear();

	query = "SELECT Agri_TroupeauVente.*";
	query += " FROM Agri_TroupeauVente";
	query += " WHERE ((Agri_TroupeauVente.NoAgri=" + IntToStr(noAgri) + ")";
	query += " AND (Agri_TroupeauVente.NoCatBestiau=" + IntToStr(noCatBestiau)
			+ ")";
	query += " AND (Agri_TroupeauVente.NoItem=" + IntToStr(noItem) + "));";

	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
bool requete_R_Agri_TroupeauInvAniAchat(TADOQuery *adoQuery, int noAgri,
		int noCatBestiau, int noItem) {
	adoQuery->SQL->Clear();

	query = "SELECT Agri_TroupeauAchat.*";
	query += " FROM Agri_TroupeauAchat";
	query += " WHERE ((Agri_TroupeauAchat.NoAgri=" + IntToStr(noAgri) + ")";
	query += " AND (Agri_TroupeauAchat.NoCatBestiau=" + IntToStr(noCatBestiau)
			+ ")";
	query += " AND (Agri_TroupeauAchat.NoItem=" + IntToStr(noItem) + "));";

	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
bool requete_R_Agri_TroupeauInvAniValAchat(TADOQuery *adoQuery, int noAgri,
		int noCatBestiau, int noItem) {
	adoQuery->SQL->Clear();

	query = "SELECT Agri_TroupeauValAchat.*";
	query += " FROM Agri_TroupeauValAchat";
	query += " WHERE ((Agri_TroupeauValAchat.NoAgri=" + IntToStr(noAgri) + ")";
	query += " AND (Agri_TroupeauValAchat.NoCatBestiau="
			+ IntToStr(noCatBestiau) + ")";
	query += " AND (Agri_TroupeauValAchat.NoItem=" + IntToStr(noItem) + "));";

	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
bool requete_R_Agri_TroupeauInvAniValVente(TADOQuery *adoQuery, int noAgri,
		int noCatBestiau, int noItem) {
	adoQuery->SQL->Clear();

	query = "SELECT Agri_TroupeauValVente.*";
	query += " FROM Agri_TroupeauValVente";
	query += " WHERE ((Agri_TroupeauValVente.NoAgri=" + IntToStr(noAgri) + ")";
	query += " AND (Agri_TroupeauValVente.NoCatBestiau="
			+ IntToStr(noCatBestiau) + ")";
	query += " AND (Agri_TroupeauValVente.NoItem=" + IntToStr(noItem) + "));";

	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
bool requete_R_Agri_TroupeauInvAniEffMax(TADOQuery *adoQuery, int noAgri,
		int noCatBestiau, int noItem) {
	adoQuery->SQL->Clear();

	query = "SELECT Agri_TroupeauEffMax.*";
	query += " FROM Agri_TroupeauEffMax";
	query += " WHERE ((Agri_TroupeauEffMax.NoAgri=" + IntToStr(noAgri) + ")";
	query += " AND (Agri_TroupeauEffMax.NoCatBestiau=" + IntToStr(noCatBestiau)
			+ ")";
	query += " AND (Agri_TroupeauEffMax.NoItem=" + IntToStr(noItem) + "));";

	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
bool requete_R_Agri_TroupeauInvAniNoAtelier(TADOQuery *adoQuery, int noAgri,
		int noCatBestiau, int noItem) {
	adoQuery->SQL->Clear();

	query = "SELECT Agri_TroupeauNoAtelier.*";
	query += " FROM Agri_TroupeauNoAtelier";
	query += " WHERE ((Agri_TroupeauNoAtelier.NoAgri=" + IntToStr(noAgri) + ")";
	query += " AND (Agri_TroupeauNoAtelier.NoCatBestiau="
			+ IntToStr(noCatBestiau) + ")";
	query += " AND (Agri_TroupeauNoAtelier.NoItem=" + IntToStr(noItem) + "));";

	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
bool requete_R_Agri_TroupeauInvAniPVM(TADOQuery *adoQuery, int noAgri,
		int noCatBestiau, int noItem) {
	adoQuery->SQL->Clear();

	query = "SELECT Agri_TroupeauPVM.*";
	query += " FROM Agri_TroupeauPVM";
	query += " WHERE ((Agri_TroupeauPVM.NoAgri=" + IntToStr(noAgri) + ")";
	query += " AND (Agri_TroupeauPVM.NoCatBestiau=" + IntToStr(noCatBestiau)
			+ ")";
	query += " AND (Agri_TroupeauPVM.NoItem=" + IntToStr(noItem) + "));";

	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
bool requete_R_Agri_TroupeauInvAniVIM(TADOQuery *adoQuery, int noAgri,
		int noCatBestiau, int noItem) {
	adoQuery->SQL->Clear();

	query = "SELECT Agri_TroupeauVIM.*";
	query += " FROM Agri_TroupeauVIM";
	query += " WHERE ((Agri_TroupeauVIM.NoAgri=" + IntToStr(noAgri) + ")";
	query += " AND (Agri_TroupeauVIM.NoCatBestiau=" + IntToStr(noCatBestiau)
			+ ")";
	query += " AND (Agri_TroupeauVIM.NoItem=" + IntToStr(noItem) + "));";

	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}

bool requete_R_Agri_Troupeau(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Agri.IdAgri, Agri_Troupeau.*, Agri_TroupeauEff.*, Agri_TroupeauVal.*, Agri_TroupeauValAchat.*, Agri_TroupeauPVM.*, Agri_TroupeauValVente.*, ";
	query +=
			"Agri_TroupeauNoAtelier.*, Agri_TroupeauEffMax.*, Agri_TroupeauVIM.*, Agri_TroupeauAchat.*, Agri_TroupeauVente.* ";
	query +=
			"FROM ((((((((((Agri INNER JOIN Agri_Troupeau ON Agri.IdAgri = Agri_Troupeau.NoAgri) INNER JOIN Agri_TroupeauEff ON (Agri_Troupeau.NoAnimal = Agri_TroupeauEff.NoAnimal) AND ";
	query +=
			"(Agri_Troupeau.NoItem = Agri_TroupeauEff.NoItem) AND (Agri_Troupeau.NoCatBestiau = Agri_TroupeauEff.NoCatBestiau) AND (Agri_Troupeau.NoAgri = Agri_TroupeauEff.NoAgri)) ";
	query +=
			"INNER JOIN Agri_TroupeauVal ON (Agri_Troupeau.NoAnimal = Agri_TroupeauVal.NoAnimal) AND (Agri_Troupeau.NoItem = Agri_TroupeauVal.NoItem) AND ";
	query +=
			"(Agri_Troupeau.NoCatBestiau = Agri_TroupeauVal.NoCatBestiau) AND (Agri_Troupeau.NoAgri = Agri_TroupeauVal.NoAgri)) INNER JOIN Agri_TroupeauValAchat ON (Agri_Troupeau.NoAnimal = Agri_TroupeauValAchat.NoAnimal) ";
	query +=
			"AND (Agri_Troupeau.NoItem = Agri_TroupeauValAchat.NoItem) AND (Agri_Troupeau.NoCatBestiau = Agri_TroupeauValAchat.NoCatBestiau) AND (Agri_Troupeau.NoAgri = Agri_TroupeauValAchat.NoAgri)) ";
	query +=
			"INNER JOIN Agri_TroupeauPVM ON (Agri_Troupeau.NoAnimal = Agri_TroupeauPVM.NoAnimal) AND (Agri_Troupeau.NoItem = Agri_TroupeauPVM.NoItem) AND (Agri_Troupeau.NoCatBestiau = Agri_TroupeauPVM.NoCatBestiau) ";
	query +=
			"AND (Agri_Troupeau.NoAgri = Agri_TroupeauPVM.NoAgri)) INNER JOIN Agri_TroupeauValVente ON (Agri_Troupeau.NoAnimal = ";
	query +=
			"Agri_TroupeauValVente.NoAnimal) AND (Agri_Troupeau.NoItem = Agri_TroupeauValVente.NoItem) AND (Agri_Troupeau.NoCatBestiau = Agri_TroupeauValVente.NoCatBestiau) ";
	query +=
			"AND (Agri_Troupeau.NoAgri = Agri_TroupeauValVente.NoAgri)) INNER JOIN Agri_TroupeauNoAtelier ON (Agri_Troupeau.NoAnimal = Agri_TroupeauNoAtelier.NoAnimal) AND (Agri_Troupeau.NoItem = Agri_TroupeauNoAtelier.NoItem) ";
	query +=
			"AND (Agri_Troupeau.NoCatBestiau = Agri_TroupeauNoAtelier.NoCatBestiau) AND (Agri_Troupeau.NoAgri = Agri_TroupeauNoAtelier.NoAgri)) INNER JOIN ";
	query +=
			"Agri_TroupeauEffMax ON (Agri_Troupeau.NoAnimal = Agri_TroupeauEffMax.NoAnimal) AND (Agri_Troupeau.NoItem = Agri_TroupeauEffMax.NoItem) AND (Agri_Troupeau.NoCatBestiau = Agri_TroupeauEffMax.NoCatBestiau) ";
	query +=
			"AND (Agri_Troupeau.NoAgri = Agri_TroupeauEffMax.NoAgri)) INNER JOIN Agri_TroupeauVIM ON (Agri_Troupeau.NoAnimal = Agri_TroupeauVIM.NoAnimal) AND (Agri_Troupeau.NoItem = Agri_TroupeauVIM.NoItem) ";
	query +=
			"AND (Agri_Troupeau.NoCatBestiau = Agri_TroupeauVIM.NoCatBestiau) AND (Agri_Troupeau.NoAgri = Agri_TroupeauVIM.NoAgri)) INNER JOIN ";
	query +=
			"Agri_TroupeauAchat ON (Agri_Troupeau.NoAnimal = Agri_TroupeauAchat.NoAnimal) AND (Agri_Troupeau.NoItem = Agri_TroupeauAchat.NoItem) AND (Agri_Troupeau.NoCatBestiau = Agri_TroupeauAchat.NoCatBestiau) ";
	query +=
			"AND (Agri_Troupeau.NoAgri = Agri_TroupeauAchat.NoAgri)) INNER JOIN Agri_TroupeauVente ON (Agri_Troupeau.NoAnimal = Agri_TroupeauVente.NoAnimal) AND (Agri_Troupeau.NoItem = Agri_TroupeauVente.NoItem) ";
	query +=
			"AND (Agri_Troupeau.NoCatBestiau = Agri_TroupeauVente.NoCatBestiau) AND (Agri_Troupeau.NoAgri = Agri_TroupeauVente.NoAgri); ";

	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_Agri_TroupeauMVT(TADOQuery *adoQuery, int noAgri,
		int noCatBestiau) {
	adoQuery->SQL->Clear();
	query = "SELECT Agri_TroupeauMvt.*";
	query += " FROM Agri_TroupeauMvt";
	query += " WHERE Agri_TroupeauMvt.NoAgri =  " + AnsiString(noAgri);
	query += " AND Agri_TroupeauMvt.NoCatBestiau =  "
			+ AnsiString(noCatBestiau);
	query +=
			" ORDER BY Agri_TroupeauMvt.NoAgri, Agri_TroupeauMvt.NoCatBestiau, Agri_TroupeauMvt.Ligne, Agri_TroupeauMvt.DateMvt;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
//--

bool requete_R_Agri_Sub(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Agri_Sub.NoAgri, Agri_Sub.NoItem, Agri_Sub.Nom, Agri_Sub.Montant, Agri_Sub.AReal, Agri_Sub.MReal, Agri_Sub.Duree ";
	query += "FROM Agri_Sub ";
	query += "ORDER BY Agri_Sub.NoAgri, Agri_Sub.NoItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_Variable(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Agri_Formule ";
	query += "WHERE (((Agri_Formule.IdList)=10)) ";
	query += "ORDER BY NoAgri, Agri_Formule.NoItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Agri_Vivrier(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Agri_Vivrier.NoAgri, Agri_Vivrier.NoAteSousCateg, Agri_Vivrier.AnPlant, Agri_Vivrier.Duree, Agri_Vivrier.Surface ";
	query += "FROM Agri_Vivrier ";
	query += "ORDER BY Agri_Vivrier.NoAgri, Agri_Vivrier.NoAteSousCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
//todo tp 2012 ajout de order by
bool requete_R_Alea_Categ(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Alea_Categ.IdAleas, Alea_Categ.IdAleaCateg, Alea_Categ.Nom, Alea_Categ.Notes ";
	query +=
			"FROM Alea_Categ ORDER BY Alea_Categ.IdAleas, Alea_Categ.IdAleaCateg; ";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Alea_Item(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Alea_Item;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_AteAnimaux(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Ate_SousCateg.IdAteCateg, Ate_SousCateg.IdAteSousCateg, Ate_SousCateg.Nom, Ate_SousCateg.Derobe, Ate_SousCateg.ValInvRepro, Ate_SousCateg.ValInvAutre, Ate_SousCateg.Notes ";
	query += "FROM Ate_SousCateg ";
	query += "WHERE (((Ate_SousCateg.IdAteliers)=2)) ";
	query += "ORDER BY Ate_SousCateg.IdAteCateg, Ate_SousCateg.IdAteSousCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_AteCatAnimaux(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT Ate_Categ.IdAteCateg, Ate_Categ.Nom ";
	query += "FROM Ate_Categ ";
	query += "WHERE (((Ate_Categ.IdAteliers)=2)) ";
	query += "ORDER BY Ate_Categ.IdAteCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
bool requete_R_AteCatCulture(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT Ate_Categ.IdAteCateg, Ate_Categ.Nom ";
	query += "FROM Ate_Categ ";
	query += "WHERE (((Ate_Categ.IdAteliers)=1)) ";
	query += "ORDER BY Ate_Categ.IdAteCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
bool requete_R_AteCatPerenne(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Ate_Categ.IdAteCateg, Ate_Categ.Nom, Ate_Categ.DebAmor, Ate_Categ.DurAmor, Ate_Categ.NbPhase, Ate_CatPhase.Ph1, Ate_CatPhase.Ph2, Ate_CatPhase.Ph3, Ate_CatPhase.Ph4, Ate_CatPhase.Ph5, Ate_CatPhase.Ph6, Ate_CatPhase.Ph7, Ate_CatPhase.Ph8, Ate_CatPhase.Ph9, Ate_CatPhase.Ph10, Ate_CatPhase.Ph11, Ate_CatPhase.Ph12, Ate_CatPhase.Ph13, Ate_CatPhase.Ph14, Ate_CatPhase.Ph15, Ate_CatPhase.Ph16, Ate_CatPhase.Ph17, Ate_CatPhase.Ph18, Ate_CatPhase.Ph19, Ate_CatPhase.Ph20, Ate_CatPhase.Ph21, Ate_CatPhase.Ph22, Ate_CatPhase.Ph23, Ate_CatPhase.Ph24, Ate_CatPhase.Ph25, Ate_CatPhase.Ph26, Ate_CatPhase.Ph27, Ate_CatPhase.Ph28, Ate_CatPhase.Ph29, Ate_CatPhase.Ph30, Ate_CatPhase.Ph31, Ate_CatPhase.Ph32, Ate_CatPhase.Ph33, Ate_CatPhase.Ph34, Ate_CatPhase.Ph35, Ate_CatPhase.Ph36, Ate_CatPhase.Ph37, Ate_CatPhase.Ph38, Ate_CatPhase.Ph39, Ate_CatPhase.Ph40 ";
	query +=
			"FROM Ate_Categ INNER JOIN Ate_CatPhase ON Ate_Categ.IdAteCateg = Ate_CatPhase.IdAteCateg ";
	query += "WHERE (((Ate_Categ.IdAteliers)=3)) ";
	query += "ORDER BY Ate_Categ.IdAteCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_AteCatVivrier(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Ate_Categ.IdAteCateg, Ate_Categ.Nom, Ate_Categ.DebAmor, Ate_Categ.DurAmor  ";
	query += "FROM Ate_Categ ";
	query += "WHERE (((Ate_Categ.IdAteliers)=4));";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_AteCulture(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Ate_SousCateg.IdAteCateg, Ate_SousCateg.IdAteSousCateg, Ate_SousCateg.Nom, Ate_SousCateg.Derobe, Ate_SousCateg.ValInvRepro, Ate_SousCateg.ValInvAutre, Ate_SousCateg.Notes ";
	query += "FROM Ate_SousCateg ";
	query += "WHERE (((Ate_SousCateg.IdAteliers)=1)) ";
	query += "ORDER BY Ate_SousCateg.IdAteCateg, Ate_SousCateg.IdAteSousCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_AteItemAnimaux(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Ate_Item.IdAteCateg, Ate_Item.IdAteSousCateg, Ate_Item.IdList, Ate_Item.C1IdDefItem, Ate_Item.C3IdDefItem, Ate_Item.Ph0, Ate_Item.Ph1, Ate_Item.Ph2 ";
	query +=
			"FROM ((_Ateliers INNER JOIN Ate_Categ ON [_Ateliers].IdAteliers = Ate_Categ.IdAteliers) INNER JOIN Ate_SousCateg ON (Ate_Categ.IdAteCateg = Ate_SousCateg.IdAteCateg) AND (Ate_Categ.IdAteliers = Ate_SousCateg.IdAteliers)) INNER JOIN (_Ate_ListItem INNER JOIN (Def_Item AS Def_Item_1 RIGHT JOIN (Def_Item RIGHT JOIN Ate_Item ON (Def_Item.IdDefinitions = Ate_Item.C1IdDefinitions) AND (Def_Item.IdDefItem = Ate_Item.C1IdDefItem)) ON (Def_Item_1.IdDefItem = Ate_Item.C3IdDefItem) AND (Def_Item_1.IdDefinitions = Ate_Item.C3IdDefinitions)) ON [_Ate_ListItem].IdAteListItem = Ate_Item.IdList) ON (Ate_SousCateg.IdAteSousCateg = Ate_Item.IdAteSousCateg) AND (Ate_SousCateg.IdAteliers = Ate_Item.IdAteliers) ";
	query += "WHERE (((Ate_Item.IdAteliers)=2)) ";
	query +=
			"ORDER BY Ate_Item.IdAteliers, Ate_Item.IdAteCateg, Ate_Item.IdAteSousCateg, Ate_Item.IdList, Ate_Item.C1IdDefItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
bool requete_R_AteItemCulture(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Ate_Item.IdAteCateg, Ate_Item.IdAteSousCateg, Ate_Item.IdList, Ate_Item.C1IdDefItem, Ate_Item.C3IdDefItem, Ate_Item.Ph0, Ate_Item.Ph1, Ate_Item.Ph2 ";
	query +=
			"FROM ((_Ateliers INNER JOIN Ate_Categ ON [_Ateliers].IdAteliers = Ate_Categ.IdAteliers) INNER JOIN Ate_SousCateg ON (Ate_Categ.IdAteliers = Ate_SousCateg.IdAteliers) AND (Ate_Categ.IdAteCateg = Ate_SousCateg.IdAteCateg)) INNER JOIN (_Ate_ListItem INNER JOIN (Def_Item AS Def_Item_1 RIGHT JOIN (Def_Item RIGHT JOIN Ate_Item ON (Def_Item.IdDefinitions = Ate_Item.C1IdDefinitions) AND (Def_Item.IdDefItem = Ate_Item.C1IdDefItem)) ON (Def_Item_1.IdDefItem = Ate_Item.C3IdDefItem) AND (Def_Item_1.IdDefinitions = Ate_Item.C3IdDefinitions)) ON [_Ate_ListItem].IdAteListItem = Ate_Item.IdList) ON (Ate_SousCateg.IdAteliers = Ate_Item.IdAteliers) AND (Ate_SousCateg.IdAteSousCateg = Ate_Item.IdAteSousCateg) ";
	query += "WHERE (((Ate_Item.IdAteliers)=1)) ";
	query +=
			"ORDER BY Ate_Item.IdAteliers, Ate_Item.IdAteCateg, Ate_Item.IdAteSousCateg, Ate_Item.IdList, Ate_Item.C1IdDefItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
bool requete_R_AteItemPerenne(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Ate_Item.IdAteCateg, Ate_Item.IdAteSousCateg, Ate_Item.IdList, Ate_Item.C1IdDefItem, Ate_Item.C3IdDefItem, Ate_Item.Ph0, Ate_Item.Ph1, Ate_Item.Ph2, Ate_Item.Ph3, Ate_Item.Ph4, Ate_Item.Ph5, Ate_Item.Ph6, Ate_Item.Ph7, Ate_Item.Ph8, Ate_Item.Ph9, Ate_Item.Ph10, Ate_Item.Ph11, Ate_Item.Ph12, Ate_Item.Ph13, Ate_Item.Ph14, Ate_Item.Ph15, Ate_Item.Ph16, Ate_Item.Ph17, Ate_Item.Ph18, Ate_Item.Ph19, Ate_Item.Ph20, Ate_Item.Ph21, Ate_Item.Ph22, Ate_Item.Ph23, Ate_Item.Ph24, Ate_Item.Ph25, Ate_Item.Ph26, Ate_Item.Ph27, Ate_Item.Ph28, Ate_Item.Ph29, Ate_Item.Ph30, Ate_Item.Ph31, Ate_Item.Ph32, Ate_Item.Ph33, Ate_Item.Ph34, Ate_Item.Ph35, Ate_Item.Ph36, Ate_Item.Ph37, Ate_Item.Ph38, Ate_Item.Ph39, Ate_Item.Ph40 ";
	query +=
			"FROM ((_Ateliers INNER JOIN Ate_Categ ON [_Ateliers].IdAteliers = Ate_Categ.IdAteliers) INNER JOIN Ate_SousCateg ON (Ate_Categ.IdAteliers = Ate_SousCateg.IdAteliers) AND (Ate_Categ.IdAteCateg = Ate_SousCateg.IdAteCateg)) INNER JOIN (_Ate_ListItem INNER JOIN (Def_Item AS Def_Item_1 RIGHT JOIN (Def_Item RIGHT JOIN Ate_Item ON (Def_Item.IdDefItem = Ate_Item.C1IdDefItem) AND (Def_Item.IdDefinitions = Ate_Item.C1IdDefinitions)) ON (Def_Item_1.IdDefinitions = Ate_Item.C3IdDefinitions) AND (Def_Item_1.IdDefItem = Ate_Item.C3IdDefItem)) ON [_Ate_ListItem].IdAteListItem = Ate_Item.IdList) ON (Ate_SousCateg.IdAteliers = Ate_Item.IdAteliers) AND (Ate_SousCateg.IdAteSousCateg = Ate_Item.IdAteSousCateg) ";
	query += "WHERE (((Ate_Item.IdAteliers)=3)) ";
	query +=
			"ORDER BY Ate_Item.IdAteliers, Ate_Item.IdAteCateg, Ate_Item.IdAteSousCateg, Ate_Item.IdList, Ate_Item.C1IdDefItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
bool requete_R_AteItemVivrier(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Ate_Item.IdAteCateg, Ate_Item.IdAteSousCateg, Ate_Item.IdList, Ate_Item.C1IdDefItem, Ate_Item.C3IdDefItem, Ate_Item.Ph0, Ate_Item.Ph1, Ate_Item.Ph2, Ate_Item.Ph3, Ate_Item.Ph4 ";
	query +=
			"FROM ((_Ateliers INNER JOIN Ate_Categ ON [_Ateliers].IdAteliers = Ate_Categ.IdAteliers) INNER JOIN Ate_SousCateg ON (Ate_Categ.IdAteCateg = Ate_SousCateg.IdAteCateg) AND (Ate_Categ.IdAteliers = Ate_SousCateg.IdAteliers)) INNER JOIN (_Ate_ListItem INNER JOIN (Def_Item AS Def_Item_1 RIGHT JOIN (Def_Item RIGHT JOIN Ate_Item ON (Def_Item.IdDefinitions = Ate_Item.C1IdDefinitions) AND (Def_Item.IdDefItem = Ate_Item.C1IdDefItem)) ON (Def_Item_1.IdDefItem = Ate_Item.C3IdDefItem) AND (Def_Item_1.IdDefinitions = Ate_Item.C3IdDefinitions)) ON [_Ate_ListItem].IdAteListItem = Ate_Item.IdList) ON (Ate_SousCateg.IdAteSousCateg = Ate_Item.IdAteSousCateg) AND (Ate_SousCateg.IdAteliers = Ate_Item.IdAteliers) ";
	query += "WHERE (((Ate_Item.IdAteliers)=4)) ";
	query +=
			"ORDER BY Ate_Item.IdAteliers, Ate_Item.IdAteCateg, Ate_Item.IdAteSousCateg, Ate_Item.IdList, Ate_Item.C1IdDefItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
bool requete_R_AtePerenne(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Ate_SousCateg.IdAteCateg, Ate_SousCateg.IdAteSousCateg, Ate_SousCateg.Nom, Ate_SousCateg.Derobe, Ate_SousCateg.PImmoExiste, Ate_SousCateg.PImmoFamExiste, Ate_SousCateg.ValInvRepro, Ate_SousCateg.ValInvAutre, Ate_SousCateg.Notes ";
	query += "FROM Ate_SousCateg ";
	query += "WHERE (((Ate_SousCateg.IdAteliers)=3)) ";
	query += "ORDER BY Ate_SousCateg.IdAteCateg, Ate_SousCateg.IdAteSousCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
bool requete_R_AteVivrier(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Ate_SousCateg.IdAteCateg, Ate_SousCateg.IdAteSousCateg, Ate_SousCateg.Nom, Ate_SousCateg.Derobe, Ate_SousCateg.ValInvRepro, Ate_SousCateg.ValInvAutre, Ate_SousCateg.Notes  ";
	query += "FROM Ate_SousCateg ";
	query += "WHERE (((Ate_SousCateg.IdAteliers)=4)) ";
	query += "ORDER BY Ate_SousCateg.IdAteCateg, Ate_SousCateg.IdAteSousCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_AtePiedHaCulture(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Ate_PiedHa ";
	query += "WHERE IdAteliers= 1 ";
	query += "ORDER BY IdAteSousCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
bool requete_R_AtePiedHaAnimaux(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Ate_PiedHa ";
	query += "WHERE IdAteliers= 2 ";
	query += "ORDER BY IdAteSousCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
bool requete_R_AtePiedHaPerenne(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Ate_PiedHa ";
	query += "WHERE IdAteliers= 3 ";
	query += "ORDER BY IdAteSousCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
bool requete_R_AtePiedHaVivrier(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Ate_PiedHa ";
	query += "WHERE IdAteliers= 4 ";
	query += "ORDER BY IdAteSousCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}

bool requete_R_DefBestiaux(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Def_Bestiaux.IdDefCateg, Def_Bestiaux.IdBestiaux, Def_Bestiaux.Nom, Def_Bestiaux.IdOrigine, Def_Bestiaux.IdTva, Def_Bestiaux.Prix, Def_Bestiaux.Vallnv, Def_Bestiaux.Donne1, Def_Bestiaux.DonnePcent1, Def_Bestiaux.Donne2, Def_Bestiaux.DonnePcent2, Def_Bestiaux.Donne3, Def_Bestiaux.DonnePcent3, Def_Bestiaux.Donne4, Def_Bestiaux.DonnePcent4 ";
	query += "FROM Def_Bestiaux ";
	query += "ORDER BY Def_Bestiaux.IdDefCateg, Def_Bestiaux.IdBestiaux;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_DefCalendrier(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Def_Calendrier.IdDefCateg, Def_Calendrier.IdPeriode, Def_Calendrier.Nom, Def_Calendrier.JDeb, Def_Calendrier.MDeb, Def_Calendrier.JFin, Def_Calendrier.MFin, Def_Calendrier.PcentDispo, Def_Calendrier.HpJ ";
	query += "FROM Def_Calendrier ";
	query += "ORDER BY Def_Calendrier.IdDefCateg, Def_Calendrier.IdPeriode;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_DefCatBestiaux(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT Def_Categ.IdDefCateg, Def_Categ.Nom, Def_Categ.Notes ";
	query +=
			"FROM _Definitions INNER JOIN Def_Categ ON [_Definitions].IdDefinitions = Def_Categ.IdDefinitions ";
	query += "WHERE (((Def_Categ.IdDefinitions)=4)) ";
	query += "ORDER BY Def_Categ.IdDefinitions, Def_Categ.IdDefCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_DefCatCalendrier(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT Def_Categ.IdDefCateg, Def_Categ.Nom, Def_Categ.Notes ";
	query +=
			"FROM _Definitions INNER JOIN Def_Categ ON [_Definitions].IdDefinitions = Def_Categ.IdDefinitions ";
	query += "WHERE (((Def_Categ.IdDefinitions)=5)) ";
	query += "ORDER BY Def_Categ.IdDefinitions, Def_Categ.IdDefCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_DefCatCharge(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT Def_Categ.IdDefCateg, Def_Categ.Nom, Def_Categ.Notes ";
	query +=
			"FROM _Definitions INNER JOIN Def_Categ ON [_Definitions].IdDefinitions = Def_Categ.IdDefinitions ";
	query += "WHERE (((Def_Categ.IdDefinitions)=2)) ";
	query += "ORDER BY Def_Categ.IdDefinitions, Def_Categ.IdDefCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_DefCatChStruct(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT Def_Categ.IdDefCateg, Def_Categ.Nom, Def_Categ.Notes ";
	query +=
			"FROM _Definitions INNER JOIN Def_Categ ON [_Definitions].IdDefinitions = Def_Categ.IdDefinitions ";
	query += "WHERE (((Def_Categ.IdDefinitions)=6)) ";
	query += "ORDER BY Def_Categ.IdDefinitions, Def_Categ.IdDefCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_DefCatClassif(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT Def_Categ.IdDefCateg, Def_Categ.Nom, Def_Categ.Notes ";
	query +=
			"FROM _Definitions INNER JOIN Def_Categ ON [_Definitions].IdDefinitions = Def_Categ.IdDefinitions ";
	query += "WHERE (((Def_Categ.IdDefinitions)=13)) ";
	query += "ORDER BY Def_Categ.IdDefinitions, Def_Categ.IdDefCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_DefCatDepDiv(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT Def_Categ.IdDefCateg, Def_Categ.Nom, Def_Categ.Notes ";
	query +=
			"FROM _Definitions INNER JOIN Def_Categ ON [_Definitions].IdDefinitions = Def_Categ.IdDefinitions ";
	query += "WHERE (((Def_Categ.IdDefinitions)=8)) ";
	query += "ORDER BY Def_Categ.IdDefinitions, Def_Categ.IdDefCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_DefCatDepFam(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT Def_Categ.IdDefCateg, Def_Categ.Nom, Def_Categ.Notes ";
	query +=
			"FROM _Definitions INNER JOIN Def_Categ ON [_Definitions].IdDefinitions = Def_Categ.IdDefinitions ";
	query += "WHERE (((Def_Categ.IdDefinitions)=10)) ";
	query += "ORDER BY Def_Categ.IdDefinitions, Def_Categ.IdDefCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_DefCatExternalite(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT Def_Categ.IdDefCateg, Def_Categ.Nom, Def_Categ.Notes ";
	query +=
			"FROM _Definitions INNER JOIN Def_Categ ON [_Definitions].IdDefinitions = Def_Categ.IdDefinitions ";
	query += "WHERE (((Def_Categ.IdDefinitions)=3)) ";
	query += "ORDER BY Def_Categ.IdDefinitions, Def_Categ.IdDefCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_DefCatIndic(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT Def_Categ.IdDefCateg, Def_Categ.Nom, Def_Categ.Notes ";
	query += "FROM Def_Categ ";
	query += "WHERE (((Def_Categ.IdDefinitions)=16)) ";
	query += "ORDER BY Def_Categ.IdDefinitions, Def_Categ.IdDefCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_DefCatEtatSortie(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT Def_Categ.IdDefCateg, Def_Categ.Nom, Def_Categ.Notes ";
	query += "FROM Def_Categ ";
	query += "WHERE (((Def_Categ.IdDefinitions)=14)) ";
	query += "ORDER BY Def_Categ.IdDefinitions, Def_Categ.IdDefCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
bool requete_R_DefCatSerieComp(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT Def_Categ.IdDefCateg, Def_Categ.Nom, Def_Categ.Notes ";
	query += "FROM Def_Categ ";
	query += "WHERE (((Def_Categ.IdDefinitions)=15)) ";
	query += "ORDER BY Def_Categ.IdDefinitions, Def_Categ.IdDefCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}

bool requete_R_DefCatRepart(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT Def_Categ.IdDefCateg, Def_Categ.Nom, Def_Categ.Notes ";
	query += "FROM Def_Categ ";
	query += "WHERE (((Def_Categ.IdDefinitions)=17)) ";
	query += "ORDER BY Def_Categ.IdDefinitions, Def_Categ.IdDefCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}

bool requete_R_DefCatProduit(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT Def_Categ.IdDefCateg, Def_Categ.Nom, Def_Categ.Notes ";
	query +=
			"FROM _Definitions INNER JOIN Def_Categ ON [_Definitions].IdDefinitions = Def_Categ.IdDefinitions ";
	query += "WHERE (((Def_Categ.IdDefinitions)=1)) ";
	query += "ORDER BY Def_Categ.IdDefinitions, Def_Categ.IdDefCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_DefCatRecDiv(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT Def_Categ.IdDefCateg, Def_Categ.Nom, Def_Categ.Notes ";
	query +=
			"FROM _Definitions INNER JOIN Def_Categ ON [_Definitions].IdDefinitions = Def_Categ.IdDefinitions ";
	query += "WHERE (((Def_Categ.IdDefinitions)=7)) ";
	query += "ORDER BY Def_Categ.IdDefinitions, Def_Categ.IdDefCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_DefCatRecFam(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT Def_Categ.IdDefCateg, Def_Categ.Nom, Def_Categ.Notes ";
	query +=
			"FROM _Definitions INNER JOIN Def_Categ ON [_Definitions].IdDefinitions = Def_Categ.IdDefinitions ";
	query += "WHERE (((Def_Categ.IdDefinitions)=9)) ";
	query += "ORDER BY Def_Categ.IdDefinitions, Def_Categ.IdDefCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_DefCatVariable(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT Def_Categ.IdDefCateg, Def_Categ.Nom, Def_Categ.Notes ";
	query +=
			"FROM _Definitions INNER JOIN Def_Categ ON [_Definitions].IdDefinitions = Def_Categ.IdDefinitions ";
	query += "WHERE (((Def_Categ.IdDefinitions)=11)) ";
	query += "ORDER BY Def_Categ.IdDefinitions, Def_Categ.IdDefCateg;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_DefConversion(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Def_Conversion.IdConversion, Def_Conversion.NoBase, Def_Conversion.NoSortie, Def_Conversion.APartirDe, Def_Conversion.Nom, Def_Conversion.EVF1, Def_Conversion.EVF2, Def_Conversion.EVF3, Def_Conversion.EVF4, Def_Conversion.EVF5, Def_Conversion.EVF6, Def_Conversion.EVF8, Def_Conversion.EVF9, Def_Conversion.EVF10, Def_Conversion.FVE1, Def_Conversion.FVE2, Def_Conversion.FVE3, Def_Conversion.FVE4, Def_Conversion.FVE5, Def_Conversion.FVE6, Def_Conversion.FVE7, Def_Conversion.FVE8, Def_Conversion.FVE9, Def_Conversion.FVE10, Def_Conversion.EVF7 ";
	query += "FROM Def_Conversion;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_DefCritere(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Def_Critere.IdDefCateg, Def_Critere.IdDefItem, Def_Critere.Nom ";
	query += "FROM Def_Critere ";
	query += "ORDER BY Def_Critere.IdDefCateg, Def_Critere.IdDefItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
//--TP 2012 - Modification: ajout de la lecture du champ Def_EtatSortie.IdEtatSortie
bool requete_R_DefEtatSortie(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT *";
	query += " FROM Def_EtatSortie;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}

bool requete_R_EtatSortieItemEtat(TADOQuery *adoQuery, int idEtatSortie) {
	adoQuery->SQL->Clear();
	query = "SELECT *";
	query += " FROM EtatSortie";
	query += " WHERE Item = " + IntToStr(idEtatSortie) + ";";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}
bool requete_R_DefSerieComp(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT *";
	query += " FROM Def_SerieComp;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}

bool requete_R_SerieCompItemEtat(TADOQuery *adoQuery, int idSerieComp) {
	adoQuery->SQL->Clear();
	query = "SELECT *";
	query += " FROM SerieComp";
	query += " WHERE Item = " + IntToStr(idSerieComp) + ";";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}
}

//--
bool requete_R_DefIndicat(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Def_Indicateur.IdDefCateg, Def_Indicateur.IdDefItem, Def_Indicateur.Nom, Def_Indicateur.Notes ";
	query += "FROM Def_Indicateur;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_DefItemCharge(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Def_Item.IdDefCateg, Def_Item.IdDefItem, Def_Item.Nom, Def_Item.IdSysUnit, Def_Item.Prix, Def_Item.IdTva ";
	query += "FROM Def_Item ";
	query += "WHERE (((Def_Item.IdDefinitions)=2)) ";
	query +=
			"ORDER BY Def_Item.IdDefCateg, Def_Item.IdDefItem, Def_Item.IdDefinitions;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_DefItemChStruct(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Def_Item.IdDefCateg, Def_Item.IdDefItem, Def_Item.Nom, Def_Item.IdTva ";
	query += "FROM Def_Item ";
	query += "WHERE (((Def_Item.IdDefinitions)=6)) ";
	query +=
			"ORDER BY Def_Item.IdDefinitions, Def_Item.IdDefCateg, Def_Item.IdDefItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_DefItemDepDiv(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Def_Item.IdDefCateg, Def_Item.IdDefItem, Def_Item.Nom, Def_Item.IdTva ";
	query += "FROM Def_Item ";
	query += "WHERE (((Def_Item.IdDefinitions)=8)) ";
	query +=
			"ORDER BY Def_Item.IdDefinitions, Def_Item.IdDefCateg, Def_Item.IdDefItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_DefItemDepFam(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Def_Item.IdDefCateg, Def_Item.IdDefItem, Def_Item.Nom, Def_Item.IdTva ";
	query += "FROM Def_Item ";
	query += "WHERE (((Def_Item.IdDefinitions)=10)) ";
	query +=
			"ORDER BY Def_Item.IdDefinitions, Def_Item.IdDefCateg, Def_Item.IdDefItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_DefItemExternalite(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Def_Item.IdDefCateg, Def_Item.IdDefItem, Def_Item.Nom, Def_Item.IdSysUnit ";
	query += "FROM Def_Item ";
	query += "WHERE (((Def_Item.IdDefinitions)=3)) ";
	query +=
			"ORDER BY Def_Item.IdDefinitions, Def_Item.IdDefCateg, Def_Item.IdDefItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_DefItemProduit(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Def_Item.IdDefCateg, Def_Item.IdDefItem, Def_Item.Nom, Def_Item.IdSysUnit, Def_Item.Prix, Def_Item.IdTva ";
	query += "FROM Def_Item  ";
	query += "WHERE (((Def_Item.IdDefinitions)=1)) ";
	query +=
			"ORDER BY Def_Item.IdDefCateg, Def_Item.IdDefItem, Def_Item.IdDefinitions, Def_Item.IdDefCateg, Def_Item.IdDefItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_DefItemRecDiv(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Def_Item.IdDefCateg, Def_Item.IdDefItem, Def_Item.Nom, Def_Item.IdTva ";
	query += "FROM Def_Item ";
	query += "WHERE (((Def_Item.IdDefinitions)=7)) ";
	query +=
			"ORDER BY Def_Item.IdDefinitions, Def_Item.IdDefCateg, Def_Item.IdDefItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_DefItemRecFam(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Def_Item.IdDefCateg, Def_Item.IdDefItem, Def_Item.Nom, Def_Item.IdTva ";
	query += "FROM Def_Item ";
	query += "WHERE (((Def_Item.IdDefinitions)=9)) ";
	query +=
			"ORDER BY Def_Item.IdDefinitions, Def_Item.IdDefCateg, Def_Item.IdDefItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_DefItemVariable(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query =
			"SELECT Def_Item.IdDefCateg, Def_Item.IdDefItem, Def_Item.Nom, Def_Item.IdSysUnit ";
	query += "FROM Def_Item ";
	query += "WHERE (((Def_Item.IdDefinitions)=11)) ";
	query +=
			"ORDER BY Def_Item.IdDefinitions, Def_Item.IdDefCateg, Def_Item.IdDefItem;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Ens_eff(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Ens_Eff ";
	query += "ORDER BY Ens_Eff.IdEnsemble, Ens_Eff.IdAgriEff;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}
bool requete_R_Ensemble(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT Ensemble.IdEnsemble, Ensemble.Nom, Ensemble.Notes ";
	query += "FROM Ensemble;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_R_Tva(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT TVA.IdTva, TVA.Nom, TVA.Taux, TVA.Defaut, TVA.Immo ";
	query += "FROM TVA;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_Indicateur(TADOQuery *adoQuery) {
	adoQuery->SQL->Clear();
	query = "SELECT *";
	query += "FROM Indicateur;";
	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

bool requete_lireArbre(TADOQuery *adoQuery, int noIndic) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Arbre ";
	query += "WHERE NoIndic = " + IntToStr(noIndic) + " ";
	query += "ORDER BY NoIndic, noBranche";

	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		ShowMessage(e.Message);
		return false;
	}

}

bool requete_lireReseau(TADOQuery *adoQuery, int noIndic) {
	adoQuery->SQL->Clear();
	query = "SELECT * ";
	query += "FROM Reseau ";
	query += "WHERE NoIndic = " + IntToStr(noIndic) + " ";
	query += "ORDER BY NoIndic, NoMaille";

	try {
		adoQuery->SQL->Add(query);
		adoQuery->ExecSQL();
		adoQuery->Active = true;
		adoQuery->Open();
		return true;
	} catch (Exception &e) {
		return false;
	}

}

