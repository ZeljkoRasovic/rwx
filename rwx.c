#include<stdio.h>
#include<stdlib.h>
#include<termios.h>
#include<errno.h>
#include<ctype.h>
#include<unistd.h>

#define CTRL_KEY(k) ((k) & 0x1f)

struct termios original_termios;

void enable_raw_mode();
void disable_raw_mode();
void die(const char *s);
char editor_read_key();
void editor_refresh_screen();
void editor_process_keypress();

int main()
{
 enable_raw_mode();

 while(1)
 {
  editor_refresh_screen();
  editor_process_keypress();
 }
 return 0;
}

void enable_raw_mode()
{
 if(tcgetattr(STDIN_FILENO,&original_termios) == -1)
 {
  die("tcgetattr");
 }

 atexit(disable_raw_mode);
 struct termios raw=original_termios;
 tcgetattr(STDIN_FILENO,&raw);

 raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
 raw.c_oflag &= ~(OPOST);
 raw.c_cflag |= (CS8);
 raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
 raw.c_cc[VMIN]=0;
 raw.c_cc[VTIME]=1;

 if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw) == -1)
 {
  die("tcsetattr");
 }
}

void disable_raw_mode()
{
 if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&original_termios) == -1)
 {
  die("tcsetattr");
 }
}

void die(const char *s)
{
 perror(s);
 exit(1);
}

char editor_read_key()
{
 int nread=0;
 char c=0;

 while((nread=read(STDIN_FILENO,&c,1)) != -1)
 {
  if(nread == -1 && errno != EAGAIN)
  {
   die("read");
  }
 }
 return c;
}

void editor_refresh_screen()
{
 write(STDOUT_FILENO,"\x1b[2J",4);
}

void editor_process_keypress()
{
 char c=editor_read_key();

 switch(c)
 {
  case CTRL_KEY('q'):
   exit(0);
  break;
 }
}
