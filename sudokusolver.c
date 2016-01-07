#include <stdio.h>

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
// must add a function that will only print known values later
void print(int (*sudoku)[9][9]){
  printf("graph starts here\n");
  for (int i = 0; i <9 ; i ++){
    for (int i2 = 0; i2 <9 ; i2++){
        // by changing this boolean expression to (value[0][i][i2] == 1) and adding value as a parameter
        if (isvaluefound(sudoku[0][i][i2])){ 
          printf("%3d\t", sudoku[0][i][i2]);
        }else{
          printf("NA\t");
        }  
    }
    printf("\n");
  }
  printf("\n");
}
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
void printrawraw(int (*raw)[9][9]){
  printf("raw graph start\n");
  for (int i = 0; i < 9; i++){
    for (int i2 =0; i2 < 9; i2++){
      printf("%2d\t", raw[0][i][i2]);
    }
    printf("\n");
  }
  printf("\n\n");
}
int issudokucomplete(int (*value)[9][9]){
    for (int i = 0; i<9; i++){
      for (int i2 = 0; i2<9; i2++){
        if (!value[0][i][i2]){
          return 0;
        }
      }
    }
    printf("sudoku is completed\n");
    return 1;
}
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
// must check for the values in each square as well
int iswrong(int (*sudoku)[9][9], int (*value)[9][9]){
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
              printf("error at %d,%d and %d,%d\n", i,i2,i,i3);
              return 0;
            }
          }
          // for each value in that column
          if (value[0][i3][i2] && i3 != i){
            // that is know and not in the same location
            if (sudoku[0][i3][i2] == sudoku[0][i][i2]){
              // if they are the same then we have a problem.
              printf("error at %d,%d and %d,%d\n", i3,i2,i,i2);
              return 0;
            }
          }
        }
      }
    }
  }
  return 1;
}
// divide unknown values by the known values in the same row, column and square
// must also add return a int that main if logic1 is no longer useful
int logic1(int (*sudoku)[9][9], int (*value)[9][9]){
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
                value[0][i][i2] = 1;
  //printf("a sudoku [%d][%d] = %d\n", i, i2, sudoku[0][i][i2]);
                count++;
              }  
            }
          }
        }
        // then will go through each value in that column
        for (int i3 = 0 ; i3 < 9; i3++){
          if (value[0][i3][i2] == 1){
            if (sudoku[0][i][i2]%sudoku[0][i3][i2]==0 && sudoku[0][i][i2] != sudoku[0][i3][i2]){
              sudoku[0][i][i2] = sudoku[0][i][i2]/sudoku[0][i3][i2];
              if (isvaluefound(sudoku[0][i][i2])){
                value[0][i][i2] = 1;
  //printf("b sudoku [%d][%d] = %d\n", i, i2, sudoku[0][i][i2]);
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
                  value[0][i][i2] = 1;
  //printf("c sudoku [%d][%d] = %d\n", i, i2, sudoku[0][i][i2]);
                  count++;
                }
              }
            }
          }
        }
      }
    }
  }
  printf("logic 1 has found %d new numbers\n", count);
  return count;
}
// if there is only 1 location where a value can be,
// then change that location to the value only it can be.
// currently only availible for row and column
// must add square
int logic2(int (*sudoku)[9][9], int (*value)[9][9]){
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
            if (value[0][i][i3]){
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
            value[0][i][storei3] =1;
            returnvalue++;
            //printf(" sudoku[%d][%d] = %d\n", i, storei3, sudoku[0][i][storei3]);
        }   
        ///////////////////////////////////////////////// part 2
        count = 0;
        for (int i3 = 0; i3<9;i3++){
          if (sudoku[0][i3][i]%primes[i2]==0){
            if(value[0][i3][i]){
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
          value[0][storei3][i] = 1;
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
          value[0][i*3+storesi][i2*3+storesi2] =1;
          returnvalue++;
        }
      } 
    }
  }
  printf("logic 2 has found %d values\n", returnvalue);
  return returnvalue;  
}
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
  //printf("a sudoku [%d][%d] = %d\n", i, i2, sudoku[0][i][i2]);
                count++;
              }  
            }
          }
        }
        // then will go through each value in that column
        for (int i3 = 0 ; i3 < 9; i3++){
          if (value[0][i3][i2] == 1){
            if (sudoku[0][i][i2]%sudoku[0][i3][i2]==0 && sudoku[0][i][i2] != sudoku[0][i3][i2]){
              sudoku[0][i][i2] = sudoku[0][i][i2]/sudoku[0][i3][i2];
              if (isvaluefound(sudoku[0][i][i2])){
                value[0][i][i2] = depth;
  //printf("b sudoku [%d][%d] = %d\n", i, i2, sudoku[0][i][i2]);
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
  //printf("c sudoku [%d][%d] = %d\n", i, i2, sudoku[0][i][i2]);
                  count++;
                }
              }
            }
          }
        }
      }
    }
  }
  return count;
}
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
            if (value[0][i][i3]){
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
            if(value[0][i3][i]){
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
              if (value[0][i*3+si][i2*3+si2]==0){
                // if the value is a known value
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
  return returnvalue;
}
/*
void brute(int (*sudoku)[9][9], int (*value)[9][9]){
  int prime[9] = {2,3,5,7,11,13,17,19,23};
  int done = 0;
  for (int i = 0; i<9;i++){
    for (int i2 = 0; i2 < 9; i2++){
      // for each value in the square
      if (value[0][i][i2]==0){
        // if the value is unknown
        // finds it first divisor
        for (int pi = 0; pi<9; pi++){
          ///////////////////////////////////////
          // set up new array here
          ///////////////////////////////////////
          if (sudoku[0][i][i2]%prime[pi]==0){
            // if it is divisible
            sudoku[0][i][i2] = prime[pi];
            int boolean1 =1, boolean2=1;
            while(boolean1!=0||boolean2||0){
              while(boolean1!=0){
                boolean1 = blogic1(sudoku, value);
                //printf("boolean1 = %d", boolean1);
              }
              boolean2 = logic2(pointer, valuepointer);
              if (boolean2 != 0){
                boolean1 = 1;
              }
              //printf("boolean2 = %d", boolean2);
            }
            if (issudokucomplete(value)){
              if (isworng(value)){
                done = 1;
              }else{
                break;
              }
            }
          }  
        }
      }
    }
  }
}
*/
int main(void){

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

    //input(pointer);
    
    printraw(pointer);
    printraw(valuepointer);

    convert(pointer, valuepointer);
    print(pointer);
    printraw(valuepointer);

    int boolean1 =1, boolean2=1;
    while(boolean1!=0||boolean2||0){
      while(boolean1!=0){
        boolean1 = logic1(pointer, valuepointer);
        //printf("boolean1 = %d", boolean1);
      }
      boolean2 = logic2(pointer, valuepointer);
      if (boolean2 != 0){
        boolean1 = 1;
      }
      //printf("boolean2 = %d", boolean2);
    }
    printrawraw(pointer);

    unconvert(pointer);
    printraw(pointer);
    printraw(valuepointer);
    
    
    return 0;
}