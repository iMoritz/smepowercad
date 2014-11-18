#include "cad_air_ductteeconnector.h"

CAD_air_ductTeeConnector::CAD_air_ductTeeConnector() : CADitem(CADitem::Air_DuctTeeConnector)
{
    endcap_1 = new CAD_basic_duct();
    endcap_2 = new CAD_basic_duct();
    endcap_3 = new CAD_basic_duct();
    flange_1 = new CAD_basic_duct();
    flange_2 = new CAD_basic_duct();
    flange_3 = new CAD_basic_duct();

    this->subItems.append(endcap_1);
    this->subItems.append(endcap_2);
    this->subItems.append(endcap_3);
    this->subItems.append(flange_1);
    this->subItems.append(flange_2);
    this->subItems.append(flange_3);

    this->description = "Air|Duct T-Connector";
    wizardParams.insert("Position x", QVariant::fromValue(0.0));
    wizardParams.insert("Position y", QVariant::fromValue(0.0));
    wizardParams.insert("Position z", QVariant::fromValue(0.0));
    wizardParams.insert("Angle x", QVariant::fromValue(0.0));
    wizardParams.insert("Angle y", QVariant::fromValue(0.0));
    wizardParams.insert("Angle z", QVariant::fromValue(0.0));

    wizardParams.insert("Height (a)", QVariant::fromValue(30.0));
    wizardParams.insert("Width 1 (b)", QVariant::fromValue(30.0));
    wizardParams.insert("Width 2 (d)", QVariant::fromValue(30.0));
    wizardParams.insert("Offset (e)", QVariant::fromValue(00.0));
    wizardParams.insert("Width 3 (h)", QVariant::fromValue(50.0));
    wizardParams.insert("Length l", QVariant::fromValue(260.0));
    wizardParams.insert("Offset (m)", QVariant::fromValue(100.0));
    wizardParams.insert("Offset (n)", QVariant::fromValue(110.0));
    wizardParams.insert("Radius 1 (r1)", QVariant::fromValue(50.0));
    wizardParams.insert("Radius 2 (r2)", QVariant::fromValue(50.0));
    wizardParams.insert("Endcap (u)", QVariant::fromValue(50.0));
    wizardParams.insert("Flange size", QVariant::fromValue(1.0));
    wizardParams.insert("Wall thickness", QVariant::fromValue(1.0));


    processWizardInput();
    calculate();
}

CAD_air_ductTeeConnector::~CAD_air_ductTeeConnector()
{

}

QList<CADitem::ItemType> CAD_air_ductTeeConnector::flangable_items()
{
    QList<CADitem::ItemType> flangable_items;
    flangable_items.append(CADitem::Air_Duct);
    flangable_items.append(CADitem::Air_DuctEndPlate);
    flangable_items.append(CADitem::Air_DuctFireDamper);
    flangable_items.append(CADitem::Air_DuctTeeConnector);
    flangable_items.append(CADitem::Air_DuctTransition);
    flangable_items.append(CADitem::Air_DuctTransitionRectRound);
    flangable_items.append(CADitem::Air_DuctTurn);
    flangable_items.append(CADitem::Air_DuctVolumetricFlowController);
    flangable_items.append(CADitem::Air_DuctYpiece);
    flangable_items.append(CADitem::Air_Filter);
    flangable_items.append(CADitem::Air_HeatExchangerAirAir);
    flangable_items.append(CADitem::Air_HeatExchangerWaterAir);
    flangable_items.append(CADitem::Air_MultiLeafDamper);
    return flangable_items;
}

QImage CAD_air_ductTeeConnector::wizardImage()
{
    QImage image;
    QFileInfo fileinfo(__FILE__);
    QString imageFileName = fileinfo.baseName();
    imageFileName.prepend(":/itemGraphic/");
    imageFileName.append(".png");

    qDebug() << imageFileName;

    image.load(imageFileName, "PNG");

    return image;
}

