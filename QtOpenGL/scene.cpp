#include "scene.h"

namespace data{
    float const vertexPositions[] = {
        0.75f,  0.75f, 0.0f, 1.0f,
        0.75f, -0.75f, 0.0f, 1.0f,
        -0.75f, -0.75f, 0.0f, 1.0f,
    };
}

Scene::Scene(QWidget *parent) :
    QOpenGLWidget(parent){}

Scene::~Scene(){
    glDeleteBuffers(1, &positionBufferObject);
}

void Scene::initShaders()
{
    setlocale(LC_NUMERIC, "C");

    if(!program.addShaderFromSourceFile(
                QOpenGLShader::Vertex, "../Shaders/vertexShader.vert"))
    {
        close();
    }

    if(!program.addShaderFromSourceFile(
                QOpenGLShader::Fragment, "../Shaders/fragmentShader.frag"))
    {
        close();
    }

    if (!program.link() || !program.bind())
    {
        close();
    }

    setlocale(LC_ALL, "");
}

void Scene::InitializeVertexBuffer()
{
    glGenBuffers(1, &positionBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(data::vertexPositions),
                 data::vertexPositions,
                 GL_STATIC_DRAW );
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Scene::initializeGL()
{
    initializeOpenGLFunctions();
    InitializeVertexBuffer();
    initShaders();
}

void Scene::resizeGL(const int &width, const int &height)
{
    glViewport(0,0, width, height);
}

void Scene::paintGL()
{
    glClearColor(0.13f, 0.13f, 0.13f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);

    vertexLocation = program.attributeLocation("position");
    program.enableAttributeArray(vertexLocation);

    glVertexAttribPointer(
                vertexLocation,
                4,
                GL_FLOAT,
                GL_FALSE,
                0,
                0 );

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

