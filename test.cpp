#include "options.h"
#include <stdexcept>
#include <string>

namespace repeat
{

Options parse(int argc, char * argv[])
{
    Options result{};

    for (int i = 1; i < argc; ++i)
    {
        std::string arg{argv[i]};

        // --repeat=NUM
        if (arg.rfind("--repeat=", 0) == 0)
        {
            std::string value = arg.substr(9);

            if (value.empty())
                throw std::invalid_argument("Missing value for --repeat");

            result.repeat = std::stoi(value);
        }

        // -r=NUM
        else if (arg.rfind("-r=", 0) == 0)
        {
            std::string value = arg.substr(3);

            if (value.empty())
                throw std::invalid_argument("Missing value for -r");

            result.repeat = std::stoi(value);
        }

        // --color=COLOR
        else if (arg.rfind("--color=", 0) == 0)
        {
            std::string value = arg.substr(8);

            if (value.empty())
                throw std::invalid_argument("Missing value for --color");

            result.color = from_string(value);
        }

        // -c=COLOR
        else if (arg.rfind("-c", 0) == 0)
        {
            std::string value = arg.substr(2);

            if (value.empty())
                throw std::invalid_argument("Missing value for -c");

            result.color = from_string(value);
        }

        // short flags (-n -C -h or combined -nC)
        else if (arg.rfind("-", 0) == 0)
        {
            for (size_t j = 1; j < arg.size(); ++j)
            {
                char flag = arg[j];

                switch(flag)
                {
                    case 'C':
                        result.capitalize = true;
                        break;

                    case 'n':
                        result.append_newline = true;
                        break;

                    case 'h':
                        result.help = true;
                        break;

                    default:
                        throw std::invalid_argument("Unknown short flag");
                }
            }
        }

        // text argument
        else
        {
            if (!result.text.empty())
                result.text += " ";

            result.text += arg;
        }
    }

    return result;
}


Color from_string(const std::string& text)
{
    if (text == "red")
        return Color::red;
    else if (text == "green")
        return Color::green;
    else if (text == "blue")
        return Color::blue;
    else if (text == "none")
        return Color::none;
    else
        throw std::invalid_argument("Invalid color");
}


std::ostream& operator<<(std::ostream& out, Color color)
{
    switch(color)
    {
        case Color::red:
            return out << "red";
        case Color::green:
            return out << "green";
        case Color::blue:
            return out << "blue";
        case Color::none:
            return out << "none";
        default:
            return out << "unknown";
    }
}


std::ostream& operator<<(std::ostream& out, Options const& options)
{
    out << "Options:\n";
    out << "  help: " << std::boolalpha << options.help << '\n';
    out << "  capitalize: " << std::boolalpha << options.capitalize << '\n';
    out << "  append_newline: " << std::boolalpha << options.append_newline << '\n';
    out << "  color: " << options.color << '\n';
    out << "  repeat: " << options.repeat << '\n';
    out << "  text: " << options.text << '\n';

    return out;
}

} // namespace repeat