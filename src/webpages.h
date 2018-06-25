/**
 * File contents of "webpages.h" for DUMB2SMART
 *
 * This file is used to create the folowing webpages:
 * Root page ("/"), reset page ("/reset") and "page not found"
 */

 String getPage(){
   String page = "<!DOCTYPE html>";
   page += "<html lang='en'>";
   page +=   "<head>";
   page +=     "<meta charset='utf-8'>";
   page +=     "<meta http-equiv='X-UA-Compatible' content='IE=edge'>";
   page +=     "<meta name='viewport' content='width=device-width, initial-scale=1'>";
   page +=     "<meta http-equiv='refresh' content='15'/>";
   page +=     "<link rel='shortcut icon' href='data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAADAAAAAwCAYAAABXAvmHAAAABGdBTUEAALGPC/xhBQAAAAFzUkdCAK7OHOkAAAAgY0hSTQAAeiYAAICEAAD6AAAAgOgAAHUwAADqYAAAOpgAABdwnLpRPAAAAAZiS0dEAAAAAAAA+UO7fwAAAAlwSFlzAAAASAAAAEgARslrPgAAAyRJREFUaN7tmM1vDWEUxn/6QUhK4itxW6ErCQsSafEHSDStWAmxKhJKRCokysbdoHtCb22JpBo2SiyEv6FpoldYqK9ElbaKCnItZiamz7y9fWfuO23UfZJZnDnnPOc5M++8HwNllFHGf4Hqf7lmNdAHdM6i+CxwH6hyQZYDCv6VnSXxQb1rpZIdCJEF15EUxbcZ6u1LSrYS+Chkg/79tJAB3krNYWB5ErIuIZoANqYoPkAD8E1qX41LUgf8EJJ2Q1yjA8EmjtNSexKojUPaKQTPiM4Iu4HflPZhZ32OFrlfBeRFwyVb0krgjSS3SkwtME5ps1M2lD+GN/7DOCgahoAKG+IdkjgKLJaYG0Rf8foY4uuJDtGcxCyRh1TAcsiel6Sb4l8L/JKYtgRv4Lhw/CQ6zm9LTIeSmF7JVrGfir0Hb5gF6Ae6DU32+k9wHLgHbJCYHDAQsqt87jCezKDNiAHpukH8D8V/0iB+RGIKwCffF0a7xPSJf5v4+20a0OK6cOnsoGtDr0F8cPVI7CbxD4p/tfiHbRrQj2uh+PXDqpnBH77GJLZG/OPiXyT+SRVrNS05RME1oamBCbGXiv1ebB3Xj4vUeyT2OrHfib1M7C82DajAerFfir1T7A7gs4F3BG+LUCz3xQy1VZuxgbzYm8V+IPZh4cn7OXf4O432AFvwVvgAlX5uMW6trdqMOMfUD+eW+OvwFp1wzDEbYsEJ4bBZyM7aEG8nOnPoVqKb6OxQb0Puw7SV6JIY01aiwYa8Angtia0Sk/Ebc7WZGwXWiP+QaHhFjFnzMtEFRrfTLbjbTjfL/WrguWi4GIfYdKA5ZYgr9kp1EZsOJo4zRIdohpi4LiRf8ZZ+W9g2oGgEvkvulbjiAVYQPdTngVUpNlBL9FD/gYSHeoD9BiFHU2zA9Ftlb1LxAcJDKRsjL+kQyoZyYv+NMKESuAtciJmXtAHwFixnvxYh2Y/WUhqwrrnAVYfTNJB6LZfngWam/o4xNVTAW+Wb0mimVOj2o9g15Kqo6bU6PzU5xhTNs32kdI5yA/MJc/IRu0STZRNDwK65FltGGfMFfwB1P4cc2cai3gAAACV0RVh0ZGF0ZTpjcmVhdGUAMjAxNy0xMC0xM1QyMDo1OTo1MiswMDowMGf6eRAAAAAldEVYdGRhdGU6bW9kaWZ5ADIwMTctMTAtMTNUMjA6NTk6NTIrMDA6MDAWp8GsAAAAKHRFWHRzdmc6YmFzZS11cmkAZmlsZTovLy90bXAvbWFnaWNrLWZDN1pLU3MxVs1E8gAAAABJRU5ErkJggg=='>";
   page +=     "<title>";
   page +=       DEVICE_HOSTNAME;
   page +=     "</title>";
   page +=     "<link rel='stylesheet' href='//maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css' integrity='sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u' crossorigin='anonymous'>";
   page +=     "<link rel='stylesheet' href='//maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap-theme.min.css' integrity='sha384-rHyoN1iRsVXV4nD0JutlnGaslCJuC7uwjduW9SVrLvRYooPp2bWYgmgJQIXwl/Sp' crossorigin='anonymous'>";
   page +=     "<script src='//maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js' integrity='sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa' crossorigin='anonymous'></script>";
   page +=     "<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.0/jquery.min.js'></script>";
   page +=   "</head>";
   page +=   "<body>";
   page +=   "<p></p>";
   page +=     "<div class='container-fluid'>";
   page +=     "<div class='row'>";
   page +=       "<div class='col-md-12'>";
   page +=         "<div class='jumbotron'>";
   page +=           "<h2>";
   page +=             PROJ_VER;
   page +=           "</h2>";
   page +=           "<p>Readings from SDM120C energy meter.";
   page +=           "</p>";
   page +=         "</div>";
   page +=         "<div class='alert alert-info' role='alert'>";
   page +=           "<strong>This page auto-refreshes every 15 seconds!</strong> ";
   page +=         "</div>";
   page +=       "</div>";
   page +=     "</div>";


   page +=     "<div class='row'>";
   page +=       "<div class='col-md-4'>";
   page +=         "<h3 class='text-primary'>Volt</h3>";
   page +=           "<p class='lead'>";
   page +=             voltString;
   page +=           " V</p>";
   page +=         "</div>";
   page +=       "<div class='col-md-4'>";
   page +=         "<h3 class='text-primary'>Amp</h3>";
   page +=           "<p class='lead'>";
   page +=             ampString;
   page +=           " A</p>";
   page +=         "</div>";
   page +=       "<div class='col-md-4'>";
   page +=         "<h3 class='text-primary'>Watt</h3>";
   page +=           "<p class='lead'>";
   page +=             powerString;
   page +=           " W</p>";
   page +=         "</div>";
   page +=       "</div>";


   page +=     "<div class='row'>";
   page +=       "<div class='col-md-4'>";
   page +=         "<h4 class='text-primary'>Active Apparent Power</h3>";
   page +=           "<p class='lead'>";
   page +=             aapString;
   page +=           " VA</p>";
   page +=         "</div>";
   page +=       "<div class='col-md-4'>";
   page +=         "<h4 class='text-primary'>Reactive Apparent Power</h3>";
   page +=           "<p class='lead'>";
   page +=             rapString;
   page +=           " VAR</p>";
   page +=         "</div>";
   page +=       "<div class='col-md-4'>";
   page +=         "<h4 class='text-primary'>Power Factor</h3>";
   page +=           "<p class='lead'>";
   page +=             pfString;
   page +=           " pf</p>";
   page +=         "</div>";
   page +=       "</div>";


   page +=     "<div class='row'>";
   page +=       "<div class='col-md-4'>";
   page +=         "<h4 class='text-primary'>Frequency</h3>";
   page +=           "<p class='lead'>";
   page +=             freqString;
   page +=           " Hz</p>";
   page +=         "</div>";
   page +=       "<div class='col-md-4'>";
   page +=         "<h4 class='text-primary'>Import Active Energy</h3>";
   page +=           "<p class='lead'>";
   page +=             iaeString;
   page +=           " KWh</p>";
   page +=         "</div>";
   page +=       "<div class='col-md-4'>";
   page +=         "<h4 class='text-primary'>Export Active Energy</h3>";
   page +=           "<p class='lead'>";
   page +=             eaeString;
   page +=           " KWh</p>";
   page +=         "</div>";
   page +=       "</div>";


   page +=     "<div class='row'>";
   page +=       "<div class='col-md-4'>";
   page +=         "<h4 class='text-primary'>Total Active Energy</h3>";
   page +=           "<p class='lead'>";
   page +=             taeString;
   page +=           " KWh</p>";
   page +=         "</div>";
   //page +=       "<div class='col-md-4'>";
   //page +=         "<h4 class='text-primary'>AAA</h3>";
   //page +=           "<p class='lead'>";
   //page +=             aaa;
   //page +=           " X</p>";
   //page +=         "</div>";
   //page +=       "<div class='col-md-4'>";
   //page +=         "<h4 class='text-primary'>BBB</h3>";
   //page +=           "<p class='lead'>";
   //page +=             bbb;
   //page +=           " X</p>";
   //page +=         "</div>";
   page +=       "</div>";


   page +=       "<div class='row'>";
   page +=         "<div class='col-md-12'>";
   page +=           "<div class='alert alert-danger' role='alert'>";
   page +=             "<button type='button' class='close' data-dismiss='alert' aria-hidden='true'>×</button>";
   page +=           "<h5>Warning!</h4>Sometimes the board does not restart correctly. If you can't get back to this page after one minute, you need to reset on the board directly on the fisical reset button.&nbsp;&nbsp;";
   page +=           "<button type='button' class='btn btn-warning btn-default'>RESET</button>";
   page +=           "</div>";
   page +=         "</div>";
   page +=       "</div>";


   page +=       "<div class='row'>";
   page +=         "<div class='col-md-12'>";
   page +=           "<div class='alert alert-warning' role='alert'>";
   page +=             "<button type='button' class='close' data-dismiss='alert' aria-hidden='true'>×</button>";
   page +=           "<h5>Info!</h4>To flash another firmware, just click this button, choose the file and click Update&nbsp;&nbsp;";
   page +=           "<a href='/firmware'><button type='button' class='btn btn-warning btn-default'>OTA</button></a>";
   page +=           "</div>";
   page +=         "</div>";
   page +=       "</div>";


   page +=    "</div>";
   page +=     "<div class='col-md-12'>";
   page +=       "copyright <br/><br/>";
   page +=     "</div>";
   page += "</div>";
   page +=   "</body>";
   page += "</html>";
   return page;
}

void handleRoot() {                                                             // Handle "root" page
  server.send ( 200, "text/html", getPage() );
}

void handleReset() {                                                             // Handle "root" page
  ESP.restart();
}

void handleNotFound(){                                                          // Handle "not found" page
  String message = "Page or File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

// END
//********************************************************************************************************
