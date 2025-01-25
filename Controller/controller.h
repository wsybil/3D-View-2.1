#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

#include <QMainWindow>

#include "Model/parser.h"

namespace s21 {

class Controller {
 public:
  explicit Controller(Model *model) : model_(model) {}
  ~Controller() = default;

  void LoadFileName(const std::string filename);
  void MoveObj(double distance, int axis);
  void RotateObj(double angle, int axis);
  void ScaleObj(double multiplier);
  std::vector<std::vector<int>> &GetFacet();
  std::vector<std::vector<double>> &GetVert();
  unsigned int *FacetToArr(unsigned int *arr);
  double *VertToArr(double *arr);
  Vertex GetModel();

 private:
  Model *model_;
};

}  // namespace s21

#endif  // SRC_CONTROLLER_H_
