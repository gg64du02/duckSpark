#include <avr/pgmspace.h>
// Lookup table to convert ascii characters in to keyboard scan codes
// Format: most signifficant bit indicates if scan code should be sent with shift modifier
// remaining 7 bits are to be used as scan code number.

const unsigned char ascii_to_scan_code_table[] PROGMEM = {
  // /* ASCII:   0 */ 0,
  // /* ASCII:   1 */ 0,
  // /* ASCII:   2 */ 0,
  // /* ASCII:   3 */ 0,
  // /* ASCII:   4 */ 0,
  // /* ASCII:   5 */ 0,
  // /* ASCII:   6 */ 0,
  // /* ASCII:   7 */ 0,
  /* ASCII:   8 */ 42,
  /* ASCII:   9 */ 43,
  /* ASCII:  10 */ 0,//former value 40 (which is the Enter key) LN should be LF
  /* ASCII:  11 */ 0,
  /* ASCII:  12 */ 0,
  /* ASCII:  13 */ 0,//13 should be CR
  /* ASCII:  14 */ 0,
  /* ASCII:  15 */ 0,
  /* ASCII:  16 */ 0,
  /* ASCII:  17 */ 0,
  /* ASCII:  18 */ 0,
  /* ASCII:  19 */ 0,
  /* ASCII:  20 */ 0,
  /* ASCII:  21 */ 0,
  /* ASCII:  22 */ 0,
  /* ASCII:  23 */ 0,
  /* ASCII:  24 */ 0,
  /* ASCII:  25 */ 0,
  /* ASCII:  26 */ 0,
  /* ASCII:  27 */ 41,
  /* ASCII:  28 */ 0,
  /* ASCII:  29 */ 0,
  /* ASCII:  30 */ 0,
  /* ASCII:  31 */ 0,
  /* ASCII:  32 */ 44,
  /* ASCII:  33 */ 56,
  /* ASCII:  34 */ 32,
  /* ASCII:  35 */ 96,
  /* ASCII:  36 */ 48,
  /* ASCII:  37 */ 180,
  /* ASCII:  38 */ 30,
  /* ASCII:  39 */ 33,
  /* ASCII:  40 */ 34,
  /* ASCII:  41 */ 45,
  /* ASCII:  42 */ 49,
  /* ASCII:  43 */ 174,
  /* ASCII:  44 */ 16,
  /* ASCII:  45 */ 35,
  /* ASCII:  46 */ 182,
  /* ASCII:  47 */ 183,
  /* ASCII:  48 */ 167,
  /* ASCII:  49 */ 158,
  /* ASCII:  50 */ 159,
  /* ASCII:  51 */ 160,
  /* ASCII:  52 */ 161,
  /* ASCII:  53 */ 162,
  /* ASCII:  54 */ 163,
  /* ASCII:  55 */ 164,
  /* ASCII:  56 */ 165,
  /* ASCII:  57 */ 166,
  /* ASCII:  58 */ 55,
  /* ASCII:  59 */ 54,
  /* ASCII:  60 182*/ 100,//0 former gg64du02
  /* ASCII:  61 */ 46,
  /* ASCII:  62 183*/ 109,//0 former //f5 3e+1 //52 ù//101 backspace//7 d//89 1//25 v//86 -//1s//99 .//109 ' '//
  /* ASCII:  63 */ 144,
  /* ASCII:  64 */ 103,
  /* ASCII:  65 */ 148,
  /* ASCII:  66 */ 133,
  /* ASCII:  67 */ 134,
  /* ASCII:  68 */ 135,
  /* ASCII:  69 */ 136,
  /* ASCII:  70 */ 137,
  /* ASCII:  71 */ 138,
  /* ASCII:  72 */ 139,
  /* ASCII:  73 */ 140,
  /* ASCII:  74 */ 141,
  /* ASCII:  75 */ 142,
  /* ASCII:  76 */ 143,
  /* ASCII:  77 */ 179,
  /* ASCII:  78 */ 145,
  /* ASCII:  79 */ 146,
  /* ASCII:  80 */ 147,
  /* ASCII:  81 */ 132,
  /* ASCII:  82 */ 149,
  /* ASCII:  83 */ 150,
  /* ASCII:  84 */ 151,
  /* ASCII:  85 */ 152,
  /* ASCII:  86 */ 153,
  /* ASCII:  87 */ 157,
  /* ASCII:  88 */ 155,
  /* ASCII:  89 */ 156,
  /* ASCII:  90 */ 154,//z currently
  /* ASCII:  91 */ 98,
  /* ASCII:  92 */ 101,
  /* ASCII:  93 */ 109,
  /* ASCII:  94 */ 102,//102
  /* ASCII:  95 */ 37,
  /* ASCII:  96 */ 100,//100 scancode < 
  /* ASCII:  97 */ 20,//a ascii
  /* ASCII:  98 */ 5,
  /* ASCII:  99 */ 6,
  /* ASCII: 100 */ 7,
  /* ASCII: 101 */ 8,
  /* ASCII: 102 */ 9,
  /* ASCII: 103 */ 10,
  /* ASCII: 104 */ 11,
  /* ASCII: 105 */ 12,
  /* ASCII: 106 */ 13,
  /* ASCII: 107 */ 14,
  /* ASCII: 108 */ 15,
  /* ASCII: 109 */ 51,
  /* ASCII: 110 */ 17,
  /* ASCII: 111 */ 18,
  /* ASCII: 112 */ 19,
  /* ASCII: 113 */ 4,
  /* ASCII: 114 */ 21,
  /* ASCII: 115 */ 22,
  /* ASCII: 116 */ 23,
  /* ASCII: 117 */ 24,
  /* ASCII: 118 */ 25,
  /* ASCII: 119 */ 29,
  /* ASCII: 120 */ 27,
  /* ASCII: 121 */ 28,
  /* ASCII: 122 */ 26,
  /* ASCII: 123 */ 97,
  /* ASCII: 124 */ 99,
  /* ASCII: 125 */ 110,
  /* ASCII: 126 */ 95
};