#ifndef newmonstertemplate_h
#define newmonstertemplate_h


#include <gtkmm.h>
#include <vector>
#include <fstream>
#include "monsterentry.h"

class MonsterList;
class NewMonsterTemplate : public Gtk::Window{

public:
  NewMonsterTemplate();
  virtual ~NewMonsterTemplate();
  void addMonster();
  void cancel();
  void setList(MonsterList* l);
  bool hasCharacters(Glib::ustring s);
protected:

  Gtk::VBox templateBox;
  Gtk::Label monsterNameLabel;
  Gtk::Label monsterHpLabel;
  Gtk::Label diceHpLabel;
  Gtk::Label initiativeLabel;
  Gtk::Label modHpLabel;
  Gtk::Button addButton;
  Gtk::Button cancelButton;
  Gtk::Entry monsterNameEntry;
  Gtk::Entry nHpEntry;
  Gtk::Entry diceHpEntry;
  Gtk::Entry modHpEntry;
  Gtk::Entry initiativeEntry;
  Gtk::HBox nameBox;
  Gtk::HBox hpBox;
  Gtk::HBox initiativeBox;
  Gtk::HBox buttonBox;
  MonsterList* list;
  
};

#endif