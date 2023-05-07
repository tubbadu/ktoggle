# KToggle

> NOTE: it's a work in progress!

> NOTE 2: I just found out about [KWayland API](https://api.kde.org/frameworks/kwayland/html/classKWayland_1_1Server_1_1PlasmaWindowInterface.html), I'm a bit idiot I think, I'll rewrite this using this library and KX11Extras I think

KToggle is a tool to quickly toggle the visibility of your favourite windows with a single keystroke! It instantly raises the window and give it keyboard focus, or minimize it if it's already the active window!

![ktoggle in action](img/ktoggle.gif)

## usage:

```bash
ktoggle --class org.telegram.desktop --name telegram-desktop --program telegram-desktop
```

required flags:
- `--class <class>`			Window class to toggle.
- `--name <name>`			Window name to toggle. Substrings are also accepted.
- `--program <program>`		Command to run program. If it contains spaces, make sure to use quotes.

optional flags: 
- `--icon myIcon` 			Add a system tray icon with the specified name or path.
- `--xy <x,y>`				Forces window position to x and y coordinates. (Not supported yet)
- `--size <height,width>`	Forces size of the window. (Not supported yet)
- `--standalone`			Does not get minimized when other windows are toggled and does not minimize other windows when toggled.
- `--minimize-all`			Minimize all windows that were not set as standalone.
- `--test`					Get a list of all active windows names and classes. Use this to check the correct class and name for your application.

## build:

```bash
git clone https://github.com/tubbadu/ktoggle
cd ktoggle

cmake -B build/ .
cmake --build build/

./build/bin/ktoggle --help

# install:
cd build
sudo make install
```

## TODO:
* [ ] better readme
* [ ] size/position feature
* [ ] at every call, check if the saved processes in wList are still alive, and if not remove from the list (low importance)
* [ ] tray's action "close this window" should actually kill that process (only closing the window may not work)
* [ ] optional: move to current desktop before showing up (using `--to-desktop` flag)
* [ ] remake using https://api.kde.org/frameworks/kwayland/html/classKWayland_1_1Server_1_1PlasmaWindowInterface.html