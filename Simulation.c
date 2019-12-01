#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Job.h"
#include"IntegerQueue.h"
//#include"IntegerQueue.c"

// getjob()
// Reads two numbers from file in, and returns a new Job with those numbers
// as arrival and duration.
int getCharSize(IntegerQueue Q);

Job getJob(FILE* in){
   int a, d;
   fscanf(in, "%d %d\n", &a, &d);
   return newJob(a, d);
}


int* stringToArray(IntegerQueue Q, char* str) 
{
   int* arr = (int*)calloc(length(Q)+1, sizeof(int)); //change back to not + 1
  //  printf("%d", len);
 
    int j = 0; 
    for(int i = 0; i < getCharSize(Q); i++)
    {
      if(str[i] == ' ') {
          j++; 
      } else {
          arr[j] = arr[j] * 10 + (str[i] - 48); 
      }
      
    }
    
    
    return arr; 
    
    
    
}
    
    
    




//-----------------------------------------------------------------------------
// The following stub for function main() contains a possible algorithm for 
// this project.  Follow it if you like.  Note that there are no instructions 
// included below for writing to either of the output files.  You must 
// intersperse those commands as necessary.
//-----------------------------------------------------------------------------
// main()
int main(int argc, char* argv[]){
	FILE* in;
	FILE* report;
	FILE* trace; 
	
   // check command line arguments
   // 
   // open files for reading and writing
      in = fopen(argv[1], "r");
      char* inFile = (char*)calloc(strlen(argv[1]) + 5, sizeof(char));
      strcpy(inFile, argv[1]);
  //    printf("first in file creation\n");
      char* inFile2 = (char*)calloc(strlen(argv[1]) + 5, sizeof(char));
     // char* rpt = calloc(strlen(inFile) + 3, sizeof(char));
      strcpy(inFile2, inFile);
      strcat(inFile, ".rpt");
    //  printf("second in file creation\n");
     // printf("in2: %s\n", inFile2);
     // strcpy(rpt, inFile);
      report = fopen(inFile, "w"); //opens .rpt out file

      
      
   //   char* trc = calloc(strlen(inFile) + 3, sizeof(char));
      strcat(inFile2, ".trc");
   //   strcpy(trc, inFile2);
      trace = fopen(inFile2, "w"); //opens .trc out file 

   // read in m jobs from input file and place them in backup array
    
      int m; 
      fscanf(in, "%d", &m);
    //  printf("m: %d\n", m); 
   // declare and initialize an array of m-1 processor Queues along with
      IntegerQueue* Q = calloc(m, sizeof(IntegerQueue));
    //  printf("IntegerQueue array creation\n");
      for(int i = 0; i < m; i++) {
          Q[i] = newIntegerQueue();
      }
      
   // any necessary storage queues
      Job* backupArray = calloc(m, sizeof(Job)); //stores all jobs in their original order, which is needed to start each smiluation.
  //   printf("BackupArray creatio\n");
      for(int i = 0; i < m; i++) {
          backupArray[i] = getJob(in);
      }
   
   //   Job* storageQueue = calloc(m-1, sizeof(Job));
   
     
     // printJob(report, backupArray[peek(Q[0])]);
     
     //SET UP TRACE FILE ----------------------------------------------
     for(int i = 0; i < m; i++) 
          {
            enqueue(Q[0], i); // Q[0] == StorageQueue
          }
          
    
    fprintf(trace, "Trace file: %s\n", inFile2);
    fprintf(trace, "%d Jobs:\n", m);
    for(int i = 0; i < m; i++) 
    {
       printJob(trace, backupArray[i]); 
    }
    fprintf(trace, "\n");
    fprintf(trace, "\n");
    
      for(int i = 0; i < m; i++) 
          {
            dequeue(Q[0]); // Q[0] == StorageQueue
          }
  //END OF SET UP TRACE FILE ------------------------------------------------------------
 // printf("end of set up trace file\n");
  
  //SET UP REPORT FILE-------------------------------------------------------------------
   fprintf(report, "Report file: %s\n", inFile);
   fprintf(report, "%d Jobs:\n", m);
   for(int i = 0; i < m; i++)
   {
       printJob(report, backupArray[i]);
   }
   fprintf(report, "\n");
   fprintf(report, "\n");
   fprintf(report, "***********************************************************\n");
  
  //END OF SET UP REPORT FILE-------------------------------------------------------------------
//  printf("end of set up report file\n");
   // loop: run simulation with n processors for n=1 to n=m-1 {
   
   
   //BEGIN SIMULATION ------------------------------------------------------------
     for(int n = 1; n < m; n++) {
        
   //    place Job indices from backup array into storage queue
     fprintf(trace, "*****************************\n");
     
     if(n > 1)
     {
        fprintf(trace, "%d processors: \n", n); 
     } else {
     fprintf(trace, "%d processor: \n", n);
     }
     fprintf(trace, "*****************************\n");
     
     int t = 0;
     int flag = 0;
     int sum = 0;
     int maxTime = 0;
     double averageWait = 0;
     
          for(int i = 0; i < m; i++) 
          {
            enqueue(Q[0], i); // Q[0] == StorageQueue
          }
  //    }
           printf("initial printout about to start\n");
            //INITIAL PRINTOUT AT T=0---------------------------------------------------
            fprintf(trace, "time=%d\n", t);
             for(int j = 0; j <= n; j++){
                    
             fprintf(trace,"%d:", j);
                  //  printf("here");
             char* str2 = IntegerQueueToString(Q[j]);
         //    printf("%s\n", str2);
             int* arr = stringToArray(Q[j], str2);
          //   printf("stringToArrayTest: %d\n", arr[0]);
             free(str2);
            printf("initial printout 1\n");
                    
             for(int i = 0; i < length(Q[j]); i++) {
                        
                      
              printJob(trace, backupArray[arr[i]]); 
                      
                      
             }
             
             
                 fprintf(trace, "\n");
                 free(arr);
                 continue;
                }
             fprintf(trace, "\n");
            //END INITIAL PRINTOUT--------------------------------------------------------
            printf("initial printout complete\n");
            
            
  
  
   //    loop: process all Jobs in this simulation {
        while(1) {
   //       determine the time of the next arrival or finish event and update time
          
          
            //check for finish time --------------------------------
            for(int i = 1; i <= n; i++) {
                
                if(t == getFinish(backupArray[peek(Q[i])]) && length(Q[i]) > 0)
                {
                   
                    enqueue(Q[0], peek(Q[i]));
               //     printf("t: %d == getFinish(%d): %d\n", t, i, getFinish(backupArray[peek(Q[i])]));
               //     printf("finish dequeue @ %d\n", i);
                    dequeue(Q[i]);
                    flag = 1; 
                    
                     if (t == getArrival(backupArray[peek(Q[0])])) //if time is also equal to the current arrival time
                    {
                        flag = 2; 
                    }
                }
            }
            if(flag == 1) { //checks for 2 jobs finishing at same time
                //print report-------------------------------------
                fprintf(trace, "time=%d\n", t);
                for(int j = 0; j <= n; j++){
             //      printf("check for finish time 1\n"); 
                    fprintf(trace,"%d:", j);
                  //  printf("here");
                    char* str9 = IntegerQueueToString(Q[j]);
                  //  printf("%s\n", str9);
                    int* arr9 = stringToArray(Q[j], str9);
                  //  printf("stringToArrayTest: %d\n", arr9[0]);
                    free(str9);
                //   printf("check for finish time 2\n");
                     if(j > 0 && t > 0 && getFinish(backupArray[peek(Q[j])]) == UNDEF) 
                    {
                        computeFinishTime(backupArray[peek(Q[j])], t);
                    }
                    
              //  printf("check for finish time 3\n");
                    
                    for(int i = 0; i < length(Q[j]); i++) {
                        
                      
                      printJob(trace, backupArray[arr9[i]]); 
                      
                      
                    }
                 fprintf(trace, "\n");
                 free(arr9);
                }
                    fprintf(trace, "\n"); 
                    flag = 0;
            }
            
            
       //     printf("check for finish time complete\n");
            
            
           for(int i = 0; i < m; i++) { 
            // check for arrival time in storage queue--------------------------------------------
            if(t == getArrival(backupArray[peek(Q[0])]))
            {
                //place in shortest index (still doesnt work)
                //put the arrived job in the lowest Queue length
                 
                 int index;
                 //find lowest length
                  int min = 5000;
                  for(int i = 1; i <= n; i++)
                 {
                    if(length(Q[i]) < min)
                    {
                        min = length(Q[i]); //TODO: in IntegerQueue, it will add 1 to length when it is 9 < x <= 99 so length might be off
                    }
                }
        //            printf("check for arrival time 1\n");
                 for(int i = 1; i <= n; i++) 
                 {
                    if(length(Q[i]) == min) 
                    {  
                            index = i;
                            break;
                    }
                 }
                 
                 enqueue(Q[index], peek(Q[0])); 
                // printf("arrival dequeue");
                 dequeue(Q[0]);
                 flag = 1;
                 
           //      printf("check for arrival time 2\n");
            }
           }
            
            if(flag == 1 || flag == 2) { 
                //PRINT UPDATE ---------------------------------------------------
                fprintf(trace, "time=%d\n", t);
                for(int j = 0; j <= n; j++){
                    
                    fprintf(trace,"%d:", j);
                  // printf("print update\n");
                    char* str01 = IntegerQueueToString(Q[j]);
                 //   printf("%s\n", str01);
                    int* arr01 = stringToArray(Q[j], str01);
                //    printf("stringToArrayTest: %d\n", arr01[0]);
                    free(str01);
                    
                    if(j > 0 && t > 0 && getFinish(backupArray[peek(Q[j])]) == UNDEF) 
                    {
                        computeFinishTime(backupArray[peek(Q[j])], t);
                    }
                    
              //      printf("print update 2\n" );
                    
                    for(int i = 0; i < length(Q[j]); i++) {
                        
                      
                      printJob(trace, backupArray[arr01[i]]); 
                      
                      
                    }
                 fprintf(trace, "\n");
                 free(arr01);
                }
                 fprintf(trace, "\n");
                 flag = 0;
            }
            
        //    printf("print update complete \n");
            //END OF CHECK ARRIVAL TIME --------------------------------------
           /*
            if(t > 14)
            {
                break;
            } else {
                t++;
            }
            */
            
            
               //END CONDITION ------------------------------------------------------ 
               //causes infinite loop when m is not 3
               //if all the jobs in the storage queue have a finish time, that means that we are done.
               if(length(Q[0]) == m) 
               {
                   int sum = 0;
                   printf("before iqts\n");
                   char* str4 = IntegerQueueToString(Q[0]);
                   // printf("%s\n", str2);
                   printf("before sTa\n");
                   int* arr4 = stringToArray(Q[0], str4);
                    printf("end condition 1 \n");
                  // printf("stringToArrayTest: %d\n", arr4[0]);
                   free(str4);
                   for(int i = 0; i < m; i++)
                   { 
                       if(getFinish(backupArray[arr4[i]]) != UNDEF)
                       {
                           sum++;
                           
                       }
                   }
                   free(arr4);
                   printf("end condition 2 \n");
                   if(sum == length(Q[0]))
                   {
                       break;
                   } else {
                       t++; 
                   }
               } else {
                   t++;
               }
               
               printf("end condition finish \n");
               
      
           
               
            
   //       if(getArrival(peek(Q[0]) 
   //       if any Jobs finish now, then complete them in the order they appear in 
   //       the queue array, i.e. lowest index first.
   //
   //       if any Jobs arrive now, then assign them to a processor queue 
   //       of minimum length and with lowest index in the queue array.
   //
  } //end of while loop 
  
   //
   //    compute the total wait, maximum wait, and average wait for 
         
         //compute the total wait
          char* str6 = IntegerQueueToString(Q[0]);
        // printf("%s\n", str2);
          int* arr6 = stringToArray(Q[0], str6);
          
          printf("end of while loop 1\n");
          
         for(int i = 0; i < m; i++) {
             sum += getWaitTime(backupArray[arr6[i]]);
             if(getWaitTime(backupArray[arr6[i]]) > maxTime) 
             {
                 maxTime = getWaitTime(backupArray[arr6[i]]);
             }
         }
          printf("end of while loop 2\n");
         
         free(str6);
         free(arr6); 
         if(n > 1) {
         fprintf(report, "%d processors: ", n);
         } else {
         fprintf(report, "%d processor: ", n);
         }
         
         averageWait = (double) sum / m;
         fprintf(report, "totalWait=%d, ", sum);
         fprintf(report, "maxWait=%d, ", maxTime);
         fprintf(report, "averageWait=%.2f\n", averageWait);
         
          printf("end of while loop 3\n");
         
   //    all Jobs, then reset finish times for next simulation
        //reseting finish time
        char* str5 = IntegerQueueToString(Q[0]);
        // printf("%s\n", str2);
        int* arr5 = stringToArray(Q[0], str5);
         printf("end of while loop 4\n");
        for(int i = 0; i < m; i++) {
            resetFinishTime(backupArray[arr5[i]]);
            dequeue(Q[0]);
        }
         printf("end of while loop 5\n");
        free(str5);
        free(arr5);
        
         printf("end of while loop 6\n");
        
   //
   }  // end each simulation 
   //
   // free all heap memory, close input and output files
   for(int i = 0; i < m; i++) 
   {
        printf("free int queue \n");
       freeIntegerQueue(&Q[i]);
        printf("free job queue \n");
       freeJob(&backupArray[i]);
   }
   
    printf("end of smulation 1\n");
   free(inFile); //causes mem failure idk why
   free(inFile2);
  // free(rpt);
 //  free(trc);
   free(Q);
   free(backupArray);
   fclose(trace);
   fclose(report);
   fclose(in);
  

   return EXIT_SUCCESS;
}