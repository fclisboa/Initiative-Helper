#include "lineentry.h"
#include <iostream>
#include <string>



LineEntry::LineEntry(){

	add(entryBox);
  nameLabel.set_line_wrap();

  image=Gtk::manage(new Gtk::Image());
  image->set("icons/cross_icon.png");

  deleteButton.signal_clicked().connect(sigc::mem_fun(*this, &LineEntry::on_button_clicked));  
  deleteButton.set_tooltip_text("Remove player");
  entryBox.pack_start(deleteButton, Gtk::PACK_SHRINK,5);
  entryBox.pack_start(nameLabel, Gtk::PACK_SHRINK,3);

}	

void LineEntry::setInitiativeBox(Glib::ustring i){
  initiativeBox.set_text(i);
}

bool LineEntry::hasCharacters(Glib::ustring s){
  bool first=true;
  for(char& c:std::string(s)){
    try{
      std::string t(1,c);
      if(!(first && (t.compare("+")==0 || t.compare("-")==0) && std::string(s).length()>1))
        std::stoi(t);
      first=false;
    }catch(const std::invalid_argument& ia){
      return true;
    }
  }
  return false;
}

int LineEntry::getInitiativeBox(){
  return std::stoi(hasCharacters(initiativeBox.get_text())?"a":initiativeBox.get_text());
}

Glib::ustring LineEntry::getName(){
  return Glib::ustring::format(nameLabel.get_text());
}

void LineEntry::on_button_clicked(){
  for(int i=0;i<entriesPtr->size();i++){
    if(entriesPtr->at(i)->id==id){
      entriesPtr->erase(entriesPtr->begin()+i);
      break;
    }
  }
  
  delete this;

}


std::vector<int> LineEntry::getStats(){
  std::vector<int> vec;
  vec.push_back(initiative);
  vec.push_back(n);
  vec.push_back(v);
  vec.push_back(m);
  return vec;
}

void LineEntry::setN(int n_){
  n=n_;
}

void LineEntry::setV(int v_){
  v=v_;
}

void LineEntry::setM(int m_){
  m=m_;
}

void LineEntry::setInitiative(int i_){
  initiative=i_;
}

void LineEntry::setParameters(Glib::ustring name, int initiative, std::vector<LineEntry*>* e, int counter, bool isMonster){

    initiativeBox.set_max_length(3);
    initiativeBox.set_width_chars(2);
    initiativeBox.set_max_width_chars(2);
    initiativeBox.set_text(Glib::ustring::format(initiative));
    entryBox.pack_end(initiativeBox, Gtk::PACK_SHRINK,15);
    monster=isMonster;
    nameLabel.set_text(name);
    entriesPtr=e;
    id=counter;
    deleteButton.set_image(*image);
}

LineEntry::~LineEntry(){
  delete image;
}
