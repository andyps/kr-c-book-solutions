/* for Linux only */
#include <stddef.h>
#include <stdio.h>

#define NALLOC 1024

typedef long Align;
union header {
  struct {
    union header *ptr;
    unsigned size;
  } s;
  Align x;
};
typedef union header Header;

static Header base;
static Header *freep = NULL;
void *_malloc(unsigned nbytes);
static Header *morecore(unsigned nu);
void _free(void *ap);
void *_calloc(unsigned n, unsigned size);

int main() {
  char *p1;

  p1 = _calloc(10, 1);
  printf("%d\n", *p1);
  *p1 = 'a';
  *(p1 + 1) = 'b';
  printf("%s\n", p1);

  _free(p1);
  return 0;
}

void _free(void *ap) {
  Header *bp, *p;

  bp = (Header *)ap - 1;
  for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) 
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) 
      break;

  if (bp + bp->s.size == p->s.ptr) {
    bp->s.size += p->s.ptr->s.size; 
    bp->s.ptr = p->s.ptr->s.ptr; 
  } else 
    bp->s.ptr = p->s.ptr;

  if (p + p->s.size == bp) { 
    p->s.size += bp->s.size; 
    p->s.ptr = bp->s.ptr; 
  } else
    p->s.ptr = bp;

  freep = p;
}

static Header *morecore(unsigned nu) {
  char *cp, *sbrk(int); 
  Header *up;
  
  if (nu < NALLOC) 
    nu = NALLOC;

  cp = sbrk(nu * sizeof(Header));
  if (cp == (char *) - 1)
    return NULL;

  up = (Header *)cp; 
  up->s.size = nu; 
  _free((void *)(up + 1));
  return freep;
}

void *_malloc(unsigned nbytes) {
  Header *p, *prevp;
  Header *morecore(unsigned);
  unsigned nunits;

  nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1; 
  if ((prevp = freep) == NULL) {
    base.s.ptr = freep = prevp = &base; 
    base.s.size = 0; 
  }

  for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
    if (p->s.size >= nunits) {
      if (p->s.size == nunits)
        prevp->s.ptr = p->s.ptr; 
      else {
        p->s.size -= nunits; 
        p += p->s.size; 
        p->s.size = nunits; 
      } 
      freep = prevp; 
      return (void *)(p + 1); 
    }
    if (p == freep) {
      if ((p = morecore(nunits)) == NULL) 
        return NULL;
    }
  }
}

void *_calloc(unsigned n, unsigned size) {
  unsigned nbytes;
  void *p;
  char *tmp;

  nbytes = n * size;
  p = _malloc(nbytes);
  tmp = (char *)p;
  while (nbytes-- > 0) {
    *tmp++ = '\0';
  }

  return p;
}
