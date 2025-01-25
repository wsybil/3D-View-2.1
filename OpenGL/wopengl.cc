#include "wopengl.h"

#include <QMouseEvent>
#include <cmath>
#include <iostream>

WOpengl::WOpengl(QWidget *parent)
    : QOpenGLWidget(parent),
      widget_(nullptr),
      settings_(&s21::Settings::GetSettings()),
      texture(0),
      index_buff(QOpenGLBuffer::IndexBuffer) {}

void WOpengl::InitModel(std::string path) {
  widget_->LoadFileName(path);
  InitModelBuffer();
}

int WOpengl::GetTypeFlag(const s21::Vertex &model) {
  if (!model.vert_n.size() && !model.vert_t.size()) {
    return FLAG_WITHOUT_ANYTHING;
  } else if (!model.vert_n.size() && model.vert_t.size()) {
    return FLAG_WITH_TEXTURE;
  } else if (model.vert_n.size() && !model.vert_t.size()) {
    return FLAG_WITH_NORMALIES;
  } else if (model.vert_n.size() && model.vert_t.size()) {
    return FLAG_ALL;
  }
  return 0;
}

void WOpengl::InitFacade(s21::Controller *facade) { widget_ = facade; }

void WOpengl::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  initShaders();
}

void WOpengl::initShaders() {
  if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.vsh"))
    close();
  if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                       ":/fshader.fsh"))
    close();
  if (!program.link()) close();
}

void WOpengl::resizeGL(int w, int h) {
  float aspect = w / (float)h;
  projection.setToIdentity();
  projection.perspective(45, aspect, 0.1f, 10.0f);
}

void WOpengl::InitModelBuffer() {
  QVector<VertexData> vertexes;
  QVector<GLuint> indexes;
  s21::Vertex model = widget_->GetModel();
  size_t vector_count = 3;
  if (GetTypeFlag(model) == FLAG_ALL)
    BufferWithNormaliesAndTexture(model, vertexes, indexes);
  else if (GetTypeFlag(model) == FLAG_WITH_NORMALIES) {
    vector_count = 2;
    BufferWithNormalies(model, vertexes, indexes);
  } else if (GetTypeFlag(model) == FLAG_WITH_TEXTURE) {
    BufferWithTexture(model, vertexes, indexes);
    vector_count = 2;
  } else if (GetTypeFlag(model) == FLAG_WITHOUT_ANYTHING) {
    BufferWithoutNormaliesAndTexture(model, vertexes, indexes);
    vector_count = 1;
  }
  VertexAndFacetFill(model, vertexes, indexes,
                     vector_count);  // подгружаются точки и ребра через буфферы
  arr_buff.destroy();
  arr_buff.create();
  arr_buff.bind();
  arr_buff.allocate(vertexes.constData(), vertexes.size() * sizeof(VertexData));
  arr_buff.release();
  index_buff.destroy();
  index_buff.create();
  index_buff.bind();
  index_buff.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
  index_buff.release();
}

void WOpengl::BufferWithNormaliesAndTexture(const s21::Vertex &model,
                                            QVector<VertexData> &vertexes,
                                            QVector<GLuint> &indexes) {
  for (size_t i = 0; i < model.facet.size();
       i++) {  // подгружаются в нужном порядке вектора для отрисовкой квадратом
    for (size_t j = 0; j < model.facet[i].size() && model.facet[i].size() == 12;
         j += 3) {
      vertexes.append(
          VertexData(QVector3D(model.vert[model.facet[i][j] - 1][0],
                               model.vert[model.facet[i][j] - 1][1],
                               model.vert[model.facet[i][j] - 1][2]),
                     QVector2D(model.vert_t[model.facet[i][j + 1] - 1][0],
                               model.vert_t[model.facet[i][j + 1] - 1][1]),
                     QVector3D(model.vert_n[model.facet[i][j + 2] - 1][0],
                               model.vert_n[model.facet[i][j + 2] - 1][1],
                               model.vert_n[model.facet[i][j + 2] - 1][2])));
      indexes.append(indexes.size());
    }
  }
  for (size_t i = 0; i < model.facet.size();
       i++) {  // подгружаются в нужном порядке вектора для отрисовкой
               // треугольником
    for (size_t j = 0; j < model.facet[i].size() && model.facet[i].size() == 9;
         j += 3) {
      vertexes.append(
          VertexData(QVector3D(model.vert[model.facet[i][j] - 1][0],
                               model.vert[model.facet[i][j] - 1][1],
                               model.vert[model.facet[i][j] - 1][2]),
                     QVector2D(model.vert_t[model.facet[i][j + 1] - 1][0],
                               model.vert_t[model.facet[i][j + 1] - 1][1]),
                     QVector3D(model.vert_n[model.facet[i][j + 2] - 1][0],
                               model.vert_n[model.facet[i][j + 2] - 1][1],
                               model.vert_n[model.facet[i][j + 2] - 1][2])));
      indexes.append(indexes.size());
    }
  }
}

