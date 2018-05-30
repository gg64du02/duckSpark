/*
 *  Dckuino.js, an open source project licenced under MIT License
 *  Based on Dckuino.js, an open source project licenced under MIT License
 *  Modified by gg64du02
 */

/* jshint esversion: 6 */


var commandMap = { // Key that can be typed
  CONTROL:'MOD_CONTROL_LEFT', //former: KEY_LEFT_CTRL
  ESCAPE:'KEY_ESC',
  ESC:'KEY_LEFT_ESC',
  GUI:'MOD_GUI_LEFT',	//ok
  WINDOWS:'MOD_GUI_LEFT',	//ok
  COMMAND:'MODIFIERKEY_GUI',	//ok
  MENU:'KEY_MENU',
  APP:'KEY_MENU',
  END:'KEY_END',
  SPACE:'KEY_SPACE',	//ok
  TAB:'KEY_TAB',
  PRINTSCREEN:'KEY_PRINTSCREEN',
  ENTER:'KEY_ENTER',	//ok
  RETURN:'KEY_ENTER',	//ok
  UPARROW:'KEY_UP_ARROW',
  DOWNARROW:'KEY_DOWN_ARROW',
  LEFTARROW:'KEY_LEFT_ARROW',
  RIGHTARROW:'KEY_RIGHT_ARROW',
  UP:'KEY_UP_ARROW',
  DOWN:'KEY_DOWN_ARROW',
  LEFT:'KEY_LEFT_ARROW',
  RIGHT:'KEY_RIGHT_ARROW',
  CAPSLOCK:'KEY_CAPS_LOCK',
  DELETE:'KEY_DELETE',
  DEL:'KEY_DELETE',
  F1:'KEY_F1',	//ok
  F2:'KEY_F2',	//ok
  F3:'KEY_F3',	//ok
  F4:'KEY_F4',	//ok
  F5:'KEY_F5',	//ok
  F6:'KEY_F6',	//ok
  F7:'KEY_F7',	//ok
  F8:'KEY_F8',	//ok
  F9:'KEY_F9',	//ok
  F10:'KEY_F10',	//ok
  F11:'KEY_F11',	//ok
  F12:'KEY_F12',	//ok
  PAGEUP:'KEY_PAGE_UP',
  PAGEDOWN:'KEY_PAGE_DOWN',
  BACKSPACE:'KEY_BACKSPACE'//added by gg
  
 
};


var comboMap = { // Key that can only be used in combos
  //ESCAPE:'KEY_LEFT_ESC',
  ALT:'MOD_ALT_LEFT',
  SHIFT:'MOD_SHIFT_LEFT',
  CTRL:'MOD_CONTROL_LEFT',
  CONTROL:'MOD_CONTROL_LEFT' //former: KEY_LEFT_CTRL
};


var keyMap = { // Normal keys
  //ESCAPE:'KEY_LEFT_ESC',
  a:'KEY_A',
  b:'KEY_B',
  c:'KEY_C',
  d:'KEY_D',
  e:'KEY_E',
  f:'KEY_F',
  g:'KEY_G',
  h:'KEY_H',
  i:'KEY_I',
  j:'KEY_J',
  k:'KEY_K',
  l:'KEY_L',
  m:'KEY_M',
  n:'KEY_N',
  o:'KEY_O',
  p:'KEY_P',
  q:'KEY_Q',
  r:'KEY_R',
  s:'KEY_S',
  t:'KEY_T',
  u:'KEY_U',
  v:'KEY_V',
  w:'KEY_W',
  x:'KEY_X',
  y:'KEY_Y',
  z:'KEY_Z'
};


	
//gg64du02
//debugger purpose
var numbers_of_character = 0;

class Dckuinojs {
  constructor() {
    this.keyMap = keyMap;
    this.commandMap = commandMap;
    this.comboMap = comboMap;
	this.numbers_of_character;
  }

