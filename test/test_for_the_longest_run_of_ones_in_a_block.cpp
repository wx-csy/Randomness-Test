namespace test{

    //  仅实现了 M=10000 时的情况
    double test_for_the_longest_run_of_ones_in_a_block(const vector<bool> &bits, unsigned int m){
        if (bits.size()==0 || m!=10000 || bits.size()<m){
            cerr<<"Illegal parameter!"<<endl;
            throw;
        }

        int n = bits.size();
        int N = n/m;
        int n_disc = n%m;

        double v[7]={};
        static const double pi[7]={0.0882,0.2092,0.2483,0.1933,0.1208,0.0675,0.0727};
        double V=0;
        double P;

        int lr1, mlr1;
        vector<bool>::const_iterator it=bits.begin();
        for (int i=0; i<N; i++){
            lr1=0; mlr1=0;
            for (int j=0; j<m; j++){
                if (*it) {
                    lr1++;
                    mlr1=max(mlr1,lr1);
                } else {
                    lr1=0;
                }
                it++;
            }
            if (mlr1<=10) v[0]++;
            if (mlr1>=16) v[6]++;
            if (10<mlr1 && mlr1<16) v[mlr1-10]++;
        }

        for (int i=0; i<7; i++){
            V+=(v[i]-N*pi[i])*(v[i]-N*pi[i])/(N*pi[i]);
        }
        P=igamc(3, V/2.0);

        cout<<"Test for the longest run of ones in a block:"<<endl;
        cout<<"    n   = "<<n<<endl;
        cout<<"    m   = "<<m<<endl;
        cout<<"    N   = "<<N<<endl;
        cout<<"    V   = "<<fixed<<setprecision(6)<<V<<endl;
        cout<<"    P   = "<<fixed<<setprecision(4)<<P*100<<"%"<<endl;
        cout<<"  "<<n_disc<<" bits are discarded."<<endl;

        return P;
    }

    class TestForTheLongestRunOfOnesInABolock: public TestMethod{
    public:
        unsigned int m;

        void run(std::vector<bool> &bits){
            P = test_for_the_longest_run_of_ones_in_a_block(bits, m);
        }

        const char* testName(int lang = 0){
            char* names[1] = {"test for the longest run of ones in a block"};
            return names[lang];
        }

        TestForTheLongestRunOfOnesInABolock(unsigned int _m) {m=_m;}
        ~TestForTheLongestRunOfOnesInABolock() {}
    };
}
