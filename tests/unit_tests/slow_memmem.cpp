// Copyright (c) 2018, Bitlitas
// All rights reserved. Based on Cryptonote and Monero.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "gtest/gtest.h"

// OS X, FreeBSD, and OpenBSD don't need malloc.h
#if !defined(__APPLE__) && !defined(__FreeBSD__) && !defined(__OpenBSD__) && \
    !defined(__DragonFly__)
 #include <malloc.h>
#endif

//#define TEST_ORIGINAL
//#define VERBOSE

#ifdef TEST_ORIGINAL
uint64_t slow_memmem_original(void* start_buff, size_t buflen,void* pat,size_t patlen)
{
  void* buf = start_buff;
  void* end=(char*)buf+buflen-patlen;
  while((buf=memchr(buf,((char*)pat)[0],buflen)))
  {
    if(buf>end)
      return 0;
    if(memcmp(buf,pat,patlen)==0)
      return (char*)buf - (char*)start_buff;
    buf=(char*)buf+1;
  }
  return 0;
}

#define slow_memmem slow_memmem_original
#else
namespace cryptonote {
  uint64_t slow_memmem(const void* start_buff, size_t buflen,const void* pat,size_t patlen);
}
using namespace cryptonote;
#endif

static const struct {
  size_t buflen;
  const char *buf;
  size_t patlen;
  const char *pat;
  uint64_t res;
} T[]={
  {0,"",0,"",0},
  {1,"",0,"",0},
  {0,"",1,"",0},
  {1,"x",1,"x",0},
  {2,"x",1,"",1},
  {1,"x",1,"",0},
  {1,"x",2,"x",0},
  {2,"ax",2,"x",0},
  {1,"xx",2,"xx",0},
  {4,"abcd",3,"abc",0},
  {4,"abcd",3,"bcd",1},
  {4,"abcd",4,"abcd",0},
  {4,"abcd",1,"d",3},
  {4,"abcd",1,"c",2},
  {4,"abcd",1,"bc",1},
  {4,"abcd",1,"",0},
  {3,"abcd",1,"d",0},
  {5,"aaaab",2,"ab",3},
  {7,"aaaabab",2,"ab",3},
  {7,"aaaabab",3,"abc",0},
  {4,"abcd",2,"cd",2},
  {3,"abcd",2,"cd",0},
  {3,"a\0b",1,"",1},
  {3,"a\0b",2,"\0b",1},
  {8,"xxxxxxab",3,"xyz",0},
  {8,"xxxxxxab",6,"abcdef",0},
  {9,"\0xxxxxab",3,"ab",6},
  {4,"\0\0a",3,"\0a",1}, //
};

TEST(slowmem,Success)
{
  size_t n;
  for (n=0;n<sizeof(T)/sizeof(T[0]);++n) {
#ifdef VERBOSE
    printf("%3zu: ",n);
    fflush(stdout);
#endif
    void *buf=malloc(T[n].buflen);
    memcpy(buf,T[n].buf,T[n].buflen);
    void *pat=malloc(T[n].patlen);
    memcpy(pat,T[n].pat,T[n].patlen);
    uint64_t res=slow_memmem(buf,T[n].buflen,pat,T[n].patlen);
    free(pat);
    free(buf);
    ASSERT_EQ(res,T[n].res);
#ifdef VERBOSE
    if (res!=T[n].res) printf("failed (got %zu, expected %zu)",res,T[n].res); else printf("ok");
    printf("\n");
#endif
  }
}
