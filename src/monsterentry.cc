#include "monsterentry.h"
#include "monsterlist.h"
#include <iostream>

void MonsterEntry::setParameters(MonsterList* upper_, Glib::ustring name, int i, int n, int v, int m){
	monsterName.set_text(name);
	initiative=i;
	n_dice=n;
	dice_value=v;
	modifier=m;
	upper=upper_;
}

void MonsterEntry::addButtonClicked(){
	upper->addMonster(monsterName.get_text(), this->getStats());
}

void MonsterEntry::on_button_clicked(){
	std::cout<<monsterName.get_text();
}

Glib::ustring MonsterEntry::getMonsterName(){
	return monsterName.get_text();
}

std::vector<int> MonsterEntry::getStats(){
	std::vector<int> vec;
	vec.push_back(initiative);
	vec.push_back(n_dice);
	vec.push_back(dice_value);
	vec.push_back(modifier);
	return vec;
}

void MonsterEntry::removeMonster(){
	for(int i=0;i<upper->getEntries()->size();i++){
	    if(upper->getEntries()->at(i)->getMonsterName()==monsterName.get_text()){
	      upper->getEntries()->erase(upper->getEntries()->begin()+i);
	      break;
	    }
	}

	std::ifstream fin;
	std::string filename="monsters.txt";
	fin.open(filename);
	std::ofstream temp;
	temp.open("temp.txt");
	char delim=' ';
	std::string monsterHp;
    std::string monsterInit;
    std::string monster;
    char eof='\n';
	while (getline(fin, monsterHp, delim)) {
		std::getline(fin, monsterInit, delim);
      	std::getline(fin, monster, eof);
	    if ( monster!=getMonsterName())
	        temp << monsterHp <<" "<< monsterInit<<" "<<monster<<std::endl;
	}

	temp.close();
	fin.close();

	const char * p = filename.c_str();
	std::remove(p);
	std::rename("temp.txt", p);

	delete this;
}

MonsterEntry::MonsterEntry(){
	add(wrapper);
	monsterName.set_line_wrap();
	monsterName.set_valign(Gtk::ALIGN_FILL);
	monsterName.set_halign(Gtk::ALIGN_START);
	monsterName.set_xalign(0);

  	deleteButton.signal_clicked().connect(sigc::mem_fun(*this, &MonsterEntry::removeMonster)); 
  	deleteButton.set_relief(Gtk::RELIEF_NONE);
	image=Gtk::manage(new Gtk::Image());
  	image->set("icons/cross_icon.png");
  	deleteButton.set_image(*image); 

	addImage=Gtk::manage(new Gtk::Image());
  	addImage->set("icons/plus_icon.png");
  	addButton.set_image(*addImage);
  	addButton.signal_clicked().connect(sigc::mem_fun(*this, &MonsterEntry::addButtonClicked));  
  	addButton.set_relief(Gtk::RELIEF_NONE);

  	wrapper.pack_start(deleteButton, Gtk::PACK_SHRINK);
	wrapper.pack_start(monsterName, Gtk::PACK_SHRINK);
	wrapper.pack_end(addButton, Gtk::PACK_SHRINK);


}

MonsterEntry::~MonsterEntry(){
}