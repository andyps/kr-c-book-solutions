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
  int flag;
  int fd;
} FILE;
extern FILE _iob[OPEN_MAX];

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])
enum flags {
  _READ = 01,
  _WRITE = 02,
  _UNBUF = 04,
  _EOF = 010,
  _ERR = 020
};

FILE _iob[OPEN_MAX] = {
  {0, (char *)0, (char *)0, _READ, 0},
  {0, (char *)0, (char *)0, _WRITE, 1},
  {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);
int fflush(FILE *);
int fclose(FILE *);
int fseek(FILE *, long int, int);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
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
    if ((fp->flag & (_READ | _WRITE)) == 0)
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
   fp->flag = (*mode == 'r') ? _READ : _WRITE;
   return fp;
}

int _fillbuf(FILE *fp) {
  int bufsize;
  
  if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
    return EOF;
  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
  if (fp->base == NULL)
     if ((fp->base = (char *) malloc(bufsize)) == NULL)
       return EOF;
  
  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);
  if (--fp->cnt < 0) {
    if (fp->cnt == -1)
      fp->flag |= _EOF;
    else
      fp->flag |= _ERR;
    fp->cnt = 0;
    return EOF;
  }
  return (unsigned char) *fp->ptr++;
}

int _flushbuf(int c, FILE *fp) {
  int bufsize;
  int n1, n2;

  if ((fp->flag & (_WRITE | _ERR)) != _WRITE)
    return EOF;
  bufsize = (fp->flag & _UNBUF) ? 0 : BUFSIZ;
  if (fp->base == NULL && bufsize > 0) {
     if ((fp->base = (char *) malloc(bufsize)) == NULL) {
       return EOF;
     }
  } else {
    if (bufsize > 0) {
      n1 = fp->cnt <= 0 ? bufsize : bufsize - fp->cnt;
      n2 = write(fp->fd, fp->base, n1);
    } else {
      n1 = 1;
      n2 = write(fp->fd, (char *)&c, n1);
    }
    if (n2 != n1) {
      fp->cnt = 0;
      fp->flag |= _ERR;
      return EOF;
    }
  }
  if (bufsize == 0) {
    return c;
  }
  fp->cnt = bufsize - 1;
  fp->ptr = fp->base;
  *fp->ptr++ = c;
  return c;
}

int fflush(FILE *fp) {
  int n1, n2;

  if ((fp->flag & (_WRITE | _ERR)) != _WRITE)
    return EOF;
  if (fp->flag & _UNBUF || fp->base == NULL)
    return 0;
  n1 = fp->cnt <= 0 ? BUFSIZ : BUFSIZ - fp->cnt;
  n2 = write(fp->fd, fp->base, n1);
  if (n2 != n1) {
    fp->cnt = 0;
    fp->flag |= _ERR;
    return EOF;
  }
  fp->cnt = BUFSIZ;
  fp->ptr = fp->base;
  return 0;
}

int fclose(FILE *fp) {
  fflush(fp);
  return close(fp->fd);
}

int fseek(FILE *fp, long int offset, int origin) {
  long int pos;

  if (fp->flag & _ERR)
    return EOF;
  if (fp->flag & _READ) {
    fp->cnt = 0;
    fp->flag &= (~_EOF);
  } else if (fp->flag & _WRITE) {
    if (fflush(fp) != 0) {
      return EOF;
    }
  } else {
    return EOF;
  }

  pos = lseek(fp->fd, offset, origin);
  if (pos == EOF) {
    fp->cnt = 0;
    fp->flag |= _ERR;
    return EOF;
  }

  return 0;
}

int main() {
  FILE *fp;
  
  fp = fopen("1.txt", "w");
  putc('a', fp);
  putc('b', fp);
  fseek(fp, 1, 0);
  putc('c', fp);
  putc('d', fp);
  putc('e', fp);
  fclose(fp);

  fp = fopen("1.txt", "r");
  putchar(getc(fp));
  putchar(getc(fp));
  putchar(getc(fp));
  fseek(fp, 1, 0);
  putchar(getc(fp));
  fclose(fp);

  fflush(stdout);
  return 0;
}
