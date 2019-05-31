/**********************************************************************************************************
 *
 * @file ew_mode_timeline_linklist.c
 * 
 * @brief Timeline链表源文件.
 * 
 * 
 * @author      Five
 * @date        Created:    2018-07-02
 * 
**********************************************************************************************************/
#include "ew_linklist.h"
#include "ew_mode_timeline_linklist.h"
#include "system_resource.h"

/**********************************************************************************************************
  Constants and macros
**********************************************************************************************************/

/**********************************************************************************************************
  Private functions
**********************************************************************************************************/

/**********************************************************************************************************
  Local variables
**********************************************************************************************************/
static EW_LinkList_t linklistHead;

static uint32_t TimeLine = 0;
/**********************************************************************************************************
  Functions
**********************************************************************************************************/
/**
 * @brief 创建链表
 * 
 */
void EW_Timeline_LinkList_Init (void)
{
    EW_LinkList_Init(&linklistHead);
    g_SysResDataHandle.ancsNum_Timeline = 0;
    TimeLine = 0;
}

/**
 * @brief 删除链表
 * 
 */
void EW_Timeline_LinkList_Clear (void)
{
    EW_LinkList_Clear(&linklistHead);
    g_SysResDataHandle.ancsNum_Timeline = 0;
    TimeLine = 0;
}

/**
 * @brief 
 * 
 * @param type 
 * @param line 
 * @param addr 
 */
bool EW_Timeline_LinkList_Add (uint32_t type, uint32_t addr)
{
    EW_Timeline_Node_t node;
    node.type = type;
    node.line = TimeLine++;
    node.addr = addr;
    if(EW_LinkList_Insert(&linklistHead, 1, &node, sizeof(node)))
        ++g_SysResDataHandle.ancsNum_Timeline;
//    EW_DebugLog("[%s]%d-%d\r\n",__FUNCTION__,TimeLine,g_SysResDataHandle.ancsNum_Timeline);
    return true;
}

/**
 * @brief 
 * 
 * @param num 链表的第n个节点
 * @return 返回节点的addr
 */
uint32_t EW_Timeline_LinkList_AddrGet (uint32_t num)
{
    EW_LinkList_t *node = EW_LinkList_Read(&linklistHead,num);
    if(node!=NULL)
    {
        EW_Timeline_Node_t *temp = node->data;
        return temp->addr;
    }
    return NULL;
}

/**
 * @brief 
 * 
 * @param num 链表的第n个节点
 * @return 返回节点的type
 */
uint32_t EW_Timeline_LinkList_TypeGet (uint32_t num)
{
    EW_LinkList_t *node = EW_LinkList_Read(&linklistHead,num);
    if(node!=NULL)
    {
        EW_Timeline_Node_t *temp = node->data;
        return temp->type;
    }
    return NULL;
}

/**
 * @brief 
 * 
 * @param num 删除第num个节点
 */
void EW_Timeline_LinkList_NumDel (uint32_t num)
{
    uint32_t n = num;
    if(n > 0)
    {
        EW_LinkList_t *node = EW_LinkList_Read(&linklistHead, n);
        if(node!=NULL)
        {
            EW_LinkList_Del(&linklistHead, node);
            --g_SysResDataHandle.ancsNum_Timeline;
        }
    }
}

/**
 * @brief 
 * 
 * @param num 删除某种类型的所有节点
 */
void EW_Timeline_LinkList_TypeDel (uint32_t type)
{
    uint32_t length = EW_LinkList_length(&linklistHead);
    for(uint32_t i=1; i<=length; ++i)
    {
        EW_LinkList_t *node = EW_LinkList_Read(&linklistHead, i);
        if(node!=NULL)
        {
            EW_Timeline_Node_t *data = node->data;
            if(data->type == type)
            {
                EW_LinkList_Del(&linklistHead, node);
                --g_SysResDataHandle.ancsNum_Timeline;
            }
        }
    }
}

/**
 * @brief 
 * 
 * @param start 需要删除的起始地址
 * @param stop 需要删除的结束地址
 */
void EW_Timeline_LinkList_AddrDel (uint32_t start, uint32_t stop)
{
    uint32_t length = EW_LinkList_length(&linklistHead);
    for(uint32_t i=1; i<=length; ++i)
    {
        EW_LinkList_t *node = EW_LinkList_Read(&linklistHead, i);
        if(node!=NULL)
        {
            EW_Timeline_Node_t *data = node->data;
            if((data->addr>=start) && (data->addr<=stop))
            {
                EW_LinkList_Del(&linklistHead, node);
                --g_SysResDataHandle.ancsNum_Timeline;
                if(start == stop)   //删除单个
                    break;
                else
                    --i;    //继续删除
            }
        }
    }
}

/**
 * @brief 获取链表个数
 * 
 */
uint32_t EW_Timeline_LinkList_GetNum (void)
{
    return EW_LinkList_length(&linklistHead);
}

/**
 * @brief 将链表按line由大到小排序
 * 
 */
void EW_Timeline_LinkList_Sort (void)
{
    
    bool isChange = true;
    uint32_t i=0, j=0;
    uint32_t len = EW_LinkList_length(&linklistHead);
    if(len<2)
        return;
    for (j = 1; isChange&&(j <= len-1); ++j)
    {
        isChange = false;
        for (i = 1; i <= len-j; ++i)
        {
            EW_LinkList_t *p1 = EW_LinkList_Read(&linklistHead, i);
            EW_LinkList_t *p2 = EW_LinkList_Read(&linklistHead, i+1);
            if(p1!=NULL && p2!=NULL)
            {
                EW_Timeline_Node_t *d1 = p1->data;
                EW_Timeline_Node_t *d2 = p2->data;
                if(d1->line < d2->line)
                {
                    EW_LinkList_Swap(&linklistHead,i,i+1);
                    isChange = true;
                }
            }
        }
    }
    EW_LinkList_t *p = EW_LinkList_Read(&linklistHead, 1);
    EW_Timeline_Node_t *d = p->data;
    TimeLine = d->line+1;
    
}

#if 0

void EW_Timeline_LinkList_Print(void)
{
    uint32_t len = EW_Timeline_LinkList_GetNum();

    for(uint32_t i=1;i<=len;++i)
    {
        EW_LinkList_t *p1 = EW_LinkList_Read(&linklistHead, i);
        if(p1!=NULL)
        {
            EW_Timeline_Node_t *d1 = p1->data;
//            EW_DebugLog("%4d %4d \r\n",d1->line,d1->addr);
        }
    }
}
#endif
/**********************************************************************************************************
  END FILE
**********************************************************************************************************/
/**********************************************************************************************************
 *
 * @file ew_linklist.c
 * 
 * @brief 链表源文件.
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
