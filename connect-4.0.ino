
//libraries
#include <LiquidCrystal.h>

//Defining Variables...

//for LED
#define BLUE 6
#define GREEN 7
#define RED 8

int redValue;
int greenValue;
int blueValue;

//...for IR sensors:
int short_delay = 50;
int long_delay = 1000;

//for joystick button:
byte button;
byte oldbutton = 0;
byte buttonpin = 10;
byte state = 1;

//for functionality:
byte whose_go = 1;
bool turn_played = false;
const int rows = 7; // number of columns irl (due to board rotation of 90 degrees)
const int columns = 6; // number of rows irl (due to board rotation of 90 degrees)
int board[ rows ][ columns ];

bool P1_Horizontal_Win = false; // win states...
bool P1_Vertical_Win = false;
bool P1_Right_Diagonal_Win = false;
bool P1_Left_Diagonal_Win = false;
bool P2_Horizontal_Win = false;
bool P2_Vertical_Win = false;
bool P2_Right_Diagonal_Win = false;
bool P2_Left_Diagonal_Win = false;


LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // lcd object 

void setup() {
  Serial.begin(9600);

  //for leds...
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  //digitalWrite(RED, LOW);
  //digitalWrite(GREEN, LOW);
  //digitalWrite(BLUE, LOW);

  
  pinMode(A0,INPUT); // IR column 1
  pinMode(A2,INPUT); // IR column 2
  pinMode(A5,INPUT); // IR column 3
  pinMode(A7,INPUT); // IR column 4
  pinMode(A9,INPUT); // IR column 5
  pinMode(A12,INPUT); // IR column 6
  pinMode(A15,INPUT); // IR column 7

  pinMode(buttonpin, INPUT_PULLUP);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("I am CONNECT 4.0");
  lcd.setCursor(0,1);
  lcd.print("Press START"); // Press START to play
}

