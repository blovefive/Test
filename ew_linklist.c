/**********************************************************************************************************
 *
 * @file ew_linklist.c
 * 
 * @brief 单向链表源文件.
 * 
 * 
 * @author      Five
 * @date        Created:    2018-07-02
 * 
**********************************************************************************************************/
#include "ew_linklist.h"

/**********************************************************************************************************
  Constants and macros
**********************************************************************************************************/

/**********************************************************************************************************
  Private functions
**********************************************************************************************************/

/**********************************************************************************************************
  Local variables
**********************************************************************************************************/

/**********************************************************************************************************
  Functions
**********************************************************************************************************/

/**
 * @brief Init link-list
 * 
 * @param head pointer of the link-list head
 * @return void 
 */
void EW_LinkList_Init (EW_LinkList_t *head)
{
    head->data = NULL;
    head->next = NULL;
}

/**
 * @brief Clear link-list
 * 
 * @param head pointer of the link-list head
 * @return true is cleanly otherwise return false
 */
bool EW_LinkList_Clear (EW_LinkList_t *head)
{
    EW_LinkList_t *p = NULL;
    if(head==NULL)
        return false;
    while(head->next)
    {
        p = head->next;
        head->next = p->next;
        ll_free(p->data);
        ll_free(p);
    }
    return true;
}

/**
 * @brief Add link-list
 * 
 * @param head pointer of the link-list head
 * @param data pointer of the link-list data
 * @param dataSize size of the link-list data
 * @return true is added otherwise return false
 */
bool EW_LinkList_Add (EW_LinkList_t *head, void *data ,uint32_t dataSize)
{
    EW_LinkList_t *p = head;
    EW_LinkList_t *next = NULL;
    if(head==NULL)
        return false;
    next = (EW_LinkList_t *)ll_malloc(sizeof(EW_LinkList_t));
    if(next==NULL)
        return false;
    
    while(p->next)  
    {
        p = p->next;    
    }
    
    p->next = next;
    next->data = (void*)ll_malloc(dataSize);
    if(next->data==NULL)
    {
        free(next);
        return false;
    }
    
    next->next = NULL;
    memcpy(next->data,data,dataSize);

    return true;
}

/**
 * @brief Insert link-list
 * 
 * @param head pointer of the link-list head
 * @param num number of the link-list node PS:num must be greater than 1 
 * @param data pointer of the link-list data
 * @param dataSize size of the link-list data
 * @return true is inserted otherwise return false
 */
bool EW_LinkList_Insert (EW_LinkList_t *head, uint32_t num, void *data, uint32_t dataSize)
{
    EW_LinkList_t *p = head;
    EW_LinkList_t *next = NULL;
    uint32_t count = 0;
    if(head==NULL)
        return false;
    next = (EW_LinkList_t *)ll_malloc(sizeof(EW_LinkList_t));
    if(next==NULL)
        return false;
    do{
        if(++count==num)
        {
            next->next = p->next;
            p->next = next;
            next->data = (void*)ll_malloc(dataSize);
            if(next->data==NULL)
            {
                ll_free(next);
                return false;
            }
            memcpy(next->data,data,dataSize);
            return true;
        }
        p = p->next;    
    }while(p->next);  
    ll_free(next);
    return false;
}

/**
 * @brief Delete link-list
 * 
 * @param head pointer of the link-list head
 * @param node pointer of the link-list node
 * @return true is deleted otherwise return false
 */
bool EW_LinkList_Del (EW_LinkList_t *head, void *node)
{
    EW_LinkList_t *p = head;
    if(head==NULL)
        return false;
    while(p->next)
    {
        if(p->next==node)
        {
            EW_LinkList_t *del = p->next;
            p->next = del->next;
            ll_free(del->data);
            ll_free(del);
            return true;
        }
        p = p->next;
    }
    return false;
}

/**
 * @brief Move link-list 
 * 
 * @param head pointer of the link-list head
 * @param num number of the link-list node PS:num must be greater than 1 
 * @return true is moved otherwise return false
 * @note like EW_LinkList_Del function
 */
bool EW_LinkList_Move (EW_LinkList_t *head, uint32_t num)
{
    EW_LinkList_t *p = head;
    uint32_t count = 0;
    if(head==NULL)
        return false;
    while(p->next)
    {
        if(++count==num)
        {
            EW_LinkList_t *del = p->next;
            p->next = del->next;
            ll_free(del->data);
            ll_free(del);
            return true;
        }
        p = p->next;
    }
    return false;
}

/**
 * @brief Read link-list 
 * 
 * @param head pointer of the link-list head
 * @param num number of the link-list node PS:num must be greater than 1 
 * @return node pointer otherwise return NULL
 */
void * EW_LinkList_Read (EW_LinkList_t *head, uint32_t num)
{
    EW_LinkList_t *p = head;
    uint32_t count = 0;
    if(head==NULL)
        return NULL;
    while(p->next)
    {
        if(++count==num)
            return p->next;
        p = p->next;
    }
    return NULL;
}

/**
 * @brief Calculate link-list lengths
 * 
 * @param head pointer of the link-list head
 * @return number of the link-list lengths
 */
uint32_t EW_LinkList_length (EW_LinkList_t *head)
{
    EW_LinkList_t *p = head;
    uint32_t count = 0;
    if(head==NULL)
        return NULL;
    while(p->next)
    {
        ++count;
        p = p->next;
    }
    return count;
}

/**
 * @brief Swap link-list node
 * 
 * @param head pointer of the link-list head
 * @param num1 number of the link-list node PS:num1 must be greater than 1 
 * @param num2 number of the link-list node PS:num2 must be greater than num1 
 * @return true is swapped otherwise return false
 */
bool EW_LinkList_Swap (EW_LinkList_t *head, uint32_t num1, uint32_t num2)
{
    EW_LinkList_t *p = head;
    EW_LinkList_t *swap1 = NULL;
    uint32_t count = 0;
    if(head==NULL)
        return false;
    while(p->next)
    {
        ++count;
        if(count==num1)
        {
            swap1 = p->next;
        }
        else if(count==num2)
        {
            EW_LinkList_t *swap2 = p->next;
            void *temp = swap1->data;
            swap1->data = swap2->data;
            swap2->data = temp;
            return true;
        }
        p = p->next;
    }
    return false;
}

void EW_LinkList_Test(void)
{
    static EW_LinkList_t head;
    uint8_t node[]={1,2,3,4,5,6,7,8,9,10};
    EW_LinkList_Init(&head);
    for(uint8_t i=0;i<10;++i)
    {
        EW_LinkList_Add(&head,&node[i],1);
    }
    //memset(node,0,10);
    //EW_LinkList_Insert(&head, 2, &node[0], 1);
    //EW_LinkList_Swap(&head, 1, 2);
    EW_LinkList_Del(&head,EW_LinkList_Read(&head,2));
    EW_LinkList_Move(&head,2);
    for(uint8_t i=1;i<=EW_LinkList_length(&head);++i)
    {
        EW_LinkList_t *p = EW_LinkList_Read(&head,i);
        node[i-1] = *(uint8_t*)p->data;
    }
}


/**********************************************************************************************************
  END FILE
**********************************************************************************************************/
