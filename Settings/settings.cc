#include "settings.h"

namespace s21 {

void Settings::ReadSettings(std::string filename = "settings.txt") {
  std::ifstream in(filename);
  std::string line;
  if (in.is_open()) {
    while (in) {
      std::string line;
      getline(in, line);
      if (line.find("line_type_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.type_line = std::stoi(substring);
      } else if (line.find("vertex_type_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.type_point = std::stoi(substring);
      } else if (line.find("projection_type_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.projection = std::stoi(substring);
      } else if (line.find("line_width_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.line_width = std::stof(substring);
      } else if (line.find("vertex_size_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.size_point = std::stof(substring);
      } else if (line.find("back_red_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.back_.setRedF(std::stof(substring));
      } else if (line.find("back_green_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.back_.setGreenF(std::stof(substring));
      } else if (line.find("back_blue_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.back_.setBlueF(std::stof(substring));
      } else if (line.find("line_red_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.lines_.setRedF(std::stof(substring));
      } else if (line.find("line_green_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.lines_.setGreenF(std::stof(substring));
      } else if (line.find("line_blue_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.lines_.setBlueF(std::stof(substring));
      } else if (line.find("vertex_red_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.points_.setRedF(std::stof(substring));
      } else if (line.find("vertex_green_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.points_.setGreenF(std::stof(substring));
      } else if (line.find("vertex_blue_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.points_.setBlueF(std::stof(substring));
      } else if (line.find("surface_red_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.texture_.setRedF(std::stof(substring));
      } else if (line.find("surface_green_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.texture_.setGreenF(std::stof(substring));
      } else if (line.find("surface_blue_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.texture_.setBlueF(std::stof(substring));
      } else if (line.find("light_red_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.light_.setRedF(std::stof(substring));
      } else if (line.find("light_green_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.light_.setGreenF(std::stof(substring));
      } else if (line.find("light_blue_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.light_.setBlueF(std::stof(substring));
      } else if (line.find("light_power_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.light_power_ = std::stoi(substring);
      } else if (line.find("display_type_") != std::string::npos) {
        std::string substring = line.substr(line.find("=") + 1);
        info_.display_type = std::stoi(substring);
      }
    }
  }
  in.close();
}

void Settings::SaveSettings() { SaveSetInFile("settings.txt"); }

void Settings::SaveSetInFile(std::string filename = "settings.txt") {
  std::ofstream out;
  out.open(filename);
  if (out.is_open()) {
    out << "line_type_=" << info_.type_line << std::endl;
    out << "vertex_type_=" << info_.type_point << std::endl;
    out << "projection_type_=" << info_.projection << std::endl;
    out << "line_width_=" << info_.line_width << std::endl;
    out << "vertex_size_=" << info_.size_point << std::endl;
    out << "back_red_=" << info_.back_.redF() << std::endl;
    out << "back_green_=" << info_.back_.greenF() << std::endl;
    out << "back_blue_=" << info_.back_.blueF() << std::endl;
    out << "line_red_=" << info_.lines_.redF() << std::endl;
    out << "line_green_=" << info_.lines_.greenF() << std::endl;
    out << "line_blue_=" << info_.lines_.blueF() << std::endl;
    out << "vertex_red_=" << info_.points_.redF() << std::endl;
    out << "vertex_green_=" << info_.points_.greenF() << std::endl;
    out << "vertex_blue_=" << info_.points_.blueF() << std::endl;
    out << "surface_red_=" << info_.texture_.redF() << std::endl;
    out << "surface_green_=" << info_.texture_.greenF() << std::endl;
    out << "surface_blue_=" << info_.texture_.blueF() << std::endl;
    out << "light_red_=" << info_.light_.redF() << std::endl;
    out << "light_green_=" << info_.light_.greenF() << std::endl;
    out << "light_blue_=" << info_.light_.blueF() << std::endl;
    out << "light_power_=" << info_.light_power_ << std::endl;
    out << "display_type_=" << info_.display_type << std::endl;
  }
}

}  // namespace s21
