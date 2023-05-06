set(QAPPLICATION_CLASS QApplication)
add_subdirectory(./SingleApplication)

add_executable(ktoggle
	main.cpp
	resources.qrc
	TrayIcon.cpp
	KwinController.cpp
	DbusKwin.cpp
)


find_package(KF5IconThemes)
find_package(Qt5 COMPONENTS Core Gui REQUIRED)
find_package(KF5 REQUIRED COMPONENTS WindowSystem)


target_link_libraries(ktoggle
	Qt5::Gui
	Qt5::Widgets
	KF5::Kirigami2
	KF5::I18n
	KF5::IconThemes
	SingleApplication::SingleApplication
	KF5::WindowSystem
) 
