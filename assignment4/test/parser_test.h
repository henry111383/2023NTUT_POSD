#include "../src/json_object.h"
#include "../src/string_value.h"
#include "../src/beautify_visitor.h"
#include "../src/json_parser.h"
#include "../src/json_builder.h"
#include "../src/json_scanner.h"
#include "../src/json_iterator.h"
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
}

TEST(ParserTest, SimpleBuilderShouldbeCorrect){
    JsonBuilder *builder;
    ASSERT_NO_THROW(builder = new JsonBuilder());

    std::string input_str;
    input_str += "{\n";
    input_str += "    \"clean code\": {\n";
    input_str += "        \"author\": \"Robert C. Martin\",\n";
    input_str += "        \"name\": \"Clean Code\"\n";
    input_str += "    }\n";
    input_str += "}";

    builder->buildObject("");
    builder->buildObject("clean code");
    builder->buildValue("name", "Clean Code");
    builder->buildValue("author", "Robert C. Martin");
    builder->endObject();
    builder->endObject();

    JsonObject *resultJson = builder->getJsonObject();


    BeautifyVisitor *visitor = new BeautifyVisitor();
    resultJson->accept(visitor);
    std::string res = visitor->getResult();

    std::cout << std::endl << "---This is result---\n";
    std::cout << res << std::endl; 
    ASSERT_EQ(input_str, res);

    delete builder;
    delete visitor;
    delete resultJson;
}

TEST(ParserTest, BuilderAllShouldbeCorrect){
    JsonBuilder *builder;
    ASSERT_NO_THROW(builder = new JsonBuilder());

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

    builder->buildObject("");
    builder->buildObject("books");
    builder->buildObject("clean code");
    builder->buildValue("name", "Clean Code");
    builder->buildValue("author", "Robert C. Martin");
    builder->endObject();
    builder->buildObject("design pattern");
    builder->buildValue("name", "Design Patterns Elements of Reusable Object-Oriented Software");
    builder->buildValue("author", "Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides");
    builder->endObject();
    builder->endObject();
    builder->endObject();

    JsonObject *resultJson = builder->getJsonObject();


    BeautifyVisitor *visitor = new BeautifyVisitor();
    resultJson->accept(visitor);
    std::string res = visitor->getResult();

    std::cout << std::endl << "---This is result---\n";
    std::cout << res << std::endl; 
    ASSERT_EQ(input_str, res);

    delete builder;
    delete visitor;
    delete resultJson;
}

TEST(ParserTest, SimpleParserShouldbeCorrect){
    JsonBuilder *builder;
    JsonScanner *scanner;
    ASSERT_NO_THROW(builder = new JsonBuilder());
    ASSERT_NO_THROW(scanner = new JsonScanner());
    JsonParser *parser;
    ASSERT_NO_THROW(parser = new JsonParser(scanner, builder));

    std::string booksJson = 
    "{"
    "\"clean code\": {"
    "\"name\": \"Clean Code\","
    "\"author\": \"Robert C. Martin\""
    "}"
    "}";


    ASSERT_NO_THROW(parser->setInput(booksJson));
    ASSERT_NO_THROW(parser->parse());
    JsonObject *resultJson = parser->getJsonObject();

    BeautifyVisitor *visitor = new BeautifyVisitor();
    resultJson->accept(visitor);
    std::string res = visitor->getResult();

    std::string expected;
    expected += "{\n";
    expected += "    \"clean code\": {\n";
    expected += "        \"author\": \"Robert C. Martin\",\n";
    expected += "        \"name\": \"Clean Code\"\n";
    expected += "    }\n";
    expected += "}";

    ASSERT_EQ(expected, res);


    delete builder;
    delete scanner;
    delete parser;
    delete resultJson;
    delete visitor;

}

TEST(ParserTest, ParserAllShouldbeCorrect){
    JsonBuilder *builder;
    JsonScanner *scanner;
    ASSERT_NO_THROW(builder = new JsonBuilder());
    ASSERT_NO_THROW(scanner = new JsonScanner());
    JsonParser *parser;
    ASSERT_NO_THROW(parser = new JsonParser(scanner, builder));

    std::string booksJson = 
    "{\"books\": {"
    "\"design pattern\": {"
    "\"name\": \"Design Patterns: Elements of Reusable Object-Oriented Software\","
    "\"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides\""
    "},"
    "\"clean code\": {"
    "\"name\": \"Clean Code\","
    "\"author\": \"Robert C. Martin\""
    "}"
    "}}";


    ASSERT_NO_THROW(parser->setInput(booksJson));
    ASSERT_NO_THROW(parser->parse());
    JsonObject *resultJson = parser->getJsonObject();

    BeautifyVisitor *visitor = new BeautifyVisitor();
    resultJson->accept(visitor);
    std::string res = visitor->getResult();

    std::string expected;
    expected += "{\n";
    expected += "    \"books\": {\n";
    expected += "        \"clean code\": {\n";
    expected += "            \"author\": \"Robert C. Martin\",\n";
    expected += "            \"name\": \"Clean Code\"\n";
    expected += "        },\n";
    expected += "        \"design pattern\": {\n";
    expected += "            \"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides\",\n";
    expected += "            \"name\": \"Design Patterns: Elements of Reusable Object-Oriented Software\"\n";
    expected += "        }\n";
    expected += "    }\n";
    expected += "}";

    ASSERT_EQ(expected, res);

    delete builder;
    delete scanner;
    delete parser;
    delete resultJson;
    delete visitor;
}

TEST(ParserTest, ParserSpacesShouldbeCorrect){
    JsonBuilder *builder;
    JsonScanner *scanner;
    ASSERT_NO_THROW(builder = new JsonBuilder());
    ASSERT_NO_THROW(scanner = new JsonScanner());
    JsonParser *parser;
    ASSERT_NO_THROW(parser = new JsonParser(scanner, builder));

    std::string expected;
    expected += "{\n";
    expected += "    \"books\": {\n";
    expected += "        \"clean code\": {\n";
    expected += "            \"author\": \"Robert C. Martin\",\n";
    expected += "            \"name\": \"Clean Code\"\n";
    expected += "        },\n";
    expected += "        \"design pattern\": {\n";
    expected += "            \"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, and John Vlissides\",\n";
    expected += "            \"name\": \"Design Patterns: Elements of Reusable Object-Oriented Software\"\n";
    expected += "        }\n";
    expected += "    }\n";
    expected += "}";

    std::string input= R"({  "id"  :"10","desc"  :  "A Product"  ,         "isDeleted"    :  "false"})";

    ASSERT_NO_THROW(parser->setInput(input));
    ASSERT_NO_THROW(parser->parse());
    JsonObject *resultJson = parser->getJsonObject();

    BeautifyVisitor *visitor = new BeautifyVisitor();
    resultJson->accept(visitor);
    std::string res = visitor->getResult();

    std::cout << std::endl << "---Input---\n" << input <<std::endl;
    std::cout << std::endl << "---This is result---\n";
    std::cout << res << std::endl; 
    // ASSERT_EQ(expected, res);


    delete builder;
    delete scanner;
    delete parser;
    delete resultJson;
    delete visitor;
}


