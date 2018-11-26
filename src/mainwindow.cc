#include "mainwindow.h"

#include <iostream>
#include <string>
#include <stdlib.h> 
#include <time.h>
#include <algorithm>
#include <iomanip>


struct higher_initiative{
    bool operator()(const character_block& x, const character_block& y) const
    {
        return x.initiative.at(0) > y.initiative.at(0); 
    }
};


std::vector<character_block>* MainWindow::rollInitiative(){
  try{
    int size=monsters.getMonsterNumber()+players.getEntries()->size();
  }catch(const std::invalid_argument& ia){
    std::cerr<<"Invalid number";
    return NULL;
  }
  std::vector<character_block>* all_characters=new std::vector<character_block>();

  Glib::RefPtr<Gtk::TextBuffer> tempBuffer=Gtk::TextBuffer::create();
  Gtk::TextIter iter;
  Glib::RefPtr<Gtk::TextBuffer::Mark> mark;

  
  for(int i=0;i<monsters.getEntries()->size();i++){
    try{
      for(int k=0;k<monsters.getEntries()->at(i)->getInitiativeBox();k++){
        
          character_block temp;
          std::vector<int> hpStats=monsters.getEntries()->at(i)->getStats();
          temp.name=monsters.getEntries()->at(i)->getInitiativeBox()>1?monsters.getEntries()->at(i)->getName().append("_").append(Glib::ustring::format(k+1)):monsters.getEntries()->at(i)->getName();
          temp.hp=MainWindow::rollDice(hpStats.at(1),hpStats.at(2),hpStats.at(3));
          temp.initiative.push_back(MainWindow::rollDice(1,20,hpStats.at(0)));
          all_characters->push_back(temp);
      }
    }catch(const std::invalid_argument& ia){
      std::cerr<<"Invalid number";
      return NULL;
    }
  }

  for(int i=0;i<players.getEntries()->size();i++){
    try{
      character_block temp;
      temp.name=players.getEntries()->at(i)->getName();
      temp.hp=-100;
      temp.initiative.push_back(players.getEntries()->at(i)->getInitiativeBox());
      all_characters->push_back(temp);
    }catch(const std::invalid_argument& ia){
      std::cerr<<"Invalid number";
      return NULL;
    }
  }

  std::random_shuffle(all_characters->begin(),all_characters->end());
  std::sort(all_characters->begin(),all_characters->end(),higher_initiative());
  for (std::vector<character_block>::iterator it=all_characters->begin(); it!=all_characters->end(); ++it){
    mark=tempBuffer->get_insert();
    iter=tempBuffer->get_iter_at_mark (mark);
    tempBuffer->insert(iter, "["+(Glib::ustring::format(it->initiative.at(0))).append("] ").append(it->name).append(it->hp==-100?"":" "+(Glib::ustring::format(it->hp))).append("\n"));
  }

  textView.set_buffer(tempBuffer);
  return all_characters;
}

int MainWindow::rollDice(int n, int d, int mod){
  int total=0;
  for(int i=0;i<n;i++){
    total+=rand()%d+1;
  }
  return total+mod;
}

void MainWindow::saveFight(std::vector<character_block>* block){
  if(block==NULL)
    return;
  std::ofstream os;
  os.open("logs.txt", std::ios_base::app);
  for (std::vector<character_block>::iterator it=block->begin(); it!=block->end(); ++it)
    os<<"["+(Glib::ustring::format(it->initiative.at(0))).append("] ").append(it->name).append(it->hp==-100?"":" "+(Glib::ustring::format(it->hp))).append("\n");
  os<<"\n";
  os.close();

}

void MainWindow::runFight(){
  saveFight(rollInitiative());
}

MainWindow::MainWindow():mainWindow(Gtk::ORIENTATION_VERTICAL), upperBox(Gtk::ORIENTATION_HORIZONTAL), runBox(Gtk::ORIENTATION_HORIZONTAL), runButton("Run"), lowerBox(Gtk::ORIENTATION_HORIZONTAL){
	set_title("Initiative");
  srand (time(NULL));
	set_default_size(600, 500);
	add(mainWindow);
  p.set_text("<span size='17000'>Players</span>");
  p.set_use_markup(true);
  playerTitle.pack_start(p);

  runButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::runFight));  

  m.set_text("<span size='17000'>Monsters</span>");
  m.set_use_markup(true);
  monsterTitle.pack_start(m);
  titleBox.pack_start(playerTitle);
  titleBox.pack_start(monsterTitle);
  mainWindow.pack_start(titleBox, Gtk::PACK_SHRINK);
  scrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
  scrolledWindow.add(textView);
  upperBox.set_homogeneous(true);
  upperBox.pack_start(players);
  upperBox.pack_start(monsters);
  lowerBox.pack_start(scrolledWindow);

  runBox.pack_end(runButton, Gtk::PACK_SHRINK);
	mainWindow.pack_start(upperBox);
  lowerBox.pack_end(runBox, Gtk::PACK_SHRINK);
	mainWindow.pack_start(lowerBox);

	show_all_children();

}

MainWindow::~MainWindow()
{
}