void WOpengl::BufferWithNormalies(const s21::Vertex &model,
                                  QVector<VertexData> &vertexes,
                                  QVector<GLuint> &indexes) {
  for (size_t i = 0; i < model.facet.size();
       i++) {  // подгружаются в нужном порядке вектора для отрисовкой квадратом
    for (size_t j = 0; j < model.facet[i].size() && model.facet[i].size() == 8;
         j += 2) {
      vertexes.append(
          VertexData(QVector3D(model.vert[model.facet[i][j] - 1][0],
                               model.vert[model.facet[i][j] - 1][1],
                               model.vert[model.facet[i][j] - 1][2]),
                     QVector3D(model.vert_n[model.facet[i][j + 1] - 1][0],
                               model.vert_n[model.facet[i][j + 1] - 1][1],
                               model.vert_n[model.facet[i][j + 1] - 1][2])));
      indexes.append(indexes.size());
    }
  }
  for (size_t i = 0; i < model.facet.size();
       i++) {  // подгружаются в нужном порядке вектора для отрисовкой
               // треугольником
    for (size_t j = 0; j < model.facet[i].size() && model.facet[i].size() == 6;
         j += 2) {
      vertexes.append(
          VertexData(QVector3D(model.vert[model.facet[i][j] - 1][0],
                               model.vert[model.facet[i][j] - 1][1],
                               model.vert[model.facet[i][j] - 1][2]),
                     QVector3D(model.vert_n[model.facet[i][j + 1] - 1][0],
                               model.vert_n[model.facet[i][j + 1] - 1][1],
                               model.vert_n[model.facet[i][j + 1] - 1][2])));
      indexes.append(indexes.size());
    }
  }
}

void WOpengl::BufferWithTexture(const s21::Vertex &model,
                                QVector<VertexData> &vertexes,
                                QVector<GLuint> &indexes) {
  for (size_t i = 0; i < model.facet.size();
       i++) {  // подгружаются в нужном порядке вектора для отрисовкой квадратом
    for (size_t j = 0; j < model.facet[i].size() && model.facet[i].size() == 8;
         j += 2) {
      vertexes.append(
          VertexData(QVector3D(model.vert[model.facet[i][j] - 1][0],
                               model.vert[model.facet[i][j] - 1][1],
                               model.vert[model.facet[i][j] - 1][2]),
                     QVector2D(model.vert_t[model.facet[i][j + 1] - 1][0],
                               model.vert_t[model.facet[i][j + 1] - 1][1])));
      indexes.append(indexes.size());
    }
  }
  // triangles
  for (size_t i = 0; i < model.facet.size();
       i++) {  // подгружаются в нужном порядке вектора для отрисовкой
               // треугольником
    for (size_t j = 0; j < model.facet[i].size() && model.facet[i].size() == 6;
         j += 2) {
      vertexes.append(
          VertexData(QVector3D(model.vert[model.facet[i][j] - 1][0],
                               model.vert[model.facet[i][j] - 1][1],
                               model.vert[model.facet[i][j] - 1][2]),
                     QVector2D(model.vert_t[model.facet[i][j + 1] - 1][0],
                               model.vert_t[model.facet[i][j + 1] - 1][1])));
      indexes.append(indexes.size());
    }
  }
}