  toArduino(inputCode)
  {
    // Check if the parameter is empty or undefined
    if (inputCode === '' || inputCode === undefined)
    {
      console.error('Error: No ducky script was entered !');
      return false;
    }  // Parsing

    var parsedDucky = this._parse(inputCode);
    if (parsedDucky === '' || parsedDucky === undefined)
    {
      return false;
    }  // Returning the total uploadable script
	
	//parsedDucky;
	//gg64du02
	//use: https://stackoverflow.com/questions/4009756/how-to-count-string-occurrence-in-string
	//How to count string occurrence in string?
	var temp = "This is a string.";
	var count = (temp.match(/is/g) || []).length;
	//console.log("count:"+count);
	
	
	// console.log("DigiKeyboard.h:"+"1");
	// console.log("setup:"+"1");
	// console.log("pinmode:"+"2");
	
	var count_delay = (parsedDucky.match(/DigiKeyboard.delay/g) || []).length;
	//console.log("delay:"+count_delay);
	var count_delay_corrected  = count_delay+1;
	
	var count_sendKeyStroke = (parsedDucky.match(/DigiKeyboard.sendKeyStroke/g) || []).length;
	// console.log("sendKeyStroke:"+count_sendKeyStroke);
	
	var count_println = (parsedDucky.match(/DigiKeyboard.println/g) || []).length;
	// console.log("println:"+count_println);
	
	
	// console.log("numbers_of_character (println):"+numbers_of_character);
	
	var test_RAM_used = 88 + 0 * count_delay_corrected + 0* count_sendKeyStroke;
	//test_RAM_used += 2* count_println + 1* numbers_of_character;
	test_RAM_used += 0* count_println + 1* numbers_of_character;
	// console.log("test_RAM_used:"+test_RAM_used)
	this.numbers_of_character = test_RAM_used;
	
	  
	//$(".RAM-inf").val("duckSpark.js" + "lol");
	//document.getElementById('RAM-inf').innerHTML = 'John Doe';
	
	
    return '/*\n'
    + ' * Generated with <3 by Dckuino.js, an open source project ! Please check the Nurrl github, and style sheet from Seytonic`s website Modified by gg64du02\n'
    + ' */\n\n'
    + '#include "DigiKeyboard.h"\n\n'
	+ '\n\n'
    + '\n'
    + 'void setup()\n'
    + '{\n'
    + '  pinMode(1, OUTPUT); //LED on Model A\n'
    + '  digitalWrite(1, LOW); //turn off led when program start\n\n'
    + '  //INIT\n'
	+ '  DigiKeyboard.sendKeyStroke(0);\n'
	+ '  DigiKeyboard.delay(3000);\n'
    + '\n' + parsedDucky
	+ '  digitalWrite(1, HIGH); //turn on led when program end\n'
    + '}\n\n'
    + '/* Unused endless loop */\n'
    + 'void loop() {}';
  }

