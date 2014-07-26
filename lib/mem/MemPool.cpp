/*
 *==========================================================================
 *       Filename:  MemPool.cpp
 *    Description:
 *        Version:  1.0
 *        Created:  2014/07/26
 *       Revision:  none
 *       Compiler:  g++
 *       Author:  joe, sysu_joe@163.com
 *   Organization:  sysu
 *==========================================================================
 */

#include"MemPool.h"

#include <stdio.h>
using namespace std;

MemPool::MemPool(size_t _unitSize,size_t _initUNum,size_t _growUNum)
{
    blockPtr = NULL;
    initUNum = _initUNum;
    growUNum = _growUNum;

    if(_unitSize>4)
        unitSize = _unitSize + (MEM_ALIGN - _unitSize % MEM_ALIGN);
    else if(_unitSize<=2)
        unitSize = 2;
    else
        unitSize = 4;

}

void* MemPool::Alloc()
{
    if(!blockPtr)
    {
        blockPtr = blockPtr->init_MemBlock(initUNum,unitSize);
        blockPtr->blockSize = unitSize;
        blockPtr->nFreeCounter = initUNum - 1;
        blockPtr->nNextFree = 1;
        blockPtr->memAlign = MEM_ALIGN;
        blockPtr->pNext = NULL;

        char* sNum = blockPtr->serialNum;
        for(size_t i=1;i<initUNum;i++)
        {
            *reinterpret_cast<size_t*>(sNum) = i;
            sNum += unitSize;
        }
    }


    MemBlock* pBlock = blockPtr;
    while(pBlock && !pBlock->nFreeCounter)
        pBlock = pBlock->pNext;


    if(pBlock)
    {
        char* pFree = pBlock->serialNum + (pBlock->nNextFree*unitSize);
        pBlock->nNextFree = *((size_t*)pFree);

        pBlock->nFreeCounter--;
        return (void*)pFree;
    }
    else
    {
        if(!growUNum)
            return NULL;

        pBlock = pBlock->init_MemBlock(growUNum,unitSize);
        pBlock->blockSize = unitSize;
        pBlock->nFreeCounter = growUNum - 1;
        pBlock->nNextFree = 1;
        pBlock->memAlign = MEM_ALIGN;

        if(!pBlock)
            return NULL;

        pBlock->pNext = blockPtr;
        blockPtr = pBlock;

        return (void*)(pBlock->serialNum);
    }
}


void MemPool::Free(void* pToBeFree)
{
    
}

