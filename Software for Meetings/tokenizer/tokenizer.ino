/**
 * @file tokenizer.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Another tokenizer
 * @version 1.0.0
 * @date 2023-04-03
 *
 *
 */

constexpr size_t max_tokens{10}; // Allow up to 10 tokens

struct Tokens
{
    bool error{false};          // Parsing error (i.e. too many tokens)
    size_t count{0};            // number of tokens parsed
    String token[max_tokens]{}; // token contents
};

/**
 * @brief Parse blank delimited tokens in input string
 * 
 * @param input String to be tokenized
 * @return Tokens results
 */

Tokens tokenizer(const String input)
{
    Tokens result{};
    bool in_token{false};
    for (auto character : input)
    {
        if (character == ' ')
        {
            if (in_token)
                in_token = false;
        }
        else
        {
            if (!in_token)
            {
                if (++result.count > max_tokens)
                {
                    result.error = true;
                    break;
                }
                in_token = true;
            }
            result.token[result.count - 1] += character;
        }
    }
    return result;
}

/**
 * @brief Print formatted test results
 * 
 * @param result output of tokenizer()
 */

void printTokens(const Tokens result)
{
    Serial.println("---Starting test---");
    if (result.error)
    {
        Serial.println("Parsing error");
    }
    else
    {
        Serial.println("Token count is " + String(result.count));
        for (size_t index{0}; index < result.count; ++index)
            Serial.println(result.token[index]);
    }
    Serial.println("---Ending test---\n");
}

/**
 * @brief Execute test cases
 * 
 */

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;
    printTokens(tokenizer("NoOperate"));
    printTokens(tokenizer("Invalid 2 3 4 5 6 7 8 9 10"));
    printTokens(tokenizer("Invalid 2 3 4 5 6 7 8 9 10     "));
    printTokens(tokenizer("Invalid 2 3 4 5 6 7 8 9 10     11"));
    printTokens(tokenizer("Invalid 2 3 4 5 6 7 8 9 10     11 12  "));
    printTokens(tokenizer("SetClock 2023 11 11 10 10 10"));
    printTokens(tokenizer("SetClock   2023   11   11   10   10   10"));
    printTokens(tokenizer("     NoOperate"));
    printTokens(tokenizer("     SetClock 2023 11 11 10 10   10      "));
    printTokens(tokenizer(""));
}

/**
 * @brief Arduino loop function
 * 
 */

void loop() {}