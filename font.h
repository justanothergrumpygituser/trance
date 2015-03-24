#ifndef TRANCE_FONT_H
#define TRANCE_FONT_H

#include <string>
#include <list>
#include <memory>
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>

// Wrapper for an sf::Font that uses one character size only.
struct Font {
  Font(const std::string& path, unsigned int char_size)
  : font(new sf::Font)
  {
    key.path = path;
    key.char_size = char_size;
    if (!path.empty()) {
      font->loadFromFile(path);
    }
  }

  struct key_t {
    std::string path;
    unsigned int char_size;

    bool operator==(const key_t& key) const
    {
      return path == key.path && char_size == key.char_size;
    }

    bool operator!=(const key_t& key) const
    {
      return !operator==(key);
    }
  };

  key_t key;
  std::unique_ptr<sf::Font> font;
};

namespace std {
  template<>
  struct hash<Font::key_t> {
    std::size_t operator()(const Font::key_t& key)
    {
      return std::hash<std::string>()(key.path) + key.char_size;
    }
  };
}

// SFML's Font object works like this: it has a texture for each character size,
// and renders the characters used at that size into the texture for future use.
// This means even if we use some font/size combination very rarely we have no
// way to reclaim the video memory for that size individually.
//
// This is an LRU cache using a separate Font object for each character size to
// keep video memory usage down. Also locks character sizes to evenly-spaced
// possibilities so that we don't need to load so many.
class FontCache {
public:

  FontCache(unsigned int font_cache_size);

  static const std::size_t char_size_lock = 20;
  const Font& get_font(
      const std::string& font_path, unsigned int char_size) const;

private:

  std::vector<std::string> _paths;
  unsigned int _font_cache_size;
  mutable std::size_t _last_id;
  mutable std::list<Font> _list;
  mutable std::unordered_map<Font::key_t, Font*> _map;

};

#endif