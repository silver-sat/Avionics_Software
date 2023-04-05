/**
 * @file tokenizer.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief tokenizer implementation with character manipulation
 * @version 1.0.0
 * @date 2023-04-03
 *
 * Implements https://docs.google.com/presentation/d/1Xw3lUu81yLnpkeHwMXOLl7wfIG3j5VsndNmMz3wN4bU/edit?usp=sharing
 *
 */

constexpr size_t maximum_tokens{10}; // Allow up to 10 tokens

/**
 * @brief Parse the command string into tokens
 *
 * @param command string to be parsed
 * @param tokens String array of tokens
 * @param token_count token count, -1 if error
 *
 */

void tokenizer(const String &command, String tokens[], size_t &token_count)
{
    for (size_t index{0}; index < maximum_tokens; ++index)
        tokens[index] = "";
    token_count = 0;
    bool in_token{false};
    for (auto character : command)
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
                if (++token_count > maximum_tokens)
                {
                    token_count = -1; // too many tokens
                    break;
                }
                in_token = true;
            }
            tokens[token_count - 1] += character;
        }
    }
}

/**
 * @brief Print test results
 *
 * @param command String that was tokenized
 * @param tokens String array of tokens
 * @param token_count token count, -1 if error
 *
 */

void print_result(const String &command, const String tokens[], const size_t token_count)
{
    Serial.println("For command: \"" + command + '\"');
    if (static_cast<int>(token_count) == -1)
    {
        Serial.println("Parsing error");
    }
    else
    {
        Serial.println("Token count is " + String(token_count));
        for (size_t index{0}; index < token_count; ++index)
            Serial.println(tokens[index]);
    }
    Serial.println();
}

/**
 * @brief Execute the tests
 *
 */

void setup()
{
    Serial.begin(115200);
    while (!Serial)
        ;

    String tokens[maximum_tokens];
    size_t token_count{};
    String test_command;

    test_command = "NoOperate";
    tokenizer(test_command, tokens, token_count);
    print_result(test_command, tokens, token_count);

    test_command = "Invalid 2 3 4 5 6 7 8 9 10";
    tokenizer(test_command, tokens, token_count);
    print_result(test_command, tokens, token_count);

    test_command = "Invalid 2 3 4 5 6 7 8 9 10     ";
    tokenizer(test_command, tokens, token_count);
    print_result(test_command, tokens, token_count);

    test_command = "Invalid 2 3 4 5 6 7 8 9 10     11";
    tokenizer(test_command, tokens, token_count);
    print_result(test_command, tokens, token_count);

    test_command = "Invalid 2 3 4 5 6 7 8 9 10     11 12  ";
    tokenizer(test_command, tokens, token_count);
    print_result(test_command, tokens, token_count);

    test_command = "SetClock 2023 11 11 10 10 10";
    tokenizer(test_command, tokens, token_count);
    print_result(test_command, tokens, token_count);

    test_command = "SetClock   2023   11   11   10   10   10";
    tokenizer(test_command, tokens, token_count);
    print_result(test_command, tokens, token_count);

    test_command = "     NoOperate";
    tokenizer(test_command, tokens, token_count);
    print_result(test_command, tokens, token_count);

    test_command = "     SetClock 2023 11 11 10 10   10      ";
    tokenizer(test_command, tokens, token_count);
    print_result(test_command, tokens, token_count);

    test_command = "";
    tokenizer(test_command, tokens, token_count);
    print_result(test_command, tokens, token_count);
}

/**
 * @brief Arduino loop function
 *
 */

void loop() {}