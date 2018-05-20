/*
 * Based on Obdev's AVRUSB code and under the same license.
 *
 * TODO: Make a proper file header. :-)
 * Modified for Digispark by Digistump
 */
#ifndef __DigiKeyboard_h__
#define __DigiKeyboard_h__

#include <Arduino.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
#include <string.h>

#include "usbdrv.h"
#include "scancode-ascii-table.h"

// TODO: Work around Arduino 12 issues better.
//#include <WConstants.h>
//#undef int()

typedef uint8_t byte;


#define BUFFER_SIZE 2 // Minimum of 2: 1 for modifiers + 1 for keystroke 


static uchar    idleRate;           // in 4 ms units 


/* We use a simplifed keyboard report descriptor which does not support the
 * boot protocol. We don't allow setting status LEDs and but we do allow
 * simultaneous key presses. 
 * The report descriptor has been created with usb.org's "HID Descriptor Tool"
 * which can be downloaded from http://www.usb.org/developers/hidpage/.
 * Redundant entries (such as LOGICAL_MINIMUM and USAGE_PAGE) have been omitted
 * for the second INPUT item.
 */
const PROGMEM char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = { /* USB report descriptor */
  0x05, 0x01,                    // USAGE_PAGE (Generic Desktop) 
  0x09, 0x06,                    // USAGE (Keyboard) 
  0xa1, 0x01,                    // COLLECTION (Application) 
  0x05, 0x07,                    //   USAGE_PAGE (Keyboard) 
  0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl) 
  0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI) 
  0x15, 0x00,                    //   LOGICAL_MINIMUM (0) 
  0x25, 0x01,                    //   LOGICAL_MAXIMUM (1) 
  0x75, 0x01,                    //   REPORT_SIZE (1) 
  0x95, 0x08,                    //   REPORT_COUNT (8) 
  0x81, 0x02,                    //   INPUT (Data,Var,Abs) 
  0x95, 0x01,           //   REPORT_COUNT (simultaneous keystrokes) 
  0x75, 0x08,                    //   REPORT_SIZE (8) 
  0x25, 0x65,                    //   LOGICAL_MAXIMUM (101) 
  0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated)) 
  0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application) 
  0x81, 0x00,                    //   INPUT (Data,Ary,Abs) 
  0xc0                           // END_COLLECTION 
};



/* Keyboard usage values, see usb.org's HID-usage-tables document, chapter
 * 10 Keyboard/Keypad Page for more codes.
 */
 
#define MOD_CONTROL_LEFT    (1<<0)
#define MOD_SHIFT_LEFT      (1<<1)
#define MOD_ALT_LEFT        (1<<2)
#define MOD_GUI_LEFT        (1<<3)
#define MOD_CONTROL_RIGHT   (1<<4)
#define MOD_SHIFT_RIGHT     (1<<5)
#define MOD_ALT_RIGHT       (1<<6)
#define MOD_GUI_RIGHT       (1<<7)
/*
#define KEY_A       20
#define KEY_B       5
#define KEY_C       6
#define KEY_D       7
#define KEY_E       8
#define KEY_F       9
#define KEY_G       10
#define KEY_H       11
#define KEY_I       12
#define KEY_J       13
#define KEY_K       14
#define KEY_L       15
#define KEY_M       51
#define KEY_N       17
#define KEY_O       18
#define KEY_P       19
#define KEY_Q       4
#define KEY_R       21
#define KEY_S       22
#define KEY_T       23
#define KEY_U       24
#define KEY_V       25
#define KEY_W       29
#define KEY_X       27
#define KEY_Y       28
#define KEY_Z       26
#define KEY_1       30
#define KEY_2       31
#define KEY_3       32
#define KEY_4       33
#define KEY_5       34
#define KEY_6       35
#define KEY_7       36
#define KEY_8       37
#define KEY_9       38
#define KEY_0       39

#define KEY_ENTER   40

#define KEY_SPACE   44

#define KEY_F1      58
#define KEY_F2      59
#define KEY_F3      60
#define KEY_F4      61
#define KEY_F5      62
#define KEY_F6      63
#define KEY_F7      64
#define KEY_F8      65
#define KEY_F9      66
#define KEY_F10     67
#define KEY_F11     68
#define KEY_F12     69

/*
//previous code

#define LEFTARROW 0x50
#define RIGHTARROW 0x4F
#define UPARROW  0x52
#define DOWNARROW    0x51

#define MODIFIERKEY_LEFT_GUI ( 0x08 | 0xE000 )

#define KEY_MENU ( 101  | 0xF000 )

#define BACKSPACE 42
*/


#define MODIFIERKEY_CTRL        ( 0x01 | 0xE000 )
#define MODIFIERKEY_SHIFT       ( 0x02 | 0xE000 )
#define MODIFIERKEY_ALT         ( 0x04 | 0xE000 )
#define MODIFIERKEY_GUI         ( 0x08 | 0xE000 )
#define MODIFIERKEY_LEFT_CTRL   ( 0x01 | 0xE000 )
#define MODIFIERKEY_LEFT_SHIFT  ( 0x02 | 0xE000 )
#define MODIFIERKEY_LEFT_ALT    ( 0x04 | 0xE000 )
#define MODIFIERKEY_LEFT_GUI    ( 0x08 | 0xE000 )
#define MODIFIERKEY_RIGHT_CTRL  ( 0x10 | 0xE000 )
#define MODIFIERKEY_RIGHT_SHIFT ( 0x20 | 0xE000 )
#define MODIFIERKEY_RIGHT_ALT   ( 0x40 | 0xE000 )
#define MODIFIERKEY_RIGHT_GUI   ( 0x80 | 0xE000 )