void CAD_air_ductTeeConnector::calculate()
{
    matrix_rotation.setToIdentity();
    matrix_rotation.rotate(angle_x, 1.0, 0.0, 0.0);
    matrix_rotation.rotate(angle_y, 0.0, 1.0, 0.0);
    matrix_rotation.rotate(angle_z, 0.0, 0.0, 1.0);

    boundingBox.reset();

    this->snap_flanges.clear();
    this->snap_center.clear();
    this->snap_vertices.clear();

    this->snap_basepoint = (position);

    endcap_1->wizardParams.insert("Position x", QVariant::fromValue(position.x()));
    endcap_1->wizardParams.insert("Position y", QVariant::fromValue(position.y()));
    endcap_1->wizardParams.insert("Position z", QVariant::fromValue(position.z()));
    endcap_1->wizardParams.insert("Angle x", QVariant::fromValue(angle_x));
    endcap_1->wizardParams.insert("Angle y", QVariant::fromValue(angle_y));
    endcap_1->wizardParams.insert("Angle z", QVariant::fromValue(angle_z+180));
    endcap_1->wizardParams.insert("Length (l)", QVariant::fromValue(u));
    endcap_1->wizardParams.insert("Width (b)", QVariant::fromValue(b));
    endcap_1->wizardParams.insert("Height (a)", QVariant::fromValue(a));
    endcap_1->wizardParams.insert("Wall thickness", QVariant::fromValue(wall_thickness));
    endcap_1->processWizardInput();
    endcap_1->calculate();

    flange_1->wizardParams.insert("Position x", QVariant::fromValue(position.x()));
    flange_1->wizardParams.insert("Position y", QVariant::fromValue(position.y()));
    flange_1->wizardParams.insert("Position z", QVariant::fromValue(position.z()));
    flange_1->wizardParams.insert("Angle x", QVariant::fromValue(angle_x));
    flange_1->wizardParams.insert("Angle y", QVariant::fromValue(angle_y));
    flange_1->wizardParams.insert("Angle z", QVariant::fromValue(angle_z+180));
    flange_1->wizardParams.insert("Length (l)", QVariant::fromValue(flange_size));
    flange_1->wizardParams.insert("Width (b)", QVariant::fromValue(b + 2 * flange_size));
    flange_1->wizardParams.insert("Height (a)", QVariant::fromValue(a + 2 * flange_size));
    flange_1->wizardParams.insert("Wall thickness", QVariant::fromValue(flange_size));
    flange_1->processWizardInput();
    flange_1->calculate();

    QVector3D position_e2 = position + matrix_rotation * QVector3D(l, b/2 - e - d/2, 0);
    endcap_2->wizardParams.insert("Position x", QVariant::fromValue(position_e2.x()));
    endcap_2->wizardParams.insert("Position y", QVariant::fromValue(position_e2.y()));
    endcap_2->wizardParams.insert("Position z", QVariant::fromValue(position_e2.z()));
    endcap_2->wizardParams.insert("Angle x", QVariant::fromValue(angle_x));
    endcap_2->wizardParams.insert("Angle y", QVariant::fromValue(angle_y));
    endcap_2->wizardParams.insert("Angle z", QVariant::fromValue(angle_z));
    endcap_2->wizardParams.insert("Length (l)", QVariant::fromValue(u));
    endcap_2->wizardParams.insert("Width (b)", QVariant::fromValue(d));
    endcap_2->wizardParams.insert("Height (a)", QVariant::fromValue(a));
    endcap_2->wizardParams.insert("Wall thickness", QVariant::fromValue(wall_thickness));
    endcap_2->processWizardInput();
    endcap_2->calculate();

    flange_2->wizardParams.insert("Position x", QVariant::fromValue(position_e2.x()));
    flange_2->wizardParams.insert("Position y", QVariant::fromValue(position_e2.y()));
    flange_2->wizardParams.insert("Position z", QVariant::fromValue(position_e2.z()));
    flange_2->wizardParams.insert("Angle x", QVariant::fromValue(angle_x));
    flange_2->wizardParams.insert("Angle y", QVariant::fromValue(angle_y));
    flange_2->wizardParams.insert("Angle z", QVariant::fromValue(angle_z));
    flange_2->wizardParams.insert("Length (l)", QVariant::fromValue(flange_size));
    flange_2->wizardParams.insert("Width (b)", QVariant::fromValue(d + 2 * flange_size));
    flange_2->wizardParams.insert("Height (a)", QVariant::fromValue(a + 2 * flange_size));
    flange_2->wizardParams.insert("Wall thickness", QVariant::fromValue(flange_size));
    flange_2->processWizardInput();
    flange_2->calculate();

    QVector3D position_e3 = position + matrix_rotation * QVector3D(n + h/2, b/2 -e - d - m, 0);
    endcap_3->wizardParams.insert("Position x", QVariant::fromValue(position_e3.x()));
    endcap_3->wizardParams.insert("Position y", QVariant::fromValue(position_e3.y()));
    endcap_3->wizardParams.insert("Position z", QVariant::fromValue(position_e3.z()));
    endcap_3->wizardParams.insert("Angle x", QVariant::fromValue(angle_x));
    endcap_3->wizardParams.insert("Angle y", QVariant::fromValue(angle_y));
    endcap_3->wizardParams.insert("Angle z", QVariant::fromValue(angle_z-90));
    endcap_3->wizardParams.insert("Length (l)", QVariant::fromValue(u));
    endcap_3->wizardParams.insert("Width (b)", QVariant::fromValue(h));
    endcap_3->wizardParams.insert("Height (a)", QVariant::fromValue(a));
    endcap_3->wizardParams.insert("Wall thickness", QVariant::fromValue(wall_thickness));
    endcap_3->processWizardInput();
    endcap_3->calculate();

    flange_3->wizardParams.insert("Position x", QVariant::fromValue(position_e3.x()));
    flange_3->wizardParams.insert("Position y", QVariant::fromValue(position_e3.y()));
    flange_3->wizardParams.insert("Position z", QVariant::fromValue(position_e3.z()));
    flange_3->wizardParams.insert("Angle x", QVariant::fromValue(angle_x));
    flange_3->wizardParams.insert("Angle y", QVariant::fromValue(angle_y));
    flange_3->wizardParams.insert("Angle z", QVariant::fromValue(angle_z-90));
    flange_3->wizardParams.insert("Length (l)", QVariant::fromValue(flange_size));
    flange_3->wizardParams.insert("Width (b)", QVariant::fromValue(h + 2 * flange_size));
    flange_3->wizardParams.insert("Height (a)", QVariant::fromValue(a + 2 * flange_size));
    flange_3->wizardParams.insert("Wall thickness", QVariant::fromValue(flange_size));
    flange_3->processWizardInput();
    flange_3->calculate();

    snap_flanges.append(position_e2);
    snap_flanges.append(position_e3);

    int x = 0;
    int y = 0;
    QMatrix4x4 matrix_turn;
    for(int w = 0; w <= 1; w++)
    {
        for (qreal i=0.0; i < 1.01; i += 0.10)
        {
            qreal angle_turn = 90.0 * i;

            matrix_turn.setToIdentity();
            matrix_turn.rotate(-angle_turn, 0.0, 0.0, 1.0);

            QVector3D linePos_turn1_1 = matrix_rotation * (matrix_turn * QVector3D(0.0, r1, -a/2) + QVector3D(n-r1,-b/2 -r1, 0.0));
            QVector3D linePos_turn1_2 = matrix_rotation * (matrix_turn * QVector3D(0.0, r1, a/2) + QVector3D(n-r1,-b/2 -r1, 0.0));
            QVector3D linePos_turn2_1 = matrix_rotation * (matrix_turn * QVector3D(-r2, 0.0, -a/2) + QVector3D(n+h+r2,-e-d-r2/2, 0.0));
            QVector3D linePos_turn2_2 = matrix_rotation * (matrix_turn * QVector3D(-r2, 0.0, a/2) + QVector3D(n+h+r2,-e-d-r2/2, 0.0));
            vertices_turn1[w][x][y] = linePos_turn1_1;
            vertices_turn2[w][x][y] = linePos_turn2_1;
            y++;
            vertices_turn1[w][x][y] = linePos_turn1_2;
            vertices_turn2[w][x][y] = linePos_turn2_2;
            y++;
        }
        y = 0;
        x++;
    }



}

