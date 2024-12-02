#include <LiquidCrystal.h>    //Library for LCD Display
#include <Keypad.h>           //Library for Keypad

//Initializing LCD Pins with object "lcd"
LiquidCrystal lcd(27, 28, 29, 37, 36, 35);  //RS,EN,D4,D5,D6,D7 at PE1,PE2,PE3,PC4,PC5,PC6

//Built-in LED Indicators for answers
const int RED_led = 30; //At PF1
const int BLUE_led = 40; //At PF2

//////////////////////////////////////////////////////////////////////////
// Defining the Keymap layout
const byte ROWS = 4;      // Four rows
const byte COLS = 3;      // Three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

//Connect keypad ROW0, ROW1, ROW2 and ROW3 to these TivaC pins PB0, PB1, PE4, PE5
byte rowPins[ROWS] = { 3, 4, 5, 6 };
// Connect keypad COL0, COL1 and COL2 to these TivaC pins PB4, PA5, PA6
byte colPins[COLS] = { 7, 8, 9};

//Create the Keypad object
Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS );
#define pin_length 6              //Passcode/pin length+1
char Data[pin_length];            //Creating array of size of the passcode
char Master[pin_length] = "07171";    //Enter you student ID here
byte data_count = 0, master_count = 0;
bool Pass_is_good;            //flag to detect if password is correct
char customKey;               //stores the character entered by user on keypad
int firstNumber = 0;
int secondNumber = 0;
char operation = 0;
bool inputComplete = false;
//////////////////////////////////////////////////////////////////////////


void setup()
{
    pinMode(27,OUTPUT);//Pins 8-14 are enabled as output for LCD
    pinMode(28,OUTPUT);
    pinMode(29,OUTPUT);
    pinMode(37,OUTPUT);
    pinMode(36,OUTPUT);
    pinMode(35,OUTPUT);

    pinMode(RED_led, OUTPUT);
    pinMode(BLUE_led, OUTPUT);
  
    //Initialize data to be printed on LCD whenever program starts
    lcd.begin(16, 2);               //Initializing LCD
    lcd.print("Entering");          //Prints in the first row
    lcd.setCursor(0,1);             //Set curor in second row, first column
    lcd.print("Safe Lock");         //Prints in the second row, first column
    delay(5000);                    //Left the data written on LCD for 5 seconds
    lcd.clear();                    //Clears everything on the LCD
}


//Functions clear all the data from Data array that we created to store keypad characters
void clearData(){
  while(data_count !=0){
    Data[data_count--] = 0; 
  }
  return;
}


void loop()
{
    //safeLock();       //Function to execute Safe Lock logic, to be used in task02
    calculator();  //Function to execute calculator logic, to be used in task03
}


void safeLock(){
  lcd.setCursor(0,0);        //Set the cursor to initial position
  lcd.print("Enter Pin:");   //Prints in the first row of LCD

  customKey = customKeypad.getKey();  //Whenever key is pressed, the char is stored in customKey
  if (customKey){
    Data[data_count] = customKey;   //Store the character at the i'th index in Data array
    lcd.setCursor(data_count,1);    //Set cursor to second row and i'th column
    lcd.print(Data[data_count]);    //Prints character from keypad at the cursor position
    data_count++;                   //Increment the index for next iteration
  }

  //When the passcode length is reached, check whether it's correct or not
  if(data_count == pin_length-1){
    lcd.clear();      //clears all data from LCD to display results of passcode

    if(!strcmp(Data, Master)){
      //If passcode is correct print "Valid" on LCD and turn on BLUE_led for 3 seconds below    
      lcd.print("Valid"); 
      digitalWrite(BLUE_led, HIGH);
      delay(3000);
      digitalWrite(BLUE_led, LOW);
      }
    else{
      //If passcode is incorrect print "Invalid" on LCD and turn on RED_led for 3 seconds below
      lcd.print("Invalid"); 
      digitalWrite(RED_led, HIGH);
      delay(3000);
      digitalWrite(RED_led, LOW);
      }
    
    lcd.clear();
    clearData();  
  }
}

void calculator(){
  lcd.setCursor(0,0);
  lcd.print("First Number:");   //Prints in the first row of LCD
  //Write your logic for calculator below for task03

    while (!inputComplete) {
    char customKey = customKeypad.getKey(); 

    if (customKey) {
      Data[data_count] = customKey;
      lcd.setCursor(0, 1);
      lcd.print(customKey);
      delay(2000);
      data_count++; 
      firstNumber = atoi(&customKey);        
      if (data_count == 1) {
        lcd.clear();
        clearData(); 
        lcd.print("Operation: ");
        delay(500);
        break;
      }
      }
    }

    while (!operation) {
    char customKey = customKeypad.getKey();    
      if (customKey == '*' || customKey == '#') {
        operation = customKey;
        lcd.setCursor(0, 1);
        lcd.print(customKey);
        delay(2000);
        lcd.clear();
        data_count++;
        lcd.print("Second Number: ");
        delay(500);
        break;
      } 
      else if (customKey) {
        lcd.clear();
        lcd.print("Invalid");
        delay(2000);
        lcd.clear();
        return;
      }
    }

    while (!inputComplete) {
    char customKey = customKeypad.getKey();
    if (customKey) {
      Data[data_count] = customKey;
      lcd.setCursor(0, 1);
      lcd.print(customKey);
      delay(2000);
      secondNumber = atoi(&customKey);
      data_count++;

      if (data_count == 2) {
        clearData();
        inputComplete = true;
        break;
      }
    }
  }

  lcd.clear();
  lcd.print("Output:");
  lcd.setCursor(0, 1);
  if (operation == '*') {
    lcd.print(firstNumber * secondNumber);
  } 
  else if (operation == '#' && secondNumber != 0) {
    lcd.print(firstNumber / secondNumber);
  }
  else {
    lcd.print("Invalid");
  }

  delay(3000);
  lcd.clear();
  clearData();
  inputComplete = false;
  operation = 0;
  data_count = 0;
}
