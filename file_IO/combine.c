#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

//运行时，附带三个参数分别时 文本1 文本2  文本3
int main(int argc,char **argv) {
  int fd;
  char text1[4096];
  size_t size;
  struct stat statbuf;
  if(argc!=4){
  printf("参数输入错误！\n示例：");
  printf("%s 文本1 文本2  文本3(自定义名字)\n",argv[0]);
   return -1;
  }  
    //open 
     fd = open(argv[1],O_RDONLY);
   if(fd < 0) {
   printf("打开%s 失败\n,请重新运行",argv[1]);
   return -1;
   }
   
   //get
   if(stat(argv[1],&statbuf)<0) {
    printf("获取%s的size失败\n",argv[1]);
   }
   else {
     size=statbuf.st_size;
   }
   size = read(fd,text1,size);
   close(fd); 
   
   //open
   fd = open(argv[3],O_RDWR|O_CREAT);
   if(fd<0) {
    printf("新建%s 失败\n",argv[3]);
    return -1;
   }
   write(fd,text1,size);
   close(fd);
   //open
   fd=open(argv[2],O_RDONLY);
   if(fd<0) {
   printf("打开%s 失败\n,请重新运行",argv[2]);
   return -1;
   }
   //get   
   if(stat(argv[2],&statbuf)<0) {
    printf("获取%s的size失败\n",argv[2]);
   }
   else {
     size=statbuf.st_size;
   }  
   size = read(fd,text1,size);
   close(fd); 
   
   fd=open(argv[3],O_RDWR);
   if(fd<0) {
   printf("打开%s 失败\n,请重新运行",argv[3]);
   return -1;
   }
   lseek(fd,0,SEEK_END );
   write(fd,text1,size);
   close(fd);
    printf("combine over! \n");


 return 0;
}
