#include <TicTacToeDisplay.h>
int i = 1;
int j = 1;
int turn = 0;
int arr[3][3] = {
  {0,1,2},
  {3,4,5},
  {6,7,8}
  };               
int ree[3][3] = {
  {-1,-1,-1},
  {-1,-1,-1},
  {-1,-1,-1}
};
int lol[3][3] = {
  {-1,-1,-1},
  {-1,-1,-1},
  {-1,-1,-1}
};

TicTacToeDisplay display;

//ok so I have to somehow detect whether or not someone's won.
//the hard part, is figuring out whether a tile belongs to x or o...
//ok maybe 1d array would've been easier...but i'm in too deep lol.
//actually, if I create another array, that stores char's, it shouldn't
//be hard to track which tile belongs to who.
//Honestly, I just need a bunch of conditionals right?
//it doesn't even need parameters since everyything is global variable lol.
//so I dont need a reset function, I can just click the red button on the arduino lol
void victory();

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT_PULLUP);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);

  Serial.begin(9600);

  display.begin();
  display.drawBoard();
  delay(500);

}

void loop() {
  // put your main code here, to run repeatedly:

//When nothing happens, the default value(s) are: x =500ish, y = 500ish, SW = 1.
// down => x = 100ish, up => x = 1000 ish, left => y = 100 ish, right => y =1000ish

  int vrxValue = 0;
  int vryValue = 0;
  int swValue = 0;

  vrxValue = analogRead(A0);
  vryValue = analogRead(A1);
  swValue = digitalRead(2);

  //so design wise, I should definitely code in the select square thing first, 
  //then, if a press is detected, an x fills in. If the previous was an x (use a 
  // a variable to keep track lul), the next click will put in a circle.
  //somewhere down the code, I'll have conditionals for all the possible ways someone can win
  //once a conditional is fufilled, I'll do the ending sequence (set all the tracker variables
  //to like a million or something). The victory thing will keep on playin
  //until the button is clicked, then a conditional with like everything equal to a 
  //million puls the button being on will be fufilled and everything will restart.

  //so the fist thing I should focus on is selectin squares. I know I can make a function
  //for that, I just need to have conditionals that detect the joystick in the loop
  //body. Ok, so I need to use a for loop to keep the select square visibile.
  //for actually choosing the square, I'll just carry over the i in the draw
  //function

  //we don't need a loop since this is already a loop lol.

  // display.selectSquare(i);


  //if I messed around with 2d arrays, it might be easier (3x3). 
  //The only thing I would need is a formula, (i x j)-1.
  //i respresents which column we're in, j represents which row we're in

  if(vrxValue < 200)
  {
    Serial.println("down");

    if (j + 1 < 4)
    {
      j = j + 1;
    }
  }
  else if (vrxValue > 800)
  {
    Serial.println("up");

    if (j - 1 > 0)
    {
      j = j - 1;
    }
  }
  if (vryValue < 200)
  {
    Serial.println("left");
    
    if (i - 1 > 0)
    {
      i = i - 1;
    }

  }
  else if (vryValue > 800)
  {
    Serial.println("right");

    if (i + 1 < 4)
    {
      i = i + 1;
    }

  }
    

    display.selectSquare(arr[j-1][i-1]);
    delay(200);
    display.deselectSquare(arr[j-1][i-1]);

    //so there's an issue, I don't think its a good thing that
    //you can draw x's over o's and vice versa lol, lemme fix that, by created another 
    //array.

    if ((ree[j-1][i-1] != arr[j-1][i-1]) && (swValue == 0) && (turn == 0))
    {
      display.drawX(arr[j-1][i-1]);
      turn = 1;
      ree[j-1][i-1] = arr[j-1][i-1];
      lol[j-1][i-1] = 1;
    }

    else if ((ree[j-1][i-1] != arr[j-1][i-1]) && (swValue == 0) && (turn == 1))
    {
      display.drawO(arr[j-1][i-1]);
      turn = 0;
      ree[j-1][i-1] = arr[j-1][i-1];
      lol[j-1][i-1] = 0;
    }

    //is there an easier way to code this??? lol
    victory();
}

