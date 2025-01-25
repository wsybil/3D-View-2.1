#ifndef WOPENGL_H_
#define WOPENGL_H_

#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif

#include <QBasicTimer>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QQuaternion>
#include <QWidget>
#include <QtOpenGL>

#include "Controller/controller.h"
#include "Settings/settings.h"

constexpr int FLAG_ALL = 1;
constexpr int FLAG_WITH_NORMALIES = 2;
constexpr int FLAG_WITH_TEXTURE = 3;
constexpr int FLAG_WITHOUT_ANYTHING = 4;

class WOpengl : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  explicit WOpengl(QWidget *parent = nullptr);
  void InitFacade(s21::Controller *facade);
  void InitModel(std::string path);
  void TextureLoad(QString path);

  void initShaders();
  void initTextures();
  void InitModelBuffer();
  float light_pos_x = 0.0;
  float light_pos_y = 0.0;
  int count_vert = 0;
  int count_facet = 0;
  int type_flag = 0;
  bool texture_flag = false;
  int flag_texture_mode = 0;
  GLdouble *vertex_coord = nullptr;
  GLuint *facet_coord = nullptr;
  GLint count_f = 0;
  GLint attribute_coord2;
  GLint attribute_color;
  // GLuint program;
  struct VertexData {
    VertexData() {}
    explicit VertexData(QVector3D p, QVector2D t, QVector3D n)
        : position(p), textCoord(t), normal(n) {}
    explicit VertexData(QVector3D p, QVector2D t) : position(p), textCoord(t) {}
    explicit VertexData(QVector3D p, QVector3D n) : position(p), normal(n) {}
    explicit VertexData(QVector3D p) : position(p) {}
    QVector3D position;
    QVector2D textCoord;
    QVector3D normal;
  };

 protected:
  void mousePressEvent(QMouseEvent *e) override;
  void mouseReleaseEvent(QMouseEvent *e) override;

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void BufferWithNormaliesAndTexture(const s21::Vertex &model,
                                     QVector<VertexData> &vertexes,
                                     QVector<GLuint> &indexes);
  void BufferWithNormalies(const s21::Vertex &model,
                           QVector<VertexData> &vertexes,
                           QVector<GLuint> &indexes);
  void BufferWithTexture(const s21::Vertex &model,
                         QVector<VertexData> &vertexes,
                         QVector<GLuint> &indexes);
  void BufferWithoutNormaliesAndTexture(const s21::Vertex &model,
                                        QVector<VertexData> &vertexes,
                                        QVector<GLuint> &indexes);
  void VertexAndFacetFill(const s21::Vertex &model,
                          QVector<VertexData> &vertexes,
                          QVector<GLuint> &indexes, size_t vector_count);
  void DrawVertex();
  void DrawFacet();
  int GetTypeFlag(const s21::Vertex &model);

 private:
  s21::Controller *widget_;
  s21::Settings *settings_;

  QBasicTimer timer;

  QOpenGLTexture *texture;
  QOpenGLBuffer arr_buff;
  QOpenGLBuffer index_buff;

  QMatrix4x4 projection;
  QOpenGLShaderProgram program;

  QVector2D mousePressPosition;
  QVector3D rotationAxis;
  qreal angularSpeed = 0;
  QQuaternion rotation;
};

#endif  // WOPENGL_H_
