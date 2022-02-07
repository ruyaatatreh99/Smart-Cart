
#include <Wire.h>


#include <LiquidCrystal_I2C.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int buf ;
int F = 0;
int PWMval = 100;
#define BUTpin 2  // DEC button pin
#define RBUTpin 3 //RESET button pin
#define IN11 4
#define IN12 5  // right side
#define IN13 6
#define IN14 7



#define IN21 8
#define IN22 9
#define IN23 10 // lift side
#define IN24 11

#define EN11 12
#define EN12 13
#define EN21 44 // EN side
#define EN22 45


char* BCproduct[20] = {"123789", "456789", "987654", "123456", "134679"};
int OnCart[20] =      {                                                };



int BCprice[20] = {10, 20, 30, 40, 50};

int P_QTY = 0;
String BCdataIn = "";
int MAXp = 20;
int TOTprice = 0;
int price = 0;

bool button;

bool BUTdec = 0;
bool ResetButton ;

void setup() {

  Serial1.begin(9600); //for scanner
  Serial2.begin(9600); //bluetooth
  Serial.begin(9600); //arduino
  Serial1.setTimeout(100); //scanner
  // put your setup code here, to run once:
  pinMode(BUTpin , INPUT_PULLUP);
  pinMode(RBUTpin , INPUT_PULLUP);

  pinMode(IN11 , OUTPUT);
  pinMode(IN12 , OUTPUT);
  pinMode(IN13 , OUTPUT);
  pinMode(IN14 , OUTPUT);

  pinMode(IN21 , OUTPUT);
  pinMode(IN22 , OUTPUT);
  pinMode(IN21 , OUTPUT);
  pinMode(IN21 , OUTPUT);

  pinMode(EN11 , OUTPUT);
  pinMode(EN12 , OUTPUT);
  pinMode(EN21 , OUTPUT);
  pinMode(EN22 , OUTPUT);

  lcd.begin(20, 4);
  // Print a message to the LCD.
  lcd.setCursor(0, 0);
  lcd.print("Use Barcode to check");
  lcd.setCursor(0, 1);
  lcd.print("Addition Mode       ");
  delay(1000);
  pinMode(14 , OUTPUT);
  digitalWrite(14, 0); // GND for R button


}

