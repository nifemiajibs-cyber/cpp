#include "options.h"
#include <stdexcept>


namespace repeat
{

Options parse(int argc, char * argv[])
{
    (void)argc; (void)argv;
    

    // TODO: implement this function and return the actual, parsed options
    Options result{};
    for (auto i{1}; i < argc; ++i)
    {
        // convert argv[i] to string
        std::string arg{ argv[i] };

        if (arg.rfind("--repeat=", 0) == 0){
            std::string to_int = arg.substr(9);
            result.repeat = stoi(to_int);
        }
        else if(arg.rfind("--color=", 0) == 0)
        {
            std::string text = arg.substr(8);
            result.color = from_string(text);
        }
        
        else if(arg.rfind("-", 0) == 0)
        {
            for(size_t i = 1; i < arg.size(); i++){
                char flag = arg[i];

                switch(flag){
                    
                    case 'C': result.capitalize = true; break;

                    case 'n': result.append_newline = true; break;

                    case 'h': result.help = true;  break;

                    default: throw std::invalid_argument("Unknown short flag");

                }
            }

        }
        else {
            result.text = arg;
        }

    }
    return result;

    

    // just return some defaults for now
}

// return {.help=false, .capitalize=true, .append_newline=true, .color=Color::green,  .repeat=5, .text="Hello, C++ labs!"};
Color from_string(const std::string& text)
{
    if (text == "red")
    {
        return Color::red;
    }
    else if (text == "green")
    {
        return Color::green;
    }
    else if (text == "blue")
    {
        return Color::blue;
    }
    else if (text == "none")
    {
        return Color::none;
    }
    else
    {
        throw std::invalid_argument{"Invalid color"};
    }
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
