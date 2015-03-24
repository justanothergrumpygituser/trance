#ifndef TRANCE_VISUAL_H
#define TRANCE_VISUAL_H

#include <cstddef>
#include "theme.h"

class Director;

// Interface to an object which can render and control the visual state.
// These visuals are swapped out by the Director every so often for different
// styles.
class Visual {
public:

  Visual(Director& director);
  virtual ~Visual() {}

  virtual void update() = 0;
  virtual void render() const = 0;

protected:

  const Director& director() const;
  Director& director();

private:

  Director& _director;

};

class AccelerateVisual : public Visual {
public:

  AccelerateVisual(Director& director, bool start_fast);
  void update() override;
  void render() const override;

private:

  static const unsigned int max_speed = 48;
  static const unsigned int min_speed = 0;
  static const unsigned int text_time = 4;

  Image _current;
  std::string _current_text;

  bool _text_on;
  unsigned int _change_timer;
  unsigned int _change_speed;
  unsigned int _change_speed_timer;
  unsigned int _text_timer;
  bool _change_faster;

};

class SubTextVisual : public Visual {
public:

  SubTextVisual(Director& director);
  void update() override;
  void render() const override;

private:

  static const unsigned int speed = 48;
  static const unsigned int sub_speed = 12;
  static const unsigned int cycles = 32;

  Image _current;
  std::string _current_text;
  bool _text_on;
  unsigned int _change_timer;
  unsigned int _sub_timer;
  unsigned int _cycle;
  unsigned int _sub_speed_multiplier;

};

class SlowFlashVisual : public Visual {
public:

  SlowFlashVisual(Director& director);
  void update() override;
  void render() const override;

private:

  static const unsigned int max_speed = 64;
  static const unsigned int min_speed = 4;
  static const unsigned int cycle_length = 16;
  static const unsigned int set_length = 4;

  Image _current;
  std::string _current_text;
  unsigned int _change_timer;

  bool _flash;
  unsigned int _image_count;
  unsigned int _cycle_count;

};

class FlashTextVisual : public Visual {
public:

  FlashTextVisual(Director& director);
  void update() override;
  void render() const override;

private:

  static const unsigned int length = 64;
  static const unsigned int font_length = 64;
  static const unsigned int cycles = 8;

  bool _animated;
  Image _start;
  Image _end;
  std::string _current_text;
  unsigned int _timer;
  unsigned int _cycle;
  unsigned int _font_timer;

};

class ParallelVisual : public Visual {
public:

  ParallelVisual(Director& director);
  void update() override;
  void render() const override;

private:

  static const unsigned int length = 32;
  static const unsigned int cycles = 64;

  Image _image;
  Image _alternate;
  unsigned int _anim_cycle;
  unsigned int _alternate_anim_cycle;
  unsigned int _length;
  unsigned int _alternate_length;
  bool _switch_alt;
  bool _text_on;
  std::string _current_text;
  unsigned int _timer;
  unsigned int _cycle;

};

class SuperParallelVisual : public Visual {
public:

  SuperParallelVisual(Director& director);
  void update() override;
  void render() const override;

private:

  static const std::size_t image_count = 4;
  static const unsigned int font_length = 64;
  static const unsigned int length = 2;
  static const unsigned int cycles = 512;

  std::vector<Image> _images;
  std::vector<unsigned int> _lengths;
  std::size_t _index;
  std::string _current_text;
  unsigned int _timer;
  unsigned int _font_timer;
  unsigned int _cycle;

};

class AnimationVisual : public Visual {
public:

  AnimationVisual(Director& director);
  void update() override;
  void render() const override;

private:

  static const unsigned int length = 256;
  static const unsigned int cycles = 4;

  Image _animation;
  Image _current;
  std::string _current_text;
  unsigned int _timer;
  unsigned int _cycle;

};

#endif