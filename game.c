
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";
int speed = 10;
int speedcounter;
int levelup = 0;
int move = 0;
int highestpoint = 26;


struct Shape{
  int r0[4][4];
  int r1[4][4];
  int r2[4][4];
  int r3[4][4];
}Shape;

struct Block{
  int xcoord;
  int ycoord;
  int rotation;
  //No shape takes up more then 4x4 blocks. The I shape is the largest one with 4 blocks wide/tall
  int shape[4][4];
  int shapenmr;
}Block;

<<<<<<< HEAD
struct Shape {
  int shaperotation1;
  int shaperotation2;
  int shaperotation3;
  int shaperotation4;
}
=======

>>>>>>> 95cf67635362ae0f885148dab89aa8627a81bd48
//The game is a 7*26 grid
int fallenblocks[26][7];

const int leftwall = 6;
const int rightwall = 0;
const int centerX = 3;
const int top = 0;
const int bottom = 25;

static struct Block currentblock;
static struct Shape currentshape;
static struct Shape nextshape;
static struct Shape O;
static struct Shape L;
static struct Shape I;
static struct Shape T;
static struct Shape J;
static struct Shape Z;
static struct Shape S;
int score = 0;

void makeshape(int shape){
    int x;
    int y;
    //Clear currentshape
    for(x = 0; x < 4; x++){
      for (y = 0; y < 4; y++){
        currentshape.r0[y][x] = 0;
        currentshape.r1[y][x] = 0;
        currentshape.r2[y][x] = 0;
        currentshape.r3[y][x] = 0;
      }
    }
    switch (shape)
    {
    case 0:
      //square
      currentshape.r0[0][0] = 1;
	    currentshape.r0[1][0] = 1;
	    currentshape.r0[0][1] = 1;
	    currentshape.r0[1][1] = 1;
    break;
    case 1:
      //L
      currentshape.r0[0][0] = 1;
    	currentshape.r0[0][1] = 1;
    	currentshape.r0[0][2] = 1;
    	currentshape.r0[1][0] = 1;

      currentshape.r1[0][0] = 1;
    	currentshape.r1[0][1] = 1;
    	currentshape.r1[1][1] = 1;
    	currentshape.r1[2][1] = 1;

      currentshape.r2[0][2] = 1;
    	currentshape.r2[1][0] = 1;
    	currentshape.r2[1][1] = 1;
    	currentshape.r2[1][2] = 1;

      currentshape.r3[0][0] = 1;
    	currentshape.r3[1][0] = 1;
    	currentshape.r3[2][0] = 1;
    	currentshape.r3[2][1] = 1;
      break;

    case 2:
       //I
      currentshape.r0[0][0] = 1;
      currentshape.r0[0][1] = 1;
      currentshape.r0[0][2] = 1;
      currentshape.r0[0][3] = 1;

      currentshape.r1[0][0] = 1;
      currentshape.r1[1][0] = 1;
      currentshape.r1[2][0] = 1;
      currentshape.r1[3][0] = 1;

      currentshape.r2[0][0] = 1;
      currentshape.r2[0][1] = 1;
      currentshape.r2[0][2] = 1;
      currentshape.r2[0][3] = 1;

      currentshape.r3[0][0] = 1;
      currentshape.r3[1][0] = 1;
      currentshape.r3[2][0] = 1;
      currentshape.r3[3][0] = 1;

      break;
    case 3:
       // T shape
      currentshape.r0[0][0] = 1;
      currentshape.r0[0][1] = 1;
      currentshape.r0[0][2] = 1;
      currentshape.r0[1][1] = 1;

      currentshape.r1[0][1] = 1;
      currentshape.r1[1][0] = 1;
      currentshape.r1[1][1] = 1;
      currentshape.r1[2][1] = 1;

      currentshape.r2[0][1] = 1;
      currentshape.r2[1][0] = 1;
      currentshape.r2[1][1] = 1;
      currentshape.r2[1][2] = 1;

      currentshape.r3[0][0] = 1;
      currentshape.r3[1][0] = 1;
      currentshape.r3[2][0] = 1;
      currentshape.r3[1][1] = 1;
      break;

    case 4:
  // J shape

    currentshape.r0[0][0] = 1;
    currentshape.r0[0][1] = 1;
    currentshape.r0[0][2] = 1;
    currentshape.r0[1][2] = 1;

    currentshape.r1[0][1] = 1;
    currentshape.r1[1][1] = 1;
    currentshape.r1[2][0] = 1;
    currentshape.r1[2][1] = 1;

    currentshape.r2[0][0] = 1;
    currentshape.r2[1][0] = 1;
    currentshape.r2[1][1] = 1;
    currentshape.r2[1][2] = 1;

    currentshape.r3[0][0] = 1;
    currentshape.r3[0][1] = 1;
    currentshape.r3[1][0] = 1;
    currentshape.r3[2][0] = 1;
      break;

    case 5:
  // Z shape
    currentshape.r0[0][0] = 1;
    currentshape.r0[0][1] = 1;
    currentshape.r0[1][1] = 1;
    currentshape.r0[1][2] = 1;

    currentshape.r1[0][1] = 1;
    currentshape.r1[1][0] = 1;
    currentshape.r1[1][1] = 1;
    currentshape.r1[2][0] = 1;

    currentshape.r2[0][0] = 1;
    currentshape.r2[0][1] = 1;
    currentshape.r2[1][1] = 1;
    currentshape.r2[1][2] = 1;

    currentshape.r3[0][1] = 1;
    currentshape.r3[1][0] = 1;
    currentshape.r3[1][1] = 1;
    currentshape.r3[2][0] = 1;

      break;

    case 6:
  // S shape
    currentshape.r0[0][1] = 1;
    currentshape.r0[0][2] = 1;
    currentshape.r0[1][0] = 1;
    currentshape.r0[1][1] = 1;
  
    currentshape.r1[0][0] = 1;
    currentshape.r1[1][0] = 1;
    currentshape.r1[1][1] = 1;
    currentshape.r1[2][1] = 1;

    currentshape.r2[0][1] = 1;
    currentshape.r2[0][2] = 1;
    currentshape.r2[1][0] = 1;
    currentshape.r2[1][1] = 1;

    currentshape.r3[0][0] = 1;
    currentshape.r3[1][0] = 1;
    currentshape.r3[1][1] = 1;
    currentshape.r3[2][1] = 1;
      break;
    
    default:
      break;
    }
  }


