# LearningCPP

# Introdcution
The number of bits that make up a single command vary -- for example, some CPUs process instructions that are always 32 bits long, whereas some other CPUs (such as the x86/x64 family, which you may be using) have instructions that can be a variable length. <br>

**Assemly language**, for e.g., ```mov al, 061h``` sits on top of Machine Language which is atleast readable and writable and is still used today when speed is critical. An **Assembler** converts Assembly langugage to Machine langugage. <br>
It is still not very portable. <br>

Much like assembly programs, programs written in high level languages must be translated into a format the computer can understand before they can be run. There are two primary ways this is done: **compiling and interpreting**. <br>

A **compiler** is a program (or collection of programs) that reads source code (typically written in a high-level language) and translates it into some other language (typically a low-level language, such as assembly or machine language, etc…). Over the years, compilers have become very good at producing fast, optimized code, and in some cases can do a better job than humans can in assembly language! <br> 

An **interpreter** is a program that directly executes the instructions in the source code without requiring them to be compiled into an executable first. But **interpreter** must be installed on every machine where an interpreted program will be run. <br>

Studies have shown that only **20%** of a programmer’s time is actually spent writing the initial program. The other **80%** is spent on maintenance, which can consist of debugging

## Compiler
- Checks for error.
- Second, the compiler translates your C++ code into machine language instructions. These instructions are stored in an intermediate file called an **object file**. Every `.cpp` file generates `.b` or `.obj` file with same name.

## Linker
-  Linker reads in each of the **object files** generated by the compiler and makes sure they are valid.
-  Linker ensures all **cross-file dependencies** are resolved properly. If the linker is unable to connect a reference to something with its definition, you’ll get a linker error, and the linking process will abort.
-   Linker also is capable of **linking library files**. A library file is a collection of precompiled code that has been “packaged up” for reuse in other programs.  

# Basics
source is [here](https://www.goldsborough.me/c/c++/linker/2016/03/30/19-34-25-internal_and_external_linkage_in_c++/)

## Declaration vs Definition
- **Declaration** tells compiler about existense of a variable/function/symbol and it memory address and required storage may not be defined
- **Definition** tells the compiler about what the body of the variable/function/symbol contains and how much memory is required to store it
- In case of reference variables and pointers declarations along with definitions is necessary. In case of pointers they need to have a fixed memory independent of the memory type they are pointing to, in face in deferencing the pointer definition becomes important.

**Functions**
```
int f();               // declaration
int f() { return 42; } // definition
```

**Variables**
```
int x;		//both a declaration and definition
```
x in the case above is initialised with 0 via default constructor of int.

**Separating Declaration and Definition for variables**
```
extern int x; // declaration
int x = 42;   // definition
```

## Foward Declaration

In C++ we forward declare the variable/function with its **type and name without its definition**, so that we can use its body. Doing this save **unncessary compilation**.

_Example_
```
//someFile.hpp
class Class;
void f(Class object);
```
**One definition rule** : You can forward declare as many times as possible but definition can exist only once

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


## Reinterpret_Cast
It doesn't work on the basis of polymorphic behavior like Dynamic casting does.

In the code below:
```
DerivedClass* derived = reinterpret_cast<DerivedClass*>(base);
```
reinterpret_cast takes the BaseClass pointer base and forcefully reinterprets the bits of its address as if they were a DerivedClass pointer.
**It simply creates a new pointer of the target type with the same memory address as the original pointer.**

Since derived is a DerivedClass pointer, the compiler expects a DerivedClass object with its own virtual function table (vtable).
However, the actual object doesn't have a vtable for DerivedClass. It only has the vtable for BaseClass.
When derived->func2(); is called, the compiler incorrectly looks up func2 in the DerivedClass vtable, but it finds the base class version instead.  

reinterpret_cast only changes the pointer's type, not the underlying object's layout or behavior.
It doesn't magically insert the missing derived class members or vtable into the BaseClass object.
Technically, attempting to call a derived class function on a BaseClass object using a reinterpret_cast pointer is undefined behavior in C++.

# Function Pointers

## Typedef
```
typedef return_type (*FunctionPtr)(parameter_types...);

typedef void (*MyFunctionPtr)();
```

## using 
```
using FunctionPtr = return_type (*)(parameter_types...);

using MyFunctionPtr = void (*)();
```

## std::function
```
using FunctionType = std::function<return_type(parameter_types...)>;

using MyFunctionType = std::function<void()>;
```

# C-Style enums vs Class Enums

## Intro
C-Style enums
```
enum Color {green, yellow, blue};

int main()
{
	std::cout << green; //works
}
```

Class enums
```
enum Class Color {green, yellow, blue};

int main()
{
	std::cout << green;	   //doesn't work
	std::cout << Color::green; //works
}
```

## Differences
enum classes are better in these many ways:

1. enum classes can be type specified
```
enum class Color : unsigned int {  // Enum class with underlying type specified
    Red = 1,
    Green,
    Blue };
```

2. enum values can be initialized
```
enum class Day {  // Enum class without specified underlying type
    Monday = 1,
    Tuesday,
    Wednesday };
```
