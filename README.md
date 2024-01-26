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


