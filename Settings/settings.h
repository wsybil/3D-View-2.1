#ifndef SETTINGS_H
#define SETTINGS_H

#include <QColorDialog>
#include <fstream>

namespace s21 {

class Settings {
  struct SettingsStorage {
    int projection;
    int type_point;
    int type_line;
    int display_type;
    double light_power_;
    double size_point;
    double line_width;
    QColor back_;
    QColor lines_;
    QColor points_;
    QColor texture_;
    QColor light_;
  };

 public:
  Settings() {}
  ~Settings() { SaveSettings(); }
  Settings(const Settings &) = delete;
  Settings &operator=(const Settings &) = delete;
  static Settings &GetSettings() {
    static Settings instance;
    return instance;
  }

  int get_line_type() { return info_.type_line; }
  int get_vertex_type() { return info_.type_point; }
  int get_projection_type() { return info_.projection; }
  int get_display_type() { return info_.display_type; }
  float get_light_power() { return info_.light_power_; }
  float get_line_width() { return info_.line_width; }
  float get_vertex_size() { return info_.size_point; }

  QColor &get_color_back() { return info_.back_; }
  QColor &get_color_line() { return info_.lines_; }
  QColor &get_color_points() { return info_.points_; }
  QColor &get_color_texture() { return info_.texture_; }
  QColor &get_color_light() { return info_.light_; }

  void set_line_type(int line_type) { info_.type_line = line_type; }
  void set_vertex_type(int point_) { info_.type_point = point_; }
  void set_projection_type(int projection_) { info_.projection = projection_; }
  void set_line_width(float line_width_) { info_.line_width = line_width_; }
  void set_vertex_size(float size_point_) { info_.size_point = size_point_; }
  void set_display_type(int type_) { info_.display_type = type_; }
  void set_light_power(float power_) { info_.light_power_ = power_; }

  void set_color_back(QColor col_back) { info_.back_ = col_back; }
  void set_color_line(QColor col_lines_) { info_.lines_ = col_lines_; }
  void set_color_points(QColor col_points_) { info_.points_ = col_points_; }
  void set_color_texture(QColor col_texture_) { info_.texture_ = col_texture_; }
  void set_color_light(QColor col_light_) { info_.light_ = col_light_; }

  void SaveSettings();
  void ReadSettings(std::string filename);
  void SaveSetInFile(std::string filename);

 private:
  SettingsStorage info_;
};

}  // namespace s21

#endif  // SETTINGS_H
