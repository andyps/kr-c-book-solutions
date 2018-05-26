/* for Linux only */
#include <stddef.h>
#include <stdio.h>

#define NALLOC 1024
#define MAX_ALLOC 10240

typedef long Align;
union header {
  struct {
    union header *ptr;
    unsigned size;
  } s;
  Align x;
};
typedef union header Header;

static unsigned maxAllocatedUnits = 0;
static Header base;
static Header *freep = NULL;
void *_malloc(unsigned nbytes);
static Header *morecore(unsigned nu);
void _free(void *ap);

int main() {
  void *p;

  p = _malloc(MAX_ALLOC + 1);
  _free(p);

  p = _malloc(1);
  printf("maxAllocatedUnits = %d\n", maxAllocatedUnits);

  _free(p);
  return 0;
}

void _free(void *ap) {
  Header *bp, *p;

  if (maxAllocatedUnits == 0) {
    fprintf(stderr, "can't free: nothing was allocated before\n");
    return;
  }

  bp = (Header *)ap - 1;

  if (bp->s.size == 0) {
    fprintf(stderr, "can't free 0 units\n");
    return;
  }
  if (bp->s.size > maxAllocatedUnits) {
    fprintf(stderr, "can't free: the maximum number that was allocated is %d\n", maxAllocatedUnits);
    return;
  }
  
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
  maxAllocatedUnits = (nu > maxAllocatedUnits) ? nu : maxAllocatedUnits;
  _free((void *)(up + 1));
  return freep;
}

void *_malloc(unsigned nbytes) {
  Header *p, *prevp;
  Header *morecore(unsigned);
  unsigned nunits;

  if (nbytes > MAX_ALLOC) {
    fprintf(stderr, "can't allocate more than %d bytes\n", MAX_ALLOC);
    return NULL;
  }

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
