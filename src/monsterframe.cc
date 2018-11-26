#include "monsterframe.h"
#include <iostream>

int monsterCounter=0;

void MonsterFrame::addMonster(Glib::ustring name, std::vector<int> stats){
	LineEntry* temp=new LineEntry();
 	std::vector<LineEntry*>* x=&entries;
  (*temp).setParameters(name,1, x, monsterCounter,true);
  (*temp).setN(stats.at(1));
  (*temp).setV(stats.at(2));
  (*temp).setM(stats.at(3));
  (*temp).setInitiative(stats.at(0));
 	monsterCounter++;
 	entries.push_back(temp);
 	nameBox.pack_start(*temp, Gtk::PACK_SHRINK,5);

	show_all_children();
}

void MonsterFrame::buttonClicked(){
	monsterList->show();
	monsterList->show_all_children();
}

void MonsterFrame::scrollChanged(){
  Glib::RefPtr<Gtk::Adjustment> adj = scrolledWindow.get_vadjustment();
  adj->set_value(adj->get_upper());
}

int MonsterFrame::getMonsterNumber(){
  int total=0;
  for(int i=0;i<entries.size();i++)
    total+=entries.at(0)->getInitiativeBox();
  return total;
}

std::vector<LineEntry*>* MonsterFrame::getEntries(){
  return &entries;
}

MonsterFrame::MonsterFrame():box(Gtk::ORIENTATION_VERTICAL), nameBox(Gtk::ORIENTATION_VERTICAL), frameBox(Gtk::ORIENTATION_VERTICAL), addButton("Add monster"), addBox(Gtk::ORIENTATION_HORIZONTAL), headerBox(Gtk::ORIENTATION_HORIZONTAL){

  add(box);
  addButton.signal_clicked().connect(sigc::mem_fun(*this, &MonsterFrame::buttonClicked));  
  
  topLabel1.set_line_wrap();
  topLabel1.set_valign(Gtk::ALIGN_FILL);
  topLabel1.set_halign(Gtk::ALIGN_FILL);
  topLabel2.set_line_wrap();
  topLabel2.set_valign(Gtk::ALIGN_FILL);
  topLabel2.set_halign(Gtk::ALIGN_FILL);
  topLabel1.set_text("Monster name");
  topLabel2.set_text("Quantity");
  headerBox.pack_start(topLabel1,Gtk::PACK_EXPAND_WIDGET,5);
  headerBox.pack_end(topLabel2,Gtk::PACK_SHRINK,5);

  frame.add(frameBox);
  frameBox.pack_start(headerBox, Gtk::PACK_SHRINK);
  frameBox.pack_start(scrolledWindow, Gtk::PACK_EXPAND_WIDGET);
  scrolledWindow.add(nameBox);

  monsterList=new MonsterList();
  monsterList->initialize(this);
  monsterList->set_type_hint(Gdk::WINDOW_TYPE_HINT_UTILITY); 
  monsterList->set_position(Gtk::WIN_POS_MOUSE); 
  monsterList->set_title("Monster List");

  
  scrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
 
  Glib::RefPtr<Gtk::Adjustment> adj = scrolledWindow.get_vadjustment();
  adj->signal_changed().connect(sigc::mem_fun(*this, &MonsterFrame::scrollChanged));

  box.pack_start(frame);
  box.pack_start(addBox, Gtk::PACK_SHRINK);
  addBox.pack_end(addButton, Gtk::PACK_EXPAND_WIDGET);

  addButton.set_tooltip_text("Add a new monster");
}	

MonsterFrame::~MonsterFrame(){
}
