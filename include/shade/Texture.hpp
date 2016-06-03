#pragma once
#include <unordered_map>
#include "precision.hpp"
#include "ISampleable.hpp"
#include "util/StbImageReader.hpp"
class Texture : public ISampleable
{
public:
   /**
    * Rule of 5 constructor set.
    */
   Texture(int width, int height, int nComps, stbi_uc * buffer);
   Texture(std::string fileName, int reqComponents = 3);
   ~Texture();
   Texture(const Texture & other);
   Texture(Texture && other);
   Texture &operator=(const Texture &other);
   Texture &operator=(Texture && other);

   int getWidth() const;
   int getHeight() const;
   /**
    * Perform bilinear sampling at a UV point.
    * @param  uv a vector [0..1] on where to read from the texture
    * @return    the color at the texture.
    */
   Color3 sample(Vector2 uv) const override;
private:
   Color3 readPixel(int x, int y) const;
   int width, height, nComps;
   bool loaded;
   stbi_uc * buffer;

};