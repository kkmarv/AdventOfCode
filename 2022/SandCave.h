#pragma once

struct Tile
{
   static const char START = '+'; // ▼
   static const char AIR   = ' ';
   static const char ROCK  = '#'; // █
   static const char SAND  = 'o'; // ░
};

struct Vec2
{
   int x; // distance to the right
   int y; // distance downwards

   friend inline bool operator==(const Vec2& v1, const Vec2& v2) { return v1.x == v2.x && v1.y == v2.y; }
   inline bool operator!=(const Vec2& other) const { return !(*this == other); }

   inline bool operator<(const Vec2& other) const
   {
      return this->y < other.y || (this->y <= other.y && this->x < other.x);
   }
   inline bool operator>(const Vec2& other) const { return !(*this < other); }

   inline bool operator<=(const Vec2& other) const { return (*this < other || *this == other); }
   inline bool operator>=(const Vec2& other) const { return (*this > other || *this == other); }

   inline Vec2 operator+(const Vec2& other) const { return Vec2{ this->x + other.x, this->y + other.y }; }
   inline Vec2 operator++()
   {
      Vec2 tmp = *this;
      this->y += 1;
      return tmp;
   }

   inline void operator+=(const Vec2& other)
   {
      this->x = this->x + other.x;
      this->y = this->y + other.y;
   }

   Vec2(int x, int y) : x(x), y(y) {}
};
