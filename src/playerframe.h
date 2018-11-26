#ifndef playerframe_h
#define playerframe_h

#include <gtkmm.h>
#include "lineentry.h"
#include <vector>


class PlayerFrame : public Gtk::HBox{

  public:
    PlayerFrame();
    virtual ~PlayerFrame();
    void addPlayer(Glib::ustring name, int initiative);
    void buttonClicked();
    std::vector<LineEntry*>* getEntries();
    void scrollChanged();
    void loadPlayers();
    void savePlayers();
  protected:
    Gtk::Frame frame;
    Gtk::Box box;
    Gtk::Label t;
    Gtk::Box nameBox;
    Gtk::ScrolledWindow scrolledWindow;
    std::vector<LineEntry*> entries;
    Gtk::Button addButton;
    Gtk::Entry addPlayerBox;
    Gtk::Box addBox;
    Gtk::Label topLabel1, topLabel2;
    Gtk::Box headerBox;
    Gtk::Box frameBox;
    Gtk::Button savePlayersButton;


};

#endif