  // The parsing function
   _parse(toParse)
  {
    // Init chronometer
    var timerStart = Date.now();

    var parsedScript = '';
    var lastLines;
    var lastCount;

    // Trim whitespaces
    toParse = toParse.replace(/^ +| +$/gm, '');

    // Remove all *ugly* tabs
    toParse = toParse.replace(/\t/g, '');

    // Cuting the input in lines
    var lineArray = toParse.split('\n');
	
	//gg64du02
	//debugger purpose
	numbers_of_character = 0;

    // Loop every line
    for (var i = 0; i < lineArray.length; i++)
    {
      // Line empty, skip
      if (lineArray[i] === '' || lineArray[i] === '\n')
      {
        console.log('Info: Skipped line ' + (i + 1) + ', because was empty.');
        continue;
      }

      // Var who indicates to release all at the line end
      var releaseAll = false;

      // Outputs, for REPLAY/REPEAT COMMANDS
      if (parsedOut !== undefined && parsedOut !== '')
      {
        lastLines = parsedOut;
        lastCount = ((lastLines.split('\n')).length + 1);
      }
      var parsedOut = '';

      // Command known
      var commandKnown = false;

      // Cutting every line in words
      var wordArray = lineArray[i].split(' ');
      var wordOne = wordArray[0];

      // Handle commands
      switch(wordOne){
        case "STRING":
          wordArray.shift();

          var textString = wordArray.join(' ');

          // Replace all '"' by '\"' and all '\' by '\\'
          textString = textString.split('\\').join('\\\\').split('"').join('\\"');
          if (textString !== '')
          {
            parsedOut += '  DigiKeyboard.println("' + textString + '");\n';
            commandKnown = true;
			//gg64du02
			//debugger purpose
			numbers_of_character = numbers_of_character + textString.length;
          } else {
            console.error('Error: at line: ' + (i + 1) + ', STRING needs a text');
            return;
          }
          break;
        case "DELAY":
          wordArray.shift();

          if(wordArray[0] === undefined || wordArray[0] === '') {
            console.error('Error: at line: ' + (i + 1) + ', DELAY needs a time');
            return;
          }

          if (! isNaN(wordArray[0]))
          {
            parsedOut += '  DigiKeyboard.delay(' + wordArray[0] + ');\n';
            commandKnown = true;
          } else {
            console.error('Error: at line: ' + (i + 1) + ', DELAY only acceptes numbers');
            return;
          }
          break;
        case "TYPE":
          wordArray.shift();

          if(wordArray[0] === undefined || wordArray[0] === '') {
            console.error('Error: at line: ' + (i + 1) + ', TYPE needs a key');
            return;
          }

          if (keyMap[wordArray[0]] !== undefined)
          {
            commandKnown = true;
            // Replace the DuckyScript key by the Arduino key name
			// type a command/modifiers key
            parsedOut += '  DigiKeyboard.sendKeyStroke(' + keyMap[wordArray[0]] + ');\n';
			
          } else {
            console.error('Error: Unknown letter \'' + wordArray[0] +'\' at line: ' + (i + 1));
            return;
          }
          break;
        case "REM":
          wordArray.shift();

          // Placing the comment to arduino code
          if (wordArray.length > 0)
          {
            commandKnown = true;
            parsedOut += '  // ' + wordArray.join(' ');
            if (i == (lineArray.length - 1))
              parsedOut += '\n';
          } else {
            console.error('Error: at line: ' + (i + 1) + ', REM needs a comment');
            return;
          }
          break;
        case "REPEAT":
        case "REPLAY":
          wordArray.shift();

          if (wordArray[0] === undefined || wordArray[0] === '') {
            console.error('Error: at line: ' + (i + 1) + ', REPEAT/REPLAY needs a loop count');
            return;
          }

          if (lastLines === undefined)
          {
            console.error('Error: at line: ' + (i + 1) + ', nothing to repeat, this is the first line.');
            return;
          }

          if (! isNaN(wordArray[0]))
          {
            // Remove the lines we just created
            var linesTmp = parsedScript.split('\n');
            linesTmp.splice(-lastCount, lastCount);

            if (linesTmp.join('\n') === '')
              parsedScript = linesTmp.join('\n');
            else {
              parsedScript = linesTmp.join('\n') + '\n';
            }

            // Add two spaces at Begining
            lastLines = lastLines.replace(/^  /gm,'    ');

            // Replace them
            parsedOut += '  for(int i = 0; i < ' + wordArray[0] + '; i++) {\n';
            parsedOut += lastLines;
            parsedOut += '  }\n';

            commandKnown = true;
          } else {
            console.error('Error: at line: ' + (i + 1) + ', REPEAT/REPLAY only acceptes numbers');
            return;
          }
          break;
        default:
          if (wordArray.length == 1)
          {
            if (comboMap[wordArray[0]] !== undefined)
            {
              commandKnown = true;

              parsedOut += '  DigiKeyboard.sendKeyStroke(0,' + comboMap[wordArray[0]] + ');\n';
			  parsedOut +='  DigiKeyboard.sendKeyStroke(0);'
            }else if (commandMap[wordArray[0]] !== undefined) {
              commandKnown = true;
			  if(commandMap[wordArray[0]] === 'MOD_GUI_LEFT'){
				  //to get the windows press key alone if you need to.
				parsedOut += '  DigiKeyboard.sendKeyStroke(0,' + commandMap[wordArray[0]] + ');\n';
				
			  }
			  else{
				parsedOut += '  DigiKeyboard.sendKeyStroke(' + commandMap[wordArray[0]] + ');\n';
			  }
            }else {
              commandKnown = false;
              break;
            }
            wordArray.shift();
          }
		  
		  var tmpStringGG = '';
          while (wordArray.length){
			  
			  //note: DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT); //run
			  //console.log(string.indexOf(substring) !== -1);
			  
			 //gg64du02 2018
			console.log("wordArray[0]:"+wordArray[0]);
			console.log("wordArray[1]:"+wordArray[1]);
			console.log("comboMap[wordArray[0]]:"+comboMap[wordArray[0]]);
			console.log("comboMap[wordArray[1]]:"+comboMap[wordArray[1]]);
			console.log("commandMap[wordArray[0]]:"+commandMap[wordArray[0]]);
			console.log("commandMap[wordArray[1]]:"+commandMap[wordArray[1]]);
			console.log("wordArray.length:"+wordArray.length);
			
			if (comboMap[wordArray[0]] !== undefined)
            {
				
				if(wordArray.length == 2){
					 if ( ((wordArray[0] == 'CONTROL')|(wordArray[0] == 'CTRL')) &  ((wordArray[1] == 'ESC')|(wordArray[1] == 'ESCAPE')) ){
						//comboMap
						//commandMap
						commandKnown = true;
						releaseAll = true;
						//console.log("test");
						tmpStringGG = '';
						tmpStringGG = '  DigiKeyboard.sendKeyStroke('+commandMap[wordArray[1]] ;
						tmpStringGG = tmpStringGG+ ', ' + comboMap[wordArray[0]] +');\n';
						//parsedOut += tmpStringGG;
					 }
					 else{
						//do nothing
						commandKnown = true;
						releaseAll = true;
						tmpStringGG = ',' + comboMap[wordArray[0]] + tmpStringGG + ');\n';
						//gg64du02: debugging purpose
						//console.log(tmpStringGG);
						//parsedOut += '  Keyboard.press(' + comboMap[wordArray[0]] + comboMap[wordArray[1]] + ');\n';
					 }
				}
				else{
					//do nothing
				  commandKnown = true;
				  releaseAll = true;
					tmpStringGG = ',' + comboMap[wordArray[0]] + tmpStringGG + ');\n';
					//gg64du02: debugging purpose
					//console.log(tmpStringGG);
					//parsedOut += '  Keyboard.press(' + comboMap[wordArray[0]] + comboMap[wordArray[1]] + ');\n';
				}
			  
            }else if (commandMap[wordArray[0]] !== undefined) {
              commandKnown = true;
              releaseAll = true;
				tmpStringGG = ',' + commandMap[wordArray[0]] + ');\n';
				//gg64du02: debugging purpose
				//console.log(tmpStringGG);
				//parsedOut += '  Keyboard.press(' + commandMap[wordArray[0]] + commandMap[wordArray[1] + ');\n';
				
            }else if (keyMap[wordArray[0]] !== undefined) {
              commandKnown = true;
              releaseAll = true;
				tmpStringGG = '  DigiKeyboard.sendKeyStroke(' + keyMap[wordArray[0]] + tmpStringGG;
				//gg64du02: debugging purpose
				//console.log(tmpStringGG);
				//parsedOut += '  Keyboard.press(\'' + keyMap[wordArray[0]] + keyMap[wordArray[0]] + '\');\n';
				
				
				//gg64du02
             }else if ((wordArray[0] == 'CTRL-SHIFT')& (commandMap[wordArray[1]] !== undefined)){
              commandKnown = true;
              releaseAll = true;
				tmpStringGG = '  DigiKeyboard.sendKeyStroke('+commandMap[wordArray[1]] ;
				tmpStringGG = tmpStringGG+ ', MODIFIERKEY_LEFT_CTRL_LEFT_SHIFT);\n';
				console.log(',MODIFIERKEY_LEFT_CTRL_LEFT_SHIFT');
				
				parsedOut += tmpStringGG;
			
			/* }else if ( ((wordArray[0] == 'CONTROL')|(wordArray[0] == 'CTRL')) &  ((wordArray[1] == 'ESC')|(wordArray[1] == 'ESCAPE')) ){
              //comboMap
			  //commandMap
			  commandKnown = true;
              releaseAll = true;
				console.log("test");
				tmpStringGG = '  DigiKeyboard.sendKeyStroke('+commandMap[wordArray[1]] ;
				tmpStringGG = tmpStringGG+ ', ' + comboMap[wordArray[0]] +');\n';
				parsedOut += tmpStringGG;
			*/
			
            }else {
              commandKnown = false;
              break;
            }
			//gg64du02
			 if (keyMap[wordArray[0]] !== undefined) {
				parsedOut += tmpStringGG;
			 }
			 
			 if (comboMap[wordArray[0]] !== undefined) {
				 var substring = 'DigiKeyboard';
				if(tmpStringGG.indexOf(substring) !== -1){
					parsedOut += tmpStringGG;
				 }
			 }
			 
            
			wordArray.shift();
			
          }
      }

      if (!commandKnown)
      {
        // console.error("\n" + "123" + "\n" + 'Error: Unknown command or key \'' + wordArray[0] + '\' at line: ' + (i + 1) + '.');
        console.error('Error: Unknown command or key \'' + wordArray[0] + '\' at line: ' + (i + 1) + '.');
        return;
      }

      parsedScript += parsedOut; // Add what we parsed
      parsedScript += '\n'; // Add new line
    }

    var timerEnd = Date.now();
    var timePassed = new Date(timerEnd - timerStart);

    console.log('Done parsed :' + (lineArray.length) + ' lines in ' + timePassed.getMilliseconds() + 'ms');
    return parsedScript;
  }
}
