## duckSpark.js

###  Convert the rubber ducky script to Arduino IDE friendly code.


###  This will generate code containing those kind of lines:


###  DigiKeyboard.delay(3000);


#### straight foward, no comment.


###  DigiKeyboard.println("notepad");


#### println use the array scancode-ascii-table.h

#### this array maps ascii's code -> scancode


###  DigiKeyboard.sendKeyStroke(KEY_R,MOD_GUI_LEFT);

###  DigiKeyboard.sendKeyStroke(KEY_ENTER);


#### sendKeyStroke use scancodes defined with #define in DigiKeyboard.h


## DigiKeyboard.h (vary with the target keyboard layout ie keyboard's language)

###  Contains scancodes (#define at the beginnig of the file) for single keystroke and keystroke with modifiers.


## scancode-ascii-table.h (vary with the target keyboard layout ie keyboard's language)

###  Maps ascii-table to scancode
