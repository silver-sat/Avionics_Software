/**
 * @file tokenizer.ino
 * @author Lee A. Congdon (lee@silversat.org)
 * @brief Mentor solution to February 18th tokenizer challenge
 *   https://docs.google.com/presentation/d/1Xw3lUu81yLnpkeHwMXOLl7wfIG3j5VsndNmMz3wN4bU/edit?usp=sharing
 * @version 1.0.0
 * @date 2023-02-11
 * 
 * 
 */

void tokenizer(const String& command, String tokens[], size_t& token_count) {
  size_t token_index{ 0 };
  bool in_token{ false };
  for (auto character : command) {
    if (!in_token) {
      if (character == ' ') {
        continue;  // ignore leading, trailing, and extra blanks
      } else {
        in_token = true;
      }
    } else {  // in token
      if (character == ' ') {
        in_token = false;
        if (++token_index >= 10) {
          Serial.println("Error: too many tokens");
          break;
        }
        continue;
      }
    }
    tokens[token_index] += character;  // add character to token
  }
  if (in_token) {
    ++token_index;  // increment index if end of string ends token
  }
  token_count = token_index;
}

void print_test(const String& label, const String& command) {
  size_t token_count{};
  String tokens[10]{};
  Serial.print("Starting test ");
  Serial.println(label);
  Serial.println(command);
  tokenizer(command, tokens, token_count);
  Serial.print("Number of tokens: ");
  Serial.println(token_count);
  Serial.println("Tokens:");
  for (size_t i = 0; i < token_count; ++i) {
    Serial.println(tokens[i]);
  }
  Serial.print("Ending test\n\n");
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {};

  String report_t{ "ReportT" };
  String set_clock{ "SetClock 2023 3 15 10 10 30" };
  String invalid{ "Invalid 0 1 2 3 4 5 6 7 8 9" };
  String no_tokens{"     "};

  print_test("ReportT: ", report_t);
  print_test("SetClock: ", set_clock);
  print_test("Invalid: ", invalid);
  print_test("no tokens: ", no_tokens);

}

void loop() {
}