namespace test{

    double Discrete_Fourier_Transform_test(const std::vector<bool> &bits){
        if(bits.size()==0){
            cerr<<"Illegal parameter!"<<endl;
            throw;
        }
        int n = bits.size();
        double *r = new double[n];
        double *wsave = new double[2*n];
        int *ifac = new int[15];
        double T=sqrt(2.995732274*n);
        int n_mod = (n+1)/2;
        double N_1=0.0, N_0 = 0.95*n_mod;
        double V;
        double P;

        for (int i=0; i<n; i++){
            if (bits[i]) r[i]=1.0; else r[i]=-1.0;
        }

        algo::__ogg_fdrffti(n, wsave, ifac);
        algo::__ogg_fdrfftf(n, r, wsave, ifac);

        if (fabs(r[0])<T) N_1++;
        for (int i=1; i<n_mod ;i++){
            if (hypot(r[2*i-1], r[2*i])<T) N_1++;
        }

        V = (N_1-N_0)/sqrt(0.95*0.05*n_mod);
        P = erfc(fabs(V)/sqrt(2));

        /*
        for (int i=0; i<n; i++){
            cout<<r[i]<<" ";
        }
        cout<<endl;
        */

        cout<<"Discrete Fourier Transform test:"<<endl;
        cout<<"    n   = "<<n<<endl;
        cout<<"    T   = "<<T<<endl;
        cout<<"   N_0  = "<<fixed<<setprecision(1)<<N_0<<endl;
        cout<<"   N_1  = "<<fixed<<setprecision(1)<<N_1<<endl;
        cout<<"    V   = "<<fixed<<setprecision(6)<<V<<endl;
        cout<<"    P   = "<<fixed<<setprecision(4)<<P*100<<"%"<<endl;
        delete[] r;
        delete[] wsave;
        delete[] ifac;
        return P;

    }

    class DiscreteFourierTransformTest: public TestMethod{
    public:
        void run(std::vector<bool> &bits){
            P = Discrete_Fourier_Transform_test(bits);
        }

        const char* testName(int lang = 0){
            char* names[1] = {"Discrete Fourier Transform test"};
            return names[lang];
        }

        DiscreteFourierTransformTest() {}
        ~DiscreteFourierTransformTest() {}
    };
}
