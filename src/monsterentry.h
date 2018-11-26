#ifndef monsterentry_h
#define monsterentry_h


#include <gtkmm.h>
#include <vector>

class MonsterList;
class MonsterEntry : public Gtk::HBox{

public:
  MonsterEntry();
  virtual ~MonsterEntry();
  void setParameters(MonsterList* upper_, Glib::ustring name, int i, int n, int v, int m);
  void on_button_clicked();
  void addButtonClicked();
  std::vector<int> getStats();
  Glib::ustring getMonsterName();
  void removeMonster();
protected:

  Gtk::HBox wrapper;
  Gtk::Label monsterName;
  Gtk::Button addButton;
  Gtk::Image *addImage;
  Gtk::Image *image;
  Gtk::Button deleteButton;
  MonsterList* upper;
  int initiative;
  int n_dice;
  int dice_value;
  int modifier;

};

#endif