#include "Configuration.h"
#include "ConfigurationFrm.h"
#include <fstream>
#include <FileCtrl.hpp>
//--------Configuration-------------------------

Configuration::Configuration(const string & s) {
	set_conf_file(s + "\\olympe.conf");
	read_conf();
}

void Configuration::gui_input() {
	TConfigFrm * Config;
	Config = new TConfigFrm();
	Config->data_path_edit->Text = data_path().c_str();
	Config->exec_path_edit->Text = exec_path().c_str();
	Config->ShowModal();
	if (Config->ok) {
		set_data_path(Config->data_path_edit->Text.c_str());
		set_exec_path(Config->exec_path_edit->Text.c_str());
		write_conf();
	}
	delete Config;
}

bool Configuration::set_conf_file(const string & s) {
	/**Le fichier de configuration doit exister !!!*/
	if (FileExists(s.c_str())) {
		conf_file_ = s;
		return true;
	}
	return false;
}

bool Configuration::set_data_path(const string & s) {
	if (DirectoryExists(s.c_str())) {
		data_path_ = s;
		return true;
	}
	return false;
}

bool Configuration::set_exec_path(const string & s) {
	if (DirectoryExists(s.c_str())) {
		exec_path_ = s;
		return true;
	}
	return false;
}

void Configuration::read_conf() {
	/** Déclaration et ouverture du fichier */
	std::ifstream fic(conf_file_.c_str());
	if (!fic.is_open())
		/** TODO : Ici, on devrait lever une exception */
		return;

	/** Lecture du contenu -> dans une chaine pour chaque ligne */
	string el_tmp;
	char c;
	bool endline = false;

	while (fic.get(c)) {
		if (c != 10 && c != 13) /** On n'est pas en fin de ligne */
		{
			endline = false;
			el_tmp += c;
		} else {
			/** On vide el_tmp au premier marqueur de fin de ligne venu
			 et on le 'dispatche' dans la bonne variable */
			if (!endline) {
				dispatch(el_tmp);
				el_tmp = "";
			}
			endline = true;
		}
	}
	/** Le petit canaillou qui nous aurait fait un fichier de conf sans
	 crlf final nous oblige à cette vérification...*/
	if (el_tmp.size() > 0)
		dispatch(el_tmp);
	fic.close();
}

void Configuration::write_conf() {
	string out;
	string crlf;

	/** Carriage Right + Line Feed
	 est le séparateur de ligne - conventions MSDOS
	 Nous voulons la convention UNIX */
	crlf += char(10);
	//crlf += char (13);

	out += "<data_path:\"";
	out += data_path();
	out += "\">";
	out += crlf;

	out += "<exec_path:\"";
	out += exec_path();
	out += "\">";
	out += crlf;

	std::ofstream fic(conf_file_.c_str());

	for (unsigned int i = 0; i < out.size(); ++i)
		fic.put(out[i]);

	fic.close();
}

void Configuration::dispatch(const string & s) {
	/** Note : à blinder contre les fichiers corrompus
	 ou mal formés.*/
	string accu_nom, accu_var;
	unsigned int iter;

	/** Recherche du marqueur < */
	for (iter = 0; s[iter] != '<' && iter < s.size(); ++iter)
		;

	/** Accumulation du nom de variable */
	while (s[++iter] != ':' && iter < s.size())
		accu_nom += s[iter];

	/** Recherche du " de début de chaine */
	while (s[iter] != '"' && iter < s.size())
		iter++;

	/** Accumulation du contenu de la variable */
	while (s[++iter] != '"' && iter < s.size())
		accu_var += s[iter];

	/** On se fiche du > fermant pour l'instant
	 TODO : lever une exception en cas d'absence */
	/** Distribution dans une variable le cas échéant - pas de switch */
	if (accu_nom == "data_path")
		set_data_path(accu_var);
	if (accu_nom == "exec_path")
		set_exec_path(accu_var);
}

