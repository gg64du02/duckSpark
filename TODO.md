# TODO: Add mini wiki page about the possible use of the script language which
 based on the https://github.com/hak5darren/USB-Rubber-Ducky/wiki/Duckyscript
 and check how to do it threre : https://github.com/Seytonic/malduino
 
# TODO: Delays needs to be shorter without changing functionnality in the multiOS 7 8 10 admin command prompt script
 
# TODO: Fix the STRING command, try to replace the DigiKeyboard.println() by something that
 does not insert \n or \r

# TODO: take a typical end result screenshots for each OS for the multiOS script

# TODO: test code generation with other payloads on the hak5 githib https://github.com/hak5darren/USB-Rubber-Ducky/wiki/Payloads
 
 
# TODO: Clean the useless comments (in the code converter)
# TODO: Tried to correct name of files in the repository without "breaking" them ie the code converter
# TODO: check out this http://digistump.com/board/index.php/topic,894.0.html to see if there is something to do (or already done)
# TODO: Make it deployment friendly for a website (I don't know if it currently works)


# TODO: take a look at that: https://gist.github.com/acspike/1022059
# TODO: take a look a that: https://gist.github.com/yoggy/731613



#=============================================================
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