#include "dialog.h"
#include "ui_dialog.h"

#include "celestialbody.h"
#include "universe.h"

#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    theUniverse = new Universe(scene);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    scaleFactor = INITIAL_SCALE;
    ui->graphicsView->scale(scaleFactor, scaleFactor);
//    scene->setSceneRect(- MARGIN_X ,- MARGIN_Y, 2.0 * MARGIN_X + DISTANCE_EARTH_MOON, 2.0 * MARGIN_Y);
    scene->setSceneRect(- ( DISTANCE_SUN_EARTH + MARGIN_X ), - ( DISTANCE_SUN_EARTH + MARGIN_X ),
                        2.0 * ( DISTANCE_SUN_EARTH + MARGIN_X ), 2.0 * ( DISTANCE_SUN_EARTH + MARGIN_X ) );

/*
    InertialSystem *earthSystem = new InertialSystem(POSITION_X_EARTH, POSITION_Y_EARTH,
                                                     ANGULAR_VELOCITY_EARTH * 360.0 / 2.0 / PI, TIME_STEP, TIME_LAPSE);
*/
    CelestialBody *sun = new CelestialBody("Sun", MASS_SUN, RADIUS_SUN,
                                           POSITION_X_SUN, POSITION_Y_SUN, VELOCITY_X_SUN, VELOCITY_Y_SUN,
                                           Qt::darkYellow, 10.0, TIME_STEP, TIME_LAPSE);
    CelestialBody *earth = new CelestialBody("Earth", MASS_EARTH, RADIUS_EARTH,
                                             POSITION_X_EARTH, POSITION_Y_EARTH, VELOCITY_X_EARTH, VELOCITY_Y_EARTH,
                                             Qt::blue, 10.0, TIME_STEP, TIME_LAPSE);
    CelestialBody *moon = new CelestialBody("Moon", MASS_MOON, RADIUS_MOON,
                                            POSITION_X_MOON, POSITION_Y_MOON, VELOCITY_X_MOON, VELOCITY_Y_MOON,
                                            Qt::darkGray, 10.0, TIME_STEP, TIME_LAPSE);
//    earthSystem->addToGroup(earth);
/*
    QPen pen(Qt::black);
    scene->addLine(- POSITION_X_EARTH, 0.0, POSITION_X_EARTH, 0.0, pen);
    scene->addLine(0.0, - POSITION_X_EARTH, 0.0, POSITION_X_EARTH);
*/
    scene->addItem(sun);
//    scene->addItem(origin);
    //    scene->addItem(earthSystem);
    scene->addItem(earth);
    scene->addItem(moon);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), theUniverse, SLOT(advance()));
    timer->start(TIME_STEP);

    connect(ui->buttonZoomIn, SIGNAL(clicked()), this, SLOT(zoomIn()));
    connect(ui->buttonZoomOut, SIGNAL(clicked()), this, SLOT(zoomOut()));
    qDebug() << "application initialized";
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::zoomIn()
{
    scaleFactor *= 2.0;
    ui->graphicsView->scale(2.0, 2.0);
    qDebug() << "scale is " << scaleFactor;
}

void Dialog::zoomOut()
{
    scaleFactor *= 0.5;
    ui->graphicsView->scale(0.5, 0.5);
    qDebug() << "scale is " << scaleFactor;
}

