#ifndef monsterlist_h
#define monsterlist_h


#include <gtkmm.h>
#include <vector>
#include "monsterentry.h"
#include <fstream>
#include "newmonstertemplate.h"

class MonsterFrame;
class MonsterList : public Gtk::Window{

public:
  MonsterList();
  virtual ~MonsterList();
  void initialize(MonsterFrame* frame);
  void addMonster(Glib::ustring name, std::vector<int> stats);
  void on_search();
  void openMonsterTemplate();
  std::vector<MonsterEntry*>* getEntries();
  void addToList(MonsterEntry* line);
protected:

  Gtk::VBox globalBox;
  Gtk::Frame globalFrame;
  Gtk::VBox monsterBox;
  std::vector<MonsterEntry*> entries;
  Gtk::ScrolledWindow scrolledWindow;
  Gtk::VBox list;
  MonsterFrame* mainFrame;
  Gtk::Entry searchBox;
  std::FILE* monsterFileReader;
  Gtk::Button addMonsterButton;
  NewMonsterTemplate* monsterTemplate;
};

#endif