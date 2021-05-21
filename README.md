# SMSinPDU
A c++ method to encode SMS in text mode to PDU mode. Can be used in Arduino and ESP32/ESP8266 microcontrollers.

Usage:

```cpp
String pdu = SMSinPDU("+989010000000", "Hellow World!");

>>> AT+CMGS=28
0011000C918909110300000000FF10C8329BFD065DDF72363904028140
```
