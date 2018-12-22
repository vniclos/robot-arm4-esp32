// Use web server for download css styles sheet

#ifndef _WEB_CSS_H
#define _WEB_CSS_H
const char g_HTML_Web_CSS[] PROGMEM = R"=====(

.reversedRange {
  direction: rtl
}

td 
{
    text-align: center; 
    vertical-align: middle;
}

.slidecontainer {
    width: 80%;
}

.slider {
    -webkit-appearance: none;
    width: 100%;
    height: 25px;
    background: #d3d3d3;
    outline: none;
    opacity: 0.7;
    -webkit-transition: .2s;
    transition: opacity .2s;
    display:inline-box;
}

.slider:hover {
    opacity: 1;
}

.slider::-webkit-slider-thumb {
    -webkit-appearance: none;
    appearance: none;
    width: 25px;
    height: 25px;
    background: #4CAF50;
    cursor: pointer;
}

.slider::-moz-range-thumb {
    width: 25px;
    height: 25px;
    background: #4CAF50;
    cursor: pointer;
}

.box
{
  border-radius: 5px 5px 5px 5px;
-moz-border-radius: 5px 5px 5px 5px;
-webkit-border-radius: 5px 5px 5px 5px;
border: 1px solid #000000;
background-color:#dddddd;
padding:5px;
margin:5px;
margin-top:2rem;
  }
.msg{background-color:#333; color: #fff;}
.msgred{background-color:#333; color: #f00;}
.btn  {
    display: inline-block;
    width: 80px;
    height: 30px;
    background: #4E9CAF;
    padding: 10px;
    text-align: center;
    border-radius: 5px;
    color: white;
    font-weight: bold;
    margin-right:5px;
    margin-bottom:5px;
    text-decoration:none;
    font-size:1.2rem;
}
.mini {width:auto; padding: 5px;}


.loader{
  margin: 0 0 2em;
  height: 100px;
  width: 20%;
  text-align: center;
  padding: 1em;
  margin: 0 auto 1em;
  display: inline-block;
  vertical-align: top;
}



)=====";
#endif
