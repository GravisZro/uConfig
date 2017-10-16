#include "componentitem.h"

#include <QPainter>
#include <QDebug>

ComponentItem::ComponentItem(Component *component)
{
    setComponent(component);
}

void ComponentItem::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem * /*option*/,
                          QWidget * /*widget*/)
{
    painter->setPen(QColor(132, 0, 0));
    painter->drawRect(_numRect);
}

QRectF ComponentItem::boundingRect() const
{
    return _numRect.adjusted(-80, -80, 80, 80);
}

Component *ComponentItem::component() const
{
    return _component;
}

void ComponentItem::setComponent(Component *component)
{
    _component = component;
    _pinItemMap.clear();

    foreach (Pin *pin, component->pins())
    {
        PinItem *pinItem = new PinItem(pin);
        pinItem->setParentItem(this);
        _pinItemMap.insert(pin, pinItem);
    }
    _numRect = QRect(_component->rect().topLeft() / PinItem::ratio, _component->rect().size() / PinItem::ratio);

    update();
}

PinItem *ComponentItem::pinItem(Pin *pin)
{
    QMap<Pin*, PinItem* >::const_iterator pinIt = _pinItemMap.constFind(pin);
    if (pinIt != _pinItemMap.cend())
        return *pinIt;
    return Q_NULLPTR;
}
