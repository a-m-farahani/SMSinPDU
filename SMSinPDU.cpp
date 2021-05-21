// This method is implemented for Microcontrollers such as Arduino and ESP32/ESP8266 which support String data type(Arduino Language).

String SMSinPDU(String phoneNumber, String msg){
    // SMSinPDU takes a Phone number in international format, for example +98xxxxxxxxxx for Iran
    // and a text message and converts them to PDU(Protocol Data Unit) coding. PDU can be used
    // in ATM command compatible hardwares for sending SMS.

    // Encoding packet header, including phone number and its format
    // For more info about PDU headers take a look at http://www.gsm-modem.de/sms-pdu-mode.html
    String PDU = "0011000C91";
    PDU += PhoneNumberToSeptets(phoneNumber);
    PDU += "0000FF";

    // For simplicity we assume that len(msg) % 8 == 0
    // if len(msg) % 8 != 0 we add some white space to msg
    if(msg.length() % 8 !=0){
        text += String("        ").substring(0,8-(msg.length()%8)); 
    }
    
    PDU += intToHex(msg.length());  
    String msgInOctets = TextToOctets(msg);
    PDU += msgInOctets;

    unsigned int msgLength = (unsigned int)(msgInOctets.length() / 2) + 14;

    String result = "AT+CMGS=" + String(msgLength) + "\n" + PDU;
    return result;
}



String PhoneNumberToSeptets(String str){
    String res = "";
    for(int i=1; i<str.length()-1; i+=2){
        res += ( str.substring(i+1,i+2) + str.substring(i,i+1) );
    }
    return res;
}

String TextToOctets(String txt){
    String result = "";
    do{
        String tmp = txt.substring(0,8);
        String tmp_septs = str2binseq(tmp);  
        result += semioctet(tmp_septs);
        txt = txt.substring(8,txt.length());
    }while(txt.length() >= 8);
    return result;
}

String str2binseq(String txt){
    String buf = "";
    for(int i=0; i<txt.length(); i++){
        buf += Dec2Bin((unsigned char)txt[i]);
    }
    return buf;
}

String Dec2Bin(unsigned char c){
    String output = "";
    for(int i=6 ; i>=0 ; i--){
        output +=  ((c >> i) & 1 ? 1 : 0);
    }
    return output;
}

String semioctet(String s){
    if(s.length()==56){
        String res= BinToHex(s.substring(13,14)+s.substring(0,7))+ 
                    BinToHex(s.substring(19,21)+s.substring(7,13))+
                    BinToHex(s.substring(25,28)+s.substring(14,19))+
                    BinToHex(s.substring(31,35)+s.substring(21,25))+
                    BinToHex(s.substring(37,42)+s.substring(28,31))+
                    BinToHex(s.substring(43,49)+s.substring(35,37))+
                    BinToHex(s.substring(49,56)+s.substring(42,43));
    return res;
    }
    return "";  
}

String intToHex(unsigned char c){
    String res = "";
    for(int i=7; i>=0; i--){
        res += ((c >> i) & 1 ? 1 : 0);
    }
    return BinToHex(res);
}

String BinToHex(String b){
    String h1 = b.substring(0,4);
    String h2 = b.substring(4,8);
    return Fourbit2Hex(h1)+Fourbit2Hex(h2);
}

String Fourbit2Hex(String fb){
    int p = 1;
    int temp = 0;
    for(int i=3; i>=0; i--){
        String t = fb.substring(i,i+1);
        temp += p*t.toInt();
        p *= 2;
    }
    
    switch(temp){
        case 0: return "0"; break;
        case 1: return "1"; break;
        case 2: return "2"; break;
        case 3: return "3"; break;
        case 4: return "4"; break;
        case 5: return "5"; break;
        case 6: return "6"; break;
        case 7: return "7"; break;
        case 8: return "8"; break;
        case 9: return "9"; break;
        case 10: return "A"; break;
        case 11: return "B"; break;
        case 12: return "C"; break;
        case 13: return "D"; break;
        case 14: return "E"; break;
        case 15: return "F"; break;
        default: return "Z";
    }
    return "Z";
}
