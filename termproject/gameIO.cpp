#include<iostream>
#include<string>
#include<unistd.h>
#include<termios.h>
#include<stropts.h>
#include<sys/select.h>
#include"gameIO.h"
#include"color.h"

#define DEBUG_MODE false
void debugMessage(std::string msg){
    if(DEBUG_MODE)
        std::cout<<BOLD(FCYN("[DEBUG] "))<<msg<<std::endl;
}

char getch(){
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror ("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");
    return (buf);
}
