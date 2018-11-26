#include "monsterlist.h"
#include "monsterframe.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream> 



void MonsterList::addMonster(Glib::ustring name, std::vector<int> stats){
  int repeat=-1;
  for(int i=0;i<mainFrame->getEntries()->size();i++){
    if(mainFrame->getEntries()->at(i)->getName()==name)
      repeat=i;
  }

 if(repeat>-1)
    mainFrame->getEntries()->at(repeat)->setInitiativeBox(Glib::ustring::format(mainFrame->getEntries()->at(repeat)->getInitiativeBox()+1));
  else
    mainFrame->addMonster(name, stats);
}


std::vector<MonsterEntry*>* MonsterList::getEntries(){
  return &entries;
}

void MonsterList::addToList(MonsterEntry* line){
  std::sort(entries.begin(),entries.end(),[]( MonsterEntry* x, MonsterEntry* y){return x->getMonsterName() < y->getMonsterName();});
  std::vector<Widget*> vec=list.get_children();
  for(int i=0;i<vec.size();i++){
    list.remove(*(vec.at(i)));
  }

  for(int i=0;i<entries.size();i++){
    list.pack_start(*(entries.at(i)), Gtk::PACK_SHRINK);
  }
  on_search();
}


void MonsterList::initialize(MonsterFrame* frame){
  mainFrame=frame;
  std::string tempMonster;
  std::string monsterHp;
  std::string monsterInit;
  std::string monsterName;
  char delim=' ';
  char eof='\n';

  std::ifstream is("monsters.txt");
  int found_d=0;
  int found_plus=0;
  int found_minus=0;
  if(is){
    while(std::getline(is, monsterHp, delim)){
      std::getline(is, monsterInit, delim);
      std::getline(is, monsterName, eof);
      MonsterEntry* t=new MonsterEntry();
      found_d=monsterHp.find("d");
      found_plus=monsterHp.find("+");
      found_minus=monsterHp.find("-");
      try{
        (*t).setParameters(this, monsterName, std::stoi(monsterInit),std::stoi(monsterHp.substr(0,found_d)),found_plus!=std::string::npos?std::stoi(monsterHp.substr(found_d+1, found_plus-found_d)):(found_minus!=std::string::npos?std::stoi(monsterHp.substr(found_d+1,found_minus-found_d)):std::stoi(monsterHp.substr(found_d+1))), found_plus!=std::string::npos?std::stoi(monsterHp.substr(found_plus+1)):(found_minus!=std::string::npos?std::stoi(monsterHp.substr(found_minus+1)):0));
        entries.push_back(t);
      }catch(const std::invalid_argument& ia){
        std::cerr<<"Invalid argument at start :)";
      }
    }
    is.close();

    std::sort(entries.begin(),entries.end(),[]( MonsterEntry* x, MonsterEntry* y){return x->getMonsterName() < y->getMonsterName();});
    for(int i=0;i<entries.size();i++)
      list.pack_start(*(entries.at(i)), Gtk::PACK_SHRINK);
  }
}

void MonsterList::on_search(){
  if(searchBox.get_text()==""){
    list.show_all();
  }
  else{
    for(int i=0;i<entries.size();i++){
      if(entries.at(i)->getMonsterName().find(searchBox.get_text())!= std::string::npos)
        entries.at(i)->show_all();
      
      else
        entries.at(i)->hide();
    }
  }
}

void MonsterList::openMonsterTemplate(){
  monsterTemplate->show();
  monsterTemplate->show_all_children();
}

MonsterList::MonsterList():addMonsterButton("Add new monster"){
  set_default_size(200, 300);
  add(globalBox);
  globalBox.pack_start(searchBox, Gtk::PACK_SHRINK);
  globalBox.pack_start(globalFrame);
  globalBox.pack_start(addMonsterButton, Gtk::PACK_SHRINK);
  addMonsterButton.set_tooltip_text("Add a new monster to the list");
  addMonsterButton.signal_clicked().connect(sigc::mem_fun(*this, &MonsterList::openMonsterTemplate));

  monsterTemplate=new NewMonsterTemplate();
  monsterTemplate->setList(this);


  globalFrame.add(scrolledWindow);
  scrolledWindow.add(list);
  scrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  searchBox.set_max_length(100);

  searchBox.signal_changed().connect(sigc::mem_fun(*this, &MonsterList::on_search));
  show_all_children();
  
}

MonsterList::~MonsterList(){
}	