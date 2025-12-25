#define Button_K2  10
#define Button_K3  3
#define Button_K4 0

bool flagK2 = false;
bool flagK3 = false;
bool flagK4 = false;

int buttonK2State = 0;         // variable for reading the pushbutton status
int buttonK3State = 0;         // variable for reading the pushbutton status
int buttonK4State = 0;         // variable for reading the pushbutton status


void setup() {
  Serial.begin(115200);
  digitalWrite(Button_K2, LOW);
  digitalWrite(Button_K3, LOW);
  digitalWrite(Button_K4, LOW);
  pinMode(Button_K2, INPUT);
  pinMode(Button_K3, INPUT);
  pinMode(Button_K4, INPUT);
}

void loop() {
  buttonK2State = digitalRead(Button_K2);
  buttonK3State = digitalRead(Button_K3);
  buttonK4State = digitalRead(Button_K4);
  Serial.print("buttonK3State: ");
  Serial.println(buttonK3State);

  /*-------- K2 --------*/
  if (buttonK2State == LOW)
  {
    //    if (!flagK2)
    //    {
    Serial.println("buttonK2 press");
    //      flagK2 = true;
    //    }
  }
  //  else
  //  {
  //    flagK2 = false;
  //  }

  /*-------- K3 --------*/
  if (buttonK3State == LOW)
  {
    //    if (!flagK3)
    //    {
    Serial.println("buttonK3 press");
    //      flagK3 = true;
    //    }
  }
  //  else
  //  {
  //    flagK3 = false;
  //  }

  /*-------- K4 --------*/
  if (buttonK4State == LOW)
  {
    //    if (!flagK4)
    //    {
    Serial.println("buttonK4 press");
    //      flagK4 = true;
    //    }
  }
  //  else
  //  {
  //    flagK4 = false;
  //  }
  //  Serial.println("no press");
  delay(100);
}
