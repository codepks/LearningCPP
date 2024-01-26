# LearningCPP

# Virtual Table
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
*BaseClass contains a virtual function func2().
When an object of BaseClass is created, it contains a hidden virtual pointer (vptr) that points to the vtable of BaseClass.*
```
BaseClass vtable:
---------------------
| 0: Address of func2() |
---------------------
```
Virtual table of Derived class:

*DerivedClass also contains a virtual function func2(), which overrides the same function in BaseClass. When an object of DerivedClass is created, it contains a vptr that points to the vtable of DerivedClass.*
```
DerivedClass vtable:
---------------------
| 0: Address of DerivedClass::func2() |
---------------------
```

When a class is polymorphic (contains virtual functions), the compiler creates a hidden pointer in each object of that class. This pointer, called the **virtual pointer (vptr)**, points to the vtable of the dynamic type of the object.

# Static vs Dynamic vs Reinterpret Cast

## Static Casting
Static casting is done when you know the data types already:
E.g. conversion of float to int. The type is known during compile time.

## Dynamic Casting
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

### Casting Failure

```
class BaseClass
{
public:
	BaseClass() = default;
	~BaseClass() = default;

	void func1() { std::cout << "This is a base class func1\n"; };
	virtual void func2() { std::cout << "This is base class func2\n"; };
};

class DerivedClass : public BaseClass
{
public:
	DerivedClass() = default;
	~DerivedClass() = default;

	void func1() { std::cout << "This is a derived class func1\n"; };
	void func2() override { std::cout << "This is derived class func2\n"; };
};

int main()
{
	BaseClass *base = new BaseClass();
	base->func2();
	//downcasting
	DerivedClass* derived = dynamic_cast<DerivedClass*>(base); 

	derived->func2();
	// *Casting fails*
}
```

The dynamic casting fails because, intially base pointer points to BaseClass object.
In the dynamic casting we are making DerivedClass pointer point to Base class object where it fails.

```
DerivedClass* derived = dynamic_cast<DerivedClass*>(base);
```
During Dynamic Casting, the casting checks if the object being pointed to (Base class here by base *) by a pointer(Derived Class pointer here) is an instance of Derived Class or not.


# Reinterpret_Cast
It doesn't work on the basis of polymorphic behavior like Dynamic casting does.

In the code below:
```
DerivedClass* derived = reinterpret_cast<DerivedClass*>(base);
```
reinterpret_cast takes the BaseClass pointer base and forcefully reinterprets the bits of its address as if they were a DerivedClass pointer.
**It simply creates a new pointer of the target type with the same memory address as the original pointer.**

Since derived is a DerivedClass pointer, the compiler expects a DerivedClass object with its own virtual function table (vtable).
However, the actual object doesn't have a vtable for DerivedClass. It only has the vtable for BaseClass.
When derived->func2(); is called, the compiler incorrectly looks up func2 in the DerivedClass vtable, but it finds the base class version instead.  <br>
reinterpret_cast only changes the pointer's type, not the underlying object's layout or behavior.
It doesn't magically insert the missing derived class members or vtable into the BaseClass object.
Technically, attempting to call a derived class function on a BaseClass object using a reinterpret_cast pointer is undefined behavior in C++.