void victory()
{

  int counter = 0;
  //draws line thru top row
  if ((lol[0][0] == 1) && (lol[0][1] == 1) && (lol[0][2] ==1))
  {
    display.drawVictoryLine(0,2); 
    delay(500);
    counter++;
  }
  //draws a victory line through the middle row
  if ((lol[1][0] == 1) && (lol[1][1] == 1) && (lol[1][2] ==1))
  {
    display.drawVictoryLine(3,5); 
    delay(500);
    counter++;
  }

// //draws a victory line through the bottom row
  if ((lol[2][0] == 1) && (lol[2][1] == 1) && (lol[2][2] ==1))
  {
    display.drawVictoryLine(6,8);
    delay(500);
    counter++;
  }

  //draws a victory line through leftmost column
  if ((lol[0][0] == 1) && (lol[1][0] == 1) && (lol[2][0] ==1))
  {
    display.drawVictoryLine(0,6); 
    delay(500);
    counter++;
  }
  //draws victory line thru middle column
  if ((lol[0][1] == 1) && (lol[1][1] == 1) && (lol[2][1] ==1))
  {
    display.drawVictoryLine(1,7); 
    delay(500);
    counter++;
  }
  //draws victory line thru rightmost column
  if ((lol[0][2] == 1) && (lol[1][2] == 1) && (lol[2][2] ==1))
  {
    display.drawVictoryLine(2,8); 
    counter++;
  }
  //draws victory line diagonally
  if ((lol[0][0] == 1) && (lol[1][1] == 1) && (lol[2][2] ==1))
  {
    display.drawVictoryLine(0,8); 
    delay(500);
    counter++;
  }
  //draws victory line diagonally
  if ((lol[0][2] == 1) && (lol[1][1] == 1) && (lol[2][0] ==1))
  {
    display.drawVictoryLine(2,6); 
    delay(500);
    counter++;
  }


    //draws line thru top row
  if ((lol[0][0] == 0) && (lol[0][1] == 0) && (lol[0][2] == 0))
  {
    display.drawVictoryLine(0,2); 
    delay(500);
    counter--;
  }
  //draws a victory line through the middle row
  if ((lol[1][0] == 0) && (lol[1][1] == 0) && (lol[1][2] == 0))
  {
    display.drawVictoryLine(3,5); 
    delay(500);
    counter--;
  }

// //draws a victory line through the bottom row
  if ((lol[2][0] == 0) && (lol[2][1] == 0) && (lol[2][2] == 0))
  {
    display.drawVictoryLine(6,8);
    delay(500);
    counter--;
  }

  //draws a victory line through leftmost column
  if ((lol[0][0] == 0) && (lol[1][0] == 0) && (lol[2][0] == 0))
  {
    display.drawVictoryLine(0,6); 
    delay(500);
    counter--;
  }
  //draws victory line thru middle column
  if ((lol[0][1] == 0) && (lol[1][1] == 0) && (lol[2][1] == 0))
  {
    display.drawVictoryLine(1,7); 
    delay(500);
    counter--;
  }
  //draws victory line thru rightmost column
  if ((lol[0][2] == 0) && (lol[1][2] == 0) && (lol[2][2] == 0))
  {
    display.drawVictoryLine(2,8); 
    counter--;
  }
  //draws victory line diagonally
  if ((lol[0][0] == 0) && (lol[1][1] == 0) && (lol[2][2] == 0))
  {
    display.drawVictoryLine(0,8); 
    delay(500);
    counter--;
  }
  //draws victory line diagonally
  if ((lol[0][2] == 0) && (lol[1][1] == 0) && (lol[2][0] == 0))
  {
    display.drawVictoryLine(2,6); 
    delay(500);
    counter--;
  }

  if((lol[0][0] != -1) && (lol[0][1] != -1) && (lol[0][2] != -1) && (lol[1][0] != -1) && (lol[1][1] != -1) && (lol[1][2] != -1) && (lol[2][0] != -1) && (lol[2][1] != -1) && (lol[2][2] != -1) && (counter == 0))
  {
    display.flashScreen();
    delay(500);
    display.drawSmallText("Congratulations! Both of you are losers!!");
    delay(2000);
  }

  if (counter == 1)
  {
    display.flashScreen();
    delay(500);
    display.drawSmallText("Congratulations Player X! You win!");
    delay(2000);
  }
  else if (counter == -1)
  {
    display.flashScreen();
    delay(500);
    display.drawSmallText("Congratulations Player O! You win!");
    delay(2000);
  }
}