

// web server manin page root,
// has user robot interface
#ifndef _WEB_ROOT_H
#define _WEB_ROOT_H

const char g_HTML_Web_root[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<meta name=viewport content="width=device-width, initial-scale=1">
<link rel="stylesheet" type="text/css" href="/css.css">
<script src="/js.js"></script>
<title>IotFrog arm-4x  </title>
</head>
<body>
<form>
<table width="95%"><tr>
<td width="%50"> <img  style="display: inline-block; width:64px; float:right" src="data:image/png;base64,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" alt=""></td>
<td width="%50"><h2>Robot IOT Arms 4 axis v1.1 </h2></td>
</tr></table>
<div class="box">
  <table width="95%">
    <tr>
      <td class="center" ><b>Motor Num</b></td>
      <td class="center"><b>Move to</b></td>
      <td class="center"  width="15rem"><b>Press button</b></td>
      <td class="center" width="5rem"><b>Valor</b></td>
    </tr>
    <tr>
      <td >Turn </td>
      
      <td><input id="scnMotor0"  width="100%"  type="range"   min="0" max="180" value="0" class="slider" ></td>
      <td class="center" ><input id="scnbtnMotor0" type="button"  value="Go" class="btn mini"  onclick="fncGo(0);return false;"></td>
      <td class="center" ><span id="scnMotor0Txt"></span></td>
    </tr>
    <tr>
      <td >Arm 1</td>
      
      <td><input id="scnMotor1"  width="100%"  type="range"   min="0" max="180" value="0" class="slider" ></td>
      <td class="center" ><input id="scnbtnMotor1" type="button"  value="Go" class="btn mini"  onclick="fncGo(1);return false;"></td>
    <td class="center" ><span id="scnMotor1Txt"></span></td>
    </tr>
    
    
    <tr>
      <td >Arm 2</td>
       <td><input id="scnMotor2"  width="100%"  type="range"   min="0" max="180" value="0" class="slider reversedRange" ></td>
     <td class="center" ><input id="scnbtnMotor2" type="button"  value="Go" class="btn mini"  onclick="fncGo(2);return false;"></td>
    <td class="center" ><span id="scnMotor2Txt"></span></td>
    </tr>
    
    <tr>
      <td>Finger</td>
      
      <td><input id="scnMotor3" width="100%" type="range" min="48" max="68" value="0" class="slider reversedRange" ></td>
     <td class="center" ><input id="scnbtnMotor3" type="button"  value="Go" class="btn mini "  onclick="fncGo(3);return false;"></td>
    <td class="center" ><span id="scnMotor3Txt"></span></td>
    </tr>
  </table>
</div>
</div>

<div class="box">
<h3>Take away</h3>
<input type="button" class="btn mini" value="1 Init" onclick="fnctakeaway(1);return false;" />
<input type="button" class="btn mini" value="2 Take" onclick="fnctakeaway(2);return false;" />
<input type="button" class="btn mini" value="3 Up" onclick="fnctakeaway(3);return false;" />
<input type="button" class="btn mini" value="4 Down" onclick="fnctakeaway(4);return false;" />

<input type="button" class="btn mini" value="Close" onclick="fnctakeawayclose();return false;" />
<input type="button" class="btn mini" value="Open" onclick="fnctakeawayopen();return false;" />
<input type="button" class="btn mini" value="Left" onclick="fnctakeawayleft();return false;" />
<input type="button" class="btn mini" value="Center" onclick="fnctakeawaycenter();return false;" />
<input type="button" class="btn mini" value="Right" onclick="fnctakeawayright();return false;" />
</div>  
<div class="box">
<h3>Tools & Messages<h3>
<input type="button" class="btn mini" value="Get Position" onclick="fncGetPosition();return false;" />
<input type="button" class="btn mini" value="Debug" onclick="fncStatusGet();return false;" />
<input type="button" class="btn mini" value="Config" onclick="window.location.href='/_ac'" />
<input type="button" class="btn mini" value="Reset" onclick="fncReset();return false;" />
  
<div ><span clas="msgtit">Sended:</span><span id="scnMsgSend" class="msg">.</span> </div>
<div ><span clas="msgtit">Recived:</span><span id="scnMsgGet" class="msg">.</span> </div>

</div>
<script>
if (document.readyState === 'complete') {
}
</script>
</form> 
<script>
 setInterval(fncGetPosition, 60000);

var motor0 = document.getElementById("scnMotor0");
var motor1 = document.getElementById("scnMotor1");
var motor2 = document.getElementById("scnMotor2");
var motor3 = document.getElementById("scnMotor3");

var motor0Txt = document.getElementById("scnMotor0Txt");
var motor1Txt = document.getElementById("scnMotor1Txt");
var motor2Txt = document.getElementById("scnMotor2Txt");
var motor3Txt = document.getElementById("scnMotor3Txt");

motor0Txt.innerHTML = motor0.value;
motor1Txt.innerHTML = motor1.value;
motor2Txt.innerHTML = motor2.value;
motor3Txt.innerHTML = motor3.value;

motor0.oninput = function() { motor0Txt.innerHTML = this.value;}
motor1.oninput = function() { motor1Txt.innerHTML = this.value;}
motor2.oninput = function() { motor2Txt.innerHTML = this.value;}
motor3.oninput = function() { motor3Txt.innerHTML = this.value;}


fncGetPosition();  
</script>

</body>

</html>
)=====";
#endif
