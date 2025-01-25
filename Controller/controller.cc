#include "controller.h"

namespace s21 {

void Controller::LoadFileName(const std::string filename) {
  model_->LoadFile(filename);
}

void Controller::MoveObj(double distance, int axis) {
  model_->MoveModel(distance, axis);
}

void Controller::RotateObj(double angle, int axis) {
  model_->RotateModel(angle, axis);
}

void Controller::ScaleObj(double multiplier) { model_->ScaleModel(multiplier); }

std::vector<std::vector<double>> &Controller::GetVert() {
  return model_->GetVert();
}

std::vector<std::vector<int>> &Controller::GetFacet() {
  return model_->GetFacet();
}

Vertex Controller::GetModel() { return model_->GetModel(); }

}  // namespace s21
