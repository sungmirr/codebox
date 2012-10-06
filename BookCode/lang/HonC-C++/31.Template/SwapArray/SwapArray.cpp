/*++
    2012.10.06

    31.1 SwapArray(358p)
       �Ϲ�Ÿ���� Swap�Լ��� �ٸ� ������� ����
       �׷��� SwapArray���� �ۼ�
       SwapArray�� ���ø� �Լ����� Swap���� �ߺ� ���� ����
       => ���ø������� �����ε� ������
 --*/


#include <Turboc.h>

template <typename T>
void SwapArray(T *pa, T *pb, int num)
{
    T *pt;
    pt = (T *)malloc(num * sizeof(T));
    for(int i=0; i < num; ++i)
    {
        pt[i] = pa[i];
        pa[i] = pb[i];
        pb[i] = pt[i];
    }
    /*
    memcpy(tt, pa, num*sizeof(T));
    memcpy(pa, pb, num*sizeof(T));
    memcpy(pb, tt, num*sizeof(T));
    */

    free(pt);
}

void main()
{
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};
    char c[]="���ڿ�";
    char d[]="string";

    SwapArray(a, b, sizeof(a)/sizeof(a[0]));
    printf("c=%s, d=%s\n", c, d);
    SwapArray(c, d, sizeof(c)/sizeof(c[0]));
    printf("c=%s, d=%s\n", c, d);
}