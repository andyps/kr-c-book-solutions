#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

// #define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20
typedef struct _iobuf {
  int cnt;
  char *ptr;
  char *base;
  int fd;
  unsigned int read : 1;
  unsigned int write : 1;
  unsigned int unbuf : 1;
  unsigned int eof : 1;
  unsigned int err : 1;
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

FILE _iob[OPEN_MAX] = {
  {0, (char *)0, (char *)0, 0, 1, 0, 0, 0, 0},
  {0, (char *)0, (char *)0, 1, 0, 1, 0, 0, 0},
  {0, (char *)0, (char *)0, 2, 0, 1, 1, 0, 0}
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);
int fflush(FILE *);
int fclose(FILE *);

#define feof(p) ((p)->eof != 0)
#define ferror(p) ((p)->err != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

#define PERMS 0666

FILE *fopen(char *name, char *mode) {
  int fd;
  FILE *fp;
  
  if (*mode != 'r' && *mode != 'w' && *mode != 'a')
    return NULL;
  
  for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
    if (!fp->read && !fp->write)
      break;
   if (fp >= _iob + OPEN_MAX)
     return NULL;
   
   if (*mode == 'w')
     fd = creat(name, PERMS);
   else if (*mode == 'a') {
     if ((fd = open(name, O_WRONLY, 0)) == -1)
       fd = creat(name, PERMS);
     lseek(fd, 0L, 2);
   } else
     fd = open(name, O_RDONLY, 0);
   if (fd == -1)
     return NULL;
   
   fp->fd = fd;
   fp->cnt = 0;
   fp->base = NULL;

   fp->read = 0;
   fp->write = 0;
   fp->eof = 0;
   fp->err = 0;
   fp->unbuf = 0;
   if (*mode == 'r') {
     fp->read = 1;
   } else {
     fp->write = 1;
   }
   return fp;
}

int _fillbuf(FILE *fp) {
  int bufsize;
  
  if (fp->eof || fp->err || !fp->read)
    return EOF;
  bufsize = fp->unbuf ? 1 : BUFSIZ;
  if (fp->base == NULL)
     if ((fp->base = (char *) malloc(bufsize)) == NULL)
       return EOF;
  
  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);
  if (--fp->cnt < 0) {
    if (fp->cnt == -1)
      fp->eof = 1;
    else
      fp->err = 1;
    fp->cnt = 0;
    return EOF;
  }
  return (unsigned char) *fp->ptr++;
}

int main() {
  FILE *fp;
  char str[3];
  
  fp = fopen("1.txt", "w");
  str[0] = getc(fp);
  if (str[0] == EOF) {
    write(1, "cannot read from the file that was not opened for reading\n", 58);
  }
  write(fp->fd, "a", 1);
  write(fp->fd, "b", 1);
  write(fp->fd, "c", 1);
  close(fp->fd);

  fp = fopen("1.txt", "r");
  str[0] = getc(fp);
  str[1] = getc(fp);
  str[2] = getc(fp);
  write(1, str, 3);
  close(fp->fd);

  return 0;
}