#define KEY_SYSTEM_POWER_DOWN   ( 0x81 | 0xE200 )
#define KEY_SYSTEM_SLEEP        ( 0x82 | 0xE200 )
#define KEY_SYSTEM_WAKE_UP      ( 0x83 | 0xE200 )

#define KEY_MEDIA_PLAY          ( 0xB0 | 0xE400 )
#define KEY_MEDIA_PAUSE         ( 0xB1 | 0xE400 )
#define KEY_MEDIA_RECORD        ( 0xB2 | 0xE400 )
#define KEY_MEDIA_FAST_FORWARD  ( 0xB3 | 0xE400 )
#define KEY_MEDIA_REWIND        ( 0xB4 | 0xE400 )
#define KEY_MEDIA_NEXT_TRACK    ( 0xB5 | 0xE400 )
#define KEY_MEDIA_PREV_TRACK    ( 0xB6 | 0xE400 )
#define KEY_MEDIA_STOP          ( 0xB7 | 0xE400 )
#define KEY_MEDIA_EJECT         ( 0xB8 | 0xE400 )
#define KEY_MEDIA_RANDOM_PLAY   ( 0xB9 | 0xE400 )
#define KEY_MEDIA_PLAY_PAUSE    ( 0xCD | 0xE400 )
#define KEY_MEDIA_PLAY_SKIP     ( 0xCE | 0xE400 )
#define KEY_MEDIA_MUTE          ( 0xE2 | 0xE400 )
#define KEY_MEDIA_VOLUME_INC    ( 0xE9 | 0xE400 )
#define KEY_MEDIA_VOLUME_DEC    ( 0xEA | 0xE400 )
/*
//From teensy
#define KEY_A                   (   4  | 0xF000 )
#define KEY_B                   (   5  | 0xF000 )
#define KEY_C                   (   6  | 0xF000 )
#define KEY_D                   (   7  | 0xF000 )
#define KEY_E                   (   8  | 0xF000 )
#define KEY_F                   (   9  | 0xF000 )
#define KEY_G                   (  10  | 0xF000 )
#define KEY_H                   (  11  | 0xF000 )
#define KEY_I                   (  12  | 0xF000 )
#define KEY_J                   (  13  | 0xF000 )
#define KEY_K                   (  14  | 0xF000 )
#define KEY_L                   (  15  | 0xF000 )
#define KEY_M                   (  16  | 0xF000 )
#define KEY_N                   (  17  | 0xF000 )
#define KEY_O                   (  18  | 0xF000 )
#define KEY_P                   (  19  | 0xF000 )
#define KEY_Q                   (  20  | 0xF000 )
#define KEY_R                   (  21  | 0xF000 )
#define KEY_S                   (  22  | 0xF000 )
#define KEY_T                   (  23  | 0xF000 )
#define KEY_U                   (  24  | 0xF000 )
#define KEY_V                   (  25  | 0xF000 )
#define KEY_W                   (  26  | 0xF000 )
#define KEY_X                   (  27  | 0xF000 )
#define KEY_Y                   (  28  | 0xF000 )
#define KEY_Z                   (  29  | 0xF000 )
#define KEY_1                   (  30  | 0xF000 )
#define KEY_2                   (  31  | 0xF000 )
#define KEY_3                   (  32  | 0xF000 )
#define KEY_4                   (  33  | 0xF000 )
#define KEY_5                   (  34  | 0xF000 )
#define KEY_6                   (  35  | 0xF000 )
#define KEY_7                   (  36  | 0xF000 )
#define KEY_8                   (  37  | 0xF000 )
#define KEY_9                   (  38  | 0xF000 )
#define KEY_0                   (  39  | 0xF000 )
*/