/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int* trise = (volatile int*) 0xbf886100;
  *trise = *trise  & ~0xff;
  TRISD = (TRISD & ~0xfe0) | 0xfe0; 
  int periodms = 10;
  int scale = 256;
  int ck_freq = 80000000;
  T2CONCLR = 0x8000;
  T2CON = T2CON | 0x70; 
  PR2 = ((ck_freq/scale) / periodms) ; 
  T2CON = T2CON | 0x8000; 
  //Startpositions
  currentblock.xcoord = centerX;
  currentblock.ycoord = top;
  currentblock.rotation = 1;
  int i;
  //Initiate shapes
  
  int y;
  int x;
  makeshape(0);
  currentblock.shapenmr = 0;
  //First shape
  for(y = 0; y < 4; y++){
     for(x = 0; x < 4; x++){
       currentblock.shape[y][x] = currentshape.r0[y][x];
    }
  }
  return;
}

void changeshape(int newshape[4][4]){
    int y;
    int x;
    for(y = 0; y < 4; y++){ 
		  for(x = 0; x < 4; x++){
        currentblock.shape[y][x] = newshape[y][x];
      }
    }
}


void reset(void){
  int i = 0;
  i = 0;
    for(i = 0; i < sizeof(currentworld); i++){
    currentworld[i] = 0;
  }
  currentblock.xcoord = centerX;
  currentblock.ycoord = top;
  currentblock.rotation = 0;
  currentblock.shapenmr = 0;
  makeshape(0);
  changeshape(currentshape.r0);
  int x;
  int y;
  highestpoint = 26;
  speed = 10;
  for(y = 0; y < 26; y++){
    for (x = 0; x < 7; x++){
        fallenblocks[y][x] = 0;
      }
    }
  } 


