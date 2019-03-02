#pragma once
#include <memory>

template <class Type>
struct OpNewCreator
{
	static Type* create()
	{
		return new Type;
	}
protected:
	~OpNewCreator() {}
};

template <class Type>
struct MallocCreator
{
	static Type* create()
	{
		void* buf = std::malloc(sizeof(Type));
		if (!buf) return nullptr;
		return new(buf) Type;
	}
protected:
	~MallocCreator() {}
};

template <class Type>
struct PrototypeCreator
{
private:
	Type* prototype;
protected:
	~PrototypeCreator() {}
public:
	PrototypeCreator(Type* obj = nullptr) :prototype(obj)
	{}
	static Type* create()
	{
		if (prototype)
			return prototype->clone();
		return nullptr;
	}
	Type* getPrototype()
	{
		return prototype;
	}

	void setPrototype(Type* obj)
	{
		prototype = obj;
	}
};

