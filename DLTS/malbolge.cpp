#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

constexpr bool official_implementation = 1, official_specification = 0;

template<bool jf = official_implementation>
class Malbolge {
    private:
    static constexpr char XLAT1_map[] = "+b(29e*j1VMEKLyC})8&m#~W>qxdRp0wkrUo[D7,XTcA\"lI.v%{gJh4G\\-=O@5`_3i<?Z';FNQuY]szf$!BS/|t:Pn6^Ha";
    static constexpr char XLAT2_map[] = "5z]&gqtyfr$(we4{WP)H-Zn,[%\\3dL+Q;>U!pJS72FhOA1CB6v^=I_0/8|jsb9m<.TVac`uY*MK'X~xDl}REokN:#?G\"i@";
    static constexpr unsigned short opcode[7] = {'j','i','*','p','<','/','v'};
    std::vector<unsigned short> mem; unsigned short a,c,d;
    static constexpr unsigned short crz_map[9] = {1,1,2,0,0,2,0,2,1};
    static constexpr unsigned short pow_shi = std::pow(3,9);
    unsigned short XLAT1(unsigned short c, unsigned short p) noexcept {
        if (c<33||c>126){
            std::cerr<<"failed exec XLAT1 encode because `c` is can't print ASCII Code."<<std::endl;
            exit(EXIT_FAILURE);
        }
        c-=33,c=(c+p)%94;
        return XLAT1_map[c];
    }
    unsigned short XLAT2(unsigned short c) noexcept {
        return XLAT2_map[c-33];
    }
    public:
    template<typename T, typename U = int>
    T crazy(T x, T y, U ts) noexcept {
        T r = 0;
        for (U i=0,t=1;i<ts;++i,t*=3) r+=crz_map[(x%3)*3+(y%3)]*t,x/=3,y/=3;
        return r;
    }
    void operator()(const std::string& s) noexcept {
        a = c = d = 0;
        static std::string shi = "0000000000"; static unsigned short shi_r = 0;
        if (s.size() > 59049) {
            std::cerr<<"failed exec Malbolge because source code is longer than 59049."<<std::endl;
            exit(EXIT_FAILURE);
        }
        if (mem.size()!=59049) mem.assign(59049,0);
        copy(s.begin(),s.end(),mem.begin());
        if (s.size()==0) mem[0]=crazy<unsigned short>(0,0,10);
        if (s.size()<2) mem[1]=crazy<unsigned short>(mem[0],0,10);
        for (int i(std::max((int)s.size(),2));i<59049;++i) mem[i]=crazy<unsigned short>(mem[i-1],mem[i-2],10);
        while(true){
            // std::cout << c << ' ' << mem[c] << std::endl;
            // mem[c] = XLAT1(mem[c],c);
            // std::cout << c << ' ' << XLAT1(mem[c],c) << ' ' << (char)XLAT1(mem[c],c) << std::endl;
            switch (XLAT1(mem[c],c)){
                case opcode[0]:
                    d = mem[d];
                    break;
                case opcode[1]:
                    c = mem[d];
                    if (c<33||c>126){
                        std::cerr<<"failed exec Malbolge because `c` is can't print ASCII Code."<<std::endl;
                        exit(EXIT_FAILURE);
                    }
                    break;
                case opcode[2]:
                    a = mem[d] = mem[d]%3*19683+mem[d]/3;
                    break;
                case opcode[3]:
                    a = mem[d] = crazy<unsigned short>(a,mem[d],10);
                    break;
                /* さっき見てた情報と違うことが発覚 */
                case opcode[4+jf]:
                    char tmp;
                    std::cin >> tmp;
                    a = (tmp==EOF?59048:(unsigned short)tmp);
                    break;
                case opcode[5-jf]:
                    std::cout << (char)a;
                    break;
                case opcode[6]:
                    return;
                    break;
                default:
                    break;
            }
            mem[c] = XLAT2(mem[c]),++c,++d,c%=59049,d%=59049;
        }
        return;
    }
};

template<typename T, typename U = int>
T crazy(T x, T y, U ts) noexcept { static Malbolge m; return m.crazy<T, U>(x,y,ts); }

int main(){
    Malbolge mal; mal(R"((=<`:9876Z4321UT.-Q+*)M'&%$H"!~}|Bzy?=|{z]KwZY44Eq0/{mlk**hKs_dG5[m_BA{?-Y;;Vb'rR5431M}/.zHGwEDCBA@98\6543W10/.R,+O<)");
    /*
    > Hello, world.
    R"((=<`:9876Z4321UT.-Q+*)M'&%$H"!~}|Bzy?=|{z]KwZY44Eq0/{mlk**hKs_dG5[m_BA{?-Y;;Vb'rR5431M}/.zHGwEDCBA@98\6543W10/.R,+O<)"
    */
    std::cout << std::endl;
    //std::cout << mal.crazy(100,500) << std::endl;
}