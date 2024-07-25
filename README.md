# WaitCommandPlugin

Add two commands `wait` and `wait_once` to Bakkesmod.

## Usage

`wait <ms> <command>`\
`wait_once <ms> <command>`

Example:\
`wait 1000 "ball location 0 0 1000"`

## Description

`wait` will wait the specified amount of milliseconds of in-game time before executing the command.\
It therefore works for different game speeds.

`wait_once` overwrites the previous command, if it didn't yet execute.\
`wait` allows multiple commands to be queued.

Example:\
`wait 1000 "ball location 0 0 1000"; wait 2000 "ball stop"` will move the ball after 1 second and freeze it after 2 seconds.\
`wait_once 1000 "ball location 0 0 1000"; wait_once 2000 "ball stop"` will only freeze the ball after 2 seconds.
