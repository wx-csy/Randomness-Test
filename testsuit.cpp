namespace testSuit{
    vector<test::TestMethod*> tests;

    void initDefaultTests(){
        for (test::TestMethod* t:tests) delete t; tests.clear();
        tests.push_back(new test::MonobitFrequencyTest());
        tests.push_back(new test::FrequencyTestWithinABlock(100));
        tests.push_back(new test::PokerTest(4));
        tests.push_back(new test::PokerTest(8));
        tests.push_back(new test::SerialTest(2));
        tests.push_back(new test::SerialTest2(2));
        tests.push_back(new test::SerialTest(5));
        tests.push_back(new test::SerialTest2(5));
        tests.push_back(new test::RunsTest());
        tests.push_back(new test::RunsDistributionTest());
        tests.push_back(new test::TestForTheLongestRunOfOnesInABolock(10000));
        tests.push_back(new test::BinaryDerivativeTest(3));
        tests.push_back(new test::BinaryDerivativeTest(7));
        tests.push_back(new test::AutocorrelationTest(1));
        tests.push_back(new test::AutocorrelationTest(2));
        tests.push_back(new test::AutocorrelationTest(8));
        tests.push_back(new test::AutocorrelationTest(16));
        tests.push_back(new test::BinaryMatrixRankTest(32, 32));
        tests.push_back(new test::CumulativeTest());
        tests.push_back(new test::ApproximateEntropyTest(2));
        tests.push_back(new test::ApproximateEntropyTest(3));
        tests.push_back(new test::LinearComplexityTest(500));
        tests.push_back(new test::MaurersUniversalTest(7, 1280));
        tests.push_back(new test::DiscreteFourierTransformTest());
    }

    void runTest(vector<bool>& bits){
        for (test::TestMethod* t:tests){
            t->run(bits);
        }
        cout<<endl;
        cout<<"           T E S T   R E S U L T       "<<endl;
        cout<<setiosflags(ios::left);
        cout<<setw(50)<<"Name";
        cout<<setw(10)<<" P-value";
        cout<<resetiosflags(ios::left)<<endl;
        cout<<"-----------------------------------------------------------------"<<endl;
        for (test::TestMethod* t:tests){
            cout<<setiosflags(ios::left);
            cout<<setw(50)<<t->testName();
            cout<<resetiosflags(ios::left);
            cout<<setiosflags(ios::right);
            cout<<setw(8)<<setprecision(4)<<t->P*100<<"%";
            cout<<setw(3)<<(t->result()?'P':'F')<<endl;
            cout<<resetiosflags(ios::right);
        }
    }
}