void loop() {
  // put your main code here, to run repeatedly:
  
  
 button = digitalRead(buttonpin);
  if(button && !oldbutton) // same as if(button == high && oldbutton == low)
  {
    //we have a new button press
    if(state == 0) // if the state is off, turn it on
    {
      //game starts!
      state = 1;
      if (state == 1){
        lcd.clear();
        lcd.print("STARTING...");
        delay(500);
        lcd.clear();
      };
      
    }
    else // if the state is on, turn it off
    {
      //idle mode / reset game
      state = 0; 
      if (state == 0){
        lcd.clear();
        lcd.print("I am CONNECT 4.0");
        lcd.setCursor(0,1);
        lcd.print("Press START"); // Press START to play
      };
     
    }
    oldbutton = 1;
  }
  else if(!button && oldbutton) // same as if(button == low && oldbutton == high)
  {
    // the button was released
    oldbutton = 0;
  }
  
  delay(50);
 
  while (state == 1) {

  
    if (whose_go == 1){ //run while it's player 1's turn
      
      if (P1_Horizontal_Win == false && P1_Vertical_Win == false && P1_Right_Diagonal_Win == false && P1_Left_Diagonal_Win == false && P2_Horizontal_Win == false && P2_Vertical_Win == false && P2_Right_Diagonal_Win == false && P2_Left_Diagonal_Win == false){
      lcd.setCursor(0,0);
      lcd.print("Green, go!");
      whose_go = Check_Cols();
      }

      P1_Horizontal_Win = P1_Check_Horizontal_Win();
      P1_Vertical_Win = P1_Check_Vertical_Win();
      P1_Left_Diagonal_Win = P1_Check_Left_Diagonal_Win();
      P1_Right_Diagonal_Win = P1_Check_Right_Diagonal_Win();
      
      if (P1_Horizontal_Win == true || P1_Vertical_Win == true || P1_Right_Diagonal_Win == true || P1_Left_Diagonal_Win == true){
          
        lcd.clear();
        lcd.print("GREEN WINS!");
        lcd.setCursor(0,1);
        lcd.print("Reset game...");
        
          //celebration light!
          analogWrite(RED, 0);
          analogWrite(GREEN, 255);
          analogWrite(BLUE, 0);
          delay(200);
          analogWrite(RED, 0);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 0);
          delay(200);
          analogWrite(RED, 0);
          analogWrite(GREEN, 255);
          analogWrite(BLUE, 0);
          delay(200);
          analogWrite(RED, 0);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 0);
          delay(200);
          analogWrite(RED, 0);
          analogWrite(GREEN, 255);
          analogWrite(BLUE, 0);
          delay(200);
          analogWrite(RED, 0);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 0);
          delay(200);
          analogWrite(RED, 0);
          analogWrite(GREEN, 255);
          analogWrite(BLUE, 0);
          delay(200);
          analogWrite(RED, 0);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 0);
          delay(200);
          analogWrite(RED, 0);
          analogWrite(GREEN, 255);
          analogWrite(BLUE, 0);
          delay(200);
          analogWrite(RED, 0);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 0);
          delay(200);
          analogWrite(RED, 0);
          analogWrite(GREEN, 255);
          analogWrite(BLUE, 0);
          delay(200);
          analogWrite(RED, 0);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 0);
          delay(200);
          analogWrite(RED, 0);
          analogWrite(GREEN, 255);
          analogWrite(BLUE, 0);
          delay(200);
          
        
        break;
      }
      

        if (whose_go == 2){ //if whose_go has changed to player 2...
          delay(500);
          lcd.clear();
        }
      }

    if (whose_go == 2){ //run while it's player 2's turn

      if (P1_Horizontal_Win == false && P1_Vertical_Win == false && P1_Right_Diagonal_Win == false && P1_Left_Diagonal_Win == false && P2_Horizontal_Win == false && P2_Vertical_Win == false && P2_Right_Diagonal_Win == false && P2_Left_Diagonal_Win == false){
        lcd.setCursor(0,0);
        lcd.print("Pink, go!");
        whose_go = Check_Cols();
      }

      P2_Horizontal_Win = P2_Check_Horizontal_Win();
      P2_Vertical_Win = P2_Check_Vertical_Win();
      P2_Left_Diagonal_Win = P2_Check_Left_Diagonal_Win();
      P2_Right_Diagonal_Win = P2_Check_Right_Diagonal_Win();
      
      if (P2_Horizontal_Win == true || P2_Vertical_Win == true || P2_Right_Diagonal_Win == true || P2_Left_Diagonal_Win == true){
          
        lcd.clear();
        lcd.print("PINK WINS!");
        lcd.setCursor(0,1);
        lcd.print("Reset game...");
        
        //celebration light!
          analogWrite(RED, 150);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 150);
          delay(200);
          analogWrite(RED, 0);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 0);
          delay(200);
          analogWrite(RED, 150);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 150);
          delay(200);
          analogWrite(RED, 0);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 0);
          delay(200);
          analogWrite(RED, 150);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 150);
          delay(200);
          analogWrite(RED, 0);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 0);
          delay(200);
          analogWrite(RED, 150);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 150);
          delay(200);
          analogWrite(RED, 0);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 0);
          delay(200);
          analogWrite(RED, 150);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 150);
          delay(200);
          analogWrite(RED, 0);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 0);
          delay(200);
          analogWrite(RED, 150);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 150);
          delay(200);
          analogWrite(RED, 0);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 0);
          delay(200);
          analogWrite(RED, 150);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 150);
          delay(200);
          analogWrite(RED, 0);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 0);
          delay(200);
          analogWrite(RED, 150);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 150);
          delay(200);
          analogWrite(RED, 0);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 0);
          delay(200);
          analogWrite(RED, 150);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 150);
          delay(200);
          analogWrite(RED, 0);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 0);
          delay(200);
          analogWrite(RED, 150);
          analogWrite(GREEN, 0);
          analogWrite(BLUE, 150);
     
        break;
      }

        if (whose_go == 1){ //if whose_go has changed to player 1..
          delay(1000);
          lcd.clear();
        }
        
     }
   
  }

}


