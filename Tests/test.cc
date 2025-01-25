#include <gtest/gtest.h>

#include "../Model/parser.h"

#define EPS 1e-5

TEST(parsing_test, get_vert_and_facet) {
  s21::Model test;

  test.LoadFile("Tests/cube.obj");
  EXPECT_EQ(test.GetVert().size(), 8);
  EXPECT_EQ(test.GetFacet().size(), 4);

  test.LoadFile("Tests/cube_2.obj");
  EXPECT_EQ(test.GetVert().size(), 8);
  EXPECT_EQ(test.GetFacet().size(), 6);

  test.LoadFile("Tests/cube_3.obj");
  EXPECT_EQ(test.model.vert_n.size(), 8);
  EXPECT_EQ(test.model.vert_t.size(), 8);
  EXPECT_EQ(test.GetFacet().size(), 24);
}

TEST(tranformation_tests, move) {
  s21::Model test;

  test.LoadFile("Tests/cube.obj");
  std::vector<std::vector<double>> cube{
      {20.5, 41.5, -63.5}, {20.5, 41.5, -62.5}, {20.5, 42.5, -63.5},
      {20.5, 42.5, -62.5}, {21.5, 41.5, -63.5}, {21.5, 41.5, -62.5},
      {21.5, 42.5, -63.5}, {21.5, 42.5, -62.5}};
  test.MoveModel(21, 0);
  test.MoveModel(42, 1);
  test.MoveModel(-63, 2);
  std::vector<std::vector<double>> test_cube = test.GetVert();
  EXPECT_EQ(test_cube, cube);

  test.LoadFile("Tests/cube_2.obj");
  std::vector<std::vector<double>> cube_up{
      {21, -41, 64}, {21, -42, 64}, {22, -42, 64}, {22, -41, 64},
      {21, -41, 63}, {21, -42, 63}, {22, -42, 63}, {22, -41, 63}};
  test.MoveModel(21, 0);
  test.MoveModel(-42, 1);
  test.MoveModel(63, 2);
  std::vector<std::vector<double>> test_cube_up = test.GetVert();
  EXPECT_EQ(test_cube_up, cube_up);
}

TEST(tranformation_tests, rotate) {
  s21::Model test;

  test.LoadFile("Tests/cube.obj");
  std::vector<std::vector<double>> cube{
      {0.375218, -0.196718, 0.755324},   {-0.0173877, 0.692358, 0.519941},
      {-0.428933, -0.652762, 0.374056},  {-0.821539, 0.236314, 0.138673},
      {0.821539, -0.236314, -0.138673},  {0.428933, 0.652762, -0.374056},
      {0.0173877, -0.692358, -0.519941}, {-0.375218, 0.196718, -0.755324}};
  test.RotateModel(45, 0);
  test.RotateModel(90, 1);
  test.RotateModel(135, 2);
  std::vector<std::vector<double>> test_cube = test.GetVert();
  for (size_t i = 0; i < test_cube.size(); ++i) {
    for (size_t j = 0; j < test_cube[i].size(); ++j) {
      EXPECT_NEAR(test_cube[i][j], cube[i][j], EPS);
    }
  }

  test.LoadFile("Tests/cube_2.obj");
  std::vector<std::vector<double>> cube_up{
      {1.31558, -0.20459, -0.476845},   {0.458777, -0.718133, -0.523267},
      {0.223394, -0.248497, -1.37417},  {1.0802, 0.265046, -1.32775},
      {0.856807, 0.513543, 0.046422},   {0, 0, 0},
      {-0.235383, 0.469636, -0.850904}, {0.621424, 0.983179, -0.804482}};
  test.RotateModel(135, 0);
  test.RotateModel(45, 1);
  test.RotateModel(90, 2);
  std::vector<std::vector<double>> test_cube_up = test.GetVert();
  for (size_t i = 0; i < test_cube_up.size(); ++i) {
    for (size_t j = 0; j < test_cube_up[i].size(); ++j) {
      EXPECT_NEAR(test_cube_up[i][j], cube_up[i][j], EPS);
    }
  }
}

TEST(tranformation_tests, scale) {
  s21::Model test;

  test.LoadFile("Tests/cube.obj");
  std::vector<std::vector<double>> cube{
      {-10.5, -10.5, -10.5}, {-10.5, -10.5, 10.5}, {-10.5, 10.5, -10.5},
      {-10.5, 10.5, 10.5},   {10.5, -10.5, -10.5}, {10.5, -10.5, 10.5},
      {10.5, 10.5, -10.5},   {10.5, 10.5, 10.5}};
  test.ScaleModel(21);
  std::vector<std::vector<double>> test_cube = test.GetVert();
  EXPECT_EQ(test_cube, cube);

  test.LoadFile("Tests/cube_2.obj");
  std::vector<std::vector<double>> cube_up{
      {0, 42, 42}, {0, 0, 42}, {42, 0, 42}, {42, 42, 42},
      {0, 42, 0},  {0, 0, 0},  {42, 0, 0},  {42, 42, 0}};
  test.ScaleModel(42);
  std::vector<std::vector<double>> test_cube_up = test.GetVert();
  EXPECT_EQ(test_cube_up, cube_up);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
