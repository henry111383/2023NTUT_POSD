#include "../src/json_object.h"
#include "../src/string_value.h"
#include "../src/beautify_visitor.h"
#include <gtest/gtest.h>

TEST(visitorSuite, visitorTest) {
    JsonObject *json1 = new JsonObject();
    Value *json1_name = new StringValue("Design Patterns Elements of Reusable Object-Oriented Software");
    Value *json1_author = new StringValue("Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides");
    json1->set("name", json1_name);
    json1->set("author", json1_author);

    JsonObject *json2 = new JsonObject();
    Value *json2_name = new StringValue("Clean Code");
    Value *json2_author = new StringValue("Robert C. Martin");
    json2->set("name", json2_name);
    json2->set("author", json2_author);

    JsonObject *compositeJ = new JsonObject();
    compositeJ ->set("design pattern", json1);
    compositeJ ->set("clean code", json2);

    JsonObject *total_Json = new JsonObject();
    total_Json -> set("books", compositeJ);
    
    BeautifyVisitor *visitor = new BeautifyVisitor();
    total_Json->accept(visitor);

    std::string expected;
    expected += "{\n";
    expected += "    \"books\": {\n";
    expected += "        \"clean code\": {\n";
    expected += "            \"author\": \"Robert C. Martin\",\n";
    expected += "            \"name\": \"Clean Code\"\n";
    expected += "        },\n";
    expected += "        \"design pattern\": {\n";
    expected += "            \"author\": \"Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides\",\n";
    expected += "            \"name\": \"Design Patterns Elements of Reusable Object-Oriented Software\"\n";
    expected += "        }\n";
    expected += "    }\n";
    expected += "}";
    
    std::string res = visitor->getResult();
    // std::cout << std::endl << "---This is result---\n";
    // std::cout << res << std::endl; 
    ASSERT_EQ(expected, res);

    // delete json1;
    // delete json2;
    // delete compositeJ;
    delete total_Json;
    delete visitor;
    // delete json1_name;
    // delete json1_author;
    // delete json2_name;
    // delete json2_author;
}
