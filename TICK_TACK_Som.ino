#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 led = Adafruit_SSD1306(128, 64, &Wire);

int s1 = 8, s2 = 9; // Input Pins

int gameScreen = 1;
int moves = 1;

int winner = 0;  //0 = Draw, 1 = Human, 2 = CPU
int board[]={0,0,0,0,0,0,0,0,0};// holds position data 0 is blank, 1 human, 2 is computer


void setup() {
  led.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.begin(115200);
  pinMode(s1,INPUT);
  pinMode(s2,INPUT);
  led.setTextColor(WHITE);
  led.cp437(true);
  led.clearDisplay();
  led.setTextSize(2);
  led.setCursor(5,15);
  led.print("TICK TACK TOE");
  led.drawRect( 0,  0,  128,     64,     WHITE);
  led.display();
  delay(2000);
}

void loop() {
  resetGame();
  platform();
  playGame();
  led.display();
  delay(200);
}


void playerMove()//// button//////////////////////////////////////
{
  int c = 7,c1= 15, i=0;
  int co = digitalRead(s1);
  int ok = digitalRead(s2);
  led.setCursor(c1,c);
  led.print("?"); ////////////////////////clear display/////////////
  led.display();
  Serial.print("\nPlayer Move:");
  if(co == 1)
      {
         delay(250);
         if(c==79)
         {
           c=7;
           c1 += 40;
           if(c1 == 135)
              c1 = 15;
         }
         else
            c += 24;
   }

  if(ok == 1)
      {
        delay(250);
          if(c == 7)
          {
            if(c1 == 15){ ////1
              if(board[1]==0)
                {
                  Serial.println("Player Move: 1");
                  board[1]=1;
                  drawPlayerMove(1);  
                }
            }
            if(c1 == 55){ ////2
              if(board[2]==0)
                {
                  Serial.println("Player Move: 2");
                  board[2]=1;
                  drawPlayerMove(2);  
                }
            }
            if(c1 == 95){///3
              if(board[3]==0)
                {
                  Serial.println("Player Move: 3");
                  board[3]=1;
                  drawPlayerMove(3);  
                }
            }
          }
          if(c == 33)
          {
             if(c1 == 15){  //4
              if(board[4]==0)
                {
                  Serial.println("Player Move: 4");
                  board[4]=1;
                  drawPlayerMove(4);  
                }
            }
            if(c1 == 55){ //5
              if(board[5]==0)
                {
                  Serial.println("Player Move: 5");
                  board[6]=1;
                  drawPlayerMove(5);  
                }
            }
            if(c1 == 95){ //6
              if(board[6]==0)
                {
                  Serial.println("Player Move: 6");
                  board[6]=1;
                  drawPlayerMove(6);  
                }
            }
          }
          
          if(c == 53)
          {
            if(c1 == 15){ //7
              if(board[7]==0)
                {
                  Serial.println("Player Move: 7");
                  board[7]=1;
                  drawPlayerMove(7);  
                }
            }
            if(c1 == 55){ //8
              if(board[8]==0)
                {
                  Serial.println("Player Move: 8");
                  board[8]=1;
                  drawPlayerMove(8);  
                }
            }
            if(c1 == 95){ //9
              if(board[9]==0)
                {
                  Serial.println("Player Move: 9");
                  board[9]=1;
                  drawPlayerMove(9);  
                }
            }
          }
  }
}


void resetGame()
{
  //buttonEnabled = false;
  for(int i=0;i<9;i++)
  {
   board[i]=0;
  }
  moves = 1;
  winner = 0;
  gameScreen=2;
}

void drawGameOverScreen()
{  
  led.fillScreen(BLACK);

  //Draw frame
  led.drawRect( 0,  0,  128,     64,     WHITE);

  //Print "Game Over" Text
  led.setCursor(5,20);
  led.setTextColor(WHITE);
  led.setTextSize(2);
  led.print("GAME OVER");
  

   if(winner == 0)
  {
    //Print "DRAW!" text 
    led.setCursor(5,20);
    led.setTextColor(WHITE);
    led.setTextSize(2);
    led.print("DRAW");
  }
   if(winner == 1)
  {
    //Print "HUMAN WINS!" text 
    led.setCursor(5,20);
    led.setTextColor(WHITE);
    led.setTextSize(2);
    led.print("HUMAN WINS");
  }
  
   if(winner == 2)
  {
    //Print "CPU WINS!" text 
    led.setCursor(5,20);
    led.setTextColor(WHITE);
    led.setTextSize(2);
    led.print("CPU WINS");
  }
   
}

void playGame()
{
  do
  {
    if(moves%2==1)
    {
     arduinoMove();
     printBoard();
     checkWinner();
    }else
    {
      playerMove(); 
      printBoard();
      checkWinner();  
    }
    moves++;
  }
  while (winner==0 && moves<10); 
  if(winner == 1)
  {
    Serial.println("HUMAN WINS");
    delay(3000);
    gameScreen=3;
    drawGameOverScreen();
  }else if(winner ==2)
  {
     Serial.println("CPU WINS");
     delay(3000);
     gameScreen=3;
     drawGameOverScreen();
  }else
  {
    Serial.println("DRAW");
    delay(3000);
    gameScreen=3;
    drawGameOverScreen();
  }
  
}

void printBoard()
{
  int i=0;
  Serial.println("Board: [");
  for(i=0;i<9;i++)
  {
    Serial.print(board[i]);
    Serial.print(",");
  }
  Serial.print("]");
}

