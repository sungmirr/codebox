/*++
    2012.10.20

    40.시퀀스컨테이너, ...................


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
        puts("그래픽 오브젝트입니다.");
    }
};

class Line : public Graphic
{
public:
    virtual void Draw()
    {
        puts("선을 긋습니다.");
    }
};

class Circle : public Graphic
{
public:
    virtual void Draw()
    {
        puts("동그라미를 그렸습니다.");
    }
};

class Rect : public Graphic
{
public:
    virtual void Draw()
    {
        puts("사각형을 그렸습니다.");
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