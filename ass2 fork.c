//ass2 fork
//2. Process Management (CO2)
//Process control system calls: The demonstration of FORK and WAIT system calls along with
//zombie and orphan states. Implement the C program in which main program accepts the integers
//to be sorted. Main program uses the FORK system call to create a new process called a child
//process. Parent process sorts the integers using sorting algorithm and waits for child process
//using WAIT system call to sort the integers using any sorting algorithm. Demonstrate zombie and


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<pthread.h>
#include<semaphore.h>

// bubble sort
void bubble(int arr[],int n){
  int i,j,temp;
  for(i=0;i<n-1;i++){
     for(j=0;j<n-i-1;j++){
        if(arr[j]>arr[j+1]){
           temp=arr[j];
           arr[j]=arr[j+1];
           arr[j+1]=temp;
        }
     }
  }
}

//display
void display(int arr[], int n){
   int i;
   for(i=0;i<n;i++){
      printf("%d \n",arr[i]);
   }
}

int main(){
   //input and process creation
   int i;
   int arr[100];
   int n;
   printf("Enter the number of integres:- \n");
   scanf("%d",&n);
   
   for(i=0;i<n;i++){
     printf("Enter the %d integer \n",i);
     scanf("%d",&arr[i]);
   }
   
   pid_t pid=fork();
   if(pid<0){
      perror("fork failed");
      return 1;
   }
   //child
   if(pid==0){
      printf("Child process \n");
      printf("child pid is:- %d \n",getpid());
      printf("parent pid is:- %d \n",getppid());
      
      printf("child executing is process indepndelty \n");
      bubble(arr,n);
      printf("sorted array is:- \n");
      display(arr,n);
      exit(0);
   }
   else{
      printf("Parent process \n");
      printf("parent pid is:- %d \n",getpid());
      printf("child pid is:- %d \n",pid);
      
      printf("parent execruing its own process \n");
      bubble(arr,n);
      printf("sorted array is:- \n");
      display(arr,n);
      wait(NULL);
      printf("Parent is waiting for child usig wait()\n");
   }
   //zombie 
   pid=fork();
   if(pid<0){
      perror("fork failed");
      return 1;
   }
   if(pid==0){
      printf("Chid termniated \n");
      exit(0);
   }
   else{
      printf("zombie demo and child left pid is:- %d \n",pid);
      sleep(2);
      wait(NULL);
      printf("child repeard using wait() \n");
   }
   
   //orphan
   pid=fork();
   if(pid<0){
      perror("fork failed");
      return 1;
   }
   if(pid==0){
      sleep(2);
      printf("oprhan demo \n");
      printf("child pid is:- %d \n",getpid());
      printf("new parent pid is:- %d \n",getppid());
      exit(0);
   }
   else{
      printf("parent process got terminated \n");
      exit(0);
   }
return 0;
}
//in terminal
gcc assignment2.c -o assignment2
./assignment2


//During the 15 seconds, open another terminal and run:

ps -el | grep Z
