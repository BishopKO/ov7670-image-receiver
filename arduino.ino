#include <ov7670_camera.h>

void setup() {
  
  DDRB |= (1 << 3);//pin 11
   ASSR &= ~(_BV(EXCLK) | _BV(AS2));
   TCCR2A = (1 << COM2A0) | (1 << WGM21) | (1 << WGM20);
   TCCR2B = (1 << WGM22) | (1 << CS20);
   OCR2A = 0;//(F_CPU)/(2*(X+1))
   DDRC &= ~15;//low d0-d3 camera // 00001111
   DDRD &= ~252;//d7-d4 and interrupt pins // 11111100
   _delay_ms(3000);
  
     //set up twi for 100khz
   TWSR &= ~3;//disable prescaler for TWI
   TWBR = 72;//set to 100khz
//   UBRR0H = 0;
//   UBRR0L = 0;//0 = 2M baud rate. 1 = 1M baud. 3 = 0.5M. 7 = 250k 207 is 9600 baud rate.
//   UCSR0A |= 2;//double speed aysnc
//   UCSR0B = (1 << RXEN0) | (1 << TXEN0);//Enable receiver and transmitter
//   UCSR0C = 6;//async 1 stop bit 8bit char no parity bits
  Serial.begin(1000000);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  while (!Serial) {
    delay(200);
  }
  setup_camera();
  Serial.print("RDY");
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  if(Serial.available()){
    Serial.read();
    flicker(2);   
    digitalWrite(LED_BUILTIN, LOW);
    //cli();
    capture_and_transmit_image();
    //sei();
    Serial.print("OK BYE ***");
    Serial.flush();
    flicker(5);
    Serial.print("RDY");
  }
  delay(200);
}

void flicker(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
  }
}
