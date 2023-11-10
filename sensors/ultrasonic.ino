void setup() {
  Serial.begin(115200); //Enable Serial connection to report the time
  //-----------Setting Registers for the Trigger Signal---------------------
  PMC->PMC_PCER0 |= PMC_PCER0_PID27;//TC0 power ON - Timer Counter 0 channel 0
  PIOB->PIO_PDR |= PIO_PDR_P25; // The pin is no more driven by GPIO
  PIOB->PIO_ABSR |= PIO_PB25B_TIOA0;// B Assign B25 to alternative periph_B (TIOA0):
  TC0->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK1 //MCK/2 = 42 MHz,
                              | TC_CMR_WAVE //Waveform mode
                              | TC_CMR_WAVSEL_UP_RC //Count UP mode till RC
                              | TC_CMR_ACPA_CLEAR //Clear TIOA0 on RA compare match
                              | TC_CMR_ACPC_SET; // Set TIOA0 on RC compare match
  TC0->TC_CHANNEL[0].TC_RC = 2520000-1; //Set the frequency to 16.667Hz (Period 60 ms)
  TC0->TC_CHANNEL[0].TC_RA = 420-1; //Set the duty cycle (Pulse of 10 usec)
  TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_SWTRG //Software trigger TC0 channel 0 counter
                            | TC_CCR_CLKEN;//and enable
  //-----------Setting Registers for the Echo Signal---------------------
  PMC->PMC_PCER0 |= PMC_PCER0_PID28;// Timer Counter 0 channel 1 IS TC1,TC1 power ON
  TC0->TC_CHANNEL[1].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK1 //capture mode, MCK/2 = 42 MHz
                            | TC_CMR_ABETRG // TIOA is used as the external trigger
                            | TC_CMR_LDRA_FALLING// load RA on falling edge of TIOA
                            | TC_CMR_ETRGEDG_RISING; // Trigger on rising edge
  TC0->TC_CHANNEL[1].TC_CCR = TC_CCR_SWTRG| TC_CCR_CLKEN; // Reset TC counter and enable
}
void loop(){
volatile uint32_t CaptureCountA;
  CaptureCountA = TC0->TC_CHANNEL[1].TC_RA;
  printf("L#, Group#: \r %f cm \n", 340.0*CaptureCountA/(42000000.0)/2*100);
  delay(500);
}
