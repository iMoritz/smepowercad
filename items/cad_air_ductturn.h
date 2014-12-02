#ifndef CAD_AIR_DUCTTURN_H
#define CAD_AIR_DUCTTURN_H

#include "caditem.h"
#include "cad_basic_duct.h"

class CAD_air_ductTurn : public CADitem
{
public:
    CAD_air_ductTurn();
    virtual ~CAD_air_ductTurn();
    static QList<CADitem::ItemType> flangable_items();
    static QImage wizardImage();
    virtual void calculate();
    virtual void processWizardInput();

    qreal s;
    qreal flange_size;

    qreal r;
    qreal b;
    qreal b2;
    qreal a;
    qreal alpha;
    qreal f;
    qreal e;

    QVector3D vertices[2][13][5];

    CAD_basic_duct *flange_left_duct;
    CAD_basic_duct *flange_right_duct;
};

#endif // CAD_AIR_DUCTTURN_H
