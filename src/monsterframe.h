#ifndef monsterframe_h
#define monsterframe_h

#include <gtkmm.h>
#include "lineentry.h"
#include "monsterlist.h"
#include <vector>
#include <iostream>
#include <fstream>

class MonsterFrame : public Gtk::HBox{

  public:
    MonsterFrame();
    virtual ~MonsterFrame();
    void addMonster(Glib::ustring name, std::vector<int> stats);
    void buttonClicked();
    std::vector<LineEntry*>* getEntries();
    int getMonsterNumber();
    void scrollChanged();
  protected:
    Gtk::Frame frame;
    Gtk::Box box;
    Gtk::Label t;
    Gtk::Box nameBox;
    Gtk::ScrolledWindow scrolledWindow;
    std::vector<LineEntry*> entries;
    Gtk::Button addButton;
    Gtk::Entry addMonsterBox;
    Gtk::Box addBox;
    Gtk::Label topLabel1, topLabel2;
    Gtk::Box headerBox;
    MonsterList* monsterList;
    Gtk::Box frameBox;
};

#endif