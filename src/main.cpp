/* -*-c++-*- OpenSceneGraph Cookbook
* Chapter 9 Recipe 1
* Author: Wang Rui <wangray84 at gmail dot com>
*/


#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/Viewer>

#include <QtWidgets/QApplication>
#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <QVBoxLayout>

#include <osgQt/GraphicsWindowQt>

#include "CommonFunctions.h"

osgQt::GraphicsWindowQt* createGraphicsWindow(int x, int y, int w, int h)
{
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->windowDecoration = false;
    traits->x = x;
    traits->y = y;
    traits->width = w;
    traits->height = h;
    traits->doubleBuffer = true;

    return new osgQt::GraphicsWindowQt(traits.get());
}

class ViewerWidget : public QWidget
{
public:
    ViewerWidget(osgQt::GraphicsWindowQt* gw, osg::Node* scene)
        : QWidget()
    {
        const osg::GraphicsContext::Traits* traits = gw->getTraits();

        osg::Camera* camera = _viewer.getCamera();
        camera->setGraphicsContext(gw);
        camera->setClearColor(osg::Vec4(0.2, 0.2, 0.6, 1.0));
        camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
        camera->setProjectionMatrixAsPerspective(
            30.0f, static_cast<double>(traits->width) / static_cast<double>(traits->height), 1.0f, 10000.0f);

        _viewer.setSceneData(scene);
        _viewer.addEventHandler(new osgViewer::StatsHandler);
        _viewer.setCameraManipulator(new osgGA::TrackballManipulator);
        _viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);

        QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget(gw->getGLWidget());
        setLayout(layout);

        connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
        _timer.start(40);
    }

protected:
    virtual void paintEvent(QPaintEvent* event)
    {
        _viewer.frame();
    }

    osgViewer::Viewer _viewer;
    QTimer _timer;
};

int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    osgQt::GraphicsWindowQt* gw = createGraphicsWindow(50, 50, 640, 480);
    osg::Node* scene = osgDB::readNodeFile("cow.osg");

    ViewerWidget* widget = new ViewerWidget(gw, scene);
    widget->setGeometry(100, 100, 800, 600);
    widget->show();
    return app.exec();
}










//#include <iostream>
//#include <osgDB/ReadFile>
//#include <osgViewer/Viewer>
//#include <osgGA/TrackballManipulator>
//#include <osg/PositionAttitudeTransform>
//#include <osg/PolygonMode>
//#include "KeyboardEventHandler.h"
//#include <QtCore/QtCore>
//#include <QtGui/QtGui>
//#include <osgQt/GraphicsWindowQt>
//
//
//int main(int argc, char** argv)
//{
//	osg::PositionAttitudeTransform* sceneRoot = new osg::PositionAttitudeTransform();
//
//	osg::Vec3Array* lineVertices = new osg::Vec3Array();
//	osg::DrawElementsUInt* lineIndicies = new osg::DrawElementsUInt(osg::PrimitiveSet::LINES, 0);
//	osg::Vec4Array* lineColorArray = new osg::Vec4Array();
//	osg::Geometry* geometry = new osg::Geometry();
//	osg::Geode* geode = new osg::Geode();
//
//	//Use VBOs
//	geometry->setUseDisplayList(false);
//	geometry->setUseVertexBufferObjects(true);
//	geometry->setDataVariance(osg::Object::DYNAMIC);
//
//	//Define Vertex Positions
//	osg::Vec3f startPoint(0, 0, 0);
//	osg::Vec3f joint1(1, 0, 1);
//	osg::Vec3f joint2(2, 0, 2);
//	osg::Vec3f endPoint(3, 0, 1);
//
//	//Put Positions to VertexArray
//	lineVertices->push_back(startPoint);
//	lineVertices->push_back(joint1);
//	lineVertices->push_back(joint2);
//	lineVertices->push_back(endPoint);
//
//	//Create indicies for lines
//	lineIndicies->push_back(0);
//	lineIndicies->push_back(1);
//	lineIndicies->push_back(1);
//	lineIndicies->push_back(2);
//	lineIndicies->push_back(2);
//	lineIndicies->push_back(3);
//
//	lineColorArray->push_back(osg::Vec4f(1.0, 0.0, 0.0, 1.0));
//
//	geometry->setVertexArray(lineVertices);
//	geometry->setColorArray(lineColorArray);
//	geometry->addPrimitiveSet(lineIndicies);
//
//	sceneRoot->addChild(geode);
//	geode->addDrawable(geometry);
//
//	osgViewer::Viewer* viewer = new osgViewer::Viewer();
//	viewer->setSceneData(sceneRoot);
//	viewer->setCameraManipulator(new osgGA::TrackballManipulator());
//
//	float* value = new float();
//	*value = 1.0f;
//
//	KeyboardEventHandler* kbEventHandler = new KeyboardEventHandler(value);
//	viewer->addEventHandler(kbEventHandler);
//	
//	while (!viewer->done())
//	{
//		viewer->frame();
//	}
//
//	return 0;
//
//}
