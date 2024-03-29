/**
 * @file tokenizer2.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief tokenizer implementation with String methods
 * @version 1.0.0
 * @date 2023-04-05
 *
 * Implements https://docs.google.com/presentation/d/1Xw3lUu81yLnpkeHwMXOLl7wfIG3j5VsndNmMz3wN4bU/edit?usp=sharing
 *
 */

constexpr size_t maximum_tokens{ 10 };

/**
 * @brief Parse command for blank-delimited tokens
 *
 * @param [in] command blank delimited command string
 * @param [out] tokens String array of tokens
 * @param [out] token_count token count, -1 if error
 *
 */

void tokenizer(const String &command, String tokens[], size_t &token_count) {

  token_count = 0;
  String trimmed_command{ command };

  trimmed_command.trim();  // remove leading (and trailing) blanks
  while (trimmed_command.length() > 0) {

    if (token_count >= maximum_tokens) {
      token_count = -1;  // too many tokens
      return;
    }

    int next_blank{ trimmed_command.indexOf(' ') };
    if (next_blank == -1) {  // no more blanks in command
      tokens[token_count++] = trimmed_command;
      trimmed_command = "";
    } else {
      tokens[token_count++] = trimmed_command.substring(0, next_blank);
      trimmed_command = trimmed_command.substring(next_blank);
    }

    trimmed_command.trim();  // remove leading blank(s)
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

void print_result(const String &command, const String tokens[], const size_t token_count) {
  Serial.println("For command: \"" + command + '\"');
  if (static_cast<int>(token_count) == -1) {
    Serial.println("Parsing error");
  } else {
    Serial.println("Token count is " + String(token_count));
    for (size_t index{ 0 }; index < token_count; ++index)
      Serial.println(tokens[index]);
  }
  Serial.println();
}

/**
 * @brief Execute the tests
 *
 */

void setup() {
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

  test_command = "     ";
  tokenizer(test_command, tokens, token_count);
  print_result(test_command, tokens, token_count);
}

/**
 * @brief Arduino loop function
 *
 */

void loop() {}