void rotate(){
  if(currentblock.shapenmr != 0){
  if(currentblock.rotation > 3){
    currentblock.rotation = 0;
  }
  switch (currentblock.rotation)
  {
   case 0:
      if(checkcollision(0,0, currentshape.r0) != 1){
          changeshape(currentshape.r0);
          currentblock.rotation++;
      }
    break;
    case 1:
      if(checkcollision(0,0, currentshape.r1) != 1){
          changeshape(currentshape.r1);
          currentblock.rotation++;
      }
    break;
    case 2:
      if(checkcollision(0,0, currentshape.r2) != 1){
          changeshape(currentshape.r2);
          currentblock.rotation++;
      }         
    break;
    case 3:
      if(checkcollision(0,0, currentshape.r3) != 1){
          changeshape(currentshape.r3);
          currentblock.rotation++;
      }
    break;
    default:
    break;
       }
  }
}

void checkbuttons(){
    int boolean = 0;
    int sw = getsw();
    int btns = getbtns();
    //Bitwise and för att se om 1000 är sann
    if (btns & 0x4 && currentblock.xcoord < leftwall){
      //Check if currentblock can move left
      if(checkcollision(0,1, currentblock.shape) != 1){
        //If not, move left
        currentblock.xcoord = currentblock.xcoord + 1;
      }// check -//- can move right
    } else if (btns & 0x2 && currentblock.xcoord > rightwall){
      if(checkcollision(0,-1, currentblock.shape) != 1){
        currentblock.xcoord = currentblock.xcoord - 1;
      }
      //Rotate block
    } else if (btns & 0x1){
      rotate();
    } else if (btns){
      if(checkcollision(1,0, currentblock.shape) != 1){
          currentblock.ycoord += 1;
        } else {
        //Else collision happened
        collision();
        }
    }
}

int checkcollision(int checky, int checkx, int currentshape[4][4]){
  int y;
  int x;
	for(y = 0; y < 4; y++){
		for(x = 0; x < 4; x++){
      //Checks if block hit bottom
			if (currentshape[y][x] == 1 && currentblock.ycoord + y >= 25){
					return 1;
			}
      //Check if block hit fallen blocks
      if(currentshape[y][x] == 1 && fallenblocks[currentblock.ycoord + y + checky][currentblock.xcoord + x + checkx] == 1){
        return 1;
      }
      //Check if block hit walls
      if(currentshape[y][x] == 1 && (currentblock.xcoord + checkx + x > 6 || currentblock.xcoord + checkx < 0 )){
        return 1;
      }
		}
	}
}

void clearrow(int ycoord){
  levelup++;
  int y;
  int x;
  //Clear all rows above ycoord
  for (y = ycoord; y > 0; y--){
    for(x = 0; x < 7; x++){
        fallenblocks[y][x] = fallenblocks[y-1][x];
    }
  }
  //Upper row should be empty
  for(x = 0; x < 7; x++){
        fallenblocks[0][x] = 0;
  }
  highestpoint++;
}

