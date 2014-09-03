#ifndef GEOMETRYDISPLAYTITLE_H
#define GEOMETRYDISPLAYTITLE_H

#include <QWidget>
#include <QVector3D>

namespace Ui {
class GeometryDisplayTitle;
}

class GeometryDisplayTitle : public QWidget
{
    Q_OBJECT

public:
    explicit GeometryDisplayTitle(QWidget *parent = 0);
    ~GeometryDisplayTitle();

private:
    Ui::GeometryDisplayTitle *ui;

public slots:
    void slot_sceneCoordinatesChanged(QVector3D coords);
};

#endif // GEOMETRYDISPLAYTITLE_H
