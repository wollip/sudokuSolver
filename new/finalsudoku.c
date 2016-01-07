// final version of sudoku solver
/*
it is too hard to explain how the code runs exactly,
there are a few things we have yet to learn in class
like the 
for, switch/case, recursion, arrays (multidimension arrays), pointers, methods,
however google is your friend
if you want you can input your own sudoku and see if the program can solve it
if there are any bugs or errors that you find, i am more than willing to check it over
i have not tested the code completely but i do know it works for 3 sudokus for sure
also sorry for the lack of comment or understandable comment
you can deal with it

	-JASON Peng, 2015

ps, there a few lines of printf that i commented out. 
	i used them as i code to see what the program is doing
	easier than drawing a flow chart or that chart thingy we do in class

*/

#include <stdio.h>

// prompts the user to input the sudoku storing it in sudoku
void input(int (*sudoku)[9][9]){
  printf("Separate each value by space\nif value is unknown, enter 0\n");
  for (int i = 0; i < 9; i++){
      printf("\nInput the %d row of values\n",i+1);
      scanf("%d %d %d %d %d %d %d %d %d",
       &sudoku[0][i][0],&sudoku[0][i][1],&sudoku[0][i][2],
       &sudoku[0][i][3],&sudoku[0][i][4],&sudoku[0][i][5],
       &sudoku[0][i][6],&sudoku[0][i][7],&sudoku[0][i][8]);
  }
}
// convert the sudoku values to known, unknown, 
// known is store as primes in sudoku
// unknown is stored as 1 or 0 in value
void convert(int (*sudoku)[9][9], int (*value)[9][9]){
    static int arraylength = 9;
    int i = 0, i2 = 0;
    while(i<arraylength){
        while (i2 <arraylength){
            switch (sudoku[0][i][i2]){
                case 0:
                    sudoku[0][i][i2] = 223092870;
                    value[0][i][i2] = 0;
                    break;
                case 1:
                    sudoku[0][i][i2] = 2;
                    break;
                case 2:
                    sudoku[0][i][i2] = 3;
                    break;
                case 3:
                    sudoku[0][i][i2] = 5;
                    break;
                case 4:
                    sudoku[0][i][i2] = 7;
                    break;
                case 5:
                    sudoku[0][i][i2] = 11;
                    break;
                case 6:
                    sudoku[0][i][i2] = 13;
                    break;
                case 7:
                    sudoku[0][i][i2] = 17;
                    break;
                case 8:
                    sudoku[0][i][i2] = 19;
                    break;
                case 9:
                    sudoku[0][i][i2] = 23;
                    break;
                default: 
                    printf("Invalid Input at %d , %d\n", i, i2);
                    break;
          }
          i2++;  
        }
        i2 = 0;
        i++;
    }  
}
// changes the sudoku back to values between 1 to 9
// so the users can understand the output
void unconvert(int (*sudoku)[9][9]){
    for (int i = 0; i <9; i++){
      for (int i2 = 0; i2 < 9; i2++){
        switch (sudoku[0][i][i2]){
          case 2:
              sudoku[0][i][i2] = 1;
              break;
          case 3:
              sudoku[0][i][i2] = 2;
              break;
          case 5:
              sudoku[0][i][i2] = 3;
              break;
          case 7:
              sudoku[0][i][i2] = 4;
              break;
          case 11:
              sudoku[0][i][i2] = 5;
              break;
          case 13:
              sudoku[0][i][i2] = 6;
              break;
          case 17:
              sudoku[0][i][i2] = 7;
              break;
          case 19:
              sudoku[0][i][i2] = 8;
              break;
          case 23:
              sudoku[0][i][i2] = 9;
              break;
          default:
              printf("error while converting back to normal\n");
              break;
        }
      }
    }
}
// this prints out any 9x9 matrix that contains values between 0 and 9
void printraw(int (*raw)[9][9]){
  printf("raw graph start\n");
  for (int i = 0; i < 9; i++){
    for (int i2 =0; i2 < 9; i2++){
      if (raw[0][i][i2] <=9){
        printf("%2d\t", raw[0][i][i2]);
      } else{
        printf("NA\t");
      }
    }
    printf("\n");
  }
  printf("\n\n");
}
// checks to see if the sudoku is complete
// 1 for complete
// 0 for incomplete
int issudokucomplete(int (*value)[9][9]){
    for (int i = 0; i<9; i++){
      for (int i2 = 0; i2<9; i2++){
        if (value[0][i][i2]==0){
          return 0;
        }
      }
    }
    printf("sudoku is completed\n");
    return 1;
}
// checks to see if the values found by logic is a valid value 
// return 1 if it is found
// return 0 if it is not found
// this is used to change the values in *value
int isvaluefound(int sudoku){
  if (sudoku == 2||
      sudoku == 3||
      sudoku == 5||
      sudoku == 7||
      sudoku == 11||
      sudoku == 13||
      sudoku == 17||
      sudoku == 19||
      sudoku == 23){
      return 1;
  }else{
      return 0;
  }
}
// checks to see if there is error in the sudoku
// return 0 then there is error
// return 1 means no error
int isright(int (*sudoku)[9][9], int (*value)[9][9]){
  for (int i = 0; i < 9; i++){
    for (int i2 = 0; i2 < 9; i2++){
      // testing each value
      if (value[0][i][i2]){
        // if the value is known
        for (int i3 = 0; i3<0; i3++){
          // for each value in that row
          if(value[0][i][i3] && i2 != i3){
            // that is known and not the same location
            if (sudoku[0][i][i2] == sudoku[0][i][i3]){
              // if they are the same then we have a problem
              //printf("error at %d,%d and %d,%d\n", i,i2,i,i3);
              return 0;
            }
          }
          // for each value in that column
          if (value[0][i3][i2] && i3 != i){
            // that is know and not in the same location
            if (sudoku[0][i3][i2] == sudoku[0][i][i2]){
              // if they are the same then we have a problem.
              //printf("error at %d,%d and %d,%d\n", i3,i2,i,i2);
              return 0;
            }
          }
        }
	      int ix , iy;
	      for  (int si = 0; si < 3; si++){
		      for ( int si2 = 0; si2 < 3; si2++){
			      //tests each value within the square
			      ix = i/3*3 +si;
			      iy = i2/3*3+si2;
			      if (value[0][ix][iy]){
				      // if the value is known 
				      if (sudoku[0][i][i2] == sudoku[0][ix][iy]&& ix != i && iy != i2){
					      //printf( "error at %d,%d and %d, %d\n", i,i2,ix,iy);
					      return 0;
				      }
			      }
		      }
	      }
      }
    }
  }

  return 1;
}
// logic 1 is basically
// if there is a value that is known,
// then that value can not exist in the same column row or square
int blogic1(int (*sudoku)[9][9], int (*value)[9][9], int depth){
  int count = 0;
  for (int i = 0; i < 9; i++){
    for (int i2 = 0; i2 < 9; i2++){
      // first 2 loop is just to go through all 9x9 values
      // if the value of this square is unknown
      if (value[0][i][i2] == 0){
        // then we will go through each value in that row
        for (int i3 = 0; i3 <9; i3++){
          // and if a particular value in that row is known
          if (value[0][i][i3] == 1){
            // and it is a divisor of the unknown value
            if (sudoku[0][i][i2]%sudoku[0][i][i3]==0 && sudoku[0][i][i2] != sudoku[0][i][i3] ){
              // then divide it by that value
              sudoku[0][i][i2] = sudoku[0][i][i2]/sudoku[0][i][i3];
              if (isvaluefound(sudoku[0][i][i2])){
                value[0][i][i2] = depth;
                count++;
              }  
            }
          }
	        if (value[0][i3][i2] == 1){
            if (sudoku[0][i][i2]%sudoku[0][i3][i2]==0 && sudoku[0][i][i2] != sudoku[0][i3][i2]){
              sudoku[0][i][i2] = sudoku[0][i][i2]/sudoku[0][i3][i2];
              if (isvaluefound(sudoku[0][i][i2])){
                value[0][i][i2] = depth;
                count++;
              }  
            }
          }
        }
        int i4 = i/3;
        int i5 = i2/3;
        for (int i6 = i4*3; i6 < (i4*3+3); i6++){
          for (int i7 = i5*3; i7 < (i5*3+3); i7++){
            if (value[0][i6][i7]){
              if(sudoku[0][i][i2]%sudoku[0][i6][i7]==0&&sudoku[0][i][i2]!=sudoku[0][i6][i7]){
                sudoku[0][i][i2] = sudoku[0][i][i2]/sudoku[0][i6][i7];
                if(isvaluefound(sudoku[0][i][i2])){
                  value[0][i][i2] = depth;
                  count++;
                }
              }
            }
          }
        }
      }
    }
  }
  //printf ("blogic1 has found %d values\n", count);
  return count;
}
// logic 2
// if there is only 1 place where a value can exist 
// in a row, column or square
// then that place must be that value
int blogic2(int (*sudoku)[9][9], int (*value)[9][9], int depth){
  int returnvalue=0;
  int primes[9] ={2,3,5,7,11,13,17,19,23};
  for(int i = 0; i <9; i++){
    // for each row for part 1, and for each column for part 2
    for (int i2 = 0; i2<9; i2++){
        // test each value of prime  (part 1)
        int count = 0, storei3;
        for (int i3 =0; i3<9; i3++){
          // against each sudoku value within that row  
          if (sudoku[0][i][i3]%primes[i2]==0){
            // if the prime is a divisor of that  sudoku value  
            if (value[0][i][i3]>0){
              // and that sudoku value is known, then we will move on to the next prime  
              count = 10;
              break;
            }else{
              // if that sudoku value is unknown, then we will increase count by 1
              // and store the location of that sudoku value  
              storei3 =i3;
              count++;
            }
          }
        }
        if (count == 1){
            // if count is 1, then only one sudoku value in that row is divisible by the prime
            // therefore that sudoku value has to be that prime
            sudoku[0][i][storei3] = primes[i2];
            value[0][i][storei3] = depth;
            returnvalue++;
            //printf(" sudoku[%d][%d] = %d\n", i, storei3, sudoku[0][i][storei3]);
        }    
        ///////////////////////////////////////////////// part 2
        count = 0;
        for (int i3 = 0; i3<9;i3++){
          if (sudoku[0][i3][i]%primes[i2]==0){
            if(value[0][i3][i]>0){
              count = 10;
              break;
            }else{
              storei3 = i3;
              count++;
            }
          }
        }
        if (count == 1){
          sudoku[0][storei3][i] = primes[i2];
          value[0][storei3][i] = depth;
          returnvalue++;
        }
    }
  } 
  for (int i =0; i<3; i++){
    for (int i2 = 0; i2<3; i2++){
      // for each square
      for (int pi =0; pi <9; pi++){
        // for each prime
        int storesi, storesi2;
        int boolean = 0;
        int count = 0;
        for (int si =0; si<3;si++ ){
          for (int si2 = 0; si2<9; si2++){
            // for each value in the square
            if (sudoku[0][i*3+si][i2*3+si2]%primes[pi]==0){
              // if the value is divisible by the prime
              if (value[0][i*3+si][i2*3+si2]>0){
                // if the value is a known value
                count = 10;
                boolean =1;
                break;
              }else{
                // if value is unknown,
                count++;
                storesi = si;
                storesi2 = si2;
              }
            }
          }
          if (boolean){
            break;
          }
        }
        if (count == 1){
          sudoku[0][i*3+storesi][i2*3+storesi2] = primes[pi];
          value[0][i*3+storesi][i2*3+storesi2] =depth;
          returnvalue++;
        }
      } 
    }
  } 
  //printf("blogic2 has found %d values\n", returnvalue);
  return returnvalue;
}
// combines logic 1 and 2 together for ease of use
void totallogic(int (*sudoku)[9][9], int (*value)[9][9], int depth){
	int boolean1 =1, boolean2=1;
	while(boolean1 != 0){
	  boolean1 = blogic1(sudoku , value, depth);
    boolean2 = blogic2(sudoku, value, depth);
    if (boolean2 != 0){
   		boolean1 = 1;
  	}
  }  
}
// copys a set of data to the other set of data
void copythis(int (*copy)[9][9], int (*original)[9][9]){
  for (int i=0; i<9; i++){
	  for ( int i2 = 0; i2<9; i2++){
  		copy[0][i][i2] = original[0][i][i2];
	  }
  }
}
// only use this if logic 1 and 2 can not solve the sudoku
// it guesses random values and
// uses logic to test if those values are possible
// this is done through recursion
int recurbrute (int (*sudoku)[9][9], int (*value)[9][9], int depth){
  // create a new copy of sudoku and value along with the pointers to pass on when recuring
	int copy[9][9];
	int (*copypointer)[9][9] = &copy;

	int valuecopy[9][9];
	int (*vcpointer)[9][9] = &valuecopy;
	
	copythis(copypointer, sudoku);
	copythis(vcpointer, value);

  	// set up all the prime values and ultimate break
	int ultimatebreak = 0;
	int primes[9] = {2,3,5,7,11,13,17,19,23};
	int totalerror = 0;
	int recurvalue;

  	// find the an unknown location
 	for (int i = 0; i < 9; i++){
  		for (int i2 = 0; i2 < 9; i2++){
  			if (vcpointer[0][i][i2]==0){
        		// testing if each prime can work in that location
        		for (int pi = 0; pi < 9; pi++){
	        		if (sudoku[0][i][i2]%primes[pi] ==0){ 
            			// change the values of the copy to match the test value
		        		copypointer[0][i][i2] = primes[pi];
		        		vcpointer[0][i][i2] = depth;
            			// apply logic to the copy leaving the original intact
		        		totallogic(copypointer, vcpointer, depth);
            			//check for error and completetion
            			// if there is error, move on to next test value
           				// if error and no more test values, then return 0;
            			// if there is no error and incomplete, then start recurbrute again
            			// checks to see if recurbrute value is complete. if complete break, otherwise move on to next value
            			// if there is no error and complete break out of all the loops
		        		if (isright(copypointer, vcpointer)){
              				if (issudokucomplete(vcpointer)){
				    	    	    ultimatebreak = 1;
				    	    	    break;
              				}else{	
				    	    	depth ++;
                				//printf("next depth = %d", depth);
				    	    	recurvalue = recurbrute( copypointer, vcpointer, depth);
				    	    	if (recurvalue){
                  					ultimatebreak = 1;
				    	    	}
			        		}
		        		}else{
		       		 		// start fresh from because the previous testing value is incorrect
              				copythis(copypointer, sudoku);
              				copythis(vcpointer, value);
            			}
	        		}
        		}// testing primes end here
        		if (ultimatebreak = 0){
	    		    return 0;
        		}
			}
			if (ultimatebreak){
				break;
			}
		}	
		if (ultimatebreak){
		  	break;
		}
	} // finding unknown locations end here

  	// modify the old sudoku to the new sodoku
	copythis(sudoku, copypointer);
	copythis(value, vcpointer);
	
	return 1;
}
int main(void){
    printf("program starts\n");
	// this is just a random sudoku i inputed. to test the code
	// uncomment out the user input if you want to solve your own sudoku	
    int sudoku[9][9] ={
      {2,8,5,0,0,0,0,0,0}, //1
      {0,7,0,0,2,5,0,0,9}, //2
      {0,0,0,0,0,0,0,0,4}, //3
      {1,9,0,0,0,0,0,0,0}, //4
      {6,0,0,0,9,0,0,1,0}, //5
      {0,0,0,7,0,4,0,8,0}, //6
      {0,0,0,8,0,3,0,0,0}, //7
      {0,0,3,6,0,0,0,4,0}, //8
      {0,0,0,0,0,0,5,0,0}  //9  
    };
    int (*pointer)[9][9] = &sudoku;
	// just creates a place to store value
	// default value is that all the location is 1
	// convert will change the values from 1 to 0 if the location is unknown    
    int values[9][9] = {	
      {1,1,1,1,1,1,1,1,1}, //1
      {1,1,1,1,1,1,1,1,1}, //2
      {1,1,1,1,1,1,1,1,1}, //3
      {1,1,1,1,1,1,1,1,1}, //4
      {1,1,1,1,1,1,1,1,1}, //5
      {1,1,1,1,1,1,1,1,1}, //6
      {1,1,1,1,1,1,1,1,1}, //7
      {1,1,1,1,1,1,1,1,1}, //8
      {1,1,1,1,1,1,1,1,1}  //9
    };
    int (*valuepointer)[9][9] = &values;
	
	// uncomment the next line you want to input your own sudoku    
    //input(pointer); 
	
	// converts the sudoku values to prime so it is easier to deal with    
    convert(pointer, valuepointer);
	// use logic to solve sudoku
    totallogic(pointer, valuepointer, 1);
	// if the logic can not solve the sudoku
	// then guess and checking with recurbrute will begin    
    if (issudokucomplete(valuepointer)==0){
      recurbrute(pointer, valuepointer, 1);  
    }
	// unconvert the values from primes to normal numbers
	// so the user can understand    
    unconvert(pointer);
	// prints the finished sudoku for the user to see    
    printraw(pointer);
	// i don't have a system pause because i am not a pleb
	// i run my programs from cmd prompt      
    return 0;
}