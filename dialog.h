#ifndef DIALOG_H
#define DIALOG_H

#define MARGIN_X 15.0e6             // km
#define MARGIN_Y 15.0e6             // km
#define INITIAL_SCALE 2.0e-6        // pixel / km
// #define TIME_STEP 10.0
#define TIME_STEP 500.0
#define TIME_LAPSE 1000.0
// #define TIME_LAPSE 1.0

#include <QDialog>
#include <QtGui>
#include <QtCore>
#include <QGraphicsScene>

#include "universe.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    Universe *theUniverse;
    QGraphicsScene *scene;
    QTimer *timer;
    qreal scaleFactor;

public slots:
    void zoomIn();
    void zoomOut();
};
#endif // DIALOG_H
