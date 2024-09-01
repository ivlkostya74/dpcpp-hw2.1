#include <string>
#include <iostream>

class Text {
public:
    Text()
    {
    };
    virtual void render(const std::string& data) const {
        std::cout << data;
    }
    virtual void render(const std::string& href, const std::string& data) const {
        std::cout << href << ">" << data;
    }
};


class DecoratedText : public Text {
public:
    explicit DecoratedText(Text* text) : text_(text)
    {
    }
    Text* text_;
};

class ItalicText : public DecoratedText {
public:
    explicit ItalicText(Text* text) : DecoratedText(text) {
    }
    void render(const std::string& data)  const override
    {
        std::cout << "<i>";
        text_->render(data);
        std::cout << "</i>";
    }

    void render(const std::string& href, const std::string& data) const override
    {
        std::cout << "<i>";
        text_->render(href, data);
        std::cout << "</i>";
    }
};

class BoldText : public DecoratedText {
public:
    explicit BoldText(Text* text) : DecoratedText(text) {
    }
    void render(const std::string& data) const override
    {

        std::cout << "<b>";
        text_->render(data);
        std::cout << "</b>";
    }

    void render(const std::string& href, const std::string& data) const override
    {
        std::cout << "<b>";
        text_->render(href, data);
        std::cout << "</b>";
    }
};

class Paragraph : public DecoratedText
{
public:
    explicit Paragraph(Text* text) : DecoratedText(text)
    {
    }
    void render(const std::string& data) const override
    {
        std::cout << "<p>";
        text_->render(data);
        std::cout << "</p>";
    }

    void render(const std::string& href, const std::string& data) const override
    {
        std::cout << "<p>";
        text_->render(href, data);
        std::cout << "</p>";
    }
};

class Reversed : public Text
{
public:
    explicit Reversed(Text* text) : text_(text)
    {

    }
    void render(const std::string& data) const override
    {
        std::string dataReversed = data;
        std::reverse(dataReversed.begin(), dataReversed.end());
        std::cout << dataReversed;
    }

    void render(const std::string& href, const std::string& data) const override
    {
        std::string dataReversed = data;
        std::reverse(dataReversed.begin(), dataReversed.end());
        std::cout << dataReversed;
    }
private:
    Text* text_;
};


class Link : public Text
{
public:
    explicit Link(Text* text) : text_(text)
    {

    }
    void render(const std::string& href, const std::string& data) const override
    {
        std::cout << "<a ";
        text_->render(href, data);
        std::cout << "</a>";
    }
private:
    Text* text_;
};

int main() {
    auto text_block = new Paragraph(
        new ItalicText(
            new BoldText(
                new Reversed(
                    new Text()
                )
            )
        )
    );
    text_block->render("Hello world");
    std::cout << std::endl;
    auto text_block2 = new ItalicText(new Link(new Text));
    text_block2->render("netology.ru", "Hello world");
    return 0;
}