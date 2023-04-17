#include "EngineCppUnitTest.h"

#include "Core/src/log/EntryBuilder.h"
#include "Core/src/log/Channel.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace engine;
using namespace std::string_literals;


#define engineLog log::EntryBuilder{ __FILEW__, __FUNCTIONW__, __LINE__}

class MockChannel : public log::IChannel
{
public:
	void Submit(log::Entry& e) override
	{
		entry_ = e;
	}
	log::Entry entry_;
};

namespace Infrastructure
{
	TEST_CLASS(LogTests)
	{
	public:
		TEST_METHOD(ShowOffFluent)
		{
			MockChannel chan;
			engineLog.level(log::Level::Info).note(L"HI").chan(&chan);
			Assert::AreEqual(L"HI"s, chan.entry_.note_);
			Assert::IsTrue(log::Level::Info == chan.entry_.level_);
			Assert::AreEqual(31, chan.entry_.sourceLine_);
		}

		TEST_METHOD(SimplifiedLevelNote)
		{
			MockChannel chan;
			engineLog.info(L"HI").chan(&chan);
			Assert::AreEqual(L"HI"s, chan.entry_.note_);
			Assert::IsTrue(log::Level::Info == chan.entry_.level_);
			Assert::AreEqual(40, chan.entry_.sourceLine_);
		}
	};
}
