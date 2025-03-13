#include"globalDef.h"


void setMux(int val){
    switch (val){
        case 1:
            digitalWrite(mux_A1, LOW);
            digitalWrite(mux_A0, LOW);
            break;
        case 2:
            digitalWrite(mux_A1, LOW);
            digitalWrite(mux_A0, HIGH);
            break;
        case 3:
            digitalWrite(mux_A1, HIGH);
            digitalWrite(mux_A0, LOW);
            break;
        case 4:
            digitalWrite(mux_A1, HIGH);
            digitalWrite(mux_A0, HIGH);
            break;

    }
        
}

void setDecoder(int8_t val){
    digitalWrite(DECODER_A, (val & 0x01));
    digitalWrite(DECODER_B, (val & 0x02));
    digitalWrite(DECODER_C, (val & 0x04));
}

void testDecoder(){
    setDecoder(0x01);
    delay(300);
    setDecoder(0x02);
    delay(300);
    setDecoder(0x03);
    delay(300);
    setDecoder(0x04);
    delay(300);
    setDecoder(0x05);
    delay(300);
    setDecoder(0x06);
    delay(300);
    setDecoder(0x07);
    delay(300);
    setDecoder(0x07);
    delay(300);
    setDecoder(0x06);
    delay(300);
    setDecoder(0x05);
    delay(300);
    setDecoder(0x04);
    delay(300);
    setDecoder(0x03);
    delay(300);
    setDecoder(0x02);
    delay(300);
    setDecoder(0x01);
}