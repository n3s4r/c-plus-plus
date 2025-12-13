#include <string_view>
#include <array>

// Compile-time string literal wrapper
template<size_t N>
struct StringLiteral {
    constexpr StringLiteral(const char (&str)[N]) {
        std::copy_n(str, N, value);
    }
    char value[N];
    static constexpr size_t size = N - 1;
};

// Compile-time configuration parser
template<StringLiteral... Keys>
class ConfigParser {
    template<size_t N>
    static constexpr bool match_key(std::string_view key, const char (&str)[N]) {
        return key == std::string_view(str, N - 1);
    }

    template<typename T>
    static constexpr T parse_value(std::string_view value);

public:
    template<typename... Values>
    struct Config {
        std::tuple<Values...> values;
        
        template<size_t I>
        constexpr auto get() const {
            return std::get<I>(values);
        }
    };

    static constexpr auto parse(std::string_view input) {
        std::array<std::string_view, sizeof...(Keys)> values;
        size_t pos = 0;
        size_t value_index = 0;

        while (pos < input.size()) {
            // Skip whitespace
            while (pos < input.size() && std::isspace(input[pos])) ++pos;
            
            // Find key
            size_t key_end = input.find('=', pos);
            std::string_view key = input.substr(pos, key_end - pos);
            
            // Find value
            pos = key_end + 1;
            while (pos < input.size() && std::isspace(input[pos])) ++pos;
            
            size_t value_end = input.find('\n', pos);
            std::string_view value = input.substr(pos, value_end - pos);
            
            // Store value
            values[value_index++] = value;
            
            pos = value_end + 1;
        }

        return Config<decltype(parse_value<Values>(values[0]))...>{
            std::make_tuple(parse_value<Values>(values[0])...)
        };
    }
};

// Example usage
constexpr auto config = ConfigParser<
    "server_port",
    "max_connections",
    "timeout_ms"
>::parse(R"(
    server_port=8080
    max_connections=1000
    timeout_ms=5000
)");

static_assert(config.get<0>() == 8080);
static_assert(config.get<1>() == 1000);
static_assert(config.get<2>() == 5000);
