#ifndef KEYBOARD_HH
#define KEYBOARD_HH

# include   <GL/gl.h>
# include   <GDL/Input.hpp>
# include   <GDL/Text.hpp>
# include   <vector>
# include   <map>
# include   <string>
# include   "flatTexture.hh"
# include   "CarrouselHandler.hh"

class Keyboard
{

public:
    Keyboard(int x, int y, uint limit = 15);
    ~Keyboard(void);

public:
    void update(gdl::Input& input);
    void draw(void) const;

    const std::string getData(void) const;
    void setFocus(bool);

private:
    void privateUpdate(gdl::Input& input);

private:
     int            x_;
     int            y_;
     uint           limit_;
     gdl::Text      *text_;
     bool           letbool_;
     bool           focus_;
     std::vector<std::string> data_;
     std::map<gdl::Keys::Key, std::string> letters_;
};

#endif // KEYBOARD_HH
