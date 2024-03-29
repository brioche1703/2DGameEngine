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
	void AttachDriver(std::shared_ptr<log::IDriver>) override {}

	log::Entry entry_;
};

template<> inline std::wstring __cdecl 
Microsoft::VisualStudio::CppUnitTestFramework:: 
	ToString<log::Level>(const log::Level& level) 
{ 
	return log::GetLevelName(level); 
} 

namespace Log
{
	TEST_CLASS(LogTests)
	{
	public:
		TEST_METHOD(ShowOffFluent)
		{
			MockChannel chan;
			engineLog.level(log::Level::Info).note(L"HI").chan(&chan);
			Assert::AreEqual(L"HI"s, chan.entry_.note_);
			Assert::AreEqual(log::Level::Info, chan.entry_.level_); 
		}

		TEST_METHOD(SimplifiedLevelNote)
		{
			MockChannel chan;
			engineLog.info(L"HI").chan(&chan);
			Assert::AreEqual(L"HI"s, chan.entry_.note_);
			Assert::AreEqual(log::Level::Info, chan.entry_.level_);
		}
	};
}
