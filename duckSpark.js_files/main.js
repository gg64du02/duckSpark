jQuery(function() { // Wait for jQuery

  init();

  // Check if download button can be used
  try {
    var isFileSaverSupported = !!new Blob();
  } catch (e) {}

  // Hijack console.log and console.error
  (function(){
    var oldLog = console.log;
    console.log = function (message) {
      $(".console").val("  ℹ - " + message + '\n');
      $(".console").css("color", "#2b2b2b");
      $(".console").css("padding-top","16px");
      oldLog.apply(console, arguments);
    };
    var oldErrorLog = console.error;
    console.error = function (message) {
      $(".console").val("  ⚠ - " + message + '\n');
      $(".console").css("color", "#ff3434");
      $(".console").css("padding-top","16px");
      oldErrorLog.apply(console, arguments);
    };
  })();

  // Create a little duck translator
  Duck = new Dckuinojs();

  // Compile button
  $(".compile-but").click(function(e) {
    var duckOutput = Duck.toArduino($(".duckyscript").val());
	var numbers_of_character_lol = Duck.numbers_of_character;
	//console.log("numbers_of_character_lol:"+numbers_of_character_lol);
	
	if(numbers_of_character_lol>460){
		document.getElementById("RAM-info").style.color = "#ff0000";
		document.getElementById("RAM-info").innerHTML = "Warning, RAM used:" + numbers_of_character_lol + "bytes (raw guess)";
	}
	else{
		document.getElementById("RAM-info").style.color = "#000000";
		document.getElementById("RAM-info").innerHTML = "RAM used:" + numbers_of_character_lol + "bytes (raw guess)";
	}
	
	
	
    if (duckOutput !== false)
    {
      $(".arduino").val(duckOutput);
      if (isFileSaverSupported)
        enableDl(500); // Enable download button
		//$(".dl-but").val('test');
    }
    else {
      $(".arduino").val('An error occured, the compiler returned undefined content !');
      
	  //$(".RAM-inf").val("duckSpark.js" + "lol");
      disableDl(500); // Disable download button
	  //$(".dl-but").val('test');
    }
  });

  // Download popup
  $(".dl-but").click(function() {
    $("#dl-popup").fadeIn(400);
  });
  // Close ><
  $("#dl-popup .modal-content .close").click(function() {
    $("#dl-popup").fadeOut(400);
  });

  // Generate locale list
  var LocaleKeyboardjs = new LocaleKeyboard();
  $(LocaleKeyboardjs.listLocales()).each(function() {
    $("#locale-select").append($("<option>").attr('value',this).text(this));
  });

  // Fill filename area
  $("#dl-filename").val("duckSpark.js" + makeId(4));

  // Download button
  $("#start-dl").click(function() {
    // Check if all is ready
    if ($("#dl-filename").val() === "") {
      alert("You must enter a filename");
      return;
    }

    // Create a zip and download
    var sketchName = $("#dl-filename").val();
    var zipHandler = new JSZip();

    // Add the payload as .ino
    zipHandler.file(sketchName + "/" + sketchName + ".ino", $(".arduino").val());
    // Add readme
    zipHandler.file("readme", $.ajax({
      url: 'readme.default',
      mimeType: 'text/plain',
      type: 'get',
      success: function(data) {return data;}
    }));

    // Add custom version of Keyboard lib if needed
    if ($("#locale-select").find(":selected").text() !== "en_US") {
      // Set the locale
      LocaleKeyboardjs.setLocale($("#locale-select").find(":selected").text());

      // Append all to the zip
      zipHandler.file(sketchName + "/Keyboard.cpp", LocaleKeyboardjs.getSource());
      zipHandler.file(sketchName + "/Keyboard.h", LocaleKeyboardjs.getHeader());
    }

    // Download
    zipHandler.generateAsync({type:"blob"})
      .then(function(content) {
        saveAs(content, sketchName + ".zip");
      }
    );
  });
});

function init()
{
  // Init page

  // Disable download button by default
  disableDl(500);

  // Clear console
  $(".console").val("");
}

function disableDl(time) {
  $(".dl-but").addClass("disabled").removeClass("hoverable");
  $(".dl-but span i.fa-ban").fadeTo(time, 1);
}

function enableDl(time) {
  $(".dl-but").removeClass("disabled").addClass("hoverable");
  $(".dl-but span i.fa-ban").fadeTo(time, 0);
}

function makeId(idLenght)
{
  var text = "";
  var possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

  for( var i=0; i < idLenght; i++ )
    text += possible.charAt(Math.floor(Math.random() * possible.length));

  return text;
}
