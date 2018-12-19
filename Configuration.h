//---------------------------------------------------------------------------
#ifndef ConfigurationH
#define ConfigurationH
#include <string>
using namespace std;
/** La classe Configuration fournit l'ensemble des champs
 - disponibles dans le fichier olympe.conf
 - connus par une version donnée d'Olympe

 !!! ATTENTION !!!
 Il est fortement recommandé de n'utiliser qu'un objet Configuration
 à la fois. Des effets de bord désagréables pourraient survenir
 en cas de multiples instances écrivant dans le fichier olympe.conf
 étant donnée que la classe n'a pas de mécanisme de verrouillage d'accès.

 TODO : implémenter un verrouillage d'accès.

 Note pour l'implémenteur de nouvelles options :
 pour chaque nouveau champ, un traitement doit être ajouté à la méthode
 privée 'dispatch' et une nouvelle ligne dans le formulaire ConfigurationFrm
 */
class Configuration {
	/** Nom du fichier de configuration */
	string conf_file_;
	/** Chemin des données .oly */
	string data_path_;
	/** Chemin de l'exécutable Olympe.exe */
	string exec_path_;
	/** Lecture du fichier de configuration */
	void read_conf();
	/** Distribution du contenu d'une ligne du fichier */
	void dispatch(const string &);
public:
	/** Constructeur avec emplacement du fichier de configuration */
	Configuration(const string & s);
	/** Routine pour forcer l'écriture du fichier */
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

