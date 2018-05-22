# sparkDuck

(That is not the best name I came up with, but at least it is not taken or under copyright)

## What is it:

A converter to convert USB rubber ducky's script to digispark code to put in Arduino IDE.

## What you need:

A digispark (duh)

(optionnal) USB extension cord (it will make you life WAY easier especially on laptops)


Those next, you can get on your favorite chinese seller website:

(optionnal) male usb plug to solder to it

(optionnal) empty plastic usb key case that could fit a DigiSpark

(optionnal) tin & soldering iron

(optionnal) Resin or thermo-shapable plastic to secure the male usb plug

## Why:

I found that it would be more easy to use a webpage to convert codes.
No C/C++, sketchy compiled code or python's code. Enjoy.

And why I think people should be aware of this:
https://youtu.be/XJCQBqTmGUU?t=17m23s

## For French users or azerty keyboard users:

Please use the provided .h librairy to get the correct ascii codes to get the proper results.

You could find them in the DigisparkKeyboard-azerty folder. 
Check the README inside the folder. 
You have to change files at the specified location.

## Scripts/payload:

https://github.com/hak5darren/USB-Rubber-Ducky/wiki/Payloads


## duckSpark Script Command List

This converter should (most of) support Rubber ducky commands.
See: https://github.com/hak5darren/USB-Rubber-Ducky/wiki/Duckyscript


|							Command/Modifier Keys								|
| ----------------------------------------------------------------------------- |
|  ESCAPE, ESC, GUI, WINDOWS, COMMAND, MENU, APP, END, SPACE, TAB, PRINTSCREEN, |
|  ENTER, RETURN, UPARROW, DOWNARROW, LEFTARROW, RIGHTARROW, UP, DOWN, LEFT, 	|
|  RIGHT, CAPSLOCK, DELETE, DEL, F1-F12, PAGEUP, PAGEDOWN, BACKSPACE			|

|			Keys			|
| ------------------------- |
| a - z						|
| A - Z						|
| 0 - 9						|


|			Command			|			Description				|
| ------------------------- | --------------------------------- |
| REM						| Comment							|
| STRING					| Types the following string 		|
| GUI						| Windows or CMD key				|

## Disclaimer:

Use it for educationnal purpose, be responsible please.
I don't endorse any misbehavior for using it.
I am not affiliate with DigiSpark or Hak5.

## TODO:

See TODO.md

## Credits:

Seytonic:

https://seytonic.com/

https://seytonic.com/ducky/

Digistump:

https://github.com/digistump/DigistumpArduino

Nurrl:

https://github.com/Nurrl/Duckuino

hak5darren:

https://github.com/hak5darren/USB-Rubber-Ducky

FrankBoesing:

https://github.com/FrankBoesing/cores
