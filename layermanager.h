#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <QDockWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDesktopWidget>
#include <QColorDialog>
#include <QMap>
#include <QLabel>

#include "layer.h"
#include "itemdb.h"

namespace Ui {
class LayerManager;
}

class LayerManager : public QDockWidget
{
    Q_OBJECT

public:
    explicit LayerManager(QWidget *parent, Layer *topLevelLayer, ItemDB *itemDB);
    ~LayerManager();
    void updateAllLayers();
    void updateLayer(Layer* layer);
    Layer* getCurrentLayer();

private:
    Ui::LayerManager *ui;
    ItemDB* itemDB;
    Layer* topLevelLayer;
    Layer* currentLayer;
    QMap<Layer*, QTreeWidgetItem*> layerMap;

    QPixmap icon_layerOn;
    QPixmap icon_layerOff;
    QPixmap icon_pencilOn;
    QPixmap icon_pencilOff;

public slots:
    void slot_layerAdded(Layer* newLayer, Layer* parentLayer);
private slots:
    void on_treeWidget_layer_itemClicked(QTreeWidgetItem *item, int column);

    void on_treeWidget_layer_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

signals:
    void signal_repaintNeeded();
};

#endif // LAYERMANAGER_H
