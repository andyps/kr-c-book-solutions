/* for Linux only */
#include <stddef.h>
#include <stdio.h>

/* #define NALLOC 1024 */
#define NALLOC 1 /* 1 is for testing */

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
unsigned bfree(void *p, unsigned n);

#define HEADER_SIZE (sizeof(Header))
static char a1[HEADER_SIZE * 3];

int main() {
  void *p;
  int i;

  for (i = 0; i < HEADER_SIZE * 3; i++) {
    a1[i] = i;
  }

  p = a1;

  bfree(p, HEADER_SIZE * 3);
  /* it was attached to the list */
  printf("%p == %p\n", (void *)p, (void *)((&base)->s.ptr));

  p = _malloc(HEADER_SIZE);
  printf("%p == %p\n", &a1[HEADER_SIZE * 2], p);

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

unsigned bfree(void *p, unsigned n) {
  Header *up;
  unsigned nunits;

  if (n == 0) {
    fprintf(stderr, "can't free 0 bytes");
    return 0;
  }
  nunits = n / sizeof(Header);
  /* having only Header is not enough */
  if (n <= sizeof(Header)) {
    fprintf(stderr, "can't free: the size must be more than %d\n", (int)sizeof(Header));
    return 0;
  }

  if (freep== NULL) {
    base.s.ptr = freep = &base; 
    base.s.size = 0;
  }

  up = (Header *)p;
  up->s.size = nunits;
  _free((void *)(up + 1));
  return nunits;
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
