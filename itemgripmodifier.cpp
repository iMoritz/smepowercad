#include "itemgripmodifier.h"
#include "ui_itemgripmodifier.h"

#include <QToolButton>

ItemGripModifier::ItemGripModifier(ItemDB *itemDB, ItemWizard *itemWizard, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemGripModifier)
{
    ui->setupUi(this);
    this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    this->hide();
    this->itemDB = itemDB;
    this->itemWizard = itemWizard;
    this->item = NULL;
    this->activeGrip = Grip_None;

    connect(this, SIGNAL(rejected()), this, SLOT(slot_rejected()));
}

ItemGripModifier::~ItemGripModifier()
{
    delete ui;
}

void ItemGripModifier::setItem(CADitem *item)
{
    this->item = item;
}

CADitem *ItemGripModifier::getItem()
{
    return this->item;
}

void ItemGripModifier::activateGrip(ItemGripModifier::ItemGripType gripType, QPoint mousePos, QVector3D scenePos)
{
    this->scenePos = scenePos;
    this->activeGrip = gripType;

    switch (gripType)
    {
    case Grip_Append:
    {
        showAppendBox();
        break;
    }
    case Grip_Copy:
    {
        break;
    }
    case Grip_Length:
    {
        break;
    }
    case Grip_Move:
    {
        break;
    }
    case Grip_Rotate_X:
    {
        break;
    }
    case Grip_Rotate_Y:
    {
        break;
    }
    case Grip_Rotate_Z:
    {
        break;
    }
    }
}

void ItemGripModifier::finishGrip()
{
    this->item = NULL;
    this->activeGrip = Grip_None;
    hide();
    deleteWdgs(ui->gridLayout);
}

ItemGripModifier::ItemGripType ItemGripModifier::getActiveGrip()
{
    return this->activeGrip;
}

void ItemGripModifier::slot_rejected()
{
    this->item = NULL;
    this->hide();
    deleteWdgs(ui->gridLayout);
}

void ItemGripModifier::slot_button_clicked()
{
    QToolButton* button = (QToolButton*)this->sender();
    CADitem::ItemType type = (CADitem::ItemType)button->property("ItemType").toInt();

    CADitem* newItem = itemDB->drawItem(this->item->layerName, type);

    newItem->wizardParams.insert("Position x", QVariant::fromValue(scenePos.x()));
    newItem->wizardParams.insert("Position y", QVariant::fromValue(scenePos.y()));
    newItem->wizardParams.insert("Position z", QVariant::fromValue(scenePos.z()));
    // tbd: add flange angles
    newItem->wizardParams.insert("Angle x", QVariant::fromValue(this->item->angle_x));
    newItem->wizardParams.insert("Angle y", QVariant::fromValue(this->item->angle_y));
    newItem->wizardParams.insert("Angle z", QVariant::fromValue(this->item->angle_z));

    itemWizard->showWizard(newItem);

    finishGrip();
}

void ItemGripModifier::deleteWdgs(QLayout *layout)
{
    QLayoutItem *item;
    while ((item = layout->takeAt(0)))
    {
        if (item->layout())
        {
            deleteWdgs(item->layout());
            delete item->layout();
            qDebug() << "Deleting a layout";
        }
        if (item->widget())
        {
            delete item->widget();
            qDebug() << "Deleting a widget";
        }
        delete item;
        qDebug() << "Deleting an item";

    }

    qDebug() << "layout count:" << layout->count();


    this->layout()->removeItem(ui->gridLayout);
    ui->gridLayout->deleteLater();
    ui->gridLayout = new QGridLayout(this);
    ((QVBoxLayout*)this->layout())->insertLayout(1, ui->gridLayout);
}

