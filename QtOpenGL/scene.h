#ifndef SCENE_H
#define SCENE_H



#include <QWidget>
#include <QOpenGLWidget>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>

#include <GL/glu.h>
#include <GL/gl.h>



class Scene : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit Scene(QWidget *parent = 0);
    virtual ~Scene();

    void initShaders();
    void InitializeVertexBuffer();

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(const int &width, const int &height);

private:
    QOpenGLShaderProgram program;
    GLuint positionBufferObject;
    GLint vertexLocation;
};

#endif // SCENE_H