void WOpengl::BufferWithoutNormaliesAndTexture(const s21::Vertex &model,
                                               QVector<VertexData> &vertexes,
                                               QVector<GLuint> &indexes) {
  for (size_t i = 0; i < model.facet.size();
       i++) {  // подгружаются в нужном порядке вектора для отрисовкой квадратом
    for (size_t j = 0; j < model.facet[i].size() && model.facet[i].size() == 4;
         j++) {
      vertexes.append(
          VertexData(QVector3D(model.vert[model.facet[i][j] - 1][0],
                               model.vert[model.facet[i][j] - 1][1],
                               model.vert[model.facet[i][j] - 1][2])));
      indexes.append(indexes.size());
    }
  }
  for (size_t i = 0; i < model.facet.size();
       i++) {  // подгружаются в нужном порядке вектора для отрисовкой
               // треугольником
    for (size_t j = 0; j < model.facet[i].size() && model.facet[i].size() == 3;
         j++) {
      vertexes.append(
          VertexData(QVector3D(model.vert[model.facet[i][j] - 1][0],
                               model.vert[model.facet[i][j] - 1][1],
                               model.vert[model.facet[i][j] - 1][2])));
      indexes.append(indexes.size());
    }
  }
}

void WOpengl::VertexAndFacetFill(const s21::Vertex &model,
                                 QVector<VertexData> &vertexes,
                                 QVector<GLuint> &indexes,
                                 size_t vector_count) {
  for (size_t i = 0; i < model.vert.size(); i++) {  // грузим точки
    vertexes.append(VertexData(
        QVector3D(model.vert[i][0], model.vert[i][1], model.vert[i][2])));
    indexes.append(indexes.size());
  }
  for (size_t i = 0; i < model.facet.size(); i++) {  // грузим ребра
    for (size_t j = 0; j < model.facet[i].size(); j += vector_count) {
      vertexes.append(
          VertexData(QVector3D(model.vert[model.facet[i][j] - 1][0],
                               model.vert[model.facet[i][j] - 1][1],
                               model.vert[model.facet[i][j] - 1][2])));
      indexes.append(indexes.size());
      if (j) {
        vertexes.append(
            VertexData(QVector3D(model.vert[model.facet[i][j] - 1][0],
                                 model.vert[model.facet[i][j] - 1][1],
                                 model.vert[model.facet[i][j] - 1][2])));
        indexes.append(indexes.size());
      }
    }
    vertexes.append(
        VertexData(QVector3D(model.vert[model.facet[i][0] - 1][0],
                             model.vert[model.facet[i][0] - 1][1],
                             model.vert[model.facet[i][0] - 1][2])));
    indexes.append(indexes.size());
  }
}

void WOpengl::paintGL() {
  glClearColor(settings_->get_color_back().redF(),
               settings_->get_color_back().greenF(),
               settings_->get_color_back().blueF(),
               settings_->get_color_back().alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  QMatrix4x4 modelView;
  QMatrix4x4 ViewMatrix;
  modelView.setToIdentity();
  ViewMatrix.setToIdentity();
  ViewMatrix.translate(0.0, 0.0, -5.0);
  if (settings_->get_projection_type() == 0)
    ViewMatrix.ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);  // тип проекции
  ViewMatrix.rotate(rotation);
  if (texture_flag == true) texture->bind(0);
  program.bind();
  program.setUniformValue("flag_texture",
                          texture_flag);  // есть ли текстура или нет
  program.setUniformValue("flag_type",
                          settings_->get_display_type());  // тип отображения
  program.setUniformValue("u_projection_matrix",
                          projection);  // задаем матрицу проекции
  program.setUniformValue("u_view_matrix",
                          ViewMatrix);  // задаем видовую матрицу
  program.setUniformValue("u_model_matrix",
                          modelView);  // задаем модельную матрицу
  program.setUniformValue("u_texture",
                          0);  // базовая штука для текстур, вроде как на
                               // нолевом номере начинаем текстурировать
  program.setUniformValue("u_light_position",
                          QVector4D(light_pos_x, light_pos_y, 0.0,
                                    1.0));  // позиция источника света
  program.setUniformValue("u_light_power",
                          settings_->get_light_power());  // сила света
  program.setUniformValue("u_light_color", settings_->get_color_light().redF(),
                          settings_->get_color_light().greenF(),
                          settings_->get_color_light().blueF(),
                          settings_->get_color_light().alphaF());  // цвет света
  arr_buff.bind();
  int offset = 0;
  int vert_loc = program.attributeLocation("a_position");
  program.enableAttributeArray(vert_loc);
  program.setAttributeBuffer(vert_loc, GL_FLOAT, offset, 3, sizeof(VertexData));
  offset += sizeof(QVector3D);
  int text_loc = program.attributeLocation("a_texcoord");
  program.enableAttributeArray(text_loc);
  program.setAttributeBuffer(text_loc, GL_FLOAT, offset, 2, sizeof(VertexData));
  offset += sizeof(QVector2D);
  int norm_loc = program.attributeLocation("a_normal");
  program.enableAttributeArray(norm_loc);
  program.setAttributeBuffer(norm_loc, GL_FLOAT, offset, 3, sizeof(VertexData));
  index_buff.bind();
  if (settings_->get_display_type()) {
    program.setUniformValue(
        "u_base_color", QVector4D(settings_->get_color_texture().redF(),
                                  settings_->get_color_texture().greenF(),
                                  settings_->get_color_texture().blueF(), 1.0));
    glDrawElements(GL_QUADS, widget_->GetModel().quads_count * 4,
                   GL_UNSIGNED_INT,
                   0);  // отрисовка квадратами
    glDrawElements(
        GL_TRIANGLES, widget_->GetModel().triangles_count * 3, GL_UNSIGNED_INT,
        (GLvoid *)(sizeof(GLubyte) * (widget_->GetModel().quads_count *
                                      16)));  // отрисовка треугольниками
  }
  DrawVertex();
  DrawFacet();
}

