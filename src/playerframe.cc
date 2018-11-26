#include "playerframe.h"
#include "lineentry.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream> 
#include <string>
int counter=0;


void PlayerFrame::addPlayer(Glib::ustring name, int initiative){
  LineEntry* temp=new LineEntry();
  std::vector<LineEntry*>* x=&entries;
  (*temp).setParameters(name,initiative, x, counter,false);
  counter++;
  entries.push_back(temp);
  nameBox.pack_start(*temp, Gtk::PACK_SHRINK,5);
  show_all_children();

  /*Glib::RefPtr<Gtk::Adjustment> adj = scrolledWindow.get_vadjustment();
  adj->set_value(adj->get_upper());*/
}

std::vector<LineEntry*>* PlayerFrame::getEntries(){
  return &entries;
}

void PlayerFrame::scrollChanged(){
  Glib::RefPtr<Gtk::Adjustment> adj = scrolledWindow.get_vadjustment();
  adj->set_value(adj->get_upper());
}

void PlayerFrame::buttonClicked(){
  if(addPlayerBox.get_text().size()>0){
    addPlayer(Glib::ustring::format(addPlayerBox.get_text()),0);
    addPlayerBox.set_text("");
  }

}

void PlayerFrame::savePlayers(){
  std::ofstream os("players.txt");
  for(int i=0;i<entries.size();i++){
    os<<entries.at(i)->getName()<<"\n";
  }
  os.close();
}

void PlayerFrame::loadPlayers(){
  std::ifstream is("players.txt");
  std::string player;
  Glib::ustring delim;
  if(is){
    while(std::getline(is, player)){
      addPlayer(player,0);
    }
    is.close();
  }
}

PlayerFrame::PlayerFrame():box(Gtk::ORIENTATION_VERTICAL), frameBox(Gtk::ORIENTATION_VERTICAL),nameBox(Gtk::ORIENTATION_VERTICAL), addButton("Add player"), savePlayersButton("Save"), addBox(Gtk::ORIENTATION_HORIZONTAL), headerBox(Gtk::ORIENTATION_HORIZONTAL){
  add(box);
  addButton.signal_clicked().connect(sigc::mem_fun(*this, &PlayerFrame::buttonClicked)); 
  savePlayersButton.signal_clicked().connect(sigc::mem_fun(*this, &PlayerFrame::savePlayers));
  addPlayerBox.set_max_length(40);


  topLabel1.set_line_wrap();
  topLabel1.set_valign(Gtk::ALIGN_FILL);
  topLabel1.set_halign(Gtk::ALIGN_FILL);
  topLabel2.set_line_wrap();
  topLabel2.set_valign(Gtk::ALIGN_FILL);
  topLabel2.set_halign(Gtk::ALIGN_FILL);
  topLabel1.set_text("Player name");
  topLabel2.set_text("Initiative");
  headerBox.pack_start(topLabel1,Gtk::PACK_EXPAND_WIDGET,5);
  headerBox.pack_end(topLabel2,Gtk::PACK_SHRINK,5);
  
  frame.add(frameBox);
  frameBox.pack_start(headerBox, Gtk::PACK_SHRINK);
  frameBox.pack_start(scrolledWindow, Gtk::PACK_EXPAND_WIDGET);
  scrolledWindow.add(nameBox);

  scrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  Glib::RefPtr<Gtk::Adjustment> adj = scrolledWindow.get_vadjustment();
  adj->signal_changed().connect(sigc::mem_fun(*this, &PlayerFrame::scrollChanged));
  
  loadPlayers();
  
  box.pack_start(frame);
  box.pack_start(addBox, Gtk::PACK_SHRINK);
  addBox.pack_start(addPlayerBox, Gtk::PACK_EXPAND_WIDGET);
  addBox.pack_end(savePlayersButton, Gtk::PACK_SHRINK);
  addBox.pack_end(addButton, Gtk::PACK_SHRINK);

  addButton.set_tooltip_text("Add a new player");
  savePlayersButton.set_tooltip_text("Save this set of players");


}	



PlayerFrame::~PlayerFrame()
{
}

