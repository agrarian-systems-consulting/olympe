//---------------------------------------------------------------------------
#ifndef ConfigurationH
#define ConfigurationH
#include <string>
using namespace std;
/** La classe Configuration fournit l'ensemble des champs
 - disponibles dans le fichier olympe.conf
 - connus par une version donn�e d'Olympe

 !!! ATTENTION !!!
 Il est fortement recommand� de n'utiliser qu'un objet Configuration
 � la fois. Des effets de bord d�sagr�ables pourraient survenir
 en cas de multiples instances �crivant dans le fichier olympe.conf
 �tant donn�e que la classe n'a pas de m�canisme de verrouillage d'acc�s.

 TODO : impl�menter un verrouillage d'acc�s.

 Note pour l'impl�menteur de nouvelles options :
 pour chaque nouveau champ, un traitement doit �tre ajout� � la m�thode
 priv�e 'dispatch' et une nouvelle ligne dans le formulaire ConfigurationFrm
 */
class Configuration {
	/** Nom du fichier de configuration */
	string conf_file_;
	/** Chemin des donn�es .oly */
	string data_path_;
	/** Chemin de l'ex�cutable Olympe.exe */
	string exec_path_;
	/** Lecture du fichier de configuration */
	void read_conf();
	/** Distribution du contenu d'une ligne du fichier */
	void dispatch(const string &);
public:
	/** Constructeur avec emplacement du fichier de configuration */
	Configuration(const string & s);
	/** Routine pour forcer l'�criture du fichier */
	void write_conf();
	/**@name Acesseurs
	 @{*/
	string conf_file() const {
		return conf_file_;
	}
	string data_path() const {
		return data_path_;
	}
	string exec_path() const {
		return exec_path_;
	}
	/*@}*/
	/**@name Modificateurs
	 @{*/
	bool set_conf_file(const string &);
	bool set_data_path(const string &);
	bool set_exec_path(const string &);
	/*@}*/
	/** Appel au formulaire */
	void gui_input();
};
/** Bug !! pourquoi cette initialisation est-elle impossible ? */
//Configuration::instance_ = 0;
#endif

