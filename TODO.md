
# TODO: correct style sheet for the console error in firefox (5.2% marketshare)
still works but you can't read the lines' number if you are on firefox

# TODO:Add an info button next to it when the RAM usage guess is RED.

# TODO: Make it deployment friendly for a website (I don't know if it currently works)

# TODO: Delays needs to be shorter without changing functionnality in the
 multiOS 7 8 10 admin command prompt script

# TODO: Try to came a with a single array generation during code translation (duckSpark.js)
maybe it will save some RAM and allow more lenght ?!?

# TODO: check support of this below string for french keyboard
DigiKeyboard.println("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890ß ü+öä#,.- !"X$%&/()=? Ü*ÖÄ';:_ {[]}\~ <>| @§ ^´``");

# TODO: make a more accurate predection of RAM use
# TODO: add Edge support (1.9% marketshare)

# TODO: check https://digistump.com/board/index.php?topic=1676.0
# TODO: check "digiduck uslurper"

# =============================================================
# DONE: (the Ino) Make the custom payload discovered (multiOS: 7 8 10) public (no spoiler ;) )

# DONE: A lot of fixing mainly focused to get the 7_8_10.txt converted properly

# DONE: fix 
  DigiKeyboard.sendKeyStroke(0,MODIFIERKEY_LEFT_GUI); is ok
  DigiKeyboard.sendKeyStroke(MODIFIERKEY_LEFT_GUI); is not ok (the result is:'e');

  DigiKeyboard.sendKeyStroke(0,BACKSPACE); is not ok
  DigiKeyboard.sendKeyStroke(BACKSPACE); is  ok
  
  maybe in DigiKeyboard.h ?
  https://github.com/Tranquilite0/Teensy-Keyboard/blob/master/usb_keyboard.h
  
# DONE: (the sequence on the keyboard to input) Make the custom payload discovered (multiOS 7 8 10) public (no spoiler ;) )
# BETTER KEYBOARD support for French

# DONE: add more keyboard key support from the script language (modify both duckSpark.js and DigiKeyboard.h)

# DONE: take a typical end result screenshots for each OS for the multiOS script

# DONE: check for teensy keyboard support (emulation) english too ?
https://github.com/FrankBoesing/cores/blob/master/teensy/keylayouts.h

# DONE: check the (scancode.h or duckSpark.js) files: why they are some missing keystroke during the tests ?
 for a better support of DigiSpakr.println for french/english (example check: Payload_WiFi_key_grabber)
 : The payload is too long ? (quite common :( ie on several scripts)
 
# DONE: Fix the STRING command, try to replace the DigiKeyboard.println() by something that
 does not insert \n or \r
 
# DONE: Add mini wiki page about the possible use of the script language which
 based on the https://github.com/hak5darren/USB-Rubber-Ducky/wiki/Duckyscript
 and check how to do it threre : https://github.com/Seytonic/malduino

# DONE: test code generation with other payloads on the hak5 githib https://github.com/hak5darren/USB-Rubber-Ducky/wiki/Payloads

# DONE: take a look at that: https://gist.github.com/acspike/1022059
# DONE: take a look a that: https://gist.github.com/yoggy/731613
-> teensy constants are enough

# DONE: Clean the useless comments (in the code converter)

# DONE: Try to correct name of files in the repository without "breaking" them ie the code converter

# DONE: remove .download from the names

# DONE: check out this http://digistump.com/board/index.php/topic,894.0.html 
to see if there is something to do (or already done)
DigiKeyboard.println("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890 !\"#$%&'()*+,-./:;<=>?@[\]^_`{|}~~");
is fine

# DONE: test the multiOS script on 8.0 professionnal

# DONE: change the links inside the webpage 

# DONE: See the memory threshold when it happens.
use: https://stackoverflow.com/questions/4009756/how-to-count-string-occurrence-in-string

# DONE: add a score number to notify the user that his script is to long, 
therefore not be able to run on the DigiSpark!!!
w/ proper stylesheet ?

# DONE: correcting style sheet in the error textarea and removing console message in the log area

# DONE: add the support of DEFAULT_DELAY

# DONE: try most scripts available with hak5's payloads
|-> tested duckSpark.js on all of them, the 30/05/2018
|-> some were ajusted/corrected to work with duckSpark.js (error in the script, not a converter side issue)

# DONE: change the webpage's title

# DONE: add line numbers in duckSpark.js

# DONE: make a video about it ?

# DONE: test chromium-browser: works

# DONE: test chrome: works (58% marketshare)

# DONE: add explaination about what is the main purpose of each files

# =============================================================

# DON'T/CAN'T DO IT: multiOS script on 7 would change back the keyboard layout settings to the primary one set in 7
This is an issue with people switching between keyboard layout
-> Cannot be predicted (accross all OSs)
 