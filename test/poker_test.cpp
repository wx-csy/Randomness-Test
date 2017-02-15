namespace test{

    double poker_test(const vector<bool> &bits, int m){
        if (bits.size()==0 || m<=0 || m>30 || bits.size()<m){
            cerr<<"Illegal parameter!"<<endl;
            throw;
        }

        int* patterns = new int[1<<m];
        int n = bits.size();
        int N = n/m;
        int n_disc = n%m;
        double V=0;
        double P;
        int tmp;

        memset(patterns, 0, sizeof(int)<<m);
        vector<bool>::const_iterator it=bits.begin();
        for (int i=0; i<N; i++){
            tmp=0;
            for (int j=0; j<m; j++){
                tmp<<=1;
                if (*it) tmp++;
                it++;
            }
            patterns[tmp]++;
        }

        for (int i=0; i<(1<<m); i++){
            V+=patterns[i]*patterns[i];
        }
        V*=(1<<m); V/=N; V-=N;
        P=igamc(((1<<m)-1)>>1, V/2);

        cout<<"Poker test:"<<endl;
        cout<<"    n   = "<<n<<endl;
        cout<<"    m   = "<<m<<endl;
        cout<<"    N   = "<<N<<endl;
        cout<<"    V   = "<<fixed<<setprecision(6)<<V<<endl;
        cout<<"    P   = "<<fixed<<setprecision(4)<<P*100<<"%"<<endl;
        cout<<"  "<<n_disc<<" bits are discarded."<<endl;

        delete[] patterns;
        return P;
    }

    class PokerTest: public TestMethod{
    public:
        int m;

        void run(std::vector<bool> &bits){
            P = poker_test(bits, m);
        }

        const char* testName(int lang = 0){
            char* names[1] = {"Poker test"};
            return names[lang];
        }

        PokerTest(int _m) {m = _m;}
        ~PokerTest() {}
    };

}
