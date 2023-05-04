set(QAPPLICATION_CLASS QApplication)
add_subdirectory(./SingleApplication)

add_executable(helloworld
	main.cpp
	resources.qrc
	launcher.cpp
	TrayIcon.cpp
	Embedder.cpp
	MainWindow.cpp
	DbusKwin.cpp
)


find_package(KF5IconThemes)
find_package(Qt5 COMPONENTS Core Gui Quick QuickWidgets WaylandCompositor REQUIRED)
find_package(KF5 REQUIRED COMPONENTS WindowSystem)


target_link_libraries(helloworld
	Qt5::Quick
	Qt5::Qml
	Qt5::Gui
	Qt5::QuickControls2
	Qt5::Widgets
	Qt5::QuickWidgets
	Qt5::WaylandCompositor
	KF5::Kirigami2
	KF5::I18n
	KF5::IconThemes
	SingleApplication::SingleApplication
	KF5::WindowSystem
) 