//Checking column sensors function-----------------------------------------------------------------------------------------------------------------------------------
int Check_Cols(){
    if(digitalRead(A0)==0) // IF PLAYER GOES IN COLUMN 1----------------------
    {
    lcd.setCursor(0,1);
    lcd.print("Counter in col 1");
    delay(long_delay);

    if (whose_go == 1){
      find_spot_col_1();
      Serial.println();
      printArray(board);
      return 2;
    }

    if (whose_go == 2){
      find_spot_col_1();
      Serial.println();
      printArray(board);
      return 1;
    }
     
    }    
    else{
      delay(short_delay); // nothing detected in column 1
    }

    if(digitalRead(A2)==0) // IF PLAYER GOES IN COLUMN 2------------------
    {
    lcd.setCursor(0,1);
    lcd.print("Counter in col 2");
    delay(long_delay);

    if (whose_go == 1){
      find_spot_col_2();
      Serial.println();
      printArray(board);
      return 2;
    }

    if (whose_go == 2){
      find_spot_col_2();
      Serial.println();
      printArray(board);
      return 1;
    }
    
    }
    else{
      delay(short_delay); // nothing detected in column 2
    }

   if(digitalRead(A5)==0)// IF PLAYER GOES IN COLUMN 3-----------------
    {
    lcd.setCursor(0,1);
    lcd.print("Counter in col 3");
    delay(long_delay);

    if (whose_go == 1){
      find_spot_col_3();
      Serial.println();
      printArray(board);
      return 2;
    }

    if (whose_go == 2){
      find_spot_col_3();
      Serial.println();
      printArray(board);
      return 1;
    }
    
    }
    else{
      delay(short_delay);// nothing detected in column 3
    }

   if(digitalRead(A7)==0)// IF PLAYER GOES IN COLUMN 4----------------------
    {
    lcd.setCursor(0,1);
    lcd.print("Counter in col 4");
    delay(long_delay);
    
    if (whose_go == 1){
      find_spot_col_4();
      Serial.println();
      printArray(board);
      return 2;
    }

    if (whose_go == 2){
      find_spot_col_4();
      Serial.println();
      printArray(board);
      return 1;
    }
    
    }
    else{
      delay(short_delay); // nothing detected in column 4
    }

   if(digitalRead(A9)==0)// IF PLAYER GOES IN COLUMN 5----------------
    {
    lcd.setCursor(0,1);
    lcd.print("Counter in col 5");
    delay(long_delay);
    
    if (whose_go == 1){
      find_spot_col_5();
      Serial.println();
      printArray(board);
      return 2;
    }

    if (whose_go == 2){
      find_spot_col_5();
      Serial.println();
      printArray(board);
      return 1;
    }

    }
    else{
      delay(short_delay); // nothing detected in column 5
    }

   if(digitalRead(A12)==0) // IF PLAYER GOES IN COLUMN 6--------------------
    {
    lcd.setCursor(0,1);
    lcd.print("Counter in col 6");
    delay(long_delay);
    
    if (whose_go == 1){
      find_spot_col_6();
      Serial.println();
      printArray(board);
      return 2;
    }

    if (whose_go == 2){
      find_spot_col_6();
      Serial.println();
      printArray(board);
      return 1;
    }

    }
    else{
      delay(short_delay); // nothing detected in column 6
    }

   if(digitalRead(A15)==0)// IF PLAYER GOES IN COLUMN 7---------------------------
    {
    lcd.setCursor(0,1);
    lcd.print("Counter in col 7");
    delay(long_delay);

    if (whose_go == 1){
      find_spot_col_7();
      Serial.println();
      printArray(board);
      return 2;
    }

    if (whose_go == 2){
      find_spot_col_7();
      Serial.println();
      printArray(board);
      return 1;
    }
    
    }
    else{
      delay(short_delay); // nothing detected in column 7
    } 

    return whose_go; // nothing at all detected. It remains the same player's go. 
}


//finding correct space for players in matrix functions ----------------------------------------------------------------------------------------------------------------

void find_spot_col_1(){ //col refers to irl column (matrix row)
  for ( int column = 0; column < 6; ++column )
   if (board[ 0 ][ column ] == 0){
    board[ 0 ][ column ] = whose_go;
    return;
   }
}

void find_spot_col_2(){ //col refers to irl column (matrix row)
  for ( int column = 0; column < 6; ++column )
   if (board[ 1 ][ column ] == 0){
    board[ 1 ][ column ] = whose_go;
    return;
   }
}

void find_spot_col_3(){ //col refers to irl column (matrix row)
  for ( int column = 0; column < 6; ++column )
   if (board[ 2 ][ column ] == 0){
    board[ 2 ][ column ] = whose_go;
    return;
   }
}

void find_spot_col_4(){ //col refers to irl column (matrix row)
  for ( int column = 0; column < 6; ++column )
   if (board[ 3 ][ column ] == 0){
    board[ 3 ][ column ] = whose_go;
    return;
   }
}

void find_spot_col_5(){ //col refers to irl column (matrix row)
  for ( int column = 0; column < 6; ++column )
   if (board[ 4 ][ column ] == 0){
    board[ 4 ][ column ] = whose_go;
    return;
   }
}

void find_spot_col_6(){ //col refers to irl column (matrix row)
  for ( int column = 0; column < 6; ++column )
   if (board[ 5 ][ column ] == 0){
    board[ 5 ][ column ] = whose_go;
    return;
   }
}

void find_spot_col_7(){ //col refers to irl column (matrix row)
  for ( int column = 0; column < 6; ++column )
   if (board[ 6 ][ column ] == 0){
    board[ 6 ][ column ] = whose_go;
    return;
   }
}



// Function to print what the board looks like ---------------------------------------------------------------------------------------------------------------------
void printArray( const int a[][ columns ] ) {  
   // loop through array's rows
   for ( int i = 0; i < rows; ++i ) {
      // loop through columns of current row
      for ( int j = 0; j < columns; ++j )
      Serial.print (a[ i ][ j ] );
      Serial.println () ; // start new line of output
   } 
} 

