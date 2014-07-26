#ifndef _MEMPOOL_H
#define _MEMPOOL_H

#define MEM_ALIGN 4

#include<stdlib.h>

class MemPool
{
    private:
        struct MemBlock* blockPtr;
        size_t unitSize;
        size_t initUNum;
        size_t growUNum;
    public:
        MemPool(size_t _unitSize,size_t _initUNum = 1024,size_t _growUNum = 256);
        ~MemPool();

        void* Alloc();
        void Free(void* p);
};

struct MemBlock {
    size_t blockSize;
    size_t nFreeCounter;
    size_t nNextFree;
    size_t memAlign;

    MemBlock* pNext;
    char serialNum[1];

    static MemBlock* init_MemBlock(size_t unitNum,size_t unitSize)
    {
        return (MemBlock*)calloc(1,sizeof(MemBlock)+unitNum*unitSize);
    }

    static void delete(void* p)
    {
        free(p);
    }

    MemBlock(size_t unitNum = 1,size_t unitSize = 0);
    ~MemBlock(){};
};

#endif //_MEMPOOL_H