void WOpengl::DrawVertex() {  // рисуем вершины
  if (settings_->get_vertex_type() != 0) {
    // размер вершин
    glPointSize(settings_->get_vertex_size());
    // тип вершин
    if (settings_->get_vertex_type() == 1) {
      glDisable(GL_TRIANGLE_STRIP);
      glEnable(GL_POINT_SMOOTH);
    } else if (settings_->get_vertex_type() == 2) {
      glDisable(GL_POINT_SMOOTH);
      glEnable(GL_TRIANGLE_STRIP);
    }
    program.setUniformValue(
        "u_base_color",
        QVector4D(settings_->get_color_points().redF(),
                  settings_->get_color_points().greenF(),
                  settings_->get_color_points().blueF(), 1.0));  // цвет вершин
    glDrawElements(
        GL_POINTS, count_vert, GL_UNSIGNED_INT,
        (GLvoid *)(sizeof(GLubyte) * ((widget_->GetModel().quads_count * 16) +
                                      (widget_->GetModel().triangles_count *
                                       12))));  // отрисовка вершин
  }
}

void WOpengl::DrawFacet() {  // рисуем ребра
  if (settings_->get_line_type()) {
    // задаем ширину линий
    glLineWidth(settings_->get_line_width());
    // тип линий
    if (settings_->get_line_type() == 2) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(1, 0x00F0);
    } else if (settings_->get_line_type() == 1) {
      glDisable(GL_LINE_STIPPLE);
    }
    program.setUniformValue(
        "u_base_color",
        QVector4D(settings_->get_color_line().redF(),
                  settings_->get_color_line().greenF(),
                  settings_->get_color_line().blueF(), 1.0));  // цвет граней
    glDrawElements(
        GL_LINES, count_f, GL_UNSIGNED_INT,
        (GLvoid *)(sizeof(GLubyte) *
                   ((count_vert * 4) + (widget_->GetModel().quads_count * 16) +
                    (widget_->GetModel().triangles_count *
                     12))));  // отрисовка граней
  }
}

void WOpengl::TextureLoad(QString path) {
  texture = new QOpenGLTexture(QImage(path).mirrored());  // задали техтуру
  texture->setMinificationFilter(QOpenGLTexture::Nearest);
  texture->setMagnificationFilter(QOpenGLTexture::Linear);
  texture->setWrapMode(QOpenGLTexture::Repeat);
}

void WOpengl::mousePressEvent(QMouseEvent *e) {
  mousePressPosition = QVector2D(e->position());
}

void WOpengl::mouseReleaseEvent(QMouseEvent *e) {
  QVector2D diff = QVector2D(e->position()) - mousePressPosition;
  float angle = diff.length() / 2.0;
  QVector3D axis = QVector3D(diff.y(), diff.x(), 0.0);
  rotation = QQuaternion::fromAxisAndAngle(axis, angle) * rotation;
  update();
}