//Functions to check if game has been won --------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------player 1 win---------------------------------------------------------------------------------------
bool P1_Check_Horizontal_Win(){
  
  // loop through array's rows
  for ( int i = 0; i < rows; ++i ) {
    
      // loop through columns of current row
      for ( int j = 0; j < columns; ++j ){

        //check adjacent values
        if (board[i][j] == 1){ //only works if the first values isnt zero 
          if (board[i+1][j] == 1){
            if (board[i+2][j] == 1){
              if (board[i+3][j] == 1){
              Serial.print("player 1 horizontal win!");
              return true; //The game has been won horizontally!
              }
            }
          }
        }
        
        
      }
       
   } 
   
   return false;
}

bool P1_Check_Vertical_Win(){
  // loop through array's rows
  for ( int i = 0; i < rows; ++i ) {
    
      // loop through columns of current row
      for ( int j = 0; j < columns; ++j ){

        //check adjacent values
        if (board[i][j]== 1){ //only works if the first values isnt zero 
          if (board[i][j+1] == 1){
            if (board[i][j+2] == 1){
              if (board[i][j+3] == 1){
              Serial.print("player 1 vertical win!");
              return true; //The game has been won vertically!
              }
            }
          }
        }
        
      }

   } 
   return false;
}

bool P1_Check_Right_Diagonal_Win(){
  // loop through array's rows
  for ( int i = 0; i < rows; ++i ) {
    
      // loop through columns of current row
      for ( int j = 0; j < columns; ++j ){

        //check adjacent values
        if (board[i][j] == 1){
          if (board[i+1][j+1] == 1){
            if (board[i+2][j+2] == 1){
              if (board[i+3][j+3] == 1){
              Serial.print("player 1 diagonal win!");
              return true; //The game has been won diagonally!
              }
            }
          }
        }
        
      }

   } 
   return false;
}


bool P1_Check_Left_Diagonal_Win(){
  // loop through array's rows
  for ( int i = 0; i < rows; ++i ) {
    
      // loop through columns of current row
      for ( int j = 0; j < columns; ++j ){

        //check adjacent values
        if (board[i][j] == 1){ 
          if (board[i+1][j-1] == 1){
            if (board[i+2][j-2] == 1){
              if (board[i+3][j-3] == 1){
              Serial.print("player 1 diagonal win!");
              return true; //The game has been won diagonally!
              }
            }
          }
        }
        
      }

   } 
   return false;
}




//-------------------------------------------------------------player 2 win---------------------------------------------------------------------------------------


bool P2_Check_Horizontal_Win(){
  
  // loop through array's rows
  for ( int i = 0; i < rows; ++i ) {
    
      // loop through columns of current row
      for ( int j = 0; j < columns; ++j ){

        //check adjacent values
        if (board[i][j]== 2){ 
          if (board[i+1][j] == 2){
            if (board[i+2][j] == 2){
              if (board[i+3][j] == 2){
              Serial.print("player 2 horizontal win!");
              return true; //The game has been won horizontally!
              }
            }
          }
        }
        
        
      }
       
   } 
   
   return false;
}

bool P2_Check_Vertical_Win(){
  // loop through array's rows
  for ( int i = 0; i < rows; ++i ) {
    
      // loop through columns of current row
      for ( int j = 0; j < columns; ++j ){

        //check adjacent values
        if (board[i][j] == 2){ 
          if (board[i][j+1] == 2){
            if (board[i][j+2] == 2){
              if (board[i][j+3] == 2){
              Serial.print("player 2 vertical win!");
              return true; //The game has been won vertically!
              }
            }
          }
        }
        
      }

   } 
   return false;
}

bool P2_Check_Right_Diagonal_Win(){
  // loop through array's rows
  for ( int i = 0; i < rows; ++i ) {
    
      // loop through columns of current row
      for ( int j = 0; j < columns; ++j ){

        //check adjacent values
        if (board[i][j] == 2){
          if (board[i+1][j+1] == 2){
            if (board[i+2][j+2] == 2){
              if (board[i+3][j+3] == 2){
              Serial.print("player 2 diagonal win!");
              return true; //The game has been won diagonally!
              }
            }
          }
        }
        
      }

   } 
   return false;
}


bool P2_Check_Left_Diagonal_Win(){
  // loop through array's rows
  for ( int i = 0; i < rows; ++i ) {
    
      // loop through columns of current row
      for ( int j = 0; j < columns; ++j ){

        //check adjacent values
        if (board[i][j] == 2){
          if (board[i+1][j-1] == 2){
            if (board[i+2][j-2] == 2){
              if (board[i+3][j-3] == 2){
              Serial.print("player 2 diagonal win!");
              return true; //The game has been won diagonally!
              }
            }
          }
        }
        
      }

   } 
   return false;
}