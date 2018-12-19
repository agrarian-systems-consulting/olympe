//---------------------------------------------------------------------------

#ifndef RequeteH
#define RequeteH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ADODB.hpp>
#include <ComCtrls.hpp>

bool requete_R_SystemeUnite(TADOQuery *adoQuery);
bool requete_R_Agri(TADOQuery *adoQuery);
bool requete_R_Agri_Animaux(TADOQuery *adoQuery);
bool requete_R_Agri_Assol(TADOQuery *adoQuery);
bool requete_R_Agri_EnCoursCreance(TADOQuery *adoQuery);
bool requete_R_Agri_Critere(TADOQuery *adoQuery);
bool requete_R_Agri_DefSim(TADOQuery *adoQuery);
bool requete_R_Agri_EnCoursDette(TADOQuery *adoQuery);
bool requete_R_Agri_EmpCT(TADOQuery *adoQuery);
bool requete_R_Agri_EmpLT(TADOQuery *adoQuery);
bool requete_R_Agri_FinanceGlobal(TADOQuery *adoQuery);
bool requete_R_Agri_FormuleCharge(TADOQuery *adoQuery);
bool requete_R_Agri_FormuleChStruct(TADOQuery *adoQuery);
bool requete_R_Agri_FormuleDepDiv(TADOQuery *adoQuery);
bool requete_R_Agri_FormuleDepFam(TADOQuery *adoQuery);
bool requete_R_Agri_FormuleExtNeg(TADOQuery *adoQuery);
bool requete_R_Agri_FormuleExtPos(TADOQuery *adoQuery);
bool requete_R_Agri_FormuleProduit(TADOQuery *adoQuery);
bool requete_R_Agri_FormuleRecFam(TADOQuery *adoQuery);
bool requete_R_Agri_FormuleRecDiv(TADOQuery *adoQuery);
bool requete_R_Agri_FormuleStockIni(TADOQuery *adoQuery);
bool requete_R_Agri_Immo(TADOQuery *adoQuery);
bool requete_R_Agri_LstSer(TADOQuery *adoQuery);
bool requete_R_Agri_ImmoGlobal(TADOQuery *adoQuery);
bool requete_R_Agri_LstVar(TADOQuery *adoQuery);
bool requete_R_Agri_Occc(TADOQuery *adoQuery);
bool requete_R_Agri_Perenne(TADOQuery *adoQuery);
bool requete_R_Agri_Petit(TADOQuery *adoQuery);
bool requete_R_Agri_Plact(TADOQuery *adoQuery);
bool requete_R_Agri_Polstock(TADOQuery *adoQuery);
bool requete_R_Agri_StockIni(TADOQuery *adoQuery);
bool requete_R_Agri_Sub(TADOQuery *adoQuery);
bool requete_R_Agri_Variable(TADOQuery *adoQuery);
bool requete_R_Agri_Vivrier(TADOQuery *adoQuery);
bool requete_R_Alea_Categ(TADOQuery *adoQuery);
bool requete_R_Alea_Item(TADOQuery *adoQuery);
bool requete_R_AteAnimaux(TADOQuery *adoQuery);
bool requete_R_AteCatAnimaux(TADOQuery *adoQuery);
bool requete_R_AteCatCulture(TADOQuery *adoQuery);
bool requete_R_AteCatPerenne(TADOQuery *adoQuery);
bool requete_R_AteCatVivrier(TADOQuery *adoQuery);
bool requete_R_AteCulture(TADOQuery *adoQuery);
bool requete_R_AteItemAnimaux(TADOQuery *adoQuery);
bool requete_R_AteItemCulture(TADOQuery *adoQuery);
bool requete_R_AteItemPerenne(TADOQuery *adoQuery);
bool requete_R_AteItemVivrier(TADOQuery *adoQuery);
bool requete_R_AtePerenne(TADOQuery *adoQuery);
bool requete_R_AteVivrier(TADOQuery *adoQuery);
bool requete_R_DefBestiaux(TADOQuery *adoQuery);
bool requete_R_DefCalendrier(TADOQuery *adoQuery);
bool requete_R_DefCatBestiaux(TADOQuery *adoQuery);
bool requete_R_DefCatCalendrier(TADOQuery *adoQuery);
bool requete_R_DefCatCharge(TADOQuery *adoQuery);
bool requete_R_DefCatChStruct(TADOQuery *adoQuery);
bool requete_R_DefCatClassif(TADOQuery *adoQuery);
bool requete_R_DefCatDepDiv(TADOQuery *adoQuery);
bool requete_R_DefCatDepFam(TADOQuery *adoQuery);
bool requete_R_DefCatExternalite(TADOQuery *adoQuery);
bool requete_R_DefCatIndic(TADOQuery *adoQuery);
bool requete_R_DefCatProduit(TADOQuery *adoQuery);
bool requete_R_DefCatRecDiv(TADOQuery *adoQuery);
bool requete_R_DefCatRecFam(TADOQuery *adoQuery);
bool requete_R_DefCatVariable(TADOQuery *adoQuery);
bool requete_R_DefConversion(TADOQuery *adoQuery);
bool requete_R_DefCritere(TADOQuery *adoQuery);
bool requete_R_DefEtatSortie(TADOQuery *adoQuery);
bool requete_R_DefIndicat(TADOQuery *adoQuery);
bool requete_R_DefItemCharge(TADOQuery *adoQuery);
bool requete_R_DefItemChStruct(TADOQuery *adoQuery);
bool requete_R_DefItemDepDiv(TADOQuery *adoQuery);
bool requete_R_DefItemDepFam(TADOQuery *adoQuery);
bool requete_R_DefItemExternalite(TADOQuery *adoQuery);
bool requete_R_DefItemProduit(TADOQuery *adoQuery);
bool requete_R_DefItemRecDiv(TADOQuery *adoQuery);
bool requete_R_DefItemRecFam(TADOQuery *adoQuery);
bool requete_R_DefItemVariable(TADOQuery *adoQuery);
bool requete_R_Ens_eff(TADOQuery *adoQuery);
bool requete_R_Ensemble(TADOQuery *adoQuery);
bool requete_R_Tva(TADOQuery *adoQuery);
//---------------------------------------------------------------------------
#endif
