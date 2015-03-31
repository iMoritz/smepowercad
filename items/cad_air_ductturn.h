/**********************************************************************
** smepowercad
** Copyright (C) 2015 Smart Micro Engineering GmbH
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/

#ifndef CAD_AIR_DUCTTURN_H
#define CAD_AIR_DUCTTURN_H

#include "caditem.h"
#include "cad_basic_duct.h"

class CAD_air_ductTurn : public CADitem
{
public:
    CAD_air_ductTurn();
    virtual ~CAD_air_ductTurn();
    virtual QList<CADitemTypes::ItemType> flangable_items();
    virtual QImage wizardImage();
    virtual QString iconPath();
    virtual QString domain();
    virtual QString description();
    virtual void calculate();
    virtual void processWizardInput();
    virtual void paint(GLWidget* glwidget);
    virtual QMatrix4x4 rotationOfFlange(quint8 num);

    qreal s;
    qreal ff, fe;

    qreal r;
    qreal b;
    qreal b2;
    qreal a;
    qreal alpha;
    qreal f;
    qreal e;

//    QVector3D vertices[2][13][5];

    QOpenGLBuffer arrayBufVertices;
    QOpenGLBuffer indexBufFaces;
    QOpenGLBuffer indexBufLines;

    CAD_basic_duct *flange_left_duct;
    CAD_basic_duct *flange_right_duct;
};

#endif // CAD_AIR_DUCTTURN_H
