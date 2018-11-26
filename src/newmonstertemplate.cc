#include "monsterlist.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream> 


void NewMonsterTemplate::setList(MonsterList* l){
  list=l;
}

bool NewMonsterTemplate::hasCharacters(Glib::ustring s){
  bool first=true;
  for(char& c:std::string(s)){
    try{
      std::string t(1,c);
      if(!(first && (t.compare(std::string("+"))==0 || t.compare(std::string("-"))==0) && std::string(s).length()>1))
        std::stoi(t);
      first=false;
    }catch(const std::invalid_argument& ia){
      return true;
    }
  }
  return false;
}

void NewMonsterTemplate::addMonster(){
  MonsterEntry* t=new MonsterEntry();
  Glib::ustring mName=Glib::ustring::format(monsterNameEntry.get_text());
  int m;
  int init;
  int n;
  int v;
  if(mName=="")
    return;

  for(int i=0;i<list->getEntries()->size();i++){
    if(list->getEntries()->at(i)->getMonsterName()==mName)
      return;
  }
  try{
    if(initiativeEntry.get_text()=="")
      return;
    init=std::stoi(hasCharacters(initiativeEntry.get_text())?"a":initiativeEntry.get_text());
    if(nHpEntry.get_text()=="" || std::stoi(hasCharacters(nHpEntry.get_text())?"a":nHpEntry.get_text())<0)
      return;
    n=std::stoi(nHpEntry.get_text());
    if(diceHpEntry.get_text()=="" || std::stoi(hasCharacters(diceHpEntry.get_text())?"a":diceHpEntry.get_text())<0)
      return;
    v=std::stoi(diceHpEntry.get_text());
    if(modHpEntry.get_text()=="")
      m=0;
    else
      m=std::stoi(hasCharacters(modHpEntry.get_text())?"a":modHpEntry.get_text());
  }
  catch(const std::invalid_argument& ia){
    std::cerr<<"Invalid argument :)";
    return;
  }
  t->setParameters(list, mName, init, n, v, m);
  list->getEntries()->push_back(t);
  list->addToList(t);

  std::ofstream os;
  os.open("monsters.txt", std::ios_base::app);

  os<<Glib::ustring::format(n)+"d"+Glib::ustring::format(v)+(m>0?("+"+Glib::ustring::format(m)):(m<0?Glib::ustring::format(m):""))+" "+Glib::ustring::format(init)+" "+mName+"\n";
  
  os.close();
  this->close();
}

void NewMonsterTemplate::cancel(){
  this->close();
}

NewMonsterTemplate::NewMonsterTemplate():addButton("Add"), cancelButton("Cancel"){
  set_default_size(300, 200);
  add(templateBox);

  addButton.signal_clicked().connect(sigc::mem_fun(*this, &NewMonsterTemplate::addMonster));
  cancelButton.signal_clicked().connect(sigc::mem_fun(*this, &NewMonsterTemplate::cancel));

  monsterNameLabel.set_text("Monster name ");
  monsterNameEntry.set_max_length(40);
  nameBox.pack_start(monsterNameLabel, Gtk::PACK_SHRINK,5);
  nameBox.pack_start(monsterNameEntry);
  templateBox.pack_start(nameBox, Gtk::PACK_SHRINK, 10);

  monsterHpLabel.set_text("Monster HP ");
  nHpEntry.set_max_length(5);
  nHpEntry.set_width_chars(2);
  nHpEntry.set_placeholder_text("10");
  diceHpLabel.set_text("d");
  diceHpEntry.set_max_length(5);
  diceHpEntry.set_width_chars(2);
  diceHpEntry.set_placeholder_text("12");
  modHpLabel.set_text("+");
  modHpEntry.set_max_length(5);
  modHpEntry.set_width_chars(2);
  modHpEntry.set_placeholder_text("15");

  hpBox.pack_start(monsterHpLabel, Gtk::PACK_SHRINK,5);
  hpBox.pack_start(nHpEntry, Gtk::PACK_SHRINK,1);
  hpBox.pack_start(diceHpLabel, Gtk::PACK_SHRINK,1);
  hpBox.pack_start(diceHpEntry, Gtk::PACK_SHRINK,1);
  hpBox.pack_start(modHpLabel, Gtk::PACK_SHRINK,1);
  hpBox.pack_start(modHpEntry, Gtk::PACK_SHRINK,1);
  templateBox.pack_start(hpBox, Gtk::PACK_SHRINK, 3);

  initiativeLabel.set_text("Initiative ");
  initiativeEntry.set_max_length(5);
  initiativeEntry.set_width_chars(2);
  initiativeEntry.set_placeholder_text("2");
  initiativeBox.pack_start(initiativeLabel, Gtk::PACK_SHRINK,5);
  initiativeBox.pack_start(initiativeEntry, Gtk::PACK_SHRINK,1);
  templateBox.pack_start(initiativeBox, Gtk::PACK_SHRINK,3);

  buttonBox.set_homogeneous(true);
  buttonBox.pack_start(addButton);
  buttonBox.pack_start(cancelButton);
  templateBox.pack_end(buttonBox, Gtk::PACK_SHRINK);
  
}

NewMonsterTemplate::~NewMonsterTemplate(){
}	