#include "EngineCppUnitTest.h"

#include "Core/src/ioc/Container.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

struct Base 
{
	virtual int Test() { return 420; }
	virtual ~Base() = default;
};

struct Derived : public Base
{
	int Test() override { return 69; }
};

using namespace engine;

namespace Ioc
{
	TEST_CLASS(IocTests)
	{
	public:
		TEST_METHOD_INITIALIZE(Init)
		{
			pIoc = std::make_unique<ioc::Container>();
		}
		
		TEST_METHOD(SimpleResolve)
		{
			pIoc->Register<Base>([] { return std::make_shared<Derived>(); });
			Assert::AreEqual(69, pIoc->Resolve<Base>()->Test());
		}
		TEST_METHOD(SimpleResolveFailure)
		{
			Assert::ExpectException<std::runtime_error>([this]
			{
				pIoc->Resolve<Base>();
			});
		}

	private:
		std::unique_ptr<ioc::Container> pIoc;
	};
}
