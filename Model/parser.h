#ifndef PARSER_H
#define PARSER_H

#include <algorithm>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>

#define OS_X 0
#define OS_Y 1
#define OS_Z 2

namespace s21 {
class Vertex {
 public:
  Vertex() {}
  std::vector<std::vector<double>> vert;
  std::vector<std::vector<double>> vert_n;
  std::vector<std::vector<double>> vert_t;
  std::vector<std::vector<int>> facet;
  int quads_count = 0;
  int triangles_count = 0;
};

class Model {
 public:
  Vertex model;
  Model() {}
  ~Model() {}
  void LoadFile(std::string filename);
  void MoveModel(double distance, int os);
  void RotateModel(double angle, int os);
  void ScaleModel(double multiplier);
  std::vector<std::vector<double>> &GetVert() { return model.vert; }
  std::vector<std::vector<int>> &GetFacet() { return model.facet; }
  int GetVertex() { return model.vert.size(); }
  int GetFacets() { return model.facet.size(); }
  Vertex GetModel();

 private:
  void VertexRecord(std::string str);
  void VertexNRecord(std::string str);
  void VertexTRecord(std::string str);
  bool CheckString(const std::string str);
  void FacetRecord(std::string str);
  void ModelFree();
};

}  // namespace s21

#endif  // PARSER_H
