#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      controller_(controller),
      set_settings_(&Settings::GetSettings()) {
  ui->setupUi(this);
  this->resize(1100, 755);
  widget_3d = new WOpengl;
  set_settings_->ReadSettings("settings.txt");
  ui->doubleSpinBox_SizeLine->setValue(set_settings_->get_line_width());
  ui->doubleSpinBox_SizeVert->setValue(set_settings_->get_vertex_size());
  ui->comboBox_Lines->setCurrentIndex(set_settings_->get_line_type());
  ui->comboBox_Vertex->setCurrentIndex(set_settings_->get_vertex_type());
  ui->comboBox_Proection->setCurrentIndex(set_settings_->get_projection_type());
  ui->Widget->InitFacade(controller_);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_Open_clicked() {
  QString filepath =
      QFileDialog::getOpenFileName(this, tr("Выберете файл"), "/", tr("*.obj"));
  if (!filepath.isEmpty()) {
    ui->Widget->InitModel(filepath.toStdString());
    ui->Widget->count_facet = controller_->GetFacet().size();
    ui->Widget->count_vert = controller_->GetVert().size();
    if (ui->Widget->facet_coord != nullptr) {
      delete[] ui->Widget->facet_coord;
      delete[] ui->Widget->vertex_coord;
      ui->Widget->facet_coord = nullptr;
      ui->Widget->vertex_coord = nullptr;
    }
    ui->Widget->count_f = 0;
    for (size_t i = 0; i < controller_->GetFacet().size(); ++i) {
      ui->Widget->count_f += controller_->GetFacet()[i].size();
    }
  }
  QFileInfo filename(filepath);
  ui->label_filepath->setText(filename.fileName());
  ui->label_vertex->setText(QString::number(controller_->GetVert().size()));
  ui->label_edges->setText(QString::number(controller_->GetFacet().size()));
  ui->Widget->update();
}

void MainWindow::on_pushButton_rotX_clicked() {
  controller_->RotateObj(ui->doubleSpinBox_Rotate->value(), OS_X);
  ui->Widget->InitModelBuffer();
  ui->Widget->update();
}

void MainWindow::on_pushButton_rotY_clicked() {
  controller_->RotateObj(ui->doubleSpinBox_Rotate->value(), OS_Y);
  ui->Widget->InitModelBuffer();
  ui->Widget->update();
}

void MainWindow::on_pushButton_rotZ_clicked() {
  controller_->RotateObj(ui->doubleSpinBox_Rotate->value(), OS_Z);
  ui->Widget->InitModelBuffer();
  ui->Widget->update();
}

void MainWindow::on_pushButton_moveX_clicked() {
  controller_->MoveObj(ui->doubleSpinBox_Move->value(), OS_X);
  ui->Widget->InitModelBuffer();
  ui->Widget->update();
}

void MainWindow::on_pushButton_moveY_clicked() {
  controller_->MoveObj(ui->doubleSpinBox_Move->value(), OS_Y);
  ui->Widget->InitModelBuffer();
  ui->Widget->update();
}

void MainWindow::on_pushButton_moveZ_clicked() {
  controller_->MoveObj(ui->doubleSpinBox_Move->value(), OS_Z);
  ui->Widget->InitModelBuffer();
  ui->Widget->update();
}

void MainWindow::on_pushButton_sizeP_clicked() {
  controller_->ScaleObj(1.2);
  ui->Widget->InitModelBuffer();
  ui->Widget->update();
}

void MainWindow::on_pushButton_sizeM_clicked() {
  controller_->ScaleObj(0.8);
  ui->Widget->InitModelBuffer();
  ui->Widget->update();
}

void MainWindow::on_pushButton_Image_clicked() {
  QImage screenshot = ui->Widget->grabFramebuffer();
  QString saveDialog = QFileDialog::getSaveFileName(
      this, "Cохранить как", QDir::homePath(), "JPEG (*.jpeg);; BMP(*.bmp)");
  if (!saveDialog.isEmpty()) {
    screenshot.save(saveDialog);
  }
}

void MainWindow::on_pushButton_Gif_clicked() {
  QGifImage *gif = new QGifImage(QSize(640, 480));
  gif->setDefaultDelay(100);
  QTimer *time = new QTimer(this);
  time->start(100);
  while (1) {
    if (gif->frameCount() < 50) {
      QImage image;
      controller_->RotateObj(7.2, OS_Y);
      ui->Widget->update();
      image = ui->Widget->grabFramebuffer();
      image = image.scaled(640, 480, Qt::IgnoreAspectRatio,
                           Qt::SmoothTransformation);
      gif->addFrame(image);
    } else {
      QString FileName = QFileDialog::getSaveFileName(
          this, "Open a file", QDir::homePath(), "GIF (*.gif)");
      gif->save(FileName);
      time->stop();
      break;
    }
  }
}

void MainWindow::on_comboBox_Proection_currentIndexChanged(int index) {
  set_settings_->set_projection_type(index);
  ui->Widget->update();
}

void MainWindow::on_doubleSpinBox_SizeLine_valueChanged(double arg1) {
  set_settings_->set_line_width(arg1);
  ui->Widget->update();
}

void MainWindow::on_comboBox_Lines_currentIndexChanged(int index) {
  set_settings_->set_line_type(index);
  ui->Widget->update();
}

void MainWindow::on_doubleSpinBox_SizeVert_valueChanged(double arg1) {
  set_settings_->set_vertex_size(arg1);
  ui->Widget->update();
}

void MainWindow::on_comboBox_Vertex_currentIndexChanged(int index) {
  set_settings_->set_vertex_type(index);
  ui->Widget->update();
}

void MainWindow::on_pushButton_colBack_clicked() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) {
    set_settings_->set_color_back(color);
  }
  ui->Widget->update();
}

