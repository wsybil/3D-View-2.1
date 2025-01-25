#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QTimer>

#include "Controller/controller.h"
#include "OpenGL/wopengl.h"
#include "QtGifImage/src/gifimage/qgifimage.h"
#include "Settings/settings.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(Controller *controller, QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pushButton_Open_clicked();
  void on_pushButton_rotX_clicked();
  void on_pushButton_rotY_clicked();
  void on_pushButton_rotZ_clicked();
  void on_pushButton_moveX_clicked();
  void on_pushButton_moveY_clicked();
  void on_pushButton_moveZ_clicked();
  void on_pushButton_sizeP_clicked();
  void on_pushButton_sizeM_clicked();
  void on_comboBox_Proection_currentIndexChanged(int index);
  void on_doubleSpinBox_SizeLine_valueChanged(double arg1);
  void on_comboBox_Lines_currentIndexChanged(int index);
  void on_doubleSpinBox_SizeVert_valueChanged(double arg1);
  void on_comboBox_Vertex_currentIndexChanged(int index);
  void on_pushButton_colBack_clicked();
  void on_pushButton_colLines_clicked();
  void on_pushButton_colDots_clicked();
  void on_pushButton_Gif_clicked();
  void on_pushButton_Image_clicked();
  void on_pushButton_setTexture_clicked();
  void on_pushButton_removeTexture_clicked();
  void on_comboBox_DisplayType_currentIndexChanged(int index);
  void on_pushButton_colSurface_clicked();
  void on_pushButton_colLight_clicked();
  void on_doubleSpinBox_PowerLight_valueChanged(double arg1);
  void on_pushButton_Reset_clicked();
  void on_pushButton_SaveSet_clicked();
  void on_pushButton_LoadSet_clicked();
  void on_pushButton_lightLeft_clicked();
  void on_pushButton_lightRight_clicked();
  void on_pushButton_lightUp_clicked();
  void on_pushButton_lightDown_clicked();

 private:
  Ui::MainWindow *ui;
  Controller *controller_;
  WOpengl *widget_3d;
  Settings *set_settings_;
  QPoint mPos_;
  float xRot = 0, yRot = 0;
  GLdouble *vertex_coord_ = nullptr;
  GLuint *facet_coord_ = nullptr;
};

}  // namespace s21

#endif  // MAINWINDOW_H
