#ifndef SHOOTER_TEXTUREHOLDER_HPP
#define SHOOTER_TEXTUREHOLDER_HPP

#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

class TextureHolder {
private:
    // A map container from the STL,
    // that holds related pairs of String and Texture
    map<string, Texture> textures;

    // A pointer of the same type as the class itself
    // the one and only instance
    static TextureHolder* instance;

public:
    TextureHolder();
    static Texture& GetTexture(string const& filename);
};
#endif //SHOOTER_TEXTUREHOLDER_HPP