#define KEY_ENTER               (  40  | 0xF000 )
#define KEY_ESC                 (  41  | 0xF000 )
#define KEY_BACKSPACE           (  42  | 0xF000 )
#define KEY_TAB                 (  43  | 0xF000 )
#define KEY_SPACE               (  44  | 0xF000 )
#define KEY_MINUS               (  45  | 0xF000 )
#define KEY_EQUAL               (  46  | 0xF000 )
#define KEY_LEFT_BRACE          (  47  | 0xF000 )
#define KEY_RIGHT_BRACE         (  48  | 0xF000 )
#define KEY_BACKSLASH           (  49  | 0xF000 )
#define KEY_NON_US_NUM          (  50  | 0xF000 )
#define KEY_SEMICOLON           (  51  | 0xF000 )
#define KEY_QUOTE               (  52  | 0xF000 )
#define KEY_TILDE               (  53  | 0xF000 )
#define KEY_COMMA               (  54  | 0xF000 )
#define KEY_PERIOD              (  55  | 0xF000 )
#define KEY_SLASH               (  56  | 0xF000 )
#define KEY_CAPS_LOCK           (  57  | 0xF000 )
#define KEY_F1                  (  58  | 0xF000 )
#define KEY_F2                  (  59  | 0xF000 )
#define KEY_F3                  (  60  | 0xF000 )
#define KEY_F4                  (  61  | 0xF000 )
#define KEY_F5                  (  62  | 0xF000 )
#define KEY_F6                  (  63  | 0xF000 )
#define KEY_F7                  (  64  | 0xF000 )
#define KEY_F8                  (  65  | 0xF000 )
#define KEY_F9                  (  66  | 0xF000 )
#define KEY_F10                 (  67  | 0xF000 )
#define KEY_F11                 (  68  | 0xF000 )
#define KEY_F12                 (  69  | 0xF000 )
#define KEY_PRINTSCREEN         (  70  | 0xF000 )
#define KEY_SCROLL_LOCK         (  71  | 0xF000 )
#define KEY_PAUSE               (  72  | 0xF000 )
#define KEY_INSERT              (  73  | 0xF000 )
#define KEY_HOME                (  74  | 0xF000 )
#define KEY_PAGE_UP             (  75  | 0xF000 )
#define KEY_DELETE              (  76  | 0xF000 )
#define KEY_END                 (  77  | 0xF000 )
#define KEY_PAGE_DOWN           (  78  | 0xF000 )
#define KEY_RIGHT               (  79  | 0xF000 )
#define KEY_LEFT                (  80  | 0xF000 )
#define KEY_DOWN                (  81  | 0xF000 )
#define KEY_UP                  (  82  | 0xF000 )
#define KEY_NUM_LOCK            (  83  | 0xF000 )
#define KEYPAD_SLASH            (  84  | 0xF000 )
#define KEYPAD_ASTERIX          (  85  | 0xF000 )
#define KEYPAD_MINUS            (  86  | 0xF000 )
#define KEYPAD_PLUS             (  87  | 0xF000 )
#define KEYPAD_ENTER            (  88  | 0xF000 )
#define KEYPAD_1                (  89  | 0xF000 )
#define KEYPAD_2                (  90  | 0xF000 )
#define KEYPAD_3                (  91  | 0xF000 )
#define KEYPAD_4                (  92  | 0xF000 )
#define KEYPAD_5                (  93  | 0xF000 )
#define KEYPAD_6                (  94  | 0xF000 )
#define KEYPAD_7                (  95  | 0xF000 )
#define KEYPAD_8                (  96  | 0xF000 )
#define KEYPAD_9                (  97  | 0xF000 )
#define KEYPAD_0                (  98  | 0xF000 )
#define KEYPAD_PERIOD           (  99  | 0xF000 )
#define KEY_NON_US_BS           ( 100  | 0xF000 )
#define KEY_MENU        	( 101  | 0xF000 )
#define KEY_F13                 ( 104  | 0xF000 )
#define KEY_F14                 ( 105  | 0xF000 )
#define KEY_F15                 ( 106  | 0xF000 )
#define KEY_F16                 ( 107  | 0xF000 )
#define KEY_F17                 ( 108  | 0xF000 )
#define KEY_F18                 ( 109  | 0xF000 )
#define KEY_F19                 ( 110  | 0xF000 )
#define KEY_F20                 ( 111  | 0xF000 )
#define KEY_F21                 ( 112  | 0xF000 )
#define KEY_F22                 ( 113  | 0xF000 )
#define KEY_F23                 ( 114  | 0xF000 )
#define KEY_F24                 ( 115  | 0xF000 )

// for compatibility with Leonardo's slightly different names
#define KEY_UP_ARROW	KEY_UP
#define KEY_DOWN_ARROW	KEY_DOWN
#define KEY_LEFT_ARROW	KEY_LEFT
#define KEY_RIGHT_ARROW	KEY_RIGHT
#define KEY_RETURN	KEY_ENTER
#define KEY_LEFT_CTRL	MODIFIERKEY_LEFT_CTRL
#define KEY_LEFT_SHIFT	MODIFIERKEY_LEFT_SHIFT
#define KEY_LEFT_ALT	MODIFIERKEY_LEFT_ALT
#define KEY_LEFT_GUI	MODIFIERKEY_LEFT_GUI
#define KEY_RIGHT_CTRL	MODIFIERKEY_RIGHT_CTRL
#define KEY_RIGHT_SHIFT	MODIFIERKEY_RIGHT_SHIFT
#define KEY_RIGHT_ALT	MODIFIERKEY_RIGHT_ALT
#define KEY_RIGHT_GUI	MODIFIERKEY_RIGHT_GUI



//###########################################################
/*
//From teensy
#define KEY_A                   (   4  | 0xF000 )
#define KEY_B                   (   5  | 0xF000 )
#define KEY_C                   (   6  | 0xF000 )
#define KEY_D                   (   7  | 0xF000 )
#define KEY_E                   (   8  | 0xF000 )
#define KEY_F                   (   9  | 0xF000 )
#define KEY_G                   (  10  | 0xF000 )
#define KEY_H                   (  11  | 0xF000 )
#define KEY_I                   (  12  | 0xF000 )
#define KEY_J                   (  13  | 0xF000 )
#define KEY_K                   (  14  | 0xF000 )
#define KEY_L                   (  15  | 0xF000 )
#define KEY_M                   (  16  | 0xF000 )
#define KEY_N                   (  17  | 0xF000 )
#define KEY_O                   (  18  | 0xF000 )
#define KEY_P                   (  19  | 0xF000 )
#define KEY_Q                   (  20  | 0xF000 )
#define KEY_R                   (  21  | 0xF000 )
#define KEY_S                   (  22  | 0xF000 )
#define KEY_T                   (  23  | 0xF000 )
#define KEY_U                   (  24  | 0xF000 )
#define KEY_V                   (  25  | 0xF000 )
#define KEY_W                   (  26  | 0xF000 )
#define KEY_X                   (  27  | 0xF000 )
#define KEY_Y                   (  28  | 0xF000 )
#define KEY_Z                   (  29  | 0xF000 )
#define KEY_1                   (  30  | 0xF000 )
#define KEY_2                   (  31  | 0xF000 )
#define KEY_3                   (  32  | 0xF000 )
#define KEY_4                   (  33  | 0xF000 )
#define KEY_5                   (  34  | 0xF000 )
#define KEY_6                   (  35  | 0xF000 )
#define KEY_7                   (  36  | 0xF000 )
#define KEY_8                   (  37  | 0xF000 )
#define KEY_9                   (  38  | 0xF000 )
#define KEY_0                   (  39  | 0xF000 )
*/