void loop() {

  button = digitalRead(BUTpin);
  if (button == 0) {
    BUTdec = 1;
    lcd.setCursor(0, 1);
    lcd.print("Subtracting Mode   ");
    //lcd.print("-");
  }
  // --------- reseting -----------------------

  ResetButton = digitalRead(RBUTpin);
  if (ResetButton == 0) {
    TOTprice = 0;
    P_QTY = 0;
    int i = 0;
    for ( i ; i < MAXp; i++) {
      OnCart[i] = 0;
    }



    lcd.setCursor(0, 2);
    lcd.print("Reset done      ");
    lcd.setCursor(0, 3);
    lcd.print("Total Price:");
    lcd.print(TOTprice);
    lcd.print("   ");
  }



  if (Serial1.available()) {
    //Serial.println("");
    BCdataIn = Serial1.readString();
    Serial.println(BCdataIn);



    /*

        char a[] = {};
        BCdataIn.toCharArray(a, 10);
        BCproduct[5] = a;
        Serial.print("    ");
        Serial.print(BCproduct[5]);
        Serial.println("    ");



    */
    int i = 0;
    for ( i ; i < MAXp; i++) {
      if (BCdataIn == BCproduct[i]) {

        // break;
        Serial.println(BCdataIn);
        goto lable;
      }




    }
    Serial.print("i");
    Serial.println(i);

    if (i == (MAXp)) {

      //error
      lcd.setCursor(0, 2);
      lcd.print("Error (NOT LISTED)!!");
      // lcd.print(" ");


      goto lable1;
    }

lable:

    if (BUTdec == 1) {


      //lcd.setCursor(14, 1);
      //lcd.print(" ");
      BUTdec = 0;



      if (OnCart[i] > 0 && P_QTY > 0) {

        // break;
        // Serial.println("in");



        price = BCprice[i];
        lcd.setCursor(0, 2);
        lcd.print("Del Item Price:");
        lcd.print(price);
        lcd.print("   ");
        TOTprice = TOTprice - price;
        lcd.setCursor(0, 3);
        lcd.print("Total Price:");
        lcd.print(TOTprice);
        lcd.print("   ");
        lcd.setCursor(0, 1);
        lcd.print("Addition Mode       ");
        OnCart[i]--;
        P_QTY--;

      }
      else {
        //error
        lcd.setCursor(0, 2);
        lcd.print("Sub Error (OUT)!!");
        lcd.print("  ");
      }




    }


    else {



      OnCart[i]++;
      price = BCprice[i];

      lcd.setCursor(0, 2);
      lcd.print("Item Price:");
      lcd.print(price);
      lcd.print("          ");


      TOTprice = TOTprice + price;
      Serial.print("price");
      Serial.println(price);

      lcd.setCursor(0, 3);
      lcd.print("Total Price:");
      lcd.print(TOTprice);
      lcd.print("   ");
      lcd.setCursor(0, 1);
      lcd.print("Addition Mode       ");
      P_QTY++;
    }




  }

lable1:
  if (Serial2.available() ) { //BT






    buf = Serial2.read();

    if (buf == 'F') {

      FRWD();
    }

    if (buf == 'B') {
      BKWD();

    }
    if (buf == 'L') {
      LIFT();
    }
    if (buf == 'R') {
      RIGHT();

    }
    if (buf == 'S') {
      STOP();

    }

    if (buf == '1') {
      PWMval = 255 * 0.1;

    }
    if (buf == '2') {
      PWMval = 255 * 0.2;

    }
    if (buf == '3') {
      PWMval = 255 * 0.3;

    }
    if (buf == '4') {

      PWMval = 255 * 0.4;
    }
    if (buf == '5') {

      PWMval = 255 * 0.5;
    }
    if (buf == '6') {

      PWMval = 255 * 0.6;
    }
    if (buf == '7') {

      PWMval = 255 * 0.7;
    }
    if (buf == '8') {

      PWMval = 255 * 0.8;
    }
    if (buf == '9') {

      PWMval = 255 * 0.9;
    }
    if (buf == 'q') {
      PWMval = 255 ;

    }



    analogWrite(EN11, PWMval);
    analogWrite(EN12, PWMval);
    analogWrite(EN21, PWMval);
    analogWrite(EN22, PWMval);

  }



  if (F == 1) {
    /* digitalWrite(IN1, 0);
      digitalWrite(IN2, 0);
      digitalWrite(IN3, 0);
      digitalWrite(IN4, 0);
    */
  }

}





void FRWD() {
  digitalWrite(IN11, 1);
  digitalWrite(IN12, 0);
  digitalWrite(IN13, 1);
  digitalWrite(IN14, 0);

  digitalWrite(IN21, 1);
  digitalWrite(IN22, 0);
  digitalWrite(IN23, 1);
  digitalWrite(IN24, 0);

}
void BKWD() {
  digitalWrite(IN11, 0);
  digitalWrite(IN12, 1);
  digitalWrite(IN13, 0);
  digitalWrite(IN14, 1);

  digitalWrite(IN21, 0);
  digitalWrite(IN22, 1);
  digitalWrite(IN23, 0);
  digitalWrite(IN24, 1);

}
void RIGHT() {
  digitalWrite(IN11, 0);
  digitalWrite(IN12, 0);
  digitalWrite(IN13, 0);
  digitalWrite(IN14, 0);

  digitalWrite(IN21, 1);
  digitalWrite(IN22, 0);
  digitalWrite(IN23, 1);
  digitalWrite(IN24, 0);

}
void LIFT() {
  digitalWrite(IN11, 1);
  digitalWrite(IN12, 0);
  digitalWrite(IN13, 1);
  digitalWrite(IN14, 0);

  digitalWrite(IN21, 0);
  digitalWrite(IN22, 0);
  digitalWrite(IN23, 0);
  digitalWrite(IN24, 0);

}
void STOP() {
  digitalWrite(IN11, 0);
  digitalWrite(IN12, 0);
  digitalWrite(IN13, 0);
  digitalWrite(IN14, 0);

  digitalWrite(IN21, 0);
  digitalWrite(IN22, 0);
  digitalWrite(IN23, 0);
  digitalWrite(IN24, 0);

}
