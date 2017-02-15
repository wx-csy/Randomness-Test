namespace test{

    double approximate_entropy_test(vector<bool> &bits, unsigned int m){
        if (bits.size()==0 || m<1 || m>30){
            cerr<<"Illegal parameter!"<<endl;
            throw;
        }

        int n = bits.size();
        int* pattern;
        unsigned int mask;
        unsigned int tmp;
        double Cjm;
        double phim=0, phim1=0;
        double ApEn;
        double V;
        double P;
        vector<bool>::const_iterator it;

        // round1
        for (int i=0; i<m-1; i++){
            bits.push_back(bits[i]);
        }

        pattern = new int[1<<m];
        mask=(1<<m)-1;
        memset(pattern, 0, sizeof(int)<<m);

        it=bits.begin();
        for (int i=0; i<m-1; i++){
            tmp<<=1;
            if (*it) tmp++;
            it++;
        }
        for (int i=0; i<n; i++){
            tmp<<=1;
            if (*it) tmp++;
            it++;
            pattern[tmp&mask]++;
        }

        for (int i=0; i<(1<<m); i++){
            Cjm = double(pattern[i])/double(n);
            phim+=Cjm*log(Cjm);
        }

        for (int i=0; i<m-1; i++){
            bits.pop_back();
        }
        delete[] pattern;

        // round2
        m++;
        for (int i=0; i<m-1; i++){
            bits.push_back(bits[i]);
        }

        pattern = new int[1<<m];
        mask=(1<<m)-1;
        memset(pattern, 0, sizeof(int)<<m);

        it=bits.begin();
        for (int i=0; i<m-1; i++){
            tmp<<=1;
            if (*it) tmp++;
            it++;
        }
        for (int i=0; i<n; i++){
            tmp<<=1;
            if (*it) tmp++;
            it++;
            pattern[tmp&mask]++;
        }

        for (int i=0; i<(1<<m); i++){
            Cjm = double(pattern[i])/double(n);
            phim1+=Cjm*log(Cjm);
        }

        for (int i=0; i<m-1; i++){
            bits.pop_back();
        }
        delete[] pattern;

        //
        m--;
        ApEn=phim-phim1;
        V=2.0*n*(log(2)-ApEn);
        P=igamc((1<<m)/2.0, V/2.0);

        cout<<"Approximate entropy test:"<<endl;
        cout<<"    n   = "<<n<<endl;
        cout<<"    m   = "<<m<<endl;
        cout<<"  ApEn  = "<<fixed<<setprecision(6)<<ApEn<<endl;
        cout<<"    V   = "<<fixed<<setprecision(6)<<V<<endl;
        cout<<"    P   = "<<fixed<<setprecision(4)<<P*100<<"%"<<endl;

        return P;
    }

    class ApproximateEntropyTest: public TestMethod{
    public:
        unsigned int m;
        void run(std::vector<bool> &bits){
            P = approximate_entropy_test(bits, m);
        }

        const char* testName(int lang = 0){
            char* names[1] = {"Approximate entropy test"};
            return names[lang];
        }

        ApproximateEntropyTest(unsigned int _m) {m=_m;}
        ~ApproximateEntropyTest() {}
    };
}
