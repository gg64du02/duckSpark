/*
 * Generated with <3 by Dckuino.js, an open source project ! Please check the Nurrl github, and style sheet from Seytonic`s website Modified by gg64du02
 */

#include "DigiKeyboard.h"

void typeKey(int key)
{
  DigiKeyboard.sendKeyStroke(key);
  //Keyboard.press(key);
  //delay(50);
  //Keyboard.release(key);
}


void setup()
{
  pinMode(1, OUTPUT); //LED on Model A
  digitalWrite(1, LOW); //turn off led when program start

  //INIT
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(3000);

  DigiKeyboard.delay(3500);

  // win
  DigiKeyboard.sendKeyStroke(0,MODIFIERKEY_LEFT_GUI);

  DigiKeyboard.delay(4000);

  // cmd
  // TYPEing cmd
  // STRING debug
  DigiKeyboard.sendKeyStroke(KEY_C);

  DigiKeyboard.sendKeyStroke(KEY_M);

  DigiKeyboard.sendKeyStroke(KEY_D);

  DigiKeyboard.delay(4000);

  // gui menu (context)
  DigiKeyboard.sendKeyStroke(KEY_MENU);

  DigiKeyboard.delay(2000);

  // a
  DigiKeyboard.sendKeyStroke(KEY_A);

  DigiKeyboard.delay(2000);

  // BACKSPACE
  DigiKeyboard.sendKeyStroke(BACKSPACE);

  DigiKeyboard.delay(2000);

  // ALT y
  DigiKeyboard.sendKeyStroke(KEY_Y,MOD_ALT_LEFT);

  DigiKeyboard.delay(2000);

  // gui menu (context)
  DigiKeyboard.sendKeyStroke(KEY_MENU);

  DigiKeyboard.delay(2000);

  // DOWNARROW
  DigiKeyboard.sendKeyStroke(DOWNARROW);

  DigiKeyboard.delay(2000);

  // ENTER
  DigiKeyboard.sendKeyStroke(KEY_ENTER);

  DigiKeyboard.delay(2000);

  // LEFTARROW
  DigiKeyboard.sendKeyStroke(LEFTARROW);

  DigiKeyboard.delay(2000);

  // LEFTARROW
  DigiKeyboard.sendKeyStroke(LEFTARROW);

  DigiKeyboard.delay(2000);

  // ENTER
  DigiKeyboard.sendKeyStroke(KEY_ENTER);

  DigiKeyboard.delay(2000);

  DigiKeyboard.delay(2000);

  // LEFTARROW
  DigiKeyboard.sendKeyStroke(LEFTARROW);

  DigiKeyboard.delay(2000);

  // TYPEing cmd
  DigiKeyboard.sendKeyStroke(KEY_C);

  DigiKeyboard.sendKeyStroke(KEY_M);

  DigiKeyboard.sendKeyStroke(KEY_D);

  DigiKeyboard.delay(2000);

  // gui menu (context)
  DigiKeyboard.sendKeyStroke(KEY_MENU);

  DigiKeyboard.delay(2000);

  // UPARROW
  DigiKeyboard.sendKeyStroke(UPARROW);

  DigiKeyboard.delay(2000);

  // UPARROW
  DigiKeyboard.sendKeyStroke(UPARROW);

  DigiKeyboard.delay(2000);

  // ENTER
  DigiKeyboard.sendKeyStroke(KEY_ENTER);

  DigiKeyboard.delay(2000);

  // ALT y
  DigiKeyboard.sendKeyStroke(KEY_Y,MOD_ALT_LEFT);

  DigiKeyboard.delay(2000);

  // ENTER
  DigiKeyboard.sendKeyStroke(KEY_ENTER);

  DigiKeyboard.delay(2000);

  DigiKeyboard.println("echo hello world!");

  DigiKeyboard.delay(2000);

  digitalWrite(1, HIGH); //turn on led when program end
}

/* Unused endless loop */
void loop() {}
