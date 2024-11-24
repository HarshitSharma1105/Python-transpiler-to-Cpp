#include<fstream>
#include"generator.cpp"

int main(int argc,char* argv[]){
    if(argc<2){
        std::cerr << "errored\n";
        exit(EXIT_FAILURE);
    }
    std::string source,path=argv[1];
    {
        std::ifstream file(path);
        std::string line;
        while (std::getline(file, line)) {
            source += line + "LINEEND\n";
        }
    }
    source.push_back('\0');
    Tokenizer tokenizer(source);
    std::vector<Token> tokens=tokenizer.tokenize();
    // for(const Token& token:tokens){
    //     debug(token.type);
    //     std::cout<< " " << token.val << std::endl;
    // }
    Parser parser(tokens);
    NodeProg nodeprog=parser.parse();
    Generator generator(nodeprog);
    //std::cout << nodeprog.NodeStmts.size() << std::endl;
    std::string cppsourcecode=generator.generate();
    //std::cout << cppsourcecode; 
    std::string filename=argv[2];
    std::string cppname=filename+".cpp";
    {
        std::ofstream out(cppname);
        out << cppsourcecode;
    }
    std::string command="g++ "+filename+ ".cpp "+ "-o " + filename;
    system(command.c_str());
    system(argv[2]);
    if((std::string)argv[3]=="interpret")
    {
    system(("del "+  cppname).c_str());
    system(("del "+ filename + ".exe").c_str());
    }
    exit(EXIT_SUCCESS);
}