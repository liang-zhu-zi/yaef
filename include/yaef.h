

#ifndef __YAEF_H__
#define __YAEF_H__

class XSet;
class XEvent;
class XData;

class XData
{
public:
    XData();
    virtual ~XData()=0;

private:
    bool changed; // value changed
    bool updated; // value updated - XData notified

    XSet* set;
};

class XEvent
{
public:
    XEvent();
    virtual ~XEvent()=0;

    // TODO: add more functions
};

class XSet
{
public:
    XSet();
    virtual ~XSet();

    virtual void addEvent(XEvent* pEvent);
    virtual void removeEvent(XEvent* pEvent);

    virtual void addData(XData* pData);
    virtual void addSubData(XData* parent, XData* pData);
    virtual void removeData(XData* pData);

    virtual void subscribe([](XEvent* pEvent, XData* pData, ...){}, XEvent* pEvent, XData* pData, ...);
    // virtual void unsubscribe([](XEvent* pEvent, XData* pData, ...){}, , XEvent* pEvent, XData* pData, ...);
    virtual void subscribe([](XData* pData, ...){}, XData* pData, ...);
    // virtual void unsubscribe([](XData* pData, ...){}, XData* pData, ...);

    virtual void notify(XEvent* pEvent, XData* pData, ...);
private:
    void dispatch(XEvent* pEvent, XData* pData);

    std::list<XEvent*> events;
    std::list<XData*> datas;
    std::map<XEvent*, std::list<XData*> > eventDataMap;
    std::map<XData*, std::list<XEvent*> > dataEventMap;
    std::map<XData*, std::list<XData*> > dataSubDataMap;
    std::map<XData*, std::list<XData*> > subDataDataMap;
};

#endif // __YAEF_H__
