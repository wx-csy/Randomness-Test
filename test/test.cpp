namespace test{
    double ALPHA = 0.01;

    class TestMethod{
    public:
        double P;

        virtual void run(std::vector<bool> &bits) = 0;
        virtual const char* testName(int lang = 0) = 0;
        bool result(){
            return P > ALPHA;
        }
    };

};
