namespace test{

    double runs_test(const vector<bool> &bits){
        if (bits.size()==0){
            cerr<<"Illegal parameter!"<<endl;
            throw;
        }
        int n = bits.size();
        double Pi=0;
        int V_obs=1;
        double P;

        for (int i=0; i<n-1; i++){
            if (bits.at(i)!=bits.at(i+1)) V_obs++;
            if (bits.at(i)) Pi++;
        }
        if (bits.at(n-1)) Pi++;
        Pi/=n;

        P=erfc(fabs(V_obs-2.0*n*Pi*(1.0-Pi))/(2.0*sqrt(2.0*n)*Pi*(1.0-Pi)));

        cout<<"Runs test:"<<endl;
        cout<<"    n   = "<<n<<endl;
        cout<<"  V_obs = "<<V_obs<<endl;
        cout<<"    Pi  = "<<fixed<<setprecision(6)<<Pi<<endl;
        cout<<"    P   = "<<fixed<<setprecision(4)<<P*100<<"%"<<endl;

        return P;
    }

    class RunsTest: public TestMethod{
    public:
        int m;

        void run(std::vector<bool> &bits){
            P = runs_test(bits);
        }

        const char* testName(int lang = 0){
            char* names[1] = {"Runs test"};
            return names[lang];
        }

        RunsTest() {}
        ~RunsTest() {}
    };

}
