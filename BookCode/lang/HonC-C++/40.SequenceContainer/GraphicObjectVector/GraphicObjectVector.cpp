/*++
    2012.10.20

    40.�����������̳�, ...................


--*/ 

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Graphic
{
public:
    virtual void Draw()
    {
        puts("�׷��� ������Ʈ�Դϴ�.");
    }
};

class Line : public Graphic
{
public:
    virtual void Draw()
    {
        puts("���� �߽��ϴ�.");
    }
};

class Circle : public Graphic
{
public:
    virtual void Draw()
    {
        puts("���׶�̸� �׷Ƚ��ϴ�.");
    }
};

class Rect : public Graphic
{
public:
    virtual void Draw()
    {
        puts("�簢���� �׷Ƚ��ϴ�.");
    }
};

void del(Graphic *g)
{
    delete g;
}

void main()
{
    vector<Graphic *> vg;
    vg.push_back(new Graphic());
    vg.push_back(new Rect());
    vg.push_back(new Circle());
    vg.push_back(new Line());

    vector<Graphic *>::iterator it;
    for(it=vg.begin(); it!=vg.end(); ++it)
        (*it)->Draw();

    for_each(vg.begin(), vg.end(), del);
}