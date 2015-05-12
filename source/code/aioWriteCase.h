/*
 * =====================================================================================
 *
 *       Filename:  aioWriteCase.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/14/2014 01:50:24 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  jiangheng , jiangheng@UnitedStack.com 
 *        Company:  United Stack 
 *
 * =====================================================================================
 */
#ifndef AIO_WRITE_CASE_H
#define AIO_WRITE_CASE_H

#include "aioCase.h" 
static void aio_write_completion(void *vc, void *pc);
class AioWriteCase: public AioCase {
public:
    AioWriteCase(string caseName, librbd::Image *pImage, uint64_t ioSize, uint64_t ioThreads, uint64_t ioBytes, string ioPattern);
    ~AioWriteCase();
    bool start_io(int max, uint64_t off, uint64_t len, bufferlist& bl);
};
#endif