//From the former code
#define KEY_A       20
#define KEY_B       5
#define KEY_C       6
#define KEY_D       7
#define KEY_E       8
#define KEY_F       9
#define KEY_G       10
#define KEY_H       11
#define KEY_I       12
#define KEY_J       13
#define KEY_K       14
#define KEY_L       15
#define KEY_M       51
#define KEY_N       17
#define KEY_O       18
#define KEY_P       19
#define KEY_Q       4
#define KEY_R       21
#define KEY_S       22
#define KEY_T       23
#define KEY_U       24
#define KEY_V       25
#define KEY_W       29
#define KEY_X       27
#define KEY_Y       28
#define KEY_Z       26
#define KEY_1       30
#define KEY_2       31
#define KEY_3       32
#define KEY_4       33
#define KEY_5       34
#define KEY_6       35
#define KEY_7       36
#define KEY_8       37
#define KEY_9       38
#define KEY_0       39


#define KEY_ENTER               (  40  | 0xF000 )
#define KEY_ESC                 (  41  | 0xF000 )
#define KEY_BACKSPACE           (  42  | 0xF000 )
#define KEY_TAB                 (  43  | 0xF000 )
#define KEY_SPACE               (  44  | 0xF000 )
#define KEY_MINUS               (  45  | 0xF000 )
#define KEY_EQUAL               (  46  | 0xF000 )
#define KEY_LEFT_BRACE          (  47  | 0xF000 )
#define KEY_RIGHT_BRACE         (  48  | 0xF000 )
#define KEY_BACKSLASH           (  49  | 0xF000 )
#define KEY_NON_US_NUM          (  50  | 0xF000 )
#define KEY_SEMICOLON           (  51  | 0xF000 )
#define KEY_QUOTE               (  52  | 0xF000 )
#define KEY_TILDE               (  53  | 0xF000 )
#define KEY_COMMA               (  54  | 0xF000 )
#define KEY_PERIOD              (  55  | 0xF000 )
#define KEY_SLASH               (  56  | 0xF000 )
#define KEY_CAPS_LOCK           (  57  | 0xF000 )
#define KEY_F1                  (  58  | 0xF000 )
#define KEY_F2                  (  59  | 0xF000 )
#define KEY_F3                  (  60  | 0xF000 )
#define KEY_F4                  (  61  | 0xF000 )
#define KEY_F5                  (  62  | 0xF000 )
#define KEY_F6                  (  63  | 0xF000 )
#define KEY_F7                  (  64  | 0xF000 )
#define KEY_F8                  (  65  | 0xF000 )
#define KEY_F9                  (  66  | 0xF000 )
#define KEY_F10                 (  67  | 0xF000 )
#define KEY_F11                 (  68  | 0xF000 )
#define KEY_F12                 (  69  | 0xF000 )
#define KEY_PRINTSCREEN         (  70  | 0xF000 )
#define KEY_SCROLL_LOCK         (  71  | 0xF000 )
#define KEY_PAUSE               (  72  | 0xF000 )
#define KEY_INSERT              (  73  | 0xF000 )
#define KEY_HOME                (  74  | 0xF000 )
#define KEY_PAGE_UP             (  75  | 0xF000 )
#define KEY_DELETE              (  76  | 0xF000 )
#define KEY_END                 (  77  | 0xF000 )
#define KEY_PAGE_DOWN           (  78  | 0xF000 )
#define KEY_RIGHT               (  79  | 0xF000 )
#define KEY_LEFT                (  80  | 0xF000 )
#define KEY_DOWN                (  81  | 0xF000 )
#define KEY_UP                  (  82  | 0xF000 )
#define KEY_NUM_LOCK            (  83  | 0xF000 )
#define KEYPAD_SLASH            (  84  | 0xF000 )
#define KEYPAD_ASTERIX          (  85  | 0xF000 )
#define KEYPAD_MINUS            (  86  | 0xF000 )
#define KEYPAD_PLUS             (  87  | 0xF000 )
#define KEYPAD_ENTER            (  88  | 0xF000 )
#define KEYPAD_1                (  89  | 0xF000 )
#define KEYPAD_2                (  90  | 0xF000 )
#define KEYPAD_3                (  91  | 0xF000 )
#define KEYPAD_4                (  92  | 0xF000 )
#define KEYPAD_5                (  93  | 0xF000 )
#define KEYPAD_6                (  94  | 0xF000 )
#define KEYPAD_7                (  95  | 0xF000 )
#define KEYPAD_8                (  96  | 0xF000 )
#define KEYPAD_9                (  97  | 0xF000 )
#define KEYPAD_0                (  98  | 0xF000 )
#define KEYPAD_PERIOD           (  99  | 0xF000 )
#define KEY_NON_US_BS           ( 100  | 0xF000 )
#define KEY_MENU        	( 101  | 0xF000 )
#define KEY_F13                 ( 104  | 0xF000 )
#define KEY_F14                 ( 105  | 0xF000 )
#define KEY_F15                 ( 106  | 0xF000 )
#define KEY_F16                 ( 107  | 0xF000 )
#define KEY_F17                 ( 108  | 0xF000 )
#define KEY_F18                 ( 109  | 0xF000 )
#define KEY_F19                 ( 110  | 0xF000 )
#define KEY_F20                 ( 111  | 0xF000 )
#define KEY_F21                 ( 112  | 0xF000 )
#define KEY_F22                 ( 113  | 0xF000 )
#define KEY_F23                 ( 114  | 0xF000 )
#define KEY_F24                 ( 115  | 0xF000 )





