#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    system("touch dane.txt;");
    system("mkdir inne;");
    system("rm dane.txt;");
    system("rmdir inne;");
    system("cp dane.txt inne/dane.txt;");
    system("move dane.txt inne/dane.txt;");

}