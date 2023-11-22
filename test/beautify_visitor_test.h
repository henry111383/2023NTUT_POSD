#include "../src/json_object.h"
#include "../src/string_value.h"
#include "../src/beautify_visitor.h"

TEST(visitorSuite, visitorTest) {
    JsonObject *json1 = new JsonObject();
    json1->set("name", new StringValue("Design Patterns Elements of Reusable Object-Oriented Software"));
    json1->set("author", new StringValue("Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides"));

    JsonObject *json2 = new JsonObject();
    json2->set("name", new StringValue("Clean Code"));
    json2->set("author", new StringValue("Robert C. Martin"));

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

}
