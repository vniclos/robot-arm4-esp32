//javascripts

#ifndef _WEB_JS_H
#define _WEB_JS_H

const char g_HTML_Web_JS[] PROGMEM = R"=====(
function fnctakeaway(steep)
{ var url="/fnctakeaway?m="+steep;
 var oMsgSend=document.getElementById("scnMsgSend");
  oMsgSend.innerHTML="send "+url;
  fncGetHtml("scnMsgGet",url);
  
  }

function fnctakeawayleft ()
{var url="/fnctakeawayleft";
 var oMsgSend=document.getElementById("scnMsgSend");
  oMsgSend.innerHTML="send "+url;
  fncGetHtml("scnMsgGet",url);
  }
function fnctakeawayright ()
{var url="/fnctakeawayright";
 var oMsgSend=document.getElementById("scnMsgSend");
  oMsgSend.innerHTML="send "+url;
  fncGetHtml("scnMsgGet",url);
  }

  function fnctakeawaycenter ()
{var url="/fnctakeawaycenter";
 var oMsgSend=document.getElementById("scnMsgSend");
  oMsgSend.innerHTML="send "+url;
  fncGetHtml("scnMsgGet",url);
  }
  
function fnctakeawayclose ()
{var url="/fnctakeawayclose";
 var oMsgSend=document.getElementById("scnMsgSend");
  oMsgSend.innerHTML="send "+url;
  fncGetHtml("scnMsgGet",url);
  }
function fnctakeawayopen ()
{var url="/fnctakeawayopen";
 var oMsgSend=document.getElementById("scnMsgSend");
  oMsgSend.innerHTML="send "+url;
  fncGetHtml("scnMsgGet",url);
  }
  



function fncGo (pId)
{
  var sMotor="scnMotor"+pId;
  var sMotorTxt=sMotor+"Txt";
  var oMotor=document.getElementById(sMotor);
  var oMotorTxt=document.getElementById(sMotorTxt);
  var oMsgSend=document.getElementById("scnMsgSend");
  var sMotorValue=""+oMotor.value;
  var url="/fncmotorset?m="+pId+"&p=" +sMotorValue;
  oMsgSend.innerHTML="send "+url;
  fncGetHtml("scnMsgGet",url);
  }

function fncGetPosition()
{
console.log("fncGetPosition");
   var xhttp;
   var reply = "";
   pURL="/fncGetPosition";
    document.getElementById("scnMsgSend").innerHTML = pURL;
   
   
   xhttp = new XMLHttpRequest();
   xhttp.onreadystatechange = function() {
   if (xhttp.readyState == 4 && xhttp.status == 200) {
      var szReply="";
      szReply=""+ xhttp.responseText;
      var iValues = szReply.split(",");
      var motor0 = document.getElementById("scnMotor0");
      var motor1 = document.getElementById("scnMotor1");
      var motor2 = document.getElementById("scnMotor2");
      var motor3 = document.getElementById("scnMotor3");
      motor0.value=iValues[0];
      motor1.value=iValues[2];
      motor2.value=iValues[2];
      motor3.value=iValues[3];
       var date = new Date();
       var vTimeDate="<br/>"+date.toDateString()+ " "+date.toLocaleTimeString();
      document.getElementById("scnMsgGet").innerHTML = szReply+vTimeDate;
   }
  };
    xhttp.open("GET", pURL, true);
    xhttp.send();
  }

  function fncReset()
  {
     fncGetHtml( "scnMsgGet","/fncReset");
    }
function fncStatusGet()
{ 
 fncGetHtml( "scnMsgGet","/fncGetStatus");
return false;
}
function fncDebug()
{
 fncGetHtml( "msgDebug","/fncDebug");
  return false;
  }
function fncGetHtml(pDivTarget, pURL) {
  console.log("pDivTarget="+pDivTarget+"\n pURL= "+pURL);
   var xhttp;
   var reply = "";
   xhttp = new XMLHttpRequest();
   xhttp.onreadystatechange = function() {
    if (xhttp.readyState == 4 && xhttp.status == 200) {
       var date = new Date();
       var vTimeDate="<br/>"+date.toDateString()+ " "+date.toLocaleTimeString();
        console.log(vTimeDate);
        document.getElementById(pDivTarget).innerHTML = xhttp.responseText+ ".At: "+vTimeDate;
       }
    };
    xhttp.open("GET", pURL, true);
    xhttp.send();
}
function fncMsg(pDivTarget,msg)
{
  document.getElementById(pDivTarget).innerHTML =msg;
  return false;
  }
)=====";
#endif
