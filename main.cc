#include <QApplication>

#include "View/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model model;
  s21::Controller controller(&model);
  s21::MainWindow w(&controller);
  w.setWindowTitle("3D Viewer");
  w.setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
  w.show();
  return a.exec();
}
