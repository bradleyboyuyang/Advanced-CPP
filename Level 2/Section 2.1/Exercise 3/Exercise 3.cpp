/*
    Level 2.1: Type Traits
    Problem 3: Type Properties and Type Relationships

    Name: Boyu Yang

    Problem objective:
    Regarding the given class, answer the following questions using appropriate type traits functions
    a) Which classes/types are empty, polymorphic or abstract?
    b) Which classes are the same?
    c) Which classes have a gen/spec (base/derived) relationship?
    d) Which types can be converted to each other?

*/

#include <iostream>

class Shape {
public:
    virtual void draw() = 0;
};

class Base {
private:
    int y;
public:
    Base() {}
    void draw() {}
};

class Point : public Shape {
public:
    Point() {}
    virtual void draw() override {}
};

/// Part (A) Check type properties
template <typename T>
void checkTypeProperty(const T& t){ 
    // A class with no data and no virtual functions
    std::cout << "** Check type properties **\n";
    std::cout << "Is class empty? " << std::boolalpha << std::is_empty<T>::value << std::endl;
    std::cout << "Is the class polymorphic? " << std::boolalpha << std::is_polymorphic<T>::value << std::endl;
    std::cout << "Abstract class type? " << std::boolalpha << std::is_abstract<T>::value << std::endl;
    std::cout << "End *********************\n";
}

/// Part (B), (C), (D)
// Check type relations
template <typename T1, typename T2>
void checkTypeRelations(const T1& t1, const T2& t2){
    std::cout << "** Check type relations **\n";
    std::cout << "Is same type? " << std::boolalpha << std::is_same<T1, T2>::value << std::endl;
    std::cout << "Is base of? " << std::boolalpha << std::is_base_of<T1, T2>::value << std::endl;
    std::cout << "Is convertible? " << std::boolalpha << std::is_convertible<T1, T2>::value << std::endl;
    std::cout << "End *********************\n";
}

int main()
{
    /// Part (A) Which classes / types are empty, polymorphic or abstract ?
    // Check Type properties. We answer question (A) using ``checkTypeProperty" function
    Shape* sh = nullptr;
    checkTypeProperty(*sh); // Test empty class

    Shape* shape = new Point;
    checkTypeProperty(*shape); // Test polymorphic and non-empty class
    delete shape;

    Base b;
    checkTypeProperty(b); // Test non-polymorphic and non-empty class

    Point p;
    checkTypeProperty(p); // Test polymorphic and non-empty class

    /// Part (B) Which classes are the same ?
    /// Part (C) Which classes have a gen / spec(base / derived) relationship ?
    /// Part (D) Which types can be converted to each other ?
    // Check type relations. We answer question (B), (C), (D) using ``checkTypeProperty" function
    checkTypeRelations(*shape, *shape); // same classes, is base of, not convertible
    checkTypeRelations(b, b); // same classes, is base of, convertible
    checkTypeRelations(*shape, b); // not same classes, not base of, not convertible
    checkTypeRelations(*shape, p); // not same classes, is base of, not convertible
    checkTypeRelations(b, p); // not same classes, not base of, not convertible

    return 0;
}