//===============================================
//===============================================
//===============================================




#define SHIFT_MASK		0x0040
#define ALTGR_MASK		0x0080
#define DEADKEYS_MASK		0x0700
#define	CIRCUMFLEX_BITS		0x0100
#define GRAVE_ACCENT_BITS	0x0200
#define DIAERESIS_BITS		0x0300
#define TILDE_BITS		0x0400
#define KEYCODE_TYPE		uint16_t
#define KEYCODE_MASK		0x07FF
#define DEADKEY_CIRCUMFLEX	KEY_LEFT_BRACE
#define DEADKEY_GRAVE_ACCENT	KEY_7 + ALTGR_MASK
#define DEADKEY_DIAERESIS	KEY_LEFT_BRACE + SHIFT_MASK
#define DEADKEY_TILDE		KEY_2 + ALTGR_MASK
#define KEY_NON_US_100		63

#define ASCII_20	KEY_SPACE				// 32  
#define ASCII_21	KEY_SLASH				// 33 !
#define ASCII_22	KEY_3					// 34 "
#define ASCII_23	KEY_3 + ALTGR_MASK			// 35 #
#define ASCII_24	KEY_RIGHT_BRACE				// 36 $
#define ASCII_25	KEY_QUOTE + SHIFT_MASK			// 37 %
#define ASCII_26	KEY_1					// 38 &
#define ASCII_27	KEY_4					// 39 '
#define ASCII_28	KEY_5					// 40 (
#define ASCII_29	KEY_MINUS				// 41 )
#define ASCII_2A	KEY_BACKSLASH				// 42 *
#define ASCII_2B	KEY_EQUAL + SHIFT_MASK			// 43 +
#define ASCII_2C	KEY_M					// 44 ,
#define ASCII_2D	KEY_6					// 45 -
#define ASCII_2E	KEY_COMMA + SHIFT_MASK			// 46 .
#define ASCII_2F	KEY_PERIOD + SHIFT_MASK			// 47 /
#define ASCII_30	KEY_0 + SHIFT_MASK			// 48 0
#define ASCII_31	KEY_1 + SHIFT_MASK			// 49 1
#define ASCII_32	KEY_2 + SHIFT_MASK			// 50 2
#define ASCII_33	KEY_3 + SHIFT_MASK			// 51 3
#define ASCII_34	KEY_4 + SHIFT_MASK			// 52 4
#define ASCII_35	KEY_5 + SHIFT_MASK			// 53 5
#define ASCII_36	KEY_6 + SHIFT_MASK			// 54 6
#define ASCII_37	KEY_7 + SHIFT_MASK			// 55 7
#define ASCII_38	KEY_8 + SHIFT_MASK			// 55 8
#define ASCII_39	KEY_9 + SHIFT_MASK			// 57 9
#define ASCII_3A	KEY_PERIOD				// 58 :
#define ASCII_3B	KEY_COMMA				// 59 ;
#define ASCII_3C	KEY_NON_US_100				// 60 <
#define ASCII_3D	KEY_EQUAL				// 61 =
#define ASCII_3E	KEY_NON_US_100 + SHIFT_MASK		// 62 >
#define ASCII_3F	KEY_M + SHIFT_MASK			// 63 ?
#define ASCII_40	KEY_0 + ALTGR_MASK			// 64 @
#define ASCII_41	KEY_Q + SHIFT_MASK			// 65 A
#define ASCII_42	KEY_B + SHIFT_MASK			// 66 B
#define ASCII_43	KEY_C + SHIFT_MASK			// 67 C
#define ASCII_44	KEY_D + SHIFT_MASK			// 68 D
#define ASCII_45	KEY_E + SHIFT_MASK			// 69 E
#define ASCII_46	KEY_F + SHIFT_MASK			// 70 F
#define ASCII_47	KEY_G + SHIFT_MASK			// 71 G
#define ASCII_48	KEY_H + SHIFT_MASK			// 72 H
#define ASCII_49	KEY_I + SHIFT_MASK			// 73 I
#define ASCII_4A	KEY_J + SHIFT_MASK			// 74 J
#define ASCII_4B	KEY_K + SHIFT_MASK			// 75 K
#define ASCII_4C	KEY_L + SHIFT_MASK			// 76 L
#define ASCII_4D	KEY_SEMICOLON + SHIFT_MASK		// 77 M
#define ASCII_4E	KEY_N + SHIFT_MASK			// 78 N
#define ASCII_4F	KEY_O + SHIFT_MASK			// 79 O
#define ASCII_50	KEY_P + SHIFT_MASK			// 80 P
#define ASCII_51	KEY_A + SHIFT_MASK			// 81 Q
#define ASCII_52	KEY_R + SHIFT_MASK			// 82 R
#define ASCII_53	KEY_S + SHIFT_MASK			// 83 S
#define ASCII_54	KEY_T + SHIFT_MASK			// 84 T
#define ASCII_55	KEY_U + SHIFT_MASK			// 85 U
#define ASCII_56	KEY_V + SHIFT_MASK			// 86 V
#define ASCII_57	KEY_Z + SHIFT_MASK			// 87 W
#define ASCII_58	KEY_X + SHIFT_MASK			// 88 X
#define ASCII_59	KEY_Y + SHIFT_MASK			// 89 Y
#define ASCII_5A	KEY_W + SHIFT_MASK			// 90 Z
#define ASCII_5B	KEY_5 + ALTGR_MASK			// 91 [
#define ASCII_5C	KEY_8 + ALTGR_MASK			// 92
#define ASCII_5D	KEY_MINUS + ALTGR_MASK			// 93 ]
#define ASCII_5E	KEY_9 + ALTGR_MASK			// 94 ^
#define ASCII_5F	KEY_8					// 95 _
#define ASCII_60	GRAVE_ACCENT_BITS + KEY_SPACE		// 96 `
#define ASCII_61	KEY_Q					// 97 a
#define ASCII_62	KEY_B					// 98 b
#define ASCII_63	KEY_C					// 99 c
#define ASCII_64	KEY_D					// 100 d
#define ASCII_65	KEY_E					// 101 e
#define ASCII_66	KEY_F					// 102 f
#define ASCII_67	KEY_G					// 103 g
#define ASCII_68	KEY_H					// 104 h
#define ASCII_69	KEY_I					// 105 i
#define ASCII_6A	KEY_J					// 106 j
#define ASCII_6B	KEY_K					// 107 k
#define ASCII_6C	KEY_L					// 108 l
#define ASCII_6D	KEY_SEMICOLON				// 109 m
#define ASCII_6E	KEY_N					// 110 n
#define ASCII_6F	KEY_O					// 111 o
#define ASCII_70	KEY_P					// 112 p
#define ASCII_71	KEY_A					// 113 q
#define ASCII_72	KEY_R					// 114 r
#define ASCII_73	KEY_S					// 115 s
#define ASCII_74	KEY_T					// 116 t
#define ASCII_75	KEY_U					// 117 u
#define ASCII_76	KEY_V					// 118 v
#define ASCII_77	KEY_Z					// 119 w
#define ASCII_78	KEY_X					// 120 x
#define ASCII_79	KEY_Y					// 121 y
#define ASCII_7A	KEY_W					// 122 z
#define ASCII_7B	KEY_4 + ALTGR_MASK			// 123 {
#define ASCII_7C	KEY_6 + ALTGR_MASK			// 124 |
#define ASCII_7D	KEY_EQUAL + ALTGR_MASK			// 125 }
#define ASCII_7E	TILDE_BITS + KEY_SPACE			// 126 ~
#define ASCII_7F	KEY_BACKSPACE				// 127
#define ISO_8859_1_A0	KEY_SPACE				// 160       Nonbreakng Space
#define ISO_8859_1_A1	0					// 161 ¡     Inverted Exclamation
#define ISO_8859_1_A2	0					// 162 ¢     Cent SIGN
#define ISO_8859_1_A3	KEY_RIGHT_BRACE + SHIFT_MASK		// 163 £     Pound Sign
#define ISO_8859_1_A4	KEY_RIGHT_BRACE + ALTGR_MASK		// 164 ¤     Currency or Euro Sign
#define ISO_8859_1_A5	0					// 165 ¥     YEN SIGN
#define ISO_8859_1_A6	0					// 166 ¦     BROKEN BAR
#define ISO_8859_1_A7	KEY_SLASH + SHIFT_MASK			// 167 §     SECTION SIGN
#define ISO_8859_1_A8	DIAERESIS_BITS + KEY_SPACE		// 168 ¨     DIAERESIS
#define ISO_8859_1_A9	0					// 169 ©     COPYRIGHT SIGN
#define ISO_8859_1_AA	0					// 170 ª     FEMININE ORDINAL
#define ISO_8859_1_AB	0					// 171 «     LEFT DOUBLE ANGLE QUOTE
#define ISO_8859_1_AC	0					// 172 ¬     NOT SIGN
#define ISO_8859_1_AD	0					// 173       SOFT HYPHEN
#define ISO_8859_1_AE	0					// 174 ®     REGISTERED SIGN
#define ISO_8859_1_AF	0					// 175 ¯     MACRON
#define ISO_8859_1_B0	KEY_MINUS + SHIFT_MASK			// 176 °     DEGREE SIGN
#define ISO_8859_1_B1	0					// 177 ±     PLUS-MINUS SIGN
#define ISO_8859_1_B2	KEY_TILDE				// 178 ²     SUPERSCRIPT TWO
#define ISO_8859_1_B3	0					// 179 ³     SUPERSCRIPT THREE
#define ISO_8859_1_B4	0					// 180 ´     ACUTE ACCENT
#define ISO_8859_1_B5	KEY_BACKSLASH + SHIFT_MASK		// 181 µ     MICRO SIGN
#define ISO_8859_1_B6	0					// 182 ¶     PILCROW SIGN
#define ISO_8859_1_B7	0					// 183 ·     MIDDLE DOT
#define ISO_8859_1_B8	0					// 184 ¸     CEDILLA
#define ISO_8859_1_B9	0					// 185 ¹     SUPERSCRIPT ONE
#define ISO_8859_1_BA	0					// 186 º     MASCULINE ORDINAL
#define ISO_8859_1_BB	0					// 187 »     RIGHT DOUBLE ANGLE QUOTE
#define ISO_8859_1_BC	0					// 188 ¼     FRACTION ONE QUARTER
#define ISO_8859_1_BD	0					// 189 ½     FRACTION ONE HALF
#define ISO_8859_1_BE	0					// 190 ¾     FRACTION THREE QUARTERS
#define ISO_8859_1_BF	0					// 191 ¿     INVERTED QUESTION MARK
#define ISO_8859_1_C0	GRAVE_ACCENT_BITS + KEY_Q + SHIFT_MASK	// 192 À     A GRAVE
#define ISO_8859_1_C1	0					// 193 Á     A ACUTE
#define ISO_8859_1_C2	CIRCUMFLEX_BITS	+ KEY_Q + SHIFT_MASK	// 194 Â     A CIRCUMFLEX
#define ISO_8859_1_C3	TILDE_BITS + KEY_Q + SHIFT_MASK		// 195 Ã     A TILDE
#define ISO_8859_1_C4	DIAERESIS_BITS + KEY_Q + SHIFT_MASK	// 196 Ä     A DIAERESIS
#define ISO_8859_1_C5	0					// 197 Å     A RING ABOVE
#define ISO_8859_1_C6	0					// 198 Æ     AE
#define ISO_8859_1_C7	0					// 199 Ç     C CEDILLA
#define ISO_8859_1_C8	GRAVE_ACCENT_BITS + KEY_E + SHIFT_MASK	// 200 È     E GRAVE
#define ISO_8859_1_C9	0					// 201 É     E ACUTE
#define ISO_8859_1_CA	CIRCUMFLEX_BITS + KEY_E + SHIFT_MASK	// 202 Ê     E CIRCUMFLEX
#define ISO_8859_1_CB	DIAERESIS_BITS + KEY_E + SHIFT_MASK	// 203 Ë     E DIAERESIS
#define ISO_8859_1_CC	GRAVE_ACCENT_BITS + KEY_I + SHIFT_MASK	// 204 Ì     I GRAVE
#define ISO_8859_1_CD	0					// 205 Í     I ACUTE
#define ISO_8859_1_CE	CIRCUMFLEX_BITS + KEY_I + SHIFT_MASK	// 206 Î     I CIRCUMFLEX
#define ISO_8859_1_CF	DIAERESIS_BITS + KEY_I + SHIFT_MASK	// 207 Ï     I DIAERESIS
#define ISO_8859_1_D0	0					// 208 Ð     ETH
#define ISO_8859_1_D1	TILDE_BITS + KEY_N + SHIFT_MASK		// 209 Ñ     N TILDE
#define ISO_8859_1_D2	GRAVE_ACCENT_BITS + KEY_O + SHIFT_MASK	// 210 Ò     O GRAVE
#define ISO_8859_1_D3	0					// 211 Ó     O ACUTE
#define ISO_8859_1_D4	CIRCUMFLEX_BITS + KEY_O + SHIFT_MASK	// 212 Ô     O CIRCUMFLEX
#define ISO_8859_1_D5	TILDE_BITS + KEY_O + SHIFT_MASK		// 213 Õ     O TILDE
#define ISO_8859_1_D6	DIAERESIS_BITS + KEY_O + SHIFT_MASK	// 214 Ö     O DIAERESIS
#define ISO_8859_1_D7	0					// 215 ×     MULTIPLICATION
#define ISO_8859_1_D8	0					// 216 Ø     O STROKE
#define ISO_8859_1_D9	GRAVE_ACCENT_BITS + KEY_U + SHIFT_MASK	// 217 Ù     U GRAVE
#define ISO_8859_1_DA	0					// 218 Ú     U ACUTE
#define ISO_8859_1_DB	CIRCUMFLEX_BITS + KEY_U + SHIFT_MASK	// 219 Û     U CIRCUMFLEX
#define ISO_8859_1_DC	DIAERESIS_BITS + KEY_U			// 220 Ü     U DIAERESIS
#define ISO_8859_1_DD	0					// 221 Ý     Y ACUTE
#define ISO_8859_1_DE	0					// 222 Þ     THORN
#define ISO_8859_1_DF	0					// 223 ß     SHARP S
#define ISO_8859_1_E0	KEY_0					// 224 à     a GRAVE
#define ISO_8859_1_E1	0					// 225 á     a ACUTE
#define ISO_8859_1_E2	CIRCUMFLEX_BITS + KEY_Q			// 226 â     a CIRCUMFLEX
#define ISO_8859_1_E3	TILDE_BITS + KEY_Q			// 227 ã     a TILDE
#define ISO_8859_1_E4	DIAERESIS_BITS + KEY_Q			// 228 ä     a DIAERESIS
#define ISO_8859_1_E5	0					// 229 å     a RING ABOVE
#define ISO_8859_1_E6	0					// 230 æ     ae
#define ISO_8859_1_E7	KEY_9					// 231 ç     c CEDILLA
#define ISO_8859_1_E8	KEY_7					// 232 è     e GRAVE
#define ISO_8859_1_E9	KEY_2					// 233 é     e ACUTE
#define ISO_8859_1_EA	CIRCUMFLEX_BITS + KEY_E			// 234 ê     e CIRCUMFLEX
#define ISO_8859_1_EB	DIAERESIS_BITS + KEY_E			// 235 ë     e DIAERESIS
#define ISO_8859_1_EC	GRAVE_ACCENT_BITS + KEY_I		// 236 ì     i GRAVE
#define ISO_8859_1_ED	0					// 237 í     i ACUTE
#define ISO_8859_1_EE	CIRCUMFLEX_BITS + KEY_I			// 238 î     i CIRCUMFLEX
#define ISO_8859_1_EF	DIAERESIS_BITS + KEY_I			// 239 ï     i DIAERESIS
#define ISO_8859_1_F0	0					// 240 ð     ETH
#define ISO_8859_1_F1	TILDE_BITS + KEY_N			// 241 ñ     n TILDE
#define ISO_8859_1_F2	GRAVE_ACCENT_BITS + KEY_O		// 242 ò     o GRAVE
#define ISO_8859_1_F3	0					// 243 ó     o ACUTE
#define ISO_8859_1_F4	CIRCUMFLEX_BITS + KEY_O			// 244 ô     o CIRCUMFLEX
#define ISO_8859_1_F5	TILDE_BITS + KEY_O			// 245 õ     o TILDE
#define ISO_8859_1_F6	DIAERESIS_BITS + KEY_O			// 246 ö     o DIAERESIS
#define ISO_8859_1_F7	0					// 247 ÷     DIVISION
#define ISO_8859_1_F8	0					// 248 ø     o STROKE
#define ISO_8859_1_F9	KEY_SEMICOLON				// 249 ù     u GRAVE
#define ISO_8859_1_FA	0					// 250 ú     u ACUTE
#define ISO_8859_1_FB	CIRCUMFLEX_BITS + KEY_U			// 251 û     u CIRCUMFLEX
#define ISO_8859_1_FC	DIAERESIS_BITS + KEY_U			// 252 ü     u DIAERESIS
#define ISO_8859_1_FD	0					// 253 ý     y ACUTE
#define ISO_8859_1_FE	0					// 254 þ     THORN
#define ISO_8859_1_FF	DIAERESIS_BITS + KEY_Y			// 255 ÿ     y DIAERESIS
#define UNICODE_20AC	KEY_E + ALTGR_MASK			//     €     Euro Sign
// not yet implemented
#define UNICODE_EXTRA00	0x20AC
#define KEYCODE_EXTRA00	KEY_E + ALTGR_MASK			// 20AC €    Euro Sign