int checkOpponent()
{
  if(board[0]==1 && board[1]==1 && board[2]==0)
  return 2;
  else if(board[0]==1 && board[1]==0 && board[2]==1)
  return 1;
  else if (board[1]==1 && board [2]==1 && board[0]==0)
  return 0;
  else if (board[3]==1 && board[4]==1 && board[5]==0)
  return 5;
  else if (board[4]==1 && board[5]==1&& board[3]==0)
  return 3;
  else if (board[3]==1 && board[4]==0&& board[5]==1)
  return 4;
  else if (board[1]==0 && board[4]==1&& board[7]==1)
  return 1;
  else
  return 100;
}

void arduinoMove()
{
  int b = 0;
  int counter =0;
  int movesPlayed = 0;
  Serial.print("\nArduino Move:");

  int firstMoves[]={0,2,6,8}; // will use these positions first

  for(counter=0;counter<4;counter++) //Count first moves played
  {
    if(board[firstMoves[counter]]!=0) // First move is played by someone
    {
      movesPlayed++;
    }
  }  
  do{
    if(moves<=2)
    {
      int randomMove =random(4); 
      int c=firstMoves[randomMove];
      
      if (board[c]==0)
      {  
        delay(1000);
        board[c]=2;
        Serial.print(firstMoves[randomMove]);
        Serial.println();
        drawCpuMove(firstMoves[randomMove]);
        b=1;
      }   
        
    }else
    {
    int nextMove = checkOpponent();
    if(nextMove == 100)
    {  
    if(movesPlayed == 4) //All first moves are played
    {
      int randomMove =random(9); 
      if (board[randomMove]==0)
      {  
        delay(1000);
        board[randomMove]=2;
        Serial.print(randomMove);
        Serial.println();
        drawCpuMove(randomMove);
        b=1;
      }   
    }else
    {
      int randomMove =random(4); 
      int c=firstMoves[randomMove];
      
      if (board[c]==0)
      {  
        delay(1000);
        board[c]=2;
        Serial.print(firstMoves[randomMove]);
        Serial.println();
        drawCpuMove(firstMoves[randomMove]);
        b=1;
      }   
  }
    }else
    {
       delay(1000);
       board[nextMove]=2;
       drawCpuMove(nextMove);
       b=1;
    }
  }
  }
  while (b<1);
}


void drawCpuMove(int move)
{
  switch(move)
  {
    case 0: led.setCursor(15,7); led.print("O");  break;
    case 1: led.setCursor(55,7); led.print("O");  break;
    case 2: led.setCursor(95,7); led.print("O");  break;
    case 3: led.setCursor(15,33); led.print("O");  break;
    case 4: led.setCursor(55,33); led.print("O");  break;
    case 5: led.setCursor(95,33); led.print("O");  break;
    case 6: led.setCursor(15,53); led.print("O");  break;
    case 7: led.setCursor(55,53); led.print("O");  break;
    case 8: led.setCursor(95,53); led.print("O");  break;
  }
}

void drawPlayerMove(int move)
{
  switch(move)
  {
    case 0: led.setCursor(15,7); led.print("X");  break;
    case 1: led.setCursor(55,7); led.print("X");  break;
    case 2: led.setCursor(95,7); led.print("X");  break;
    case 3: led.setCursor(15,33); led.print("X");  break;
    case 4: led.setCursor(55,33); led.print("X");  break;
    case 5: led.setCursor(95,33); led.print("X");  break;
    case 6: led.setCursor(15,53); led.print("X");  break;
    case 7: led.setCursor(55,53); led.print("X");  break;
    case 8: led.setCursor(95,53); led.print("X");  break;
  }
}

void checkWinner() 
// checks board to see if there is a winner
// places result in the global variable 'winner'
{
  int qq=0;
  // noughts win?
  if (board[0]==1 && board[1]==1 && board[2]==1) { 
    winner=1; 
  }
  if (board[3]==1 && board[4]==1 && board[5]==1) { 
    winner=1; 
  }
  if (board[6]==1 && board[7]==1 && board[8]==1) { 
    winner=1; 
  }  
  if (board[0]==1 && board[3]==1 && board[6]==1) { 
    winner=1; 
  }
  if (board[1]==1 && board[4]==1 && board[7]==1) { 
    winner=1; 
  }
  if (board[2]==1 && board[5]==1 && board[8]==1) { 
    winner=1; 
  }  
  if (board[0]==1 && board[4]==1 && board[8]==1) { 
    winner=1; 
  }
  if (board[2]==1 && board[4]==1 && board[6]==1) { 
    winner=1; 
  }
  // crosses win?
  if (board[0]==2 && board[1]==2 && board[2]==2) { 
    winner=2; 
  }
  if (board[3]==2 && board[4]==2 && board[5]==2) { 
    winner=2; 
  }
  if (board[6]==2 && board[7]==2 && board[8]==2) { 
    winner=2; 
  }  
  if (board[0]==2 && board[3]==2 && board[6]==2) { 
    winner=2; 
  }
  if (board[1]==2 && board[4]==2 && board[7]==2) { 
    winner=2; 
  }
  if (board[2]==2 && board[5]==2 && board[8]==2) { 
    winner=2; 
  }  
  if (board[0]==2 && board[4]==2 && board[8]==2) { 
    winner=2; 
  }
  if (board[2]==2 && board[4]==2 && board[6]==2) { 
    winner=2; 
  }
 
}

void platform(){
  led.clearDisplay();
  led.drawLine( 5, 20,   125,  20, WHITE);
  led.drawLine( 5, 40,   125,  40, WHITE);

  led.drawLine( 45, 5,   45,  60, WHITE);
  led.drawLine( 85, 5,   85,  60, WHITE);
}
