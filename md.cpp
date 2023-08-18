#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]){
    std::string str = "aaaaaaaaaaa", in = argv[2], en = "zzzzzzzzzzz";
    str[0] = argv[1][0], en[0] = argv[1][0];
        FILE* fp;
        //cout << (std::string("php -r `printf(\"%x\\n\", crc32(\"")+str+"\"));`") << endl;
        if ((fp = popen((std::string("php -r 'printf(\"%x\\n\", crc32(\"")+str+"\"));' 2> /dev/null").c_str(), "r"))==NULL){
            cerr << "faild crc32" << endl;
            exit(EXIT_FAILURE);
        }
        char buf[1024]; std::string res;
        fgets(buf, sizeof(buf), fp),res = buf;
        for (int i(0);i < res.size();++i){
            if (res[i]==' '||res[i]=='\n'){res.resize(i);break;}
        }
        pclose(fp);
        cout << res << endl;
        if (res==in) cout << str << endl;
        auto it = str.rbegin();
        for (decltype(it) e = str.rend();it!=e;++it){
            if (*it!='z'){ ++(*it); break; }
            else *it = 'a';
        }
}