class DigiKeyboardDevice : public Print {
 public:
  DigiKeyboardDevice () {
    cli();
    usbDeviceDisconnect();
    _delay_ms(250);
    usbDeviceConnect();


    usbInit();
      
    sei();

    // TODO: Remove the next two lines once we fix
    //       missing first keystroke bug properly.
    memset(reportBuffer, 0, sizeof(reportBuffer));      
    usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
  }
    
  void update() {
    usbPoll();
  }
	
	// delay while updating until we are finished delaying
	void delay(long milli) {
		unsigned long last = millis();
	  while (milli > 0) {
	    unsigned long now = millis();
	    milli -= now - last;
	    last = now;
	    update();
	  }
	}
  
  //sendKeyStroke: sends a key press AND release
  void sendKeyStroke(byte keyStroke) {
    sendKeyStroke(keyStroke, 0);
  }

  //sendKeyStroke: sends a key press AND release with modifiers
  void sendKeyStroke(byte keyStroke, byte modifiers) {
	sendKeyPress(keyStroke, modifiers);
    // This stops endlessly repeating keystrokes:
	sendKeyPress(0,0);
  }

  //sendKeyPress: sends a key press only - no release
  //to release the key, send again with keyPress=0
  void sendKeyPress(byte keyPress) {
	sendKeyPress(keyPress, 0);
  }

