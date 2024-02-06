#include <avr/interrupt.h>
#include <avr/sleep.h>

#define BUTTON 0
#define LED 3

ISR(PCINT0_vect) {
  if (digitalRead(BUTTON) == LOW)           // # PB0 = pin 5 pressed => LED on
    digitalWrite(LED, HIGH);
}

void setup() {  
  pinMode(LED,OUTPUT); // LED
  pinMode(BUTTON,INPUT_PULLUP);
  ADCSRA = 0; // ADC disabled
  GIMSK = 0b00100000;  // General Interrupt Mask Register, / Bit 5 – PCIE: Pin Change Interrupt Enable / When the PCIE bit is set (one) and the I-bit in the Status Register (SREG) is set (one), pin change interrupt is enabled. Any change on any enabled PCINT[5:0] pin will cause an interrupt. The corresponding interrupt of Pin Change Interrupt Request is executed from the PCI Interrupt Vector. PCINT[5:0] pins are enabled individually by the PCMSK0 Register. / see https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-2586-AVR-8-bit-Microcontroller-ATtiny25-ATtiny45-ATtiny85_Datasheet.pdf
  PCMSK = 0b00000111;  
} 

void loop() {
  sleep_enable();
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  sleep_cpu();
  delay(10000);
  digitalWrite(LED,LOW);
}