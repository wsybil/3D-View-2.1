#include "parser.h"

#include <iostream>
#include <string>

namespace s21 {

// parsing
void Model::LoadFile(const std::string filename) {
  ModelFree();
  std::string StrTmp;
  std::ifstream file;
  file.open(filename);
  while (getline(file, StrTmp)) {
    while (StrTmp == "") getline(file, StrTmp);
    if (StrTmp.at(0) == 'v' && StrTmp.at(1) == ' ') {
      VertexRecord(StrTmp);
    } else if (StrTmp.at(0) == 'f') {
      FacetRecord(StrTmp);
    } else if (StrTmp.at(0) == 'v' && StrTmp.at(1) == 'n') {
      VertexNRecord(StrTmp);
    } else if (StrTmp.at(0) == 'v' && StrTmp.at(1) == 't') {
      VertexTRecord(StrTmp);
    }
  }
}

void Model::VertexRecord(std::string str) {
  std::vector<double> VectTmp;
  std::string::size_type count = 0;
  while (str.begin() != str.end()) {
    if (CheckString(str)) {
      VectTmp.push_back(std::stod(str, &count));
      str.erase(0, count);
      while (str.begin() != str.end() && str.at(0) != ' ') str.erase(0, 1);
    } else {
      str.erase(0, 1);
    }
  }
  model.vert.push_back(VectTmp);
}

bool Model::CheckString(const std::string str) {
  return (str.at(0) >= '0' && str.at(0) <= '9' && str.at(0) != ' ' &&
          str.at(0) != '\r') ||
         str.at(0) == '-';
}

void Model::VertexNRecord(std::string str) {
  std::vector<double> VectTmp;
  std::string::size_type count = 0;
  while (str.begin() != str.end()) {
    if (CheckString(str)) {
      VectTmp.push_back(std::stod(str, &count));
      str.erase(0, count);
      while (str.begin() != str.end() && str.at(0) != ' ') str.erase(0, 1);
    } else {
      str.erase(0, 1);
    }
  }
  model.vert_n.push_back(VectTmp);
}

void Model::VertexTRecord(std::string str) {
  std::vector<double> VectTmp;
  std::string::size_type count = 0;
  while (str.begin() != str.end()) {
    if (CheckString(str)) {
      VectTmp.push_back(std::stod(str, &count));
      str.erase(0, count);
      while (str.begin() != str.end() && str.at(0) != ' ') str.erase(0, 1);
    } else {
      str.erase(0, 1);
    }
  }
  model.vert_t.push_back(VectTmp);
}

void Model::FacetRecord(std::string str) {
  std::vector<int> VectTmp;
  std::string::size_type count = 0;
  while (str.begin() != str.end()) {
    if (CheckString(str)) {
      VectTmp.push_back(std::stod(str, &count));
      str.erase(0, count);
      while (str.begin() != str.end() && str.at(0) != ' ') {
        if (str.at(0) == '/') {
          str.erase(0, 1);
          break;
        }
        str.erase(0, 1);
      }
    } else {
      str.erase(0, 1);
    }
  }
  if (VectTmp.size() == 4 || VectTmp.size() == 8 || VectTmp.size() == 12)
    model.quads_count++;
  else
    model.triangles_count++;
  model.facet.push_back(VectTmp);
}

void Model::ModelFree() {
  model.facet.clear();
  model.vert.clear();
  model.vert_n.clear();
  model.vert_t.clear();
  model.quads_count = 0;
  model.triangles_count = 0;
}

// affin
void Model::MoveModel(double distance, int os) {
  for (size_t i = 0; i < model.vert.size(); i++) {
    model.vert[i][os] += distance;
  }
}

void Model::RotateModel(double angle, int os) {
  for (size_t i = 0; i < model.vert.size(); i++) {
    switch (os) {
      case OS_X: {
        double tmp_a = model.vert[i][OS_Y];
        double tmp_b = model.vert[i][OS_Z];
        model.vert[i][OS_Y] = cos(angle) * tmp_a - sin(angle) * tmp_b;
        model.vert[i][OS_Z] = sin(angle) * tmp_a + cos(angle) * tmp_b;
        break;
      }
      case OS_Y: {
        double tmp_a = model.vert[i][OS_X];
        double tmp_b = model.vert[i][OS_Z];
        model.vert[i][OS_X] = cos(angle) * tmp_a + sin(angle) * tmp_b;
        model.vert[i][OS_Z] = -sin(angle) * tmp_a + cos(angle) * tmp_b;
        break;
      }
      case OS_Z: {
        double tmp_a = model.vert[i][OS_X];
        double tmp_b = model.vert[i][OS_Y];
        model.vert[i][OS_X] = cos(angle) * tmp_a - sin(angle) * tmp_b;
        model.vert[i][OS_Y] = sin(angle) * tmp_a + cos(angle) * tmp_b;
        break;
      }
      default:
        break;
    }
  }
}

void Model::ScaleModel(double multiplier) {
  for (size_t i = 0; i < model.vert.size(); i++) {
    for (int j = 0; j < 3; j++) model.vert[i][j] *= multiplier;
  }
}

Vertex Model::GetModel() { return model; }

}  // namespace s21