  //sendKeyPress: sends a key press only, with modifiers - no release
  //to release the key, send again with keyPress=0
  void sendKeyPress(byte keyPress, byte modifiers) {
   	while (!usbInterruptIsReady()) {
      // Note: We wait until we can send keyPress
      //       so we know the previous keyPress was
      //       sent.
    	usbPoll();
    	_delay_ms(5);
    }
    
    memset(reportBuffer, 0, sizeof(reportBuffer));
		
    reportBuffer[0] = modifiers;
    reportBuffer[1] = keyPress;
    
    usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
  }
  
  size_t write(uint8_t chr) {
    if(chr == '<')
      sendKeyStroke(100);
    else if(chr == '>')
      sendKeyStroke(100, MOD_SHIFT_RIGHT);
    else
    {
      uint8_t data = pgm_read_byte_near(ascii_to_scan_code_table + (chr - 8));
      sendKeyStroke(data & 0b00111111, data >> 7 ? MOD_SHIFT_RIGHT : 0 | (data << 1) >> 7 ? MOD_ALT_RIGHT : 0);
    }
    
    return 1;
  }
    
  //private: TODO: Make friend?
  uchar    reportBuffer[2];    // buffer for HID reports [ 1 modifier byte + (len-1) key strokes]
  using Print::write;
};

DigiKeyboardDevice DigiKeyboard = DigiKeyboardDevice();

#ifdef __cplusplus
extern "C"{
#endif 
  // USB_PUBLIC uchar usbFunctionSetup
	uchar usbFunctionSetup(uchar data[8]) {
    usbRequest_t    *rq = (usbRequest_t *)((void *)data);

    usbMsgPtr = DigiKeyboard.reportBuffer; //
    if ((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS) {
      /* class request type */

      if (rq->bRequest == USBRQ_HID_GET_REPORT) {
				/* wValue: ReportType (highbyte), ReportID (lowbyte) */

				/* we only have one report type, so don't look at wValue */
        // TODO: Ensure it's okay not to return anything here?    
				return 0;

      } else if (rq->bRequest == USBRQ_HID_GET_IDLE) {
				//usbMsgPtr = &idleRate;
				//return 1;
				return 0;
				
      } else if (rq->bRequest == USBRQ_HID_SET_IDLE) {
				idleRate = rq->wValue.bytes[1];
				
      }
    } else {
      /* no vendor specific requests implemented */
    }
		
    return 0;
  }
#ifdef __cplusplus
} // extern "C"
#endif


#endif // __DigiKeyboard_h__
