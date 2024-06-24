#!/bin/bash

# This script creates 3 splits in tmux and open 3 screen sessions with a TTY device

PORT1="/dev/ttyUSB0"
PORT2="/dev/ttyUSB1"
PORT3="/dev/ttyUSB2"

BAUDRATE="9600"

tmux rename-window -t 0 'Main'

tmux split-window -h
tmux split-window -h

tmux select-layout even-horizontal

tmux send-keys -t 'Main' "screen ${PORT1} ${BAUDRATE}" C-m

tmux selectp -L
tmux send-keys -t 'Main' "screen ${PORT2} ${BAUDRATE}" C-m

tmux selectp -L
tmux send-keys -t 'Main' "screen ${PORT3} ${BAUDRATE}" C-m
