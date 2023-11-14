#include "../src/json_object.h"
#include "../src/string_value.h"
#include "../src/beautify_visitor.h"

TEST(visitorSuite, visitorTest) {
    JsonObject *json1 = new JsonObject;
    json1->set("name", new StringValue("Design Patterns Elements of Reusable Object-Oriented Software"));
    json1->set("author", new StringValue("Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides"));

    JsonObject *json2 = new JsonObject;
    json2->set("name", new StringValue("Clean Code"));
    json2->set("author", new StringValue("Robert C. Martin"));

    JsonObject *compositeJ = new JsonObject;
    compositeJ ->set("design pattern", json1);
    compositeJ ->set("clean code", json2);
    
    BeautifyVisitor *visitor = new BeautifyVisitor();
    compositeJ->accept(visitor);

    // ASSERT_EQ("", visitor->getResult());

}

// {
//     "books": {
//         "design pattern": {
//             "name": "Design Patterns Elements of Reusable Object-Oriented Software",
//             "author": "Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides"
//         },
//         "clean code": {
//             "name": "Clean Code",
//             "author": "Robert C. Martin"
//         }
//     }
// }
