#ifndef mainwindow_h
#define mainwindow_h


#include <gtkmm.h>
#include "playerframe.h"
#include "monsterframe.h"

typedef struct {
  Glib::ustring name;
  int hp;
  std::vector<int> initiative;   
}character_block;

class MainWindow : public Gtk::Window{

public:
  MainWindow();
  virtual ~MainWindow();
  int rollDice(int n, int d, int mod);
  void runFight();
  std::vector<character_block>* rollInitiative();
  void saveFight(std::vector<character_block>* block);

protected:
  PlayerFrame players;
  MonsterFrame monsters;
  Gtk::Box playerTitle;
  Gtk::Box titleBox;
  Gtk::Label p;
  Gtk::Label m;
  Gtk::Box monsterTitle;
  Gtk::Box mainWindow;
  Gtk::Box upperBox;
  Gtk::ScrolledWindow scrolledWindow;
  Gtk::TextView textView;
  Gtk::Button runButton;
  Gtk::Box runBox;
  Gtk::Box lowerBox;

};

#endif