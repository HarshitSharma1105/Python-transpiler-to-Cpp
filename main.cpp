#include<fstream>
#include"parser.cpp"

int main(int argc,char* argv[]){
    if(argc<4){
        std::cerr << "errored\n";
        exit(EXIT_FAILURE);
    }
    std::string source,path=argv[1];
    {
        std::ifstream file(path);
        std::string line;
        while (std::getline(file, line)) 
        {
            source += line + "LINEEND\n";
        }
    }
    std::string filename=argv[2];
    bool interpret=(std::string)argv[3]=="interpret";
    bool debugging=(std::string)argv[4]=="debug";
    source.push_back('\0');
    Tokenizer tokenizer(source);
    std::vector<Token> tokens=tokenizer.tokenize();
    if(debugging)
    {
        debug(tokens);
    }
    Parser parser(tokens);
    parser.parse();
    std::string cppsourcecode=parser.generate();
    if(debugging)std::cout << cppsourcecode; 
    std::string cppname=filename+".cpp";
    {
        std::ofstream out(cppname);
        out << cppsourcecode;
    }
    std::string command="g++ "+filename+ ".cpp "+ "-o " + filename;
    system(command.c_str());
    system(argv[2]);
    if(interpret)
    {
        system(("del "+  cppname).c_str());
        system(("del "+ filename + ".exe").c_str());
    }
    exit(EXIT_SUCCESS);
}