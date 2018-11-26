

link_directories(
    ${GTKMM_LIBRARY_DIRS}  )

include_directories(
    ${GTKMM_INCLUDE_DIRS}  )

add_executable(Initiative # name of the executable on Windows will be example.exe 
    initiative.cc
	playerframe.cc
	monsterframe.cc
	lineentry.cc
	mainwindow.cc
	newmonstertemplate.cc
	monsterlist.cc
	monsterentry.cc
	monsterlist.h
	monsterentry.h
	newmonstertemplate.h
	lineentry.h
	playerframe.h
	mainwindow.h
	monsterframe.h)

target_link_libraries(Initiative
    ${GTKMM_LIBRARIES}  )