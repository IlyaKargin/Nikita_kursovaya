#include <UnitTest++/UnitTest++.h>
#include <UnitTest++/TestReporterStdout.h>

#include <vector>

#include <UserInterface.h>
#include <Comunicator.h>
#include <Logs.h>
#include <ClientBase.h>
#include <ServerError.h>

#include <exception>

auto RunTest (const char* SuiteName)
{ 
    UnitTest::TestReporterStdout reporter;
    UnitTest::TestRunner runner(reporter);
        return runner.RunTestsIf(UnitTest::Test::GetTestList(),
                                SuiteName,
                                UnitTest::True(),0);
}

SUITE(UserInterface){

    TEST(cmdLine_invalid_type){
        std::vector<char*> arguments= {"test","-p","test","-l","logs","-f","usersBase"};

        CHECK_THROW(UserInterface(arguments.size(),arguments.data()),boost::program_options::error);
    }

    TEST(cmdLine_invalid_param){
        std::vector<char*> arguments= {"test","-p","33333","-l","logs","-f","usersBase","-t"};

        CHECK_THROW(UserInterface(arguments.size(),arguments.data()),boost::program_options::error);
    }

}

SUITE(Communicator){
    TEST(communicator_portInUse){
        Comunicator com1;
        com1.Initialize(33333);

        Comunicator com2;
        CHECK_THROW(com2.Initialize(33333),ServerError);
    }
}

SUITE(Logs){
    TEST(Logs_nonWriteable){
        CHECK_THROW(Logs("logs_nonWriteable"),ServerError);
    }
}

SUITE(ClientBase){
    TEST(ClientBase_nonReadable){
        ClientBase cb;
        CHECK_THROW(cb.read("users_nonReadable"),ServerError);
    }

    TEST(ClientBase_empty){
        ClientBase cb;
        CHECK_THROW(cb.read("users_empty"),ServerError);
    }
}

int main() {
    RunTest("UserInterface");
    RunTest("Communicator");
    RunTest("Logs");
    RunTest("ClientBase");

    return 0;
    
}