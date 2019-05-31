// 冒泡排序算法
void Bubble_Sort(uint8 *buff, uint8 num)
{
    bool isChange = true;
    uint32_t i=0, j=0;
    uint32_t len = num;
    if(len<2)
        return;
    for (j = 0; isChange&&(j < len); ++j)
    {
        isChange = false;
        for (i = j; i < len-j-1; ++i)
        {
            if(buff[i] > buff[i+1]) // 由小到大
            {
                uint8 temp = buff[i];
                buff[i] = buff[i+1];
                buff[i+1] = temp;
                isChange = true;
            }
        }
    }
}
