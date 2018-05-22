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

#define KEY_A       4
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
#define KEY_M       16
#define KEY_N       17
#define KEY_O       18
#define KEY_P       19
#define KEY_Q       20
#define KEY_R       21
#define KEY_S       22
#define KEY_T       23
#define KEY_U       24
#define KEY_V       25
#define KEY_W       26
#define KEY_X       27
#define KEY_Y       28
#define KEY_Z       29
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
/*
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

#define LEFTARROW 0x50
#define RIGHTARROW 0x4F
#define UPARROW  0x52
#define DOWNARROW    0x51

#define MODIFIERKEY_LEFT_GUI ( 0x08 | 0xE000 )

#define KEY_MENU ( 101  | 0xF000 )

#define BACKSPACE 42
*/



//=====================================================================

#define SHIFT_MASK		0x40
#define KEYCODE_TYPE		uint8_t
#define KEYCODE_MASK		0x007F

#define ASCII_20	KEY_SPACE				// 32  
#define ASCII_21	KEY_1 + SHIFT_MASK			// 33 !
#define ASCII_22	KEY_QUOTE + SHIFT_MASK			// 34 "
#define ASCII_23	KEY_3 + SHIFT_MASK			// 35 #
#define ASCII_24	KEY_4 + SHIFT_MASK			// 36 $
#define ASCII_25	KEY_5 + SHIFT_MASK			// 37 %
#define ASCII_26	KEY_7 + SHIFT_MASK			// 38 &
#define ASCII_27	KEY_QUOTE				// 39 '
#define ASCII_28	KEY_9 + SHIFT_MASK			// 40 (
#define ASCII_29	KEY_0 + SHIFT_MASK			// 41 )
#define ASCII_2A	KEY_8 + SHIFT_MASK			// 42 *
#define ASCII_2B	KEY_EQUAL + SHIFT_MASK			// 43 +
#define ASCII_2C	KEY_COMMA				// 44 ,
#define ASCII_2D	KEY_MINUS				// 45 -
#define ASCII_2E	KEY_PERIOD				// 46 .
#define ASCII_2F	KEY_SLASH				// 47 /
#define ASCII_30	KEY_0					// 48 0
#define ASCII_31	KEY_1					// 49 1
#define ASCII_32	KEY_2					// 50 2
#define ASCII_33	KEY_3					// 51 3
#define ASCII_34	KEY_4					// 52 4
#define ASCII_35	KEY_5					// 53 5
#define ASCII_36	KEY_6					// 54 6
#define ASCII_37	KEY_7					// 55 7
#define ASCII_38	KEY_8					// 55 8
#define ASCII_39	KEY_9					// 57 9
#define ASCII_3A	KEY_SEMICOLON + SHIFT_MASK		// 58 :
#define ASCII_3B	KEY_SEMICOLON				// 59 ;
#define ASCII_3C	KEY_COMMA + SHIFT_MASK			// 60 <
#define ASCII_3D	KEY_EQUAL				// 61 =
#define ASCII_3E	KEY_PERIOD + SHIFT_MASK			// 62 >
#define ASCII_3F	KEY_SLASH + SHIFT_MASK			// 63 ?
#define ASCII_40	KEY_2 + SHIFT_MASK			// 64 @
#define ASCII_41	KEY_A + SHIFT_MASK			// 65 A
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
#define ASCII_4D	KEY_M + SHIFT_MASK			// 77 M
#define ASCII_4E	KEY_N + SHIFT_MASK			// 78 N
#define ASCII_4F	KEY_O + SHIFT_MASK			// 79 O
#define ASCII_50	KEY_P + SHIFT_MASK			// 80 P
#define ASCII_51	KEY_Q + SHIFT_MASK			// 81 Q
#define ASCII_52	KEY_R + SHIFT_MASK			// 82 R
#define ASCII_53	KEY_S + SHIFT_MASK			// 83 S
#define ASCII_54	KEY_T + SHIFT_MASK			// 84 T
#define ASCII_55	KEY_U + SHIFT_MASK			// 85 U
#define ASCII_56	KEY_V + SHIFT_MASK			// 86 V
#define ASCII_57	KEY_W + SHIFT_MASK			// 87 W
#define ASCII_58	KEY_X + SHIFT_MASK			// 88 X
#define ASCII_59	KEY_Y + SHIFT_MASK			// 89 Y
#define ASCII_5A	KEY_Z + SHIFT_MASK			// 90 Z
#define ASCII_5B	KEY_LEFT_BRACE				// 91 [
#define ASCII_5C	KEY_BACKSLASH				// 92
#define ASCII_5D	KEY_RIGHT_BRACE				// 93 ]
#define ASCII_5E	KEY_6 + SHIFT_MASK			// 94 ^
#define ASCII_5F	KEY_MINUS + SHIFT_MASK			// 95 _
#define ASCII_60	KEY_TILDE				// 96 `
#define ASCII_61	KEY_A					// 97 a
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
#define ASCII_6D	KEY_M					// 109 m
#define ASCII_6E	KEY_N					// 110 n
#define ASCII_6F	KEY_O					// 111 o
#define ASCII_70	KEY_P					// 112 p
#define ASCII_71	KEY_Q					// 113 q
#define ASCII_72	KEY_R					// 114 r
#define ASCII_73	KEY_S					// 115 s
#define ASCII_74	KEY_T					// 116 t
#define ASCII_75	KEY_U					// 117 u
#define ASCII_76	KEY_V					// 118 v
#define ASCII_77	KEY_W					// 119 w
#define ASCII_78	KEY_X					// 120 x
#define ASCII_79	KEY_Y					// 121 y
#define ASCII_7A	KEY_Z					// 122 z
#define ASCII_7B	KEY_LEFT_BRACE + SHIFT_MASK		// 123 {
#define ASCII_7C	KEY_BACKSLASH + SHIFT_MASK		// 124 |
#define ASCII_7D	KEY_RIGHT_BRACE + SHIFT_MASK		// 125 }
#define ASCII_7E	KEY_TILDE + SHIFT_MASK			// 126 ~
#define ASCII_7F	KEY_BACKSPACE				// 127


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


// Everything below this line is not intended for use in "normal" programs.
// These private symbols populate lookup tables, which are used to translate
// ascii and UTF8 unicode into keystroke sequences.

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
    uint8_t data = pgm_read_byte_near(ascii_to_scan_code_table + (chr - 8));
    sendKeyStroke(data & 0b01111111, data >> 7 ? MOD_SHIFT_RIGHT : 0);
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
