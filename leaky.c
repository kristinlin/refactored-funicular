#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
  
  int READ = 0;
  int WRITE = 1;
  int f;
  int num;

  //WRITE for parent; READ for child
  int wire1[2];
  //READ for parent; WRITE for child
  int wire2[2];
  
  //create the two pipes before; so child has it
  pipe(wire1);
  pipe(wire2);

  f = fork();

  //if parent...
  if (f) {
    //close appropriate ends of pipes
    close(wire1[READ]);
    close(wire2[WRITE]);

    //send num, <child process>, receive diff num
    num = 3;
    printf("[parent] sending: %d\n", num);
    write(wire1[WRITE], &num, sizeof(num));
    read(wire2[READ], &num, sizeof(num));
    printf("[parent] received: %d\n", num);
  }
  //if child...
  else {
    //close appropriate ends of pipes
    close(wire1[WRITE]);
    close(wire2[READ]);

    //<parent process>, receive num, do math, send diff num, <parent process>
    read(wire1[READ], &num, sizeof(num));
    printf("[child] doing maths on: %d\n", num);
    num = num * 100 - 8;
    printf("[child] sending: %d\n", num);
    write(wire2[WRITE], &num, sizeof(num));
  }
  
}