void collision(){
    int y;
    int x;
    //Collision happened, add currentblocks position to fallenblocks
    for(y = 0; y < 4; y++){
		  for(x = 0; x < 4; x++){
		  	if (currentblock.shape[y][x] == 1){
					fallenblocks[currentblock.ycoord + y][currentblock.xcoord + x] = 1;
          if(currentblock.ycoord + y < highestpoint){
            highestpoint =  (currentblock.ycoord + y);
          }
			  }
		  }
	  }
    //Check if row is filled
    for(y = 0; y < 26; y++){
      int xcount = 0;
      for(x = 0; x < 7; x++){
        if(fallenblocks[y][x] == 1){
          xcount++;
        }
      }
      //If row filled, clear row
      if(xcount == 7){
        clearrow(y);
      }
    }
    //Check top row, if fallenblocks at top row, game lost
    for(x = 0; x  < 7; x++){
      if(fallenblocks[0][x] == 1){
        /*fillscreen();*/
        drawgameover();
        quicksleep(10000000);
        reset();
        drawgrid();
        display_image();
        quicksleep(10000000);
      }
    }
    
    //Reset currentblock
    currentblock.ycoord = top; 
    currentblock.xcoord = centerX;
    currentblock.rotation = 1;
    currentblock.shapenmr++;
    if(currentblock.shapenmr > 6){
      currentblock.shapenmr = 0;
    }
    makeshape(currentblock.shapenmr);
    changeshape(currentshape.r0);
    //Let the player pause a shoort moment
    quicksleep(1000000);
    //Levelup => speed increase
    if(levelup % 4 && speed != 0){
          speed--;
          levelup = 0;
    }
}



//draw all fallen blocks
void drawfallen(void){
    int x;
    int y;
    for(y = 0; y < 26; y++){
      for (x = 0; x < 7; x++){
        //For all blocks that have fallen in a position, aka == 1, draw block in that position
        if(fallenblocks[y][x] == 1){
          drawblock(y,x);
        }
    }
  }
}