void CAD_air_ductTeeConnector::processWizardInput()
{
    position.setX(wizardParams.value("Position x").toDouble());
    position.setY(wizardParams.value("Position y").toDouble());
    position.setZ(wizardParams.value("Position z").toDouble());
    angle_x = wizardParams.value("Angle x").toDouble();
    angle_y = wizardParams.value("Angle y").toDouble();
    angle_z = wizardParams.value("Angle z").toDouble();


    this->a = wizardParams.value("Height (a)").toDouble();
    this->b = wizardParams.value("Width 1 (b)").toDouble();
    this->d = wizardParams.value("Width 2 (d)").toDouble();
    this->e = wizardParams.value("Offset (e)").toDouble();
    this->h = wizardParams.value("Width 3 (h)").toDouble();
    this->l = wizardParams.value("Length l").toDouble();
    this->m = wizardParams.value("Offset (m)").toDouble();
    this->n = wizardParams.value("Offset (n)").toDouble();
    this->r1 = wizardParams.value("Radius 1 (r1)").toDouble();
    this->r2 = wizardParams.value("Radius 2 (r2)").toDouble();
    this->u = wizardParams.value("Endcap (u)").toDouble();
    this->flange_size = wizardParams.value("Flange size").toDouble();
    this->wall_thickness = wizardParams.value("Wall thickness").toDouble();

    if((u + r1 + b) != (e + d + m))
        qDebug() << "This item can not be drawn! (u + r1 + b) != (e + d + m)";

    if((n + h + r2 + u) != l)
        qDebug() << "This item can not be drawn! (n + h + r2 + u) != l";

}
