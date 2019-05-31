/**********************************************************************************************************
 *
 * @file ew_linklist.h
 * 
 * @brief 单向链表头文件.
 * 
 * 
 * @author      Five
 * @date        Created:    2018-07-02
 * 
**********************************************************************************************************/
#ifndef __EW_LINKLIST_H
#define __EW_LINKLIST_H

/**********************************************************************************************************
  Includes
**********************************************************************************************************/
#include "ew_common.h"

/**********************************************************************************************************
  Defines
**********************************************************************************************************/
#define QR_MEM_CUSTOM      1 

#if QR_MEM_CUSTOM
#include <stdint.h>
#include <stdlib.h>

#include "lv_misc/lv_mem.h"

#define ll_malloc    pvPortMalloc //lv_mem_alloc
#define ll_free      vPortFree //lv_mem_free
#define ll_calloc    //lv_mem_calloc
#define ll_realloc   //lv_mem_realloc

#else
#define ll_malloc    malloc
#define ll_free      free
#define ll_calloc    calloc
#define ll_realloc   realloc
#endif
/**********************************************************************************************************
  Typedefs
**********************************************************************************************************/
struct _EW_LinkList
{
    void * data;
    struct _EW_LinkList *next;
}; 
typedef struct _EW_LinkList EW_LinkList_t;

/**********************************************************************************************************
  Extern
**********************************************************************************************************/

/**********************************************************************************************************
  Functions 
**********************************************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

void EW_LinkList_Init (EW_LinkList_t *head);

bool EW_LinkList_Clear (EW_LinkList_t *head);

bool EW_LinkList_Add (EW_LinkList_t *head, void *data ,uint32_t dataSize);

bool EW_LinkList_Insert (EW_LinkList_t *head, uint32_t num, void *data, uint32_t dataSize);

bool EW_LinkList_Del (EW_LinkList_t *head, void *node);

bool EW_LinkList_Move (EW_LinkList_t *head, uint32_t num);

void * EW_LinkList_Read (EW_LinkList_t *head, uint32_t num);

uint32_t EW_LinkList_length (EW_LinkList_t *head);

bool EW_LinkList_Swap (EW_LinkList_t *head, uint32_t num1, uint32_t num2);

void EW_LinkList_Test(void);


#ifdef __cplusplus
}
#endif

#endif                                                                  /* __EW_LINKLIST_H           */
/**********************************************************************************************************
  END FILE
**********************************************************************************************************/
