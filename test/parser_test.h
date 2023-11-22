#include "../src/json_object.h"
#include "../src/string_value.h"
#include "../src/beautify_visitor.h"
#include "../src/json_parser.h"
#include "../src/json_builder.h"
#include "../src/json_scanner.h"
#include <gtest/gtest.h>

TEST(ParserTest, BuilderShouldbeCorrectlyBuilt){
    JsonBuilder *builder;
    ASSERT_NO_THROW(builder = new JsonBuilder());
    delete builder;
}

TEST(ParserTest, ScannerShouldbeCorrectlyBuilt){
    JsonScanner *scanner;
    ASSERT_NO_THROW(scanner = new JsonScanner());
    delete scanner;
}

TEST(ParserTest, PaserShouldbeCorrectlyBuilt){
    JsonBuilder *builder;
    JsonScanner *scanner;
    ASSERT_NO_THROW(builder = new JsonBuilder());
    ASSERT_NO_THROW(scanner = new JsonScanner());
    JsonParser *parser;
    ASSERT_NO_THROW(parser = new JsonParser(scanner, builder));
    delete builder;
    delete scanner;
    delete parser;
}

TEST(ParserTest, ScannerAllShouldbeCorrect){
    JsonBuilder *builder;
    JsonScanner *scanner;
    ASSERT_NO_THROW(builder = new JsonBuilder());
    ASSERT_NO_THROW(scanner = new JsonScanner());
    JsonParser *parser;
    ASSERT_NO_THROW(parser = new JsonParser(scanner, builder));

    std::string input_str;
    input_str += "{\n";
    input_str += "    \"books\": {\n";
    input_str += "        \"clean code\": {\n";
    input_str += "            \"author\": \"Robert C. Martin\",\n";
    input_str += "            \"name\": \"Clean Code\"\n";
    input_str += "        },\n";
    input_str += "        \"design pattern\": {\n";
    input_str += "            \"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides\",\n";
    input_str += "            \"name\": \"Design Patterns Elements of Reusable Object-Oriented Software\"\n";
    input_str += "        }\n";
    input_str += "    }\n";
    input_str += "}";

    ASSERT_NO_THROW(scanner->setInput(input_str));
    ASSERT_EQ('{', scanner->next());
    ASSERT_EQ('\n', scanner->next());

    delete builder;
    delete scanner;
    delete parser;
}

TEST(ParserTest, ParserAllShouldbeCorrect){
    JsonBuilder *builder;
    JsonScanner *scanner;
    ASSERT_NO_THROW(builder = new JsonBuilder());
    ASSERT_NO_THROW(scanner = new JsonScanner());
    JsonParser *parser;
    ASSERT_NO_THROW(parser = new JsonParser(scanner, builder));

    std::string input_str;
    input_str += "{\n";
    input_str += "    \"books\": {\n";
    input_str += "        \"clean code\": {\n";
    input_str += "            \"author\": \"Robert C. Martin\",\n";
    input_str += "            \"name\": \"Clean Code\"\n";
    input_str += "        },\n";
    input_str += "        \"design pattern\": {\n";
    input_str += "            \"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides\",\n";
    input_str += "            \"name\": \"Design Patterns Elements of Reusable Object-Oriented Software\"\n";
    input_str += "        }\n";
    input_str += "    }\n";
    input_str += "}";

    ASSERT_NO_THROW(parser->setInput(input_str));
    ASSERT_NO_THROW(parser->parse());
    JsonObject *resultJson = parser->getJsonObject();

    BeautifyVisitor *visitor = new BeautifyVisitor();
    resultJson->accept(visitor);
    std::string res = visitor->getResult();

    std::cout << std::endl << "---This is result---\n";
    std::cout << res << std::endl; 

    delete builder;
    delete scanner;
    delete parser;
}
