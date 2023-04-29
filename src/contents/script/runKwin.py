#!/usr/bin/env python3

import subprocess
from datetime import datetime


def get_list_of_windows():
   datetime_now = datetime.now()

   script = "/home/tubbadu/code/Kirigami/ktoggle/src/contents/script/listWindows.js"

   reg_script_number = subprocess.run("dbus-send --print-reply --dest=org.kde.KWin \
                        /Scripting org.kde.kwin.Scripting.loadScript \
                        string:" + script + " | awk 'END {print $2}'",
                           capture_output=True, shell=True).stdout.decode().split("\n")[0]

   subprocess.run("dbus-send --print-reply --dest=org.kde.KWin /" + reg_script_number + " org.kde.kwin.Script.run",
                  shell=True, stdout=subprocess.DEVNULL)
   subprocess.run("dbus-send --print-reply --dest=org.kde.KWin /" + reg_script_number + " org.kde.kwin.Script.stop",
                  shell=True, stdout=subprocess.DEVNULL)  # unregister number

   since = str(datetime_now)

   msg = subprocess.run("journalctl _COMM=kwin_$XDG_SESSION_TYPE -o cat --since \"" + since + "\"",
                        capture_output=True, shell=True).stdout.decode().rstrip().split("\n")
   msg = [el.lstrip("js: > ") for el in msg]

   return msg

print('\n'.join(get_list_of_windows()))