namespace test{
    double autocorrelation_test(const std::vector<bool> &bits, unsigned int d){
        if(bits.size()<0 || bits.size()<d){
            cerr<<"Illegal parameter!"<<endl;
            throw;
        }

        int n=bits.size();
        int Ad=0;
        double V;
        double P;

        for (int i=0; i<n-d; i++){
            if (bits[i]^bits[i+d]) Ad++;
        }

        V = 2.0*(Ad-((n-d)/2.0))/sqrt(n-d);
        P = erfc(fabs(V)/sqrt(2));

        cout<<"Autocorrelation test:"<<endl;
        cout<<"    n   = "<<n<<endl;
        cout<<"    d   = "<<d<<endl;
        cout<<"   Ad   = "<<Ad<<endl;
        cout<<"    V   = "<<fixed<<setprecision(6)<<V<<endl;
        cout<<"    P   = "<<fixed<<setprecision(4)<<P*100<<"%"<<endl;
        return P;
    }

    class AutocorrelationTest: public TestMethod{
    public:
        unsigned int d;
        void run(std::vector<bool> &bits){
            P = autocorrelation_test(bits, d);
        }

        const char* testName(int lang = 0){
            char* names[1] = {"Autocorrelation test"};
            return names[lang];
        }

        AutocorrelationTest(unsigned int _d) {d=_d;}
        ~AutocorrelationTest() {}
    };

}
