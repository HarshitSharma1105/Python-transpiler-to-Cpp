#include<fstream>
#include"parser.cpp"

int main(int argc,char* argv[]){
    if(argc<3)
    {
        std::cerr << "give atleast 3 parameters\n";
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
    bool debugging=(std::string)argv[3]=="debug";
    source.push_back('\0');
    Tokenizer tokenizer(source);
    std::vector<Token> tokens=tokenizer.tokenize();
    Parser parser(tokens);
    parser.parse();
    std::string cppsourcecode=parser.generate();
    if(debugging)
    {
        debug(tokens);
        std::cout << cppsourcecode << std::endl; 
    }
    std::string cppname=filename+".cpp";
    {
        std::ofstream out(cppname);
        out << cppsourcecode;
    }
    std::string compilecommand="g++ "+filename+ ".cpp "+ "-o " + filename;
    system(compilecommand.c_str());
    system(argv[2]);
    system(("del "+  cppname).c_str());
    system(("del "+ filename + ".exe").c_str());
    exit(EXIT_SUCCESS);
}