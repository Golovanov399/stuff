#!/bin/bash

("$(dirname $0)"/qwe.py "$@"; notify-send "AtCoder watcher has finished its work") &
