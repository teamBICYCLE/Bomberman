#include "Keyboard.hh"
#include "ModelHandler.hh"

Keyboard::Keyboard(int x, int y, uint limit)
    : x_(x), y_(y), limit_(limit), text_(new gdl::Text())
{
    text_->setFont("Ressources/Fonts/Dimbo.ttf");
    letters_.insert(std::make_pair(gdl::Keys::A, "A"));
    letters_.insert(std::make_pair(gdl::Keys::B, "B"));
    letters_.insert(std::make_pair(gdl::Keys::C, "C"));
    letters_.insert(std::make_pair(gdl::Keys::D, "D"));
    letters_.insert(std::make_pair(gdl::Keys::E, "E"));
    letters_.insert(std::make_pair(gdl::Keys::F, "F"));
    letters_.insert(std::make_pair(gdl::Keys::G, "G"));
    letters_.insert(std::make_pair(gdl::Keys::H, "H"));
    letters_.insert(std::make_pair(gdl::Keys::I, "I"));
    letters_.insert(std::make_pair(gdl::Keys::J, "J"));
    letters_.insert(std::make_pair(gdl::Keys::K, "K"));
    letters_.insert(std::make_pair(gdl::Keys::L, "L"));
    letters_.insert(std::make_pair(gdl::Keys::M, "M"));
    letters_.insert(std::make_pair(gdl::Keys::N, "N"));
    letters_.insert(std::make_pair(gdl::Keys::O, "O"));
    letters_.insert(std::make_pair(gdl::Keys::P, "P"));
    letters_.insert(std::make_pair(gdl::Keys::Q, "Q"));
    letters_.insert(std::make_pair(gdl::Keys::R, "R"));
    letters_.insert(std::make_pair(gdl::Keys::S, "S"));
    letters_.insert(std::make_pair(gdl::Keys::T, "T"));
    letters_.insert(std::make_pair(gdl::Keys::U, "U"));
    letters_.insert(std::make_pair(gdl::Keys::V, "V"));
    letters_.insert(std::make_pair(gdl::Keys::W, "W"));
    letters_.insert(std::make_pair(gdl::Keys::X, "X"));
    letters_.insert(std::make_pair(gdl::Keys::Y, "Y"));
    letters_.insert(std::make_pair(gdl::Keys::Z, "Z"));
    letters_.insert(std::make_pair(gdl::Keys::Numpad1, "1"));
    letters_.insert(std::make_pair(gdl::Keys::Numpad2, "2"));
    letters_.insert(std::make_pair(gdl::Keys::Numpad3, "3"));
    letters_.insert(std::make_pair(gdl::Keys::Numpad4, "4"));
    letters_.insert(std::make_pair(gdl::Keys::Numpad5, "5"));
    letters_.insert(std::make_pair(gdl::Keys::Numpad6, "6"));
    letters_.insert(std::make_pair(gdl::Keys::Numpad7, "7"));
    letters_.insert(std::make_pair(gdl::Keys::Numpad8, "8"));
    letters_.insert(std::make_pair(gdl::Keys::Numpad9, "9"));
    letters_.insert(std::make_pair(gdl::Keys::Numpad0, "0"));
    letters_.insert(std::make_pair(gdl::Keys::Period, "."));

    letbool_ = false;
    focus_ = true;
}

Keyboard::~Keyboard()
{

}

void Keyboard::update(gdl::Input& input)
{
    if (focus_)
        Keyboard::privateUpdate(input);
}

void Keyboard::privateUpdate(gdl::Input& input)
{
    bool let;

    if (input.isKeyDown(gdl::Keys::Back) && !letbool_)
    {
        if (data_.size() > 0)
            data_.pop_back();
    }
    else
        for (std::map<gdl::Keys::Key, std::string>::iterator it = letters_.begin(); it != letters_.end(); ++it)
          if (input.isKeyDown(it->first) && !letbool_ && data_.size() < limit_)
            data_.push_back(it->second);

    let = input.isKeyDown(gdl::Keys::Back);
    for (std::map<gdl::Keys::Key, std::string>::iterator it = letters_.begin(); it != letters_.end(); ++it)
    {
        if (let != true)
            let = input.isKeyDown(it->first);
    }
    letbool_ = let;
}

void Keyboard::draw(void) const
{
    std::vector<std::string>::const_iterator it;
    int i = 0;
    glPushMatrix();
    for (it = data_.begin(); it != data_.end(); it++)
    {
        text_->setText(std::string(*it));
        text_->setPosition(x_ + (i * 15), 900 - y_ - 37);
        text_->draw();
        i++;
    }
    glPopMatrix();
}

const std::string Keyboard::getData(void) const
{
    std::string ret;

    std::vector<std::string>::const_iterator it;

    for (it = data_.begin(); it != data_.end(); it++)
        ret.append(*it);
    return ret;
}

void Keyboard::setFocus(bool b)
{
    focus_ = b;
}
