#ifndef line_entry_h
#define line_entry_h

#include <gtkmm.h>
#include <vector>

class LineEntry : public Gtk::HBox{

  public:
    LineEntry();
    void setParameters(Glib::ustring name, int initiative,std::vector<LineEntry*>* e, int counter, bool isMonster);
    void on_button_clicked();
    Glib::ustring getName();
    int getInitiativeBox();
    void setInitiativeBox(Glib::ustring i);
    void setV(int v_);
    void setInitiative(int i_);
    void setN(int n_);
    void setM(int m_);
    std::vector<int> getStats();
    bool hasCharacters(Glib::ustring s);
    virtual ~LineEntry();
  protected:
    Gtk::Label nameLabel;
    Gtk::Button deleteButton;
    Gtk::Entry initiativeBox;
    Gtk::HBox entryBox;
    Gtk::Image *image;
    std::vector<LineEntry*>* entriesPtr;
    Gtk::Button inspectButton;
    int n;
    int v;
    int m;
    bool monster;
    int initiative;
    int id;

};

#endif