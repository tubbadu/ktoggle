# KToggle


## NOTE: I moved this repo on codeberg: https://codeberg.org/tubbadu/ktoggle

> NOTE: it's a work in progress!

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
- `--xy <x,y>`				Forces window position to x and y coordinates.
- `--size <height,width>`	Forces size of the window.
- `--standalone`			Does not get minimized when other windows are toggled and does not minimize other windows when toggled.
- `--force-geometry`		Forces the <size> and/or <xy> everytime the window is shown or hidden. If not set, these parameter will be only set when the app is launched.
- `--follow-desktop`		Moves the window to the current desktop when showing.
- `--minimize-all`			Minimize all windows that were not set as standalone.
- `--test`					Get a list of all active windows names and classes. Use this to check the correct class and name for your application.

## how it works:
it writes a kwin script on a temporary file, installs it, runs it and uninstalls it. All using DBUS communication. 

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
* [x] size/position feature
* [ ] at every call, check if the saved processes in wList are still alive, and if not remove from the list (low importance)
* [ ] tray's action "close this window" should actually kill that process (only closing the window may not work)
* [x] optional: move to current desktop before showing up (using `--follow-desktop` flag)
* [ ] skipTaskbar is not supported under wayland for electron apps, so I will disable it for every app. 
