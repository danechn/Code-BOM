#include <PS2X_lib.h>


PS2X ps2x;

int error = 0;
byte type = 0;
byte vibrate = 0;


 int m1_0 = 8;
 int m1_1 = 9;
 int m2_0 = 7;
 int m2_1 = 6;
 int lmotor = 0;
 int rmotor = 0;

void setup() {
  Serial.begin(57600);

  pinMode(m1_0, OUTPUT);
  pinMode(m2_0, OUTPUT);


  error = ps2x.config_gamepad(13, 11, 10, 12, true, true); 
  if(error == 0){
    Serial.println("Controller Found, configured successful.");
    Serial.println("Try all buttons, X will vibrate controller, harder you press, the faster.");
  }
   else if(error == 1){
    Serial.println("No controller found, check wiring, search up how to fix");
    }

    else if(error == 2){
      Serial.println("Controller found, but not working, search to fix"); 
    }

    else if(error == 3){
      Serial.println("Contrtoller refusing to enter Pressures mode");
    }
  

    type = ps2x.readType(); 
    switch(type) {
      case 0:
       Serial.println("Unknown Controller type");
      break;
      case 1:
       Serial.println("DualShock Controller Found");
      break;
    }

}

void loop() {
  // put your main code here, to run repeatedly:

  if(error == 1) return; // if no controller is found
  if(type == 2){ 
  ps2x.read_gamepad();          //read controller 
  if(ps2x.ButtonPressed(GREEN_FRET))
    Serial.println("Green Fret Pressed");
  if(ps2x.ButtonPressed(RED_FRET))
    Serial.println("Red Fret Pressed");
  if(ps2x.ButtonPressed(YELLOW_FRET))
    Serial.println("Yellow Fret Pressed");
  if(ps2x.ButtonPressed(BLUE_FRET))
    Serial.println("Blue Fret Pressed");
  if(ps2x.ButtonPressed(ORANGE_FRET))
    Serial.println("Orange Fret Pressed");
   if(ps2x.ButtonPressed(STAR_POWER))
    Serial.println("Star Power Command");
   if(ps2x.Button(UP_STRUM))          //will be TRUE as long as button is pressed
    Serial.println("Up Strum");
   if(ps2x.Button(DOWN_STRUM))
    Serial.println("DOWN Strum");
   if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
        Serial.println("Start is being held");
   if(ps2x.Button(PSB_SELECT))
        Serial.println("Select is being held");
   if(ps2x.Button(ORANGE_FRET)) // print stick value IF TRUE
   {
       Serial.print("Wammy Bar Position:");
       Serial.println(ps2x.Analog(WHAMMY_BAR), DEC); 
   } 
}

else { //DualShock Controller
   ps2x.read_gamepad(false, vibrate);          //read controller and set large motor to spin at 'vibrate' speed
   if(ps2x.Button(PSB_START))                   //will be TRUE as long as button is pressed
        Serial.println("Start is being held");
   if(ps2x.Button(PSB_SELECT))
        Serial.println("Select is being held");
    if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
      Serial.print("Up held this hard: ");
      Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
     }
     if(ps2x.Button(PSB_PAD_RIGHT)){
      Serial.print("Right held this hard: ");
       Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
     }
     if(ps2x.Button(PSB_PAD_LEFT)){
      Serial.print("LEFT held this hard: ");
       Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
     }
     if(ps2x.Button(PSB_PAD_DOWN)){
      Serial.print("DOWN held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
     }   
     vibrate = ps2x.Analog(PSAB_BLUE);        //this will set the large motor vibrate speed based on 
                                             //how hard you press the blue (X) button    
   if (ps2x.NewButtonState())               //will be TRUE if any button changes state (on to off, or off to on)
   {   
       if(ps2x.Button(PSB_L3))
        Serial.println("L3 pressed");
       if(ps2x.Button(PSB_R3))
        Serial.println("R3 pressed");
       if(ps2x.Button(PSB_L2))
        Serial.println("L2 pressed");
       if(ps2x.Button(PSB_R2))
        Serial.println("R2 pressed");
       if(ps2x.Button(PSB_GREEN))
        Serial.println("Triangle pressed");
   }   
   if(ps2x.ButtonPressed(PSB_RED))             //will be TRUE if button was JUST pressed
        Serial.println("Circle just pressed");
   if(ps2x.ButtonReleased(PSB_PINK))             //will be TRUE if button was JUST released
        Serial.println("Square just released");     
   if(ps2x.NewButtonState(PSB_BLUE))            //will be TRUE if button was JUST pressed OR released
        Serial.println("X just changed");    
   if(ps2x.Button(PSB_L1) || ps2x.Button(PSB_R1)) // print stick values if either is TRUE
   {
       Serial.print("Stick Values:");
       Serial.print(ps2x.Analog(PSS_LY), DEC); //Left stick, Y axis. Other options: LX, RY, RX  
       Serial.print(",");
       Serial.print(ps2x.Analog(PSS_LX), DEC); 
       Serial.print(",");
       Serial.print(ps2x.Analog(PSS_RY), DEC); 
       Serial.print(",");
       Serial.println(ps2x.Analog(PSS_RX), DEC); 
   } 
}
  
  if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
       Serial.print("Up held this hard: ");
       Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);
      }
      if(ps2x.Button(PSB_PAD_RIGHT)){
       Serial.print("Right held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
      }
      if(ps2x.Button(PSB_PAD_LEFT)){
       Serial.print("LEFT held this hard: ");
        Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);
      }
      if(ps2x.Button(PSB_PAD_DOWN)){
       Serial.print("DOWN held this hard: ");
     Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);
      }   

      vibrate = ps2x.Analog(PSAB_BLUE);

    if(ps2x.Button(PSB_PAD_UP))// make this<= or ==
   {
    digitalWrite(m1_1, LOW);
    digitalWrite(m1_0, HIGH);   //PWM Speed Control
    digitalWrite(m2_1, LOW);
    digitalWrite(m2_0, HIGH); 
   }

    if(ps2x.Button(PSB_PAD_DOWN))// make this<= or ==
   {
    digitalWrite(m1_1, HIGH);
    digitalWrite(m1_0, LOW);   //PWM Speed Control
    digitalWrite(m2_1, HIGH);
    digitalWrite(m2_0, LOW); 
   }

    if(ps2x.Button(PSB_PAD_LEFT))// make this<= or ==
   {
    digitalWrite(m1_1, HIGH);
    digitalWrite(m1_0, LOW);   //PWM Speed Control
    digitalWrite(m2_1, LOW);
    digitalWrite(m2_0, HIGH); 
   }

    if(ps2x.Button(PSB_PAD_RIGHT))// make this<= or ==
   {
    digitalWrite(m1_1, LOW);
    digitalWrite(m1_0, HIGH);   //PWM Speed Control
    digitalWrite(m2_1, HIGH);
    digitalWrite(m2_0, LOW); 
   }

   if(ps2x.Button(PSB_BLUE))// make this<= or ==
   {
    digitalWrite(m1_1, LOW);
    digitalWrite(m1_0, LOW);   //PWM Speed Control
    digitalWrite(m2_1, LOW);
    digitalWrite(m2_0, LOW); 
   }
   
 
  delay(50);
  }
