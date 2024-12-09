#include<fstream>
#include"parser.cpp"

int main(int argc,char* argv[]){
    if(argc<2)
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
    std::string filename="done";
    bool debugging=(std::string)argv[2]=="debug";
    source.push_back('\0');
    Tokenizer tokenizer(source);
    std::vector<Token> tokens=tokenizer.tokenize();
    Parser parser(tokens);
    std::string cppsourcecode=parser.parse();
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
    system(filename.c_str());
    system(("del "+  cppname).c_str());
    system(("del "+ filename + ".exe").c_str());
    exit(EXIT_SUCCESS);
}