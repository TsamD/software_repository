#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void parse(const unsigned char *data, size_t len){
    char buf[64];
    if(len>=4 && !memcmp(data,"FUZZ",4)){
        size_t paylen = len - 4;
        if(paylen > sizeof(buf)-1) paylen = sizeof(buf)-1;   /* CORRECTIF : borne */
        memcpy(buf, data+4, paylen);
        buf[paylen]='\0';
        printf("enregistrement analyse (%zu octets)\n", paylen);
    }
}
int main(int argc,char**argv){
    unsigned char d[1024]; long n;
    if(argc>=2){FILE*f=fopen(argv[1],"rb");if(!f)return 1;n=(long)fread(d,1,sizeof d,f);fclose(f);}
    else n=(long)read(0,d,sizeof d);
    if(n<0)return 1; parse(d,(size_t)n); return 0;
}