fillscreen(){
  int y;
  int x;
  for(y = 0; y < 26; y++){
      for(x = 0; x < 7; x++){
          fallenblocks[y][x] = 1;
                   //G
          fallenblocks[2][1] = 1;
          fallenblocks[2][2] = 1;
          fallenblocks[2][3] = 1;
          fallenblocks[2][4] = 1;
          fallenblocks[3][4] = 1;
          fallenblocks[4][1] = 1;
          fallenblocks[4][2] = 1;
          fallenblocks[4][4] = 1;
          fallenblocks[5][1] = 1;
          fallenblocks[5][4] = 1;
          fallenblocks[6][1] = 1;
          fallenblocks[6][2] = 1;
          fallenblocks[6][3] = 1;
          fallenblocks[6][4] = 1;
          
        
          //A
          fallenblocks[8][1] = 1;
          fallenblocks[8][2] = 1;
          fallenblocks[8][3] = 1;
          fallenblocks[8][4] = 1;
          fallenblocks[9][1] = 1;
          fallenblocks[9][4] = 1;
          fallenblocks[10][1] = 1;
          fallenblocks[10][2] = 1;
          fallenblocks[10][3] = 1;
          fallenblocks[10][4] = 1;
          fallenblocks[11][1] = 1;
          fallenblocks[11][4] = 1;
          fallenblocks[12][1] = 1;
          fallenblocks[12][4] = 1;
          //M
          fallenblocks[14][1] = 1;
          fallenblocks[14][2] = 1;
          fallenblocks[14][4] = 1;
          fallenblocks[14][5] = 1;
          fallenblocks[15][1] = 1;
          fallenblocks[15][3] = 1;
          fallenblocks[15][5] = 1;
          fallenblocks[16][1] = 1;
          fallenblocks[16][5] = 1;
          fallenblocks[17][1] = 1;
          fallenblocks[17][5] = 1;
          fallenblocks[18][1] = 1;
          fallenblocks[18][5] = 1;
          //E
          fallenblocks[20][1] = 1;
          fallenblocks[20][2] = 1;
          fallenblocks[20][3] = 1;
          fallenblocks[20][4] = 1;
          fallenblocks[21][4] = 1;
          fallenblocks[22][2] = 1;
          fallenblocks[22][3] = 1;
          fallenblocks[22][4] = 1;
          fallenblocks[23][4] = 1;
          fallenblocks[24][1] = 1;
          fallenblocks[24][2] = 1;
          fallenblocks[24][3] = 1;
          fallenblocks[24][4] = 1;

          drawfallen();
          drawgrid();
          display_image();
          quicksleep(100000);
        }
      }
  for(y = 0; y < 26; y++){
      for(x = 0; x < 7; x++){

          fallenblocks[y][x] = 0;
           //O
          fallenblocks[2][1] = 1;
          fallenblocks[2][2] = 1;
          fallenblocks[2][3] = 1;
          fallenblocks[2][4] = 1;
          fallenblocks[3][1] = 1;
          fallenblocks[3][4] = 1;
          fallenblocks[4][1] = 1;
          fallenblocks[4][4] = 1;
          fallenblocks[5][1] = 1;
          fallenblocks[5][4] = 1;
          fallenblocks[6][1] = 1;
          fallenblocks[6][2] = 1;
          fallenblocks[6][3] = 1;
          fallenblocks[6][4] = 1;


          //V
          fallenblocks[8][1] = 1;
          fallenblocks[8][4] = 1;
          fallenblocks[9][1] = 1;
          fallenblocks[9][4] = 1;
          fallenblocks[10][1] = 1;
          fallenblocks[10][4] = 1;
          fallenblocks[11][1] = 1;
          fallenblocks[11][4] = 1;
          fallenblocks[12][2] = 1;
          fallenblocks[12][3] = 1;

          //E
          fallenblocks[14][1] = 1;
          fallenblocks[14][2] = 1;
          fallenblocks[14][3] = 1;
          fallenblocks[14][4] = 1;
          fallenblocks[15][4] = 1;
          fallenblocks[16][2] = 1;
          fallenblocks[16][3] = 1;
          fallenblocks[16][4] = 1;
          fallenblocks[17][4] = 1;
          fallenblocks[18][1] = 1;
          fallenblocks[18][2] = 1;
          fallenblocks[18][3] = 1;
          fallenblocks[18][4] = 1;

          //R
          fallenblocks[20][1] = 1;
          fallenblocks[20][2] = 1;
          fallenblocks[20][3] = 1;
          fallenblocks[20][4] = 1;
          fallenblocks[21][1] = 1;
          fallenblocks[21][4] = 1;
          fallenblocks[22][1] = 1;
          fallenblocks[22][2] = 1;
          fallenblocks[22][3] = 1;
          fallenblocks[22][4] = 1;
          fallenblocks[23][2] = 1;
          fallenblocks[23][4] = 1;
          fallenblocks[24][1] = 1;
          fallenblocks[24][4] = 1;
          drawfallen();
          display_image();
          quicksleep(100000);
        }
      }
  
  }  

void fall(int multiplier){
    //Increase ycoord if collision hasnt happened
    if(checkcollision(1,0, currentblock.shape) != 1){
    move++;
    if(move == speed){
      currentblock.ycoord += 1 * multiplier;
      move = 0;
    }
    } else {
      //Else collision happened
      collision();
    }
}


/* This function is called repetitively from the main program */
void labwork( void)
{
  static int globalcounter = 0;
  //interrupt
  if (IFS(0) & 0x100) //Om 9;e biten, catches the flag 
  {
  //Reset interuppt
  IFS(0) = IFS(0) & ~0x100;
  //increase counter
  globalcounter ++;
  }

  if(globalcounter == 1){
    //Check input
    checkbuttons();
    //Increase ycoord if collision hasnt happened
    fall(1);

    //Draw current block, fallen blocks and grid
    drawshape(currentblock.ycoord,currentblock.xcoord,1,currentblock.shape);
    drawfallen();
    drawgrid();
    /* Design test
    int y;
    int x;
    for(y = 0; y < highestpoint; y++){
      drawblock(y, 7);
    }
    for(x = 0; x < 8; x++){
      drawblock(-1, x);
    }*/

    tick( &mytime );
    display_image();
    //Reset counter
    globalcounter = 0;
  }
}



