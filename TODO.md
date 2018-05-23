
# TODO: check out this http://digistump.com/board/index.php/topic,894.0.html 
to see if there is something to do (or already done)
# TODO: Make it deployment friendly for a website (I don't know if it currently works)


# TODO: test the multiOS script on 8.0
 
# TODO: Delays needs to be shorter without changing functionnality in the
 multiOS 7 8 10 admin command prompt script

# TODO: remove .download from the names
 
# TODO: add a score number to notify the user that his script is to long, 
therefore not be able to run on the DigiSpark!!!
w/ proper stylesheet ?
# TODO: See the memory threshold when it happens.
# TODO: Try to came a with a single array generation during code translation (duckSpark.js)
maybe it will save the lenght issue ?!?



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
 
# =============================================================

# DON'T/CAN'T DO IT: multiOS script on 7 would change back the keyboard layout settings to the primary one set in 7
This is an issue with people switching between keyboard layout
-> Cannot be predicted (accross all OSs)
 