void MainWindow::on_pushButton_colLines_clicked() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) {
    set_settings_->set_color_line(color);
  }
  ui->Widget->update();
}

void MainWindow::on_pushButton_colDots_clicked() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) {
    set_settings_->set_color_points(color);
  }
  ui->Widget->update();
}

void MainWindow::on_pushButton_setTexture_clicked() {
  QString texture = QFileDialog::getOpenFileName(0, "Открыть", "", "*.bmp");
  if (!texture.isEmpty()) {
    ui->Widget->texture_flag = true;
    ui->Widget->TextureLoad(texture);
    ui->Widget->update();
  }
}

void MainWindow::on_pushButton_removeTexture_clicked() {
  ui->Widget->texture_flag = false;
  ui->Widget->update();
}

void MainWindow::on_comboBox_DisplayType_currentIndexChanged(int index) {
  set_settings_->set_display_type(index);
  ui->Widget->update();
}

void MainWindow::on_pushButton_colSurface_clicked() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) {
    set_settings_->set_color_texture(color);
  }
  ui->Widget->update();
}

void MainWindow::on_pushButton_colLight_clicked() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) {
    set_settings_->set_color_light(color);
  }
  ui->Widget->update();
}

void MainWindow::on_doubleSpinBox_PowerLight_valueChanged(double arg1) {
  set_settings_->set_light_power(arg1);
  ui->Widget->update();
}

void MainWindow::on_pushButton_Reset_clicked() {
  set_settings_->set_line_type(0);
  set_settings_->set_vertex_type(0);
  set_settings_->set_projection_type(0);
  set_settings_->set_line_width(1.0);
  set_settings_->set_light_power(0.0);
  set_settings_->set_vertex_size(0);
  set_settings_->set_display_type(0);
  set_settings_->set_color_back(Qt::white);
  set_settings_->set_color_line(Qt::black);
  set_settings_->set_color_points(Qt::black);
  set_settings_->set_color_texture(Qt::black);
  set_settings_->set_color_light(Qt::lightGray);
  ui->Widget->texture_flag = false;
  ui->Widget->update();
}

void MainWindow::on_pushButton_SaveSet_clicked() {
  QString filename = QFileDialog::getSaveFileName(
      this, "Cохранить как", QDir::homePath(), "TXT(*.txt)");
  if (!filename.isEmpty()) {
    set_settings_->SaveSetInFile(filename.toStdString());
  }
}

void MainWindow::on_pushButton_LoadSet_clicked() {
  QString filename = QFileDialog::getOpenFileName(0, "Открыть", "", "*.txt");
  if (!filename.isEmpty()) {
    set_settings_->ReadSettings(filename.toStdString());
    ui->Widget->update();
  }
}

void MainWindow::on_pushButton_lightLeft_clicked() {
  ui->Widget->light_pos_x -= 0.3;
}

void MainWindow::on_pushButton_lightRight_clicked() {
  ui->Widget->light_pos_x += 0.3;
}

void MainWindow::on_pushButton_lightUp_clicked() {
  ui->Widget->light_pos_y += 0.3;
}

void MainWindow::on_pushButton_lightDown_clicked() {
  ui->Widget->light_pos_y -= 0.3;
}

}  // namespace s21
