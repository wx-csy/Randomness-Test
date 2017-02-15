namespace test{

    double monobit_frequency_test(const std::vector<bool> &bits){
        if(bits.size()==0){
            cerr<<"Illegal parameter!"<<endl;
            throw;
        }

        int n = bits.size();
        int S = 0;
        double V;
        double P;
        for (int i=0; i<n; i++)
            if(bits[i]) S++; else S--;
        V = fabs(S)/sqrt(n);
        P = erfc(V/sqrt(2));
        cout<<"Monobit frequency test:"<<endl;
        cout<<"    n   = "<<n<<endl;
        cout<<"    S   = "<<S<<endl;
        cout<<"    V   = "<<fixed<<setprecision(6)<<V<<endl;
        cout<<"    P   = "<<fixed<<setprecision(4)<<P*100<<"%"<<endl;
        return P;
    }

    class MonobitFrequencyTest: public TestMethod{
    public:
        void run(std::vector<bool> &bits){
            P = monobit_frequency_test(bits);
        }

        const char* testName(int lang = 0){
            char* names[1] = {"Monobit frequency test"};
            return names[lang];
        }

        MonobitFrequencyTest() {}
        ~MonobitFrequencyTest() {}
    };
}
