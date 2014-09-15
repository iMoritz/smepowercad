#include "itemwizard.h"
#include "ui_itemwizard.h"

ItemWizard::ItemWizard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemWizard)
{
    ui->setupUi(this);
}

ItemWizard::~ItemWizard()
{
    delete ui;
}

void ItemWizard::showWizard(CADitem *item)
{
    currentItem = item;
    QMap<QString, QVariant>::iterator it;
    for (it = item->wizardParams.begin(); it != item->wizardParams.end(); it++)
    {
        QWidget *wdg;
        switch (it.value().type())
        {
        case QVariant::String:
            wdg = new QLineEdit(it.value().toString(), this);
            break;
        case QVariant::Int:
            wdg = new QSpinBox(this);
            ((QSpinBox*)wdg)->setValue(it.value().toInt());
            break;
        case QVariant::Double:
            wdg = new QDoubleSpinBox(this);
            ((QDoubleSpinBox*)wdg)->setValue(it.value().toDouble());
            break;
        }


        ui->formLayout->addRow(it.key(), wdg);
    }

    this->show();
}

void ItemWizard::on_buttonBox_accepted()
{
}

void ItemWizard::on_buttonBox_rejected()
{

}

void ItemWizard::save()
{
    for (int r = 0; r < ui->formLayout->rowCount(); r++)
    {
        ui->formLayout->itemAt(r, QFormLayout::FieldRole);
    }


    //currentItem->wizardParams = ;
}
