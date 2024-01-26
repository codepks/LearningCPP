# LearningCPP

## Virtual Table
When a function contains virtual function than virtual table corresponding to that class is generated during compile time.

Let's look at virtual table of this class:

```class BaseClass
{
public:
	BaseClass() = default;
	~BaseClass() = default;

	void func1() { std::cout << "This is a base class func1\n"; };
	virtual void func2() { std::cout << "This is base class func2\n\n"; };

};

class DerivedClass : public BaseClass
{
public:
	DerivedClass() = default;
	~DerivedClass() = default;

	void func1() { std::cout << "This is a derived class func1\n"; };
	void func2() override { std::cout << "This is derived class func2\n\n"; };

};
```

Virtual table of Base class:
```
BaseClass vtable:
---------------------
| 0: Address of func2() |
---------------------
```
Virtual table of Derived class:

```
DerivedClass vtable:
---------------------
| 0: Address of DerivedClass::func2() |
---------------------
```

When a class is polymorphic (contains virtual functions), the compiler creates a hidden pointer in each object of that class. This pointer, called the **virtual pointer (vptr)**, points to the vtable of the dynamic type of the object.

## Static vs Dynamic vs Reinterpret Cast

### Static Casting
Static casting is done when you know the data types already:
E.g. conversion of float to int. The type is known during compile time.

### Dynamic Casting
Dynamic casting is done when the classes involved in conversion have virtual function and their behaviour is known during run time.
Types : Upcasting - derived to parent case class, where loss of information happens
Downcasting : parent to derived class : information can be restored.

```
class Base {
    virtual void foo() {};
};

class Derived : public Base {
    void foo () {};
};

Base* basePtr = new Derived;	//Upcasting - Loss of Information
Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);	//Downcasting - Retrieve back information

if (derivedPtr) {
    // Successfully casted
} else {
    // Cast failed
}
```




