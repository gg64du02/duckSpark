/*
 * Generated with <3 by Dckuino.js, an open source project ! Modified by gg64du02 combined with azerty keyboard
 */

#include "DigiKeyboard.h"

//#define KEY_TAB 179
#define KEY_BACKSPACE 8
#define MINI 170
#define MAXI 175

#define KEY_LEFT_GUI    0x0108
#define MODIFIERKEY_LEFT_GUI    ( 0x08 | 0xE000 )
#define MODIFIERKEY_ALT         ( 0x04 | 0xE000 )

#define KEY_MENU          ( 101  | 0xF000 )

#define ALTGR_MASK    0x0080


//for win 8

void setup()
{
  pinMode(1, OUTPUT); //LED on Model A
  digitalWrite(1, LOW); //turn off led when program start

  //INIT
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(3500);
  
  //DigiKeyboard.sendKeyStroke(MOD_GUI_LEFT);
  //DigiKeyboard.sendKeyStroke(KEY_LEFT_GUI);
  //bugfix windows key
  //win
  DigiKeyboard.sendKeyPress(0,MODIFIERKEY_LEFT_GUI);
  DigiKeyboard.sendKeyPress(0);

  
  DigiKeyboard.delay(200);
  //cmd
  DigiKeyboard.sendKeyStroke(KEY_C);
  DigiKeyboard.sendKeyStroke(KEY_M);
  DigiKeyboard.sendKeyStroke(KEY_D);
  DigiKeyboard.delay(4000);

  //DigiKeyboard.sendKeyPress(0,KEY_MENU);
  //DigiKeyboard.sendKeyPress(0);
  //bugfix
  //gui menu (context)
  DigiKeyboard.sendKeyStroke(KEY_MENU);
  
  
  DigiKeyboard.delay(1000);
  //a
  DigiKeyboard.sendKeyStroke(KEY_A);
  DigiKeyboard.delay(1000);
  //backspace
  DigiKeyboard.sendKeyStroke(42);
  DigiKeyboard.delay(1000);
  //alt + y
  DigiKeyboard.sendKeyStroke(KEY_Y,MOD_ALT_LEFT);
  DigiKeyboard.delay(1000);

  //gui menu (context)
  DigiKeyboard.sendKeyStroke(KEY_MENU);

  //DigiKeyboard.delay(200);
  DigiKeyboard.delay(2000);
  //arrow down
  DigiKeyboard.sendKeyStroke(81);
  //DigiKeyboard.delay(200);
  DigiKeyboard.delay(2000);
  //enter
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  
  //====================ok
  
  //digitalWrite(1, HIGH); //turn on led when program end
  
  DigiKeyboard.delay(2000);
  
  //arrow left
  //DigiKeyboard.sendKeyStroke(80);
  DigiKeyboard.sendKeyStroke(KEY_ARROW_LEFT);
  DigiKeyboard.delay(2000);
  
  DigiKeyboard.sendKeyStroke(KEY_ARROW_LEFT);
  DigiKeyboard.delay(2000);
  
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  
  //====================ok 10 7 cmd ouvert an admin ok 2018 05 18
  DigiKeyboard.delay(2000);//2018 05 18

  //from here in win 8

  //digitalWrite(1, HIGH); //turn on led when program end
  
  //DigiKeyboard.sendKeyPress(0);//2018 05 18
  DigiKeyboard.delay(2000);//2018 05 18
  
  DigiKeyboard.sendKeyStroke(KEY_ARROW_LEFT);
  DigiKeyboard.delay(2000);//2018 05 18

  //cmd
  DigiKeyboard.sendKeyStroke(KEY_C);
  DigiKeyboard.sendKeyStroke(KEY_M);
  DigiKeyboard.sendKeyStroke(KEY_D);

  DigiKeyboard.delay(2000);//2018 05 18
  
  //gui menu (context)
  DigiKeyboard.sendKeyStroke(KEY_MENU);
  DigiKeyboard.delay(2000);//2018 05 18

  DigiKeyboard.sendKeyStroke(KEY_ARROW_UP);
  DigiKeyboard.delay(2000);//2018 05 18

  DigiKeyboard.sendKeyStroke(KEY_ARROW_UP);
  DigiKeyboard.delay(2000);//2018 05 18
  
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(2000);//2018 05 18
  
  //alt + y
  DigiKeyboard.sendKeyStroke(KEY_Y,MOD_ALT_LEFT);
  DigiKeyboard.delay(2000);//2018 05 18
  
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(2000);//2018 05 18
  
  DigiKeyboard.println("echo hello world!");

  //works in 2018 05 19 at 01:46

  DigiKeyboard.delay(2000);//2018 05 18

  digitalWrite(1, HIGH); //turn on led when program end
}

/* Unused endless loop */
void loop() {}