void ItemGripModifier::showAppendBox()
{
    QList<CADitem::ItemType> flangable_items;

    switch (item->getType())
    {
    case CADitem::Air_CanvasFlange:
    {
        flangable_items = CAD_air_canvasFlange::flangable_items();
        break;
    }
    case CADitem::Air_Duct:
    {
        flangable_items = CAD_air_duct::flangable_items();
        break;
    }
    case CADitem::Air_DuctBaffleSilencer:
    {
        flangable_items = CAD_air_ductBaffleSilencer::flangable_items();
        break;
    }
    case CADitem::Air_DuctEndPlate:
    {
        flangable_items = CAD_air_ductEndPlate::flangable_items();
        break;
    }
    case CADitem::Air_DuctFireDamper:
    {
        flangable_items = CAD_air_ductFireDamper::flangable_items();
        break;
    }
    case CADitem::Air_DuctFireResistant:
    {
        flangable_items = CAD_air_ductFireResistant::flangable_items();
        break;
    }
    case CADitem::Air_DuctTeeConnector:
    {
        flangable_items = CAD_air_ductTeeConnector::flangable_items();
        break;
    }
    case CADitem::Air_DuctTransition:
    {
        flangable_items = CAD_air_ductTransition::flangable_items();
        break;
    }
    case CADitem::Air_DuctTransitionRectRound:
    {
        flangable_items = CAD_air_ductTransitionRectRound::flangable_items();
        break;
    }
    case CADitem::Air_DuctTurn:
    {
        flangable_items = CAD_air_ductTurn::flangable_items();
        break;
    }
    case CADitem::Air_DuctVolumetricFlowController:
    {
        flangable_items = CAD_air_ductVolumetricFlowController::flangable_items();
        break;
    }
    case CADitem::Air_DuctYpiece:
    {
        flangable_items = CAD_air_ductYpiece::flangable_items();
        break;
    }
    case CADitem::Air_EmptyCabinet:
    {
        flangable_items = CAD_air_emptyCabinet::flangable_items();
        break;
    }
    case CADitem::Air_EquipmentFrame:
    {
        flangable_items = CAD_air_equipmentFrame::flangable_items();
        break;
    }
    case CADitem::Air_Fan:
    {
        flangable_items = CAD_air_fan::flangable_items();
        break;
    }
    case CADitem::Air_Filter:
    {
        flangable_items = CAD_air_filter::flangable_items();
        break;
    }
    case CADitem::Air_HeatExchangerAirAir:
    {
        flangable_items = CAD_air_heatExchangerAirAir::flangable_items();
        break;
    }
    case CADitem::Air_HeatExchangerWaterAir:
    {
        flangable_items = CAD_air_heatExchangerWaterAir::flangable_items();
        break;
    }
    case CADitem::Air_Humidifier:
    {
        flangable_items = CAD_air_humidifier::flangable_items();
        break;
    }
    case CADitem::Air_MultiLeafDamper:
    {
        flangable_items = CAD_air_multiLeafDamper::flangable_items();
        break;
    }
    case CADitem::Air_Pipe:
    {
        flangable_items = CAD_air_pipe::flangable_items();
        break;
    }
    case CADitem::Air_PipeEndCap:
    {
        flangable_items = CAD_air_pipeEndCap::flangable_items();
        break;
    }
    case CADitem::Air_PipeFireDamper:
    {
        flangable_items = CAD_air_pipeFireDamper::flangable_items();
        break;
    }
    case CADitem::Air_PipeReducer:
    {
        flangable_items = CAD_air_pipeReducer::flangable_items();
        break;
    }
    case CADitem::Air_PipeSilencer:
    {
        flangable_items = CAD_air_pipeSilencer::flangable_items();
        break;
    }
    case CADitem::Air_PipeTeeConnector:
    {
        flangable_items = CAD_air_pipeTeeConnector::flangable_items();
        break;
    }
    case CADitem::Air_PipeTurn:
    {
        flangable_items = CAD_air_pipeTurn::flangable_items();
        break;
    }
    case CADitem::Air_PipeVolumetricFlowController:
    {
        flangable_items = CAD_air_pipeVolumetricFlowController::flangable_items();
        break;
    }
    case CADitem::Air_PressureReliefDamper:
    {
        flangable_items = CAD_air_pressureReliefDamper::flangable_items();
        break;
    }
    case CADitem::Air_ThrottleValve:
    {
        flangable_items = CAD_air_throttleValve::flangable_items();
        break;
    }

    case CADitem::Arch_Beam:
    {
        flangable_items = CAD_arch_beam::flangable_items();
        break;
    }
    case CADitem::Arch_BlockOut:
    {
        flangable_items = CAD_arch_blockOut::flangable_items();
        break;
    }
    case CADitem::Arch_BoredPile:
    {
//        flangable_items = CAD_arch_::flangable_items();
        break;
    }
    case CADitem::Arch_Door:
    {
        flangable_items = CAD_arch_door::flangable_items();
        break;
    }
    case CADitem::Arch_Foundation:
    {
//        flangable_items = CAD_arch_::flangable_items();
        break;
    }
    case CADitem::Arch_Grating:
    {
//        flangable_items = CAD_arch_::flangable_items();
        break;
    }
    case CADitem::Arch_LevelSlab:
    {
        flangable_items = CAD_arch_levelSlab::flangable_items();
        break;
    }
    case CADitem::Arch_Support:
    {
        flangable_items = CAD_arch_support::flangable_items();
        break;
    }
    case CADitem::Arch_Wall_loadBearing:
    {
        flangable_items = CAD_arch_wall_loadBearing::flangable_items();
        break;
    }
    case CADitem::Arch_Wall_nonLoadBearing:
    {
        flangable_items = CAD_arch_wall_nonLoadBearing::flangable_items();
        break;
    }
    case CADitem::Arch_Window:
    {
        flangable_items = CAD_arch_window::flangable_items();
        break;
    }

    case CADitem::Basic_Arc:
    {
        flangable_items = CAD_basic_arc::flangable_items();
        break;
    }
    case CADitem::Basic_Box:
    {
        flangable_items = CAD_basic_box::flangable_items();
        break;
    }
    case CADitem::Basic_Circle:
    {
        flangable_items = CAD_basic_circle::flangable_items();
        break;
    }
    case CADitem::Basic_Cylinder:
    {
        flangable_items = CAD_basic_cylinder::flangable_items();
        break;
    }
    case CADitem::Basic_Duct:
    {
        flangable_items = CAD_basic_duct::flangable_items();
        break;
    }
    case CADitem::Basic_Face:
    {
//        flangable_items = CAD_basic_::flangable_items();
        break;
    }
    case CADitem::Basic_Line:
    {
        flangable_items = CAD_basic_line::flangable_items();
        break;
    }
    case CADitem::Basic_Pipe:
    {
        flangable_items = CAD_basic_pipe::flangable_items();
        break;
    }
    case CADitem::Basic_Plane:
    {
        flangable_items = CAD_basic_plane::flangable_items();
        break;
    }
    case CADitem::Basic_Point:
    {
        flangable_items = CAD_basic_point::flangable_items();
        break;
    }
    case CADitem::Basic_Polyline:
    {
        flangable_items = CAD_basic_polyline::flangable_items();
        break;
    }
    case CADitem::Basic_Sphere:
    {
        flangable_items = CAD_basic_sphere::flangable_items();
        break;
    }
    case CADitem::Basic_Turn:
    {
        flangable_items = CAD_basic_turn::flangable_items();
        break;
    }

    case CADitem::Electrical_Cabinet:
    {
        flangable_items = CAD_electrical_cabinet::flangable_items();
        break;
    }
    case CADitem::Electrical_CableTray:
    {
        flangable_items = CAD_electrical_cableTray::flangable_items();
        break;
    }

    case CADitem::HeatCool_Adjustvalve:
    {
        flangable_items = CAD_heatcool_adjustvalve::flangable_items();
        break;
    }
    case CADitem::HeatCool_BallValve:
    {
        flangable_items = CAD_heatcool_ballValve::flangable_items();
        break;
    }
    case CADitem::HeatCool_Boiler:
    {
        flangable_items = CAD_heatcool_boiler::flangable_items();
        break;
    }
    case CADitem::HeatCool_ButterflyValve:
    {
        flangable_items = CAD_heatcool_butterflyValve::flangable_items();
        break;
    }
    case CADitem::HeatCool_Chiller:
    {
        flangable_items = CAD_heatcool_chiller::flangable_items();
        break;
    }
    case CADitem::HeatCool_Controlvalve:
    {
        flangable_items = CAD_heatcool_controlvalve::flangable_items();
        break;
    }
    case CADitem::HeatCool_CoolingTower:
    {
        flangable_items = CAD_heatcool_coolingTower::flangable_items();
        break;
    }
    case CADitem::HeatCool_ExpansionChamber:
    {
        flangable_items = CAD_heatcool_expansionChamber::flangable_items();
        break;
    }
    case CADitem::HeatCool_Filter:
    {
        flangable_items = CAD_heatcool_filter::flangable_items();
        break;
    }
    case CADitem::HeatCool_Flange:
    {
        flangable_items = CAD_heatcool_flange::flangable_items();
        break;
    }
    case CADitem::HeatCool_Flowmeter:
    {
        flangable_items = CAD_heatcool_flowmeter::flangable_items();
        break;
    }
    case CADitem::HeatCool_HeatExchanger:
    {
        flangable_items = CAD_heatcool_heatExchanger::flangable_items();
        break;
    }
    case CADitem::HeatCool_Pipe:
    {
        flangable_items = CAD_heatcool_pipe::flangable_items();
        break;
    }
    case CADitem::HeatCool_PipeEndCap:
    {
        flangable_items = CAD_heatcool_pipeEndCap::flangable_items();
        break;
    }
    case CADitem::HeatCool_PipeReducer:
    {
        flangable_items = CAD_heatcool_pipeReducer::flangable_items();
        break;
    }
    case CADitem::HeatCool_PipeTeeConnector:
    {
        flangable_items = CAD_heatcool_pipeTeeConnector::flangable_items();
        break;
    }
    case CADitem::HeatCool_PipeTurn:
    {
        flangable_items = CAD_heatcool_pipeTurn::flangable_items();
        break;
    }
    case CADitem::HeatCool_Pump:
    {
        flangable_items = CAD_heatcool_pump::flangable_items();
        break;
    }
    case CADitem::HeatCool_Radiator:
    {
        flangable_items = CAD_heatcool_radiator::flangable_items();
        break;
    }
    case CADitem::HeatCool_SafetyValve:
    {
        flangable_items = CAD_heatcool_safetyValve::flangable_items();
        break;
    }
    case CADitem::HeatCool_Sensor:
    {
        flangable_items = CAD_heatcool_sensor::flangable_items();
        break;
    }
    case CADitem::HeatCool_StorageBoiler:
    {
        flangable_items = CAD_heatcool_storageBoiler::flangable_items();
        break;
    }
    case CADitem::HeatCool_WaterHeater:
    {
        flangable_items = CAD_heatcool_waterHeater::flangable_items();
        break;
    }

    case CADitem::Sanitary_ElectricWaterHeater:
    {
        flangable_items = CAD_sanitary_electricWaterHeater::flangable_items();
        break;
    }
    case CADitem::Sanitary_EmergencyEyeShower:
    {
        flangable_items = CAD_sanitary_emergencyEyeShower::flangable_items();
        break;
    }
    case CADitem::Sanitary_EmergencyShower:
    {
        flangable_items = CAD_sanitary_emergencyShower::flangable_items();
        break;
    }
    case CADitem::Sanitary_Flange:
    {
        flangable_items = CAD_sanitary_flange::flangable_items();
        break;
    }
    case CADitem::Sanitary_LiftingUnit:
    {
        flangable_items = CAD_sanitary_liftingUnit::flangable_items();
        break;
    }
    case CADitem::Sanitary_Pipe:
    {
        flangable_items = CAD_sanitary_pipe::flangable_items();
        break;
    }
    case CADitem::Sanitary_PipeEndCap:
    {
        flangable_items = CAD_sanitary_pipeEndCap::flangable_items();
        break;
    }
    case CADitem::Sanitary_PipeReducer:
    {
        flangable_items = CAD_sanitary_pipeReducer::flangable_items();
        break;
    }
    case CADitem::Sanitary_PipeTeeConnector:
    {
        flangable_items = CAD_sanitary_pipeTeeConnector::flangable_items();
        break;
    }
    case CADitem::Sanitary_PipeTurn:
    {
        flangable_items = CAD_sanitary_pipeTurn::flangable_items();
        break;
    }
    case CADitem::Sanitary_Shower:
    {
        flangable_items = CAD_sanitary_shower::flangable_items();
        break;
    }
    case CADitem::Sanitary_Sink:
    {
        flangable_items = CAD_sanitary_sink::flangable_items();
        break;
    }
    case CADitem::Sanitary_WashBasin:
    {
        flangable_items = CAD_sanitary_washBasin::flangable_items();
        break;
    }

    default:
        break;
    }

    deleteWdgs(ui->gridLayout);
    ui->label->setText(tr("Choose new item"));

    int buttonCount = flangable_items.count();
    int columnCount = sqrt(buttonCount);
    int column = 0;
    int row = 0;

    foreach(CADitem::ItemType type, flangable_items)
    {
        QIcon icon = itemDB->getIconByItemType(type, QSize(64, 64));
        QToolButton* button = new QToolButton(this);
        button->setMinimumSize(74, 74);
        button->setMaximumSize(74, 74);
        button->setFocusPolicy(Qt::NoFocus);
        button->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        button->setIconSize(QSize(64, 64));
        button->setIcon(icon);
        button->setProperty("ItemType", QVariant((int)type));

        connect(button, SIGNAL(clicked()), this, SLOT(slot_button_clicked()));


        ui->gridLayout->addWidget(button, row, column);
        column++;
        if (column == columnCount)
        {
            column = 0;
            row++;
        }
    }

    this->move(QCursor::pos());
    this->show();
}
